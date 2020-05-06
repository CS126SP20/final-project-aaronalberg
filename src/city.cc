// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include <homefinder/city.h>

namespace homefinder {

City::City() = default;

City::City(const std::string& name, const std::string& country,
           const double& population) {
  this->name = name;
  this->population = population;
  this->country = country;
}

}  // namespace homefinder
