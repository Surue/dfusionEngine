#source files
List(APPEND SOURCE_NAMES
	"engine"
	"debug"
	"graphics"
	"inputs"
	"utility"
)

List(APPEND DFE_CORE_DIRS)

macro(SetupSources sourceName)
	file(GLOB_RECURSE LOCAL_SOURCES ${sourceName}/src/*.cpp)
	file(GLOB_RECURSE LOCAL_INCLUDES ${sourceName}/include/*.h)

	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/${sourceName}/include" PREFIX "${sourceName}" FILES ${LOCAL_INCLUDES})
	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/${sourceName}/src" PREFIX "${sourceName}" FILES ${LOCAL_SOURCES})

	List(APPEND DFE_DIR ${LOCAL_SOURCES} ${LOCAL_INCLUDES})

	List(APPEND DFE_CORE_DIRS ${DFE_DIR})
endmacro()

foreach(sourceName IN LISTS SOURCE_NAMES)
	SetupSources(${sourceName})
endforeach()

#Create Library
add_library(DFE_CORE STATIC ${DFE_CORE_DIRS})

set_target_properties (DFE_CORE PROPERTIES FOLDER DFE)

#Add subfolders to library
foreach(sourceName IN LISTS SOURCE_NAMES)
	target_include_directories(DFE_CORE PUBLIC "${sourceName}/include/")
endforeach()

#Common
target_link_libraries(DFE_CORE PUBLIC DFE_Common)

#SDL 2
find_package(SDL2 REQUIRED)
target_include_directories(DFE_CORE PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(DFE_CORE PUBLIC ${SDL2_LIBRARIES})

add_custom_command(TARGET DFE_CORE POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${CMAKE_SOURCE_DIR}/externals/SDL2-2.0.16/lib/x64/SDL2.dll"
         $<TARGET_FILE_DIR:DFE_Core>)

#Vulkan
find_package(Vulkan REQUIRED)
target_include_directories(DFE_CORE PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(DFE_CORE PUBLIC ${Vulkan_LIBRARIES})
