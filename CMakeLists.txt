cmake_minimum_required(VERSION 3.14)

# 1. project declaration, versioning and languages
project(MyProject
    VERSION 1.0.0
    LANGUAGES CXX C
)

# 2. user‐configurable options
option(BUILD_SHARED_LIBS
       "Build MyProject as shared libraries" OFF)

# 3. C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. configure a header from a template
configure_file(
    ${CMAKE_SOURCE_DIR}/Config.h.in
    ${CMAKE_BINARY_DIR}/Config.h
)

# 5. include CTest to get add_test() and enable_testing()
include(CTest)

# 6. add a library target
add_library(mylib
    src/lib.cpp
)
target_include_directories(mylib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>  # for Config.h
        $<INSTALL_INTERFACE:include>
)
# version the library target
set_target_properties(mylib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# 7. add an executable that links the library
add_executable(myapp
    src/main.cpp
)
target_link_libraries(myapp
    PRIVATE mylib
)

# 8. installation rules
install(TARGETS myapp mylib
    EXPORT MyProjectTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT MyProjectTargets
    FILE MyProjectConfig.cmake
    NAMESPACE MyProject::
    DESTINATION lib/cmake/MyProject
)

# 9. export for find_package()
export(PACKAGE MyProject)

# 10. define a test
enable_testing()
add_test(NAME RunMyApp
    COMMAND myapp
)
