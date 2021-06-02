#include <legacy/nrf_drv_clock.h>
#include <softdevice/common/nrf_sdh.h>
#include <drivers/SpiMaster.h>
#include <drivers/Spi.h>
#include <drivers/SpiNorFlash.h>
#include <libraries/log/nrf_log.h>
#include "bootloader/boot_graphics.h"
#include <FreeRTOS.h>
#include <task.h>
#include <legacy/nrf_drv_gpiote.h>
#include <libraries/gpiote/app_gpiote.h>
#include <hal/nrf_wdt.h>
#include <cstring>
#include <components/gfx/Gfx.h>
#include <drivers/St7789.h>
#include "SEGGER_RTT.h" 
#if NRF_LOG_ENABLED
#include "logging/NrfLogger.h"
Watch::Logging::NrfLogger logger;
#else
#include "logging/DummyLogger.h"
Watch::Logging::DummyLogger logger;
#endif

static constexpr uint8_t pinSpiSck = 16;
static constexpr uint8_t pinSpiMosi = 14;
static constexpr uint8_t pinSpiMiso = 15;
static constexpr uint8_t pinSpiFlashCsn = 23;
static constexpr uint8_t pinLcdCsn = 22;
static constexpr uint8_t pinLcdDataCommand = 11;
static constexpr uint8_t pinTwiScl = 6;
static constexpr uint8_t pinTwiSda = 7;
static constexpr uint8_t touchPanelTwiAddress = 0x15;
static constexpr uint8_t motionSensorTwiAddress = 0x1e;
static constexpr uint8_t pinSpiAccCsn = 8;

Watch::Drivers::SpiMaster spi{Watch::Drivers::SpiMaster::SpiModule::SPI0, {
        Watch::Drivers::SpiMaster::BitOrder::Msb_Lsb,
        Watch::Drivers::SpiMaster::Modes::Mode3,
        Watch::Drivers::SpiMaster::Frequencies::Freq8Mhz,
        pinSpiSck,
        pinSpiMosi,
        pinSpiMiso
  }
};
Watch::Drivers::Spi flashSpi{spi, pinSpiFlashCsn};
Watch::Drivers::SpiNorFlash spiNorFlash{flashSpi};

Watch::Drivers::Spi lcdSpi {spi, pinLcdCsn};
Watch::Drivers::St7789 lcd {lcdSpi, pinLcdDataCommand};

//Watch::Components::Gfx gfx{lcd};

extern "C" {
void vApplicationIdleHook(void) {

}

void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void) {
  if(((NRF_SPIM0->INTENSET & (1<<6)) != 0) && NRF_SPIM0->EVENTS_END == 1) {
    NRF_SPIM0->EVENTS_END = 0;
    spi.OnEndEvent();
  }

  if(((NRF_SPIM0->INTENSET & (1<<19)) != 0) && NRF_SPIM0->EVENTS_STARTED == 1) {
    NRF_SPIM0->EVENTS_STARTED = 0;
    spi.OnStartedEvent();
  }

  if(((NRF_SPIM0->INTENSET & (1<<1)) != 0) && NRF_SPIM0->EVENTS_STOPPED == 1) {
    NRF_SPIM0->EVENTS_STOPPED = 0;
  }
}
}

void Process(void* instance) {
  // Wait before erasing the memory to let the time to the SWD debugger to flash a new firmware before running this one.
  vTaskDelay(5000);

  APP_GPIOTE_INIT(2);

  NRF_LOG_INFO("Init...");
  spi.Init();
  spiNorFlash.Init();
  spiNorFlash.Wakeup();
  lcd.Init();
  //gfx.Init();
  NRF_LOG_INFO("Init Done!")
/*
  NRF_LOG_INFO("Erasing...");
  for (uint32_t erased = 0; erased < graphicSize; erased += 0x1000) {
    spiNorFlash.SectorErase(erased);
  }
  NRF_LOG_INFO("Erase done!");

  NRF_LOG_INFO("Writing graphic...");
  static constexpr uint32_t memoryChunkSize = 200;
  uint8_t writeBuffer[memoryChunkSize];
  for(int offset = 0; offset < 115200; offset+=memoryChunkSize) {
    std::memcpy(writeBuffer, &graphicBuffer[offset], memoryChunkSize);
    spiNorFlash.Write(offset, writeBuffer, memoryChunkSize);
  }
  NRF_LOG_INFO("Writing graphic done!");

  NRF_LOG_INFO("Read memory and display the graphic...");
  static constexpr uint32_t screenWidth = 240;
  static constexpr uint32_t screenWidthInBytes = screenWidth*2; // LCD display 16bits color (1 pixel = 2 bytes)
  uint16_t displayLineBuffer[screenWidth];
  for(uint32_t line = 0; line < screenWidth; line++) {
    spiNorFlash.Read(line*screenWidthInBytes, reinterpret_cast<uint8_t *>(displayLineBuffer), screenWidth);
    spiNorFlash.Read((line*screenWidthInBytes)+screenWidth, reinterpret_cast<uint8_t *>(displayLineBuffer) + screenWidth, screenWidth);
    for(uint32_t col = 0; col < screenWidth; col++) {
      gfx.pixel_draw(col, line, displayLineBuffer[col]);
    }
  }

  NRF_LOG_INFO("Done!");
*/
  while(1) {
    asm("nop" );
  }
}
void  led_init(uint8_t pin_number){
nrf_gpio_cfg_output(pin_number);
nrf_gpio_pin_set(pin_number); 
}

int main(void) {
  TaskHandle_t taskHandle;
  nrf_drv_clock_init();
  led_init(2);
  if (pdPASS != xTaskCreate(Process, "MAIN", 512, nullptr, 0, &taskHandle))
    APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);

  vTaskStartScheduler();

  for (;;) {
    APP_ERROR_HANDLER(NRF_ERROR_FORBIDDEN);
  }
}
