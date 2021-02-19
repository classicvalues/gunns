////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup  UT_GUNNS_FLUID_POTENTIAL   Potential Unit tests
/// @ingroup   UT_GUNNS_FLUID
/// @copyright Copyright 2019 United States Government as represented by the Administrator of the
///            National Aeronautics and Space Administration.  All Rights Reserved.
/// @details   Unit test classes for GUNNS fluid potential link models.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cppunit/ui/text/TestRunner.h>

#include "UtGunnsGasFanCurve.hh"
#include "UtGunnsGasFan.hh"
#include "UtGunnsPumpCavitation.hh"
#include "UtGunnsLiquidCentrifugalPump.hh"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param    int     --  not used
/// @param    char**  --  not used
///
/// @return    --  status (always 0)
///
/// @details  Main for GUNNS fluid potential link model unit tests in the CPPUNIT framework.
////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int, char**)
{
    CppUnit::TextTestRunner runner;

    runner.addTest(UtGunnsGasFanCurve::suite());
    runner.addTest(UtGunnsGasFan::suite());
    runner.addTest(UtGunnsPumpCavitation::suite());
    runner.addTest(UtGunnsLiquidCentrifugalPump::suite());

    runner.run();

    return 0;
}
