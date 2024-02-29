cmake_minimum_required(VERSION 3.5)

project(03.homework)

set(SOURCES 
	high_scores.cpp
	theGame.cpp
)

set(HEADERS
	theGame.h
)

add_executable(GuessTheNumber ${SOURCES} ${HEADERS})


target_compile_features(GuessTheNumber PUBLIC cxx_std_17)
set_target_properties(GuessTheNumber PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(GuessTheNumber PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(MSVC)
        target_compile_options(GuessTheNumber PUBLIC /W4 /WX)
else()
        target_compile_options(GuessTheNumber PUBLIC -Wall -Wextra -Werror -pedantic)
endif()