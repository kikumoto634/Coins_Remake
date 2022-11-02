#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>
#include <string>
#include <wrl.h>
#include <d3dx12.h>

#include "Window.h"

/// <summary>
/// DirectXCommon
/// </summary>
class DirectXCommon
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static DirectXCommon* GetInstance();

	void Initialize(Window* window);
	void BeginDraw();
	void EndDraw();

	ID3D12Device* GetDevice()		{return device.Get();}
	ID3D12GraphicsCommandList* GetCommandList()		{return commandList.Get();}

private:
	/// <summary>
	/// ����
	/// </summary>
	
	HRESULT CreateDevice();
	HRESULT CreateCommand();
	HRESULT CreateSwapChain();
	HRESULT CreateRTV();
	HRESULT CreateDSV();
	HRESULT CreateFence();

private:
	Window* window = nullptr;

	//DXGI�t�@�N�g���[
	ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	//�f�o�C�X
	ComPtr<ID3D12Device> device = nullptr;
	//�O���t�B�b�N�X�R�}���h
	ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;
	//�R�}���h�A���P�[�^
	ComPtr<ID3D12CommandAllocator> commandAllocator = nullptr;
	//�R�}���h�L���[
	ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	//�X���b�v�`�F�[��
	ComPtr<IDXGISwapChain4> swapChain  = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuffer = nullptr;
	//�[�x�X�e���V���r���[
	ComPtr<ID3D12DescriptorHeap> dsvHeap= nullptr;
	//�����_�[�^�[�Q�b�g�r���[
	ComPtr<ID3D12DescriptorHeap> rtvHeap= nullptr;
	//�t�F���X
	ComPtr<ID3D12Fence> fence= nullptr;
	UINT64 fenceVal = 0;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvH;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH;
};

