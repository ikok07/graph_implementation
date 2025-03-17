cmake_minimum_required(VERSION 3.30)
project(graph_implementation C)

set(CMAKE_C_STANDARD 11)

include_directories(./lib/include)

file(GLOB LIB_SOURCES "lib/src/*.c")

add_executable(graph_implementation main.c
        graph.c
        graph.h
        ${LIB_SOURCES}
        lib/src/queue.c
        lib/include/queue.h
        lib/src/utils.c
        lib/include/utils.h
)
