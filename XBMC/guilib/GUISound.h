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

#pragma once

#ifdef HAS_SDL_AUDIO
#include <SDL_mixer.h>
#endif

class CGUISound
{
public:
  CGUISound();
  virtual ~CGUISound();

  bool        Load(const CStdString& strFile);
  void        Play();
  void        Stop();
  bool        IsPlaying();
  void        SetVolume(int level);

private:
#ifndef HAS_SDL_AUDIO
  bool        LoadWav(const CStdString& strFile, WAVEFORMATEX* wfx, LPBYTE* ppWavData, int* pDataSize);
  bool        CreateBuffer(LPWAVEFORMATEX wfx, int iLength);
  bool        FillBuffer(LPBYTE pbData, int iLength);
  void        FreeBuffer();

  LPDIRECTSOUNDBUFFER m_soundBuffer;
#else
  Mix_Chunk* m_soundBuffer;  
#endif
};
