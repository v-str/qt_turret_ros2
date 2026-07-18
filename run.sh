#!/usr/bin/env bash
set -e

unset ROS_DISTRO ROS_VERSION ROS_PYTHON_VERSION AMENT_PREFIX_PATH

source /opt/ros/lyrical/setup.bash
source "$HOME/Ros2/ros2_ws/install/setup.bash"

exec "$(dirname "$0")/build/Desktop_Qt_6_11_1_Debug/qt_turret_ros2" "$@"
