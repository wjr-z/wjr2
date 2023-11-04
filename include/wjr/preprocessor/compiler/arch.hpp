#ifndef WJR_PREPROCESSOR_COMPILER_ARCH_H__
#define WJR_PREPROCESSOR_COMPILER_ARCH_H__

// Only optimization for x86-64 now

#if (defined(_M_IX86) || defined(__i386__)) && !defined(WJR_VM)
#define WJR_X86_32 1
#else
#define WJR_X86_32 0
#endif

#if (defined(_M_X64) || defined(__x86_64__)) && !defined(WJR_VM)
#define WJR_X86_64 1
#else
#define WJR_X86_64 0
#endif

#if defined(WJR_X86_32) || defined(WJR_X86_64)
#define WJR_X86 1
#else
#define WJR_X86 0
#endif

#endif // !WJR_PREPROCESSOR_COMPILER_ARCH_H__
