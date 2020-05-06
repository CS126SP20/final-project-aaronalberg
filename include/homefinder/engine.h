// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H


#include <cinder/app/AppBase.h>
#include "city.h"
#include "HTTP.h"

#include <HTTPRequest.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace homefinder {

class Engine {
 public:
  Engine(const std::vector<homefinder::City>& cities,
         const std::vector<double>& responses);
  homefinder::City FindIdealCity();
  static std::vector<homefinder::City> ParseJSONFile(const std::string& path);

  //public only for testing purposes only
  static std::string RemoveSpaces(const std::string& to_change);

 private:
  void NarrowByPopulation();
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
