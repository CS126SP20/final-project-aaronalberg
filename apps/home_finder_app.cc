// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include "home_finder_app.h"

namespace homefinderapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;

using std::string;
using std::vector;
using std::stringstream;

using nlohmann::json;

const vector<string> kMessages = {
    "Welcome! Select your preferences to find your next home",
    "What is your ideal metropolitan area population?",
    "How important is moderate/likeable weather?",
    "How okay are you with crime?",
    "How okay are you with a high cost of living?",
    "How important is quality healthcare?",
    "How important is good air quality?",
    "The end."};
const vector<string> kDirections = {
    "Enter a value between 0 and 35 million",
    "Enter a percentage between 0 and 99"};
const string kEndingMessage = "Based on your preferences, you should live in: ";
const Color kThemeColor(1,0,0);


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

HomeFinderApp::HomeFinderApp()
  : message_index_{0},
    direction_index_{0},
    ended_{false},
    answering_question_{false},
    city_found_{false},
    center{getWindowCenter()},
    answered_{true},
    is_start_{message_index_ == 0},
    current_response_{""} {}


void HomeFinderApp::setup() {
  cities_ = homefinder::Engine::ParseJSONFile("population.json");
}

void HomeFinderApp::update() {
  center = getWindowCenter();
  if (!is_start_) {
    answering_question_ = true;
  }

  if (message_index_ == kMessages.size() - 1) {
    ended_ = true;
  }

  if (message_index_ != 0) {
    is_start_ = false;
  }
}

void HomeFinderApp::draw() {
  cinder::gl::clear(Color(1,1,1));
  cinder::gl::color(Color(1, 0, 0));
  if (ended_) {
    if (!city_found_) {
      homefinder::Engine engine(cities_, responses_);
      city_result_ = engine.FindIdealCity();
      city_found_ = true;
    }

    DrawEnd();
    return;
  }

  DrawMessage();
  DrawNextButton();
  if (!current_response_.empty()) DrawCurrentResponse();
  if (answering_question_) DrawDirections();
  if (!answered_ && !is_start_) DrawErrorMessage();
}

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
  const cinder::vec2 locp =
      {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void HomeFinderApp::DrawEnd() {
  PrintText(kEndingMessage, Color(0,0,0),
      {500, 100}, {center.x, center.y - 250});
  PrintText(city_result_.name, kThemeColor, {250, 50},
            {center.x, center.y});
  PrintText(city_result_.country, kThemeColor, {150, 100},
            {center.x, center.y + 100});
}

void HomeFinderApp::DrawCurrentResponse() {
  PrintText(current_response_, Color(1,0,0),
      {150,50}, {center.x, center.y});
}

void HomeFinderApp::DrawMessage() {
  const cinder::ivec2 size = {500, 120};
  PrintText(kMessages[message_index_],Color(0,0,0),
      size,{center.x, center.y - 250});
}

void HomeFinderApp::DrawDirections() {
  if (message_index_ == 1) {
    direction_index_ = 0;
  } else {
    direction_index_ = 1;
  }

  PrintText(
      kDirections[direction_index_], Color(0,0,0),
      {350, 85},{center.x, center.y - 175});
}

void HomeFinderApp::DrawErrorMessage() {
  string error = "You must enter a response";
  PrintText(error, Color(1,0,0),
            {350, 85},{center.x, center.y + 300});
}

void HomeFinderApp::DrawNextButton() {
  const cinder::ivec2 size = {100, 70};
  cinder::gl::color(Color(0,0,0));
  cinder::gl::drawSolidRect(Rectf(center.x - 50,
      center.y + 155, center.x + 50, center.y + 210));
  PrintText("Next", kThemeColor,
            size, {center.x, center.y + 200});
}


void HomeFinderApp::keyDown(KeyEvent event) {
  if (!answering_question_) return;
  int key = event.getChar();

  //ASCII codes representing digits 0 - 9
  if (key >= 48 && key <= 57) {

    int cap = 0;
    if (direction_index_ == 0) {
      cap = 8; //number of digits in 35 million
    } else {
      cap = 2; //number of digits in temperature or percentage
    }

    if (current_response_.size() >= cap) {
      if (cap == 8 & std::stoi(current_response_) > 35000000) {
        current_response_ = "";
      }

      return;
    }

    current_response_ += event.getChar();
  } else {
    current_response_ = "";
  }
}

void HomeFinderApp::mouseDown(cinder::app::MouseEvent event) {
  if (!event.isLeftDown()) return;

  //Next button clicked
  if (event.getX() > center.x - 50 &&
  event.getX() < center.x + 50) {
    if (event.getY() > center.y + 155 && event.getY() < center.y + 210) {
      if (current_response_ == "" && !is_start_) {
        answered_ = false;
        return;
      }

      if (!is_start_) responses_.push_back(stod(current_response_));
      current_response_ = "";

      //Cap index so it doesn't go out of bounds
      message_index_++;
      answered_ = true;
      if (message_index_ >= kMessages.size()) {
        message_index_ = kMessages.size() - 1;
      }
    }
  }
}

}  // namespace homefinderapp
