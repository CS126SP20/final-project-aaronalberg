// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#include <homefinder/engine.h>



using nlohmann::json;
using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::endl;
using nlohmann::json;

namespace homefinder {

Engine::Engine(const std::vector<homefinder::City>& cities, const std::vector<double>& responses) {
  all_cities_ = cities;
  responses_ = responses;
}

string Engine::FindIdealCity() {

  // Question indices:
  // Weather(0), Population(1), Crime(2), CoL(3), Healthcare(4), Pollution(5)
  narrowed_list_ = NarrowByPopulation();
  narrowed_list_ = NarrowByWeather();



  return "chicago";
}




std::vector<homefinder::City> Engine::NarrowByPopulation() {
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
  return narrowed_list;
}
std::vector<homefinder::City> Engine::NarrowByWeather() {


  try {
    // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
    http::Request request("http://jsonplaceholder.typicode.com/todos/1");

    // send a get request
    const http::Response response = request.send("GET");
    std::cout << std::string(response.body.begin(), response.body.end()) << '\n'; // print the result

    //writing JSON from request
    json obj;
    stringstream stream;

    stream << std::string(response.body.begin(), response.body.end()) << '\n'; // print the result
    stream >> obj;

  } catch (const std::exception& e) {
    std::cerr << "Request failed, error: " << e.what() << '\n';
  }

  return std::vector<homefinder::City>();

}

} //namespace homefinder
