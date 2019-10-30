cmake_minimum_required(VERSION 3.0)

project (VST_SDK)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/public.sdk/source/vst2.x SOURCE_LIB)

					  
add_library(VST_SDK STATIC ${SOURCE_LIB})

target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public.sdk/source/vst2.x ${CMAKE_CURRENT_SOURCE_DIR}/ ${CMAKE_CURRENT_SOURCE_DIR}/public.sdk ${CMAKE_CURRENT_SOURCE_DIR}/pluginterfaces/vst2.x)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
