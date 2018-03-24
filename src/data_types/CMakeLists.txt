add_library(${DATA_TYPES_LIB} INTERFACE)

target_link_libraries(
    ${DATA_TYPES_LIB}
    INTERFACE Boost::boost
    INTERFACE Boost::date_time)

target_include_directories(
    ${DATA_TYPES_LIB}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
