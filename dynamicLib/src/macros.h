#pragma once

#include "pch/so2pch.h"

#ifdef SO2_PLATFORM_WINDOWS
#ifdef SO2_BUILD_DLL
#define SO2_API __declspec(dllexport)
#define SO2_DLL _T("[DLL] ")
#else
#define SO2_API __declspec(dllimport)
#define SO2_DLL _T("[PROGRAM] ")
#endif 
#else
#error "This app only supports Windows!"
#endif

#define _TENDL std::endl

#ifdef UNICODE
#define _TCOUT					std::wcout
#define _TCIN					std::wcin
#define _TSTRING				std::wstring
#define _TSTRINGSTREAM			std::wstringstream
#define _TIFSTREAM				std::wifstream
#define _TOFSTREAM				std::wofstream
#define _TTOSTRING				std::to_wstring
#define _TSTRCPY				wcscpy
#define _TSTRCPY_S				wcscpy_s
#define _TSTRCMP				wcscmp
#define _TSTRLEN				wcslen
#define _TSTRCAT				wcscat
#define _TSTRCAT_S				wcscat_s
#define _TSPRINTF				wsprintf
#define _TLPSTR					LPWSTR
#else
#define _TCOUT					std::cout
#define _TCIN					std::cin
#define _TSTRING				std::string
#define _TSTRINGSTREAM			std::stringstream
#define _TIFSTREAM				std::ifstream
#define _TOFSTREAM				std::ofstream
#define _TTOSTRING				std::to_string
#define _TSTRCPY				lstrcpyA
#define _TSTRCPY_S				lstrcpynA
#define _TSTRCMP				strcmp
#define _TSTRLEN				strlen
#define _TSTRCAT				strcat
#define _TSTRCAT_S				strcat_s
#define _TSPRINTF				sprintf
#define _TLPSTR					LPSTR
#endif

#ifdef SO2_DEBUG
#define LOG_INFO(x, ...) _tprintf_s(SO2_DLL _T("[Info] ") x _T("\n"), __VA_ARGS__);
#define LOG_DEBUG(x, ...) _tprintf_s(SO2_DLL _T("[Debug] ") x _T("\n"), __VA_ARGS__);
#define LOG_ERRO(x, ...) _tprintf_s(SO2_DLL _T("[Erro] ") x _T("\n"), __VA_ARGS__);
#else
#define LOG_INFO(...)
#define LOG_DEBUG(...)
#define LOG_ERROR(...)
#endif

#ifdef UNICODE
#define DEFINE_UNICODE if (_setmode(_fileno(stdin), _O_WTEXT) <= 0) \
					LOG_ERRO(_T("Erro ao definir o stdin como UNICODE!")); \
			if (_setmode(_fileno(stdout), _O_WTEXT) <= 0) \
					LOG_ERRO(_T("Erro ao definir o stdout como UNICODE!"));
#define SET_FILE_UTF8(x) x.imbue(std::locale(x.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff,\
			std::consume_header>));
#else
#define DEFINE_UNICODE
#define SET_FILE_UTF8(x)
#endif