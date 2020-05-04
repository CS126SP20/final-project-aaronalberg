// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <HTTPRequest.hpp>
#include <mylibrary/city.h>




namespace homefinderapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

 private:
  void DrawMessage();
  void DrawButtons();
  void DrawNextButton();
  void DrawCurrentResponse();
  void DrawDirections();
  void DrawEnd();
  void DrawErrorMessage();
  std::vector<mylibrary::City> ParseJSON();

 private:
  int message_index_;
  bool answering_question_;
  bool ended_;
  bool answered_;
  bool is_start_;
  cinder::vec2 center;
  std::string current_response_;
  std::string city_;
  std::vector<mylibrary::City> cities_;
};

}  // namespace homefinderapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
