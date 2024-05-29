cmake_minimum_required(VERSION 3.27)
project(ParticleProject)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add GLFW library
find_package(glfw3 REQUIRED)

# Include GLFW headers
include_directories(${GLFW_INCLUDE_DIRS})

# Add your source files
add_executable(ParticleProject main.cpp)

find_package(glm CONFIG REQUIRED)
target_link_libraries(ParticleProject PRIVATE glm::glm)



# Link GLFW and OpenGL libraries
target_link_libraries(ParticleProject PRIVATE ${OPENGL_LIBRARIES} glfw)

set(CMAKE_CXX_STANDARD 17)


