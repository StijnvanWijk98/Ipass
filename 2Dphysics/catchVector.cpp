#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "particle.hpp"

TEST_CASE("constructor, basic") {
  vector v{1.1, 2.2};
  std::stringstream s;
  s << v;
  REQUIRE(s.str() == "(1.1,2.2)");
}

TEST_CASE("equality, equal") {
  vector v{1.8, 5.2};
  REQUIRE(v == vector{1.8, 5.2});
}

TEST_CASE("equality, unequal") {
  vector v{2.2, 3.0};
  REQUIRE(!(v == vector{1.8, 3.9}));
}

TEST_CASE("add with vector") {
  vector v{4.5, 3.0};
  vector x = v + vector{2.0, 2.5};
  REQUIRE(v == vector{4.5, 3.0});
  REQUIRE(x == vector{6.5, 5.5});
}

TEST_CASE("multiply by vector") {
  vector v{2.5, 3.0};
  vector x = v * vector{2.0, 3.5};
  REQUIRE(v == vector{2.5, 3.0});
  REQUIRE(x == vector{5.0, 10.5});
}

TEST_CASE("multiply by float") {
  vector v{2.5, 3.0};
  vector x = v * 2.5;
  REQUIRE(v == vector{2.5, 3.0});
  REQUIRE(x == vector{6.25, 7.5});
}

TEST_CASE("multiply by integer into vector") {
  vector v{2.5, 3.0};
  vector x = v * 2;
  REQUIRE(v == vector{2.5, 3.0});
  REQUIRE(x == vector{5.0, 6.0});
}

TEST_CASE("multiply float with vector") {
  vector v{2.5, 3.0};
  vector x = 2.5 * v;
  REQUIRE(v == vector{2.5, 3.0});
  REQUIRE(x == vector{6.25, 7.5});
}

TEST_CASE("Magnitude") {
  vector v{3.0, 4.0};
  float x = v.magnitude();
  REQUIRE(v == vector{3.0, 4.0});
  REQUIRE(x == 5.0);
}

TEST_CASE("Magnitude squared") {
  vector v{2.5, 2.5};
  float x = v.squaredMagnitude();
  REQUIRE(v == vector{2.5, 2.5});
  REQUIRE(x == 12.5);
}