#ifndef WJR_PREPROCESSOR_DETAILS_BASIC_HPP__
#define WJR_PREPROCESSOR_DETAILS_BASIC_HPP__

#define WJR_PP_EMPTY(...)

#define WJR_PP_CONCAT(x, y) WJR_PP_CONCAT_I(x, y)
#define WJR_PP_CONCAT_I(x, y) x##y

#define WJR_PP_PAREN ()

#define WJR_PP_DEFER(FUNC) FUNC WJR_PP_PAREN

#define WJR_PP_EXPAND(...) WJR_PP_EXPAND_I(__VA_ARGS__)
#define WJR_PP_EXPAND_I(...) __VA_ARGS__

#define WJR_PP_REC_EXPAND(...)                                                           \
    WJR_PP_REC_EXPAND3(WJR_PP_REC_EXPAND3(WJR_PP_REC_EXPAND3(__VA_ARGS__)))
#define WJR_PP_REC_EXPAND3(...)                                                          \
    WJR_PP_REC_EXPAND2(WJR_PP_REC_EXPAND2(WJR_PP_REC_EXPAND2(__VA_ARGS__)))
#define WJR_PP_REC_EXPAND2(...)                                                          \
    WJR_PP_REC_EXPAND1(WJR_PP_REC_EXPAND1(WJR_PP_REC_EXPAND1(__VA_ARGS__)))
#define WJR_PP_REC_EXPAND1(...) __VA_ARGS__

#define WJR_PP_STR(x) WJR_PP_STR_I(x)
#define WJR_PP_STR_I(x) #x

#define WJR_PP_ESC(x) WJR_PP_ESC_(WJR_PP_ESC_I, x)
#define WJR_PP_ESC_(M, x) M x
#define WJR_PP_ESC_I(...) __VA_ARGS__

// don't support 0 agument
#define WJR_PP_ARGS_LEN(...) WJR_PP_ARGS_LEN_I(__VA_ARGS__)

#define WJR_PP_ARGS_LEN_I(...)                                                           \
    WJR_PP_EXPAND(WJR_PP_ARGS_LEN_(0, ##__VA_ARGS__, WJR_PP_ARGS_LEN_RSEQ_N()))

#define WJR_PP_ARGS_LEN_RSEQ_N()                                                         \
    64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44,  \
        43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24,  \
        23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,  \
        1, 0
#define WJR_PP_ARGS_LEN_(...) WJR_PP_EXPAND(WJR_PP_ARGS_LEN_N(__VA_ARGS__))
#define WJR_PP_ARGS_LEN_N(                                                               \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18,     \
    _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, \
    _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, \
    _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, N, ...)             \
    N

#define WJR_PP_FUNC_TABLE_DEF(FUNC) WJD_HOLDER, WJR_PP_DEFER, FUNC

#define WJR_PP_USE(FUNC) WJR_PP_USE_I(WJR_PP_FUNC_TABLE_##FUNC, WJR_PP_USE_X, FUNC)
#define WJR_PP_USE_I(...) WJR_PP_USE_II(__VA_ARGS__)
#define WJR_PP_USE_II(HOLDER, FUNC, ARG, ...) FUNC(ARG)
#define WJR_PP_USE_X(FUNC) FUNC

#define WJR_PP_USE_FUNC() WJR_PP_USE
#define WJR_PP_FUNC_TABLE_WJR_PP_USE WJR_PP_FUNC_TABLE_DEF(WJR_PP_USE_FUNC)

#endif // ! WJR_PREPROCESSOR_DETAILS_BASIC_HPP__
