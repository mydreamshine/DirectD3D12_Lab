#pragma once
class CGameFramework
{
private:
	HINSTANCE                  m_hInstance;
	HWND                       m_hWnd;

	int                        m_nWndClientWidth;
	int                        m_nWndClientHeight;

	//Direct3D Device
	IDXGIFactory6             *m_pdxgiFactory;
	IDXGISwapChain4           *m_pdxgiSwapChain;
	ID3D12Device              *m_pd3dDevice;

	//Multi Sampling
	bool                       m_bMsaa4xEnable = false;
	UINT                       m_nMsaa4xQualityLevels = 0;

	//Swap Chain
	static const UINT          m_nSwapChainBuffers = 2;
	UINT                       m_nSwapChainBufferIndex;

	//Render Target Buffers
	ID3D12Resource            *m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap      *m_pd3dRtvDescriptorHeap;
	UINT                       m_nRtvDescriptorIncrementSize;

	//Depth-Stencil Buffer
	ID3D12Resource            *m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap      *m_pd3dDsvDescriptorHeap;
	UINT                       m_nDsvDescriptorIncrementSize;

	//Graphics Command Management
	ID3D12CommandQueue        *m_pd3dCommandQueue;
	ID3D12CommandAllocator    *m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList *m_pd3dCommandList;

	//Synchronization between CPU and GPU
	ID3D12Fence               *m_pd3dFence;
	UINT64                     m_nFenceValue;
	HANDLE                     m_hFenceEvenet;

#if defined(_DEBUG)
	ID3D12Debug               *m_pd3dDebugController;
#endif

	//Wnd View Set
	D3D12_VIEWPORT             m_d3dViewport;
	D3D12_RECT                 m_d3dScissorRect;

public:
	CGameFramework();
	~CGameFramework();

	//Initallization "GameFramework"
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	//Create Direct3D Device
	void CreateSwapChain();
	void CreateDirect3DDevice();
	void CreateRtvAndDsvDescriptorHeaps();
	void CreateCommandQueueAndList();

	//Build GameObject
	void BuildObject();
	void ReleaseObject();

	//Framework Processing
	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	//Synchronization between CPU and GPU
	void WaitForGpuComplete();

	//Wnd Message Processing
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyBoardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
};

