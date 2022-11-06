#include "DirectXCommon.h"
#include <cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

DirectXCommon *DirectXCommon::GetInstance()
{
	static DirectXCommon dxcommon;
	return &dxcommon;
}

void DirectXCommon::Initialize(Window *window)
{
	this->window = window;

	//FPX�Œ菉����
	//InitializeFixFPS();

	///�f�o�b�N���C���[
#ifdef _DEBUG
	//�f�o�b�N���C���[���I����
	ID3D12Debug* debugController= nullptr;
	if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))){
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG

	if(FAILED(CreateDevice())) assert(0);
	if(FAILED(CreateCommand())) assert(0);
	if(FAILED(CreateSwapChain())) assert(0);
	if(FAILED(CreateRTV())) assert(0);
	if(FAILED(CreateDSV())) assert(0);
	if(FAILED(CreateFence())) assert(0);
}

void DirectXCommon::BeginDraw()
{
	//���\�[�X�o���A
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	//���\�[�X�o���A�������݉\
	commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	//�`���̕ύX
	//���\�[�X�o���A�r���[
	rtvH = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvH.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//�[�x�o�b�t�@�r���[
	dsvH = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	commandList->OMSetRenderTargets(1, &rtvH, false, &dsvH);


	//�N���A�R�}���h
	//�F
	FLOAT clearColor[] = {0.1f, 0.25f, 0.5f, 0.0f};
	//��ʃN���A
	commandList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//�[�x�N���A
	commandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH,1.f,0,0,nullptr);

	//�r���[�|�[�g
	commandList->RSSetViewports(1, &CD3DX12_VIEWPORT(0.0f, 0.0f, (float)window->GetWindowWidth(), (float)window->GetWindowHeight()));
	//�V�U�[��`
	commandList->RSSetScissorRects(1, &CD3DX12_RECT(0, 0, (LONG)window->GetWindowWidth(), (LONG)window->GetWindowHeight()));
}

void DirectXCommon::EndDraw()
{
	//���\�[�X�o���A
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();
	commandList->ResourceBarrier(1,&CD3DX12_RESOURCE_BARRIER::Transition(backBuffers[bbIndex].Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	//�R�}���h���X�g
	//���߃N���[�Y
	commandList->Close();
	//�R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = {commandList.Get()};
	commandQueue->ExecuteCommandLists(1, commandLists);

	//�R�}���h�����҂�
	commandQueue->Signal(fence.Get(), ++fenceVal);
	if(fence->GetCompletedValue() != fenceVal)
	{
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}

	//FPS�Œ�
	//UpdateFixFPS();

	//�L���[�N���A
	commandAllocator->Reset();
	//�ĂуR�}���h���X�g�𗭂߂鏀��
	commandList->Reset(commandAllocator.Get(), nullptr);

	//��ʂɕ\������o�b�t�@���t���b�v(�\���̓���ւ�)
	swapChain->Present(1, 0);
}

HRESULT DirectXCommon::CreateDevice()
{
	HRESULT result;

	///�f�o�C�X�̐���(1�Q�[���Ɉ��)
	//�Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[] = 
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	///�A�_�v�^��
	//DXGI�t�@�N�g���[
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	if(FAILED(result)){
		return result;
	}

	//�A�_�v�^�[�̗񋓗p
	std::vector<ComPtr<IDXGIAdapter4>> adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter = nullptr;

	//�p�t�H�[�}���X���������̂��珇�ɁA���ׂẴA�_�v�^��񋓂���
	for(UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		//���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}

	///�A�_�v�^�̑I��
	//�œ|�ȃA�_�v�^��I�ʂ���
	for(size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		//�A�_�v�^�[�̏����擾����
		adapters[i]->GetDesc3(&adapterDesc);

		//�\�t�g�E�F�A�f�o�C�X�����
		if(!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			//�f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i].Get();
			break;
		}
	}

	D3D_FEATURE_LEVEL featureLevel;
	for(size_t i = 0; i < _countof(levels); i++)
	{
		//�̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&device));
		if(SUCCEEDED(result))
		{
			//�f�o�C�X�𐶐��o�������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}
	return result;
}

HRESULT DirectXCommon::CreateCommand()
{
	HRESULT result;

	///�R�}���h���X�g(GPU�ɁA�܂Ƃ߂Ė��߂𑗂邽�߂̃R�}���h)
	//�R�}���h�A���P�[�^�𐶐�
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)
	);
	if(FAILED(result)){
		return result;
	}

	//�R�}���h���X�g�𐶐�
	result = device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(&commandList)
	);
	if(FAILED(result)){
		return result;
	}


	///�R�}���h�L���[(�R�}���h���X�g��GPU�ɏ��ʎ��s�����Ă����d�g��)
	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�R�}���h�L���[�𐶐�
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	if(FAILED(result)){
		return result;
	}

	return result;
}

HRESULT DirectXCommon::CreateSwapChain()
{
	HRESULT result;

	///�X���b�v�`�F�[��(�t�����g�o�b�t�@�A�o�b�N�o�b�t�@�����ւ��ăp���p����������)
	//�ݒ�
	swapChainDesc.Width = window->GetWindowWidth();
	swapChainDesc.Height = window->GetWindowHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				//�F��񏑎�
	swapChainDesc.SampleDesc.Count = 1;								//�}���`�T���v�����Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				//�o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;									//�o�b�t�@�����ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		//�t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//����
	//IDXGISwapChain1��ComPtr�p��
	ComPtr<IDXGISwapChain1> swapchain1;
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(),
		window->GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapchain1
	);


	//��������IDXGISwapChain1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	swapchain1.As(&swapChain);
	if(FAILED(result)){
		return result;
	}

	return result;
}

HRESULT DirectXCommon::CreateRTV()
{
	HRESULT result;

	///�����_�[�^�[�Q�b�g�r���[(�o�b�N�o�b�t�@��`��L�����o�X�Ƃ��Ĉ����I�u�W�F�N�g)
	//�f�X�N���v�^�q�[�v����(�����_�[�^�[�Q�b�g�r���[�̓f�X�N���v�^�q�[�v�ɐ�������̂ŏ���)
	//�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		//�����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;	//�\���̓��(�_�u���o�b�t�@�����O)
	//����
	result = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	if(FAILED(result)){
		return result;
	}

	//�o�b�N�o�b�t�@(�X���b�v�`�F�[�����Ő������ꂽ�o�b�N�o�b�t�@�̃A�h���X���e�p)
	backBuffers.resize(swapChainDesc.BufferCount);

	//�����_�[�^�[�Q�b�g�r���[(RTV)����
	//�X���b�v�`�F�[���̂��ׂẴo�b�t�@�ɂ��ď�������
	for(size_t i = 0; i < backBuffers.size(); i++)
	{
		//�X���b�v�`�F�[������o�b�t�@���擾
		result = swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		if(FAILED(result)){
			return result;
		}

		//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//�V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//�����_�[�^�[�Q�b�g�r���[�̐���
		device->CreateRenderTargetView
		(
			backBuffers[i].Get(),
			&rtvDesc,
			CD3DX12_CPU_DESCRIPTOR_HANDLE//�f�X�N���v�^�q�[�v�̃n���h�����擾
			(//�\�����ŃA�h���X�������
				rtvHeap->GetCPUDescriptorHandleForHeapStart(),
				INT(i),
				device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type)
			)
		);
	}
	return result;
}

HRESULT DirectXCommon::CreateDSV()
{
	HRESULT result;

	///�[�x�o�b�t�@�̃��\�[�X(�e�N�X�`���̈��)
	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC depthReourceDesc = CD3DX12_RESOURCE_DESC::Tex2D
		(
			DXGI_FORMAT_D32_FLOAT,
			window->GetWindowWidth(),
			window->GetWindowHeight(),
			1,0,
			1,0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);
	//�[�x�o�b�t�@�̐���
	result = device->CreateCommittedResource
		(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
			D3D12_HEAP_FLAG_NONE,
			&depthReourceDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,	//�[�x�l�������݂Ɏg�p
			&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0),
			IID_PPV_ARGS(&depthBuffer)
		);
	if(FAILED(result)){
		return result;
	}
	
	//�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬(DSV)
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1;			//�[�x�r���[�͈��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;	//�f�v�X�X�e���V���r���[
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	if(FAILED(result)){
		return result;
	}
	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuffer.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);

	return result;
}

HRESULT DirectXCommon::CreateFence()
{
	HRESULT result;

	///�t�F���X(CPU��GPU�œ������Ƃ邽�߂̎d�g��)
	//����
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if(FAILED(result)){
		return result;
	}
	return result;
}

void DirectXCommon::InitializeFixFPS()
{
	reference_ = std::chrono::steady_clock::now();
}

void DirectXCommon::UpdateFixFPS()
{
	//1/60�b�҂�����̎���
	const std::chrono::microseconds kMinTime(uint64_t(1000000.0f/60.0f));
	//1/60�b���킸���ɒZ������
	const std::chrono::microseconds kMinCheckTime(uint64_t(1000000.0f/65.0f));

	//���ݎ��Ԃ��擾
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	//�O��L�^����̌o�ߎ��Ԃ��擾����
	std::chrono::microseconds elapsed = 
		std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	//1/60�b(���킸���ɒZ������)�o���Ă��Ȃ��ꍇ
	if(elapsed < kMinCheckTime){
		//1/60�b�o�߂���܂Ŕ����ȃX���[�v���J��Ԃ�
		while(std::chrono::steady_clock::now() - reference_ < kMinTime){
			//1�}�C�N���b�X���[�v
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	//���݂̎��Ԃ��L�^����
	reference_ = std::chrono::steady_clock::now();
}

