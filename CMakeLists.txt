# Force CMake version 3.1 or above
cmake_minimum_required (VERSION 3.1)

# This project has the name: heatEquation
project (heatEquation)

# Create an executable named 'heatEquation' from the source file 'heatEquation'
include_directories(src)
add_executable(heatEquation src/main.cxx src/heat.hxx src/vector.hxx src/matrix.hxx src/cg.hxx)

# Define C++14 standard
set_property(TARGET heatEquation PROPERTY CXX_STANDARD 14)

# Add test called "heatEquation-test" based on the executable "heatEquation"
add_test (heatEquation-test heatEquation)
