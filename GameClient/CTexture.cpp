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
	wchar_t szExt[50] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);

	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (m_hBit == nullptr)
		{
			LOG(LOG_TYPE::DBG_ERROR, "비트맵 Asset 로딩 실패");
			return E_FAIL;
		}
	}
	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gdiplusinput = {};
		GdiplusStartup(&gdiplusToken, &gdiplusinput, nullptr);

		Image* pImg = Image::FromFile(_strFilePath.c_str(), 0);
		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Gdiplus::Status status = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);
		assert(status == Gdiplus::Status::Ok);
	}
	else
	{
		assert(nullptr);
	}

	

	

	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	return S_OK;
}

