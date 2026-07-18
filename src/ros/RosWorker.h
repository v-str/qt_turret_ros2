#ifndef ROSWORKER_H
#define ROSWORKER_H

#include <QObject>
#include <rclcpp/rclcpp.hpp>
#include <proto_turret_interfaces/msg/turret_command.hpp>

class RosWorker : public QObject
{
    Q_OBJECT

public:
    explicit RosWorker(QObject *parent = nullptr);
    ~RosWorker() override;

public slots:
    void start();
    void stop();
    void publishCommand(float pan, float tilt, float pan_vel, float tilt_vel, bool laser);

signals:
    void finished();
    void stateUpdated(float pan_pos, float tilt_pos, bool laser);

private:
    rclcpp::Node::SharedPtr m_node;
    rclcpp::Publisher<proto_turret_interfaces::msg::TurretCommand>::SharedPtr publisher_;
    rclcpp::Subscription<proto_turret_interfaces::msg::TurretCommand>::SharedPtr subscriber_;
};

#endif // ROSWORKER_H
