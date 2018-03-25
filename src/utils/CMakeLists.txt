add_library(${UTILS_LIB} INTERFACE)

target_include_directories(${UTILS_LIB}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
