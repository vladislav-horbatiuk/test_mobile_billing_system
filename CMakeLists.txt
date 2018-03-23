cmake_minimum_required(VERSION 3.7.2)

project(MobileBillingSystem)

################################################################################
# Compiler settings
################################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

find_package(Boost 1.63 REQUIRED COMPONENTS program_options)
