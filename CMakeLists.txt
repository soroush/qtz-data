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

# Include directories
include_directories("include")

# OS-dependent sources
set(OS_SOURCES )
if(WIN32)
    list(APPEND OS_SOURCES QtzData.rc)
endif()

# Define the library
add_library (QtzData SHARED
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
    resources/QtzData.qrc)

# Add 'd' suffix to debug builds
set_property(TARGET QtzData PROPERTY DEBUG_POSTFIX d)

# Set version
set_target_properties(QtzData PROPERTIES VERSION 0.3.0)
set_target_properties(QtzData PROPERTIES SOVERSION 0)

# pkg-config
configure_file(QtzData.pc.in QtzData.pc @ONLY)

# Define symbol exporter
target_compile_definitions(QtzData PRIVATE -DQTZ_DATA_LIBRARY)
target_compile_features(QtzData PRIVATE cxx_std_11)

# Install and export
include(GNUInstallDirs)
target_include_directories(QtzData PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>  
    $<INSTALL_INTERFACE:include/>
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtz/data)

install(TARGETS QtzData
    EXPORT QtzDataConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
export(TARGETS QtzData FILE QtzDataConfig.cmake)

install(EXPORT QtzDataConfig
    FILE QtzDataConfig.cmake
    NAMESPACE Qtz::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtzData.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# Link againsg dependencies
target_link_libraries(QtzData Qt5::Core Qt5::Sql Qtz::QtzCore)
