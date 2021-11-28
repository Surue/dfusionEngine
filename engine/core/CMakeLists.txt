#source files
file(GLOB_RECURSE DFE_ENGINE_SRC engine/src/*.cpp engine/include/*.h)
file(GLOB_RECURSE DFE_DEBUG_SRC debug/src/*.cpp debug/include/*.h)
file(GLOB_RECURSE DFE_GRAPHICS_SRC graphics/src/*.cpp graphics/include/*.h)
file(GLOB_RECURSE DFE_INPUTS_SRC inputs/src/*.cpp inputs/include/*.h)

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/ecs" PREFIX "ECS" FILES ${Alloy_ECS_SRC})
source_group("Engine" FILES ${DFE_ENGINE_SRC})
source_group("Debug" FILES ${DFE_DEBUG_SRC})
source_group("Graphics" FILES ${DFE_GRAPHICS_SRC})
source_group("Inputs" FILES ${DFE_INPUTS_SRC})

List(APPEND DFE_SRC
		${DFE_ENGINE_SRC}
		${DFE_DEBUG_SRC}
		${DFE_GRAPHICS_SRC}
		${DFE_INPUTS_SRC}
)


#Create Library
add_library(DFE_Core STATIC ${DFE_SRC})

set_target_properties (DFE_Core PROPERTIES FOLDER DFE)

#Add subfolders to library
target_include_directories(DFE_Core PUBLIC "engine/include/")
target_include_directories(DFE_Core PUBLIC "debug/include/")
target_include_directories(DFE_Core PUBLIC "graphics/include/")
target_include_directories(DFE_Core PUBLIC "inputs/include/")

#Comon
target_link_libraries(DFE_Core PUBLIC DFE_Common)

#SDL 2
find_package(SDL2 REQUIRED)
target_include_directories(DFE_Core PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(DFE_Core PUBLIC ${SDL2_LIBRARIES})

#Vulkan
find_package(Vulkan REQUIRED)
target_include_directories(DFE_Core PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(DFE_Core PUBLIC ${Vulkan_LIBRARIES})
