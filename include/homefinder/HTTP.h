// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_HTTP_H
#define FINALPROJECT_HTTP_H

#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "city.h"
#include "engine.h"

namespace homefinder {

class HTTP {
 public:
  HTTP();
  void AddAPIData(const std::string& url, homefinder::City&);
};



} //namespace homefinder

#endif  // FINALPROJECT_HTTP_H
