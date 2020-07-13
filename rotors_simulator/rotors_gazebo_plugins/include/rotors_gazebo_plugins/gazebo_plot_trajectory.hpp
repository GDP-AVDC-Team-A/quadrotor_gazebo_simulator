#ifndef GAZEBO_PLOT_TRAJECTORY_H
#define GAZEBO_PLOT_TRAJECTORY_H

#include "gazebo/physics/physics.hh"
#include "gazebo/transport/TransportTypes.hh"
#include "gazebo/msgs/MessageTypes.hh"

#include "gazebo/common/Time.hh"
#include "gazebo/common/Plugin.hh"
#include "gazebo/common/Events.hh"

#include "gazebo/rendering/DynamicLines.hh"
#include "gazebo/rendering/RenderTypes.hh"
#include "gazebo/rendering/Visual.hh"
#include "gazebo/rendering/Scene.hh"

#include <ros/callback_queue.h>
#include <ros/advertise_options.h>
#include <ros/ros.h>

#include <geometry_msgs/Point.h>
// if you want some positions of the model use this....
#include <gazebo_msgs/ModelStates.h>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include <droneMsgsROS/dronePose.h>


namespace gazebo
{
  namespace rendering
  {
    class SomeVisualPlugin : public VisualPlugin
    {
      public:
        /// \brief Constructor
        SomeVisualPlugin();

        /// \brief Destructor
        virtual ~SomeVisualPlugin();

        /// \brief Load the visual force plugin tags
        /// \param node XML config node
        void Load( VisualPtr _parent, sdf::ElementPtr _sdf );


      protected:
        /// \brief Update the visual plugin
        virtual void UpdateChild();


      private:
        /// \brief pointer to ros node
        ros::NodeHandle* rosnode_;

        /// \brief store model name
        std::string model_name_;

        /// \brief topic name
        std::string topic_name_;

        const int OFFSET = 0;
        const int COUNTER = 10;

        // /// \brief The visual pointer used to visualize the force.
        VisualPtr visual_;

        // /// \brief The scene pointer.
        ScenePtr scene_;

        /// \brief For example a line to visualize the force
        DynamicLines *line;
        int counter_;

        /// \brief for setting ROS name space
        std::string visual_namespace_;

        /// \Subscribe to some force
        ros::Subscriber pose_sub_;
        droneMsgsROS::dronePose previous_point;

        /// \brief Visualize the force
        void VisualizeTrajectory(const droneMsgsROS::dronePose::ConstPtr pose_msg);

        // Pointer to the update event connection
        event::ConnectionPtr update_connection_;
    };
  }
}

#endif
