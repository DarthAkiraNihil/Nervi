cmake_minimum_required(VERSION 3.23)
project(Nervi)

file(GLOB SOURCES
        3rdparty/fmt/*.h
        )

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/fmt/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

add_subdirectory(3rdparty/fmt EXCLUDE_FROM_ALL)

add_executable(NerviTestMem kernel/storage/test.cpp ${SOURCES})
add_executable(NerviTestLexis kernel/lexis/test.cpp ${SOURCES})

target_link_libraries(NerviTestMem PRIVATE fmt::fmt-header-only)

