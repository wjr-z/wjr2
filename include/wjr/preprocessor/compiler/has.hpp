#ifndef WJR_PREPROCESSOR_HAS_HPP__
#define WJR_PREPROCESSOR_HAS_HPP__

#include <wjr/preprocessor/compiler/compiler.hpp>

#define WJR_HAS_INLINE_ASM 0
#define WJR_HAS_INT128 0
#define WJR_HAS_INT128_DIV 0

#if defined(WJR_X86) &&                                                        \
    (defined(WJR_COMPILER_GCC) || defined(WJR_COMPILER_CLANG))
#undef WJR_HAS_INLINE_ASM
#define WJR_HAS_INLINE_ASM 1
#endif

#if defined(__SIZEOF_INT128__)
#undef WJR_HAS_INT128
#define WJR_HAS_INT128 1
#if !(defined(__clang__) && defined(LIBDIVIDE_VC))
#undef WJR_HAS_INT128_DIV
#define WJR_HAS_INT128_DIV 1
#endif
#endif

#endif // ! WJR_PREPROCESSOR_HAS_HPP__