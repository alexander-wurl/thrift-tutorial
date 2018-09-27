CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1)
PROJECT(ThriftTutorial)

IF((CMAKE_SYSTEM_NAME STREQUAL Linux) AND
    ((CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64) OR
        (CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l)))

    # linux found (tested for x86_64/arm systems)
    MESSAGE("Using configuration for Linux ...")

    FIND_PACKAGE(Boost)

    FIND_PACKAGE(Thrift REQUIRED)
    MESSAGE("THRIFT_LIBRARIES: " ${THRIFT_LIBRARIES})
    MESSAGE("THRIFT_INCLUDE_DIR: " ${THRIFT_INCLUDE_DIR})
    MESSAGE("THRIFT_COMPILER: " ${THRIFT_COMPILER})

    # make sure gen-cpp files can be included
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}")
    INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}/gen-cpp")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")


    # thrift generated files ...
    SET(ThriftTutorial_GENCPP_SOURCES gen-cpp/TestService.cpp)

    # .. can be compiled to static library 'ThriftTutorial_GENCPP.a'
    ADD_LIBRARY(ThriftTutorial_GENCPP STATIC ${ThriftTutorial_GENCPP_SOURCES})

    # recompile thrift file from interface file 'tutorial.thrift'
    ADD_CUSTOM_COMMAND(
        OUTPUT gen-cpp/TestService.cpp
        COMMAND ${THRIFT_COMPILER} --gen cpp -r ${PROJECT_SOURCE_DIR}/src/tutorial.thrift
    )

    # create executable 'TutorialServer' from sources ...
    ADD_EXECUTABLE(TutorialServer src/CppServer.cpp)

    # ... and link necessary libraries
    TARGET_LINK_LIBRARIES(TutorialServer ThriftTutorial_GENCPP ${THRIFT_LIBRARIES})

    # create executable 'TutorialClient' from sources ...
    ADD_EXECUTABLE(TutorialClient src/CppClient.cpp)

    # ... and link necessary libraries
    TARGET_LINK_LIBRARIES(TutorialClient ThriftTutorial_GENCPP ${THRIFT_LIBRARIES})
    
ELSE()

    # other systems not supported
    MESSAGE("System not supported!")

ENDIF()
