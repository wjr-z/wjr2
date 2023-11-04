#ifndef WJR_CONTAINER_LIST_HPP__
#define WJR_CONTAINER_LIST_HPP__

#include <memory>

#include <wjr/preprocessor.hpp>

// TODO

namespace wjr {

struct list_node {
    list_node() = default;
    ~list_node() = default;
    list_node(const list_node &) = delete;
    list_node &operator=(const list_node &) = delete;

    list_node *next;
    list_node *prev;
};

} // namespace wjr

#endif // WJR_CONTAINER_LIST_HPP__