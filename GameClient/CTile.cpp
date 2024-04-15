#include "pch.h"
#include "CTile.h"

#include "CDbgRenderMgr.h"

CTile::CTile()
	: m_Row(1)
	, m_Col(1)
	, m_TileSize(TILE_SIZE)
	, m_JellyData(nullptr)
{

}

CTile::~CTile()
{
}

void CTile::begin()
{
}

void CTile::tick()
{
}

void CTile::render()
{
	if (CDbgRenderMgr::GetInst()->IsDbgRender())
	{
		render_grid();
	}
}

Vec2D CTile::CorrectClickedTile(Vec2D _ClickedPos)
{
	Vec2D vRealMousePos = CCamera::GetInst()->GetRealPos(_ClickedPos);

	if (vRealMousePos.x < GetPos().x || GetPos().x + m_TileSize.x * m_Col + m_TileSize.x < vRealMousePos.x
		|| vRealMousePos.y < GetPos().y || GetPos().y + m_TileSize.y * m_Row + m_TileSize.y < vRealMousePos.y)
		return vRealMousePos;

	float CorrectedPosX = (int)(vRealMousePos.x / m_TileSize.x) * (int)m_TileSize.x + (m_TileSize.x / 2.f);
	float CorrectedPosY = (int)(vRealMousePos.y / m_TileSize.y) * (int)m_TileSize.y + (m_TileSize.x / 2.f);
	return Vec2D(CorrectedPosX, CorrectedPosY);
}

bool CTile::CheckJellyOnTile(Vec2D _ClickedPos)
{
	Vec2D vRealMousePos = CCamera::GetInst()->GetRealPos(_ClickedPos);

	if (vRealMousePos.x < GetPos().x || GetPos().x + m_TileSize.x * m_Col < vRealMousePos.x
		|| vRealMousePos.y < GetPos().y || GetPos().y + m_TileSize.y * m_Row < vRealMousePos.y)
		return true;

	UINT SelectTileCol = (int)(vRealMousePos.x / m_TileSize.x);
	UINT SelectTileRow = (int)(vRealMousePos.y / m_TileSize.y);

	if (IsFilledJellyData(SelectTileCol, SelectTileRow)) return true;
	else return false;
}

UINT CTile::ConvertToColFromMousePos(Vec2D _ClickedPos)
{
	Vec2D vRealMousePos = CCamera::GetInst()->GetRealPos(_ClickedPos);

	UINT SelectTileCol = (int)(vRealMousePos.x / m_TileSize.x);
	
	return SelectTileCol;
}

UINT CTile::ConvertToRowFromMousePos(Vec2D _ClickedPos)
{
	Vec2D vRealMousePos = CCamera::GetInst()->GetRealPos(_ClickedPos);

	UINT SelectTileRow = (int)(vRealMousePos.y / m_TileSize.y);

	return SelectTileRow;
}

UINT CTile::ConvertToColFromRealPos(Vec2D _RealPos)
{
	UINT SelectTileCol = (int)(_RealPos.x / m_TileSize.x);

	return SelectTileCol;
}

UINT CTile::ConvertToRowFromRealPos(Vec2D _RealPos)
{
	UINT SelectTileRow = (int)(_RealPos.y / m_TileSize.y);

	return SelectTileRow;
}



void CTile::InitJellyData()
{
	m_JellyData = new char* [m_Col];

	for (int i = 0; i < m_Col; ++i)
	{
		m_JellyData[i] = new char[m_Row];
	}

	for (int i = 0; i < m_Col; ++i)
	{
		for (int j = 0; j < m_Row; ++j)
		{
			m_JellyData[i][j] = -1;
		}
	}
}

void CTile::ReleaseJellyData()
{
	if (m_JellyData != nullptr)
	{
		for (int i = 0; i < m_Col; ++i)
		{
			delete[] m_JellyData[i];
		}
		delete[] m_JellyData;
		m_JellyData = nullptr;
	}
}

void CTile::render_grid()
{
	Vec2D vRenderPos = GetRenderPos();
	Vec2D vRealPos = GetPos();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	for (UINT i = 0; i < m_Col; ++i)
	{
		for (UINT j = 0; j < m_Row; ++j)
		{
			if (RENDER_MAXPOSX < vRealPos.x + m_TileSize.x * i
				|| vRealPos.x + m_TileSize.x * i + m_TileSize.x < RENDER_MINPOSX)
			{
				break;
			}

			Rectangle(DC, (int)(vRenderPos.x + m_TileSize.x * i), (int)(vRenderPos.y + m_TileSize.y * j)
				, (int)(vRenderPos.x + m_TileSize.x * i + m_TileSize.x), (int)(vRenderPos.y + m_TileSize.y * j + m_TileSize.y));
		}
	}
}

void CTile::SaveToFile(const wstring& _FullPath)
{
}

void CTile::LoadFromFile(const wstring& _FullPath)
{
}

