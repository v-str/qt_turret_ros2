cmake_minimum_required(VERSION 3.16)

project(qt_turret_ros2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# автоопределение числа ядер для параллельной сборки
include(ProcessorCount)
ProcessorCount(NCPUS)
if(NCPUS GREATER 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${NCPUS})
    set(ENV{MAKEFLAGS} "-j${NCPUS}")
endif()

# пути к ROS2 и своей рабочей области
list(APPEND CMAKE_PREFIX_PATH
    /opt/ros/lyrical
    $ENV{HOME}/Ros2/ros2_ws/install
)
set(ENV{AMENT_PREFIX_PATH} "/opt/ros/lyrical:$ENV{HOME}/Ros2/ros2_ws/install")

# Qt — графический интерфейс
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Python — для скриптов ament (cmake-помощники ROS2)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')"
    OUTPUT_VARIABLE _py_ver
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(ENV{PYTHONPATH} "/opt/ros/lyrical/lib/python${_py_ver}/site-packages:$ENV{PYTHONPATH}")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/ament_cmake_package_templates")

# OpenCV — камера
find_package(OpenCV REQUIRED COMPONENTS core imgproc videoio)

# ROS2
find_package(rclcpp REQUIRED)
find_package(proto_turret_interfaces REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        src/ros/RosHandler.h
        src/ros/RosHandler.cpp
        src/ros/QtRosWorker.h
        src/ros/QtRosWorker.cpp
        src/constants.h
        src/camera/CameraGrabber.h
        src/camera/CameraGrabber.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_turret_ros2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qt_turret_ros2 SHARED ${PROJECT_SOURCES})
    else()
        add_executable(qt_turret_ros2 ${PROJECT_SOURCES})
    endif()
endif()

target_include_directories(qt_turret_ros2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(qt_turret_ros2 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCV_LIBS}
    rclcpp::rclcpp
    proto_turret_interfaces::proto_turret_interfaces
)

# настройки бандла для macOS/iOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.qt_turret_ros2)
endif()
set_target_properties(qt_turret_ros2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS qt_turret_ros2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt_turret_ros2)
endif()
