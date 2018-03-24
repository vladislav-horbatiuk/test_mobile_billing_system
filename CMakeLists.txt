cmake_minimum_required(VERSION 3.7.2)

project(MobileBillingSystem)

################################################################################
# Compiler settings
################################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

################################################################################
# Third-party libraries
################################################################################

find_package(Boost 1.63 REQUIRED COMPONENTS program_options date_time)
find_package(GTest REQUIRED)

################################################################################
# CMake configuration
################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

################################################################################
# Project's libraries names
################################################################################

set(DATA_TYPES_LIB ${PROJECT_NAME}DataTypes)
set(DATA_VALIDATION_LIB ${PROJECT_NAME}DataValidation)

################################################################################
# Configuring cmake
################################################################################

add_subdirectory(src)
add_subdirectory(test)
