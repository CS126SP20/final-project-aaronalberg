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

Engine::Engine(const std::vector<homefinder::City>& cities, const std::vector<double>& responses) {
  all_cities_ = cities;
  responses_ = responses;
}

string Engine::FindIdealCity() {

  // Question indices (in responses_):
  // Weather(0), Population(1), Crime(2), CoL(3), Healthcare(4), Pollution(5)
  NarrowByPopulation();
  //NarrowByWeather();

  GenerateParameterData();
  NarrowByCrime();
  NarrowByCoL();
  NarrowByHealthcare();
  NarrowByPollution();

  try {
    string result = narrowed_list_[0].name;
    return result;
  } catch (std::exception& exception) {
    return "Chicago"; // Default just in case
  }
}

void Engine::GenerateParameterData() {
  for (homefinder::City& city : narrowed_list_) {
    try {

      string city_name = city.name;
      int space_index = city_name.find(' ');
      if (space_index != string::npos) {
        city_name.replace(space_index, 1, "%20");
      }

      string url = kNumbeoUrl + city_name;
      http::Request request(url);

      // send a get request
      http::Response response = request.send("GET");

      // print the result
      std::cout << std::string(response.body.begin(), response.body.end()) << '\n';

      //writing JSON from request
      nlohmann::json obj;
      stringstream stream;

      stream << std::string(response.body.begin(), response.body.end()) << '\n';
      stream >> obj;

      city.crime_index = obj["crime_index"];
      city.healthcare_index = obj["health_care_index"];
      city.col_index = obj["cpi_and_rent_index"];
      city.pollution_index = obj["pollution_index"];

      cout << city.pollution_index << endl;
      cout << city.name << endl;
      cout << city.crime_index << endl;
      cout << city.population << endl;

    } catch (const std::exception& e) {
      std::cerr << "Request failed, error: " << e.what() << '\n';
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

    error += .02;
  }

  //cout << narrowed_list.size() << "  size" << endl;
  //cout << narrowed_list[3].name << endl;
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

void Engine::NarrowByCrime() {
}

void Engine::NarrowByCoL() {
}

void Engine::NarrowByHealthcare() {
}

void Engine::NarrowByPollution() {
}


} //namespace homefinder
