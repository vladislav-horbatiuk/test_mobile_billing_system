set(TEST_APPLICATION_CONTROLLER Test${PROJECT_NAME}ApplicationController)

add_executable(${TEST_APPLICATION_CONTROLLER} TestApplicationController.cpp)

target_link_libraries(${TEST_APPLICATION_CONTROLLER}
    PRIVATE ${MAIN_APPLICATION_CONTROLLER_LIB}
    PRIVATE ${DATA_TYPES_LIB}
    PRIVATE GTest::Main
    PRIVATE Boost::filesystem
    )

GTEST_ADD_TESTS(${TEST_APPLICATION_CONTROLLER} "" AUTO)
