#ifndef __xplatform_h__
#define __xplatform_h__

/*
#include "../shared/xplatform.h"
*/

/*
  Platform				Defined
  Waves Plugin			SE_TARGET_WAVES
  SEM Plugin			SE_TARGET_SEM (selected SEMs)
  VST3 Plugin			SE_TARGET_VST3									SE_PLUGIN_SUPPORT
  JUCE Plugin			GMPI_IS_PLATFORM_JUCE==1						SE_PLUGIN_SUPPORT
  VST2 Plugin			SE_TARGET_VST2					SE_SUPPORT_MFC	SE_PLUGIN_SUPPORT
  SynthEdit.exe			SE_EDIT_SUPPORT					SE_SUPPORT_MFC	SE_PLUGIN_SUPPORT
  SynthEdit.exe (store)	SE_EDIT_SUPPORT					SE_SUPPORT_MFC	SE_PLUGIN_SUPPORT  SE_TARGET_UWP
  
  SynthEdit Universal	SE_TARGET_WINDOWS_STORE_APP
  Win Store App			SE_TARGET_WINDOWS_STORE_APP

  SE_PLUGIN_SUPPORT - SEM Version2 dll support.
  SE_SUPPORT_MFC    - MFC-based GUI support (SynthEdit 1, VST2).
*/

#if (defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_APP )
#define SE_TARGET_WINDOWS_STORE_APP
#endif

#if defined(JUCE_APP_VERSION)
#define GMPI_IS_PLATFORM_JUCE 1
#else
#define GMPI_IS_PLATFORM_JUCE 0
#endif

// SE_SUPPORT_MFC = VST 2.4
#if (GMPI_IS_PLATFORM_JUCE == 0) && !defined(SE_SUPPORT_MFC) && !defined(SE_TARGET_VST3) && !defined(SE_TARGET_AU) && !defined(SE_TARGET_SEM) && !defined(SE_EDIT_SUPPORT) && !defined(SE_TARGET_WINDOWS_STORE_APP)
    #define SE_TARGET_WAVES
	#define GMPI_IS_PLATFORM_WV 1
#else
	#define GMPI_IS_PLATFORM_WV 0
#endif

// Can code include inline assembler?
#if defined(_MSC_VER )
    // MS Windows.
    #if !defined(_M_X64)
        #define SE_USE_ASM
    #endif
#endif

// External plugins not supported on Waves, and Not supported on Windows store Apps
#if !defined( SE_TARGET_WAVES ) && !defined(SE_TARGET_WINDOWS_STORE_APP)
	#define SE_EXTERNAL_SEM_SUPPORT
#endif

#endif

// MFC Support
#if defined( SE_TARGET_VST2 ) || (defined( SE_EDIT_SUPPORT ) && !defined(SE_TARGET_WINDOWS_STORE_APP))
#if !defined(SE_SUPPORT_MFC)
#error please define SE_SUPPORT_MFC
#endif
#endif

#ifdef _WIN32
	#define PLATFORM_PATH_SLASH '\\'
	#define PLATFORM_PATH_SLASH_L L'\\'
#else
	#define PLATFORM_PATH_SLASH '/'
	#define PLATFORM_PATH_SLASH_L L'/'
    #define MAX_PATH 500
#endif

// Strings.
#include <string>

#if defined(UNICODE) || defined(_UNICODE)
	typedef std::wstring platform_string;
#else
	typedef std::string platform_string;
#endif

#ifdef _WIN32
	#include "tchar.h"
#else

#ifndef __TCHAR_DEFINED
	#if defined(UNICODE) || defined(_UNICODE)
		typedef wchar_t _TCHAR;
	#else
		typedef char _TCHAR;
	#endif
	typedef _TCHAR* LPTSTR;

	#ifndef _T
		#if defined(UNICODE) || defined(_UNICODE)
			#define _T(x) L##x
		#else
			#define _T(x) x
		#endif
	#endif
#endif

#endif
