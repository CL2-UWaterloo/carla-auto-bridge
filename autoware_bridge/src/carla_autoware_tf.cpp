#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

#include "geometry_msgs/msg/transform_stamped.hpp"

#include<memory>

using namespace std::chrono_literals;

class CarlaAutowareTf : public rclcpp::Node
{
public:
    explicit CarlaAutowareTf();
private:
    void timerCb();
    std::unique_ptr<tf2_ros::StaticTransformBroadcaster> tf_publisher;
    std::unique_ptr<tf2_ros::TransformListener> tf_listener{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer;
    rclcpp::TimerBase::SharedPtr timer{nullptr};

};

CarlaAutowareTf::CarlaAutowareTf() : Node("carla_autoware_tf_node")
{
    tf_publisher = std::make_unique<tf2_ros::StaticTransformBroadcaster>(*this);
    tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
    tf_listener = std::make_unique<tf2_ros::TransformListener>(*tf_buffer);

    timer = this->create_wall_timer(1s, std::bind(&CarlaAutowareTf::timerCb, this));

}

void CarlaAutowareTf::timerCb()
{
    rclcpp::Time now = this->get_clock()->now();
    geometry_msgs::msg::TransformStamped pub_tf;

    pub_tf.header.stamp = now;
    pub_tf.header.frame_id = "base_link";
    pub_tf.child_frame_id = "ego_vehicle";
    pub_tf.transform.translation.x = 0.0;
    pub_tf.transform.translation.y = 0.0;
    pub_tf.transform.translation.z = 0.0;
    pub_tf.transform.rotation.x = 0.0;
    pub_tf.transform.rotation.y = 0.0;
    pub_tf.transform.rotation.z = 0.0;
    pub_tf.transform.rotation.w = 1.0;
    tf_publisher->sendTransform(pub_tf);
}

int main(int argc, char ** argv)
{
    auto logger = rclcpp::get_logger("logger");

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CarlaAutowareTf>());

    return 0;
}
