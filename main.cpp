#include <iostream>
#include <wjr/atomic.hpp>
#include <wjr/preprocessor.hpp>

#define REPEAT(x, n) REPEAT_I(x, n)
#define REPEAT_FUNC() REPEAT

#define PP_REPEAT_FUNC WJR_PP_DEFER(REPEAT_FUNC)
#define PP_1 1
#define PP_x x

#define FUNC(x) PP_##x

#define REPEAT_I(x, n) REPEAT_##n(x)

#define REPEAT_1(x) FUNC(x)
#define REPEAT_2(x) REPEAT_1(x), REPEAT_1(x)

#define BOOST_PP_NOT_EQUAL_I(x, y)                                                       \
    WJR_PP_CONCAT(BOOST_PP_NOT_EQUAL_CHECK_,                                             \
                  BOOST_PP_NOT_EQUAL_##x(0, BOOST_PP_NOT_EQUAL_##y))

#define BOOST_PP_NOT_EQUAL_0(c, y) WJR_PP_BOOL_IF(c, NIF, y(1, NIF))
#define BOOST_PP_NOT_EQUAL_1(c, y) WJR_PP_BOOL_IF(c, NIF, y(1, NIF))

#define WJR_PP_GET_FUNC(FUNC)                                                            \
    WJR_PP_GET_FUNC_I(WJR_PP_EXPAND(WJR_PP_FUNC_TABLE_##FUNC), FUNC)
#define WJR_PP_GET_FUNC_I(HOLDER, FUNC, ...) (HOLDER), (FUNC), (__VA_ARGS__)

#define WJR_PP_GET_2(HOLDER, FUNC, ...) FUNC

#define WJR_PP_FUNC_TABLE(x) 0, x

#define WJR_PP_FUNC_TABLE_x 0, xx

int main() { 
    printf("%s\n", WJR_PP_STR((WJR_PP_GET_FUNC(x))));
    return 0;
}
