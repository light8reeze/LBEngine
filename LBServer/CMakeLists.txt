cmake_minimum_required(VERSION 3.12.2)

project(LBServer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

set(BOOST_DIRECTORY C:\boost_1_70_0>)
set(LBENGINE_OUT_DIRECTORY \bin)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(FILE_EXTENSION "dll")
else(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(FILE_EXTENSION "so")
endif()

add_executable(LBServer
  Src/Cpp/CTestServer.cpp
  Src/Cpp/LBAcceptor.cpp
  Src/Cpp/LBFactory.cpp
  Src/Cpp/LBGameObject.cpp
  Src/Cpp/LBHandler.cpp
  Src/Cpp/LBIOContext.cpp
  Src/Cpp/LBManagedObject.cpp
  Src/Cpp/LBSender.cpp
  Src/Cpp/LBSendPool.cpp
  Src/Cpp/LBServer.cpp
  Src/Cpp/LBSession.cpp
  Src/Cpp/LBSessionManager.cpp
  Src/Cpp/LBSocket.cpp
  Src/Cpp/LBTimer.cpp
  Src/Cpp/main.cpp
  Src/Inc/CTestServer.h
  Src/Inc/LBAcceptor.h
  Src/Inc/LBBoostConfig.h
  Src/Inc/LBError.h
  Src/Inc/LBFactory.h
  Src/Inc/LBGameObject.h
  Src/Inc/LBGameServer.h
  Src/Inc/LBHandler.h
  Src/Inc/LBIOContext.h
  Src/Inc/LBManagedObject.h
  Src/Inc/LBSender.h
  Src/Inc/LBSendPool.h
  Src/Inc/LBServer.h
  Src/Inc/LBSession.h
  Src/Inc/LBSessionManager.h
  Src/Inc/LBShard.h
  Src/Inc/LBShardObject.h
  Src/Inc/LBSocket.h
  Src/Inc/LBTimer.h
)
# Output file name
set_target_properties(LBServer
  PROPERTIES
  OUTPUT_NAME_DEBUG LBServerD
  OUTPUT_NAME_RELEASE LBServer
)

# Additional include directories
set_property(TARGET LBServer
  APPEND PROPERTY INCLUDE_DIRECTORIES
  $<$<CONFIG:Debug>:
    BOOST_DIRECTORY
  $<$<CONFIG:Release>:
    BOOST_DIRECTORY
)

# Preprocessor definitions
target_compile_definitions(LBServer PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;X64;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;X64;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(LBServer PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

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
