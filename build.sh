#!/usr/bin/env bash
set -e

source /opt/ros/lyrical/setup.bash
source "$HOME/Ros2/ros2_ws/install/setup.bash"

BUILD_DIR="$(dirname "$0")/build"

cmake -B "$BUILD_DIR" -S "$(dirname "$0")"
cmake --build "$BUILD_DIR" -j "$(nproc)"
