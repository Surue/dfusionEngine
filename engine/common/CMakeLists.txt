#source files
file(GLOB_RECURSE DFE_MATH_SRC math/src/*.cpp math/include/*.h)

source_group("Maths" FILES ${DFE_MATH_SRC})

List(APPEND DFE_SRC
        ${DFE_MATH_SRC}
        )

add_library(DFE_Common STATIC ${DFE_SRC})

set_target_properties (DFE_Common PROPERTIES FOLDER DFE)

target_include_directories(DFE_Common PUBLIC "math/include/")

