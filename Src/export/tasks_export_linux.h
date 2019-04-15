
#ifndef TASKS_EXPORT_LINUX_H
#define TASKS_EXPORT_LINUX_H

#ifdef TASKS_STATIC_DEFINE
#  define TASKS_EXPORT
#  define TASKS_NO_EXPORT
#else
#  ifndef TASKS_EXPORT
#    ifdef Tasks_EXPORTS
        /* We are building this library */
#      define TASKS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define TASKS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef TASKS_NO_EXPORT
#    define TASKS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef TASKS_DEPRECATED
#  define TASKS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef TASKS_DEPRECATED_EXPORT
#  define TASKS_DEPRECATED_EXPORT TASKS_EXPORT TASKS_DEPRECATED
#endif

#ifndef TASKS_DEPRECATED_NO_EXPORT
#  define TASKS_DEPRECATED_NO_EXPORT TASKS_NO_EXPORT TASKS_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define TASKS_NO_DEPRECATED
#endif

#endif
