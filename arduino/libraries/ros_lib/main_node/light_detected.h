#ifndef _ROS_main_node_light_detected_h
#define _ROS_main_node_light_detected_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace main_node
{

  class light_detected : public ros::Msg
  {
    public:
      typedef int64_t _detected_type;
      _detected_type detected;

    light_detected():
      detected(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_detected;
      u_detected.real = this->detected;
      *(outbuffer + offset + 0) = (u_detected.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_detected.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_detected.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_detected.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_detected.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_detected.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_detected.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_detected.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->detected);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_detected;
      u_detected.base = 0;
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_detected.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->detected = u_detected.real;
      offset += sizeof(this->detected);
     return offset;
    }

    const char * getType(){ return "main_node/light_detected"; };
    const char * getMD5(){ return "23f88efd171b2e5dc0ad9793b17bca9d"; };

  };

}
#endif
