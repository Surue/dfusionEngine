#source files
file(GLOB_RECURSE DFE_ENGINE_SRC engine/src/*.cpp engine/include/*.h)
file(GLOB_RECURSE DFE_DEBUG_SRC debug/src/*.cpp debug/include/*.h)

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/ecs" PREFIX "ECS" FILES ${Alloy_ECS_SRC})
source_group("Engine" FILES ${DFE_ENGINE_SRC})
source_group("Debug" FILES ${DFE_DEBUG_SRC})

List(APPEND DFE_SRC
		${DFE_ENGINE_SRC}
		${DFE_DEBUG_SRC}
)

#SDL 2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#Create Library
add_library(DFE_Core STATIC ${DFE_SRC})

set_target_properties (DFE_Core PROPERTIES FOLDER DFE)

#Add subfolders to library
target_include_directories(DFE_Core PUBLIC "engine/include/")
target_include_directories(DFE_Core PUBLIC "debug/include/")

#Link SDL2 to core library
target_link_libraries(DFE_Core ${SDL2_LIBRARIES})
