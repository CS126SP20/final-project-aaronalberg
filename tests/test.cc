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

TEST_CASE("JSON file parsing", "[json][parse]") {
  std::vector<homefinder::City> cities =
      homefinder::Engine::ParseJSONFile("population.json");
  REQUIRE(cities.size() == 5336); //number with all fields not null

  SECTION("Tokyo") {
    REQUIRE(cities[0].name == "Tokyo");
    REQUIRE(cities[0].population == 35676000);
    REQUIRE(cities[0].country == "Japan");
  }

  SECTION ("Chicago") {
    REQUIRE(cities[24].name == "Chicago");
    REQUIRE(cities[24].population == 8675982);
    REQUIRE(cities[24].country == "United States");
  }

  SECTION ("Nakhodka") {
    REQUIRE(cities[2449].name == "Nakhodka");
    REQUIRE(cities[2449].population == 159551);
    REQUIRE(cities[2449].country == "Russia");
  }
}

TEST_CASE("Narrow by population", "[engine][narrow]") {

}

TEST_CASE("Generate Parameters", "[engine][") {

}

TEST_CASE("HTTP Request", "[http-request]") {

}

TEST_CASE("Remove spaces", "[engine][helper]") {
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
    REQUIRE(homefinder::Engine::RemoveSpaces("") == "");
  }
}