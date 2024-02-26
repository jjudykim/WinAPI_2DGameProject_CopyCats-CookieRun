#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

CTexture::CTexture()
	: m_hDC{}
	, m_hBit{}
	, m_Info{}
{
}

CTexture::~CTexture()
{
}

int CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (m_hBit == nullptr)
	{
		return E_FAIL;
	}

	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	return S_OK;
}

