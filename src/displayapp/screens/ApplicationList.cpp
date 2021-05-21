#include "ApplicationList.h"
#include <lvgl/lvgl.h>
#include <array>
#include "Symbols.h"
//#include "Tile.h"
#include "displayapp/Apps.h"
#include "../DisplayApp.h"

using namespace Watch::Applications::Screens;

ApplicationList::ApplicationList(Watch::Applications::DisplayApp *app) :
        Screen(app),
        screens{app, {
                [this]() -> std::unique_ptr<Screen> { return CreateScreen1(); },
               // [this]() -> std::unique_ptr<Screen> { return CreateScreen2(); },
               // [this]() -> std::unique_ptr<Screen> { return CreateScreen3(); }
          }
        } {}


ApplicationList::~ApplicationList() {
  lv_obj_clean(lv_scr_act());
}

bool ApplicationList::Refresh() {
  if(running)
    running = screens.Refresh();
  return running;
}

bool ApplicationList::OnButtonPushed() {
  running = false;
  app->StartApp(Apps::Clock);
  return true;
}

bool ApplicationList::OnTouchEvent(Watch::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}
/*
std::unique_ptr<Screen> ApplicationList::CreateScreen1() {
  std::array<Screens::Tile::Applications, 6> applications {
          {{Symbols::none, Apps::None},
          {Symbols::none, Apps::None},          
          {Symbols::none, Apps::None},
          {Symbols::none, Apps::None},
          {Symbols::none, Apps::None},
          {Symbols::none, Apps::None}
          }
  };
  return std::unique_ptr<Screen>(new Screens::Tile(app, applications));
}
*/
/*
std::unique_ptr<Screen> ApplicationList::CreateScreen2() {
  std::array<Screens::Tile::Applications, 6> applications {
          {{"A", Apps::None},
           {"B", Apps::None},           
                  {Symbols::none, Apps::None},
                  {Symbols::none, Apps::None},
                  {Symbols::none, Apps::None},
                  {Symbols::none, Apps::None}
          }
  };

  return std::unique_ptr<Screen>(new Screens::Tile(app, applications));
}


std::unique_ptr<Screen> ApplicationList::CreateScreen3() {
  std::array<Screens::Tile::Applications, 6> applications {
          {{"A", Apps::None},
           {"B", Apps::None},
           {"C", Apps::None},
           {Symbols::none, Apps::None},
           {Symbols::none, Apps::None},
           {Symbols::none, Apps::None}
          }
  };

  return std::unique_ptr<Screen>(new Screens::Tile(app, applications));
}
*/