# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from darknet_ros_msgs/TargetPoint.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class TargetPoint(genpy.Message):
  _md5sum = "35dbeb86b706cfd5d35e4c142abe1f81"
  _type = "darknet_ros_msgs/TargetPoint"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string Class
float64 probability
float64 camera_x
float64 camera_y
float64 camera_z
"""
  __slots__ = ['Class','probability','camera_x','camera_y','camera_z']
  _slot_types = ['string','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       Class,probability,camera_x,camera_y,camera_z

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TargetPoint, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.Class is None:
        self.Class = ''
      if self.probability is None:
        self.probability = 0.
      if self.camera_x is None:
        self.camera_x = 0.
      if self.camera_y is None:
        self.camera_y = 0.
      if self.camera_z is None:
        self.camera_z = 0.
    else:
      self.Class = ''
      self.probability = 0.
      self.camera_x = 0.
      self.camera_y = 0.
      self.camera_z = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self.Class
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_4d.pack(_x.probability, _x.camera_x, _x.camera_y, _x.camera_z))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Class = str[start:end].decode('utf-8')
      else:
        self.Class = str[start:end]
      _x = self
      start = end
      end += 32
      (_x.probability, _x.camera_x, _x.camera_y, _x.camera_z,) = _struct_4d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self.Class
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_4d.pack(_x.probability, _x.camera_x, _x.camera_y, _x.camera_z))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Class = str[start:end].decode('utf-8')
      else:
        self.Class = str[start:end]
      _x = self
      start = end
      end += 32
      (_x.probability, _x.camera_x, _x.camera_y, _x.camera_z,) = _struct_4d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_4d = struct.Struct("<4d")
