#ifndef TASKS_EXPORT
#define TASKS_EXPORT

#if defined (Q_OS_WINDOWS)
	#include "tasks_export_windows.h"
#endif

#if defined(Q_OS_LINUX)
	#include "tasks_export_linux.h"
#endif

#endif
