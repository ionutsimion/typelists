cmake_minimum_required(VERSION 3.21)

project(
        PiTypeLists
        VERSION 1.0.0
        DESCRIPTION "Enhances the use of variadic templates"
        LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.2.1
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/contrib")

add_library(PiTypeLists INTERFACE include/typelists.hxx include/tl_matching_strategy.hxx include/tl_constants.hxx include/tl_find.hxx include/tl_count.hxx)
add_library(pi::TypeLists ALIAS PiTypeLists)

target_include_directories(PiTypeLists INTERFACE include)
target_compile_features(PiTypeLists INTERFACE cxx_std_20)

if (MSVC)
    target_compile_options(PiTypeLists INTERFACE /W4 /WX /sdl)
else()
    target_compile_options(PiTypeLists INTERFACE -Werror -Wall -Wextra -pedantic)
endif()

add_executable(tests tests/main.cxx tests/main.cxx tests/find.cxx tests/count.cxx)
target_link_libraries(tests PRIVATE PiTypeLists Catch2::Catch2)
target_include_directories(tests PRIVATE ${Catch2_INCLUDE_DIRS})
target_compile_features(tests PRIVATE cxx_std_20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(tests PRIVATE /Od /MDd)
    else()
        target_compile_options(tests PRIVATE -O0 -g)
    endif()
else()
    if (MSVC)
        target_compile_options(tests PRIVATE /O2 /MD)
    else()
        target_compile_options(tests PRIVATE -O3)
    endif()
endif()

include(CTest)
include(Catch)
catch_discover_tests(tests)
