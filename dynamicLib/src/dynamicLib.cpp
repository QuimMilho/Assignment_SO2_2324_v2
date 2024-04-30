#include "pch/so2pch.h"

#include "dynamicLib.h"

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved)
{
    DEFINE_UNICODE;
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        LOG_DEBUG(_T("Processo adicionado!"));
        break;

    case DLL_THREAD_ATTACH:
        LOG_DEBUG(_T("Thread adicionada!"));
        break;

    case DLL_THREAD_DETACH:
        LOG_DEBUG(_T("Thread removida!"));
        break;

    case DLL_PROCESS_DETACH:
        LOG_DEBUG(_T("Processo removido!"));
        break;
    }
    return TRUE;

}
