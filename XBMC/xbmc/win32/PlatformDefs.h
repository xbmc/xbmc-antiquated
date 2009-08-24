#ifndef __PLATFORM_DEFS_H__
#define __PLATFORM_DEFS_H__

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

#ifdef _WIN32

#define __STDC_FORMAT_MACROS
#include "inttypes.h"

typedef __int64 off64_t;
typedef __int64 fpos64_t;
typedef __int64 __off64_t;
typedef long    __off_t;

typedef uint32_t  u_int32_t;

#define ssize_t int

#define snprintf _snprintf
#define ftello64 _ftelli64
#define fseeko64 _fseeki64

#ifndef PRIdS
#define PRIdS "Id"
#endif

#define popen   _popen
#define pclose  _pclose 

#define XBMC_LIL_ENDIAN	1234
#define XBMC_BIG_ENDIAN	4321

#if defined(__hppa__) || \
  defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
  (defined(__MIPS__) && defined(__MISPEB__)) || \
  defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
  defined(__sparc__)
#define XBMC_BYTEORDER XBMC_BIG_ENDIAN
#else
#define XBMC_BYTEORDER XBMC_LIL_ENDIAN
#endif

#ifdef HAS_SDL
#include <SDL/SDL_endian.h>
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define XBMC_BYTEORDER XBMC_BIG_ENDIAN
#else
#define XBMC_BYTEORDER = XBMC_LITTLE_ENDIAN
#endif
#endif // SDL

#if XBMC_BYTEORDER == XBMC_BIG_ENDIAN
#define PIXEL_ASHIFT 0
#define PIXEL_RSHIFT 8
#define PIXEL_GSHIFT 16
#define PIXEL_BSHIFT 24
#define AMASK 0x000000ff
#define RMASK 0x0000ff00
#define GMASK 0x00ff0000
#define BMASK 0xff000000
// so we can use endian neutral PIX_FMT_BGRA in place of 
// little endian PIX_FMT_RGB32 when setting up ffmpeg 
#ifndef WORDS_BIGENDIAN
#define WORDS_BIGENDIAN 1
#endif
#else // little endian
#define PIXEL_ASHIFT 24
#define PIXEL_RSHIFT 16
#define PIXEL_GSHIFT 8
#define PIXEL_BSHIFT 0
#define AMASK 0xff000000
#define RMASK 0x00ff0000
#define GMASK 0x0000ff00
#define BMASK 0x000000ff
#endif


#ifndef va_copy
#define va_copy(dst, src) ((dst) = (src))
#endif

#define lrint(x) ((x) >= 0 ? ((int)((x) + 0.5)) : ((int)((x) - 0.5)))
#define llrint(x) ((x) >= 0 ? ((__int64)((x) + 0.5)) : ((__int64)((x) - 0.5)))

extern "C" char * strptime(const char *buf, const char *fmt, struct tm *tm);
#endif // _WIN32

#endif //__PLATFORM_DEFS_H__

