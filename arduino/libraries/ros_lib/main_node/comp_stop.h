#ifndef _ROS_main_node_comp_stop_h
#define _ROS_main_node_comp_stop_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace main_node
{

  class comp_stop : public ros::Msg
  {
    public:
      typedef int64_t _stop_type;
      _stop_type stop;

    comp_stop():
      stop(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_stop;
      u_stop.real = this->stop;
      *(outbuffer + offset + 0) = (u_stop.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_stop.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_stop.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_stop.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_stop.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_stop.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_stop.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_stop.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->stop);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_stop;
      u_stop.base = 0;
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_stop.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->stop = u_stop.real;
      offset += sizeof(this->stop);
     return offset;
    }

    const char * getType(){ return "main_node/comp_stop"; };
    const char * getMD5(){ return "839f326c2e6df1e173665bdc360e82bd"; };

  };

}
#endif
