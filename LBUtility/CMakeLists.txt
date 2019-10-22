cmake_minimum_required(VERSION 3.12.2)

project(LBUtility)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_library(LBUtility SHARED
  Src/Cpp/LBBuffer.cpp
  Src/Cpp/LBLocker.cpp
  Src/Cpp/LBTime.cpp
  Src/Cpp/LBUtility.cpp
  Src/Inc/LBBuffer.h
  Src/Inc/LBChar.h
  Src/Inc/LBCharBase.h
  Src/Inc/LBEncyption.h
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
  OUTPUT_NAME_DEBUG LBUtilityD_x64
  OUTPUT_NAME_RELEASE LBUtility_x64
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
