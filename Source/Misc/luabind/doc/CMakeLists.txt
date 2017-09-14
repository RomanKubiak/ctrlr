# Embedded build for LuaBind
# 2009-2011 Ryan Pavlik <rpavlik@iastate.edu>
# http://academic.cleardefinition.com/
# Iowa State University HCI Graduate Program/VRAC

set(SOURCES
    conf.py
    acknowledgments.rst
    basic-usage.rst
    build-options.rst
    building.rst
    classes.rst
    errors.rst
    exceptions.rst
    faq.rst
    functions.rst
    impl-notes.rst
    index.rst
    intro.rst
    issues.rst
    lua-classes.rst
    object.rst
    policies.rst
    scopes.rst
    split-registration.rst
    userdefined-converters.rst
    policies/adopt.rst
    policies/copy.rst
    policies/dependency.rst
    policies/discard_result.rst
    policies/out_value.rst
    policies/pure_out_value.rst
    policies/raw.rst
    policies/return_reference_to.rst
    policies/return_stl_iterator.rst
    policies/yield.rst)

    
if (WIN32)
    list (APPEND SOURCES make.bat)
    set(SPHINX_CMD "${CMAKE_CURRENT_BINARY_DIR}/make.bat" html)
else()
    list (APPEND SOURCES Makefile)
    set(SPHINX_CMD make html)
endif()

set(SOURCES_COPIED)
foreach(SOURCE ${SOURCES})
    set(CURRENT_SOURCE_O "${CMAKE_CURRENT_BINARY_DIR}/${SOURCE}")
    add_custom_command(OUTPUT ${CURRENT_SOURCE_O}
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}" ${CURRENT_SOURCE_O}
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}"
        COMMENT "Copying ${SOURCE}")
    list(APPEND SOURCES_COPIED ${CURRENT_SOURCE_O})
endforeach()

include(GetGitRevisionDescription.cmake)
git_describe(GIT_DESCRIPTION)
if(GIT_DESCRIPTION)
    string(REGEX REPLACE "^v" "" DOCS_VERSION "${GIT_DESCRIPTION}")
else()
    set(DOCS_VERSION "${CPACK_PACKAGE_VERSION}")
endif()

configure_file(git_version.in "${CMAKE_CURRENT_BINARY_DIR}/git_version")
list(APPEND SOURCES "${CMAKE_CURRENT_BINARY_DIR}/git_version.py")

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/_build/"
    COMMAND ${SPHINX_CMD}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS ${SOURCES_COPIED}
    VERBATIM
    COMMENT "Generating HTML documentation with sphinx makefile/script.")
add_custom_target(doc DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/_build/")


