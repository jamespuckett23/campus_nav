#include <lanelet2_core/primitives/Lanelet.h>
#include <lanelet2_io/Io.h>
#include <lanelet2_projection/UTM.h>
#include <lanelet2_routing/Route.h>
#include <lanelet2_routing/RoutingCost.h>
#include <lanelet2_routing/RoutingGraph.h>
#include <lanelet2_routing/RoutingGraphContainer.h>
#include <lanelet2_traffic_rules/TrafficRulesFactory.h>

#include <ros/ros.h>
#include "campus_routing/Plan.h"

class Map
{
    public:
        Map();

    private:
        ros::NodeHandle nh_;
        ros::ServiceServer service_;

        std::string MapPath;
        LaneletMapPtr map;
        
        lanelet2::Origin origin;
        lanelet2::projection::UtmProjector projector;

        double start;
        double goal;

        bool handleRequest();

        void getLocalMap();

        void loadOSM();

        nav_msgs::msg::Path plan(geometry_msgs::msg::Pose start, geometry_msgs::msg::Pose goal);


}

