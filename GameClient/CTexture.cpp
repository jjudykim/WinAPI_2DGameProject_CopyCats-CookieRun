#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"

CTexture::CTexture()
	: m_hDC{}
	, m_hBit{}
	, m_pBit{}
	, m_Info{}
	, m_Path{}
{
}

CTexture::~CTexture()
{
}

int CTexture::Create(UINT _Width, UINT _Height)
{
	// DC 생성
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	// Bitmap 생성
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, _Height);

	// SubDC 가 SubBitmap 을 지정하게 함
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBitmap);

	// 로드된 비트맵의 정보를 확인한다.
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return S_OK;
}

int CTexture::CreateWithAlpha(UINT _Width, UINT _Height)
{
	Bitmap bitmap(_Width, _Height, PixelFormat32bppARGB);
	Graphics graphics(&bitmap);

	Color color(128, 0, 0, 255);
	SolidBrush brush(color);

	graphics.FillRectangle(&brush, 0, 0, _Width, _Height);
	
	bitmap.GetHBITMAP(Color::Black, &m_hBit);
	m_hDC = CreateCompatibleDC(nullptr);
	SelectObject(m_hDC, m_hBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return S_OK;
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
			LOG(LOG_TYPE::DBG_ERROR, L"비트맵 Asset 로딩 실패");
			return E_FAIL;
		}

		m_Path = _strFilePath;
	}
	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gdiplusinput = {};
		GdiplusStartup(&gdiplusToken, &gdiplusinput, nullptr);

		Image* pImg = Image::FromFile(_strFilePath.c_str(), 0);
		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		m_pBit = pBitmap;
		Gdiplus::Status status = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);
		assert(status == Gdiplus::Status::Ok);
		m_Path = _strFilePath;
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

