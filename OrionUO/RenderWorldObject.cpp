﻿/***********************************************************************************
**
** RenderWorldObject.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "RenderWorldObject.h"
#include "SelectedObject.h"
#include "PressedObject.h"
#include "Managers/ConfigManager.h"
//----------------------------------------------------------------------------------
//---------------------------------RenderWorldObject--------------------------------
//----------------------------------------------------------------------------------
CRenderWorldObject::CRenderWorldObject(const RENDER_OBJECT_TYPE &renderType, const uint &serial, const ushort &graphic, const ushort &color, const int &x, const int &y, const char &z)
: CRenderObject(serial, graphic, color, x, y), m_RenderType(renderType),
m_Z(z), m_NextXY(NULL), m_PrevXY(NULL), m_RenderQueueIndex(0), m_NoDrawTile(false)
#if UO_RENDER_LIST_SORT == 1
, m_CurrentRenderIndex(0)
#endif
{
	WISPFUN_DEBUG("c202_f1");
	m_DrawTextureColor[0] = 0xFF;
	m_DrawTextureColor[1] = 0xFF;
	m_DrawTextureColor[2] = 0xFF;
	m_DrawTextureColor[3] = 0x00;
}
//---------------------------------------------------------------------------
CRenderWorldObject::~CRenderWorldObject()
{
	WISPFUN_DEBUG("c202_f2");
	RemoveRender();
}
//---------------------------------------------------------------------------
bool CRenderWorldObject::ProcessAlpha(const int &maxAlpha)
{
	WISPFUN_DEBUG("c202_f3");
	if (!g_ConfigManager.RemoveOrCreateObjectsWithBlending)
	{
		m_DrawTextureColor[3] = (uchar)maxAlpha;

		return (maxAlpha != 0);
	}

	bool result = false;
	int alpha = (int)m_DrawTextureColor[3];

	if (alpha > maxAlpha)
	{
		alpha -= ALPHA_STEP;

		if (alpha < maxAlpha)
			alpha = maxAlpha;

		result = true;
	}
	else if (alpha < maxAlpha)
	{
		alpha += ALPHA_STEP;

		if (alpha > maxAlpha)
			alpha = maxAlpha;

		result = true;
	}

	m_DrawTextureColor[3] = (uchar)alpha;

	return result;
}
//---------------------------------------------------------------------------
void CRenderWorldObject::RemoveRender()
{
	WISPFUN_DEBUG("c202_f4");
	if (m_PrevXY != NULL)
		m_PrevXY->m_NextXY = m_NextXY;

	if (m_NextXY != NULL)
		m_NextXY->m_PrevXY = m_PrevXY;

	m_NextXY = NULL;
	m_PrevXY = NULL;
}
//---------------------------------------------------------------------------
bool CRenderWorldObject::RemovedFromRender()
{
	return m_NextXY == NULL && m_PrevXY == NULL;
}
//---------------------------------------------------------------------------
CLandObject *CRenderWorldObject::GetLand()
{
	WISPFUN_DEBUG("c202_f5");
	CRenderWorldObject *land = this;

	while (land != NULL && !land->IsLandObject())
		land = land->m_NextXY;

	return (CLandObject*)land;
}
//---------------------------------------------------------------------------