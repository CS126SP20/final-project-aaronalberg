// Copyright (c) 2020 Aaron Alberg. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H


#include <cinder/app/AppBase.h>
#include <HTTPRequest.hpp>
#include <nlohmann/json.hpp>
#include "city.h"
#include "HTTP.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace homefinder {

class Engine {
 public:
  Engine();
  homefinder::City FindIdealCity(const std::vector<double>& responses,
                                 const std::vector<homefinder::City>& cities);
  static std::vector<homefinder::City> ParseJSONFile(const std::string& path);

  //public only for testing purposes only
  static std::string RemoveSpaces(const std::string& to_change);

 private:
  void NarrowByPopulation(const double& population, const std::vector<homefinder::City>& cities);
  void GenerateParameterData();
  std::vector<std::vector<double>> CalculateWeights(const std::vector<double>& responses);
  int FindBestMatchIndex(const std::vector<std::vector<double>>& all_weights);

 private:
  std::vector<homefinder::City> narrowed_list_;
};

}  // namespace homefinder

#endif  // FINALPROJECT_ENGINE_H
