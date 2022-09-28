#ifndef __ICLIENTMODULE_H__
#define __ICLIENTMODULE_H__

#ifdef DLLICLIENT_EX
    #ifdef __linux__
        #define DLLICLIENT __attribute__((visibility("default")))
    #else
        #define DLLICLIENT  __declspec(dllexport)
    #endif
#else
    #ifdef __linux__
        #define DLLICLIENT
    #else
        #define DLLICLIENT  __declspec(dllimport)
    #endif
#endif

#endif
