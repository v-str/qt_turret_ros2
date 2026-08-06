#include "RosHandler.h"

#include <chrono>

#include "constants.h"

RosHandler::~RosHandler()
{
    stop();
}

void RosHandler::init() {
    rclcpp::init(0, nullptr);

    m_node = std::make_shared<rclcpp::Node>(qt_turret::node_name);

    m_executor = std::make_shared<Executor>();
    m_executor->add_node(m_node);

    m_publisher = m_node->create_publisher<TurretCommand>(
        qt_turret::cmd_turret_topic,
        qt_turret::qos_depth);

    m_subscriber = m_node->create_subscription<TurretCommand>(
        qt_turret::status_topic,
        qt_turret::qos_depth,
        [this](const TurretCommand::SharedPtr msg) {
            if (m_onStatus) {
                m_onStatus(msg->pan_pos, msg->tilt_pos, msg->laser_enable);
            }
        });

    m_temperatureSub = m_node->create_subscription<std_msgs::msg::Float32>(
        qt_turret::temperature_topic,
        qt_turret::qos_depth,
        [this](const std_msgs::msg::Float32::SharedPtr msg) {
            if (m_onTemperature) {
                m_onTemperature(msg->data);
            }
        });
}

void RosHandler::run()
{
    m_executor->spin_some(std::chrono::milliseconds(10));
}

void RosHandler::stop()
{
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
    m_publisher.reset();
    m_subscriber.reset();
    m_temperatureSub.reset();
    m_node.reset();
}

void RosHandler::publishCommand(const CommandData &cmd) {
    if (!m_publisher) return;
    auto msg = TurretCommand();
    msg.pan_pos = cmd.pan;
    msg.tilt_pos = cmd.tilt;
    msg.pan_vel = cmd.panVel;
    msg.tilt_vel = cmd.tiltVel;
    msg.laser_enable = cmd.laserOn;
    msg.fan_enable = cmd.fanOn;
    m_publisher->publish(msg);
}

void RosHandler::setStatusCallback(StatusCallback cb)
{
    m_onStatus = std::move(cb);
}

void RosHandler::setTemperatureCallback(TemperatureCallback cb)
{
    m_onTemperature = std::move(cb);
}
