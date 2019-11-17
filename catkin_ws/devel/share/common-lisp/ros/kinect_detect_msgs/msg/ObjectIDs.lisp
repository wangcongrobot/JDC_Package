; Auto-generated. Do not edit!


(cl:in-package kinect_detect_msgs-msg)


;//! \htmlinclude ObjectIDs.msg.html

(cl:defclass <ObjectIDs> (roslisp-msg-protocol:ros-message)
  ((object_ids
    :reader object_ids
    :initarg :object_ids
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass ObjectIDs (<ObjectIDs>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObjectIDs>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObjectIDs)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kinect_detect_msgs-msg:<ObjectIDs> is deprecated: use kinect_detect_msgs-msg:ObjectIDs instead.")))

(cl:ensure-generic-function 'object_ids-val :lambda-list '(m))
(cl:defmethod object_ids-val ((m <ObjectIDs>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kinect_detect_msgs-msg:object_ids-val is deprecated.  Use kinect_detect_msgs-msg:object_ids instead.")
  (object_ids m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObjectIDs>) ostream)
  "Serializes a message object of type '<ObjectIDs>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'object_ids))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) ele) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) ele) ostream))
   (cl:slot-value msg 'object_ids))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObjectIDs>) istream)
  "Deserializes a message object of type '<ObjectIDs>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'object_ids) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'object_ids)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:aref vals i)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:aref vals i)) (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObjectIDs>)))
  "Returns string type for a message object of type '<ObjectIDs>"
  "kinect_detect_msgs/ObjectIDs")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObjectIDs)))
  "Returns string type for a message object of type 'ObjectIDs"
  "kinect_detect_msgs/ObjectIDs")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObjectIDs>)))
  "Returns md5sum for a message object of type '<ObjectIDs>"
  "51b8c1ab69cd630e4f6eaee2d22fc8d0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObjectIDs)))
  "Returns md5sum for a message object of type 'ObjectIDs"
  "51b8c1ab69cd630e4f6eaee2d22fc8d0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObjectIDs>)))
  "Returns full string definition for message of type '<ObjectIDs>"
  (cl:format cl:nil "uint32[] object_ids~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObjectIDs)))
  "Returns full string definition for message of type 'ObjectIDs"
  (cl:format cl:nil "uint32[] object_ids~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObjectIDs>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'object_ids) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObjectIDs>))
  "Converts a ROS message object to a list"
  (cl:list 'ObjectIDs
    (cl:cons ':object_ids (object_ids msg))
))
