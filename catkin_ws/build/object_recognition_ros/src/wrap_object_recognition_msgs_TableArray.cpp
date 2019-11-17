/* DO NOT EDIT or check into source control
 * Generated code for wrapping a ros message Pub/Sub in ecto
 *
 * package : object_recognition_msgs
 * msg : TableArray
 */
#include <ecto_ros/wrap_sub.hpp>
#include <ecto_ros/wrap_pub.hpp>
#include <ecto_ros/wrap_bag.hpp>


#include <object_recognition_msgs/TableArray.h>

namespace ecto_object_recognition_msgs
{
    struct Subscriber_TableArray : ecto_ros::Subscriber<object_recognition_msgs::TableArray> {};
    struct Publisher_TableArray : ecto_ros::Publisher<object_recognition_msgs::TableArray> {};
    struct Bagger_TableArray : ecto_ros::Bagger<object_recognition_msgs::TableArray> {};
}

ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Subscriber_TableArray,"Subscriber_TableArray", "Subscribes to a object_recognition_msgs::TableArray.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Publisher_TableArray,"Publisher_TableArray", "Publishes a object_recognition_msgs::TableArray.");
ECTO_CELL(ecto_object_recognition_msgs, ecto_object_recognition_msgs::Bagger_TableArray,"Bagger_TableArray", "A bagger for messages of a given type. Can enable read/write to ros bags.");
