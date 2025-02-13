#include "../include/campus_routing/MapNode.h"


Map::Map() {
    // set up ROS1 node 
    nh_ = ros::NodeHandle();

    MapPath = std::string(PKG_DIR) + "/../campus_data/data/a&m_campus.osm";

    // lat and long of A&M's campus
    origin.position.lat = 30.615011;
    origin.position.lon = -96.342476;

    loadOSM(origin);

    getLocalMap();

    service_ = nh_.advertiseService("plan", &Map::handleRequest, this);
}

void Map::loadOSM(lanelet2::Origin& origin) {
    // find projector
    projection::UtmProjector projector(origin);
    BasicPoint3d projection = projector.forward(GPSPoint{49, 8.4, 0});

    // load map
    lanelet2::ErrorMessages errors;
    map = lanelet2::load(MapPath, lanelet2::projection::UtmProjector(Origin({49, 8.4})), errors);
    
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

    geometry_msgs::msg::Pose start = req[0];
    geometry_msgs::msg::Pose goal = req[1];

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