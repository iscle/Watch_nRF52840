#pragma once

#include <functional>

namespace Watch {
  namespace Controllers{
    class BleClient {
      public:
        virtual void Discover(uint16_t connectionHandle, std::function<void(uint16_t)> lambda) = 0;
    };
  }
}