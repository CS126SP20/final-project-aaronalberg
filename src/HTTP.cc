// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include "homefinder/HTTP.h"

using std::stringstream;
using std::string;
using nlohmann::json;
using homefinder::City;

using std::endl;

namespace homefinder {

HTTP::HTTP() = default;

void HTTP::MakeRequest(const string &url, City& city, bool is_weather) {
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

  if (!is_weather) {
    try {
      city.crime_index = json_object["crime_index"];
    } catch (std::exception& e) {
      city.crime_index = 0;
    }

    try {
      city.col_index = json_object["cpi_and_rent_index"];
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
  }
}

} //namespace homefinder
