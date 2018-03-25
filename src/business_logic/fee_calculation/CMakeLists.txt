add_library(${FEE_CALCULATION_LIB} INTERFACE)

target_include_directories(${FEE_CALCULATION_LIB}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${FEE_CALCULATION_LIB}
    INTERFACE ${DATA_TYPES_LIB}
    INTERFACE Boost::date_time)
