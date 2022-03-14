cmake_minimum_required(VERSION 3.19.0)

project(QtzData VERSION 0.3.0 
    DESCRIPTION "Qtz Rapid Application Development Framework, Data Module"
    HOMEPAGE_URL "https://github.com/soroush/qtz-data"
    LANGUAGES CXX)
    
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Check for dependencies
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

if(NOT QTZ_LOCAL_BUILD)
find_package(QtzCore CONFIG REQUIRED)
endif()

# OS-dependent sources
set(OS_SOURCES )
if(WIN32)
    list(APPEND OS_SOURCES "${PROJECT_NAME}.rc")
endif()

# Define the library
add_library (${PROJECT_NAME} SHARED
    src/async/database-connection.cpp
    src/async/database-exception.cpp
    src/async/model-register.cpp
    src/async/query-request.cpp
    src/async/query-result.cpp
    src/async/query-thread.cpp
    src/async/query-worker.cpp
    src/async/sql-table-model.cpp
    src/data-provider-information.cpp
    src/data-provider.cpp
    src/database-pool.cpp
    src/i-edit-record.cpp
    src/i-insert-record.cpp
    src/jalali-table-model.cpp
    include/async/database-connection.hpp
    include/async/database-exception.hpp
    include/async/model-register.hpp
    include/async/query-request.hpp
    include/async/query-result.hpp
    include/async/query-thread.hpp
    include/async/query-worker.hpp
    include/async/sql-table-model.hpp
    include/data-provider-information.hpp
    include/data-provider.hpp
    include/data.hpp
    include/database-pool.hpp
    include/i-edit-record.h
    include/i-insert-record.hpp
    include/jalali-table-model.hpp
    include/table-node.hpp
    ${OS_SOURCES}
    # Resources
    resources/QtzData.qrc
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    VERSION 0.3.0
    SOVERSION 0
    DEBUG_POSTFIX d
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE
    DEFINE_SYMBOL QTZ_DATA_LIBRARY
    PUBLIC_HEADER "include/data.hpp"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${QTZ_LOCAL_INCLUDES_DIR}>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Sql PRIVATE QtzCore)

# Copy headers for local builds
if(QTZ_LOCAL_BUILD)
add_custom_command(TARGET QtzData POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -P 
        "${CMAKE_CURRENT_LIST_DIR}/cmake/copy_local_includes.cmake" 
        "${CMAKE_CURRENT_SOURCE_DIR}/include/" "data" "${QTZ_LOCAL_INCLUDES_DIR}"
)
endif()

# Install and export
include(GNUInstallDirs)

export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Targets.cmake")

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtz/data)

install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/qtz/data"
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtz/data)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES "cmake/${PROJECT_NAME}Config.cmake" 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

# pkg-config
configure_file("${PROJECT_NAME}.pc.in" "${PROJECT_NAME}.pc" @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
