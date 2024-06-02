cmake_minimum_required(VERSION 3.27)
project(ParticleProject)

# Find OpenGL
find_package(OpenGL REQUIRED)


find_package(GLUT REQUIRED)

# Add GLFW library
find_package(glfw3 REQUIRED)

# Include GLFW headers
include_directories(${GLFW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# Add your source files
add_executable(ParticleProject
        Particle.cpp
        Particle.h
        SlopeFieldRunner.cpp
        Vector2.h
        SlopeFieldRunner.h
        CoulombSimulation.cpp
        CoulombSimulation.h
        main.cpp
        PhasePlot.cpp
        PhasePlot.h)

find_package(glm CONFIG REQUIRED)
target_link_libraries(ParticleProject PRIVATE ${OPENGL_LIBRARIES} glfw ${GLUT_LIBRARIES} glm::glm)





set(CMAKE_CXX_STANDARD 17)


