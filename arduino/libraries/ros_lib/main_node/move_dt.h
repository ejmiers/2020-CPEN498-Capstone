#ifndef _ROS_main_node_move_dt_h
#define _ROS_main_node_move_dt_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace main_node
{

  class move_dt : public ros::Msg
  {
    public:
      typedef int64_t _direction_type;
      _direction_type direction;

    move_dt():
      direction(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_direction;
      u_direction.real = this->direction;
      *(outbuffer + offset + 0) = (u_direction.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_direction.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_direction.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_direction.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_direction.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_direction.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_direction.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_direction.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->direction);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_direction;
      u_direction.base = 0;
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_direction.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->direction = u_direction.real;
      offset += sizeof(this->direction);
     return offset;
    }

    const char * getType(){ return "main_node/move_dt"; };
    const char * getMD5(){ return "acc888e5f8dfeabbbf64aca41aafb072"; };

  };

}
#endif
