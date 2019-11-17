; Auto-generated. Do not edit!


(cl:in-package beginner_tutorials-msg)


;//! \htmlinclude ForceData.msg.html

(cl:defclass <ForceData> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 8 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass ForceData (<ForceData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ForceData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ForceData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beginner_tutorials-msg:<ForceData> is deprecated: use beginner_tutorials-msg:ForceData instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <ForceData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beginner_tutorials-msg:id-val is deprecated.  Use beginner_tutorials-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <ForceData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beginner_tutorials-msg:data-val is deprecated.  Use beginner_tutorials-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ForceData>) ostream)
  "Serializes a message object of type '<ForceData>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ForceData>) istream)
  "Deserializes a message object of type '<ForceData>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 8)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ForceData>)))
  "Returns string type for a message object of type '<ForceData>"
  "beginner_tutorials/ForceData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ForceData)))
  "Returns string type for a message object of type 'ForceData"
  "beginner_tutorials/ForceData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ForceData>)))
  "Returns md5sum for a message object of type '<ForceData>"
  "7b61d0924a09e3316ba5fea2e1ca8c6f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ForceData)))
  "Returns md5sum for a message object of type 'ForceData"
  "7b61d0924a09e3316ba5fea2e1ca8c6f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ForceData>)))
  "Returns full string definition for message of type '<ForceData>"
  (cl:format cl:nil "int32 id~%int16[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ForceData)))
  "Returns full string definition for message of type 'ForceData"
  (cl:format cl:nil "int32 id~%int16[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ForceData>))
  (cl:+ 0
     4
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ForceData>))
  "Converts a ROS message object to a list"
  (cl:list 'ForceData
    (cl:cons ':id (id msg))
    (cl:cons ':data (data msg))
))
