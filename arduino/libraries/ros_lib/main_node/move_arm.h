#ifndef _ROS_main_node_move_arm_h
#define _ROS_main_node_move_arm_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace main_node
{

  class move_arm : public ros::Msg
  {
    public:
      typedef int64_t _move_type;
      _move_type move;

    move_arm():
      move(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_move;
      u_move.real = this->move;
      *(outbuffer + offset + 0) = (u_move.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_move.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_move.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_move.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_move.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_move.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_move.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_move.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->move);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_move;
      u_move.base = 0;
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_move.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->move = u_move.real;
      offset += sizeof(this->move);
     return offset;
    }

    const char * getType(){ return "main_node/move_arm"; };
    const char * getMD5(){ return "914ff1f14bec6dca55c0a9db6e0d727d"; };

  };

}
#endif
