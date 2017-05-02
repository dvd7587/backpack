cmake_minimum_required(VERSION 2.8)


if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)


set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/archive/archive.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/archive/bufferarchive.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/archive/jsonarchive.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/archive/archivable.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/serializable.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/example/foo.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/example/bar.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/example/baz.h
                 ${CMAKE_CURRENT_SOURCE_DIR}/example/fred.h)

set(SOURCES_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/archive/bufferarchive.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/backpack/archive/jsonarchive.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/example/foo.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/example/bar.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/example/baz.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/example/fred.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party ${CMAKE_CURRENT_SOURCE_DIR}/lib)

project(BackPack)
add_executable(${PROJECT_NAME} "example/main.cpp" ${HEADER_FILES} ${SOURCES_SRC})
