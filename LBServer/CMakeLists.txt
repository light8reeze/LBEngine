cmake_minimum_required(VERSION 3.8.2)

project(LBServer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

set(LBENGINE_OUT_DIRECTORY "/bin")

# Compile options
include(../Build/CMake/CompileOptions.cmake)

INCLUDE_DIRECTORIES(Src/Inc)
INCLUDE_DIRECTORIES(../LBUtility/Src/Inc)
INCLUDE_DIRECTORIES(BOOST_DIRECTORY)

# Source
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Inc/*.h)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Cpp/*.cpp)

add_library(LBServer SHARED
    ${SOURCES}
)

# Set postfix by configuration
if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
   set(CONFIGURATUON_POSTFIX "D")
else(CMAKE_CONFIGURATION_TYPES STREQUAL "Release")
   set(CONFIGURATUON_POSTFIX "")
endif()

set(OUTPUT_FILE_NAME "LBServer${CONFIGURATUON_POSTFIX}_x64")

# Preprocessor definitions
target_compile_definitions(LBServer PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;X64;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;X64;NDEBUG;_CONSOLE>
)

# SDL check
if (MSVC)
	target_compile_options(TestServer PRIVATE
	  "$<$<CONFIG:Debug>:/sdl>"
	  "$<$<CONFIG:Release>:/sdl>"
	)
endif ()

# Minimal rebuild
if (MSVC)
  target_compile_options(LBServer PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(LBServer PRIVATE
    ""
  )
endif ()