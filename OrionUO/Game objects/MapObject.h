﻿/***********************************************************************************
**
** MapObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MAPOBJECT_H
#define MAPOBJECT_H
//----------------------------------------------------------------------------------
//!Map object base
class CMapObject : public CRenderWorldObject
{
public:
	/*!
	Constructor
	@param [__in] type Type of render object
	@param [__in] serial Object's serial
	@param [__in] graphic Object's graphic
	@param [__in] color Object's color
	@param [__in] x Coordinate X in the world
	@param [__in] y Coordinate Y in the world
	@param [__in] z Coordinate Z in the world
	@return
	*/
	CMapObject(const RENDER_OBJECT_TYPE &type, const uint &serial, const ushort &graphic, const ushort &color, const short &x, const short &y, const char &z);

	/*!
	Destructor
	@return
	*/
	virtual ~CMapObject();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
