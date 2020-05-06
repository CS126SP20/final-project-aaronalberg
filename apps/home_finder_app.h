// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <nlohmann/json.hpp>
#include <HTTPRequest.hpp>
#include <homefinder/city.h>
#include <homefinder/city.h>
#include <homefinder/engine.h>

namespace homefinderapp {

class HomeFinderApp : public cinder::app::App {
 public:
  HomeFinderApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

 private:
  void DrawMessage();
  void DrawNextButton();
  void DrawCurrentResponse();
  void DrawDirections();
  void DrawEnd();
  void DrawErrorMessage();

 private:
  int message_index_;
  int direction_index_;
  bool answering_question_;
  bool ended_;
  bool answered_;
  bool is_start_;
  bool city_found_;
  cinder::vec2 center;
  std::string current_response_;
  homefinder::City city_result_;
  std::vector<homefinder::City> cities_;
  std::vector<double> responses_;
};

}  // namespace homefinderapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
