#include "../include/campus_routing/MapNode.h"


Map::Map() {
    // set up ROS1 node 
    nh_ = ros::NodeHandle();

    MapPath = std::string(PKG_DIR) + "/../campus_data/data/a&m_campus.osm";

    // lat and long of A&M's campus
    origin.position.lat = 30.615011;
    origin.position.lon = -96.342476;

    projector(origin);

    loadOSM();

    getLocalMap();

    service_ = nh_.advertiseService("plan", &Map::handleRequest, this);
}

void Map::loadOSM() {
    // load map
    lanelet2::ErrorMessages errors;
    map = lanelet2::load(MapPath, projector, errors);
    
    if (!errors.empty()) {
        ROS_ERROR("Error loading the OSM map");
        return;
    }

    ROS_INFO("OSM Map loaded successfully");
}

void Map::getLocalMap() {

}

bool Map::handleRequest(campus_routing::Plan::Request &req,
                   campus_routing::Plan::Response &res) {
    ROS_INFO("Received service request");

    lanelet2::GPS_point start_gps = req[0];
    lanelet2::GPS_point goal_gps = req[1];

    BasicPoint3d start_projection = projector.forward(start_gps);
    BasicPoint3d goal_projection = projector.forward(goal_gps);

    geometry_msgs::msg::Pose start;
    start.position.x = start_projection.x();
    start.position.y = start_projection.y();
    geometry_msgs::msg::Pose goal;
    goal.position.x = goal_projection.x();
    goal.position.y = goal_projection.y();

    nav_msgs::msg::Path path = plan(start, goal);

    if (path.poses.empty()) return false;

    res.output_value = path;

    return true;
}

nav_msgs::msg::Path Map::plan(geometry_msgs::msg::Pose start, geometry_msgs::msg::Pose goal) {

}


int main(int argc, char** argv) {
    ros::init(argc, argv, "MapNode");

    Map node;
    ros::spin()

    return 0;
}