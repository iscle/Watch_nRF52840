#pragma once

namespace Watch {
  namespace Logging {
    class Logger {
      public:
        virtual void Init() = 0;
        virtual void Resume() = 0;
    };
  }
}