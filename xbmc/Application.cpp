/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://xbmc.org
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

#if (defined HAVE_CONFIG_H) && (!defined WIN32)
  #include "config.h"
#endif
#include "Application.h"
#include "utils/Builtins.h"
#include "utils/Variant.h"
#include "Splash.h"
#include "KeyboardLayoutConfiguration.h"
#include "LangInfo.h"
#include "Util.h"
#include "Picture.h"
#include "TextureManager.h"
#include "cores/dvdplayer/DVDFileInfo.h"
#include "PlayListPlayer.h"
#include "Autorun.h"
#ifdef HAS_LCD
#include "utils/LCDFactory.h"
#endif
#include "GUIControlProfiler.h"
#include "LangCodeExpander.h"
#include "utils/GUIInfoManager.h"
#include "PlayListFactory.h"
#include "GUIFontManager.h"
#include "GUIColorManager.h"
#include "GUITextLayout.h"
#include "addons/Skin.h"
#ifdef HAS_PYTHON
#include "lib/libPython/XBPython.h"
#endif
#include "ButtonTranslator.h"
#include "GUIAudioManager.h"
#include "lib/libscrobbler/lastfmscrobbler.h"
#include "lib/libscrobbler/librefmscrobbler.h"
#include "GUIPassword.h"
#include "ApplicationMessenger.h"
#include "SectionLoader.h"
#include "cores/DllLoader/DllLoaderContainer.h"
#include "GUIUserMessages.h"
#include "FileSystem/DirectoryCache.h"
#include "FileSystem/StackDirectory.h"
#include "FileSystem/SpecialProtocol.h"
#include "FileSystem/DllLibCurl.h"
#include "FileSystem/MythSession.h"
#include "FileSystem/PluginDirectory.h"
#ifdef HAS_FILESYSTEM_SAP
#include "FileSystem/SAPDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_HTSP
#include "FileSystem/HTSPDirectory.h"
#endif
#include "utils/TuxBoxUtil.h"
#include "utils/SystemInfo.h"
#include "utils/TimeUtils.h"
#include "GUILargeTextureManager.h"
#include "TextureCache.h"
#include "LastFmManager.h"
#include "SmartPlaylist.h"
#ifdef HAS_FILESYSTEM_RAR
#include "FileSystem/RarManager.h"
#endif
#include "PlayList.h"
#include "WindowingFactory.h"
#include "PowerManager.h"
#include "DPMSSupport.h"
#include "Settings.h"
#include "AdvancedSettings.h"
#include "LocalizeStrings.h"
#include "CPUInfo.h"

#include "KeyboardStat.h"
#include "MouseStat.h"

#if defined(FILESYSTEM) && !defined(_LINUX)
#include "FileSystem/FileDAAP.h"
#endif
#ifdef HAS_UPNP
#include "UPnP.h"
#include "FileSystem/UPnPDirectory.h"
#endif
#if defined(_LINUX) && defined(HAS_FILESYSTEM_SMB)
#include "FileSystem/SMBDirectory.h"
#endif
#ifdef HAS_FILESYSTEM_SFTP
#include "FileSystem/FileSFTP.h"
#endif
#include "PartyModeManager.h"
#ifdef HAS_VIDEO_PLAYBACK
#include "cores/VideoRenderers/RenderManager.h"
#endif
#ifdef HAS_KARAOKE
#include "karaoke/karaokelyricsmanager.h"
#include "karaoke/GUIDialogKaraokeSongSelector.h"
#include "karaoke/GUIWindowKaraokeLyrics.h"
#endif
#include "AudioContext.h"
#include "GUIFontTTF.h"
#include "utils/Network.h"
#include "utils/IoSupport.h"
#include "Zeroconf.h"
#include "ZeroconfBrowser.h"
#ifndef _LINUX
#include "utils/Win32Exception.h"
#endif
#ifdef HAS_EVENT_SERVER
#include "utils/EventServer.h"
#endif
#ifdef HAS_DBUS_SERVER
#include "utils/DbusServer.h"
#endif
#ifdef HAS_HTTPAPI
#include "lib/libhttpapi/XBMChttp.h"
#endif
#ifdef HAS_JSONRPC
#include "lib/libjsonrpc/JSONRPC.h"
#include "lib/libjsonrpc/TCPServer.h"
#endif
#if defined(HAVE_LIBCRYSTALHD)
#include "cores/dvdplayer/DVDCodecs/Video/CrystalHD.h"
#endif
#include "utils/AnnouncementManager.h"

// Windows includes
#include "GUIWindowManager.h"
#include "GUIWindowHome.h"
#include "GUIStandardWindow.h"
#include "GUIWindowSettings.h"
#include "GUIWindowFileManager.h"
#include "GUIWindowSettingsCategory.h"
#include "GUIWindowMusicPlaylist.h"
#include "GUIWindowMusicSongs.h"
#include "GUIWindowMusicNav.h"
#include "GUIWindowMusicPlaylistEditor.h"
#include "GUIWindowVideoPlaylist.h"
#include "GUIWindowMusicInfo.h"
#include "GUIWindowVideoInfo.h"
#include "GUIWindowVideoFiles.h"
#include "GUIWindowVideoNav.h"
#include "GUIWindowSettingsProfile.h"
#ifdef HAS_GL
#include "GUIWindowTestPatternGL.h"
#endif
#ifdef HAS_DX
#include "GUIWindowTestPatternDX.h"
#endif
#include "GUIWindowSettingsScreenCalibration.h"
#include "GUIWindowPrograms.h"
#include "GUIWindowPictures.h"
#include "GUIWindowWeather.h"
#include "GUIWindowLoginScreen.h"
#include "GUIWindowAddonBrowser.h"
#include "GUIWindowVisualisation.h"
#include "GUIWindowSystemInfo.h"
#include "GUIWindowScreensaver.h"
#include "GUIWindowSlideShow.h"
#include "GUIWindowStartup.h"
#include "GUIWindowFullScreen.h"
#include "GUIWindowOSD.h"
#include "GUIWindowMusicOverlay.h"
#include "GUIWindowVideoOverlay.h"

// Dialog includes
#include "GUIDialogMusicOSD.h"
#include "GUIDialogVisualisationPresetList.h"
#include "GUIDialogTextViewer.h"
#include "GUIDialogNetworkSetup.h"
#include "GUIDialogMediaSource.h"
#include "GUIDialogVideoSettings.h"
#include "GUIDialogAudioSubtitleSettings.h"
#include "GUIDialogVideoBookmarks.h"
#include "GUIDialogProfileSettings.h"
#include "GUIDialogLockSettings.h"
#include "GUIDialogContentSettings.h"
#include "GUIDialogVideoScan.h"
#include "GUIDialogBusy.h"
#include "GUIDialogKeyboard.h"
#include "GUIDialogYesNo.h"
#include "GUIDialogOK.h"
#include "GUIDialogProgress.h"
#include "GUIDialogSelect.h"
#include "GUIDialogFileStacking.h"
#include "GUIDialogNumeric.h"
#include "GUIDialogGamepad.h"
#include "GUIDialogSubMenu.h"
#include "GUIDialogFavourites.h"
#include "GUIDialogButtonMenu.h"
#include "GUIDialogContextMenu.h"
#include "GUIDialogMusicScan.h"
#include "GUIDialogPlayerControls.h"
#include "GUIDialogSongInfo.h"
#include "GUIDialogSmartPlaylistEditor.h"
#include "GUIDialogSmartPlaylistRule.h"
#include "GUIDialogPictureInfo.h"
#include "GUIDialogAddonSettings.h"
#include "GUIDialogAddonInfo.h"
#ifdef HAS_LINUX_NETWORK
#include "GUIDialogAccessPoints.h"
#endif
#include "GUIDialogFullScreenInfo.h"
#include "GUIDialogTeletext.h"
#include "GUIDialogSlider.h"
#include "GUIControlFactory.h"
#include "cores/dlgcache.h"

#ifdef HAS_PERFORMANCE_SAMPLE
#include "utils/PerformanceSample.h"
#else
#define MEASURE_FUNCTION
#endif

#ifdef HAS_SDL_AUDIO
#include <SDL/SDL_mixer.h>
#endif
#ifdef _WIN32
#include <shlobj.h>
#include "win32util.h"
#endif
#ifdef HAS_XRANDR
#include "XRandR.h"
#endif
#ifdef __APPLE__
#include "CocoaInterface.h"
#include "XBMCHelper.h"
#endif

#ifdef HAS_DVD_DRIVE
#include <cdio/logging.h>
#endif

#ifdef HAS_HAL
#include "linux/HALManager.h"
#endif

#include "MediaManager.h"
#include "utils/JobManager.h"
#include "utils/SaveFileStateJob.h"
#include "utils/AlarmClock.h"

#ifdef _LINUX
#include "XHandle.h"
#endif

#ifdef HAS_LIRC
#include "common/LIRC.h"
#endif
#ifdef HAS_IRSERVERSUITE
  #include "common/IRServerSuite/IRServerSuite.h"
#endif

using namespace std;
using namespace ADDON;
using namespace XFILE;
#ifdef HAS_DVD_DRIVE
using namespace MEDIA_DETECT;
#endif
using namespace PLAYLIST;
using namespace VIDEO;
using namespace MUSIC_INFO;
#ifdef HAS_EVENT_SERVER
using namespace EVENTSERVER;
#endif
#ifdef HAS_DBUS_SERVER
using namespace DBUSSERVER;
#endif
#ifdef HAS_JSONRPC
using namespace JSONRPC;
#endif
using namespace ANNOUNCEMENT;

// uncomment this if you want to use release libs in the debug build.
// Atm this saves you 7 mb of memory
#define USE_RELEASE_LIBS

#define MAX_FFWD_SPEED 5

//extern IDirectSoundRenderer* m_pAudioDecoder;
CApplication::CApplication(void) : m_itemCurrentFile(new CFileItem), m_progressTrackingItem(new CFileItem)
{
  m_iPlaySpeed = 1;
  m_pPlayer = NULL;
  m_bScreenSave = false;
  m_dpms = NULL;
  m_dpmsIsActive = false;
  m_dpmsIsManual = false;
  m_iScreenSaveLock = 0;
  m_bInitializing = true;
  m_eForcedNextPlayer = EPC_NONE;
  m_strPlayListFile = "";
  m_nextPlaylistItem = -1;
  m_bPlaybackStarting = false;

#ifdef HAS_GLX
  XInitThreads();
#endif

  //true while we in IsPaused mode! Workaround for OnPaused, which must be add. after v2.0
  m_bIsPaused = false;

  /* for now always keep this around */
#ifdef HAS_KARAOKE
  m_pKaraokeMgr = new CKaraokeLyricsManager();
#endif
  m_currentStack = new CFileItemList;

#ifdef HAS_SDL
  m_frameCount = 0;
  m_frameMutex = SDL_CreateMutex();
  m_frameCond = SDL_CreateCond();
#endif

  m_bPresentFrame = false;
  m_bPlatformDirectories = true;

  m_bStandalone = false;
  m_bEnableLegacyRes = false;
  m_bSystemScreenSaverEnable = false;
  m_debugLayout = NULL;
}

CApplication::~CApplication(void)
{
  delete m_currentStack;

#ifdef HAS_KARAOKE
  delete m_pKaraokeMgr;
#endif

#ifdef HAS_SDL
  if (m_frameMutex)
    SDL_DestroyMutex(m_frameMutex);

  if (m_frameCond)
    SDL_DestroyCond(m_frameCond);
#endif
  delete m_dpms;
}

bool CApplication::OnEvent(XBMC_Event& newEvent)
{
  switch(newEvent.type)
  {
    case XBMC_QUIT:
      if (!g_application.m_bStop)
        g_application.getApplicationMessenger().Quit();
      break;
//    case XBMC_KEYDOWN:
//    case XBMC_KEYUP:
//      g_Keyboard.HandleEvent(newEvent);
//      g_application.ProcessKeyboard();
//      break;
// New key handling code added in preparation for the major overhaul
// of the keyboard handling
    case XBMC_KEYDOWN:
      g_application.OnKey(g_Keyboard.ProcessKeyDown(newEvent.key.keysym));
      break;
    case XBMC_KEYUP:
      g_Keyboard.ProcessKeyUp();
      break;
    case XBMC_MOUSEBUTTONDOWN:
    case XBMC_MOUSEBUTTONUP:
    case XBMC_MOUSEMOTION:
      g_Mouse.HandleEvent(newEvent);
      g_application.ProcessMouse();
      break;
    case XBMC_VIDEORESIZE:
      if (!g_application.m_bInitializing &&
          !g_advancedSettings.m_fullScreen)
      {
        g_Windowing.SetWindowResolution(newEvent.resize.w, newEvent.resize.h);
        g_graphicsContext.SetVideoResolution(RES_WINDOW, true);
        g_guiSettings.SetInt("window.width", newEvent.resize.w);
        g_guiSettings.SetInt("window.height", newEvent.resize.h);
        g_settings.Save();
      }
      break;
    case XBMC_USEREVENT:
      g_application.getApplicationMessenger().UserEvent(newEvent.user.code);
      break;
    case XBMC_APPCOMMAND:
      {
        // Special media keys are mapped to WM_APPCOMMAND on Windows (and to DBUS events on Linux?)
        // XBMC translates WM_APPCOMMAND to XBMC_APPCOMMAND events.
        g_application.OnAppCommand(CAction(newEvent.appcommand.action));
      }
      break;
  }
  return true;
}

// This function does not return!
void CApplication::FatalErrorHandler(bool WindowSystemInitialized, bool MapDrives, bool InitNetwork)
{
  fprintf(stderr, "Fatal error encountered, aborting\n");
  fprintf(stderr, "Error log at %sxbmc.log\n", g_settings.m_logFolder.c_str());
  abort();
}

extern "C" void __stdcall init_emu_environ();
extern "C" void __stdcall update_emu_environ();

//
// Utility function used to copy files from the application bundle
// over to the user data directory in Application Support/XBMC.
//
static void CopyUserDataIfNeeded(const CStdString &strPath, const CStdString &file)
{
  CStdString destPath = CUtil::AddFileToFolder(strPath, file);
  if (!CFile::Exists(destPath))
  {
    // need to copy it across
    CStdString srcPath = CUtil::AddFileToFolder("special://xbmc/userdata/", file);
    CFile::Cache(srcPath, destPath);
  }
}

void CApplication::Preflight()
{
#ifdef HAS_DBUS
  // call 'dbus_threads_init_default' before any other dbus calls in order to
  // avoid race conditions with other threads using dbus connections
  dbus_threads_init_default();
#endif

  // run any platform preflight scripts.
#ifdef __APPLE__
  CStdString install_path;

  CUtil::GetHomePath(install_path);
  setenv("XBMC_HOME", install_path.c_str(), 0);
  install_path += "/tools/osx/preflight";
  system(install_path.c_str());
#endif
}

bool CApplication::Create()
{
  g_settings.Initialize(); //Initialize default AdvancedSettings

  m_bSystemScreenSaverEnable = g_Windowing.IsSystemScreenSaverEnabled();
  g_Windowing.EnableSystemScreenSaver(false);

#ifdef _LINUX
  tzset();   // Initialize timezone information variables
#endif

  // Grab a handle to our thread to be used later in identifying the render thread.
  m_threadID = CThread::GetCurrentThreadId();

#ifndef _LINUX
  //floating point precision to 24 bits (faster performance)
  _controlfp(_PC_24, _MCW_PC);

  /* install win32 exception translator, win32 exceptions
   * can now be caught using c++ try catch */
  win32_exception::install_handler();
#endif

  // only the InitDirectories* for the current platform should return true
  // putting this before the first log entries saves another ifdef for g_settings.m_logFolder
  bool inited = InitDirectoriesLinux();
  if (!inited)
    inited = InitDirectoriesOSX();
  if (!inited)
    inited = InitDirectoriesWin32();

  // copy required files
  CopyUserDataIfNeeded("special://masterprofile/", "RssFeeds.xml");
  CopyUserDataIfNeeded("special://masterprofile/", "favourites.xml");
  CopyUserDataIfNeeded("special://masterprofile/", "Lircmap.xml");
  CopyUserDataIfNeeded("special://masterprofile/", "LCD.xml");

  if (!CLog::Init(_P(g_settings.m_logFolder).c_str()))
  {
    fprintf(stderr,"Could not init logging classes. Permission errors on ~/.xbmc?\n");
    return false;
  }

  g_settings.LoadProfiles(PROFILES_FILE);

  CLog::Log(LOGNOTICE, "-----------------------------------------------------------------------");
#if defined(__APPLE__)
  CLog::Log(LOGNOTICE, "Starting XBMC, Platform: Mac OS X (%s). Built on %s (SVN:%s)", g_sysinfo.GetUnameVersion().c_str(), __DATE__, SVN_REV);
#elif defined(_LINUX)
  CLog::Log(LOGNOTICE, "Starting XBMC, Platform: Linux (%s, %s). Built on %s (SVN:%s)", g_sysinfo.GetLinuxDistro().c_str(), g_sysinfo.GetUnameVersion().c_str(), __DATE__, SVN_REV);
#elif defined(_WIN32)
  CLog::Log(LOGNOTICE, "Starting XBMC, Platform: %s. Built on %s (SVN:%s, compiler %i)",g_sysinfo.GetKernelVersion().c_str(), __DATE__, SVN_REV, _MSC_VER);
  CLog::Log(LOGNOTICE, g_cpuInfo.getCPUModel().c_str());
  CLog::Log(LOGNOTICE, CWIN32Util::GetResInfoString());
  CLog::Log(LOGNOTICE, "Running with %s rights", (CWIN32Util::IsCurrentUserLocalAdministrator() == TRUE) ? "administrator" : "restricted");
  CLog::Log(LOGNOTICE, "Aero is %s", (g_sysinfo.IsAeroDisabled() == true) ? "disabled" : "enabled");
#endif
  CSpecialProtocol::LogPaths();

  CStdString executable = CUtil::ResolveExecutablePath();
  CLog::Log(LOGNOTICE, "The executable running is: %s", executable.c_str());
  CLog::Log(LOGNOTICE, "Log File is located: %sxbmc.log", g_settings.m_logFolder.c_str());
  CLog::Log(LOGNOTICE, "-----------------------------------------------------------------------");

  CStdString strExecutablePath;
  CUtil::GetHomePath(strExecutablePath);

  // if we are running from DVD our UserData location will be TDATA
  if (CUtil::IsDVD(strExecutablePath))
  {
    // TODO: Should we copy over any UserData folder from the DVD?
    if (!CFile::Exists("special://masterprofile/guisettings.xml")) // first run - cache userdata folder
    {
      CFileItemList items;
      CUtil::GetRecursiveListing("special://xbmc/userdata",items,"");
      for (int i=0;i<items.Size();++i)
          CFile::Cache(items[i]->m_strPath,"special://masterprofile/"+CUtil::GetFileName(items[i]->m_strPath));
    }
    g_settings.m_logFolder = "special://masterprofile/";
  }

#ifdef HAS_XRANDR
  g_xrandr.LoadCustomModeLinesToAllOutputs();
#endif

  // Init our DllLoaders emu env
  init_emu_environ();


#ifdef HAS_SDL
  CLog::Log(LOGNOTICE, "Setup SDL");

  /* Clean up on exit, exit on window close and interrupt */
  atexit(SDL_Quit);

  uint32_t sdlFlags = 0;

#if defined(HAS_SDL_OPENGL) || (HAS_GLES == 2)
  sdlFlags |= SDL_INIT_VIDEO;
#endif

#ifdef HAS_SDL_AUDIO
  sdlFlags |= SDL_INIT_AUDIO;
#endif

#ifdef HAS_SDL_JOYSTICK
  sdlFlags |= SDL_INIT_JOYSTICK;
#endif

  //depending on how it's compiled, SDL periodically calls XResetScreenSaver when it's fullscreen
  //this might bring the monitor out of standby, so we have to disable it explicitly
  //by passing 0 for overwrite to setsenv, the user can still override this by setting the environment variable
#if defined(_LINUX) && !defined(__APPLE__)
  setenv("SDL_VIDEO_ALLOW_SCREENSAVER", "1", 0);
#endif

#endif // HAS_SDL

#ifdef _LINUX
  // for nvidia cards - vsync currently ALWAYS enabled.
  // the reason is that after screen has been setup changing this env var will make no difference.
  setenv("__GL_SYNC_TO_VBLANK", "1", 0);
  setenv("__GL_YIELD", "USLEEP", 0);
#endif

#ifdef HAS_SDL
  if (SDL_Init(sdlFlags) != 0)
  {
    CLog::Log(LOGFATAL, "XBAppEx: Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }
#endif

  // for python scripts that check the OS
#ifdef __APPLE__
  setenv("OS","OS X",true);
#elif defined(_LINUX)
  setenv("OS","Linux",true);
#elif defined(_WIN32)
  SetEnvironmentVariable("OS","win32");
#endif

  // Initialize core peripheral port support. Note: If these parameters
  // are 0 and NULL, respectively, then the default number and types of
  // controllers will be initialized.
  if (!g_Windowing.InitWindowSystem())
  {
    CLog::Log(LOGFATAL, "CApplication::Create: Unable to init windowing system");
    return false;
  }

  g_powerManager.Initialize();

  CLog::Log(LOGNOTICE, "load settings...");

  g_guiSettings.Initialize();  // Initialize default Settings - don't move
  g_powerManager.SetDefaults();
  if (!g_settings.Load())
    FatalErrorHandler(true, true, true);

  CLog::Log(LOGINFO, "creating subdirectories");
  CLog::Log(LOGINFO, "userdata folder: %s", g_settings.GetProfileUserDataFolder().c_str());
  CLog::Log(LOGINFO, "recording folder:%s", g_guiSettings.GetString("audiocds.recordingpath",false).c_str());
  CLog::Log(LOGINFO, "screenshots folder:%s", g_guiSettings.GetString("debug.screenshotpath",false).c_str());
  CDirectory::Create(g_settings.GetUserDataFolder());
  CDirectory::Create(g_settings.GetProfileUserDataFolder());
  g_settings.CreateProfileFolders();

  update_emu_environ();//apply the GUI settings

  // initialize our charset converter
  g_charsetConverter.reset();

  // Load the langinfo to have user charset <-> utf-8 conversion
  CStdString strLanguage = g_guiSettings.GetString("locale.language");
  strLanguage[0] = toupper(strLanguage[0]);

  CStdString strLangInfoPath;
  strLangInfoPath.Format("special://xbmc/language/%s/langinfo.xml", strLanguage.c_str());

  CLog::Log(LOGINFO, "load language info file: %s", strLangInfoPath.c_str());
  g_langInfo.Load(strLangInfoPath);

  CStdString strLanguagePath;
  strLanguagePath.Format("special://xbmc/language/%s/strings.xml", strLanguage.c_str());

  CLog::Log(LOGINFO, "load language file:%s", strLanguagePath.c_str());
  if (!g_localizeStrings.Load(strLanguagePath))
    FatalErrorHandler(false, false, true);

  // start-up Addons Framework
  // currently bails out if either cpluff Dll is unavailable or system dir can not be scanned
  if (!CAddonMgr::Get().Init())
  {
    CLog::Log(LOGFATAL, "CApplication::Create: Unable to start CAddonMgr");
    FatalErrorHandler(true, true, true);
  }

  // Create the Mouse, Keyboard, Remote, and Joystick devices
  // Initialize after loading settings to get joystick deadzone setting
  g_Mouse.Initialize();
  g_Mouse.SetEnabled(g_guiSettings.GetBool("input.enablemouse"));

  g_Keyboard.Initialize();
#if defined(HAS_LIRC) || defined(HAS_IRSERVERSUITE)
  g_RemoteControl.Initialize();
#endif
#ifdef HAS_SDL_JOYSTICK
  g_Joystick.Initialize();
#endif

#ifdef __APPLE__
  // Configure and possible manually start the helper.
  XBMCHelper::GetInstance().Configure();
#endif

  // update the window resolution
  g_Windowing.SetWindowResolution(g_guiSettings.GetInt("window.width"), g_guiSettings.GetInt("window.height"));

  if (g_advancedSettings.m_startFullScreen && g_guiSettings.m_LookAndFeelResolution == RES_WINDOW)
    g_guiSettings.m_LookAndFeelResolution = RES_DESKTOP;

  if (!g_graphicsContext.IsValidResolution(g_guiSettings.m_LookAndFeelResolution))
  {
    // Oh uh - doesn't look good for starting in their wanted screenmode
    CLog::Log(LOGERROR, "The screen resolution requested is not valid, resetting to a valid mode");
    g_guiSettings.m_LookAndFeelResolution = RES_DESKTOP;
  }

#ifdef __APPLE__
  // force initial window creation to be windowed, if fullscreen, it will switch to it below
  // fixes the white screen of death if starting fullscreen and switching to windowed.
  bool bFullScreen = false;
  if (!g_Windowing.CreateNewWindow("XBMC", bFullScreen, g_settings.m_ResInfo[RES_WINDOW], OnEvent))
  {
    CLog::Log(LOGFATAL, "CApplication::Create: Unable to create window");
    return false;
  }
#else
  bool bFullScreen = g_guiSettings.m_LookAndFeelResolution != RES_WINDOW;
  if (!g_Windowing.CreateNewWindow("XBMC", bFullScreen, g_settings.m_ResInfo[g_guiSettings.m_LookAndFeelResolution], OnEvent))
  {
    CLog::Log(LOGFATAL, "CApplication::Create: Unable to create window");
    return false;
  }
#endif

  if (!g_Windowing.InitRenderSystem())
  {
    CLog::Log(LOGFATAL, "CApplication::Create: Unable to init rendering system");
    return false;
  }

  // set GUI res and force the clear of the screen
  g_graphicsContext.SetVideoResolution(g_guiSettings.m_LookAndFeelResolution);

  CStdString strUserSplash = "special://home/media/Splash.png";
  if (CFile::Exists(strUserSplash))
  {
    CLog::Log(LOGINFO, "load user splash image: %s", CSpecialProtocol::TranslatePath(strUserSplash).c_str());
    m_splash = new CSplash(strUserSplash);
  }
  else
  {
    CLog::Log(LOGINFO, "load default splash image: %s", CSpecialProtocol::TranslatePath("special://xbmc/media/Splash.png").c_str());
    m_splash = new CSplash("special://xbmc/media/Splash.png");
  }
  m_splash->Show();

  CLog::Log(LOGINFO, "load keymapping");
  if (!CButtonTranslator::GetInstance().Load())
    FatalErrorHandler(false, false, true);

  int iResolution = g_graphicsContext.GetVideoResolution();
  CLog::Log(LOGINFO, "GUI format %ix%i %s",
            g_settings.m_ResInfo[iResolution].iWidth,
            g_settings.m_ResInfo[iResolution].iHeight,
            g_settings.m_ResInfo[iResolution].strMode.c_str());
  g_windowManager.Initialize();

  CUtil::InitRandomSeed();

  g_mediaManager.Initialize();

  return Initialize();
}

bool CApplication::InitDirectoriesLinux()
{
/*
   The following is the directory mapping for Platform Specific Mode:

   special://xbmc/          => [read-only] system directory (/usr/share/xbmc)
   special://home/          => [read-write] user's directory that will override special://xbmc/ system-wide
                               installations like skins, screensavers, etc.
                               ($HOME/.xbmc)
                               NOTE: XBMC will look in both special://xbmc/addons and special://home/addons for addons.
   special://masterprofile/ => [read-write] userdata of master profile. It will by default be
                               mapped to special://home/userdata ($HOME/.xbmc/userdata)
   special://profile/       => [read-write] current profile's userdata directory.
                               Generally special://masterprofile for the master profile or
                               special://masterprofile/profiles/<profile_name> for other profiles.

   NOTE: All these root directories are lowercase. Some of the sub-directories
         might be mixed case.
*/

#if defined(_LINUX) && !defined(__APPLE__)
  CStdString userName;
  if (getenv("USER"))
    userName = getenv("USER");
  else
    userName = "root";

  CStdString userHome;
  if (getenv("HOME"))
    userHome = getenv("HOME");
  else
    userHome = "/root";

  CStdString xbmcBinPath, xbmcPath;
  CUtil::GetHomePath(xbmcBinPath, "XBMC_BIN_HOME");
  xbmcPath = getenv("XBMC_HOME");

  if (xbmcPath.IsEmpty())
  {
    xbmcPath = INSTALL_PATH;
    /* Check if xbmc binaries and arch independent data files are being kept in
     * separate locations. */
    if (!CFile::Exists(CUtil::AddFileToFolder(xbmcPath, "language")))
    {
      /* Attempt to locate arch independent data files. */
      CUtil::GetHomePath(xbmcPath);
      if (!CFile::Exists(CUtil::AddFileToFolder(xbmcPath, "language")))
      {
        fprintf(stderr, "Unable to find path to XBMC data files!\n");
        exit(1);
      }
    }
  }

  /* Set some environment variables */
  setenv("XBMC_BIN_HOME", xbmcBinPath.c_str(), 0);
  setenv("XBMC_HOME", xbmcPath.c_str(), 0);

  if (m_bPlatformDirectories)
  {
    // map our special drives
    CSpecialProtocol::SetXBMCBinPath(xbmcBinPath);
    CSpecialProtocol::SetXBMCPath(xbmcPath);
    CSpecialProtocol::SetHomePath(userHome + "/.xbmc");
    CSpecialProtocol::SetMasterProfilePath(userHome + "/.xbmc/userdata");

    CStdString strTempPath = CUtil::AddFileToFolder(userHome, ".xbmc/temp");
    CSpecialProtocol::SetTempPath(strTempPath);

    CUtil::AddSlashAtEnd(strTempPath);
    g_settings.m_logFolder = strTempPath;

    CreateUserDirs();

  }
  else
  {
    CUtil::AddSlashAtEnd(xbmcPath);
    g_settings.m_logFolder = xbmcPath;

    CSpecialProtocol::SetXBMCBinPath(xbmcBinPath);
    CSpecialProtocol::SetXBMCPath(xbmcPath);
    CSpecialProtocol::SetHomePath(CUtil::AddFileToFolder(xbmcPath, "portable_data"));
    CSpecialProtocol::SetMasterProfilePath(CUtil::AddFileToFolder(xbmcPath, "portable_data/userdata"));

    CStdString strTempPath = CUtil::AddFileToFolder(xbmcPath, "portable_data/temp");
    CSpecialProtocol::SetTempPath(strTempPath);
    CreateUserDirs();

    CUtil::AddSlashAtEnd(strTempPath);
    g_settings.m_logFolder = strTempPath;
  }

  return true;
#else
  return false;
#endif
}

bool CApplication::InitDirectoriesOSX()
{
#ifdef __APPLE__
  CStdString userName;
  if (getenv("USER"))
    userName = getenv("USER");
  else
    userName = "root";

  CStdString userHome;
  if (getenv("HOME"))
    userHome = getenv("HOME");
  else
    userHome = "/root";

  CStdString xbmcPath;
  CUtil::GetHomePath(xbmcPath);
  setenv("XBMC_HOME", xbmcPath.c_str(), 0);

  // OSX always runs with m_bPlatformDirectories == true
  if (m_bPlatformDirectories)
  {
    // map our special drives
    CSpecialProtocol::SetXBMCBinPath(xbmcPath);
    CSpecialProtocol::SetXBMCPath(xbmcPath);
    CSpecialProtocol::SetHomePath(userHome + "/Library/Application Support/XBMC");
    CSpecialProtocol::SetMasterProfilePath(userHome + "/Library/Application Support/XBMC/userdata");

#ifdef __APPLE__
    CStdString strTempPath = CUtil::AddFileToFolder(userHome, ".xbmc/");
    CDirectory::Create(strTempPath);
#endif

    strTempPath = CUtil::AddFileToFolder(userHome, ".xbmc/temp");
    CSpecialProtocol::SetTempPath(strTempPath);

#ifdef __APPLE__
    strTempPath = userHome + "/Library/Logs";
#endif
    CUtil::AddSlashAtEnd(strTempPath);
    g_settings.m_logFolder = strTempPath;

    CreateUserDirs();
  }
  else
  {
    CUtil::AddSlashAtEnd(xbmcPath);
    g_settings.m_logFolder = xbmcPath;

    CSpecialProtocol::SetXBMCBinPath(xbmcPath);
    CSpecialProtocol::SetXBMCPath(xbmcPath);
    CSpecialProtocol::SetHomePath(CUtil::AddFileToFolder(xbmcPath, "portable_data"));
    CSpecialProtocol::SetMasterProfilePath(CUtil::AddFileToFolder(xbmcPath, "portable_data/userdata"));

    CStdString strTempPath = CUtil::AddFileToFolder(xbmcPath, "portable_data/temp");
    CSpecialProtocol::SetTempPath(strTempPath);

    CUtil::AddSlashAtEnd(strTempPath);
    g_settings.m_logFolder = strTempPath;
  }

  return true;
#else
  return false;
#endif
}

bool CApplication::InitDirectoriesWin32()
{
#ifdef _WIN32
  CStdString xbmcPath;

  CUtil::GetHomePath(xbmcPath);
  SetEnvironmentVariable("XBMC_HOME", xbmcPath.c_str());
  CSpecialProtocol::SetXBMCBinPath(xbmcPath);
  CSpecialProtocol::SetXBMCPath(xbmcPath);

  if (m_bPlatformDirectories)
  {

    CStdString strWin32UserFolder = CWIN32Util::GetProfilePath();

    // create user/app data/XBMC
    CStdString homePath = CUtil::AddFileToFolder(strWin32UserFolder, "XBMC");

    // move log to platform dirs
    g_settings.m_logFolder = homePath;
    CUtil::AddSlashAtEnd(g_settings.m_logFolder);

    // map our special drives
    CSpecialProtocol::SetXBMCBinPath(xbmcPath);
    CSpecialProtocol::SetXBMCPath(xbmcPath);
    CSpecialProtocol::SetHomePath(homePath);
    CSpecialProtocol::SetMasterProfilePath(CUtil::AddFileToFolder(homePath, "userdata"));
    SetEnvironmentVariable("XBMC_PROFILE_USERDATA",_P("special://masterprofile").c_str());

    CSpecialProtocol::SetTempPath(CUtil::AddFileToFolder(homePath,"cache"));

    CreateUserDirs();

  }
  else
  {
    CUtil::AddSlashAtEnd(xbmcPath);
    g_settings.m_logFolder = xbmcPath;

    CSpecialProtocol::SetHomePath(CUtil::AddFileToFolder(xbmcPath, "portable_data"));
    CSpecialProtocol::SetMasterProfilePath(CUtil::AddFileToFolder(xbmcPath, "portable_data/userdata"));

    CStdString strTempPath = CUtil::AddFileToFolder(xbmcPath, "portable_data/temp");
    CSpecialProtocol::SetTempPath(strTempPath);

    CreateUserDirs();

    SetEnvironmentVariable("XBMC_PROFILE_USERDATA",_P("special://masterprofile/").c_str());
  }

  // Expand the DLL search path with our directories
  CWIN32Util::ExtendDllPath();

  // check for a DVD drive
  VECSOURCES vShare;
  CWIN32Util::GetDrivesByType(vShare, DVD_DRIVES);
  if(!vShare.empty())
    g_mediaManager.SetHasOpticalDrive(true);

  // Can be removed once the StorageHandler supports optical media
  VECSOURCES::const_iterator it;
  for(it=vShare.begin();it!=vShare.end();++it)
    if(g_mediaManager.GetDriveStatus(it->strPath) == DRIVE_CLOSED_MEDIA_PRESENT)
      g_application.getApplicationMessenger().OpticalMount(it->strPath);
  // remove end

  return true;
#else
  return false;
#endif
}

void CApplication::CreateUserDirs()
{
  CDirectory::Create("special://home/");
  CDirectory::Create("special://home/addons");
  CDirectory::Create("special://home/addons/packages");
  CDirectory::Create("special://home/media");
  CDirectory::Create("special://home/sounds");
  CDirectory::Create("special://home/system");
  CDirectory::Create("special://masterprofile/");
  CDirectory::Create("special://temp/");
  CDirectory::Create("special://temp/temp"); // temp directory for python and dllGetTempPathA
}

bool CApplication::Initialize()
{
#ifdef HAS_DVD_DRIVE
  // turn off cdio logging
  cdio_loglevel_default = CDIO_LOG_ERROR;
#endif

#ifdef _LINUX // TODO: Win32 has no special://home/ mapping by default, so we
              //       must create these here. Ideally this should be using special://home/ and
              //       be platform agnostic (i.e. unify the InitDirectories*() functions)
  if (!m_bPlatformDirectories)
#endif
  {
    CDirectory::Create("special://xbmc/language");
    CDirectory::Create("special://xbmc/addons");
    CDirectory::Create("special://xbmc/sounds");
  }

  StartServices();

  // Init DPMS, before creating the corresponding setting control.
  m_dpms = new DPMSSupport();
  g_guiSettings.GetSetting("powermanagement.displaysoff")->SetVisible(m_dpms->IsSupported());

  g_windowManager.Add(new CGUIWindowHome);                     // window id = 0
  g_windowManager.Add(new CGUIWindowPrograms);                 // window id = 1
  g_windowManager.Add(new CGUIWindowPictures);                 // window id = 2
  g_windowManager.Add(new CGUIWindowFileManager);      // window id = 3
  g_windowManager.Add(new CGUIWindowVideoFiles);          // window id = 6
  g_windowManager.Add(new CGUIWindowSettings);                 // window id = 4
  g_windowManager.Add(new CGUIWindowSystemInfo);               // window id = 7
#ifdef HAS_GL
  g_windowManager.Add(new CGUIWindowTestPatternGL);      // window id = 8
#endif
#ifdef HAS_DX
  g_windowManager.Add(new CGUIWindowTestPatternDX);      // window id = 8
#endif
  g_windowManager.Add(new CGUIDialogTeletext);               // window id =
  g_windowManager.Add(new CGUIWindowSettingsScreenCalibration); // window id = 11
  g_windowManager.Add(new CGUIWindowSettingsCategory);         // window id = 12 slideshow:window id 2007
  g_windowManager.Add(new CGUIWindowVideoNav);                 // window id = 36
  g_windowManager.Add(new CGUIWindowVideoPlaylist);            // window id = 28
  g_windowManager.Add(new CGUIWindowLoginScreen);            // window id = 29
  g_windowManager.Add(new CGUIWindowSettingsProfile);          // window id = 34
  g_windowManager.Add(new CGUIWindowAddonBrowser);          // window id = 40
  g_windowManager.Add(new CGUIDialogYesNo);              // window id = 100
  g_windowManager.Add(new CGUIDialogProgress);           // window id = 101
  g_windowManager.Add(new CGUIDialogKeyboard);           // window id = 103
  g_windowManager.Add(&m_guiDialogVolumeBar);          // window id = 104
  g_windowManager.Add(&m_guiDialogSeekBar);            // window id = 115
  g_windowManager.Add(new CGUIDialogSubMenu);            // window id = 105
  g_windowManager.Add(new CGUIDialogContextMenu);        // window id = 106
  g_windowManager.Add(&m_guiDialogKaiToast);           // window id = 107
  g_windowManager.Add(new CGUIDialogNumeric);            // window id = 109
  g_windowManager.Add(new CGUIDialogGamepad);            // window id = 110
  g_windowManager.Add(new CGUIDialogButtonMenu);         // window id = 111
  g_windowManager.Add(new CGUIDialogMusicScan);          // window id = 112
  g_windowManager.Add(new CGUIDialogPlayerControls);     // window id = 113
#ifdef HAS_KARAOKE
  g_windowManager.Add(new CGUIDialogKaraokeSongSelectorSmall); // window id 143
  g_windowManager.Add(new CGUIDialogKaraokeSongSelectorLarge); // window id 144
#endif
  g_windowManager.Add(new CGUIDialogSlider);             // window id = 145
  g_windowManager.Add(new CGUIDialogMusicOSD);           // window id = 120
  g_windowManager.Add(new CGUIDialogVisualisationPresetList);   // window id = 122
  g_windowManager.Add(new CGUIDialogVideoSettings);             // window id = 123
  g_windowManager.Add(new CGUIDialogAudioSubtitleSettings);     // window id = 124
  g_windowManager.Add(new CGUIDialogVideoBookmarks);      // window id = 125
  // Don't add the filebrowser dialog - it's created and added when it's needed
  g_windowManager.Add(new CGUIDialogNetworkSetup);  // window id = 128
  g_windowManager.Add(new CGUIDialogMediaSource);   // window id = 129
  g_windowManager.Add(new CGUIDialogProfileSettings); // window id = 130
  g_windowManager.Add(new CGUIDialogVideoScan);      // window id = 133
  g_windowManager.Add(new CGUIDialogFavourites);     // window id = 134
  g_windowManager.Add(new CGUIDialogSongInfo);       // window id = 135
  g_windowManager.Add(new CGUIDialogSmartPlaylistEditor);       // window id = 136
  g_windowManager.Add(new CGUIDialogSmartPlaylistRule);       // window id = 137
  g_windowManager.Add(new CGUIDialogBusy);      // window id = 138
  g_windowManager.Add(new CGUIDialogPictureInfo);      // window id = 139
  g_windowManager.Add(new CGUIDialogAddonInfo);
  g_windowManager.Add(new CGUIDialogAddonSettings);      // window id = 140
#ifdef HAS_LINUX_NETWORK
  g_windowManager.Add(new CGUIDialogAccessPoints);      // window id = 141
#endif

  g_windowManager.Add(new CGUIDialogLockSettings); // window id = 131

  g_windowManager.Add(new CGUIDialogContentSettings);        // window id = 132

  g_windowManager.Add(new CGUIWindowMusicPlayList);          // window id = 500
  g_windowManager.Add(new CGUIWindowMusicSongs);             // window id = 501
  g_windowManager.Add(new CGUIWindowMusicNav);               // window id = 502
  g_windowManager.Add(new CGUIWindowMusicPlaylistEditor);    // window id = 503

  g_windowManager.Add(new CGUIDialogSelect);             // window id = 2000
  g_windowManager.Add(new CGUIWindowMusicInfo);                // window id = 2001
  g_windowManager.Add(new CGUIDialogOK);                 // window id = 2002
  g_windowManager.Add(new CGUIWindowVideoInfo);                // window id = 2003
  g_windowManager.Add(new CGUIDialogTextViewer);
  g_windowManager.Add(new CGUIWindowFullScreen);         // window id = 2005
  g_windowManager.Add(new CGUIWindowVisualisation);      // window id = 2006
  g_windowManager.Add(new CGUIWindowSlideShow);          // window id = 2007
  g_windowManager.Add(new CGUIDialogFileStacking);       // window id = 2008
#ifdef HAS_KARAOKE
  g_windowManager.Add(new CGUIWindowKaraokeLyrics);      // window id = 2009
#endif

  g_windowManager.Add(new CGUIWindowOSD);                // window id = 2901
  g_windowManager.Add(new CGUIWindowMusicOverlay);       // window id = 2903
  g_windowManager.Add(new CGUIWindowVideoOverlay);       // window id = 2904
  g_windowManager.Add(new CGUIWindowScreensaver);        // window id = 2900 Screensaver
  g_windowManager.Add(new CGUIWindowWeather);            // window id = 2600 WEATHER
  g_windowManager.Add(new CGUIWindowStartup);            // startup window (id 2999)

  /* window id's 3000 - 3100 are reserved for python */

  // Make sure we have at least the default skin
  if (!LoadSkin(g_guiSettings.GetString("lookandfeel.skin")) && !LoadSkin(DEFAULT_SKIN))
  {
      CLog::Log(LOGERROR, "Default skin '%s' not found! Terminating..", DEFAULT_SKIN);
      FatalErrorHandler(true, true, true);
  }

  SAFE_DELETE(m_splash);

  if (g_guiSettings.GetBool("masterlock.startuplock") &&
      g_settings.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE &&
     !g_settings.GetMasterProfile().getLockCode().IsEmpty())
  {
     g_passwordManager.CheckStartUpLock();
  }

  // check if we should use the login screen
  if (g_settings.UsingLoginScreen())
    g_windowManager.ActivateWindow(WINDOW_LOGIN_SCREEN);
  else
    g_windowManager.ActivateWindow(g_SkinInfo->GetFirstWindow());

  g_sysinfo.Refresh();

  CLog::Log(LOGINFO, "removing tempfiles");
  CUtil::RemoveTempFiles();

  //  Show mute symbol
  if (g_settings.m_nVolumeLevel == VOLUME_MINIMUM)
    Mute();

  // if the user shutoff the xbox during music scan
  // restore the settings
  if (g_settings.m_bMyMusicIsScanning)
  {
    CLog::Log(LOGWARNING,"System rebooted during music scan! ... restoring UseTags and FindRemoteThumbs");
    RestoreMusicScanSettings();
  }

  if (!g_settings.UsingLoginScreen())
  {
    UpdateLibraries();
#ifdef HAS_PYTHON
  g_pythonParser.m_bLogin = true;
#endif
  }

  m_slowTimer.StartZero();

#ifdef __APPLE__
  XBMCHelper::GetInstance().CaptureAllInput();
#endif
#if defined(HAVE_LIBCRYSTALHD)
  CCrystalHD::GetInstance();
#endif

  CAddonMgr::Get().StartServices();

  CLog::Log(LOGNOTICE, "initialize done");

  m_bInitializing = false;

  // reset our screensaver (starts timers etc.)
  ResetScreenSaver();
  return true;
}

void CApplication::StartWebServer()
{
#ifdef HAS_WEB_SERVER
  if (g_guiSettings.GetBool("services.webserver") && m_network.IsAvailable())
  {
    int webPort = atoi(g_guiSettings.GetString("services.webserverport"));
    CLog::Log(LOGNOTICE, "Webserver: Starting...");
#ifdef _LINUX
    if (webPort < 1024 && geteuid() != 0)
    {
        CLog::Log(LOGERROR, "Cannot start Web Server as port is smaller than 1024 and user is not root");
        return;
    }
#endif

    if (m_WebServer.Start(webPort, g_guiSettings.GetString("services.webserverusername"), g_guiSettings.GetString("services.webserverpassword")))
    {
      // publish web frontend and API services
#ifdef HAS_WEB_INTERFACE
      CZeroconf::GetInstance()->PublishService("servers.webserver", "_http._tcp", "XBMC Web Server", webPort);
#endif
#ifdef HAS_HTTPAPI
      CZeroconf::GetInstance()->PublishService("servers.webapi", "_xbmc-web._tcp", "XBMC HTTP API", webPort);
#endif
#ifdef HAS_JSONRPC
      CZeroconf::GetInstance()->PublishService("servers.webjsonrpc", "_xbmc-jsonrpc._tcp", "XBMC JSONRPC", webPort);
#endif
    }
#ifdef HAS_HTTPAPI
    if (g_settings.m_HttpApiBroadcastLevel >= 1)
      getApplicationMessenger().HttpApi("broadcastlevel; StartUp;1");
#endif
  }
#endif
}

void CApplication::StopWebServer()
{
#ifdef HAS_WEB_SERVER
  if (m_WebServer.IsStarted())
  {
    CLog::Log(LOGNOTICE, "Webserver: Stopping...");
    m_WebServer.Stop();
    if(! m_WebServer.IsStarted() )
    {
      CLog::Log(LOGNOTICE, "Webserver: Stopped...");
      CZeroconf::GetInstance()->RemoveService("services.webserver");
      CZeroconf::GetInstance()->RemoveService("servers.webjsonrpc");
      CZeroconf::GetInstance()->RemoveService("services.webapi");
    } else
      CLog::Log(LOGWARNING, "Webserver: Failed to stop.");
  }
#endif
}

void CApplication::StartJSONRPCServer()
{
#ifdef HAS_JSONRPC
  if (g_guiSettings.GetBool("services.esenabled"))
  {
    if (CTCPServer::StartServer(9090, g_guiSettings.GetBool("services.esallinterfaces")))
      CZeroconf::GetInstance()->PublishService("servers.jsonrpc", "_xbmc-jsonrpc._tcp", "XBMC JSONRPC", 9090);
  }
#endif
}

void CApplication::StopJSONRPCServer(bool bWait)
{
#ifdef HAS_JSONRPC
  CTCPServer::StopServer(bWait);
  CZeroconf::GetInstance()->RemoveService("servers.jsonrpc");
#endif
}

void CApplication::StartUPnP()
{
#ifdef HAS_UPNP
  StartUPnPServer();
  StartUPnPRenderer();
#endif
}

void CApplication::StopUPnP(bool bWait)
{
#ifdef HAS_UPNP
  if (CUPnP::IsInstantiated())
  {
    CLog::Log(LOGNOTICE, "stopping upnp");
    CUPnP::ReleaseInstance(bWait);
  }
#endif
}

void CApplication::StartEventServer()
{
#ifdef HAS_EVENT_SERVER
  CEventServer* server = CEventServer::GetInstance();
  if (!server)
  {
    CLog::Log(LOGERROR, "ES: Out of memory");
    return;
  }
  if (g_guiSettings.GetBool("services.esenabled"))
  {
    CLog::Log(LOGNOTICE, "ES: Starting event server");
    server->StartServer();
  }
#endif
}

bool CApplication::StopEventServer(bool bWait, bool promptuser)
{
#ifdef HAS_EVENT_SERVER
  CEventServer* server = CEventServer::GetInstance();
  if (!server)
  {
    CLog::Log(LOGERROR, "ES: Out of memory");
    return false;
  }
  if (promptuser)
  {
    if (server->GetNumberOfClients() > 0)
    {
      bool cancelled = false;
      if (!CGUIDialogYesNo::ShowAndGetInput(13140, 13141, 13142, 20022,
                                            -1, -1, cancelled, 10000)
          || cancelled)
      {
        CLog::Log(LOGNOTICE, "ES: Not stopping event server");
        return false;
      }
    }
    CLog::Log(LOGNOTICE, "ES: Stopping event server with confirmation");

    CEventServer::GetInstance()->StopServer(true);
  }
  else
  {
    if (!bWait)
      CLog::Log(LOGNOTICE, "ES: Stopping event server");

    CEventServer::GetInstance()->StopServer(bWait);
  }

  return true;
#endif
}

void CApplication::RefreshEventServer()
{
#ifdef HAS_EVENT_SERVER
  if (g_guiSettings.GetBool("services.esenabled"))
  {
    CEventServer::GetInstance()->RefreshSettings();
  }
#endif
}

void CApplication::StartDbusServer()
{
#ifdef HAS_DBUS_SERVER
  CDbusServer* serverDbus = CDbusServer::GetInstance();
  if (!serverDbus)
  {
    CLog::Log(LOGERROR, "DS: Out of memory");
    return;
  }
  CLog::Log(LOGNOTICE, "DS: Starting dbus server");
  serverDbus->StartServer( this );
#endif
}

bool CApplication::StopDbusServer(bool bWait)
{
#ifdef HAS_DBUS_SERVER
  CDbusServer* serverDbus = CDbusServer::GetInstance();
  if (!serverDbus)
  {
    CLog::Log(LOGERROR, "DS: Out of memory");
    return false;
  }
  CDbusServer::GetInstance()->StopServer(bWait);
#endif
  return true;
}

void CApplication::StartUPnPRenderer()
{
#ifdef HAS_UPNP
  if (g_guiSettings.GetBool("services.upnprenderer"))
  {
    CLog::Log(LOGNOTICE, "starting upnp renderer");
    CUPnP::GetInstance()->StartRenderer();
  }
#endif
}

void CApplication::StopUPnPRenderer()
{
#ifdef HAS_UPNP
  if (CUPnP::IsInstantiated())
  {
    CLog::Log(LOGNOTICE, "stopping upnp renderer");
    CUPnP::GetInstance()->StopRenderer();
  }
#endif
}

void CApplication::StartUPnPServer()
{
#ifdef HAS_UPNP
  if (g_guiSettings.GetBool("services.upnpserver"))
  {
    CLog::Log(LOGNOTICE, "starting upnp server");
    CUPnP::GetInstance()->StartServer();
  }
#endif
}

void CApplication::StopUPnPServer()
{
#ifdef HAS_UPNP
  if (CUPnP::IsInstantiated())
  {
    CLog::Log(LOGNOTICE, "stopping upnp server");
    CUPnP::GetInstance()->StopServer();
  }
#endif
}

void CApplication::StartZeroconf()
{
#ifdef HAS_ZEROCONF
  //entry in guisetting only present if HAS_ZEROCONF is set
  if(g_guiSettings.GetBool("services.zeroconf"))
  {
    CLog::Log(LOGNOTICE, "starting zeroconf publishing");
    CZeroconf::GetInstance()->Start();
  }
#endif
}

void CApplication::StopZeroconf()
{
#ifdef HAS_ZEROCONF
  if(CZeroconf::IsInstantiated())
  {
    CLog::Log(LOGNOTICE, "stopping zeroconf publishing");
    CZeroconf::GetInstance()->Stop();
  }
#endif
}

void CApplication::DimLCDOnPlayback(bool dim)
{
#ifdef HAS_LCD
  if (g_lcd)
  {
    if (dim)
      g_lcd->DisableOnPlayback(IsPlayingVideo(), IsPlayingAudio());
    else
      g_lcd->SetBackLight(1);
  }
#endif
}

void CApplication::StartServices()
{
#if !defined(_WIN32) && defined(HAS_DVD_DRIVE)
  // Start Thread for DVD Mediatype detection
  CLog::Log(LOGNOTICE, "start dvd mediatype detection");
  m_DetectDVDType.Create(false, THREAD_MINSTACKSIZE);
#endif

  CLog::Log(LOGNOTICE, "initializing playlistplayer");
  g_playlistPlayer.SetRepeat(PLAYLIST_MUSIC, g_settings.m_bMyMusicPlaylistRepeat ? PLAYLIST::REPEAT_ALL : PLAYLIST::REPEAT_NONE);
  g_playlistPlayer.SetShuffle(PLAYLIST_MUSIC, g_settings.m_bMyMusicPlaylistShuffle);
  g_playlistPlayer.SetRepeat(PLAYLIST_VIDEO, g_settings.m_bMyVideoPlaylistRepeat ? PLAYLIST::REPEAT_ALL : PLAYLIST::REPEAT_NONE);
  g_playlistPlayer.SetShuffle(PLAYLIST_VIDEO, g_settings.m_bMyVideoPlaylistShuffle);
  CLog::Log(LOGNOTICE, "DONE initializing playlistplayer");

#ifdef HAS_LCD
  CLCDFactory factory;
  g_lcd = factory.Create();
  if (g_lcd)
  {
    g_lcd->Initialize();
  }
#endif
}

void CApplication::StopServices()
{
  m_network.NetworkMessage(CNetwork::SERVICES_DOWN, 0);

#if !defined(_WIN32) && defined(HAS_DVD_DRIVE)
  CLog::Log(LOGNOTICE, "stop dvd detect media");
  m_DetectDVDType.StopThread();
#endif
}

void CApplication::ReloadSkin()
{
  CGUIMessage msg(GUI_MSG_LOAD_SKIN, -1, g_windowManager.GetActiveWindow());
  g_windowManager.SendMessage(msg);
  // Reload the skin, restoring the previously focused control.  We need this as
  // the window unload will reset all control states.
  CGUIWindow* pWindow = g_windowManager.GetWindow(g_windowManager.GetActiveWindow());
  int iCtrlID = pWindow->GetFocusedControlID();
  g_application.LoadSkin(g_guiSettings.GetString("lookandfeel.skin"));
  pWindow = g_windowManager.GetWindow(g_windowManager.GetActiveWindow());
  if (pWindow && pWindow->HasSaveLastControl())
  {
    CGUIMessage msg3(GUI_MSG_SETFOCUS, g_windowManager.GetActiveWindow(), iCtrlID, 0);
    pWindow->OnMessage(msg3);
  }
}

bool CApplication::LoadSkin(const CStdString& skinID)
{
  AddonPtr addon;
  if (CAddonMgr::Get().GetAddon(skinID, addon, ADDON_SKIN))
  {
    LoadSkin(boost::dynamic_pointer_cast<ADDON::CSkinInfo>(addon));
    return true;
  }
  return false;
}

void CApplication::LoadSkin(const SkinPtr& skin)
{
  if (!skin)
  {
    CLog::Log(LOGERROR, "failed to load requested skin, fallback to \"%s\" skin", DEFAULT_SKIN);
    g_guiSettings.SetString("lookandfeel.skin", DEFAULT_SKIN);
    LoadSkin(DEFAULT_SKIN);
    return ;
  }

  bool bPreviousPlayingState=false;
  bool bPreviousRenderingState=false;
  if (g_application.m_pPlayer && g_application.IsPlayingVideo())
  {
    bPreviousPlayingState = !g_application.m_pPlayer->IsPaused();
    if (bPreviousPlayingState)
      g_application.m_pPlayer->Pause();
#ifdef HAS_VIDEO_PLAYBACK
    if (!g_renderManager.Paused())
    {
      if (g_windowManager.GetActiveWindow() == WINDOW_FULLSCREEN_VIDEO)
     {
        g_windowManager.ActivateWindow(WINDOW_HOME);
        bPreviousRenderingState = true;
      }
    }
#endif
  }
  // close the music and video overlays (they're re-opened automatically later)
  CSingleLock lock(g_graphicsContext);

  // save the current window details
  int currentWindow = g_windowManager.GetActiveWindow();
  vector<int> currentModelessWindows;
  g_windowManager.GetActiveModelessWindows(currentModelessWindows);

  CLog::Log(LOGINFO, "  delete old skin...");
  UnloadSkin();

  CLog::Log(LOGINFO, "  load skin from:%s", skin->Path().c_str());
  g_SkinInfo = skin;
  g_SkinInfo->Start();

  CLog::Log(LOGINFO, "  load fonts for skin...");
  g_graphicsContext.SetMediaDir(skin->Path());
  g_directoryCache.ClearSubPaths(skin->Path());
  if (g_langInfo.ForceUnicodeFont() && !g_fontManager.IsFontSetUnicode(g_guiSettings.GetString("lookandfeel.font")))
  {
    CLog::Log(LOGINFO, "    language needs a ttf font, loading first ttf font available");
    CStdString strFontSet;
    if (g_fontManager.GetFirstFontSetUnicode(strFontSet))
    {
      CLog::Log(LOGINFO, "    new font is '%s'", strFontSet.c_str());
      g_guiSettings.SetString("lookandfeel.font", strFontSet);
      g_settings.Save();
    }
    else
      CLog::Log(LOGERROR, "    no ttf font found, but needed for the language %s.", g_guiSettings.GetString("locale.language").c_str());
  }
  g_colorManager.Load(g_guiSettings.GetString("lookandfeel.skincolors"));

  g_fontManager.LoadFonts(g_guiSettings.GetString("lookandfeel.font"));

  // load in the skin strings
  CStdString langPath, skinEnglishPath;
  CUtil::AddFileToFolder(skin->Path(), "language", langPath);
  CUtil::AddFileToFolder(langPath, g_guiSettings.GetString("locale.language"), langPath);
  CUtil::AddFileToFolder(langPath, "strings.xml", langPath);

  CUtil::AddFileToFolder(skin->Path(), "language", skinEnglishPath);
  CUtil::AddFileToFolder(skinEnglishPath, "English", skinEnglishPath);
  CUtil::AddFileToFolder(skinEnglishPath, "strings.xml", skinEnglishPath);

  g_localizeStrings.LoadSkinStrings(langPath, skinEnglishPath);

  int64_t start;
  start = CurrentHostCounter();

  CLog::Log(LOGINFO, "  load new skin...");
  CGUIWindowHome *pHome = (CGUIWindowHome *)g_windowManager.GetWindow(WINDOW_HOME);
  if (!pHome || !pHome->Load("Home.xml"))
  {
    // failed to load home.xml
    // fallback to default skin
    if ( strcmpi(skin->ID().c_str(), DEFAULT_SKIN) != 0)
    {
      CLog::Log(LOGERROR, "failed to load home.xml for skin:%s, fallback to \"%s\" skin", skin->ID().c_str(), DEFAULT_SKIN);
      g_guiSettings.SetString("lookandfeel.skin", DEFAULT_SKIN);
      LoadSkin(DEFAULT_SKIN);
      return ;
    }
  }

  // Load the user windows
  LoadUserWindows();

  int64_t end, freq;
  end = CurrentHostCounter();
  freq = CurrentHostFrequency();
  CLog::Log(LOGDEBUG,"Load Skin XML: %.2fms", 1000.f * (end - start) / freq);

  CLog::Log(LOGINFO, "  initialize new skin...");
  m_guiPointer.AllocResources(true);
  m_guiDialogVolumeBar.AllocResources(true);
  m_guiDialogSeekBar.AllocResources(true);
  m_guiDialogKaiToast.AllocResources(true);
  m_guiDialogMuteBug.AllocResources(true);
  g_windowManager.AddMsgTarget(this);
  g_windowManager.AddMsgTarget(&g_playlistPlayer);
  g_windowManager.AddMsgTarget(&g_infoManager);
  g_windowManager.AddMsgTarget(&g_fontManager);
  g_windowManager.SetCallback(*this);
  g_windowManager.Initialize();
  CTextureCache::Get().Initialize();
  g_audioManager.Enable(true);
  g_audioManager.Load();

  if (g_SkinInfo->HasSkinFile("DialogFullScreenInfo.xml"))
    g_windowManager.Add(new CGUIDialogFullScreenInfo);

  CLog::Log(LOGINFO, "  skin loaded...");

  // leave the graphics lock
  lock.Leave();

  // restore windows
  if (currentWindow != WINDOW_INVALID)
  {
    g_windowManager.ActivateWindow(currentWindow);
    for (unsigned int i = 0; i < currentModelessWindows.size(); i++)
    {
      CGUIDialog *dialog = (CGUIDialog *)g_windowManager.GetWindow(currentModelessWindows[i]);
      if (dialog) dialog->Show();
    }
  }

  if (g_application.m_pPlayer && g_application.IsPlayingVideo())
  {
    if (bPreviousPlayingState)
      g_application.m_pPlayer->Pause();
    if (bPreviousRenderingState)
      g_windowManager.ActivateWindow(WINDOW_FULLSCREEN_VIDEO);
  }
}

void CApplication::UnloadSkin()
{
  g_audioManager.Enable(false);

  g_windowManager.DeInitialize();
  CTextureCache::Get().Deinitialize();

  //These windows are not handled by the windowmanager (why not?) so we should unload them manually
  CGUIMessage msg(GUI_MSG_WINDOW_DEINIT, 0, 0);
  m_guiPointer.OnMessage(msg);
  m_guiPointer.ResetControlStates();
  m_guiPointer.FreeResources(true);
  m_guiDialogMuteBug.OnMessage(msg);
  m_guiDialogMuteBug.ResetControlStates();
  m_guiDialogMuteBug.FreeResources(true);

  delete m_debugLayout;
  m_debugLayout = NULL;

  // remove the skin-dependent window
  g_windowManager.Delete(WINDOW_DIALOG_FULLSCREEN_INFO);

  g_TextureManager.Cleanup();
  g_largeTextureManager.CleanupUnusedImages(true);

  g_fontManager.Clear();

  g_colorManager.Clear();

  g_charsetConverter.reset();

  g_infoManager.Clear();
}

bool CApplication::LoadUserWindows()
{
  // Start from wherever home.xml is
  std::vector<CStdString> vecSkinPath;
  g_SkinInfo->GetSkinPaths(vecSkinPath);
  for (unsigned int i = 0;i < vecSkinPath.size();++i)
  {
    CLog::Log(LOGINFO, "Loading user windows, path %s", vecSkinPath[i].c_str());
    CFileItemList items;
    if (CDirectory::GetDirectory(vecSkinPath[i], items, ".xml", false))
    {
      for (int i = 0; i < items.Size(); ++i)
      {
        if (items[i]->m_bIsFolder)
          continue;
        CStdString skinFile = CUtil::GetFileName(items[i]->m_strPath);
        if (skinFile.Left(6).CompareNoCase("custom") == 0)
        {
          TiXmlDocument xmlDoc;
          if (!xmlDoc.LoadFile(items[i]->m_strPath))
          {
            CLog::Log(LOGERROR, "unable to load:%s, Line %d\n%s", items[i]->m_strPath.c_str(), xmlDoc.ErrorRow(), xmlDoc.ErrorDesc());
            continue;
          }

          // Root element should be <window>
          TiXmlElement* pRootElement = xmlDoc.RootElement();
          CStdString strValue = pRootElement->Value();
          if (!strValue.Equals("window"))
          {
            CLog::Log(LOGERROR, "file :%s doesnt contain <window>", skinFile.c_str());
            continue;
          }

          // Read the <type> element to get the window type to create
          // If no type is specified, create a CGUIWindow as default
          CGUIWindow* pWindow = NULL;
          CStdString strType;
          if (pRootElement->Attribute("type"))
            strType = pRootElement->Attribute("type");
          else
          {
            const TiXmlNode *pType = pRootElement->FirstChild("type");
            if (pType && pType->FirstChild())
              strType = pType->FirstChild()->Value();
          }
          int id = WINDOW_INVALID;
          if (!pRootElement->Attribute("id", &id))
          {
            const TiXmlNode *pType = pRootElement->FirstChild("id");
            if (pType && pType->FirstChild())
              id = atol(pType->FirstChild()->Value());
          }
          int visibleCondition = 0;
          CGUIControlFactory::GetConditionalVisibility(pRootElement, visibleCondition);

          if (strType.Equals("dialog"))
            pWindow = new CGUIDialog(id + WINDOW_HOME, skinFile);
          else if (strType.Equals("submenu"))
            pWindow = new CGUIDialogSubMenu(id + WINDOW_HOME, skinFile);
          else if (strType.Equals("buttonmenu"))
            pWindow = new CGUIDialogButtonMenu(id + WINDOW_HOME, skinFile);
          else
            pWindow = new CGUIStandardWindow(id + WINDOW_HOME, skinFile);

          // Check to make sure the pointer isn't still null
          if (pWindow == NULL)
          {
            CLog::Log(LOGERROR, "Out of memory / Failed to create new object in LoadUserWindows");
            return false;
          }
          if (id == WINDOW_INVALID || g_windowManager.GetWindow(WINDOW_HOME + id))
          {
            delete pWindow;
            continue;
          }
          pWindow->SetVisibleCondition(visibleCondition, false);
          g_windowManager.AddCustomWindow(pWindow);
        }
      }
    }
  }
  return true;
}

void CApplication::RenderNoPresent()
{
  MEASURE_FUNCTION;

// DXMERGE: This may have been important?
//  g_graphicsContext.AcquireCurrentContext();

  g_graphicsContext.Lock();

  // dont show GUI when playing full screen video
  if (g_graphicsContext.IsFullScreenVideo())
  {
    if (m_bPresentFrame && IsPlaying() && !IsPaused())
    {
      ResetScreenSaver();
      g_renderManager.Present();
    }
    else
      g_renderManager.RenderUpdate(true);

    // close window overlays
    CGUIDialog *overlay = (CGUIDialog *)g_windowManager.GetWindow(WINDOW_VIDEO_OVERLAY);
    if (overlay) overlay->Close(true);
    overlay = (CGUIDialog *)g_windowManager.GetWindow(WINDOW_MUSIC_OVERLAY);
    if (overlay) overlay->Close(true);

  }

  g_windowManager.Render();

  // if we're recording an audio stream then show blinking REC
  if (!g_graphicsContext.IsFullScreenVideo())
  {
    if (m_pPlayer && m_pPlayer->IsRecording() )
    {
      static int iBlinkRecord = 0;
      iBlinkRecord++;
      if (iBlinkRecord > 25)
      {
        CGUIFont* pFont = g_fontManager.GetFont("font13");
        CGUITextLayout::DrawText(pFont, 60, 50, 0xffff0000, 0, "REC", 0);
      }

      if (iBlinkRecord > 50)
        iBlinkRecord = 0;
    }
  }

  // Render the mouse pointer
  if (g_Mouse.IsActive())
    m_guiPointer.Render();

  // reset image scaling and effect states
  g_graphicsContext.SetRenderingResolution(g_graphicsContext.GetVideoResolution(), false);

  RenderMemoryStatus();
  RenderScreenSaver();

  g_graphicsContext.Unlock();
}

static int screenSaverFadeAmount = 0;

void CApplication::RenderScreenSaver()
{
  if (!m_screenSaver)
    return;

  if (m_screenSaver->ID() != "screensaver.xbmc.builtin.dim" &&
      m_screenSaver->ID() != "screensaver.xbmc.builtin.black")
    return; // nothing to do

  float amount = 1.0f;
  if (!m_screenSaver->GetSetting("level").IsEmpty())
    amount = 1.0f - 0.01f * (float)atof(m_screenSaver->GetSetting("level"));

  // special case for dim screensaver
  bool draw = false;
  if (amount > 0.f)
  {
    if (m_bScreenSave)
    {
      draw = true;
      if (screenSaverFadeAmount < 100)
      {
        screenSaverFadeAmount = std::min(100, screenSaverFadeAmount + 2);  // around a second to fade
      }
    }
    else
    {
      if (screenSaverFadeAmount > 0)
      {
        draw = true;
        screenSaverFadeAmount = std::max(0, screenSaverFadeAmount - 4);  // around a half second to unfade
      }
    }
  }
  if (draw)
  {
    color_t color = ((color_t)(screenSaverFadeAmount * amount * 2.55f) & 0xff) << 24;
    CGUITexture::DrawQuad(CRect(0, 0, (float)g_graphicsContext.GetWidth(), (float)g_graphicsContext.GetHeight()), color);
  }
}

bool CApplication::WaitFrame(unsigned int timeout)
{
  bool done = false;
#ifdef HAS_SDL
  // Wait for all other frames to be presented
  SDL_mutexP(m_frameMutex);
  //wait until event is set, but modify remaining time
  DWORD dwStartTime = CTimeUtils::GetTimeMS();
  DWORD dwRemainingTime = timeout;
  while(m_frameCount > 0)
  {
    int result = SDL_CondWaitTimeout(m_frameCond, m_frameMutex, dwRemainingTime);
    if (result == 0)
    {
      //fix time to wait because of spurious wakeups
      DWORD dwElapsed = CTimeUtils::GetTimeMS() - dwStartTime;
      if(dwElapsed < dwRemainingTime)
      {
        dwRemainingTime -= dwElapsed;
        continue;
      }
      else
      {
        //ran out of time
        result = SDL_MUTEX_TIMEDOUT;
      }
    }

    if(result == SDL_MUTEX_TIMEDOUT)
      break;
    if(result < 0)
      CLog::Log(LOGWARNING, "CApplication::WaitFrame - error from conditional wait");
  }
  done = m_frameCount == 0;
  SDL_mutexV(m_frameMutex);
#endif
  return done;
}

void CApplication::NewFrame()
{
#ifdef HAS_SDL
  // We just posted another frame. Keep track and notify.
  SDL_mutexP(m_frameMutex);
  m_frameCount++;
  SDL_mutexV(m_frameMutex);

  SDL_CondBroadcast(m_frameCond);
#endif
}

void CApplication::Render()
{
  if (!m_AppActive && !m_bStop && (!IsPlayingVideo() || IsPaused()))
  {
    Sleep(1);
    ResetScreenSaver();
    return;
  }

  MEASURE_FUNCTION;

  bool decrement = false;

  { // frame rate limiter (really bad, but it does the trick :p)
    static unsigned int lastFrameTime = 0;
    unsigned int currentTime = CTimeUtils::GetTimeMS();
    int nDelayTime = 0;
    // Less fps in DPMS or Black screensaver
    bool lowfps = (m_dpmsIsActive
                   || (m_bScreenSave && m_screenSaver && (m_screenSaver->ID() == "screensaver.xbmc.builtin.black")
                       && (screenSaverFadeAmount >= 100)));
    // Whether externalplayer is playing and we're unfocused
    bool extPlayerActive = m_eCurrentPlayer >= EPC_EXTPLAYER && IsPlaying() && !m_AppFocused;
    unsigned int singleFrameTime = 10; // default limit 100 fps

    m_bPresentFrame = false;
    if (!extPlayerActive && g_graphicsContext.IsFullScreenVideo() && !IsPaused())
    {
#ifdef HAS_SDL
      SDL_mutexP(m_frameMutex);

      //wait until event is set, but modify remaining time
      DWORD dwStartTime = CTimeUtils::GetTimeMS();
      DWORD dwRemainingTime = 100;
      // If we have frames or if we get notified of one, consume it.
      while(m_frameCount == 0)
      {
        int result = SDL_CondWaitTimeout(m_frameCond, m_frameMutex, dwRemainingTime);
        if (result == 0)
        {
          //fix time to wait because of spurious wakeups
          DWORD dwElapsed = CTimeUtils::GetTimeMS() - dwStartTime;
          if(dwElapsed < dwRemainingTime)
          {
            dwRemainingTime -= dwElapsed;
            continue;
          }
          else
          {
            //ran out of time
            result = SDL_MUTEX_TIMEDOUT;
          }
        }

        if(result == SDL_MUTEX_TIMEDOUT)
          break;
        if(result < 0)
          CLog::Log(LOGWARNING, "CApplication::Render - error from conditional wait");
      }

      m_bPresentFrame = m_frameCount > 0;
      SDL_mutexV(m_frameMutex);
#else
      m_bPresentFrame = true;
#endif
      decrement = m_bPresentFrame;
    }
    else
    {
      // engage the frame limiter as needed
      bool limitFrames = lowfps || extPlayerActive;
      // DXMERGE - we checked for g_videoConfig.GetVSyncMode() before this
      //           perhaps allowing it to be set differently than the UI option??
      if (g_guiSettings.GetInt("videoscreen.vsync") == VSYNC_DISABLED ||
          g_guiSettings.GetInt("videoscreen.vsync") == VSYNC_VIDEO)
        limitFrames = true; // not using vsync.
      else if ((g_infoManager.GetFPS() > g_graphicsContext.GetFPS() + 10) && g_infoManager.GetFPS() > 1000/singleFrameTime)
        limitFrames = true; // using vsync, but it isn't working.

      if (limitFrames)
      {
        if (extPlayerActive)
        {
          ResetScreenSaver();  // Prevent screensaver dimming the screen
          singleFrameTime = 1000;  // 1 fps, high wakeup latency but v.low CPU usage
        }
        else if (lowfps)
          singleFrameTime = 200;  // 5 fps, <=200 ms latency to wake up

        if (lastFrameTime + singleFrameTime > currentTime)
          nDelayTime = lastFrameTime + singleFrameTime - currentTime;
        Sleep(nDelayTime);
      }
      decrement = true;
    }

    lastFrameTime = CTimeUtils::GetTimeMS();
  }

  CSingleLock lock(g_graphicsContext);
  CTimeUtils::UpdateFrameTime();
  g_infoManager.UpdateFPS();

  int vsync_mode = g_guiSettings.GetInt("videoscreen.vsync");
  if (g_graphicsContext.IsFullScreenVideo() && IsPlaying() && vsync_mode == VSYNC_VIDEO)
    g_Windowing.SetVSync(true);
  else if (vsync_mode == VSYNC_ALWAYS)
    g_Windowing.SetVSync(true);
  else if (vsync_mode != VSYNC_DRIVER)
    g_Windowing.SetVSync(false);

  g_windowManager.UpdateModelessVisibility();

  if(!g_Windowing.BeginRender())
    return;

  RenderNoPresent();
  g_Windowing.EndRender();

  g_TextureManager.FreeUnusedTextures();

  // reset our info cache - we do this at the end of Render so that it is
  // fresh for the next process(), or after a windowclose animation (where process()
  // isn't called)
  g_infoManager.ResetCache();

  lock.Leave();

  g_graphicsContext.Flip();

  g_renderManager.UpdateResolution();

#ifdef HAS_SDL
  SDL_mutexP(m_frameMutex);
  if(m_frameCount > 0 && decrement)
    m_frameCount--;
  SDL_mutexV(m_frameMutex);
  SDL_CondBroadcast(m_frameCond);
#endif
}

void CApplication::SetStandAlone(bool value)
{
  g_advancedSettings.m_handleMounting = m_bStandalone = value;
}

void CApplication::RenderMemoryStatus()
{
  MEASURE_FUNCTION;

  g_cpuInfo.getUsedPercentage(); // must call it to recalculate pct values

  // reset the window scaling and fade status
  RESOLUTION res = g_graphicsContext.GetVideoResolution();
  g_graphicsContext.SetRenderingResolution(res, false);

  static int yShift = 20;
  static int xShift = 40;
  static unsigned int lastShift = time(NULL);
  time_t now = time(NULL);
  if (now - lastShift > 10)
  {
    yShift *= -1;
    if (now % 5 == 0)
      xShift *= -1;
    lastShift = now;
  }

  if (!m_debugLayout)
  {
    CGUIFont *font13 = g_fontManager.GetDefaultFont();
    CGUIFont *font13border = g_fontManager.GetDefaultFont(true);
    if (font13)
      m_debugLayout = new CGUITextLayout(font13, true, 0, font13border);
  }
  if (!m_debugLayout)
    return;

  if (LOG_LEVEL_DEBUG_FREEMEM <= g_advancedSettings.m_logLevel)
  {
    CStdString info;
    MEMORYSTATUS stat;
    GlobalMemoryStatus(&stat);
    CStdString profiling = CGUIControlProfiler::IsRunning() ? " (profiling)" : "";
    CStdString strCores = g_cpuInfo.GetCoresUsageString();
#if !defined(_LINUX)
    info.Format("LOG: %sxbmc.log\nMEM: %d/%d KB - FPS: %2.1f fps\nCPU: %s%s", g_settings.m_logFolder.c_str(),
              stat.dwAvailPhys/1024, stat.dwTotalPhys/1024, g_infoManager.GetFPS(), strCores.c_str(), profiling.c_str());
#else
    double dCPU = m_resourceCounter.GetCPUUsage();
    info.Format("LOG: %sxbmc.log\nMEM: %"PRIu64"/%"PRIu64" KB - FPS: %2.1f fps\nCPU: %s (CPU-XBMC %4.2f%%%s)", g_settings.m_logFolder.c_str(),
              stat.dwAvailPhys/1024, stat.dwTotalPhys/1024, g_infoManager.GetFPS(), strCores.c_str(), dCPU, profiling.c_str());
#endif


    float x = xShift + 0.04f * g_graphicsContext.GetWidth() + g_settings.m_ResInfo[res].Overscan.left;
    float y = yShift + 0.04f * g_graphicsContext.GetHeight() + g_settings.m_ResInfo[res].Overscan.top;

    m_debugLayout->Update(info);
    m_debugLayout->RenderOutline(x, y, 0xffffffff, 0xff000000, 0, 0);
  }

  // render the skin debug info
  if (g_SkinInfo->IsDebugging())
  {
    CStdString info;
    CGUIWindow *window = g_windowManager.GetWindow(g_windowManager.GetFocusedWindow());
    CPoint point(m_guiPointer.GetXPosition(), m_guiPointer.GetYPosition());
    if (window)
    {
      CStdString windowName = CButtonTranslator::TranslateWindow(window->GetID());
      if (!windowName.IsEmpty())
        windowName += " (" + window->GetProperty("xmlfile") + ")";
      else
        windowName = window->GetProperty("xmlfile");
      info = "Window: " + windowName + "  ";
      // transform the mouse coordinates to this window's coordinates
      g_graphicsContext.SetScalingResolution(window->GetCoordsRes(), true);
      point.x *= g_graphicsContext.GetGUIScaleX();
      point.y *= g_graphicsContext.GetGUIScaleY();
      g_graphicsContext.SetRenderingResolution(res, false);
    }
    info.AppendFormat("Mouse: (%d,%d)  ", (int)point.x, (int)point.y);
    if (window)
    {
      CGUIControl *control = window->GetFocusedControl();
      if (control)
        info.AppendFormat("Focused: %i (%s)", control->GetID(), CGUIControlFactory::TranslateControlType(control->GetControlType()).c_str());
    }

    float x = xShift + 0.04f * g_graphicsContext.GetWidth() + g_settings.m_ResInfo[res].Overscan.left;
    float y = yShift + 0.08f * g_graphicsContext.GetHeight() + g_settings.m_ResInfo[res].Overscan.top;

    m_debugLayout->Update(info);
    m_debugLayout->RenderOutline(x, y, 0xffffffff, 0xff000000, 0, 0);
  }
}

// OnKey() translates the key into a CAction which is sent on to our Window Manager.
// The window manager will return true if the event is processed, false otherwise.
// If not already processed, this routine handles global keypresses.  It returns
// true if the key has been processed, false otherwise.

bool CApplication::OnKey(const CKey& key)
{

  // Turn the mouse off, as we've just got a keypress from controller or remote
  g_Mouse.SetActive(false);

  // get the current active window
  int iWin = g_windowManager.GetActiveWindow() & WINDOW_ID_MASK;

  // this will be checked for certain keycodes that need
  // special handling if the screensaver is active
  CAction action = CButtonTranslator::GetInstance().GetAction(iWin, key);

  // a key has been pressed.
  // reset Idle Timer
  m_idleTimer.StartZero();
  bool processKey = AlwaysProcess(action);

  ResetScreenSaver();

  // allow some keys to be processed while the screensaver is active
  if (WakeUpScreenSaverAndDPMS() && !processKey)
  {
    CLog::Log(LOGDEBUG, "%s: %s pressed, screen saver/dpms woken up", __FUNCTION__, g_Keyboard.GetKeyName((int) key.GetButtonCode()).c_str());
    return true;
  }

  // change this if we have a dialog up
  if (g_windowManager.HasModalDialog())
  {
    iWin = g_windowManager.GetTopMostModalDialogID() & WINDOW_ID_MASK;
  }
  if (iWin == WINDOW_DIALOG_FULLSCREEN_INFO)
  { // fullscreen info dialog - special case
    action = CButtonTranslator::GetInstance().GetAction(iWin, key);

    if (!key.IsAnalogButton())
      CLog::Log(LOGDEBUG, "%s: %s pressed, trying fullscreen info action %s", __FUNCTION__, g_Keyboard.GetKeyName((int) key.GetButtonCode()).c_str(), action.GetName().c_str());

    if (OnAction(action))
      return true;

    // fallthrough to the main window
    iWin = WINDOW_FULLSCREEN_VIDEO;
  }
  if (iWin == WINDOW_FULLSCREEN_VIDEO)
  {
    // current active window is full screen video.
    if (g_application.m_pPlayer && g_application.m_pPlayer->IsInMenu())
    {
      // if player is in some sort of menu, (ie DVDMENU) map buttons differently
      action = CButtonTranslator::GetInstance().GetAction(WINDOW_VIDEO_MENU, key);
    }
    else
    {
      // no then use the fullscreen window section of keymap.xml to map key->action
      action = CButtonTranslator::GetInstance().GetAction(iWin, key);
    }
  }
  else
  {
    // current active window isnt the fullscreen window
    // just use corresponding section from keymap.xml
    // to map key->action

    // first determine if we should use keyboard input directly
    bool useKeyboard = key.FromKeyboard() && (iWin == WINDOW_DIALOG_KEYBOARD || iWin == WINDOW_DIALOG_NUMERIC);
    CGUIWindow *window = g_windowManager.GetWindow(iWin);
    if (window)
    {
      CGUIControl *control = window->GetFocusedControl();
      if (control)
      {
        if (control->GetControlType() == CGUIControl::GUICONTROL_EDIT ||
           (control->IsContainer() && key.GetModifiers() == CKey::MODIFIER_SHIFT)) // shift and no other modifiers
          useKeyboard = true;
      }
    }
    if (useKeyboard)
    {
      action = CAction(0); // reset our action
      if (g_guiSettings.GetBool("input.remoteaskeyboard"))
      {
        // users remote is executing keyboard commands, so use the virtualkeyboard section of keymap.xml
        // and send those rather than actual keyboard presses.  Only for navigation-type commands though
        action = CButtonTranslator::GetInstance().GetAction(WINDOW_DIALOG_KEYBOARD, key);
        if (!(action.GetID() == ACTION_MOVE_LEFT ||
              action.GetID() == ACTION_MOVE_RIGHT ||
              action.GetID() == ACTION_MOVE_UP ||
              action.GetID() == ACTION_MOVE_DOWN ||
              action.GetID() == ACTION_SELECT_ITEM ||
              action.GetID() == ACTION_ENTER ||
              action.GetID() == ACTION_PREVIOUS_MENU ||
              action.GetID() == ACTION_CLOSE_DIALOG))
        {
          // the action isn't plain navigation - check for a keyboard-specific keymap
          action = CButtonTranslator::GetInstance().GetAction(WINDOW_DIALOG_KEYBOARD, key, false);
          if (!(action.GetID() >= REMOTE_0 && action.GetID() <= REMOTE_9) ||
                action.GetID() == ACTION_BACKSPACE ||
                action.GetID() == ACTION_SHIFT ||
                action.GetID() == ACTION_SYMBOLS ||
                action.GetID() == ACTION_CURSOR_LEFT ||
                action.GetID() == ACTION_CURSOR_RIGHT)
            action = CAction(0); // don't bother with this action
        }
      }
      if (!action.GetID())
      {
        // keyboard entry - pass the keys through directly
        if (key.GetFromHttpApi())
          action = CAction(key.GetButtonCode() != KEY_INVALID ? key.GetButtonCode() : 0, key.GetUnicode());
        else
        { // see if we've got an ascii key
          if (key.GetUnicode())
            action = CAction(key.GetAscii() | KEY_ASCII, key.GetUnicode());
          else
            action = CAction(key.GetVKey() | KEY_VKEY);
        }
      }

      CLog::Log(LOGDEBUG, "%s: %s pressed, trying keyboard action %i", __FUNCTION__, g_Keyboard.GetKeyName((int) key.GetButtonCode()).c_str(), action.GetID());

      if (OnAction(action))
        return true;
      // failed to handle the keyboard action, drop down through to standard action
    }
    if (key.GetFromHttpApi())
    {
      if (key.GetButtonCode() != KEY_INVALID)
        action = CButtonTranslator::GetInstance().GetAction(iWin, key);
    }
    else
      action = CButtonTranslator::GetInstance().GetAction(iWin, key);
  }
  if (!key.IsAnalogButton())
    CLog::Log(LOGDEBUG, "%s: %s pressed, action is %s", __FUNCTION__, g_Keyboard.GetKeyName((int) key.GetButtonCode()).c_str(), action.GetName().c_str());

  //  Play a sound based on the action
  g_audioManager.PlayActionSound(action);

  return OnAction(action);
}

// OnAppCommand is called in response to a XBMC_APPCOMMAND event.

bool CApplication::OnAppCommand(const CAction &action)
{
  // Reset the screen saver
  ResetScreenSaver();

  // If we were currently in the screen saver wake up and don't process the appcommand
  if (WakeUpScreenSaverAndDPMS())
  {
    return true;
  }

  // Process the appcommand
  return OnAction(action);
}

bool CApplication::OnAction(const CAction &action)
{
#ifdef HAS_HTTPAPI
  // Let's tell the outside world about this action, ignoring mouse moves
  if (g_settings.m_HttpApiBroadcastLevel>=2 && action.GetID() != ACTION_MOUSE_MOVE)
  {
    CStdString tmp;
    tmp.Format("%i",action.GetID());
    getApplicationMessenger().HttpApi("broadcastlevel; OnAction:"+tmp+";2");
  }
#endif

  // special case for switching between GUI & fullscreen mode.
  if (action.GetID() == ACTION_SHOW_GUI)
  { // Switch to fullscreen mode if we can
    if (SwitchToFullScreen())
    {
      m_navigationTimer.StartZero();
      return true;
    }
  }

  if (action.GetID() == ACTION_TOGGLE_FULLSCREEN)
  {
    g_graphicsContext.ToggleFullScreenRoot();
    return true;
  }

  if (action.IsMouse())
  {
    g_Mouse.SetActive(true);
    m_guiPointer.SetPosition(action.GetAmount(0), action.GetAmount(1));
  }

  // The action PLAYPAUSE behaves as ACTION_PAUSE if we are currently
  // playing or ACTION_PLAYER_PLAY if we are not playing.
  if (action.GetID() == ACTION_PLAYER_PLAYPAUSE)
  {
    if (IsPlaying())
      return OnAction(CAction(ACTION_PAUSE));
    else
      return OnAction(CAction(ACTION_PLAYER_PLAY));
  }

// in normal case
  // just pass the action to the current window and let it handle it
  if (g_windowManager.OnAction(action))
  {
    m_navigationTimer.StartZero();
    return true;
  }

  // handle extra global presses

  // screenshot : take a screenshot :)
  if (action.GetID() == ACTION_TAKE_SCREENSHOT)
  {
    CUtil::TakeScreenshot();
    return true;
  }
  // built in functions : execute the built-in
  if (action.GetID() == ACTION_BUILT_IN_FUNCTION)
  {
    CBuiltins::Execute(action.GetName());
    m_navigationTimer.StartZero();
    return true;
  }

  // reload keymaps
  if (action.GetID() == ACTION_RELOAD_KEYMAPS)
  {
    CButtonTranslator::GetInstance().Clear();
    CButtonTranslator::GetInstance().Load();
  }

  // show info : Shows the current video or song information
  if (action.GetID() == ACTION_SHOW_INFO)
  {
    g_infoManager.ToggleShowInfo();
    return true;
  }

  // codec info : Shows the current song, video or picture codec information
  if (action.GetID() == ACTION_SHOW_CODEC)
  {
    g_infoManager.ToggleShowCodec();
    return true;
  }

  if ((action.GetID() == ACTION_INCREASE_RATING || action.GetID() == ACTION_DECREASE_RATING) && IsPlayingAudio())
  {
    const CMusicInfoTag *tag = g_infoManager.GetCurrentSongTag();
    if (tag)
    {
      *m_itemCurrentFile->GetMusicInfoTag() = *tag;
      char rating = tag->GetRating();
      bool needsUpdate(false);
      if (rating > '0' && action.GetID() == ACTION_DECREASE_RATING)
      {
        m_itemCurrentFile->GetMusicInfoTag()->SetRating(rating - 1);
        needsUpdate = true;
      }
      else if (rating < '5' && action.GetID() == ACTION_INCREASE_RATING)
      {
        m_itemCurrentFile->GetMusicInfoTag()->SetRating(rating + 1);
        needsUpdate = true;
      }
      if (needsUpdate)
      {
        CMusicDatabase db;
        if (db.Open())      // OpenForWrite() ?
        {
          db.SetSongRating(m_itemCurrentFile->m_strPath, m_itemCurrentFile->GetMusicInfoTag()->GetRating());
          db.Close();
        }
        // send a message to all windows to tell them to update the fileitem (eg playlistplayer, media windows)
        CGUIMessage msg(GUI_MSG_NOTIFY_ALL, 0, 0, GUI_MSG_UPDATE_ITEM, 0, m_itemCurrentFile);
        g_windowManager.SendMessage(msg);
      }
    }
    return true;
  }

  // stop : stops playing current audio song
  if (action.GetID() == ACTION_STOP)
  {
    StopPlaying();
    return true;
  }

  // previous : play previous song from playlist
  if (action.GetID() == ACTION_PREV_ITEM)
  {
    // first check whether we're within 3 seconds of the start of the track
    // if not, we just revert to the start of the track
    if (m_pPlayer && m_pPlayer->CanSeek() && GetTime() > 3)
    {
      SeekTime(0);
      SetPlaySpeed(1);
    }
    else
    {
      g_playlistPlayer.PlayPrevious();
    }
    return true;
  }

  // next : play next song from playlist
  if (action.GetID() == ACTION_NEXT_ITEM)
  {
    if (IsPlaying() && m_pPlayer->SkipNext())
      return true;

    g_playlistPlayer.PlayNext();

    return true;
  }

  if ( IsPlaying())
  {
    // pause : pauses current audio song
    if (action.GetID() == ACTION_PAUSE && m_iPlaySpeed == 1)
    {
      m_pPlayer->Pause();
#ifdef HAS_KARAOKE
      m_pKaraokeMgr->SetPaused( m_pPlayer->IsPaused() );
#endif
      if (!m_pPlayer->IsPaused())
      { // unpaused - set the playspeed back to normal
        SetPlaySpeed(1);
      }
      g_audioManager.Enable(m_pPlayer->IsPaused() && !g_audioContext.IsPassthroughActive());
      return true;
    }
    if (!m_pPlayer->IsPaused())
    {
      // if we do a FF/RW in my music then map PLAY action togo back to normal speed
      // if we are playing at normal speed, then allow play to pause
      if (action.GetID() == ACTION_PLAYER_PLAY || action.GetID() == ACTION_PAUSE)
      {
        if (m_iPlaySpeed != 1)
        {
          SetPlaySpeed(1);
        }
        else
        {
          m_pPlayer->Pause();
        }
        return true;
      }
      if (action.GetID() == ACTION_PLAYER_FORWARD || action.GetID() == ACTION_PLAYER_REWIND)
      {
        int iPlaySpeed = m_iPlaySpeed;
        if (action.GetID() == ACTION_PLAYER_REWIND && iPlaySpeed == 1) // Enables Rewinding
          iPlaySpeed *= -2;
        else if (action.GetID() == ACTION_PLAYER_REWIND && iPlaySpeed > 1) //goes down a notch if you're FFing
          iPlaySpeed /= 2;
        else if (action.GetID() == ACTION_PLAYER_FORWARD && iPlaySpeed < 1) //goes up a notch if you're RWing
          iPlaySpeed /= 2;
        else
          iPlaySpeed *= 2;

        if (action.GetID() == ACTION_PLAYER_FORWARD && iPlaySpeed == -1) //sets iSpeed back to 1 if -1 (didn't plan for a -1)
          iPlaySpeed = 1;
        if (iPlaySpeed > 32 || iPlaySpeed < -32)
          iPlaySpeed = 1;

        SetPlaySpeed(iPlaySpeed);
        return true;
      }
      else if ((action.GetAmount() || GetPlaySpeed() != 1) && (action.GetID() == ACTION_ANALOG_REWIND || action.GetID() == ACTION_ANALOG_FORWARD))
      {
        // calculate the speed based on the amount the button is held down
        int iPower = (int)(action.GetAmount() * MAX_FFWD_SPEED + 0.5f);
        // returns 0 -> MAX_FFWD_SPEED
        int iSpeed = 1 << iPower;
        if (iSpeed != 1 && action.GetID() == ACTION_ANALOG_REWIND)
          iSpeed = -iSpeed;
        g_application.SetPlaySpeed(iSpeed);
        if (iSpeed == 1)
          CLog::Log(LOGDEBUG,"Resetting playspeed");
        return true;
      }
    }
    // allow play to unpause
    else
    {
      if (action.GetID() == ACTION_PLAYER_PLAY)
      {
        // unpause, and set the playspeed back to normal
        m_pPlayer->Pause();
        g_audioManager.Enable(m_pPlayer->IsPaused() && !g_audioContext.IsPassthroughActive());

        g_application.SetPlaySpeed(1);
        return true;
      }
    }
  }
  if (action.GetID() == ACTION_MUTE)
  {
    Mute();
    return true;
  }

  if (action.GetID() == ACTION_TOGGLE_DIGITAL_ANALOG)
  {
    switch(g_guiSettings.GetInt("audiooutput.mode"))
    {
      case AUDIO_ANALOG: g_guiSettings.SetInt("audiooutput.mode", AUDIO_IEC958); break;
      case AUDIO_IEC958: g_guiSettings.SetInt("audiooutput.mode", AUDIO_HDMI  ); break;
      case AUDIO_HDMI  : g_guiSettings.SetInt("audiooutput.mode", AUDIO_ANALOG); break;
    }

    g_application.Restart();
    if (g_windowManager.GetActiveWindow() == WINDOW_SETTINGS_SYSTEM)
    {
      CGUIMessage msg(GUI_MSG_WINDOW_INIT, 0,0,WINDOW_INVALID,g_windowManager.GetActiveWindow());
      g_windowManager.SendMessage(msg);
    }
    return true;
  }

  // Check for global volume control
  if (action.GetAmount() && (action.GetID() == ACTION_VOLUME_UP || action.GetID() == ACTION_VOLUME_DOWN))
  {
    if (!m_pPlayer || !m_pPlayer->IsPassthrough())
    {
      // increase or decrease the volume
      int volume = g_settings.m_nVolumeLevel + g_settings.m_dynamicRangeCompressionLevel;

      // calculate speed so that a full press will equal 1 second from min to max
      float speed = float(VOLUME_MAXIMUM - VOLUME_MINIMUM);
      if (action.GetRepeat())
        speed *= action.GetRepeat();
      else
        speed /= 50; //50 fps
      if (g_settings.m_bMute)
      {
        // only unmute if volume is to be increased, otherwise leave muted
        if (action.GetID() == ACTION_VOLUME_DOWN)
          return true;
          
        if (g_settings.m_iPreMuteVolumeLevel == 0)
          SetVolume(1);
        else
          // In muted, unmute
          Mute();
        return true;
      }
      if (action.GetID() == ACTION_VOLUME_UP)
      {
        volume += (int)((float)fabs(action.GetAmount()) * action.GetAmount() * speed);
      }
      else
      {
        volume -= (int)((float)fabs(action.GetAmount()) * action.GetAmount() * speed);
      }

      SetHardwareVolume(volume);
  #ifndef HAS_SDL_AUDIO
      g_audioManager.SetVolume(g_settings.m_nVolumeLevel);
  #else
      g_audioManager.SetVolume((int)(128.f * (g_settings.m_nVolumeLevel - VOLUME_MINIMUM) / (float)(VOLUME_MAXIMUM - VOLUME_MINIMUM)));
  #endif
    }
    // show visual feedback of volume change...
    m_guiDialogVolumeBar.Show();
    m_guiDialogVolumeBar.OnAction(action);
    return true;
  }
  // Check for global seek control
  if (IsPlaying() && action.GetAmount() && (action.GetID() == ACTION_ANALOG_SEEK_FORWARD || action.GetID() == ACTION_ANALOG_SEEK_BACK))
  {
    if (!m_pPlayer->CanSeek()) return false;
    m_guiDialogSeekBar.OnAction(action);
    return true;
  }
  if (action.GetID() == ACTION_GUIPROFILE_BEGIN)
  {
    CGUIControlProfiler::Instance().SetOutputFile(_P("special://home/guiprofiler.xml"));
    CGUIControlProfiler::Instance().Start();
    return true;
  }
  return false;
}

void CApplication::UpdateLCD()
{
#ifdef HAS_LCD
  static long lTickCount = 0;

  if (!g_lcd || !g_guiSettings.GetBool("videoscreen.haslcd"))
    return ;
  long lTimeOut = 1000;
  if ( m_iPlaySpeed != 1)
    lTimeOut = 0;
  if ( ((long)CTimeUtils::GetTimeMS() - lTickCount) >= lTimeOut)
  {
    if (g_application.NavigationIdleTime() < 5)
      g_lcd->Render(ILCD::LCD_MODE_NAVIGATION);
    else if (IsPlayingVideo())
      g_lcd->Render(ILCD::LCD_MODE_VIDEO);
    else if (IsPlayingAudio())
      g_lcd->Render(ILCD::LCD_MODE_MUSIC);
    else if (IsInScreenSaver())
      g_lcd->Render(ILCD::LCD_MODE_SCREENSAVER);
    else
      g_lcd->Render(ILCD::LCD_MODE_GENERAL);

    // reset tick count
    lTickCount = CTimeUtils::GetTimeMS();
  }
#endif
}

void CApplication::FrameMove()
{
  MEASURE_FUNCTION;

  // currently we calculate the repeat time (ie time from last similar keypress) just global as fps
  float frameTime = m_frameTime.GetElapsedSeconds();
  m_frameTime.StartZero();
  // never set a frametime less than 2 fps to avoid problems when debuggin and on breaks
  if( frameTime > 0.5 ) frameTime = 0.5;

  g_graphicsContext.Lock();
  // check if there are notifications to display
  if (m_guiDialogKaiToast.DoWork())
  {
    if (!m_guiDialogKaiToast.IsDialogRunning())
    {
      m_guiDialogKaiToast.Show();
    }
  }
  g_graphicsContext.Unlock();

  UpdateLCD();

#if defined(HAS_LIRC) || defined(HAS_IRSERVERSUITE)
  // Read the input from a remote
  g_RemoteControl.Update();
#endif

  // process input actions
  CWinEvents::MessagePump();
  ProcessHTTPApiButtons();
  ProcessRemote(frameTime);
  ProcessGamepad(frameTime);
  ProcessEventServer(frameTime);

  g_windowManager.FrameMove();
}

bool CApplication::ProcessGamepad(float frameTime)
{
#ifdef HAS_SDL_JOYSTICK
  if (!g_advancedSettings.m_bReadControllerIfNotFocused && !m_AppFocused)
    return false;
  int iWin = g_windowManager.GetActiveWindow() & WINDOW_ID_MASK;
  if (g_windowManager.HasModalDialog())
  {
    iWin = g_windowManager.GetTopMostModalDialogID() & WINDOW_ID_MASK;
  }
  int bid;
  g_Joystick.Update();
  if (g_Joystick.GetButton(bid))
  {
    // reset Idle Timer
    m_idleTimer.StartZero();

    ResetScreenSaver();
    if (WakeUpScreenSaverAndDPMS())
    {
      g_Joystick.Reset(true);
      return true;
    }

    int actionID;
    CStdString actionName;
    bool fullrange;
    if (CButtonTranslator::GetInstance().TranslateJoystickString(iWin, g_Joystick.GetJoystick().c_str(), bid, JACTIVE_BUTTON, actionID, actionName, fullrange))
    {
      CAction action(actionID, 1.0f, 0.0f, actionName);
      g_audioManager.PlayActionSound(action);
      g_Joystick.Reset();
      g_Mouse.SetActive(false);
      return OnAction(action);
    }
    else
    {
      g_Joystick.Reset();
    }
  }
  if (g_Joystick.GetAxis(bid))
  {
    if (g_Joystick.GetAmount() < 0)
    {
      bid = -bid;
    }

    int actionID;
    CStdString actionName;
    bool fullrange;
    if (CButtonTranslator::GetInstance().TranslateJoystickString(iWin, g_Joystick.GetJoystick().c_str(), bid, JACTIVE_AXIS, actionID, actionName, fullrange))
    {
      ResetScreenSaver();
      if (WakeUpScreenSaverAndDPMS())
      {
        return true;
      }

      CAction action(actionID, fullrange ? (g_Joystick.GetAmount() + 1.0f)/2.0f : fabs(g_Joystick.GetAmount()), 0.0f, actionName);
      g_audioManager.PlayActionSound(action);
      g_Joystick.Reset();
      g_Mouse.SetActive(false);
      return OnAction(action);
    }
    else
    {
      g_Joystick.ResetAxis(abs(bid));
    }
  }
  int position;
  if (g_Joystick.GetHat(bid, position))
  {
    // reset Idle Timer
    m_idleTimer.StartZero();

    ResetScreenSaver();
    if (WakeUpScreenSaverAndDPMS())
    {
      g_Joystick.Reset();
      return true;
    }

    int actionID;
    CStdString actionName;
    bool fullrange;

    bid = position<<16|bid;

    if (CButtonTranslator::GetInstance().TranslateJoystickString(iWin, g_Joystick.GetJoystick().c_str(), bid, JACTIVE_HAT, actionID, actionName, fullrange))
    {
      CAction action(actionID, 1.0f, 0.0f, actionName);
      g_audioManager.PlayActionSound(action);
      g_Joystick.Reset();
      g_Mouse.SetActive(false);
      return OnAction(action);
    }
  }
#endif
  return false;
}

bool CApplication::ProcessRemote(float frameTime)
{
#if defined(HAS_LIRC) || defined(HAS_IRSERVERSUITE)
  if (g_RemoteControl.GetButton())
  {
    CKey key(g_RemoteControl.GetButton(), g_RemoteControl.GetHoldTime());
    g_RemoteControl.Reset();
    return OnKey(key);
  }
#endif
  return false;
}

bool CApplication::ProcessMouse()
{
  MEASURE_FUNCTION;

  if (!g_Mouse.IsActive() || !m_AppFocused)
    return false;

  // Reset the screensaver and idle timers
  m_idleTimer.StartZero();
  ResetScreenSaver();
  if (WakeUpScreenSaverAndDPMS())
    return true;

  return OnAction(g_Mouse.GetAction());
}

void  CApplication::CheckForTitleChange()
{
#ifdef HAS_HTTPAPI
  if (g_settings.m_HttpApiBroadcastLevel>=1)
  {
    if (IsPlayingVideo())
    {
      const CVideoInfoTag* tagVal = g_infoManager.GetCurrentMovieTag();
      if (m_pXbmcHttp && tagVal && !(tagVal->m_strTitle.IsEmpty()))
      {
        CStdString msg=m_pXbmcHttp->GetOpenTag()+"MovieTitle:"+tagVal->m_strTitle+m_pXbmcHttp->GetCloseTag();
        if (m_prevMedia!=msg && g_settings.m_HttpApiBroadcastLevel>=1)
        {
          getApplicationMessenger().HttpApi("broadcastlevel; MediaChanged:"+msg+";1");
          m_prevMedia=msg;
        }
      }
    }
    else if (IsPlayingAudio())
    {
      const CMusicInfoTag* tagVal=g_infoManager.GetCurrentSongTag();
      if (m_pXbmcHttp && tagVal)
      {
        CStdString msg="";
        if (!tagVal->GetTitle().IsEmpty())
          msg=m_pXbmcHttp->GetOpenTag()+"AudioTitle:"+tagVal->GetTitle()+m_pXbmcHttp->GetCloseTag();
        if (!tagVal->GetArtist().IsEmpty())
          msg+=m_pXbmcHttp->GetOpenTag()+"AudioArtist:"+tagVal->GetArtist()+m_pXbmcHttp->GetCloseTag();
        if (m_prevMedia!=msg)
        {
          getApplicationMessenger().HttpApi("broadcastlevel; MediaChanged:"+msg+";1");
          m_prevMedia=msg;
        }
      }
    }
  }
#endif
}

bool CApplication::ProcessHTTPApiButtons()
{
#ifdef HAS_HTTPAPI
  if (m_pXbmcHttp)
  {
    // copy key from webserver, and reset it in case we're called again before
    // whatever happens in OnKey()
    CKey keyHttp(m_pXbmcHttp->GetKey());
    m_pXbmcHttp->ResetKey();
    if (keyHttp.GetButtonCode() != KEY_INVALID)
    {
      if (keyHttp.GetButtonCode() == KEY_VMOUSE) //virtual mouse
      {
        int actionID = ACTION_MOUSE_MOVE;
        if (keyHttp.GetLeftTrigger() == 1)
          actionID = ACTION_MOUSE_LEFT_CLICK;
        else if (keyHttp.GetLeftTrigger() == 2)
          actionID = ACTION_MOUSE_RIGHT_CLICK;
        else if (keyHttp.GetLeftTrigger() == 3)
          actionID = ACTION_MOUSE_MIDDLE_CLICK;
        else if (keyHttp.GetRightTrigger() == 1)
          actionID = ACTION_MOUSE_DOUBLE_CLICK;
        CAction action(actionID, keyHttp.GetLeftThumbX(), keyHttp.GetLeftThumbY());
        OnAction(action);
      }
      else
        OnKey(keyHttp);
      return true;
    }
  }
  return false;
#endif
}

bool CApplication::ProcessEventServer(float frameTime)
{
#ifdef HAS_EVENT_SERVER
  CEventServer* es = CEventServer::GetInstance();
  if (!es || !es->Running() || es->GetNumberOfClients()==0)
    return false;

  // process any queued up actions
  if (es->ExecuteNextAction())
  {
    // reset idle timers
    m_idleTimer.StartZero();
    ResetScreenSaver();
    WakeUpScreenSaverAndDPMS();
  }

  // now handle any buttons or axis
  std::string joystickName;
  bool isAxis = false;
  float fAmount = 0.0;

  WORD wKeyID = es->GetButtonCode(joystickName, isAxis, fAmount);

  if (wKeyID)
  {
    if (joystickName.length() > 0)
    {
      if (isAxis == true)
      {
        if (fabs(fAmount) >= 0.08)
          m_lastAxisMap[joystickName][wKeyID] = fAmount;
        else
          m_lastAxisMap[joystickName].erase(wKeyID);
      }

      return ProcessJoystickEvent(joystickName, wKeyID, isAxis, fAmount);
    }
    else
    {
      CKey key;
      if(wKeyID == KEY_BUTTON_LEFT_ANALOG_TRIGGER)
        key = CKey(wKeyID, (BYTE)(255*fAmount), 0, 0.0, 0.0, 0.0, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_RIGHT_ANALOG_TRIGGER)
        key = CKey(wKeyID, 0, (BYTE)(255*fAmount), 0.0, 0.0, 0.0, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_LEFT_THUMB_STICK_LEFT)
        key = CKey(wKeyID, 0, 0, -fAmount, 0.0, 0.0, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_LEFT_THUMB_STICK_RIGHT)
        key = CKey(wKeyID, 0, 0,  fAmount, 0.0, 0.0, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_LEFT_THUMB_STICK_UP)
        key = CKey(wKeyID, 0, 0, 0.0,  fAmount, 0.0, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_LEFT_THUMB_STICK_DOWN)
        key = CKey(wKeyID, 0, 0, 0.0, -fAmount, 0.0, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_RIGHT_THUMB_STICK_LEFT)
        key = CKey(wKeyID, 0, 0, 0.0, 0.0, -fAmount, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_RIGHT_THUMB_STICK_RIGHT)
        key = CKey(wKeyID, 0, 0, 0.0, 0.0,  fAmount, 0.0, frameTime);
      else if(wKeyID == KEY_BUTTON_RIGHT_THUMB_STICK_UP)
        key = CKey(wKeyID, 0, 0, 0.0, 0.0, 0.0,  fAmount, frameTime);
      else if(wKeyID == KEY_BUTTON_RIGHT_THUMB_STICK_DOWN)
        key = CKey(wKeyID, 0, 0, 0.0, 0.0, 0.0, -fAmount, frameTime);
      else
        key = CKey(wKeyID);
      return OnKey(key);
    }
  }

  if (m_lastAxisMap.size() > 0)
  {
    // Process all the stored axis.
    for (map<std::string, map<int, float> >::iterator iter = m_lastAxisMap.begin(); iter != m_lastAxisMap.end(); ++iter)
    {
      for (map<int, float>::iterator iterAxis = (*iter).second.begin(); iterAxis != (*iter).second.end(); ++iterAxis)
        ProcessJoystickEvent((*iter).first, (*iterAxis).first, true, (*iterAxis).second);
    }
  }

  {
    CPoint pos;
    if (es->GetMousePos(pos.x, pos.y) && g_Mouse.IsEnabled())
      return OnAction(CAction(ACTION_MOUSE_MOVE, pos.x, pos.y));
  }
#endif
  return false;
}

bool CApplication::ProcessJoystickEvent(const std::string& joystickName, int wKeyID, bool isAxis, float fAmount)
{
#if defined(HAS_EVENT_SERVER)
  m_idleTimer.StartZero();

   // Make sure to reset screen saver, mouse.
   ResetScreenSaver();
   if (WakeUpScreenSaverAndDPMS())
     return true;

#ifdef HAS_SDL_JOYSTICK
   g_Joystick.Reset();
#endif
   g_Mouse.SetActive(false);

   // Figure out what window we're taking the event for.
   int iWin = g_windowManager.GetActiveWindow() & WINDOW_ID_MASK;
   if (g_windowManager.HasModalDialog())
       iWin = g_windowManager.GetTopMostModalDialogID() & WINDOW_ID_MASK;

   // This code is copied from the OnKey handler, it should be factored out.
   if (iWin == WINDOW_FULLSCREEN_VIDEO &&
       g_application.m_pPlayer &&
       g_application.m_pPlayer->IsInMenu())
   {
     // If player is in some sort of menu, (ie DVDMENU) map buttons differently.
     iWin = WINDOW_VIDEO_MENU;
   }

   int actionID;
   CStdString actionName;
   bool fullRange = false;

   // Translate using regular joystick translator.
   if (CButtonTranslator::GetInstance().TranslateJoystickString(iWin, joystickName.c_str(), wKeyID, isAxis ? JACTIVE_AXIS : JACTIVE_BUTTON, actionID, actionName, fullRange))
   {
     CAction action(actionID, fAmount, 0.0f, actionName);
     g_audioManager.PlayActionSound(action);
     return OnAction(action);
   }
   else
   {
     CLog::Log(LOGDEBUG, "ERROR mapping joystick action. Joystick: %s %i",joystickName.c_str(), wKeyID);
   }
#endif

   return false;
}

bool CApplication::ProcessKeyboard()
{
  MEASURE_FUNCTION;

  // Get the keypress from the keyboard
  const CKey key(g_Keyboard.GetKey());

  // If we have a valid keypress pass it to OnKey
  if (key.GetVKey() || key.GetUnicode())
  {
    g_Keyboard.Reset();
    return OnKey(key);
  }
  return false;
}

bool CApplication::Cleanup()
{
  try
  {
    g_windowManager.Delete(WINDOW_MUSIC_PLAYLIST);
    g_windowManager.Delete(WINDOW_MUSIC_PLAYLIST_EDITOR);
    g_windowManager.Delete(WINDOW_MUSIC_FILES);
    g_windowManager.Delete(WINDOW_MUSIC_NAV);
    g_windowManager.Delete(WINDOW_MUSIC_INFO);
    g_windowManager.Delete(WINDOW_VIDEO_INFO);
    g_windowManager.Delete(WINDOW_VIDEO_FILES);
    g_windowManager.Delete(WINDOW_VIDEO_PLAYLIST);
    g_windowManager.Delete(WINDOW_VIDEO_NAV);
    g_windowManager.Delete(WINDOW_FILES);
    g_windowManager.Delete(WINDOW_MUSIC_INFO);
    g_windowManager.Delete(WINDOW_VIDEO_INFO);
    g_windowManager.Delete(WINDOW_DIALOG_YES_NO);
    g_windowManager.Delete(WINDOW_DIALOG_PROGRESS);
    g_windowManager.Delete(WINDOW_DIALOG_NUMERIC);
    g_windowManager.Delete(WINDOW_DIALOG_GAMEPAD);
    g_windowManager.Delete(WINDOW_DIALOG_SUB_MENU);
    g_windowManager.Delete(WINDOW_DIALOG_BUTTON_MENU);
    g_windowManager.Delete(WINDOW_DIALOG_CONTEXT_MENU);
    g_windowManager.Delete(WINDOW_DIALOG_MUSIC_SCAN);
    g_windowManager.Delete(WINDOW_DIALOG_PLAYER_CONTROLS);
    g_windowManager.Delete(WINDOW_DIALOG_KARAOKE_SONGSELECT);
    g_windowManager.Delete(WINDOW_DIALOG_KARAOKE_SELECTOR);
    g_windowManager.Delete(WINDOW_DIALOG_MUSIC_OSD);
    g_windowManager.Delete(WINDOW_DIALOG_VIS_PRESET_LIST);
    g_windowManager.Delete(WINDOW_DIALOG_SELECT);
    g_windowManager.Delete(WINDOW_DIALOG_OK);
    g_windowManager.Delete(WINDOW_DIALOG_FILESTACKING);
    g_windowManager.Delete(WINDOW_DIALOG_KEYBOARD);
    g_windowManager.Delete(WINDOW_FULLSCREEN_VIDEO);
    g_windowManager.Delete(WINDOW_DIALOG_PROFILE_SETTINGS);
    g_windowManager.Delete(WINDOW_DIALOG_LOCK_SETTINGS);
    g_windowManager.Delete(WINDOW_DIALOG_NETWORK_SETUP);
    g_windowManager.Delete(WINDOW_DIALOG_MEDIA_SOURCE);
    g_windowManager.Delete(WINDOW_DIALOG_VIDEO_OSD_SETTINGS);
    g_windowManager.Delete(WINDOW_DIALOG_AUDIO_OSD_SETTINGS);
    g_windowManager.Delete(WINDOW_DIALOG_VIDEO_BOOKMARKS);
    g_windowManager.Delete(WINDOW_DIALOG_VIDEO_SCAN);
    g_windowManager.Delete(WINDOW_DIALOG_CONTENT_SETTINGS);
    g_windowManager.Delete(WINDOW_DIALOG_FAVOURITES);
    g_windowManager.Delete(WINDOW_DIALOG_SONG_INFO);
    g_windowManager.Delete(WINDOW_DIALOG_SMART_PLAYLIST_EDITOR);
    g_windowManager.Delete(WINDOW_DIALOG_SMART_PLAYLIST_RULE);
    g_windowManager.Delete(WINDOW_DIALOG_BUSY);
    g_windowManager.Delete(WINDOW_DIALOG_PICTURE_INFO);
    g_windowManager.Delete(WINDOW_DIALOG_ADDON_INFO);
    g_windowManager.Delete(WINDOW_DIALOG_ADDON_SETTINGS);
    g_windowManager.Delete(WINDOW_DIALOG_ACCESS_POINTS);
    g_windowManager.Delete(WINDOW_DIALOG_SLIDER);

    g_windowManager.Delete(WINDOW_DIALOG_OSD_TELETEXT);
    g_windowManager.Delete(WINDOW_DIALOG_TEXT_VIEWER);

    g_windowManager.Delete(WINDOW_STARTUP_ANIM);
    g_windowManager.Delete(WINDOW_LOGIN_SCREEN);
    g_windowManager.Delete(WINDOW_VISUALISATION);
    g_windowManager.Delete(WINDOW_KARAOKELYRICS);
    g_windowManager.Delete(WINDOW_SETTINGS_MENU);
    g_windowManager.Delete(WINDOW_SETTINGS_PROFILES);
    g_windowManager.Delete(WINDOW_SETTINGS_MYPICTURES);  // all the settings categories
    g_windowManager.Delete(WINDOW_TEST_PATTERN);
    g_windowManager.Delete(WINDOW_SCREEN_CALIBRATION);
    g_windowManager.Delete(WINDOW_SYSTEM_INFORMATION);
    g_windowManager.Delete(WINDOW_SCREENSAVER);
    g_windowManager.Delete(WINDOW_OSD);
    g_windowManager.Delete(WINDOW_MUSIC_OVERLAY);
    g_windowManager.Delete(WINDOW_VIDEO_OVERLAY);
    g_windowManager.Delete(WINDOW_SLIDESHOW);

    g_windowManager.Delete(WINDOW_HOME);
    g_windowManager.Delete(WINDOW_PROGRAMS);
    g_windowManager.Delete(WINDOW_PICTURES);
    g_windowManager.Delete(WINDOW_WEATHER);

    g_windowManager.Delete(WINDOW_SETTINGS_MYPICTURES);
    g_windowManager.Remove(WINDOW_SETTINGS_MYPROGRAMS);
    g_windowManager.Remove(WINDOW_SETTINGS_MYWEATHER);
    g_windowManager.Remove(WINDOW_SETTINGS_MYMUSIC);
    g_windowManager.Remove(WINDOW_SETTINGS_SYSTEM);
    g_windowManager.Remove(WINDOW_SETTINGS_MYVIDEOS);
    g_windowManager.Remove(WINDOW_SETTINGS_NETWORK);
    g_windowManager.Remove(WINDOW_SETTINGS_APPEARANCE);
    g_windowManager.Remove(WINDOW_DIALOG_KAI_TOAST);

    g_windowManager.Remove(WINDOW_DIALOG_SEEK_BAR);
    g_windowManager.Remove(WINDOW_DIALOG_VOLUME_BAR);

    CAddonMgr::Get().DeInit();

    CLog::Log(LOGNOTICE, "unload sections");
    CSectionLoader::UnloadAll();

#ifdef HAS_PERFORMANCE_SAMPLE
    CLog::Log(LOGNOTICE, "performance statistics");
    m_perfStats.DumpStats();
#endif

    //  Shutdown as much as possible of the
    //  application, to reduce the leaks dumped
    //  to the vc output window before calling
    //  _CrtDumpMemoryLeaks(). Most of the leaks
    //  shown are no real leaks, as parts of the app
    //  are still allocated.

    g_localizeStrings.Clear();
    g_LangCodeExpander.Clear();
    g_charsetConverter.clear();
    g_directoryCache.Clear();
    CButtonTranslator::GetInstance().Clear();
    CLastfmScrobbler::RemoveInstance();
    CLibrefmScrobbler::RemoveInstance();
    CLastFmManager::RemoveInstance();
#ifdef HAS_EVENT_SERVER
    CEventServer::RemoveInstance();
#endif
#ifdef HAS_DBUS_SERVER
    CDbusServer::RemoveInstance();
#endif
    DllLoaderContainer::Clear();
    g_playlistPlayer.Clear();
    g_settings.Clear();
    g_guiSettings.Clear();
    g_advancedSettings.Clear();

#ifdef _LINUX
    CXHandle::DumpObjectTracker();
#endif

#ifdef _CRTDBG_MAP_ALLOC
    _CrtDumpMemoryLeaks();
    while(1); // execution ends
#endif
#ifdef _WIN32
    WSACleanup();

    //Uninitialize COM
    CoUninitialize();
#endif
    return true;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Exception in CApplication::Cleanup()");
    return false;
  }
}

void CApplication::Stop()
{
  try
  {
    CAnnouncementManager::Announce(System, "xbmc", "ApplicationStop");

    // cancel any jobs from the jobmanager
    CJobManager::GetInstance().CancelJobs();

    g_alarmClock.StopThread();

#ifdef HAS_HTTPAPI
    if (m_pXbmcHttp)
    {
      if (g_settings.m_HttpApiBroadcastLevel >= 1)
        getApplicationMessenger().HttpApi("broadcastlevel; ShutDown;1");

      m_pXbmcHttp->shuttingDown = true;
    }
#endif

    if( m_bSystemScreenSaverEnable )
      g_Windowing.EnableSystemScreenSaver(true);

    CLog::Log(LOGNOTICE, "Storing total System Uptime");
    g_settings.m_iSystemTimeTotalUp = g_settings.m_iSystemTimeTotalUp + (int)(CTimeUtils::GetFrameTime() / 60000);

    // Update the settings information (volume, uptime etc. need saving)
    if (CFile::Exists(g_settings.GetSettingsFile()))
    {
      CLog::Log(LOGNOTICE, "Saving settings");
      g_settings.Save();
    }
    else
      CLog::Log(LOGNOTICE, "Not saving settings (settings.xml is not present)");

    m_bStop = true;
    CLog::Log(LOGNOTICE, "stop all");

    // stop scanning before we kill the network and so on
    CGUIDialogMusicScan *musicScan = (CGUIDialogMusicScan *)g_windowManager.GetWindow(WINDOW_DIALOG_MUSIC_SCAN);
    if (musicScan)
      musicScan->StopScanning();

    CGUIDialogVideoScan *videoScan = (CGUIDialogVideoScan *)g_windowManager.GetWindow(WINDOW_DIALOG_VIDEO_SCAN);
    if (videoScan)
      videoScan->StopScanning();

    m_applicationMessenger.Cleanup();

    StopServices();
    //Sleep(5000);

#ifdef __APPLE__
    XBMCHelper::GetInstance().ReleaseAllInput();
#endif

    if (m_pPlayer)
    {
      CLog::Log(LOGNOTICE, "stop player");
      delete m_pPlayer;
      m_pPlayer = NULL;
    }

#if HAS_FILESYTEM_DAAP
    CLog::Log(LOGNOTICE, "stop daap clients");
    g_DaapClient.Release();
#endif
#ifdef HAS_FILESYSTEM_SAP
    CLog::Log(LOGNOTICE, "stop sap announcement listener");
    g_sapsessions.StopThread();
#endif
#ifdef HAS_ZEROCONF
    if(CZeroconfBrowser::IsInstantiated())
    {
      CLog::Log(LOGNOTICE, "stop zeroconf browser");
      CZeroconfBrowser::GetInstance()->Stop();
      CZeroconfBrowser::ReleaseInstance();
    }
#endif

    CLog::Log(LOGNOTICE, "clean cached files!");
#ifdef HAS_FILESYSTEM_RAR
    g_RarManager.ClearCache(true);
#endif

#ifdef HAS_FILESYSTEM_SFTP
    CSFTPSessionManager::DisconnectAllSessions();
#endif

    CLog::Log(LOGNOTICE, "unload skin");
    UnloadSkin();

#ifdef __APPLE__
    if (XBMCHelper::GetInstance().IsAlwaysOn() == false)
      XBMCHelper::GetInstance().Stop();
#endif

#if defined(HAVE_LIBCRYSTALHD)
    CCrystalHD::RemoveInstance();
#endif

  g_mediaManager.Stop();

  // Stop services before unloading Python
  CAddonMgr::Get().StopServices();

/* Python resource freeing must be done after skin has been unloaded, not before
   some windows still need it when deinitializing during skin unloading. */
#ifdef HAS_PYTHON
  CLog::Log(LOGNOTICE, "stop python");
  g_pythonParser.FreeResources();
#endif
#ifdef HAS_LCD
    if (g_lcd)
    {
      g_lcd->Stop();
      delete g_lcd;
      g_lcd=NULL;
    }
#endif

    g_Windowing.DestroyRenderSystem();
    g_Windowing.DestroyWindowSystem();

    CLog::Log(LOGNOTICE, "stopped");
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Exception in CApplication::Stop()");
  }

  // we may not get to finish the run cycle but exit immediately after a call to g_application.Stop()
  // so we may never get to Destroy() in CXBApplicationEx::Run(), we call it here.
  Destroy();
}

bool CApplication::PlayMedia(const CFileItem& item, int iPlaylist)
{
  if (item.IsLastFM())
  {
    g_partyModeManager.Disable();
    return CLastFmManager::GetInstance()->ChangeStation(item.GetAsUrl());
  }
  if (item.IsSmartPlayList())
  {
    CDirectory dir;
    CFileItemList items;
    if (dir.GetDirectory(item.m_strPath, items) && items.Size())
    {
      CSmartPlaylist smartpl;
      //get name and type of smartplaylist, this will always succeed as GetDirectory also did this.
      smartpl.OpenAndReadName(item.m_strPath);
      CPlayList playlist;
      playlist.Add(items);
      return ProcessAndStartPlaylist(smartpl.GetName(), playlist, (smartpl.GetType() == "songs" || smartpl.GetType() == "albums") ? PLAYLIST_MUSIC:PLAYLIST_VIDEO);
    }
  }
  else if (item.IsPlayList() || item.IsInternetStream())
  {
    CDlgCache* dlgCache = new CDlgCache(5000, g_localizeStrings.Get(10214), item.GetLabel());

    //is or could be a playlist
    auto_ptr<CPlayList> pPlayList (CPlayListFactory::Create(item));
    bool gotPlayList = (pPlayList.get() && pPlayList->Load(item.m_strPath));

    if (dlgCache)
    {
       dlgCache->Close();
       if (dlgCache->IsCanceled())
          return true;
    }

    if (gotPlayList)
    {

      if (iPlaylist != PLAYLIST_NONE)
        return ProcessAndStartPlaylist(item.m_strPath, *pPlayList, iPlaylist);
      else
      {
        CLog::Log(LOGWARNING, "CApplication::PlayMedia called to play a playlist %s but no idea which playlist to use, playing first item", item.m_strPath.c_str());
        if(pPlayList->size())
          return PlayFile(*(*pPlayList)[0], false);
      }
    }
  }

  //nothing special just play
  return PlayFile(item, false);
}

// PlayStack()
// For playing a multi-file video.  Particularly inefficient
// on startup, as we are required to calculate the length
// of each video, so we open + close each one in turn.
// A faster calculation of video time would improve this
// substantially.
bool CApplication::PlayStack(const CFileItem& item, bool bRestart)
{
  if (!item.IsStack())
    return false;

  // see if we have the info in the database
  // TODO: If user changes the time speed (FPS via framerate conversion stuff)
  //       then these times will be wrong.
  //       Also, this is really just a hack for the slow load up times we have
  //       A much better solution is a fast reader of FPS and fileLength
  //       that we can use on a file to get it's time.
  vector<int> times;
  bool haveTimes(false);
  CVideoDatabase dbs;
  if (dbs.Open())
  {
    dbs.GetVideoSettings(item.m_strPath, g_settings.m_currentVideoSettings);
    haveTimes = dbs.GetStackTimes(item.m_strPath, times);
    dbs.Close();
  }


  // calculate the total time of the stack
  CStackDirectory dir;
  dir.GetDirectory(item.m_strPath, *m_currentStack);
  long totalTime = 0;
  for (int i = 0; i < m_currentStack->Size(); i++)
  {
    if (haveTimes)
      (*m_currentStack)[i]->m_lEndOffset = times[i];
    else
    {
      int duration;
      if (!CDVDFileInfo::GetFileDuration((*m_currentStack)[i]->m_strPath, duration))
      {
        m_currentStack->Clear();
        return false;
      }
      totalTime += duration / 1000;
      (*m_currentStack)[i]->m_lEndOffset = totalTime;
      times.push_back(totalTime);
    }
  }

  double seconds = item.m_lStartOffset / 75.0;

  if (!haveTimes || item.m_lStartOffset == STARTOFFSET_RESUME )
  {  // have our times now, so update the dB
    if (dbs.Open())
    {
      if( !haveTimes )
        dbs.SetStackTimes(item.m_strPath, times);

      if( item.m_lStartOffset == STARTOFFSET_RESUME )
      {
        // can only resume seek here, not dvdstate
        CBookmark bookmark;
        if( dbs.GetResumeBookMark(item.m_strPath, bookmark) )
          seconds = bookmark.timeInSeconds;
        else
          seconds = 0.0f;
      }
      dbs.Close();
    }
  }

  *m_itemCurrentFile = item;
  m_currentStackPosition = 0;
  m_eCurrentPlayer = EPC_NONE; // must be reset on initial play otherwise last player will be used

  if (seconds > 0)
  {
    // work out where to seek to
    for (int i = 0; i < m_currentStack->Size(); i++)
    {
      if (seconds < (*m_currentStack)[i]->m_lEndOffset)
      {
        CFileItem item(*(*m_currentStack)[i]);
        long start = (i > 0) ? (*m_currentStack)[i-1]->m_lEndOffset : 0;
        item.m_lStartOffset = (long)(seconds - start) * 75;
        m_currentStackPosition = i;
        return PlayFile(item, true);
      }
    }
  }

  return PlayFile(*(*m_currentStack)[0], true);
}

bool CApplication::PlayFile(const CFileItem& item, bool bRestart)
{
  if (!bRestart)
  {
    SaveCurrentFileSettings();

    OutputDebugString("new file set audiostream:0\n");
    // Switch to default options
    g_settings.m_currentVideoSettings = g_settings.m_defaultVideoSettings;
    // see if we have saved options in the database

    m_iPlaySpeed = 1;
    *m_itemCurrentFile = item;
    m_nextPlaylistItem = -1;
    m_currentStackPosition = 0;
    m_currentStack->Clear();

    if (item.IsVideo())
      CUtil::ClearSubtitles();
  }

  if (item.IsPlayList())
    return false;

  if (item.IsPlugin())
  { // we modify the item so that it becomes a real URL
    CFileItem item_new(item);
    if (XFILE::CPluginDirectory::GetPluginResult(item.m_strPath, item_new))
      return PlayFile(item_new, false);
    return false;
  }

  if (CUtil::IsUPnP(item.m_strPath))
  {
    CFileItem item_new(item);
    if (XFILE::CUPnPDirectory::GetResource(item.m_strPath, item_new))
      return PlayFile(item_new, false);
    return false;
  }

  // if we have a stacked set of files, we need to setup our stack routines for
  // "seamless" seeking and total time of the movie etc.
  // will recall with restart set to true
  if (item.IsStack())
    return PlayStack(item, bRestart);

  //Is TuxBox, this should probably be moved to CFileTuxBox
  if(item.IsTuxBox())
  {
    CLog::Log(LOGDEBUG, "%s - TuxBox URL Detected %s",__FUNCTION__, item.m_strPath.c_str());

    if(g_tuxboxService.IsRunning())
      g_tuxboxService.Stop();

    CFileItem item_new;
    if(g_tuxbox.CreateNewItem(item, item_new))
    {

      // Make sure it doesn't have a player
      // so we actually select one normally
      m_eCurrentPlayer = EPC_NONE;

      // keep the tuxbox:// url as playing url
      // and give the new url to the player
      if(PlayFile(item_new, true))
      {
        if(!g_tuxboxService.IsRunning())
          g_tuxboxService.Start();
        return true;
      }
    }
    return false;
  }

  CPlayerOptions options;
  PLAYERCOREID eNewCore = EPC_NONE;
  if( bRestart )
  {
    // have to be set here due to playstack using this for starting the file
    options.starttime = item.m_lStartOffset / 75.0;
    if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0 && m_itemCurrentFile->m_lStartOffset != 0)
      m_itemCurrentFile->m_lStartOffset = STARTOFFSET_RESUME; // to force fullscreen switching

    if( m_eForcedNextPlayer != EPC_NONE )
      eNewCore = m_eForcedNextPlayer;
    else if( m_eCurrentPlayer == EPC_NONE )
      eNewCore = CPlayerCoreFactory::GetDefaultPlayer(item);
    else
      eNewCore = m_eCurrentPlayer;
  }
  else
  {
    options.starttime = item.m_lStartOffset / 75.0;

    if (item.IsVideo())
    {
      // open the d/b and retrieve the bookmarks for the current movie
      CVideoDatabase dbs;
      dbs.Open();
      dbs.GetVideoSettings(item.m_strPath, g_settings.m_currentVideoSettings);

      if( item.m_lStartOffset == STARTOFFSET_RESUME )
      {
        options.starttime = 0.0f;
        CBookmark bookmark;
        if(dbs.GetResumeBookMark(item.m_strPath, bookmark))
        {
          options.starttime = bookmark.timeInSeconds;
          options.state = bookmark.playerState;
        }
      }
      else if (item.HasVideoInfoTag())
      {
        const CVideoInfoTag *tag = item.GetVideoInfoTag();

        if (tag->m_iBookmarkId != -1 && tag->m_iBookmarkId != 0)
        {
          CBookmark bookmark;
          dbs.GetBookMarkForEpisode(*tag, bookmark);
          options.starttime = bookmark.timeInSeconds;
          options.state = bookmark.playerState;
        }
      }

      dbs.Close();
    }

    if (m_eForcedNextPlayer != EPC_NONE)
      eNewCore = m_eForcedNextPlayer;
    else
      eNewCore = CPlayerCoreFactory::GetDefaultPlayer(item);
  }

  // this really aught to be inside !bRestart, but since PlayStack
  // uses that to init playback, we have to keep it outside
  int playlist = g_playlistPlayer.GetCurrentPlaylist();
  if (playlist == PLAYLIST_VIDEO && g_playlistPlayer.GetPlaylist(playlist).size() > 1)
  { // playing from a playlist by the looks
    // don't switch to fullscreen if we are not playing the first item...
    options.fullscreen = !g_playlistPlayer.HasPlayedFirstFile() && g_advancedSettings.m_fullScreenOnMovieStart && !g_settings.m_bStartVideoWindowed;
  }
  else if(m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0)
  {
    // TODO - this will fail if user seeks back to first file in stack
    if(m_currentStackPosition == 0 || m_itemCurrentFile->m_lStartOffset == STARTOFFSET_RESUME)
      options.fullscreen = g_advancedSettings.m_fullScreenOnMovieStart && !g_settings.m_bStartVideoWindowed;
    else
      options.fullscreen = false;
    // reset this so we don't think we are resuming on seek
    m_itemCurrentFile->m_lStartOffset = 0;
  }
  else
    options.fullscreen = g_advancedSettings.m_fullScreenOnMovieStart && !g_settings.m_bStartVideoWindowed;

  // reset m_bStartVideoWindowed as it's a temp setting
  g_settings.m_bStartVideoWindowed = false;
  // reset any forced player
  m_eForcedNextPlayer = EPC_NONE;

#ifdef HAS_KARAOKE
  //We have to stop parsing a cdg before mplayer is deallocated
  // WHY do we have to do this????
  if (m_pKaraokeMgr)
    m_pKaraokeMgr->Stop();
#endif

  // tell system we are starting a file
  m_bPlaybackStarting = true;

  // We should restart the player, unless the previous and next tracks are using
  // one of the players that allows gapless playback (paplayer, dvdplayer)
  if (m_pPlayer)
  {
    if ( !(m_eCurrentPlayer == eNewCore && (m_eCurrentPlayer == EPC_DVDPLAYER || m_eCurrentPlayer  == EPC_PAPLAYER)) )
    {
      delete m_pPlayer;
      m_pPlayer = NULL;
    }
  }

  if (!m_pPlayer)
  {
    m_eCurrentPlayer = eNewCore;
    m_pPlayer = CPlayerCoreFactory::CreatePlayer(eNewCore, *this);
  }

  // Workaround for bug/quirk in SDL_Mixer on OSX.
  // TODO: Remove after GUI Sounds redux
#if defined(__APPLE__)
  g_audioManager.Enable(false);
#endif

  bool bResult;
  if (m_pPlayer)
  {
    // don't hold graphicscontext here since player
    // may wait on another thread, that requires gfx
    CSingleExit ex(g_graphicsContext);
    bResult = m_pPlayer->OpenFile(item, options);
  }
  else
  {
    CLog::Log(LOGERROR, "Error creating player for item %s (File doesn't exist?)", item.m_strPath.c_str());
    bResult = false;
  }

  if(bResult)
  {
    if (m_iPlaySpeed != 1)
    {
      int iSpeed = m_iPlaySpeed;
      m_iPlaySpeed = 1;
      SetPlaySpeed(iSpeed);
    }

    if( IsPlayingAudio() )
    {
      if (g_windowManager.GetActiveWindow() == WINDOW_FULLSCREEN_VIDEO)
        g_windowManager.ActivateWindow(WINDOW_VISUALISATION);
    }

#ifdef HAS_VIDEO_PLAYBACK
    if( IsPlayingVideo() )
    {
      if (g_windowManager.GetActiveWindow() == WINDOW_VISUALISATION)
        g_windowManager.ActivateWindow(WINDOW_FULLSCREEN_VIDEO);

      // if player didn't manange to switch to fullscreen by itself do it here
      if( options.fullscreen && g_renderManager.IsStarted()
       && g_windowManager.GetActiveWindow() != WINDOW_FULLSCREEN_VIDEO )
       SwitchToFullScreen();

      if (!item.IsDVDImage() && !item.IsDVDFile())
      {
        CVideoInfoTag *details = m_itemCurrentFile->GetVideoInfoTag();
        // Save information about the stream if we currently have no data
        if (!details->HasStreamDetails() ||
             details->m_streamDetails.GetVideoDuration() <= 0)
        {
          if (m_pPlayer->GetStreamDetails(details->m_streamDetails) && details->HasStreamDetails())
          {
            CVideoDatabase dbs;
            dbs.Open();
            dbs.SetStreamDetailsForFileId(details->m_streamDetails, details->m_iFileId);
            dbs.Close();
            CUtil::DeleteVideoDatabaseDirectoryCache();
          }
        }
      }
    }
#endif

#if !defined(__APPLE__)
    g_audioManager.Enable(false);
#endif
  }
  m_bPlaybackStarting = false;
  if(bResult)
  {
    // we must have started, otherwise player might send this later
    if(IsPlaying())
      OnPlayBackStarted();
    else
      OnPlayBackEnded();
  }
  else
  {
    // we send this if it isn't playlistplayer that is doing this
    int next = g_playlistPlayer.GetNextSong();
    int size = g_playlistPlayer.GetPlaylist(g_playlistPlayer.GetCurrentPlaylist()).size();
    if(next < 0
    || next >= size)
      OnPlayBackStopped();
  }

  return bResult;
}

void CApplication::OnPlayBackEnded()
{
  if(m_bPlaybackStarting)
    return;

  // informs python script currently running playback has ended
  // (does nothing if python is not loaded)
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackEnded();
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
    getApplicationMessenger().HttpApi("broadcastlevel; OnPlayBackEnded;1");
#endif

  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackEnded");

  if (IsPlayingAudio())
  {
    CLastfmScrobbler::GetInstance()->SubmitQueue();
    CLibrefmScrobbler::GetInstance()->SubmitQueue();
  }

  CGUIMessage msg(GUI_MSG_PLAYBACK_ENDED, 0, 0);
  g_windowManager.SendThreadMessage(msg);
}

void CApplication::OnPlayBackStarted()
{
  if(m_bPlaybackStarting)
    return;

#ifdef HAS_PYTHON
  // informs python script currently running playback has started
  // (does nothing if python is not loaded)
  g_pythonParser.OnPlayBackStarted();
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
    getApplicationMessenger().HttpApi("broadcastlevel; OnPlayBackStarted;1");
#endif

  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackStarted", m_itemCurrentFile);

  CGUIMessage msg(GUI_MSG_PLAYBACK_STARTED, 0, 0);
  g_windowManager.SendThreadMessage(msg);
}

void CApplication::OnQueueNextItem()
{
  // informs python script currently running that we are requesting the next track
  // (does nothing if python is not loaded)
#ifdef HAS_PYTHON
  g_pythonParser.OnQueueNextItem(); // currently unimplemented
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
    getApplicationMessenger().HttpApi("broadcastlevel; OnQueueNextItem;1");
#endif

  CAnnouncementManager::Announce(Playback, "xbmc", "QueueNextItem");

  if(IsPlayingAudio())
  {
    CLastfmScrobbler::GetInstance()->SubmitQueue();
    CLibrefmScrobbler::GetInstance()->SubmitQueue();
  }

  CGUIMessage msg(GUI_MSG_QUEUE_NEXT_ITEM, 0, 0);
  g_windowManager.SendThreadMessage(msg);
}

void CApplication::OnPlayBackStopped()
{
  if(m_bPlaybackStarting)
    return;

  // informs python script currently running playback has ended
  // (does nothing if python is not loaded)
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackStopped();
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
    getApplicationMessenger().HttpApi("broadcastlevel; OnPlayBackStopped;1");
#endif

  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackStopped", m_itemCurrentFile);

  CLastfmScrobbler::GetInstance()->SubmitQueue();
  CLibrefmScrobbler::GetInstance()->SubmitQueue();

  CGUIMessage msg( GUI_MSG_PLAYBACK_STOPPED, 0, 0 );
  g_windowManager.SendThreadMessage(msg);
}

void CApplication::OnPlayBackPaused()
{
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackPaused();
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
    getApplicationMessenger().HttpApi("broadcastlevel; OnPlayBackPaused;1");
#endif

  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackPaused", m_itemCurrentFile);
}

void CApplication::OnPlayBackResumed()
{
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackResumed();
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
    getApplicationMessenger().HttpApi("broadcastlevel; OnPlayBackResumed;1");
#endif

  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackResumed", m_itemCurrentFile);
}

void CApplication::OnPlayBackSpeedChanged(int iSpeed)
{
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackSpeedChanged(iSpeed);
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
  {
    CStdString tmp;
    tmp.Format("broadcastlevel; OnPlayBackSpeedChanged:%i;1",iSpeed);
    getApplicationMessenger().HttpApi(tmp);
  }
#endif

  CVariant param;
  param["speed"] = iSpeed;
  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackSpeedChanged", m_itemCurrentFile, param);
}

void CApplication::OnPlayBackSeek(int iTime, int seekOffset)
{
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackSeek(iTime, seekOffset);
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
  {
    CStdString tmp;
    tmp.Format("broadcastlevel; OnPlayBackSeek:%i;1",iTime);
    getApplicationMessenger().HttpApi(tmp);
  }
#endif

  CVariant param;
  param["time"] = iTime;
  param["seekoffset"] = seekOffset;
  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackSeek", param);
  g_infoManager.SetDisplayAfterSeek(2500, seekOffset/1000);
}

void CApplication::OnPlayBackSeekChapter(int iChapter)
{
#ifdef HAS_PYTHON
  g_pythonParser.OnPlayBackSeekChapter(iChapter);
#endif

#ifdef HAS_HTTPAPI
  // Let's tell the outside world as well
  if (g_settings.m_HttpApiBroadcastLevel>=1)
  {
    CStdString tmp;
    tmp.Format("broadcastlevel; OnPlayBackSkeekChapter:%i;1",iChapter);
    getApplicationMessenger().HttpApi(tmp);
  }
#endif

  CVariant param;
  param["chapter"] = iChapter;
  CAnnouncementManager::Announce(Playback, "xbmc", "PlaybackSeekChapter", param);
}

bool CApplication::IsPlaying() const
{
  if (!m_pPlayer)
    return false;
  if (!m_pPlayer->IsPlaying())
    return false;
  return true;
}

bool CApplication::IsPaused() const
{
  if (!m_pPlayer)
    return false;
  if (!m_pPlayer->IsPlaying())
    return false;
  return m_pPlayer->IsPaused();
}

bool CApplication::IsPlayingAudio() const
{
  if (!m_pPlayer)
    return false;
  if (!m_pPlayer->IsPlaying())
    return false;
  if (m_pPlayer->HasVideo())
    return false;
  if (m_pPlayer->HasAudio())
    return true;
  return false;
}

bool CApplication::IsPlayingVideo() const
{
  if (!m_pPlayer)
    return false;
  if (!m_pPlayer->IsPlaying())
    return false;
  if (m_pPlayer->HasVideo())
    return true;

  return false;
}

bool CApplication::IsPlayingFullScreenVideo() const
{
  return IsPlayingVideo() && g_graphicsContext.IsFullScreenVideo();
}

void CApplication::SaveFileState()
{
  if (!g_settings.GetCurrentProfile().canWriteDatabases())
    return;
  CJob* job = new CSaveFileStateJob(*m_progressTrackingItem,
      m_progressTrackingVideoResumeBookmark,
      m_progressTrackingPlayCountUpdate);
  CJobManager::GetInstance().AddJob(job, NULL);
}

void CApplication::UpdateFileState()
{
  // Did the file change?
  if (m_progressTrackingItem->m_strPath != "" && m_progressTrackingItem->m_strPath != CurrentFile())
  {
    SaveFileState();

    // Reset tracking item
    m_progressTrackingItem->Reset();
  }
  else
  {
    if (IsPlayingVideo() || IsPlayingAudio())
    {
      if (m_progressTrackingItem->m_strPath == "")
      {
        // Init some stuff
        *m_progressTrackingItem = CurrentFileItem();
        m_progressTrackingPlayCountUpdate = false;
      }

      if ((m_progressTrackingItem->IsAudio() && g_advancedSettings.m_audioPlayCountMinimumPercent > 0 &&
          GetPercentage() >= g_advancedSettings.m_audioPlayCountMinimumPercent) ||
          (m_progressTrackingItem->IsVideo() && g_advancedSettings.m_videoPlayCountMinimumPercent > 0 &&
          GetPercentage() >= g_advancedSettings.m_videoPlayCountMinimumPercent))
      {
        m_progressTrackingPlayCountUpdate = true;
      }

      if (m_progressTrackingItem->IsVideo())
      {
        if ((m_progressTrackingItem->IsDVDImage() || m_progressTrackingItem->IsDVDFile()) && m_pPlayer->GetTotalTime() > 15*60)
        {
          m_progressTrackingItem->GetVideoInfoTag()->m_streamDetails.Reset();
          m_pPlayer->GetStreamDetails(m_progressTrackingItem->GetVideoInfoTag()->m_streamDetails);
        }
        // Update bookmark for save
        m_progressTrackingVideoResumeBookmark.player = CPlayerCoreFactory::GetPlayerName(m_eCurrentPlayer);
        m_progressTrackingVideoResumeBookmark.playerState = m_pPlayer->GetPlayerState();
        m_progressTrackingVideoResumeBookmark.thumbNailImage.Empty();

        if (g_advancedSettings.m_videoIgnorePercentAtEnd > 0 &&
            GetTotalTime() - GetTime() < 0.01f * g_advancedSettings.m_videoIgnorePercentAtEnd * GetTotalTime())
        {
          // Delete the bookmark
          m_progressTrackingVideoResumeBookmark.timeInSeconds = -1.0f;
        }
        else
        if (GetTime() > g_advancedSettings.m_videoIgnoreSecondsAtStart)
        {
          // Update the bookmark
          m_progressTrackingVideoResumeBookmark.timeInSeconds = GetTime();
          m_progressTrackingVideoResumeBookmark.totalTimeInSeconds = GetTotalTime();
        }
        else
        {
          // Do nothing
          m_progressTrackingVideoResumeBookmark.timeInSeconds = 0.0f;
        }
      }
    }
  }
}

void CApplication::StopPlaying()
{
  int iWin = g_windowManager.GetActiveWindow();
  if ( IsPlaying() )
  {
#ifdef HAS_KARAOKE
    if( m_pKaraokeMgr )
      m_pKaraokeMgr->Stop();
#endif

    if (m_pPlayer)
      m_pPlayer->CloseFile();

    // turn off visualisation window when stopping
    if (iWin == WINDOW_VISUALISATION
    ||  iWin == WINDOW_FULLSCREEN_VIDEO)
      g_windowManager.PreviousWindow();

    g_partyModeManager.Disable();
  }
}

void CApplication::ResetScreenSaver()
{
  // reset our timers
  m_shutdownTimer.StartZero();

  // screen saver timer is reset only if we're not already in screensaver or
  // DPMS mode
  if ((!m_bScreenSave && m_iScreenSaveLock == 0) && !m_dpmsIsActive)
    ResetScreenSaverTimer();
}

void CApplication::ResetScreenSaverTimer()
{
#ifdef __APPLE__
  Cocoa_UpdateSystemActivity();
#endif
  m_screenSaverTimer.StartZero();
}

bool CApplication::ToggleDPMS(bool manual)
{
  if (manual || (m_dpmsIsManual == manual))
  {
    if (m_dpmsIsActive)
    {
      m_dpmsIsActive = false;
      m_dpmsIsManual = false;
      return m_dpms->DisablePowerSaving();
    }
    else
    {
      if (m_dpms->EnablePowerSaving(m_dpms->GetSupportedModes()[0]))
      {
        m_dpmsIsActive = true;
        m_dpmsIsManual = manual;
        return true;
      }
    }
  }
  return false;
}

bool CApplication::WakeUpScreenSaverAndDPMS()
{

#ifdef HAS_LCD
    // turn on lcd backlight
    if (g_lcd && g_advancedSettings.m_lcdDimOnScreenSave)
      g_lcd->SetBackLight(1);
#endif

  // First reset DPMS, if active
  if (m_dpmsIsActive)
  {
    if (m_dpmsIsManual)
      return false;
    // TODO: if screensaver lock is specified but screensaver is not active
    // (DPMS came first), activate screensaver now.
    ToggleDPMS(false);
    ResetScreenSaverTimer();
    return !m_bScreenSave || WakeUpScreenSaver();
  }
  else
    return WakeUpScreenSaver();
}

bool CApplication::WakeUpScreenSaver()
{
  if (m_iScreenSaveLock == 2)
    return false;

  // if Screen saver is active
  if (m_bScreenSave && m_screenSaver)
  {
    if (m_iScreenSaveLock == 0)
      if (g_settings.GetMasterProfile().getLockMode() != LOCK_MODE_EVERYONE &&
          (g_settings.UsingLoginScreen() || g_guiSettings.GetBool("masterlock.startuplock")) &&
          g_settings.GetCurrentProfile().getLockMode() != LOCK_MODE_EVERYONE &&
          m_screenSaver->ID() != "screensaver.xbmc.builtin.dim" && m_screenSaver->ID() != "screensaver.xbmc.builtin.black" && m_screenSaver->ID() != "visualization")
      {
        m_iScreenSaveLock = 2;
        CGUIMessage msg(GUI_MSG_CHECK_LOCK,0,0);
        g_windowManager.GetWindow(WINDOW_SCREENSAVER)->OnMessage(msg);
      }
    if (m_iScreenSaveLock == -1)
    {
      m_iScreenSaveLock = 0;
      return true;
    }

    // disable screensaver
    m_bScreenSave = false;
    m_iScreenSaveLock = 0;
    ResetScreenSaverTimer();

    if (m_screenSaver->ID() == "visualization" || m_screenSaver->ID() == "screensaver.xbmc.builtin.slideshow")
    {
      // we can just continue as usual from vis mode
      return false;
    }
    else if (m_screenSaver->ID() == "screensaver.xbmc.builtin.dim" || m_screenSaver->ID() == "screensaver.xbmc.builtin.black")
      return true;
    else if (!m_screenSaver->ID().IsEmpty())
    { // we're in screensaver window
      if (g_windowManager.GetActiveWindow() == WINDOW_SCREENSAVER)
        g_windowManager.PreviousWindow();  // show the previous window
    }
    return true;
  }
  else
    return false;
}

void CApplication::CheckScreenSaverAndDPMS()
{
#if defined(_LINUX) && !defined(__APPLE__)
  if (!m_dpmsIsActive)
    g_Windowing.ResetX11Screensaver();
#endif

  bool maybeScreensaver =
      !m_dpmsIsActive && !m_bScreenSave
      && !g_guiSettings.GetString("screensaver.mode").IsEmpty();
  bool maybeDPMS =
      !m_dpmsIsActive && m_dpms->IsSupported()
      && g_guiSettings.GetInt("powermanagement.displaysoff") > 0;

  // Has the screen saver window become active?
  if (maybeScreensaver && g_windowManager.IsWindowActive(WINDOW_SCREENSAVER))
  {
    m_bScreenSave = true;
    maybeScreensaver = false;
  }

  if (!maybeScreensaver && !maybeDPMS) return;  // Nothing to do.

  // See if we need to reset timer.
  // * Are we playing a video and it is not paused?
  if ((IsPlayingVideo() && !m_pPlayer->IsPaused())
      // * Are we playing some music in fullscreen vis?
      || (IsPlayingAudio() && g_windowManager.GetActiveWindow() == WINDOW_VISUALISATION))
  {
    ResetScreenSaverTimer();
    return;
  }

  float elapsed = m_screenSaverTimer.GetElapsedSeconds();

  // DPMS has priority (it makes the screensaver not needed)
  if (maybeDPMS
      && elapsed > g_guiSettings.GetInt("powermanagement.displaysoff") * 60)
  {
    ToggleDPMS(false);
    WakeUpScreenSaver();
  }
  else if (maybeScreensaver
           && elapsed > g_guiSettings.GetInt("screensaver.time") * 60)
  {
    ActivateScreenSaver();
  }
}

// activate the screensaver.
// if forceType is true, we ignore the various conditions that can alter
// the type of screensaver displayed
void CApplication::ActivateScreenSaver(bool forceType /*= false */)
{
  m_bScreenSave = true;

  // Get Screensaver Mode
  m_screenSaver.reset();
  if (!CAddonMgr::Get().GetAddon(g_guiSettings.GetString("screensaver.mode"), m_screenSaver))
    m_screenSaver.reset(new CScreenSaver(""));

#ifdef HAS_LCD
  // turn off lcd backlight if requested
  if (g_lcd && g_advancedSettings.m_lcdDimOnScreenSave)
    g_lcd->SetBackLight(0);
#endif

  // disable screensaver lock from the login screen
  m_iScreenSaveLock = g_windowManager.GetActiveWindow() == WINDOW_LOGIN_SCREEN ? 1 : 0;
  if (!forceType)
  {
    // set to Dim in the case of a dialog on screen or playing video
    if (g_windowManager.HasModalDialog() || (IsPlayingVideo() && g_guiSettings.GetBool("screensaver.usedimonpause")))
    {
      if (!CAddonMgr::Get().GetAddon("screensaver.xbmc.builtin.dim", m_screenSaver))
        m_screenSaver.reset(new CScreenSaver(""));
    }
    // Check if we are Playing Audio and Vis instead Screensaver!
    else if (IsPlayingAudio() && g_guiSettings.GetBool("screensaver.usemusicvisinstead") && !g_guiSettings.GetString("musicplayer.visualisation").IsEmpty())
    { // activate the visualisation
      m_screenSaver.reset(new CScreenSaver("visualization"));
      g_windowManager.ActivateWindow(WINDOW_VISUALISATION);
      return;
    }
  }
  // Picture slideshow
  if (m_screenSaver->ID() == "screensaver.xbmc.builtin.slideshow")
  {
    // reset our codec info - don't want that on screen
    g_infoManager.SetShowCodec(false);
    CStdString type = m_screenSaver->GetSetting("type");
    CStdString path = m_screenSaver->GetSetting("path");
    if (type == "2" && path.IsEmpty())
      type = "0";
    if (type == "0")
      path = "special://profile/Thumbnails/Video/Fanart";
    if (type == "1")
      path = "special://profile/Thumbnails/Music/Fanart";
    m_applicationMessenger.PictureSlideShow(path, true, type != "2");
  }
  else if (m_screenSaver->ID() == "screensaver.xbmc.builtin.dim")
    return;
  else if (m_screenSaver->ID() == "screensaver.xbmc.builtin.black")
    return;
  else if (!m_screenSaver->ID().IsEmpty())
    g_windowManager.ActivateWindow(WINDOW_SCREENSAVER);
}

void CApplication::CheckShutdown()
{
  CGUIDialogMusicScan *pMusicScan = (CGUIDialogMusicScan *)g_windowManager.GetWindow(WINDOW_DIALOG_MUSIC_SCAN);
  CGUIDialogVideoScan *pVideoScan = (CGUIDialogVideoScan *)g_windowManager.GetWindow(WINDOW_DIALOG_VIDEO_SCAN);

  // first check if we should reset the timer
  bool resetTimer = false;
  if (IsPlaying()) // is something playing?
    resetTimer = true;

  if (pMusicScan && pMusicScan->IsScanning()) // music scanning?
    resetTimer = true;

  if (pVideoScan && pVideoScan->IsScanning()) // video scanning?
    resetTimer = true;

  if (g_windowManager.IsWindowActive(WINDOW_DIALOG_PROGRESS)) // progress dialog is onscreen
    resetTimer = true;

  if (resetTimer)
  {
    m_shutdownTimer.StartZero();
    return;
  }

  if ( m_shutdownTimer.GetElapsedSeconds() > g_guiSettings.GetInt("powermanagement.shutdowntime") * 60 )
  {
    // Since it is a sleep instead of a shutdown, let's set everything to reset when we wake up.
    m_shutdownTimer.Stop();

    // Sleep the box
    getApplicationMessenger().Shutdown();
  }
}

bool CApplication::OnMessage(CGUIMessage& message)
{
  switch ( message.GetMessage() )
  {
  case GUI_MSG_NOTIFY_ALL:
    {
      if (message.GetParam1()==GUI_MSG_REMOVED_MEDIA)
      {
        // Update general playlist: Remove DVD playlist items
        int nRemoved = g_playlistPlayer.RemoveDVDItems();
        if ( nRemoved > 0 )
        {
          CGUIMessage msg( GUI_MSG_PLAYLIST_CHANGED, 0, 0 );
          g_windowManager.SendMessage( msg );
        }
        // stop the file if it's on dvd (will set the resume point etc)
        if (m_itemCurrentFile->IsOnDVD())
          StopPlaying();
      }
    }
    break;

  case GUI_MSG_PLAYBACK_STARTED:
    {
      // Update our infoManager with the new details etc.
      if (m_nextPlaylistItem >= 0)
      { // we've started a previously queued item
        CFileItemPtr item = g_playlistPlayer.GetPlaylist(g_playlistPlayer.GetCurrentPlaylist())[m_nextPlaylistItem];
        // update the playlist manager
        int currentSong = g_playlistPlayer.GetCurrentSong();
        int param = ((currentSong & 0xffff) << 16) | (m_nextPlaylistItem & 0xffff);
        CGUIMessage msg(GUI_MSG_PLAYLISTPLAYER_CHANGED, 0, 0, g_playlistPlayer.GetCurrentPlaylist(), param, item);
        g_windowManager.SendThreadMessage(msg);
        g_playlistPlayer.SetCurrentSong(m_nextPlaylistItem);
        *m_itemCurrentFile = *item;
      }
      g_infoManager.SetCurrentItem(*m_itemCurrentFile);
      CLastFmManager::GetInstance()->OnSongChange(*m_itemCurrentFile);
      g_partyModeManager.OnSongChange(true);

      DimLCDOnPlayback(true);

      if (IsPlayingAudio())
      {
        // Start our cdg parser as appropriate
#ifdef HAS_KARAOKE
        if (m_pKaraokeMgr && g_guiSettings.GetBool("karaoke.enabled") && !m_itemCurrentFile->IsInternetStream())
        {
          m_pKaraokeMgr->Stop();
          if (m_itemCurrentFile->IsMusicDb())
          {
            if (!m_itemCurrentFile->HasMusicInfoTag() || !m_itemCurrentFile->GetMusicInfoTag()->Loaded())
            {
              IMusicInfoTagLoader* tagloader = CMusicInfoTagLoaderFactory::CreateLoader(m_itemCurrentFile->m_strPath);
              tagloader->Load(m_itemCurrentFile->m_strPath,*m_itemCurrentFile->GetMusicInfoTag());
              delete tagloader;
            }
            m_pKaraokeMgr->Start(m_itemCurrentFile->GetMusicInfoTag()->GetURL());
          }
          else
            m_pKaraokeMgr->Start(m_itemCurrentFile->m_strPath);
        }
#endif
        // Let scrobbler know about the track
        const CMusicInfoTag* tag=g_infoManager.GetCurrentSongTag();
        if (tag)
        {
          CLastfmScrobbler::GetInstance()->AddSong(*tag, CLastFmManager::GetInstance()->IsRadioEnabled());
          CLibrefmScrobbler::GetInstance()->AddSong(*tag, CLastFmManager::GetInstance()->IsRadioEnabled());
        }
      }

      return true;
    }
    break;

  case GUI_MSG_QUEUE_NEXT_ITEM:
    {
      // Check to see if our playlist player has a new item for us,
      // and if so, we check whether our current player wants the file
      int iNext = g_playlistPlayer.GetNextSong();
      CPlayList& playlist = g_playlistPlayer.GetPlaylist(g_playlistPlayer.GetCurrentPlaylist());
      if (iNext < 0 || iNext >= playlist.size())
      {
        if (m_pPlayer) m_pPlayer->OnNothingToQueueNotify();
        return true; // nothing to do
      }
      // ok, grab the next song
      CFileItemPtr item = playlist[iNext];
      // ok - send the file to the player if it wants it
      if (m_pPlayer && m_pPlayer->QueueNextFile(*item))
      { // player wants the next file
        m_nextPlaylistItem = iNext;
      }
      return true;
    }
    break;

  case GUI_MSG_PLAYBACK_STOPPED:
  case GUI_MSG_PLAYBACK_ENDED:
  case GUI_MSG_PLAYLISTPLAYER_STOPPED:
    {
#ifdef HAS_KARAOKE
      if (m_pKaraokeMgr )
        m_pKaraokeMgr->Stop();
#endif

      // first check if we still have items in the stack to play
      if (message.GetMessage() == GUI_MSG_PLAYBACK_ENDED)
      {
        if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0 && m_currentStackPosition < m_currentStack->Size() - 1)
        { // just play the next item in the stack
          PlayFile(*(*m_currentStack)[++m_currentStackPosition], true);
          return true;
        }
      }
      
      // In case playback ended due to user eg. skipping over the end, clear
      // our resume bookmark here
      if (message.GetMessage() == GUI_MSG_PLAYBACK_ENDED && m_progressTrackingPlayCountUpdate && g_advancedSettings.m_videoIgnorePercentAtEnd > 0)
      {
        // Delete the bookmark
        m_progressTrackingVideoResumeBookmark.timeInSeconds = -1.0f;
      }

      // reset the current playing file
      m_itemCurrentFile->Reset();
      g_infoManager.ResetCurrentItem();
      m_currentStack->Clear();

      if (message.GetMessage() == GUI_MSG_PLAYBACK_ENDED)
      {
        // sending true to PlayNext() effectively passes bRestart to PlayFile()
        // which is not generally what we want (except for stacks, which are
        // handled above)
        g_playlistPlayer.PlayNext();
      }
      else
      {
        // stop lastfm
        if (CLastFmManager::GetInstance()->IsRadioEnabled())
          CLastFmManager::GetInstance()->StopRadio();

        delete m_pPlayer;
        m_pPlayer = 0;
      }

      if (!IsPlaying())
      {
        g_audioManager.Enable(true);
        DimLCDOnPlayback(false);
      }

      if (!IsPlayingVideo() && g_windowManager.GetActiveWindow() == WINDOW_FULLSCREEN_VIDEO)
      {
        g_windowManager.PreviousWindow();
      }

      if (!IsPlayingAudio() && g_playlistPlayer.GetCurrentPlaylist() == PLAYLIST_NONE && g_windowManager.GetActiveWindow() == WINDOW_VISUALISATION)
      {
        g_settings.Save();  // save vis settings
        WakeUpScreenSaverAndDPMS();
        g_windowManager.PreviousWindow();
      }

      // DVD ejected while playing in vis ?
      if (!IsPlayingAudio() && (m_itemCurrentFile->IsCDDA() || m_itemCurrentFile->IsOnDVD()) && !g_mediaManager.IsDiscInDrive() && g_windowManager.GetActiveWindow() == WINDOW_VISUALISATION)
      {
        // yes, disable vis
        g_settings.Save();    // save vis settings
        WakeUpScreenSaverAndDPMS();
        g_windowManager.PreviousWindow();
      }

      if (IsEnableTestMode()) g_application.getApplicationMessenger().Quit();
      return true;
    }
    break;

  case GUI_MSG_PLAYLISTPLAYER_STARTED:
  case GUI_MSG_PLAYLISTPLAYER_CHANGED:
    {
      return true;
    }
    break;
  case GUI_MSG_FULLSCREEN:
    { // Switch to fullscreen, if we can
      SwitchToFullScreen();
      return true;
    }
    break;
  case GUI_MSG_EXECUTE:
    if (message.GetNumStringParams())
      return ExecuteXBMCAction(message.GetStringParam());
    else
    {
      CGUIActionDescriptor action = message.GetAction();
      action.m_sourceWindowId = message.GetControlId(); // set source window id,
      return ExecuteAction(action);
    }

    break;
  }
  return false;
}

bool CApplication::ExecuteXBMCAction(std::string actionStr)
    {
      // see if it is a user set string
      CLog::Log(LOGDEBUG,"%s : Translating %s", __FUNCTION__, actionStr.c_str());
      CGUIInfoLabel info(actionStr, "");
      actionStr = info.GetLabel(0);
      CLog::Log(LOGDEBUG,"%s : To %s", __FUNCTION__, actionStr.c_str());

      // user has asked for something to be executed
      if (CBuiltins::HasCommand(actionStr))
        CBuiltins::Execute(actionStr);
      else
      {
        // try translating the action from our ButtonTranslator
        int actionID;
        if (CButtonTranslator::TranslateActionString(actionStr.c_str(), actionID))
        {
          OnAction(CAction(actionID));
          return true;
        }
        CFileItem item(actionStr, false);
#ifdef HAS_PYTHON
        if (item.IsPythonScript())
        { // a python script
          g_pythonParser.evalFile(item.m_strPath.c_str());
        }
        else
#endif
        if (item.IsAudio() || item.IsVideo())
        { // an audio or video file
          PlayFile(item);
        }
        else
          return false;
      }
      return true;
    }

bool CApplication::ExecuteAction(CGUIActionDescriptor action)
{
  if (action.m_lang == CGUIActionDescriptor::LANG_XBMC)
  {
    return ExecuteXBMCAction(action.m_action);
  }
  else if (action.m_lang == CGUIActionDescriptor::LANG_PYTHON)
  {
#ifdef HAS_PYTHON
    // Determine the context of the action, if possible
    vector<CStdString> argv;
    g_pythonParser.evalString(action.m_action, argv);
    return true;
#else
    return false;
#endif
  }
  return false;
}

void CApplication::Process()
{
  MEASURE_FUNCTION;

  // dispatch the messages generated by python or other threads to the current window
  g_windowManager.DispatchThreadMessages();

  // process messages which have to be send to the gui
  // (this can only be done after g_windowManager.Render())
  m_applicationMessenger.ProcessWindowMessages();

#ifdef HAS_PYTHON
  // process any Python scripts
  g_pythonParser.Process();
#endif

  // process messages, even if a movie is playing
  m_applicationMessenger.ProcessMessages();
  if (g_application.m_bStop) return; //we're done, everything has been unloaded

  // check if we can free unused memory
#ifndef _LINUX
  g_audioManager.FreeUnused();
#endif

  // check how far we are through playing the current item
  // and do anything that needs doing (lastfm submission, playcount updates etc)
  CheckPlayingProgress();

  // update sound
  if (m_pPlayer)
    m_pPlayer->DoAudioWork();

  // do any processing that isn't needed on each run
  if( m_slowTimer.GetElapsedMilliseconds() > 500 )
  {
    m_slowTimer.Reset();
    ProcessSlow();
  }
}

// We get called every 500ms
void CApplication::ProcessSlow()
{
  g_powerManager.ProcessEvents();

#if defined(__APPLE__)
  // There is an issue on OS X that several system services ask the cursor to become visible
  // during their startup routines.  Given that we can't control this, we hack it in by
  // forcing the
  if (g_Windowing.IsFullScreen())
  { // SDL thinks it's hidden
    Cocoa_HideMouse();
  }
#endif

  // Store our file state for use on close()
  UpdateFileState();

  if (IsPlayingAudio())
  {
    CLastfmScrobbler::GetInstance()->UpdateStatus();
    CLibrefmScrobbler::GetInstance()->UpdateStatus();
  }

  // Check if we need to activate the screensaver / DPMS.
  CheckScreenSaverAndDPMS();

  // Check if we need to shutdown (if enabled).
#ifdef __APPLE__
  if (g_guiSettings.GetInt("powermanagement.shutdowntime") && g_advancedSettings.m_fullScreen)
#else
  if (g_guiSettings.GetInt("powermanagement.shutdowntime"))
#endif
  {
    CheckShutdown();
  }

  // check if we should restart the player
  CheckDelayedPlayerRestart();

  //  check if we can unload any unreferenced dlls or sections
  if (!IsPlayingVideo())
    CSectionLoader::UnloadDelayed();

  // check for any idle curl connections
  g_curlInterface.CheckIdle();

  // check for any idle myth sessions
  CMythSession::CheckIdle();

#ifdef HAS_FILESYSTEM_HTSP
  // check for any idle htsp sessions
  HTSP::CHTSPDirectorySession::CheckIdle();
#endif

#ifdef HAS_KARAOKE
  if ( m_pKaraokeMgr )
    m_pKaraokeMgr->ProcessSlow();
#endif

  // LED - LCD SwitchOn On Paused! m_bIsPaused=TRUE -> LED/LCD is ON!
  if(IsPaused() != m_bIsPaused)
  {
#ifdef HAS_LCD
    DimLCDOnPlayback(m_bIsPaused);
#endif
    m_bIsPaused = IsPaused();
  }

  if (!IsPlayingVideo())
    g_largeTextureManager.CleanupUnusedImages();

#ifdef HAS_DVD_DRIVE
  // checks whats in the DVD drive and tries to autostart the content (xbox games, dvd, cdda, avi files...)
  if (!IsPlayingVideo())
    m_Autorun.HandleAutorun();
#endif

  // update upnp server/renderer states
  if(CUPnP::IsInstantiated())
    CUPnP::GetInstance()->UpdateState();

  //Check to see if current playing Title has changed and whether we should broadcast the fact
  CheckForTitleChange();

#if defined(_LINUX) && defined(HAS_FILESYSTEM_SMB)
  smb.CheckIfIdle();
#endif

#ifdef HAS_FILESYSTEM_SFTP
  CSFTPSessionManager::ClearOutIdleSessions();
#endif

  g_mediaManager.ProcessEvents();

#ifdef HAS_LIRC
  if (g_RemoteControl.IsInUse() && !g_RemoteControl.IsInitialized())
    g_RemoteControl.Initialize();
#endif

#ifdef HAS_LCD
  // attempt to reinitialize the LCD (e.g. after resuming from sleep)
  if (!IsPlayingVideo())
  {
    if (g_lcd && !g_lcd->IsConnected())
    {
      g_lcd->Stop();
      g_lcd->Initialize();
    }
  }
#endif
  
  if (!IsPlayingVideo())
    ADDON::CAddonMgr::Get().UpdateRepos();
}

// Global Idle Time in Seconds
// idle time will be resetet if on any OnKey()
// int return: system Idle time in seconds! 0 is no idle!
int CApplication::GlobalIdleTime()
{
  if(!m_idleTimer.IsRunning())
  {
    m_idleTimer.Stop();
    m_idleTimer.StartZero();
  }
  return (int)m_idleTimer.GetElapsedSeconds();
}

float CApplication::NavigationIdleTime()
{
  if (!m_navigationTimer.IsRunning())
  {
    m_navigationTimer.Stop();
    m_navigationTimer.StartZero();
  }
  return m_navigationTimer.GetElapsedSeconds();
}

void CApplication::DelayedPlayerRestart()
{
  m_restartPlayerTimer.StartZero();
}

void CApplication::CheckDelayedPlayerRestart()
{
  if (m_restartPlayerTimer.GetElapsedSeconds() > 3)
  {
    m_restartPlayerTimer.Stop();
    m_restartPlayerTimer.Reset();
    Restart(true);
  }
}

void CApplication::Restart(bool bSamePosition)
{
  // this function gets called when the user changes a setting (like noninterleaved)
  // and which means we gotta close & reopen the current playing file

  // first check if we're playing a file
  if ( !IsPlayingVideo() && !IsPlayingAudio())
    return ;

  if( !m_pPlayer )
    return ;

  SaveFileState();

  // do we want to return to the current position in the file
  if (false == bSamePosition)
  {
    // no, then just reopen the file and start at the beginning
    PlayFile(*m_itemCurrentFile, true);
    return ;
  }

  // else get current position
  double time = GetTime();

  // get player state, needed for dvd's
  CStdString state = m_pPlayer->GetPlayerState();

  // set the requested starttime
  m_itemCurrentFile->m_lStartOffset = (long)(time * 75.0);

  // reopen the file
  if ( PlayFile(*m_itemCurrentFile, true) && m_pPlayer )
    m_pPlayer->SetPlayerState(state);
}

const CStdString& CApplication::CurrentFile()
{
  return m_itemCurrentFile->m_strPath;
}

CFileItem& CApplication::CurrentFileItem()
{
  return *m_itemCurrentFile;
}

void CApplication::Mute(void)
{
  if (g_settings.m_bMute)
  { // muted - unmute.
    // In case our premutevolume is 0, return to 100% volume
    if( g_settings.m_iPreMuteVolumeLevel == 0 )
    {
      SetVolume(100);
    }
    else
    {
      SetVolume(g_settings.m_iPreMuteVolumeLevel);
      g_settings.m_iPreMuteVolumeLevel = 0;
    }
    m_guiDialogVolumeBar.Show();
  }
  else
  { // mute
    g_settings.m_iPreMuteVolumeLevel = GetVolume();
    SetVolume(0);
  }
}

void CApplication::SetVolume(int iPercent)
{
  // convert the percentage to a mB (milliBell) value (*100 for dB)
  long hardwareVolume = (long)((float)iPercent * 0.01f * (VOLUME_MAXIMUM - VOLUME_MINIMUM) + VOLUME_MINIMUM);
  SetHardwareVolume(hardwareVolume);
  g_audioManager.SetVolume(iPercent);
}

void CApplication::SetHardwareVolume(long hardwareVolume)
{
  // TODO DRC
  if (hardwareVolume >= VOLUME_MAXIMUM) // + VOLUME_DRC_MAXIMUM
    hardwareVolume = VOLUME_MAXIMUM;// + VOLUME_DRC_MAXIMUM;
  if (hardwareVolume <= VOLUME_MINIMUM)
  {
    hardwareVolume = VOLUME_MINIMUM;
  }
  // update our settings
  if (hardwareVolume > VOLUME_MAXIMUM)
  {
    g_settings.m_dynamicRangeCompressionLevel = hardwareVolume - VOLUME_MAXIMUM;
    g_settings.m_nVolumeLevel = VOLUME_MAXIMUM;
  }
  else
  {
    g_settings.m_dynamicRangeCompressionLevel = 0;
    g_settings.m_nVolumeLevel = hardwareVolume;
  }

  // update mute state
  if(!g_settings.m_bMute && hardwareVolume <= VOLUME_MINIMUM)
  {
    g_settings.m_bMute = true;
    if (!m_guiDialogMuteBug.IsDialogRunning())
      m_guiDialogMuteBug.Show();
  }
  else if(g_settings.m_bMute && hardwareVolume > VOLUME_MINIMUM)
  {
    g_settings.m_bMute = false;
    if (m_guiDialogMuteBug.IsDialogRunning())
      m_guiDialogMuteBug.Close();
  }

  // and tell our player to update the volume
  if (m_pPlayer)
  {
    m_pPlayer->SetVolume(g_settings.m_nVolumeLevel);
    // TODO DRC
//    m_pPlayer->SetDynamicRangeCompression(g_settings.m_dynamicRangeCompressionLevel);
  }
}

int CApplication::GetVolume() const
{
  // converts the hardware volume (in mB) to a percentage
  return int(((float)(g_settings.m_nVolumeLevel + g_settings.m_dynamicRangeCompressionLevel - VOLUME_MINIMUM)) / (VOLUME_MAXIMUM - VOLUME_MINIMUM)*100.0f + 0.5f);
}

int CApplication::GetSubtitleDelay() const
{
  // converts subtitle delay to a percentage
  return int(((float)(g_settings.m_currentVideoSettings.m_SubtitleDelay + g_advancedSettings.m_videoSubsDelayRange)) / (2 * g_advancedSettings.m_videoSubsDelayRange)*100.0f + 0.5f);
}

int CApplication::GetAudioDelay() const
{
  // converts subtitle delay to a percentage
  return int(((float)(g_settings.m_currentVideoSettings.m_AudioDelay + g_advancedSettings.m_videoAudioDelayRange)) / (2 * g_advancedSettings.m_videoAudioDelayRange)*100.0f + 0.5f);
}

void CApplication::SetPlaySpeed(int iSpeed)
{
  if (!IsPlayingAudio() && !IsPlayingVideo())
    return ;
  if (m_iPlaySpeed == iSpeed)
    return ;
  if (!m_pPlayer->CanSeek())
    return;
  if (m_pPlayer->IsPaused())
  {
    if (
      ((m_iPlaySpeed > 1) && (iSpeed > m_iPlaySpeed)) ||
      ((m_iPlaySpeed < -1) && (iSpeed < m_iPlaySpeed))
    )
    {
      iSpeed = m_iPlaySpeed; // from pause to ff/rw, do previous ff/rw speed
    }
    m_pPlayer->Pause();
  }
  m_iPlaySpeed = iSpeed;

  m_pPlayer->ToFFRW(m_iPlaySpeed);
  if (m_iPlaySpeed == 1)
  { // restore volume
    m_pPlayer->SetVolume(g_settings.m_nVolumeLevel);
  }
  else
  { // mute volume
    m_pPlayer->SetVolume(VOLUME_MINIMUM);
  }
}

int CApplication::GetPlaySpeed() const
{
  return m_iPlaySpeed;
}

// Returns the total time in seconds of the current media.  Fractional
// portions of a second are possible - but not necessarily supported by the
// player class.  This returns a double to be consistent with GetTime() and
// SeekTime().
double CApplication::GetTotalTime() const
{
  double rc = 0.0;

  if (IsPlaying() && m_pPlayer)
  {
    if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0)
      rc = (*m_currentStack)[m_currentStack->Size() - 1]->m_lEndOffset;
    else
      rc = m_pPlayer->GetTotalTime();
  }

  return rc;
}

void CApplication::ResetPlayTime()
{
  if (IsPlaying() && m_pPlayer)
    m_pPlayer->ResetTime();
}

void CApplication::StopShutdownTimer()
{
  if (m_shutdownTimer.IsRunning())
    m_shutdownTimer.Stop();
}

void CApplication::ResetShutdownTimers()
{
  // reset system shutdown timer
  m_shutdownTimer.StartZero();

  // delete custom shutdown timer
  if (g_alarmClock.HasAlarm("shutdowntimer"))
    g_alarmClock.Stop("shutdowntimer", true);
}

// Returns the current time in seconds of the currently playing media.
// Fractional portions of a second are possible.  This returns a double to
// be consistent with GetTotalTime() and SeekTime().
double CApplication::GetTime() const
{
  double rc = 0.0;

  if (IsPlaying() && m_pPlayer)
  {
    if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0)
    {
      long startOfCurrentFile = (m_currentStackPosition > 0) ? (*m_currentStack)[m_currentStackPosition-1]->m_lEndOffset : 0;
      rc = (double)startOfCurrentFile + m_pPlayer->GetTime() * 0.001;
    }
    else
      rc = static_cast<double>(m_pPlayer->GetTime() * 0.001f);
  }

  return rc;
}

// Sets the current position of the currently playing media to the specified
// time in seconds.  Fractional portions of a second are valid.  The passed
// time is the time offset from the beginning of the file as opposed to a
// delta from the current position.  This method accepts a double to be
// consistent with GetTime() and GetTotalTime().
void CApplication::SeekTime( double dTime )
{
  if (IsPlaying() && m_pPlayer && (dTime >= 0.0))
  {
    if (!m_pPlayer->CanSeek()) return;
    if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0)
    {
      // find the item in the stack we are seeking to, and load the new
      // file if necessary, and calculate the correct seek within the new
      // file.  Otherwise, just fall through to the usual routine if the
      // time is higher than our total time.
      for (int i = 0; i < m_currentStack->Size(); i++)
      {
        if ((*m_currentStack)[i]->m_lEndOffset > dTime)
        {
          long startOfNewFile = (i > 0) ? (*m_currentStack)[i-1]->m_lEndOffset : 0;
          if (m_currentStackPosition == i)
            m_pPlayer->SeekTime((__int64)((dTime - startOfNewFile) * 1000.0));
          else
          { // seeking to a new file
            m_currentStackPosition = i;
            CFileItem item(*(*m_currentStack)[i]);
            item.m_lStartOffset = (long)((dTime - startOfNewFile) * 75.0);
            // don't just call "PlayFile" here, as we are quite likely called from the
            // player thread, so we won't be able to delete ourselves.
            m_applicationMessenger.PlayFile(item, true);
          }
          return;
        }
      }
    }
    // convert to milliseconds and perform seek
    m_pPlayer->SeekTime( static_cast<__int64>( dTime * 1000.0 ) );
  }
}

float CApplication::GetPercentage() const
{
  if (IsPlaying() && m_pPlayer)
  {
    if (IsPlayingAudio() && m_itemCurrentFile->HasMusicInfoTag())
    {
      const CMusicInfoTag& tag = *m_itemCurrentFile->GetMusicInfoTag();
      if (tag.GetDuration() > 0)
        return (float)(GetTime() / tag.GetDuration() * 100);
    }

    if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0)
      return (float)(GetTime() / GetTotalTime() * 100);
    else
      return m_pPlayer->GetPercentage();
  }
  return 0.0f;
}

void CApplication::SeekPercentage(float percent)
{
  if (IsPlaying() && m_pPlayer && (percent >= 0.0))
  {
    if (!m_pPlayer->CanSeek()) return;
    if (m_itemCurrentFile->IsStack() && m_currentStack->Size() > 0)
      SeekTime(percent * 0.01 * GetTotalTime());
    else
      m_pPlayer->SeekPercentage(percent);
  }
}

// SwitchToFullScreen() returns true if a switch is made, else returns false
bool CApplication::SwitchToFullScreen()
{
  // if playing from the video info window, close it first!
  if (g_windowManager.HasModalDialog() && g_windowManager.GetTopMostModalDialogID() == WINDOW_VIDEO_INFO)
  {
    CGUIWindowVideoInfo* pDialog = (CGUIWindowVideoInfo*)g_windowManager.GetWindow(WINDOW_VIDEO_INFO);
    if (pDialog) pDialog->Close(true);
  }

  // don't switch if there is a dialog on screen or the slideshow is active
  if (/*g_windowManager.HasModalDialog() ||*/ g_windowManager.GetActiveWindow() == WINDOW_SLIDESHOW)
    return false;

  // See if we're playing a video, and are in GUI mode
  if ( IsPlayingVideo() && g_windowManager.GetActiveWindow() != WINDOW_FULLSCREEN_VIDEO)
  {
#ifdef HAS_SDL
    // Reset frame count so that timing is FPS will be correct.
    SDL_mutexP(m_frameMutex);
    m_frameCount = 0;
    SDL_mutexV(m_frameMutex);
#endif

    // then switch to fullscreen mode
    g_windowManager.ActivateWindow(WINDOW_FULLSCREEN_VIDEO);
    return true;
  }
  // special case for switching between GUI & visualisation mode. (only if we're playing an audio song)
  if (IsPlayingAudio() && g_windowManager.GetActiveWindow() != WINDOW_VISUALISATION)
  { // then switch to visualisation
    g_windowManager.ActivateWindow(WINDOW_VISUALISATION);
    return true;
  }
  return false;
}

void CApplication::Minimize()
{
  g_Windowing.Minimize();
}

PLAYERCOREID CApplication::GetCurrentPlayer()
{
  return m_eCurrentPlayer;
}

// when a scan is initiated, save current settings
// and enable tag reading and remote thums
void CApplication::SaveMusicScanSettings()
{
  CLog::Log(LOGINFO,"Music scan has started... Enabling tag reading, and remote thumbs");
  g_settings.m_bMyMusicIsScanning = true;
  g_settings.Save();
}

void CApplication::RestoreMusicScanSettings()
{
  g_settings.m_bMyMusicIsScanning = false;
  g_settings.Save();
}

void CApplication::UpdateLibraries()
{
  if (g_guiSettings.GetBool("videolibrary.updateonstartup"))
  {
    CLog::Log(LOGNOTICE, "%s - Starting video library startup scan", __FUNCTION__);
    CGUIDialogVideoScan *scanner = (CGUIDialogVideoScan *)g_windowManager.GetWindow(WINDOW_DIALOG_VIDEO_SCAN);
    if (scanner && !scanner->IsScanning())
      scanner->StartScanning("");
  }

  if (g_guiSettings.GetBool("musiclibrary.updateonstartup"))
  {
    CLog::Log(LOGNOTICE, "%s - Starting music library startup scan", __FUNCTION__);
    CGUIDialogMusicScan *scanner = (CGUIDialogMusicScan *)g_windowManager.GetWindow(WINDOW_DIALOG_MUSIC_SCAN);
    if (scanner && !scanner->IsScanning())
      scanner->StartScanning("");
  }
}

void CApplication::CheckPlayingProgress()
{
  // check if we haven't rewound past the start of the file
  if (IsPlaying())
  {
    int iSpeed = g_application.GetPlaySpeed();
    if (iSpeed < 1)
    {
      iSpeed *= -1;
      int iPower = 0;
      while (iSpeed != 1)
      {
        iSpeed >>= 1;
        iPower++;
      }
      if (g_infoManager.GetPlayTime() / 1000 < iPower)
      {
        g_application.SetPlaySpeed(1);
        g_application.SeekTime(0);
      }
    }
  }
}

bool CApplication::ProcessAndStartPlaylist(const CStdString& strPlayList, CPlayList& playlist, int iPlaylist)
{
  CLog::Log(LOGDEBUG,"CApplication::ProcessAndStartPlaylist(%s, %i)",strPlayList.c_str(), iPlaylist);

  // initial exit conditions
  // no songs in playlist just return
  if (playlist.size() == 0)
    return false;

  // illegal playlist
  if (iPlaylist < PLAYLIST_MUSIC || iPlaylist > PLAYLIST_VIDEO)
    return false;

  // setup correct playlist
  g_playlistPlayer.ClearPlaylist(iPlaylist);

  // if the playlist contains an internet stream, this file will be used
  // to generate a thumbnail for musicplayer.cover
  g_application.m_strPlayListFile = strPlayList;

  // add the items to the playlist player
  g_playlistPlayer.Add(iPlaylist, playlist);

  // if we have a playlist
  if (g_playlistPlayer.GetPlaylist(iPlaylist).size())
  {
    // start playing it
    g_playlistPlayer.SetCurrentPlaylist(iPlaylist);
    g_playlistPlayer.Reset();
    g_playlistPlayer.Play();
    return true;
  }
  return false;
}

void CApplication::SaveCurrentFileSettings()
{
  if (m_itemCurrentFile->IsVideo())
  {
    // save video settings
    if (g_settings.m_currentVideoSettings != g_settings.m_defaultVideoSettings)
    {
      CVideoDatabase dbs;
      dbs.Open();
      dbs.SetVideoSettings(m_itemCurrentFile->m_strPath, g_settings.m_currentVideoSettings);
      dbs.Close();
    }
  }
}

bool CApplication::AlwaysProcess(const CAction& action)
{
  // check if this button is mapped to a built-in function
  if (!action.GetName().IsEmpty())
  {
    CStdString builtInFunction;
    vector<CStdString> params;
    CUtil::SplitExecFunction(action.GetName(), builtInFunction, params);
    builtInFunction.ToLower();

    // should this button be handled normally or just cancel the screensaver?
    if (   builtInFunction.Equals("powerdown")
        || builtInFunction.Equals("reboot")
        || builtInFunction.Equals("restart")
        || builtInFunction.Equals("restartapp")
        || builtInFunction.Equals("suspend")
        || builtInFunction.Equals("hibernate")
        || builtInFunction.Equals("quit")
        || builtInFunction.Equals("shutdown"))
    {
      return true;
    }
  }

  return false;
}

CApplicationMessenger& CApplication::getApplicationMessenger()
{
   return m_applicationMessenger;
}

bool CApplication::IsCurrentThread() const
{
  return CThread::IsCurrentThread(m_threadID);
}

bool CApplication::IsPresentFrame()
{
#ifdef HAS_SDL // TODO:DIRECTX
  SDL_mutexP(m_frameMutex);
  bool ret = m_bPresentFrame;
  SDL_mutexV(m_frameMutex);

  return ret;
#else
  return false;
#endif
}

#if defined(HAS_LINUX_NETWORK)
CNetworkLinux& CApplication::getNetwork()
{
  return m_network;
}
#elif defined(HAS_WIN32_NETWORK)
CNetworkWin32& CApplication::getNetwork()
{
  return m_network;
}
#else
CNetwork& CApplication::getNetwork()
{
  return m_network;
}

#endif
#ifdef HAS_PERFORMANCE_SAMPLE
CPerformanceStats &CApplication::GetPerformanceStats()
{
  return m_perfStats;
}
#endif
