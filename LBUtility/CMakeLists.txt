cmake_minimum_required(VERSION 3.8.2)

project(LBUtility)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

INCLUDE_DIRECTORIES(include Src/Inc)

# Set extend by compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   set(OUTPUT_EXTEND "so")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   set(OUTPUT_EXTEND "dll")
endif()

if(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
   set(CONFIGURATUON_POSTFIX "D")
else(CMAKE_CONFIGURATION_TYPES STREQUAL "Release")
   set(CONFIGURATUON_POSTFIX "")
endif()

set(OUTPUT_FILE_NAME "${CMAKE_PROJECT_NAME}${CONFIGURATUON_POSTFIX}_x64.${OUTPUT_EXTEND}")

add_library(LBUtility SHARED
  Src/Cpp/LBBuffer.cpp
  Src/Cpp/LBLocker.cpp
  Src/Cpp/LBTime.cpp
  Src/Cpp/LBUtility.cpp
  Src/Cpp/LBEncryption.cpp
  Src/Inc/LBBuffer.h
  Src/Inc/LBCharBase.h
  Src/Inc/LBEncryption.h
  Src/Inc/LBFile.h
  Src/Inc/LBLocker.h
  Src/Inc/LBPool.h
  Src/Inc/LBProbability.h
  Src/Inc/LBQueue.h
  Src/Inc/LBRandom.h
  Src/Inc/LBString.h
  Src/Inc/LBTime.h
  Src/Inc/LBUtility.h
)
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
target_compile_options(LBUtility PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(LBUtility PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(LBUtility PRIVATE
    ""
  )
endif ()