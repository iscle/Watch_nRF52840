#pragma once
#include <cstddef>

namespace Watch {
  namespace Drivers {
    class BufferProvider {
      public:
        virtual bool GetNextBuffer(uint8_t** buffer, size_t& size) = 0;
    };
  }
}