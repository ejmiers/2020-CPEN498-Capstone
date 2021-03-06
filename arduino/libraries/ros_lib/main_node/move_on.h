#ifndef _ROS_main_node_move_on_h
#define _ROS_main_node_move_on_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace main_node
{

  class move_on : public ros::Msg
  {
    public:
      typedef int64_t _moveOn_type;
      _moveOn_type moveOn;

    move_on():
      moveOn(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_moveOn;
      u_moveOn.real = this->moveOn;
      *(outbuffer + offset + 0) = (u_moveOn.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_moveOn.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_moveOn.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_moveOn.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_moveOn.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_moveOn.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_moveOn.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_moveOn.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->moveOn);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_moveOn;
      u_moveOn.base = 0;
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_moveOn.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->moveOn = u_moveOn.real;
      offset += sizeof(this->moveOn);
     return offset;
    }

    const char * getType(){ return "main_node/move_on"; };
    const char * getMD5(){ return "3d670e891fb65617d0b5d6a2f4722989"; };

  };

}
#endif
