#include "pch.h"
#include "CTile.h"

#include "CDbgRenderMgr.h"

CTile::CTile()
	: m_Row(1)
	, m_Col(1)
	, m_TileSize(TILE_SIZE)
{

}

CTile::~CTile()
{
}


void CTile::SetRow(UINT _Row)
{
	m_Row = _Row;
}

void CTile::SetCol(UINT _Col)
{
	m_Col = _Col;
}

void CTile::SetRowCol(UINT _Row, UINT _Col)
{
	m_Row = _Row;
	m_Col = _Col;
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

