// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <httplib.h>
#include <HTTPRequest.hpp>

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::string;

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
  cinder::gl::clear(Color(.9,.9,.9));
  cinder::gl::color(Color(1, 0, 0));
  Rectf texture = Rectf(getWindowWidth() / 2, getWindowHeight() / 2,
      getWindowWidth() / 2 + 100, getWindowHeight() / 2 + 100);
  cinder::gl::drawSolidRect(texture);

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 75};
  PrintText("Welcome!", Color(0,0,0), size, {center.x, center.y - 300});
  PrintText("Select your preferences to find your next home",
      Color(0,0,0), size, {center.x, center.y - 200});

}



void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
