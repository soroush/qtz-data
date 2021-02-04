include(CMakeFindDependencyMacro)
find_package(Qt5 COMPONENTS Core Sql REQUIRED)
find_package(QtzCore CONFIG REQUIRED)
include("${CMAKE_CURRENT_LIST_DIR}/QtzDataTargets.cmake")