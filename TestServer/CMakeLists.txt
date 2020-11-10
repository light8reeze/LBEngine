cmake_minimum_required(VERSION 3.8.2)

project(TestServer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

set(BOOST_DIR "C:/boost_1_70_0")

INCLUDE_DIRECTORIES(include Src/Inc)
INCLUDE_DIRECTORIES(include ../LBServer/Src/Inc)
INCLUDE_DIRECTORIES(include ../LBUtility/Src/Inc)
INCLUDE_DIRECTORIES(include BOOST_DIRECTORY)

add_executable(TestServer
  AppDefines.h
  CTestServer.cpp
  CTestServer.h
  main.cpp
)
# Output file name
set_target_properties(TestServer
  PROPERTIES
  OUTPUT_NAME_DEBUG TestServerD_x64
  OUTPUT_NAME_RELEASE TestServer_x64
)

# Preprocessor definitions
target_compile_definitions(TestServer PRIVATE
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
  target_compile_options(TestServer PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(TestServer PRIVATE
    ""
  )
endif ()
