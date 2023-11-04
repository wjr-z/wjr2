#ifndef WJR_PREPROCESSOR_EXTEND_HPP__
#define WJR_PREPROCESSOR_EXTEND_HPP__

// testing ...

#include <cassert>
#include <stdlib.h>

#include <wjr/preprocessor/arithmatic.hpp>
#include <wjr/preprocessor/compiler.hpp>
#include <wjr/preprocessor/details.hpp>
#include <wjr/preprocessor/logical.hpp>
#include <wjr/preprocessor/queue.hpp>

// TODO ...
#if defined(WJR_CPP_17)
#define WJR_INLINE_CVAR inline constexpr
#else
#define WJR_INLINE_CVAR static constexpr
#endif

#define WJR_PP_QUEUE_INIT_N(x, N) WJR_PP_QUEUE_INIT_N_I(x, N)
#define WJR_PP_QUEUE_INIT_N_I(x, N) (WJR_PP_REPEAT(x, N))

#define WJR_PP_QUEUE_CALL_SAME(args, op)                                                 \
    WJR_PP_QUEUE_CALL(args, WJR_PP_QUEUE_INIT_N(op, WJR_PP_QUEUE_SIZE(args)))

#define WJR_PP_QUEUE_CALL_N(args, ops, N) WJR_PP_QUEUE_CALL_(args, ops, WJR_PP_INC(N))

#define WJR_PP_QUEUE_CALL_N_SAME(args, op, N)                                            \
    WJR_PP_QUEUE_CALL_N(args, WJR_PP_QUEUE_INIT_N(op, N), N)

// (a, b, c) -> (f(a), g(b), h(c)) ...
// ops : WJR_PP_QUEUE_PUSH_BACK(x, f(y)/g(y)/ ...)
// gen a result queue at first of queue
#define WJR_PP_QUEUE_GENERATE(queue, ops)                                                \
    WJR_PP_QUEUE_POP_FRONT(                                                              \
        WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL(WJR_PP_QUEUE_PUSH_FRONT(queue, (0)), ops)))

#define WJR_PP_QUEUE_GENERATE_SAME(queue, op)                                            \
    WJR_PP_QUEUE_GENERATE(queue, WJR_PP_QUEUE_INIT_N(op, WJR_PP_QUEUE_SIZE(queue)))

#define WJR_PP_QUEUE_BACK(queue)                                                         \
    WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL_SAME(queue, WJR_PP_QUEUE_BACK_CALLER))
#define WJR_PP_QUEUE_BACK_CALLER(x, y) y

#define WJR_PP_QUEUE_POP_FRONT_N(queue, N)                                               \
    WJR_PP_QUEUE_CALL_N_SAME(queue, WJR_PP_QUEUE_POP_FRONT_N_CALLER, N)
#define WJR_PP_QUEUE_POP_FRONT_N_CALLER(x, y) y

#define WJR_PP_QUEUE_POP_BACK_N(queue, N)                                                \
    WJR_PP_QUEUE_GENERATE(queue,                                                         \
                          WJR_PP_QUEUE_POP_FRONT_N(                                      \
                              (WJR_PP_REPEAT(WJR_PP_QUEUE_POP_BACK_N_HEADER_CALLER,      \
                                             WJR_PP_QUEUE_SIZE(queue)),                  \
                               WJR_PP_REPEAT(WJR_PP_QUEUE_POP_BACK_N_TAILER_CALLER, N)), \
                              N))
#define WJR_PP_QUEUE_POP_BACK_N_HEADER_CALLER(x, y) WJR_PP_QUEUE_PUSH_BACK(x, y)
#define WJR_PP_QUEUE_POP_BACK_N_TAILER_CALLER(x, y) x

#define WJR_PP_QUEUE_POP_BACK(queue) WJR_PP_QUEUE_POP_BACK_N(queue, 1)

#define WJR_PP_QUEUE_AT(queue, N) WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_POP_FRONT(queue, N))

#define WJR_PP_QUEUE_REVERSE(queue)                                                      \
    WJR_PP_QUEUE_POP_BACK(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL_SAME(                     \
        WJR_PP_QUEUE_PUSH_FRONT(queue, (0)), WJR_PP_QUEUE_REVERSE_CALLER)))
#define WJR_PP_QUEUE_REVERSE_CALLER(x, y) WJR_PP_QUEUE_PUSH_FRONT(x, y)

// (a, b, c) -> (a b c)
#define WJR_PP_QUEUE_MERGE(queue) WJR_PP_QUEUE_CALL_SAME(queue, WJR_PP_QUEUE_MERGE_CALLER)
#define WJR_PP_QUEUE_MERGE_CALLER(x, y) x y

// (a, b, c) -> a b c
#define WJR_PP_QUEUE_PUT(queue) WJR_PP_QUEUE_EXPAND(WJR_PP_QUEUE_MERGE(queue))

// ((A), (B), (C)) -> (A, B, C)
#define WJR_PP_QUEUE_UNWRAP(queue)                                                       \
    WJR_PP_QUEUE_GENERATE_SAME(queue, WJR_PP_QUEUE_UNWRAP_CALLER)
#define WJR_PP_QUEUE_UNWRAP_CALLER(x, y) WJR_PP_QUEUE_PUSH_BACK(x, WJR_PP_QUEUE_EXPAND(y))

// (A, B, C) (x, y, z) -> ((A, x), (B, y), (C, z))
#define WJR_PP_QUEUE_ZIP_2(queue1, queue2)                                               \
    WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL_N_SAME(                  \
        ((queue1), queue2), WJR_PP_QUEUE_ZIP_2_CALLER, WJR_PP_QUEUE_SIZE(queue1))))

#define WJR_PP_QUEUE_ZIP_2_CALLER(x, y)                                                  \
    WJR_PP_QUEUE_PUSH_FRONT(                                                             \
        WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_PUSH_BACK(                                   \
            x, (WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_FRONT(x)), WJR_PP_QUEUE_FRONT(y)))),     \
        WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(x))),                                  \
        WJR_PP_QUEUE_POP_FRONT(y)

// ((A), (B), (C)) (x, y, z) -> ((A, x), (B, y), (C, z))
#define WJR_PP_QUEUE_ZIP_MORE(queue1, queue2)                                            \
    WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL_N_SAME(                  \
        ((queue1), queue2), WJR_PP_QUEUE_ZIP_MORE_CALLER, WJR_PP_QUEUE_SIZE(queue1))))

#define WJR_PP_QUEUE_ZIP_MORE_CALLER(x, y)                                               \
    WJR_PP_QUEUE_PUSH_FRONT(                                                             \
        WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_PUSH_BACK(                                   \
            x, (WJR_PP_QUEUE_EXPAND(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_FRONT(x))),          \
                WJR_PP_QUEUE_FRONT(y)))),                                                \
        WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(x))),                                  \
        WJR_PP_QUEUE_POP_FRONT(y)

#define WJR_PP_QUEUE_ZIP(...)                                                            \
    WJR_PP_QUEUE_ZIP_I(WJR_PP_ARGS_LEN(__VA_ARGS__), __VA_ARGS__)
#define WJR_PP_QUEUE_ZIP_I(N, ...)                                                       \
    WJR_PP_SWITCH(N, (1, WJR_PP_QUEUE_ZIP_I1), (2, WJR_PP_QUEUE_ZIP_I2),                 \
                  (WJR_PP_QUEUE_ZIP_IN))                                                 \
    (__VA_ARGS__)

#define WJR_PP_QUEUE_ZIP_I1(q1) WJR_PP_QUEUE_TRANSFORM(q1, WJR_PP_WRAP)
#define WJR_PP_WRAP(x) (x)
#define WJR_PP_QUEUE_ZIP_I2(q1, q2) WJR_PP_QUEUE_ZIP_2(q1, q2)
#define WJR_PP_QUEUE_ZIP_IN(q1, q2, ...)                                                 \
    WJR_PP_QUEUE_CALL_N_SAME((WJR_PP_QUEUE_ZIP_2(q1, q2), __VA_ARGS__),                  \
                             WJR_PP_QUEUE_ZIP_MORE, WJR_PP_ARGS_LEN(__VA_ARGS__))

// switch
// (x, F) -> WJR_PP_BOOL_IF(WJR_EQ(val, x), F, else)
// (L, R, F) -> WJR_PP_BOOL_IF(WJR_PP_BOOL_AND(WJR_PP_GE(val, L), WJR_PP_LE(val, R)), F,
// else) default : (F) -> F default must be the last arg
#define WJR_PP_SWITCH(val, ...) WJR_PP_SWITCH_I(val, (__VA_ARGS__, (error)))

#define WJR_PP_SWITCH_I(val, queue)                                                      \
    WJR_PP_QUEUE_FRONT(                                                                  \
        WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL_N_SAME(              \
            WJR_PP_QUEUE_PUSH_FRONT(                                                     \
                WJR_PP_QUEUE_POP_FRONT(queue),                                           \
                WJR_PP_QUEUE_PUSH_FRONT(WJR_PP_QUEUE_FRONT(queue), val)),                \
            WJR_PP_SWITCH_CALLER, WJR_PP_DEC(WJR_PP_QUEUE_SIZE(queue))))))

#define WJR_PP_SWITCH_CALLER(x, next) WJR_PP_SWITCH_ARG(next, WJR_PP_QUEUE_EXPAND(x))

#define WJR_PP_SWITCH_ARG(next, ...)                                                     \
    WJR_PP_SWITCH_ARG_I(WJR_PP_ARGS_LEN(__VA_ARGS__), next, __VA_ARGS__)
#define WJR_PP_SWITCH_ARG_I(N, next, ...) WJR_PP_SWITCH_ARG_I_N(N, next, __VA_ARGS__)
#define WJR_PP_SWITCH_ARG_I_N(N, next, ...) WJR_PP_SWITCH_ARG_##N(next, __VA_ARGS__)
#define WJR_PP_SWITCH_ARG_2(next, val, F) (val, F)
#define WJR_PP_SWITCH_ARG_3(next, val, x, F)                                             \
    WJR_PP_BOOL_IF(WJR_PP_EQ(val, x), (val, F), WJR_PP_QUEUE_PUSH_FRONT(next, val))
#define WJR_PP_SWITCH_ARG_4(next, val, L, R, F)                                          \
    WJR_PP_BOOL_IF(WJR_PP_BOOL_AND(WJR_PP_GE(val, L), WJR_PP_LE(val, R)), (val, F),      \
                   WJR_PP_QUEUE_PUSH_FRONT(next, val))

// (a, b, c) -> (f(a), f(b), f(c))
#define WJR_PP_QUEUE_TRANSFORM(queue, F)                                                 \
    WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_CALL_SAME(                    \
        WJR_PP_QUEUE_PUSH_FRONT(queue, (F)), WJR_PP_QUEUE_TRANSFORM_CALLER)))
#define WJR_PP_QUEUE_TRANSFORM_CALLER(x, y)                                              \
    WJR_PP_QUEUE_PUSH_BACK(x, WJR_PP_QUEUE_FRONT(x)(y))

#define WJR_PP_QUEUE_TRANSFORM_ARG(queue, F, arg)                                        \
    WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_POP_FRONT(WJR_PP_QUEUE_FRONT(                    \
        WJR_PP_QUEUE_CALL_SAME(WJR_PP_QUEUE_PUSH_FRONT(queue, (F, arg)),                 \
                               WJR_PP_QUEUE_TRANSFORM_ARG_CALLER))))
#define WJR_PP_QUEUE_TRANSFORM_ARG_CALLER(x, y)                                          \
    WJR_PP_QUEUE_PUSH_BACK(                                                              \
        x, WJR_PP_QUEUE_FRONT(x)(WJR_PP_QUEUE_FRONT(WJR_PP_QUEUE_POP_FRONT(x)), y))

// a, b, c -> ATTRIBUTE(a) ATTRIBUTE(b) ATTRIBUTE(c)
#define WJR_ATTRIBUTES(...)                                                              \
    WJR_PP_QUEUE_PUT(WJR_PP_QUEUE_TRANSFORM((__VA_ARGS__), WJR_ATTRIBUTE))

// header0, header1, ...
#define WJR_PP_VARS(header, tailer)                                                      \
    WJR_PP_QUEUE_EXPAND(WJR_PP_QUEUE_TRANSFORM_ARG(tailer, WJR_PP_VARS_CALLER, header))
#define WJR_PP_VARS_CALLER(header, x) WJR_PP_CONCAT(header, x)

#define WJR_PP_VARS_N(header, N) WJR_PP_VARS(header, (WJR_PP_IOTA(N)))

// example :
// WJR_VARS_PREFIX(typename, WJR_VARS(T, (0, 1, 2))) -> typename T0, typename T1, typename
// T2
#define WJR_PP_VARS_PREFIX(prefix, queue)                                                \
    WJR_PP_QUEUE_EXPAND(                                                                 \
        WJR_PP_QUEUE_TRANSFORM_ARG(queue, WJR_PP_VARS_PREFIX_CALLER, prefix))
#define WJR_PP_VARS_PREFIX_CALLER(prefix, x) prefix x

#define WJR_DEFINE_FUNC_IMPL(is_template, template_header, template_types,               \
                             template_fowards, template_backwards, func_ret_type,        \
                             func_name, func_types, func_vars)

// func_header, func_types, func_vars, func_body : queue
// for example :
// func_header = (template <typename T> inline void foo)
// func_types = (int)
// func_vars = (x)
// func_body = (noexcept { return x; })
#define WJR_DEFINE_FUNC(func_header, func_types, func_vars, func_body)                   \
    WJR_PP_QUEUE_EXPAND(func_header)                                                     \
    (WJR_PP_QUEUE_EXPAND(WJR_PP_QUEUE_TRANSFORM(                                         \
        WJR_PP_QUEUE_ZIP_2(func_types, func_vars), WJR_DEFINE_FUNC_TRAN_CALLER)))        \
        WJR_PP_QUEUE_EXPAND(func_body)
#define WJR_DEFINE_FUNC_TRAN_CALLER(x) WJR_DEFINE_FUNC_TRAN_CALLER_I x
#define WJR_DEFINE_FUNC_TRAN_CALLER_I(x, y) x y

// ASSERT_LEVEL : 0 ~ 3
// 0 : Release (defined(NDEBUG) && ! defined(WJR_DEBUG_LEVEL))
// 1 : Some simple runtime checks, such as boundary checks (default)
// 2 : Most runtime checks
// 3 : Maximize runtime checks
#if defined WJR_DEBUG_LEVEL
#define WJR_ASSERT_LEVEL WJR_DEBUG_LEVEL
#elif defined(NDEBUG)
#define WJR_ASSERT_LEVEL 0
#else
#define WJR_ASSERT_LEVEL 1
#endif //

#if defined(NDEBUG)
#define WJR_ASSERT_IMPL(expr)                                                            \
    abort();                                                                             \
    WJR_UNREACHABLE
#else
#define WJR_ASSERT_IMPL(expr)                                                            \
    assert(expr);                                                                        \
    WJR_UNREACHABLE
#endif

#define WJR_ASSERT_CHECK_I_NOMESSAGE(expr)                                               \
    do {                                                                                 \
        WJR_ASSERT_IMPL(expr);                                                           \
    } while (0)

#define WJR_ASSERT_CHECK_I_MESSAGE(expr, fmt, ...)                                       \
    do {                                                                                 \
        if (!WJR_UNLIKELY(expr)) {                                                       \
            fprintf(stderr, "Additional error message : " fmt "\n", ##__VA_ARGS__);      \
            WJR_ASSERT_IMPL(expr);                                                       \
        }                                                                                \
    } while (0)

#define WJR_ASSERT_CHECK_I(...)                                                          \
    WJR_ASSERT_CHECK_I_N(WJR_PP_ARGS_LEN(__VA_ARGS__), __VA_ARGS__)
#define WJR_ASSERT_CHECK_I_N(N, ...)                                                     \
    WJR_PP_BOOL_IF(WJR_PP_EQ(N, 1), WJR_ASSERT_CHECK_I_NOMESSAGE,                        \
                   WJR_ASSERT_CHECK_I_MESSAGE)                                           \
    (__VA_ARGS__)

#define WJR_ASSERT_UNCHECK_I(...)                                                        \
    do {                                                                                 \
    } while (0)

#define WJR_ASSERT(level, ...)                                                           \
    WJR_PP_BOOL_IF(WJR_PP_GT(WJR_ASSERT_LEVEL, level), WJR_ASSERT_CHECK_I,               \
                   WJR_ASSERT_UNCHECK_I)                                                 \
    (__VA_ARGS__)

#if defined(WJR_CPP_17)
#define WJR_INLINE_CVAR inline constexpr
#else
#define WJR_INLINE_CVAR static constexpr
#endif

#endif // ! WJR_PREPROCESSOR_EXTEND_HPP__