cmake_minimum_required(VERSION 3.5)
project(05.homework)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS
        max.h
        mean.h 
        pct.h 
        statistics.h 
        std.h
)

set(Execs
        pct.cpp
        std.cpp
        statistics.cpp
)


add_executable(statistics ${HEADERS} ${Execs})
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if(MSVC)
    target_compile_options(statistics PUBLIC /W4 /WX)
else()
    target_compile_options(statistics PUBLIC -Wall -Wextra -Werror -pedantic)
endif()