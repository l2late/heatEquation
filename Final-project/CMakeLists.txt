# Force CMake version 3.1 or above
cmake_minimum_required (VERSION 3.1)

# This project has the name: Final-project
project (Final-project)

# Create an executable named 'Final-project' from the source file 'Final-project'
add_executable(Final-project src/Final-project.cxx)

# Define C++11 standard
set_property(TARGET Final-project PROPERTY CXX_STANDARD 11)

# Add test called "Final-project-test" based on the executable "Final-project"
add_test (Final-project-test Final-project)

# Create an additional target for assignment submission
add_assignment(Final-project src/Final-project.cxx)
