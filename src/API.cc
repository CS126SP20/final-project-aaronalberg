// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include "homefinder/API.h"

using std::stringstream;
using std::string;
using nlohmann::json;
using homefinder::City;

using std::endl;

namespace homefinder {

API::API() = default;

void API::AddAPIData(const string &url, homefinder::City& city) {
  json json_object;
  stringstream stream;

  try {
    http::Request request(url);
    http::Response response = request.send("GET");

    stream << std::string(response.body.begin(), response.body.end()) << '\n';
    stream >> json_object;

  } catch (const std::exception& e) {
    std::cerr << "Request failed, error: " << e.what() << '\n';
    std::cerr << "City " << city.name << endl;
  }

  try {
    city.crime_index = json_object["crime_index"];
  } catch (std::exception& e) {
    city.crime_index = 0;
  }

  try {
    city.col_index = json_object["cpi_and_rent_index"];

    //For some reason API data is skewed incorrectly towards high CoL areas
    if (city.col_index > 80) {
      city.col_index = 80;
    }

  } catch (std::exception& e) {
    city.col_index = 0;
  }

  try {
    city.healthcare_index = json_object["health_care_index"];
  } catch (std::exception& e) {
    city.healthcare_index = 0;
  }

  try {
    city.pollution_index = json_object["pollution_index"];
  } catch (std::exception& e) {
    city.pollution_index = 0;
  }

  try {
    city.climate_index = json_object["climate_index"];
  } catch (std::exception& e) {
    city.climate_index = 0;
  }

}

} //namespace homefinder
