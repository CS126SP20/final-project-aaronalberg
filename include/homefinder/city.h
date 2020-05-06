#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-non-private-member-variables-in-classes"
// Copyright (c) 2020 Aaron Alberg. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <string>


namespace homefinder {

struct City {
  City();
 public:
  City(const std::string& name, const std::string& country,
       const double& population);

  std::string name;
  std::string country;
  double population;

  double climate_index;
  double crime_index;
  double healthcare_index;
  double pollution_index;
  double col_index; //Cost of Living

};

}  // namespace homefinder


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#pragma clang diagnostic pop