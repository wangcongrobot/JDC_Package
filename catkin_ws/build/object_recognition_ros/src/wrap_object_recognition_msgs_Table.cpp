/* DO NOT EDIT or check into source control
 * Generated code for wrapping a ros message Pub/Sub in ecto
 *
 * package : object_recognition_msgs
 * msg : Table
 */
#include <ecto_ros/wrap_sub.hpp>
#include <ecto_ros/wrap_pub.hpp>
#include <ecto_ros/wrap_bag.hpp>


#include <object_recognition_msgs/Table.h>

namespace ecto_object_recognition_msgs
{
    struct Subscriber_Table : ecto_ros::Subscriber<object_recognition_msgs::Table> {};
    struct Publisher_Table : ecto_ros::Publisher<object_recognition_msgs::Table> {};
    struct Bagger_Table : ecto_ros::Bagger<object_recognition_msgs::Table> {};
}

ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Subscriber_Table,"Subscriber_Table", "Subscribes to a object_recognition_msgs::Table.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Publisher_Table,"Publisher_Table", "Publishes a object_recognition_msgs::Table.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Bagger_Table,"Bagger_Table", "A bagger for messages of a given type. Can enable read/write to ros bags.");
