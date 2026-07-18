#pragma once
#include <cstddef>

namespace qt_turret {

inline constexpr auto node_name        = "turret_qt_controller";
inline constexpr auto cmd_turret_topic  = "/cmd_turret";
inline constexpr auto status_topic     = "/proto_turret_publisher";
inline constexpr size_t qos_depth       = 10;

} // namespace qt_turret

namespace camera {
inline constexpr int width      = 640;
inline constexpr int height     = 480;
inline constexpr int fpsMin     = 1;
inline constexpr int fpsMax     = 120;
inline constexpr int fpsDefault = 30;
} // namespace camera
