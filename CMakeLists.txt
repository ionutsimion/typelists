cmake_minimum_required(VERSION 3.23)

project(
        PiTypeLists
        VERSION 0.1.4
        DESCRIPTION "Enhances the use of variadic templates"
        LANGUAGES CXX
)

include(cmake/options.cmake)
include(cmake/dependencies.cmake)

enable_testing()

add_library(PiTypeLists INTERFACE include/typelists/typedecl.hxx include/typelists/typelists.hxx include/typelists/struct.hxx
        include/typelists/internal/tl_matching_strategy.hxx include/typelists/internal/tl_constants.hxx include/typelists/internal/tl_find.hxx
        include/typelists/internal/tl_count.hxx include/typelists/internal/tl_get.hxx include/typelists/internal/td_typedecl_base.hxx)
add_library(pi::TypeLists ALIAS PiTypeLists)

target_include_directories(PiTypeLists INTERFACE include)
target_compile_features(PiTypeLists INTERFACE cxx_std_23)

if (MSVC)
    target_compile_options(PiTypeLists INTERFACE /W4 /WX /sdl)
else()
    target_compile_options(PiTypeLists INTERFACE -Werror -Wall -Wextra -pedantic)
endif()

if(TYPELISTS_BUILD_TESTS)
    add_subdirectory(tests)
endif()
