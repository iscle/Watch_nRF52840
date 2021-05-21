#pragma once

// Do not edit this file, it is automatically generated by CMAKE!

namespace Watch {
  class Version {
    public:
      static constexpr uint32_t Major() {return major;}
      static constexpr uint32_t Minor() {return minor;}
      static constexpr uint32_t Patch() {return patch;}
      static constexpr const char* VersionString() {return versionString;}
    private:
      static constexpr uint32_t major = 0;
      static constexpr uint32_t minor = 14;
      static constexpr uint32_t patch = 7;
      static constexpr const char* versionString = "0.14.7";
  };
}
