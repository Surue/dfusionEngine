cmake_minimum_required(VERSION 3.16)
project(dfusionEngine)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS On)


#Common
set(DFE_COMMON_DIR "${CMAKE_SOURCE_DIR}/engine/common/" CACHE INTERNAL "")
add_subdirectory(${DFE_COMMON_DIR})

#Core
set(DFE_RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources/" CACHE INTERNAL "")
add_subdirectory(${DFE_RESOURCES_DIR})

#Core
set(DFE_CORE_DIR "${CMAKE_SOURCE_DIR}/engine/core/" CACHE INTERNAL "")
add_subdirectory(${DFE_CORE_DIR})

#Projects
#set(DFE_PROJECT_DIR "${CMAKE_SOURCE_DIR}/projects" CACHE INTERNAL "")
#add_subdirectory(${DFEPROJECT_DIR})

#Engine
add_executable(dfusionEngine main.cpp)

target_link_libraries(dfusionEngine PRIVATE DFE_Core)

