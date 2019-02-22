#ifndef __ICLIENTMODULE_H__
#define __ICLIENTMODULE_H__

#ifdef DLLICLIENT_EX
	#define DLLICLIENT __declspec(dllexport)
#else
	#define DLLICLIENT __declspec(dllimport)
#endif

#endif
