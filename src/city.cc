// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include <homefinder/city.h>

namespace homefinder {

City::City(const std::string& name, const double& population, const double& lat,
           const double& lng) {
  this->name = name;
  this->population = population;
  this->lat = lat;
  this->lng = lng;
}
}  // namespace homefinder
