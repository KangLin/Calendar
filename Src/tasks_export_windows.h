
#ifndef TASKS_EXPORT_WINDOWS_H
#define TASKS_EXPORT_WINDOWS_H

#ifdef TASKS_STATIC_DEFINE
#  define TASKS_EXPORT
#  define TASKS_NO_EXPORT
#else
#  ifndef TASKS_EXPORT
#    ifdef Tasks_EXPORTS
        /* We are building this library */
#      define TASKS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define TASKS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef TASKS_NO_EXPORT
#    define TASKS_NO_EXPORT 
#  endif
#endif

#ifndef TASKS_DEPRECATED
#  define TASKS_DEPRECATED __declspec(deprecated)
#endif

#ifndef TASKS_DEPRECATED_EXPORT
#  define TASKS_DEPRECATED_EXPORT TASKS_EXPORT TASKS_DEPRECATED
#endif

#ifndef TASKS_DEPRECATED_NO_EXPORT
#  define TASKS_DEPRECATED_NO_EXPORT TASKS_NO_EXPORT TASKS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef TASKS_NO_DEPRECATED
#    define TASKS_NO_DEPRECATED
#  endif
#endif

#endif /* TASKS_EXPORT_H */
