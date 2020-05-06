// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_HTTP_H
#define FINALPROJECT_HTTP_H

#include <string>
#include <nlohmann/json.hpp>
#include <homefinder/city.h>
#include <homefinder/engine.h>

namespace homefinder {

class HTTP {
 public:
  HTTP();
  void MakeRequest(const std::string& url, homefinder::City&, bool is_weather);
};



} //namespace homefinder

#endif  // FINALPROJECT_HTTP_H
