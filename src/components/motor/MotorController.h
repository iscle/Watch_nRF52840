#include <cstdint>

#ifdef __cplusplus
 extern "C" {
#endif 

        void MotorControllerInit();
        void MotorControllerSetDuration(uint32_t motorDuration);
        void MotorControllerStop();

#ifdef __cplusplus
}
#endif
