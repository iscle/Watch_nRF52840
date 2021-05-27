#include "InfiniPaint.h"
#include "../DisplayApp.h"
#include "../LittleVgl.h"

using namespace Watch::Applications::Screens;

InfiniPaint::InfiniPaint(Watch::Applications::DisplayApp* app, Watch::Components::LittleVgl& lvgl) : Screen(app), lvgl{lvgl} {
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
  std::fill(b, b + bufferSize, LV_COLOR_WHITE);
}

InfiniPaint::~InfiniPaint() {
  // Reset the touchmode
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  lv_obj_clean(lv_scr_act());
}

bool InfiniPaint::Refresh() {
  return running;
}

bool InfiniPaint::OnButtonPushed() {
  running = false;
  return true;
}

bool InfiniPaint::OnTouchEvent(Watch::Applications::TouchEvents event) {
  return true;
}

bool InfiniPaint::OnTouchEvent(uint16_t x, uint16_t y) {
  lv_area_t area;
  area.x1 = x - (width / 2);
  area.y1 = y - (height / 2);
  area.x2 = x + (width / 2) - 1;
  area.y2 = y + (height / 2) - 1;
 // lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);
  lvgl.FlushDisplay(&area, b);
  return true;
}

