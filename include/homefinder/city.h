#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-non-private-member-variables-in-classes"
// Copyright (c) 2020 Aaron Alberg. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <string>


namespace homefinder {

struct City {
  City(const std::string& name, const double& population,
       const double& lat, const double& lng);
  std::string name;
  double population;
  double temperature;
  double crime_index;
  double healthcare_index;
  double lat;
  double lng;

};

}  // namespace homefinder


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#pragma clang diagnostic pop