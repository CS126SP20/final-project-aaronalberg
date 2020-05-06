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
      city("Chicago", "USA", 3000000, 50, 50);
  REQUIRE(city.name == "Chicago");
  REQUIRE(city.country == "USA");
  REQUIRE(city.population == 3000000);
  REQUIRE(city.lat == 50);
  REQUIRE(city.lng == 50);
}

TEST_CASE("JSON file parsing", "[json][parse]") {
  std::vector<homefinder::City> cities =
      homefinder::Engine::ParseJSONFile("population.json");
  REQUIRE(cities.size() == 5336); //number with all fields not null

  SECTION("Tokyo") {
    REQUIRE(cities[0].name == "Tokyo");
    REQUIRE(cities[0].population == 35676000);
    REQUIRE(cities[0].country == "Japan");
    REQUIRE(cities[0].lat == 35.685);
    REQUIRE(cities[0].lng == 139.7514);
  }

  SECTION ("Chicago") {
    REQUIRE(cities[24].name == "Chicago");
    REQUIRE(cities[24].population == 8675982);
    REQUIRE(cities[24].country == "United States");
    REQUIRE(cities[24].lat == 41.8373);
    REQUIRE(cities[24].lng == -87.6862);
  }

  SECTION ("PLACE") {
    REQUIRE(cities[2449].name == "Nakhodka");
    REQUIRE(cities[2449].population == 159551);
    REQUIRE(cities[2449].country == "Russia");
    REQUIRE(cities[2449].lat == 42.8374);
    REQUIRE(cities[2449].lng == 132.8874);
  }
}

TEST_CASE("Narrow by population", "[engine][narrow]") {

}

TEST_CASE("Generate Parameters", "[engine][")