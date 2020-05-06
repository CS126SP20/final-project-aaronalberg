// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include <homefinder/engine.h>
#include <httplib.h>


using nlohmann::json;
using std::string;
using std::stringstream;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using nlohmann::json;

const string kNumbeoUrl =
    "http://www.numbeo.com:8008/api/indices?api_key=hbtoxypuja22wp&query=";
const string kWeatherUrl = "http://api.worldweatheronline.com/premium/v1"
    "/past-weather.ashx?key=e407e5ee8d4e4775885171422200405&date=2009-07-20"
                           "&format=JSON&q=";

namespace homefinder {

Engine::Engine(const std::vector<homefinder::City>& cities,
               const std::vector<double>& responses) {
  all_cities_ = cities;
  responses_ = responses;
  narrowed_list_.clear();
}

homefinder::City Engine::FindIdealCity() {

  // Question indices (in responses_):
  // Weather(0), Population(1), Crime(2), CoL(3), Healthcare(4), Pollution(5)
  NarrowByPopulation();
  //NarrowByWeather();

  GenerateParameterData();
  vector<vector<double>> all_weights = CalculateWeights();
  int best_match_index = FindBestMatchIndex(all_weights);

  return narrowed_list_[0];
}

void Engine::GenerateParameterData() {
  for (homefinder::City& city : narrowed_list_) {
    string city_name = city.name;
    int space_index = city_name.find(' ');
    if (space_index != string::npos) {
      city_name.replace(space_index, 1, "%20");
    }
    json json_object;
    stringstream stream;

    try {
      http::Request request(kNumbeoUrl + city_name);
      http::Response response = request.send("GET");

      stream << std::string(response.body.begin(), response.body.end()) << '\n';
      stream >> json_object;

    } catch (const std::exception& e) {
      std::cerr << "Request failed, error: " << e.what() << '\n';
      std::cerr << "City " << city.name << endl;
    }

    try {
      city.crime_index = json_object["crime_index"];
      city.col_index = json_object["cpi_and_rent_index"];
      city.healthcare_index = json_object["health_care_index"];
      city.pollution_index = json_object["pollution_index"];

      cout << city.crime_index << endl;
      cout << city.col_index << endl;
      cout << city.healthcare_index << endl;
      cout << city.pollution_index << endl;
    } catch (std::exception& e) {
      cout << city.name << endl;
      cout << "ERROR" << endl;
    }


  }
}

void Engine::NarrowByPopulation() {
  vector<homefinder::City> narrowed_list;
  double error = .1;
  while (narrowed_list.size() < 10) {
    narrowed_list.clear();
    for (const homefinder::City& city : all_cities_) {
      if (responses_[1] / city.population <= (1 + error) &&
          responses_[1] / city.population >= (1 - error)) {
        narrowed_list.push_back(city);
      }
    }

    //if not enough are close, slowly increase allowable error
    error += .02;

    while (narrowed_list.size() > 25) {
      narrowed_list.pop_back();
    }
  }

  narrowed_list_ = narrowed_list;
}

void Engine::NarrowByWeather() {

  try {
    // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
    http::Request request(kWeatherUrl + to_string(narrowed_list_[0].lat) +
        "," + to_string(narrowed_list_[0].lng));

    // send a get request
    const http::Response response = request.send("GET");

    // print the result
    std::cout << std::string(response.body.begin(), response.body.end()) << '\n';

    //writing JSON from request
    json obj;
    stringstream stream;

    stream << std::string(response.body.begin(), response.body.end()) << '\n';
    stream >> obj;
    cout << "HERE" << endl;
    cout << obj["data"]["weather"][0]["maxtempF"] << endl;

  } catch (const std::exception& e) {
    std::cerr << "Request failed, error: " << e.what() << '\n';
  }

}

vector<vector<double>> Engine::CalculateWeights() {
  vector<vector<double>> all_cities_weights;
  for (homefinder::City& city : narrowed_list_) {
    vector<double> city_weights;

    // Question indices (in responses_):
    // Weather(0), Population(1), Crime(2), CoL(3), Healthcare(4), Pollution(5)
    for (int i = 2; i < responses_.size(); i++) {
      double parameter_weight;

      switch (i) {
        case 2:
          parameter_weight = responses_[i] * city.crime_index;
          break;
        case 3:
          parameter_weight = responses_[i] * city.col_index;
          break;
        case 4:
          parameter_weight = responses_[i] * city.healthcare_index;
          break;
        case 5:
          parameter_weight = responses_[i] * city.pollution_index;
          break;
      }

      city_weights.push_back(parameter_weight);
    }

    all_cities_weights.push_back(city_weights);
  }

  return all_cities_weights;
}

int Engine::FindBestMatchIndex(const vector<vector<double>>& all_weights) {
  vector<double> to_compare;
  for (const vector<double>& list : all_weights) {
    double total_weight = 0;
    for (const double& weight : list) {
      total_weight += weight;
    }

    to_compare.push_back(total_weight);
  }

  int best_match_index = 0;
  int highest_weight = 0;
  for (int i = 0; i < to_compare.size(); i++) {
    if (to_compare[i] > highest_weight) {
      best_match_index = i;
      highest_weight = to_compare[i];
    }
  }

  return best_match_index;
}

} //namespace homefinder
