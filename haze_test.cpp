// Use Catch microframework.
// https://www.github.com/philsquared/Catch/

#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "hazecalc.h"

/*
 * Test cases.
 */ 
TEST_CASE( "HazeCalc", "[hazecalc]" ) {
	HazeCalc hc;
	REQUIRE(hc.getAndReset() == 0);
	
	SECTION( "Basic math" ) {
		hc.take("PM10_24HR", 50.);
		REQUIRE(hc.getAndReset() == 50.);

		hc.take("PM10_24HR", 51);
		REQUIRE(hc.getAndReset() == 50.5);

		hc.take("PM10_24HR", 150);
		REQUIRE(hc.getAndReset() == 100);

		hc.take("PM10_24HR", 100);
		REQUIRE(hc.getAndReset() == 75);
	}

	SECTION( "Special handling of NO2_1HR_MAX" ) {
		hc.take("NO2_1HR_MAX", 1129);
		REQUIRE(hc.getAndReset() == 0);

		hc.take("NO2_1HR_MAX", 1130);
		REQUIRE(hc.getAndReset() == 0);

		hc.take("NO2_1HR_MAX", 1131);
		REQUIRE(abs(hc.getAndReset() - (100.0/(2260.0-1130.0) + 200)) < .1);

		hc.take("NO2_1HR_MAX", 3749);
		REQUIRE(abs(hc.getAndReset() - (749/(3750-3000.0)*100.0 + 400)) < .1);

		hc.take("NO2_1HR_MAX", 3750);
		REQUIRE(hc.getAndReset() == 500);

		hc.take("NO2_1HR_MAX", 3751);
		REQUIRE(hc.getAndReset() == 500);
	}
}
