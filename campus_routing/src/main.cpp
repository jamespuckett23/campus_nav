#include <ros/ros.h>
#include <campus_routing/Plan.h>
#include <lanelet2_core/primitives/GPS_point.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "navigator");

    ros::NodeHandle n;
    ros::Rate loop_rate(10);

    auto zach_engineering_building = lanelet2::GPS_point(30.6185, 96.3385);
    auto kyle_field = lanelet2::GPS_point(30.6101, 96.3401);
    auto MSC_building = lanelet2::GPS_point(30.6121, 96.3414);

    std::vector<lanelet2::GPS_point> locations;
    locations.push_back(zach_engineering_building);
    locations.push_back(kyle_field);
    locations.push_back(MSC_building);

    ros::ServiceClient client = nh.serviceClient<Map::Plan>("plan");

    ROS_INFO("Waiting for service...");
    client.waitForExistence();
    ROS_INFO("Service is now available");

    lanelet2::GPS_point start = locations[0];
    lanelet2::GPS_point goal = locations[1];

    Map::Plan srv;
    srv.request.input_value.push_back(start);
    srv.request.input_value.push_back(goal);

    if (client.call(srv)) {
        ROS_INFO("Response received: %ld", srv.response.output_value);
    } else {
        ROS_ERROR("Failed to call service!");
    }
    
    return 0;
}