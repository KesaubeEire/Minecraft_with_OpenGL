cmake_minimum_required(VERSION 3.13)
project(MineCraft_OpenGL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES)
set(HEADER_FILES
        GLAD/src/glad.c
        dependencies/Camera.h
        dependencies/shader.h
        dependencies/filesystem.h
        dependencies/freetype/freetype.h
        )

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

include_directories(include)


#Include library files
include_directories(GLAD/include)
include_directories(glm/include)

#Copy src to Build directory
file(COPY resources DESTINATION ${dir}/build)
file(COPY shaders DESTINATION ${dir}/build)
file(COPY MC_Resources DESTINATION ${dir}/build)
file(COPY MC_Shaders DESTINATION ${dir}/build)


#Add deps
add_subdirectory(dependencies)


#Add Exe
add_executable(L_0_6 OldRef/L_0_6_BeforeTransform.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_0_6 glfw)

add_executable(L_0_1-6 OldRef/L_0_1-6_BeforeTransform.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_0_1-6 glfw)

add_executable(L_0_7 OldRef/L_0_7_Transform.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_0_7 glfw)

add_executable(L_0_8 OldRef/L_0_8_Axis.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_0_8 glfw)

add_executable(L_0_9 OldRef/L_0_9_Camera.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_0_9 glfw)

add_executable(L_1_0 OldRef/L_1_0_ColorInit.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_1_0 glfw)

add_executable(L_1_1 OldRef/L_1_1_BaseLighting.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_1_1 glfw)

add_executable(L_1_2_Materials OldRef/L_1_2_Materials.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_1_2_Materials glfw)

add_executable(L_1_3_LightingMaps OldRef/L_1_3_LightingMaps.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_1_3_LightingMaps glfw)

add_executable(L_1_4_LightCasters OldRef/L_1_4_LightCasters.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_1_4_LightCasters glfw)

add_executable(L_1_5_MultipleLights OldRef/L_1_5_MultipleLights.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(L_1_5_MultipleLights glfw)

#====================Upper is OpenGL-Learning  Version
#====================Lower is MineCraft-OpenGL Version

add_executable(MCOG_001 MC_Src/BaseStage.cpp ${SOURCE_FILES} ${HEADER_FILES} MC_Src/map_generate/map_generate.h)
target_link_libraries(MCOG_001 glfw)

