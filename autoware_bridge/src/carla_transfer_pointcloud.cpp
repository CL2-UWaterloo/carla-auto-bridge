#include "rclcpp/rclcpp.hpp"

#include "sensor_msgs/msg/point_cloud2.hpp"
#include <memory>

using std::placeholders::_1;

class CarlaTransferPointcloud : public rclcpp::Node
{
public:
    explicit CarlaTransferPointcloud();
private:
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_concat_cloud;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_cloud;
    void cloudCb(const sensor_msgs::msg::PointCloud2::SharedPtr in_cloud);
};


CarlaTransferPointcloud::CarlaTransferPointcloud() : Node("carla_transfer_pointcloud_node")
{
    sub_cloud = this->create_subscription<sensor_msgs::msg::PointCloud2>("/carla/ego_vehicle/lidar", 10, std::bind(&CarlaTransferPointcloud::cloudCb, this, _1));
    pub_concat_cloud = this->create_publisher<sensor_msgs::msg::PointCloud2>("/sensing/lidar/concatenated/pointcloud", 10);
}


void CarlaTransferPointcloud::cloudCb(const sensor_msgs::msg::PointCloud2::SharedPtr in_cloud)
{
    pub_concat_cloud->publish(*in_cloud);
}

int main(int argc, char ** argv)
{
    auto logger = rclcpp::get_logger("logger");

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CarlaTransferPointcloud>());

    return 0;
}
