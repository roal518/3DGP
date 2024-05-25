#include "Mesh.h"
CMesh::CMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{

}
CMesh::~CMesh()
{
	if (m_pd3dVertexBuffer)m_pd3dVertexBuffer->Release();
	if (m_pd3dVertexUploadBuffer)m_pd3dVertexUploadBuffer->Release();
}
void CMesh::ReleaseUploadBuffers()
{
	if (m_pd3dVertexUploadBuffer)m_pd3dVertexUploadBuffer->Release();
	m_pd3dVertexUploadBuffer = NULL;
}
void CMesh::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	//메쉬의 프리미티브 유형을 설정한다.
	pd3dCommandList->IASetPrimitiveTopology(m_d3dPrimitiveToplogy);
	//메쉬의 정점 버퍼 뷰를 설정한다.
	pd3dCommandList->IASetVertexBuffers(m_nSlot, 1, &m_pd3dVertexBufferView);
	//메쉬의 정점 버퍼 뷰를 렌더링한다.(파이프라인을(여기서는 입력 조립기) 작동하게 한다.)
	pd3dCommandList->DrawInstanced(m_nVertices, 1, m_nOffeset, 0);
}


CTriangleMesh::CTriangleMesh(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList) :CMesh(pd3dDevice, pd3dCommandList)
{
	//삼각형 메쉬를 정의했다.
	m_nVertices = 3;
	m_nStride = sizeof(CDiffusedVertex);
	m_d3dPrimitiveToplogy = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	CDiffusedVertex pVertices[3];
	pVertices[0] = CDiffusedVertex(XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f,
		1.0f));
	pVertices[1] = CDiffusedVertex(XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f,
		1.0f));
	pVertices[2] = CDiffusedVertex(XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::Blue));
	// 삼각형 메쉬를 리소스로 생성한다.
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	//정점 버퍼 뷰를 생성한다.
	m_pd3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_pd3dVertexBufferView.StrideInBytes = m_nStride;
	m_pd3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
}