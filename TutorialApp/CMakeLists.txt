cmake_minimum_required(VERSION 3.0.0)
project(TutorialApp)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW glfw3)
find_package(OpenGL)

if(${GLFW_FOUND})
add_executable(
	TutorialApp
	src/main.cpp
	src/Application.cpp
	src/VertexLayout.cpp
	src/VertexBuffer.cpp
	src/shader.cpp
	include/Application.hpp
	include/VertexLayout.h
	include/OGL.h
	include/VertexBuffer.h
	include/ogldev_math_3d.h
	include/shader.h
	shaders/shader.vs
	shaders/shader.fs
)



target_include_directories(TutorialApp PUBLIC 
${GLFW_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/shaders
)
target_link_directories(TutorialApp PUBLIC ${GLFW_LIBRARY_DIRS})
target_link_libraries(TutorialApp PUBLIC ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} )
target_link_libraries(TutorialApp PUBLIC "-framework OpenGL")

else()
message(FATAL_ERROR "Unable to find glfw3, tests are disabled!")
endif()
