// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <httplib.h>



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

 private:
  int message_index_;
  bool answering_question_;
  std::string current_response_;
};

}  // namespace homefinderapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
