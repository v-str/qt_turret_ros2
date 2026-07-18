#include "RosHandler.h"
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
}

void RosHandler::run() { m_executor->spin_some(); }

void RosHandler::stop()
{
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
    m_publisher.reset();
    m_subscriber.reset();
    m_node.reset();
}

void RosHandler::publishCommand(float pan, float tilt, float pan_vel,
                                float tilt_vel, bool laser) {
    if (!m_publisher) return;
    auto msg = TurretCommand();
    msg.pan_pos = pan;
    msg.tilt_pos = tilt;
    msg.pan_vel = pan_vel;
    msg.tilt_vel = tilt_vel;
    msg.laser_enable = laser;
    m_publisher->publish(msg);
}

void RosHandler::setStatusCallback(StatusCallback cb)
{
    m_onStatus = std::move(cb);
}
