#pragma once
#include <cstddef>
#include <QColor>
#include <QVariantMap>

namespace qt_turret {

inline constexpr auto node_name = "turret_qt_controller";
inline constexpr auto cmd_turret_topic = "/cmd_turret";
inline constexpr auto status_topic = "/proto_turret_publisher";
inline constexpr size_t qos_depth = 10;

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
inline constexpr float speedMultiplier = 0.3f;
} // namespace combat

namespace theme {
inline QVariantMap make() {
    QVariantMap m;
    m["spaceBg"]        = QColor(0x0A, 0x0E, 0x17);
    m["spaceSurface"]   = QColor(0x11, 0x18, 0x27);
    m["spaceElement"]   = QColor(0x1F, 0x29, 0x37);
    m["spaceElementAlpha"] = QColor(0x1F, 0x29, 0x37, 0x99);
    m["spaceText"]      = QColor(0xF3, 0xF4, 0xF6);
    m["spaceTextMuted"] = QColor(0x4B, 0x55, 0x63);
    m["spaceAccent"]    = QColor(0x00, 0xFF, 0xC6);
    m["spaceError"]     = QColor(0xFF, 0x44, 0x44);
    m["spaceWarning"]   = QColor(0xFF, 0xB8, 0x00);
    m["spaceSuccess"]   = QColor(0x00, 0xC8, 0x53);
    m["spaceBorder"]    = QColor(0x37, 0x41, 0x51);
    return m;
}
} // namespace theme
