#pragma once
#include <cstddef>
#include <QColor>
#include <QVariantMap>

namespace qt_turret {

inline constexpr auto node_name = "proto_turret_qt_node";
inline constexpr auto cmd_turret_topic = "/proto_turret_cmd";
inline constexpr auto status_topic = "/proto_turret_stm32_publisher";
inline constexpr auto temperature_topic = "/proto_turret_stm32_temperature";
inline constexpr size_t qos_depth = 10;

// vid/pid для обнаружения платы stm32
inline constexpr quint16 stm32_vid = 0x0483;
inline constexpr quint16 stm32_pid = 0x374b;

} // namespace qt_turret

namespace ui {
inline constexpr auto windowTitle = "Proto Turret Controller";
inline constexpr int windowWidth = 800;
inline constexpr int windowHeight = 600;
} // namespace ui

namespace camera {
inline constexpr int width = 640;
inline constexpr int height = 480;
inline constexpr int fpsMin = 1;
inline constexpr int fpsMax = 120;
inline constexpr int fpsDefault = 30;
} // namespace camera

namespace combat {
inline constexpr float speedMultiplier = 5.0f;
} // namespace combat

struct LogType {
    enum { Info = 0, Success = 1, Error = 2, Tracking = 3 };
};

namespace theme {
inline QVariantMap make() {
    QVariantMap m;
    m["bgDeep"]      = QColor(0x04, 0x07, 0x0C);
    m["bgPanel"]     = QColor(0x0C, 0x11, 0x18);
    m["panelAlpha"]  = QColor(0x0C, 0x11, 0x18, 0xD0);
    m["edge"]        = QColor(0x18, 0x22, 0x30);
    m["edgeBright"]  = QColor(0x2A, 0x3A, 0x4A);
    m["accent"]      = QColor(0x00, 0xE5, 0xFF);
    m["accentDim"]   = QColor(0x00, 0x8C, 0x9E);
    m["ok"]          = QColor(0x2E, 0xFF, 0x9A);
    m["warn"]        = QColor(0xFF, 0xB0, 0x20);
    m["err"]         = QColor(0xFF, 0x3B, 0x30);
    m["text"]        = QColor(0xE9, 0xF1, 0xF7);
    m["textDim"]     = QColor(0x5A, 0x6A, 0x78);
    return m;
}
} // namespace theme
