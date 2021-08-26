# EGE Link Test

cmake_minimum_required(VERSION 3.13)
project(EGE_LinkTest)

set(CMAKE_BUILD_TYPE Debug)

set(EGE_ROOT ${CMAKE_SOURCE_DIR}/../EGE/build-${CMAKE_BUILD_TYPE}/root)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${EGE_ROOT})
message(${CMAKE_PREFIX_PATH})
set(CMAKE_INSTALL_PREFIX root)
find_package(EGE REQUIRED)
include("${EGE_ROOT}/cmake/EGEUtils.cmake")

macro(add_example name sources ege_deps)
    set(sources_with_dir "")
    foreach(source ${sources})
        list(APPEND sources_with_dir src/${name}/${source})
    endforeach()

    set(ege_deps_with_ege "")
    foreach(dep ${ege_deps})
        list(APPEND ege_deps_with_ege ege-${dep})
    endforeach()

    set(target_name ${name})
    add_executable(${target_name} ${sources_with_dir})
    target_link_libraries(${target_name} ${ege_deps_with_ege})
    target_include_directories(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/${name})
    install(TARGETS ${target_name} RUNTIME DESTINATION ".")

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${name}/res)
        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/${name}/res DESTINATION ".")
    endif()
endmacro()

add_example(first-project "main.cpp" gui)
