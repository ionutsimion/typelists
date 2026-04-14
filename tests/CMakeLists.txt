include(CTest)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)

add_executable(
        typelists_tests
        main.cxx
        find.cxx
        count.cxx
        get.cxx
        sandbox_npc.cxx
        toolbox.hxx
        sandbox_player.cxx
        typedecl_fundamental.cxx
        typedecl_final_class.cxx
        typedecl_class.cxx
        struct.cxx)

target_link_libraries(typelists_tests PRIVATE PiTypeLists Catch2::Catch2)
target_compile_features(typelists_tests PRIVATE cxx_std_23)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        target_compile_options(typelists_tests PRIVATE /Od /MDd)
    else()
        target_compile_options(typelists_tests PRIVATE -O0 -g)
    endif()
else()
    if (MSVC)
        target_compile_options(typelists_tests PRIVATE /O2 /MD)
    else()
        target_compile_options(typelists_tests PRIVATE -O3)
    endif()
endif()

catch_discover_tests(typelists_tests)
