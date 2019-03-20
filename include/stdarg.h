#ifndef _STDARG_H_
#define _STDARG_H_

typedef unsigned char *va_list;

#define __va_align(type) (__alignof(type) >= 2 ? __alignof(type) : 2)

#define __va_do_align(vl, type)                                                \
  ((vl) = (char *)((((unsigned long)(vl)) + __va_align(type) - 1) /            \
                   __va_align(type) * __va_align(type)))

#define __va_mem(vl, type)                                                     \
  (__va_do_align((vl), type), (vl) += sizeof(type), ((type *)(vl))[-1])

#define va_start(ap, lastarg) ((ap) = (va_list)(&lastarg + 1))

#define va_arg(vl, type) __va_mem(vl, type)

#define va_end(vl) ((vl) = 0)

#if __STDC_VERSION__ >= 199901L
#define va_copy(new, old) ((new) = (old))
#endif

#endif /* !_STDARG_H_ */