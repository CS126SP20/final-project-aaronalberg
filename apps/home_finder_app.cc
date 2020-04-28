// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include "home_finder_app.h"

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <HTTPRequest.hpp>

namespace homefinderapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::string;
using std::vector;

const vector<string> kMessages = {
    "Welcome! Select your preferences to find your next home",
    "How important is low crime?",
    "How important is low cost of living?",
    "What is your ideal temperature?"};
#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
#endif

MyApp::MyApp() { }

void MyApp::setup() {
  message_index_ = 0;
  try
  {
    // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
    http::Request request("http://jsonplaceholder.typicode.com/todos/1");

    // send a get request
    const http::Response response = request.send("GET");
    std::cout << std::string(response.body.begin(), response.body.end()) << '\n'; // print the result
  }
  catch (const std::exception& e)
  {
    std::cerr << "Request failed, error: " << e.what() << '\n';
  }
}

void MyApp::update() { }

//Function courtesy of CS126 Snake MP
template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::draw() {
  cinder::gl::clear(Color(1,1,1));
  cinder::gl::color(Color(1, 0, 0));
  DrawMessage();
  DrawButtons();

}

void MyApp::DrawMessage() {
  //message_index_ = 1;
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 120};
  PrintText(kMessages[message_index_], Color(0,0,0), size,{center.x, center.y - 250});
}

void MyApp::DrawButtons() {
  DrawNextButton();
  if (message_index_ == 0) {
    return;
  }


}

void MyApp::DrawNextButton() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {100, 70};
  cinder::gl::color(Color(.3,.3,.3));
  cinder::gl::drawSolidRect(Rectf(
      center.x - 50, center.y + 155,
      center.x + 50, center.y + 210));

  PrintText("Next", Color(0.878, 0.764, 0.956),
            size, {center.x, center.y + 200});
}


void MyApp::keyDown(KeyEvent event) { }

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  const cinder::vec2 center = getWindowCenter();
  if (!event.isLeftDown()) return;

  //Next button clicked
  if (event.getX() > center.x - 50 && event.getX() < center.x + 50) {
    if (event.getY() > center.y + 155 && event.getY() < center.y + 210) {
      message_index_++;

      //Not exceeding bounds for index
      if (message_index_ >= kMessages.size()) {
        message_index_ = kMessages.size() - 1;
      }
    }
  }
}

}  // namespace homefinderapp
