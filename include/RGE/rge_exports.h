
#ifndef RGE_EXPORT_H
#define RGE_EXPORT_H

#ifdef RGE_STATIC_DEFINE
#  define RGE_EXPORT
#  define RGE_NO_EXPORT
#else
#  ifndef RGE_EXPORT
#    ifdef RGE_EXPORTS
        /* We are building this library */
#      define RGE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define RGE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef RGE_NO_EXPORT
#    define RGE_NO_EXPORT 
#  endif
#endif

#ifndef RGE_DEPRECATED
#  define RGE_DEPRECATED __declspec(deprecated)
#endif

#ifndef RGE_DEPRECATED_EXPORT
#  define RGE_DEPRECATED_EXPORT RGE_EXPORT RGE_DEPRECATED
#endif

#ifndef RGE_DEPRECATED_NO_EXPORT
#  define RGE_DEPRECATED_NO_EXPORT RGE_NO_EXPORT RGE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RGE_NO_DEPRECATED
#    define RGE_NO_DEPRECATED
#  endif
#endif

#endif /* RGE_EXPORT_H */
