set(TEST_DATA_TYPES_SERIALIZATION Test${PROJECT_NAME}DataTypesSerialization)

add_executable(${TEST_DATA_TYPES_SERIALIZATION} TestDataTypesSerialization.cpp)

target_link_libraries(${TEST_DATA_TYPES_SERIALIZATION}
    PRIVATE ${DATA_TYPES_LIB}
    PRIVATE GTest::Main
    PRIVATE Boost::date_time)

GTEST_ADD_TESTS(${TEST_DATA_TYPES_SERIALIZATION} "" AUTO)
