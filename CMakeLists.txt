cmake_minimum_required(VERSION 3.15)
project(PathTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_C_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "-g")

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
add_subdirectory(extern/bvh)

add_executable(Path_Tracer src/main.cpp src/File.cpp src/File.h src/Vector3.cpp src/Vector3.h src/World.cpp src/World.h src/Ray.cpp src/Ray.h src/HitRecord.h src/Camera.cpp src/Camera.h src/Material.h src/ColourCache.h src/Texture.cpp src/Texture.h src/DynMat.cpp src/DynMat.h src/Lambertian.cpp src/Lambertian.h src/Glass.cpp src/Glass.h src/Triangle.cpp src/Triangle.h src/RenderStack.h src/NormalMat.cpp src/NormalMat.h src/Window.cpp src/Window.h src/Vertex.cpp src/Vertex.h src/ModelLoader.cpp src/ModelLoader.h)

target_link_directories(Path_Tracer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/extern/bin/)
target_include_directories(Path_Tracer PUBLIC bvh ${OPENGL_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} glfw)
target_link_libraries(Path_Tracer PUBLIC ${OPENGL_LIBRARIES} ${PNG_LIBRARY} ${PNG_INCLUDE_DIR} ${ZLIB_LIBRARIES} glfw bvh)