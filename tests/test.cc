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

TEST_CASE("Engine constructor", "[engine][constructor]") {
  homefinder::Engine engine()
}