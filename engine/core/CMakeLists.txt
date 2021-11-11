#source files
file(GLOB_RECURSE DFE_ENGINE_SRC engine/src/*.cpp engine/include/*.h)

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/ecs" PREFIX "ECS" FILES ${Alloy_ECS_SRC})
source_group("Engine" FILES ${DFE_ENGINE_SRC})

List(APPEND DFE_SRC
		${DFE_ENGINE_SRC})

add_library(DFE_Core STATIC ${DFE_SRC})

set_target_properties (DFE_Core PROPERTIES FOLDER DFE)

target_include_directories(DFE_Core PUBLIC "engine/include/")
