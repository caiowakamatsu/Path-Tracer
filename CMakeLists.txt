cmake_minimum_required(VERSION 3.15)
project(PathTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_C_FLAGS "-O3")
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-fopenmp -fsanitize=undefined -pthread")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})

add_executable(Path_Tracer main.cpp File.cpp File.h Vector3.cpp Vector3.h World.cpp World.h Ray.cpp Ray.h Shape.h HitRecord.h Sphere.cpp Sphere.h Camera.cpp Camera.h Material.h ColourCache.h Texture.cpp Texture.h DynMat.cpp DynMat.h Lambertian.cpp Lambertian.h Glass.cpp Glass.h Triangle.cpp Triangle.h)
target_link_libraries(Path_Tracer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${PNG_LIBRARY} ${PNG_INCLUDE_DIR} ${ZLIB_LIBRARIES})