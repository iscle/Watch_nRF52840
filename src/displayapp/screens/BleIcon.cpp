#include "BleIcon.h"
#include "Symbols.h"
using namespace Watch::Applications::Screens;

const char* BleIcon::GetIcon(bool isConnected) {
  if(isConnected) return Symbols::bluetoothFull;
  else return "";
}

