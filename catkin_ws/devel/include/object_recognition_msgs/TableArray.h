// Generated by gencpp from file object_recognition_msgs/TableArray.msg
// DO NOT EDIT!


#ifndef OBJECT_RECOGNITION_MSGS_MESSAGE_TABLEARRAY_H
#define OBJECT_RECOGNITION_MSGS_MESSAGE_TABLEARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <object_recognition_msgs/Table.h>

namespace object_recognition_msgs
{
template <class ContainerAllocator>
struct TableArray_
{
  typedef TableArray_<ContainerAllocator> Type;

  TableArray_()
    : header()
    , tables()  {
    }
  TableArray_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , tables(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::object_recognition_msgs::Table_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::object_recognition_msgs::Table_<ContainerAllocator> >::other >  _tables_type;
  _tables_type tables;




  typedef boost::shared_ptr< ::object_recognition_msgs::TableArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::object_recognition_msgs::TableArray_<ContainerAllocator> const> ConstPtr;

}; // struct TableArray_

typedef ::object_recognition_msgs::TableArray_<std::allocator<void> > TableArray;

typedef boost::shared_ptr< ::object_recognition_msgs::TableArray > TableArrayPtr;
typedef boost::shared_ptr< ::object_recognition_msgs::TableArray const> TableArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::object_recognition_msgs::TableArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::object_recognition_msgs::TableArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace object_recognition_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'shape_msgs': ['/opt/ros/indigo/share/shape_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/indigo/share/sensor_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/indigo/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'object_recognition_msgs': ['/home/robot/catkin_ws/devel/share/object_recognition_msgs/msg', '/home/robot/catkin_ws/src/object_recognition_msgs/msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::object_recognition_msgs::TableArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::object_recognition_msgs::TableArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::object_recognition_msgs::TableArray_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d1c853e5acd0ed273eb6682dc01ab428";
  }

  static const char* value(const ::object_recognition_msgs::TableArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd1c853e5acd0ed27ULL;
  static const uint64_t static_value2 = 0x3eb6682dc01ab428ULL;
};

template<class ContainerAllocator>
struct DataType< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "object_recognition_msgs/TableArray";
  }

  static const char* value(const ::object_recognition_msgs::TableArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
# Just an array of tables\n\
object_recognition_msgs/Table[] tables\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: object_recognition_msgs/Table\n\
# Informs that a planar table has been detected at a given location\n\
\n\
Header header\n\
\n\
# The pose gives you the transform that take you to the coordinate system\n\
# of the table, with the origin somewhere in the table plane and the \n\
# z axis normal to the plane\n\
geometry_msgs/Pose pose\n\
\n\
# There is no guarantee that the table does NOT extend further than the\n\
# convex hull; this is just as far as we've observed it.\n\
# The origin of the table coordinate system is inside the convex hull\n\
\n\
# Set of points forming the convex hull of the table\n\
geometry_msgs/Point[] convex_hull\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::object_recognition_msgs::TableArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.tables);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TableArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::object_recognition_msgs::TableArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::object_recognition_msgs::TableArray_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "tables[]" << std::endl;
    for (size_t i = 0; i < v.tables.size(); ++i)
    {
      s << indent << "  tables[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::object_recognition_msgs::Table_<ContainerAllocator> >::stream(s, indent + "    ", v.tables[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // OBJECT_RECOGNITION_MSGS_MESSAGE_TABLEARRAY_H
