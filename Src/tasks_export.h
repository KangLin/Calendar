#ifndef TASKS_EXPORT_H
#define TASKS_EXPORT_H

#if defined (Q_OS_WIN)
	#include "tasks_export_windows.h"
#endif

#if defined(Q_OS_LINUX)
	#include "tasks_export_linux.h"
#endif

#endif
