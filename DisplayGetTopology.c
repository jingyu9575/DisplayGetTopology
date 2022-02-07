#include <windows.h>

#define ALLOC(T, size) (T*) LocalAlloc(LMEM_FIXED, (size) * sizeof(T))
#define FREE(p) LocalFree(p)

#ifdef USE_FREE_OPT
#define FREE_OPT FREE
#else
#define FREE_OPT(p)
#endif

int process(void) {
	UINT32 npi, nmi;
	GetDisplayConfigBufferSizes(QDC_DATABASE_CURRENT, &npi, &nmi);
	DISPLAYCONFIG_PATH_INFO* pi = ALLOC(DISPLAYCONFIG_PATH_INFO, npi);
	DISPLAYCONFIG_MODE_INFO* mi = ALLOC(DISPLAYCONFIG_MODE_INFO, nmi);
	int result = -1;
	DISPLAYCONFIG_TOPOLOGY_ID topology;
	if (QueryDisplayConfig(QDC_DATABASE_CURRENT, &npi, pi, &nmi, mi,
	                       &topology) == ERROR_SUCCESS) {
		result = topology == DISPLAYCONFIG_TOPOLOGY_INTERNAL   ? 1
		         : topology == DISPLAYCONFIG_TOPOLOGY_CLONE    ? 2
		         : topology == DISPLAYCONFIG_TOPOLOGY_EXTEND   ? 3
		         : topology == DISPLAYCONFIG_TOPOLOGY_EXTERNAL ? 4
		                                                       : -1;
	}
	FREE_OPT(pi);
	FREE_OPT(mi);
	return result;
}

int entry(void) { return ExitProcess(process()), 0; }
