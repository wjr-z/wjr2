#ifndef WJR_ATOMIC_HPP__
#define WJR_ATOMIC_HPP__

#include <atomic>

#include <wjr/type_traits.hpp>

#define WJR_ATOMIC_SLOW_DEFINE(name, types, var_header, func_body)                       \
    WJR_DEFINE_FUNC(                                                                     \
        (template <typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>    \
         static inline auto atomic_##name),                                              \
        types, (WJR_PP_VARS_N(var_header, WJR_PP_QUEUE_SIZE(types))), func_body)

#define WJR_ATOMIC_FAST_DEFINE(name, types, var_header, veris)                           \
    WJR_ATOMIC_SLOW_DEFINE(name, types, var_header, (noexcept {                          \
                               WJR_ATOMIC_VERIFY(veris);                                 \
                               return __atomic_##name(                                   \
                                   WJR_PP_VARS_N(ARG, WJR_PP_QUEUE_SIZE(types)));        \
                           }))

#define WJR_ATOMIC_VERIFY(veris)                                                         \
    WJR_PP_QUEUE_PUT(WJR_PP_QUEUE_TRANSFORM(veris, WJR_ATOMIC_VERIFY_IMPL))
#define WJR_ATOMIC_VERIFY_IMPL(ptr)                                                      \
    WJR_ASSERT(3, reinterpret_cast<::wjr::uintptr_t>(ptr) % sizeof(T) == 0,              \
               "Atomic operation used incorrectly aligned pointers");

namespace wjr {

WJR_ATOMIC_FAST_DEFINE(load_n, (T *, std::memory_order), ARG, ARG0);
WJR_ATOMIC_FAST_DEFINE(load, (T *, T *, std::memory_order), ARG, (ARG0, ARG1));
WJR_ATOMIC_FAST_DEFINE(store_n, (T *, T, std::memory_order), ARG, (ptr0));
WJR_ATOMIC_FAST_DEFINE(store, (T *, T *, std::memory_order), ARG, (ARG0, ARG1));
WJR_ATOMIC_FAST_DEFINE(exchange_n, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(exchange, (T *, T *, std::memory_order), ARG, (ARG0, ARG1));
WJR_ATOMIC_FAST_DEFINE(compare_exchange_n,
                       (T *, T *, T, bool, std::memory_order, std::memory_order), ARG,
                       (ARG0, ARG1));
WJR_ATOMIC_FAST_DEFINE(compare_exchange,
                       (T *, T *, T *, bool, std::memory_order, std::memory_order), ARG,
                       (ARG0, ARG1, ARG2));

WJR_ATOMIC_SLOW_DEFINE(compare_exchange_strong_n,
                       (T *, T *, T, std::memory_order, std::memory_order), ARG,
                       (noexcept {
                           WJR_ATOMIC_VERIFY((ARG0, ARG1));
                           return atomic_compare_exchange_n(ARG0, ARG1, ARG2, false, ARG3,
                                                            ARG4);
                       }));
WJR_ATOMIC_SLOW_DEFINE(compare_exchange_weak_n,
                       (T *, T *, T, std::memory_order, std::memory_order), ARG,
                       (noexcept {
                           WJR_ATOMIC_VERIFY((ARG0, ARG1));
                           return atomic_compare_exchange_n(ARG0, ARG1, ARG2, true, ARG3,
                                                            ARG4);
                       }));
WJR_ATOMIC_SLOW_DEFINE(compare_exchange_strong,
                       (T *, T *, T *, std::memory_order, std::memory_order), ARG,
                       (noexcept {
                           WJR_ATOMIC_VERIFY((ARG0, ARG1));
                           return atomic_compare_exchange(ARG0, ARG1, ARG2, false, ARG3,
                                                          ARG4);
                       }));
WJR_ATOMIC_SLOW_DEFINE(compare_exchange_weak,
                       (T *, T *, T *, std::memory_order, std::memory_order), ARG,
                       (noexcept {
                           WJR_ATOMIC_VERIFY((ARG0, ARG1));
                           return atomic_compare_exchange(ARG0, ARG1, ARG2, true, ARG3,
                                                          ARG4);
                       }));

WJR_ATOMIC_FAST_DEFINE(add_fetch, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(sub_fetch, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(and_fetch, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(xor_fetch, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(or_fetch, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(nand_fetch, (T *, T, std::memory_order), ARG, (ARG0));

WJR_ATOMIC_FAST_DEFINE(fetch_add, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(fetch_sub, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(fetch_and, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(fetch_xor, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(fetch_or, (T *, T, std::memory_order), ARG, (ARG0));
WJR_ATOMIC_FAST_DEFINE(fetch_nand, (T *, T, std::memory_order), ARG, (ARG0));

} // namespace wjr

#undef WJR_ATOMIC_VERIFY_IMPL
#undef WJR_ATOMIC_VERIFY
#undef WJR_ATOMIC_CONCAT_I
#undef WJR_ATOMIC_CONCAT
#undef WJR_ATOMIC_FAST_DEFINE
#undef WJR_ATOMIC_DEFINE_TYPE

#endif // WJR_ATOMIC_HPP__