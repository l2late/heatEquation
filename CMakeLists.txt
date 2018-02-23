# Force CMake version 3.1 or above
cmake_minimum_required (VERSION 3.1)

# This project has the name: heatEquation
project (heatEquation)

# Create an executable named 'heatEquation' from the source file 'heatEquation'
add_executable(heatEquation src/heatEquation.cxx)

# Define C++11 standard
set_property(TARGET heatEquation PROPERTY CXX_STANDARD 11)

# Add test called "heatEquation-test" based on the executable "heatEquation"
add_test (heatEquation-test heatEquation)
