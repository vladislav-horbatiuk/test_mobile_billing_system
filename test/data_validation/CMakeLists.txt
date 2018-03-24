set(TEST_DATA_VALIDATION Test${PROJECT_NAME}DataValidation)

add_executable(${TEST_DATA_VALIDATION} TestDataValidation.cpp)

target_link_libraries(${TEST_DATA_VALIDATION}
    PRIVATE ${DATA_VALIDATION_LIB}
    PRIVATE GTest::Main
    PRIVATE Boost::date_time
    )

GTEST_ADD_TESTS(${TEST_DATA_VALIDATION} "" AUTO)
