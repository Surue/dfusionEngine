#source files
file(GLOB_RECURSE DFE_SHADER_SRC shaders/*.vert shaders/*.frag)

source_group("Shaders" FILES ${DFE_SHADER_SRC})

List(APPEND DFE_SRC
        ${DFE_SHADER_SRC}
        )

add_custom_target(
        DFE_Resources
        SOURCES ${DFE_SRC})
set_target_properties(DFE_Resources PROPERTIES FOLDER DFE)