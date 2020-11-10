cmake_minimum_required(VERSION 3.8.2)

project(LBClient)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_library(LBClient SHARED
  Src/Cpp/LBClient.cpp
  Src/Cpp/LBClientHandler.cpp
  Src/Cpp/LBTcpClient.cpp
  Src/Inc/LBClient.h
  Src/Inc/LBClientHandler.h
  Src/Inc/LBTcpClient.h
)
# Output file name
set_target_properties(LBClient
  PROPERTIES
  OUTPUT_NAME_DEBUG LBClientD_x64
  OUTPUT_NAME_RELEASE LBClient_x64
)

# Additional include directories
set_property(TARGET LBClient
  APPEND PROPERTY INCLUDE_DIRECTORIES
  $<$<CONFIG:Debug>:
    C:\boost_1_70_0>
  $<$<CONFIG:Release>:
    C:\boost_1_70_0>
)

# Preprocessor definitions
target_compile_definitions(LBClient PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;X64;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;X64;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(LBClient PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(LBClient PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(LBClient PRIVATE
    ""
  )
endif ()
