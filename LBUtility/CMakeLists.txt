cmake_minimum_required(VERSION 3.8.2)

project(LBUtility)
set(TARGET LBUtility)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)
    
set(LBENGINE_OUT_DIRECTORY "/bin")

INCLUDE_DIRECTORIES(Src/Inc)

# Compile options
include(../Build/CMake/CompileOptions.cmake)

# Source
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Inc/*.h)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Cpp/*.cpp)
    
add_library(LBUtility SHARED
    ${SOURCES}
)

# Set postfix by configuration
if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
   set(CONFIGURATUON_POSTFIX "D")
else(CMAKE_CONFIGURATION_TYPES STREQUAL "Release")
   set(CONFIGURATUON_POSTFIX "")
endif()

set(OUTPUT_FILE_NAME "LBUtility${CONFIGURATUON_POSTFIX}_x64")

# Output file name
set_target_properties(LBUtility
  PROPERTIES
  OUTPUT_NAME_DEBUG ${OUTPUT_FILE_NAME}
  OUTPUT_NAME_RELEASE ${OUTPUT_FILE_NAME}
)

# Preprocessor definitions
target_compile_definitions(LBUtility PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;X64;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;X64;NDEBUG;_CONSOLE>
)

# SDL check
if (MSVC)
target_compile_options(LBUtility PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)
endif()

# Minimal rebuild
if (MSVC)
  target_compile_options(LBUtility PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()