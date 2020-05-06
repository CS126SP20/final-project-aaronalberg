// Copyright (c) 2020 Aaron Alberg. All rights reserved.


#include <homefinder/engine.h>


using std::string;
using std::stringstream;
using std::ifstream;
using std::to_string;
using std::vector;
using nlohmann::json;

const string kNumbeoUrl =
    "http://www.numbeo.com:8008/api/indices?api_key=hbtoxypuja22wp&query=";

namespace homefinder {

Engine::Engine(const std::vector<homefinder::City>& cities,
               const std::vector<double>& responses) {
  all_cities_ = cities;
  responses_ = responses;
  narrowed_list_.clear();
}

homefinder::City Engine::FindIdealCity() {

  // Question indices (in responses_ vector):
  // Population(0), Weather(1),  Crime(2), CoL(3), Healthcare(4), Pollution(5)
  NarrowByPopulation();
  GenerateParameterData();

  vector<vector<double>> all_weights = CalculateWeights();
  int best_match_index = FindBestMatchIndex(all_weights);
  return narrowed_list_[best_match_index];
}

// For use in http query
string Engine::RemoveSpaces(const string& to_change) {
  string city_name = to_change;
  while (city_name.find(' ') != string::npos) {
    int space_index = city_name.find(' ');
    city_name.replace(space_index, 1, "%20");
  }

  return city_name;
}

void Engine::GenerateParameterData() {
  for (homefinder::City& city : narrowed_list_) {

    string city_name = RemoveSpaces(city.name);
    homefinder::HTTP request;
    request.MakeRequest(kNumbeoUrl + city_name, city);
  }
}

void Engine::NarrowByPopulation() {
  vector<homefinder::City> narrowed_list;
  double error = .1;

  while (narrowed_list.size() < 10) {
    narrowed_list.clear();

    for (const homefinder::City& city : all_cities_) {
      if (responses_[0] / city.population <= (1 + error) &&
          responses_[0] / city.population >= (1 - error)) {
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

vector<vector<double>> Engine::CalculateWeights() {
  vector<vector<double>> all_cities_weights;
  for (homefinder::City& city : narrowed_list_) {
    vector<double> city_weights;

    // Question indices (in responses_):
    // Population(0), Weather(1), Crime(2), CoL(3), Healthcare(4), Pollution(5)
    for (int i = 1; i < responses_.size(); i++) {
      double parameter_weight;

      switch (i) {
        case 1:
          parameter_weight = responses_[i] * city.climate_index;
          break;
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
std::vector<homefinder::City> Engine::ParseJSONFile(const string& path) {

  std::ifstream json_file;
  json_file.open(
      cinder::app::getAssetPath(path).c_str());
  json population_data = json::parse(json_file);

  vector<homefinder::City> cities;
  for (auto& city : population_data) {
    if (city["population"] == nullptr) {
      break;
    }

    homefinder::City new_city(city["city_ascii"], city["country"],
                              city["population"]);
    cities.push_back(new_city);
  }

  return cities;
}

} //namespace homefinder
