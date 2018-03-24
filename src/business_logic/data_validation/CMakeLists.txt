set(DATA_VALIDATION_SOURCES
    src/DataValidatorFactory.cpp
    src/DataValidator.cpp)

add_library(${DATA_VALIDATION_LIB} STATIC ${DATA_VALIDATION_SOURCES})

target_link_libraries(
    ${DATA_VALIDATION_LIB}
    PUBLIC ${DATA_TYPES_LIB})

target_include_directories(
    ${DATA_VALIDATION_LIB}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
