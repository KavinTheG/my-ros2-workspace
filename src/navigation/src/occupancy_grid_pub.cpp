#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/occupancy_grid.hpp"



// Namespace allows code to be further organized
using namespace std::chrono_literals;
class OccupancyGrid_Publisher : public rclcpp::Node
{
    public:
        OccupancyGrid_Publisher()
        : Node("occupancy_grid_publisher")
        {
            og_pub = this->create_publisher<nav_msgs::msg::OccupancyGrid>("custom_og", 10);
            timer = this->create_wall_timer(500ms, std::bind(&OccupancyGrid_Publisher::og_callback, this));

        }

    private:
        void og_callback()
        {
            std::vector<float> range(100, 10.0f);

            auto og_msg = nav_msgs::msg::OccupancyGrid(); 

            // Declare necessary variables for occupancy grid
            og_msg.header.stamp = rclcpp::Clock().now();
            og_msg.header.frame_id = "map_frame";

            // Metadata for the map
            //og_msg.info.map_load_time = 0.05;
            og_msg.info.resolution = 0.05;
            og_msg.info.width = 3;
            og_msg.info.height = 3  ;

            og_msg.info.origin.position.x = 0.0;
            og_msg.info.origin.position.y = 0.0;
            og_msg.info.origin.position.z = 0.0;

            og_msg.info.origin.orientation.x = 0.0;
            og_msg.info.origin.orientation.y = 0.0;
            og_msg.info.origin.orientation.z = 0.0;
            og_msg.info.origin.orientation.w = 0.0;

            og_msg.data = {100, 0, 0, 0, -1, 0, 0, 0, 100};

            og_pub->publish(og_msg);

        }


        // Declare class variables
        rclcpp::TimerBase::SharedPtr timer;
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr og_pub;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OccupancyGrid_Publisher>());
    rclcpp::shutdown();
    return 0;
}