// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <httplib.h>
#include <HTTPRequest.hpp>


namespace myapp {

using cinder::app::KeyEvent;

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

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
