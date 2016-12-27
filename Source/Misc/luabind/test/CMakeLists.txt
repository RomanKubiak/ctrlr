# Build for LuaBind
# Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

# ls test_*.cpp | sort | sed -e 's/test_//' -e 's/.cpp//' -e 's/^/    /' | grep -v "has_get_pointer"
# This command removes has_get_pointer because it is a compile-only test
set(TESTS
    abstract_base
    adopt
    adopt_wrapper
    attributes
    automatic_smart_ptr
    back_reference
    builtin_converters
    class_info
    collapse_converter
    const
    construction
    create_in_thread
    def_from_base
    destruction
    dynamic_type
    exception_handlers
    exceptions
    extend_class_in_lua
    free_functions
    function_converter
    function_introspection
    function_object
    function_overload_overflow
    held_type
    implicit_cast
    implicit_raw
    intrusive_ptr
    iterator
    lua_classes
    null_pointer
    object
    operators
    package_preload
    policies
    private_destructors
    properties
    scope
    separation
    set_instance_value
    shadow
    shared_ptr
    simple_class
    smart_ptr_attributes
    super_leak
    table
    tag_function
    typetraits
    unchecked
    unsigned_int
    user_defined_converter
    value_wrapper
    vector_of_object
    virtual_inheritance
    yield)

add_library(test_main STATIC
    main.cpp
    test.hpp
    # These tests consist only of compile time asserts and define no test_main
    # function:
    test_has_get_pointer.cpp)

if (BUILD_SHARED_LIBS AND MSVC)
    add_custom_command(TARGET test_main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:luabind> $<TARGET_FILE_DIR:testmain>
        COMMENT "Copying DLL...")
endif()

foreach(test ${TESTS})
    add_executable(test_${test} test_${test}.cpp)
    target_link_libraries(test_${test} test_main luabind)
    add_test(NAME ${test} COMMAND test_${test})
    set_property(TARGET test_${test} PROPERTY FOLDER "Tests")
endforeach()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND LUABIND_ENABLE_WARNINGS)
    set (priv_dtor_flags "-Wno-ctor-dtor-privacy")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(priv_dtor_flags "${priv_dtor_flags} -Wno-unused-member-function")
    endif()
    set_property(TARGET test_private_destructors
                 PROPERTY COMPILE_FLAGS "${priv_dtor_flags}")
    set_property(TARGET test_builtin_converters
                 PROPERTY COMPILE_FLAGS "-Wno-float-equal")
endif()

add_executable(benchmark "benchmark.cpp")
target_link_libraries(benchmark ${LUA_LIBRARIES} luabind)

option(LUABIND_BUILD_HEADER_TESTS "Try to compile every header in the luabind directory, excluding detail headers, in its own translation unit, to check for missing includes." OFF)

if(BUILD_TESTING AND LUABIND_BUILD_HEADER_TESTS)
    get_filename_component(BASE "${CMAKE_CURRENT_SOURCE_DIR}/../luabind" ABSOLUTE)
    foreach(HEADER ${APIHEADERS})
        get_filename_component(FULLHEADER "${HEADER}" ABSOLUTE)
        file(RELATIVE_PATH SHORTNAME "${BASE}" "${FULLHEADER}")
        string(REPLACE "/" "_" SHORTNAME "${SHORTNAME}")
        string(REPLACE ".hpp" "" SHORTNAME "${SHORTNAME}")
        set (targetname test_headercompile_${SHORTNAME})
        set (cppname "${CMAKE_CURRENT_BINARY_DIR}/${targetname}.cpp")
        configure_file(test_headercompile.cpp.in "${cppname}" @ONLY)
        add_executable(${targetname} ${cppname})
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND LUABIND_ENABLE_WARNINGS)
            # Clang complains about '#define LUABIND_TEST_HEADERCOMPILE'.
            set_property(TARGET ${targetname}
                    PROPERTY COMPILE_FLAGS "-Wno-unused-macros")
        endif()
        set_property(TARGET ${targetname} PROPERTY FOLDER "Tests/Headers")
        target_link_libraries(${targetname} luabind)
    endforeach()
endif()
