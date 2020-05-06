// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <HTTPRequest.hpp>

#include "city.h"

namespace homefinder {

class Engine {
 public:
  Engine(const std::vector<homefinder::City>& cities,
         const std::vector<double>& responses);
  homefinder::City FindIdealCity();

 private:
  void NarrowByPopulation();
  void NarrowByWeather();
  void GenerateParameterData();
  std::vector<std::vector<double>> CalculateWeights();
  int FindBestMatchIndex(const std::vector<std::vector<double>>& all_weights);

 private:
  std::vector<homefinder::City> all_cities_;
  std::vector<homefinder::City> narrowed_list_;
  std::vector<double> responses_;
};

}  // namespace homefinder

#endif  // FINALPROJECT_ENGINE_H
