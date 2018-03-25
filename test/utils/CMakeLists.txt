set(TEST_UTILS Test${PROJECT_NAME}Utils)

add_executable(${TEST_UTILS} TestUtils.cpp)

target_link_libraries(${TEST_UTILS}
    PRIVATE ${UTILS_LIB}
    PRIVATE GTest::Main
    )

GTEST_ADD_TESTS(${TEST_UTILS} "" AUTO)
