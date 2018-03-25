add_executable(MainApplication MainApplication.cpp)

target_link_libraries(MainApplication
    PRIVATE ${MAIN_APPLICATION_CONTROLLER_LIB}
    PRIVATE ${DATA_TYPES_LIB}
    PRIVATE ${UTILS_LIB}
    PRIVATE Boost::program_options)
