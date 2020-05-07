// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_API_H
#define FINALPROJECT_API_H

#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "city.h"
#include "engine.h"

namespace homefinder {

class API {
 public:
  API();
  static void AddAPIData(const std::string& url, homefinder::City&);
};



} //namespace homefinder

#endif  // FINALPROJECT_API_H
