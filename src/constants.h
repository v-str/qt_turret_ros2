#pragma once
#include <cstddef>

namespace qt_turret {

inline constexpr auto node_name        = "turret_qt_controller";
inline constexpr auto cmd_turret_topic  = "/cmd_turret";
inline constexpr auto heartbeat_topic   = "/proto_turret_publisher";
inline constexpr size_t qos_depth       = 10;

} // namespace qt_turret
