cmake_minimum_required(VERSION 3.8.2)

project(LBServer)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

set(BOOST_DIRECTORY "C:/boost_1_70_0")
set(LBENGINE_OUT_DIRECTORY "/bin")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(FILE_EXTENSION "dll")
else(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(FILE_EXTENSION "so")
endif()

INCLUDE_DIRECTORIES(include Src/Inc)
INCLUDE_DIRECTORIES(include ../LBUtility/Src/Inc)
INCLUDE_DIRECTORIES(include BOOST_DIRECTORY)

add_library(LBServer
  Src/Cpp/LBAcceptor.cpp
  Src/Cpp/LBFactory.cpp
  Src/Cpp/LBGameObject.cpp
  Src/Cpp/LBIOContext.cpp
  Src/Cpp/LBLogger.cpp
  Src/Cpp/LBLogProcessor.cpp
  Src/Cpp/LBUdpHandler.cpp
  Src/Cpp/LBTcpHandler.cpp
  Src/Cpp/LBSender.cpp
  Src/Cpp/LBSendPool.cpp
  Src/Cpp/LBServer.cpp
  Src/Cpp/LBSession.cpp
  Src/Cpp/LBSocket.cpp
  Src/Cpp/LBTimer.cpp
  Src/Cpp/LBUdpObject.cpp
  Src/Cpp/LBUdpSession.cpp
  Src/Inc/LBAcceptor.h
  Src/Inc/LBBoostConfig.h
  Src/Inc/LBConfig.h
  Src/Inc/LBError.h
  Src/Inc/LBFactory.h
  Src/Inc/LBGameObject.h
  Src/Inc/LBGameServer.h
  Src/Inc/LBIOContext.h
  Src/Inc/LBLogger.h
  Src/Inc/LBLogProcessor.h
  Src/Inc/LBSender.h
  Src/Inc/LBSendPool.h
  Src/Inc/LBServer.h
  Src/Inc/LBSession.h
  Src/Inc/LBShard.h
  Src/Inc/LBShardObject.h
  Src/Inc/LBSocket.h
  Src/Inc/LBTcpHandler.h
  Src/Inc/LBTimer.h
  Src/Inc/LBUdpHandler.h
  Src/Inc/LBUdpObject.h
  Src/Inc/LBUdpSession.h
)
# Output file name
set_target_properties(LBServer
  PROPERTIES
  OUTPUT_NAME_DEBUG LBServerD
  OUTPUT_NAME_RELEASE LBServer
)

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
