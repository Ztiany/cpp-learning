set(
        public_src
        path.cpp
        _public.cpp
)

# Clion 的 bug，识别不到下面方式添加的 event_dispatcher_epoll。
#if (EPOLL_EXISTS)
#    MESSAGE("include epoll")
#    list(APPEND ${yolanda_lib} event_dispatcher_epoll.c)
#endif ()

add_library(public_lib ${public_src})
target_link_libraries(public_lib pthread)

install(TARGETS public_lib DESTINATION lib)