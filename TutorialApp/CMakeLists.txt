cmake_minimum_required(VERSION 3.0.0)
project(TutorialApp)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW glfw3)
find_package(OpenGL)

if(${GLFW_FOUND})
add_executable(
	TutorialApp
	include/Application.hpp
	include/VertexLayout.h
	include/OGL.h
	include/VertexBuffer.h
	include/ogldev_math_3d.h
	include/ogldev_types.h
	include/ShadersProgram.h
	include/AttributeHelper.h
	include/ModelTrans.h
	include/Camera.h
	include/CameraController.h
	include/UniformHelper.h
	include/IndexBuffer.h
	include/stb_image.h
	include/Texture.h
	include/ResourceManager.h
	include/Engine.h
	include/Pool.h
	include/RenderingQueue.h
	include/RenderPacket.h
	include/ResourceManager.h
	include/TextureList.h
	include/UniformList.h
	include/Terrain.h
	include/HeightMap.h
	include/StbHelper.h
	src/main.cpp
	src/Application.cpp
	src/VertexLayout.cpp
	src/VertexBuffer.cpp
	src/ShadersProgram.cpp
	src/AttributeHelper.cpp
	src/ModelTrans.cpp
	src/Camera.cpp
	src/CameraController.cpp
	src/math_3d.cpp
	src/ogldev_util.cpp
	src/UniformHelper.cpp
	src/IndexBuffer.cpp
	src/Texture.cpp
	src/ResourceManager.cpp
	src/Engine.cpp
	src/RenderingQueue.cpp
	src/RenderPacket.cpp
	src/TextureList.cpp
	src/UniformList.cpp
	src/Terrain.cpp
	src/HeightMap.cpp
	src/StbHelper.cpp
	shaders/shader.vs
	shaders/shader.fs
	textures/bricks.jpeg
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
