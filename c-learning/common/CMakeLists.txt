set(
        public_src
        path.c
        data.c
)

if (EPOLL_EXISTS)
    MESSAGE("include epoll")
else ()
    MESSAGE("no epoll")
endif ()

add_library(alien ${public_src})
target_link_libraries(alien pthread)

install(TARGETS alien DESTINATION lib)