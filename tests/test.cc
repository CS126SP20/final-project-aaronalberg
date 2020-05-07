// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <homefinder/city.h>
#include <homefinder/engine.h>
#include <catch2/catch.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("City constructor", "[constructor][city]") {
  homefinder::City
      city("Chicago", "USA", 3000000);
  REQUIRE(city.name == "Chicago");
  REQUIRE(city.country == "USA");
  REQUIRE(city.population == 3000000);
}

TEST_CASE("JSON file parsing", "[json-parse]") {
  std::vector<homefinder::City> cities =
      homefinder::Engine::ParseJSONFile("population.json");
  REQUIRE(cities.size() == 5336); //number with all fields not null

  SECTION("Tokyo") {
    REQUIRE(cities[0].name == "Tokyo");
    REQUIRE(cities[0].population == 35676000);
    REQUIRE(cities[0].country == "Japan");
  }

  SECTION("Chicago") {
    REQUIRE(cities[24].name == "Chicago");
    REQUIRE(cities[24].population == 8675982);
    REQUIRE(cities[24].country == "United States");
  }

  SECTION("Nakhodka") {
    REQUIRE(cities[2449].name == "Nakhodka");
    REQUIRE(cities[2449].population == 159551);
    REQUIRE(cities[2449].country == "Russia");
  }

  SECTION("Bad file path") {
    std::vector<homefinder::City> list =
        homefinder::Engine::ParseJSONFile("anypath.flarp");
    REQUIRE(list.empty());
  }
}

// Helper functions indirectly tested through this function, as per Piazza
TEST_CASE("Find ideal city", "[engine]") {
  std::vector<homefinder::City> cities =
      homefinder::Engine::ParseJSONFile("population.json");
  homefinder::Engine engine;

  //Test that the population of the result is actually close to the input
  SECTION("Top ten cities") {
    std::vector<double> responses = {35000000, 12, 35, 54, 34, 67};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "Los Angeles");
    REQUIRE(result.population / 35000000 <= 1.2);
    REQUIRE(result.population / 35000000 >= .36); //this is normal for huge cities
  }

  SECTION("Moderate sized cities") {
    std::vector<double> responses = {8000000, 12, 35, 54, 34, 67};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "London");
    REQUIRE(result.population / 8000000 <= 1.2);
    REQUIRE(result.population / 8000000 >= .80);
  }

  SECTION("Small cities") {
    std::vector<double> responses = {500000, 12, 35, 54, 34, 67};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "Bloemfontein");
    REQUIRE(result.population / 500000 <= 1.2);
    REQUIRE(result.population / 500000 >= .80);
  }

  SECTION("Bad inputs") {
    std::vector<double> responses;
    std::vector<homefinder::City> empty_cities;
    homefinder::City result = engine.FindIdealCity(responses, cities);
    homefinder::City result2 = engine.FindIdealCity(responses, empty_cities);
    REQUIRE(result.name == "Chicago");
    REQUIRE(result2.name == "Chicago");
  }

  SECTION("Checking manual calculation") {
    std::vector<double> responses = {2340567, 40, 40, 40, 40, 40};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "Daegu");
    REQUIRE(result.country == "Korea, South");
  }

  SECTION("Zero population input") {
    std::vector<double> responses = {0, 40, 40, 40, 40, 40};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "Fada");
    REQUIRE(result.country == "Chad");
  }

  SECTION("Some zeros input") {
    std::vector<double> responses = {1000000, 0, 25, 0, 35, 0};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "Suwon");
    REQUIRE(result.country == "Korea, South");
  }

  SECTION("All zeros input") {
    std::vector<double> responses = {0, 0, 0, 0, 0, 0};
    homefinder::City result = engine.FindIdealCity(responses, cities);
    REQUIRE(result.name == "Lata");
    REQUIRE(result.population < 1000);
    REQUIRE(result.country == "Solomon Islands");
  }
}

TEST_CASE("Get API data with HTTP request", "[http-request]") {
  std::string url =
      "http://www.numbeo.com:8008/api/indices?api_key=hbtoxypuja22wp&query=";

  SECTION("Chicago") {
    homefinder::City city("Chicago", "USA", 3000000);
    homefinder::API::AddAPIData(url + city.name, city);
    REQUIRE(city.crime_index == 63.84484471054925);
    REQUIRE(city.climate_index == 66.11013761898052);
    REQUIRE(city.pollution_index == 42.60552407070931);
    REQUIRE(city.healthcare_index == 67.9819243213438);
    REQUIRE(city.col_index == 70.0511382127554);
  }

  SECTION("Bloomington") {
    homefinder::City city("Bloomington", "USA", 3000000);
    homefinder::API::AddAPIData(url + city.name, city);
    REQUIRE(city.crime_index == 32.14285714285714);
    REQUIRE(city.climate_index == 70.82928724340961);
    REQUIRE(city.pollution_index == 33.97877984084881);
    REQUIRE(city.healthcare_index == 70.83333333333333);
    REQUIRE(city.col_index == 65.57940637010005);
  }

  SECTION("Bad URL") {
    homefinder::City city("test", "test", 500);
    homefinder::API::AddAPIData(url, city);
    REQUIRE(city.crime_index == 0);
    REQUIRE(city.climate_index == 0);
    REQUIRE(city.pollution_index == 0);
    REQUIRE(city.healthcare_index == 0);
    REQUIRE(city.col_index == 0);
  }

  SECTION("City with some unavailable data") {
    homefinder::City city("Notre%20Dame", "USA", 3000000);
    homefinder::API::AddAPIData(url + city.name, city);
    REQUIRE(city.crime_index == 64.46078431372548);
    REQUIRE(city.climate_index == 65.83587758231477);
    REQUIRE(city.pollution_index == 9.195402298850574);
    REQUIRE(city.healthcare_index == 62.5);
    REQUIRE(city.col_index == 0);
  }
}

TEST_CASE("Remove spaces", "[engine]") {
  SECTION("No spaces to remove") {
    REQUIRE(homefinder::Engine::RemoveSpaces("Chicago") == "Chicago");
    REQUIRE(homefinder::Engine::RemoveSpaces("Lexington") == "Lexington");
  }

  SECTION("One space to remove") {
    REQUIRE(homefinder::Engine::RemoveSpaces("Sao Paulo") == "Sao%20Paulo");
    REQUIRE(homefinder::Engine::RemoveSpaces("New York") == "New%20York");
  }

  SECTION("Two spaces to remove") {
    REQUIRE(homefinder::Engine::RemoveSpaces("La Vera Cruz")
            == "La%20Vera%20Cruz");
  }

  SECTION("Bad inputs") {
    REQUIRE(homefinder::Engine::RemoveSpaces(" ") == "%20");
    REQUIRE(homefinder::Engine::RemoveSpaces("  ") == "%20%20");
    REQUIRE(homefinder::Engine::RemoveSpaces("") == "");
    REQUIRE(homefinder::Engine::RemoveSpaces("\\s+") == "\\s+");
    REQUIRE(homefinder::Engine::RemoveSpaces("\t") == "\t");
  }
}