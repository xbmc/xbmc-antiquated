/*
*      Copyright (C) 2005-2008 Team XBMC
*      http://www.xbmc.org
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with XBMC; see the file COPYING.  If not, write to
*  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*  http://www.gnu.org/copyleft/gpl.html
*
*/

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#pragma once

#include "WinSystem.h"
#include "Geometry.h"
#include "StdString.h"


typedef enum _RenderingSystemType
{
  RENDERING_SYSTEM_OPENGL,
  RENDERING_SYSTEM_DIRECTX
} RenderingSystemType;


class CRenderSystemBase
{
public:
  CRenderSystemBase();
  virtual ~CRenderSystemBase();

  RenderingSystemType GetRenderingSystemType() { return m_enumRenderingSystem; }

  virtual bool InitRenderSystem() = 0;
  virtual bool DestroyRenderSystem() = 0;

  virtual void GetRenderVersion(unsigned int& major, unsigned int& minor) = 0;
  virtual CStdString GetRenderVendor() = 0;
  virtual CStdString GetRenderRenderer() = 0;
  virtual bool BeginRender() = 0;
  virtual bool EndRender() = 0;
  virtual bool PresentRender() = 0;
  virtual bool ClearBuffers(DWORD color) = 0;
  virtual bool ClearBuffers(float r, float g, float b, float a) = 0;
  virtual bool IsExtSupported(CStdString strExt) = 0;

  virtual void SetVSync(bool vsync) = 0;
  virtual bool GetVSync() { return m_bVSync; }

  virtual void SetViewPort(CRect& viewPort) = 0;
  virtual void GetViewPort(CRect& viewPort) = 0;

  virtual bool TestRender() = 0;

protected:
  bool m_bRenderCreated;
  RenderingSystemType m_enumRenderingSystem;
  bool m_bVSync;
};

#endif // RENDER_SYSTEM_H
