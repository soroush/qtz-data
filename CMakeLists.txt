cmake_minimum_required(VERSION 3.1.0)

project(QtzData VERSION 0.3.0 
    DESCRIPTION "Qtz Rapid Application Development Framework, Data Module"
    HOMEPAGE_URL "https://github.com/soroush/qtz-data"
    LANGUAGES CXX)
    
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

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

# Set properties
set_target_properties(${PROJECT_NAME} PROPERTIES 
    PROPERTIES VERSION 0.3.0
    PROPERTIES SOVERSION 0
    CXX_STANDARD 11
    DEBUG_POSTFIX "d"
    DEFINE_SYMBOL "QTZ_DATA_LIBRARY"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link against dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Sql Qtz::QtzCore)

# Install and export
include(GNUInstallDirs)

export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}Targets.cmake")

install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
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
    NAMESPACE Qtz::
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
