/************************** TRICK HEADER ***********************************************************
@copyright Copyright 2019 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.

 LIBRARY DEPENDENCY:
    (
        (aspects/electrical/Batt/GunnsElectBatteryCell.o)
        (software/exceptions/TsInitializationException.o)
        (math/approximation/TsLinearInterpolator.o)
    )
***************************************************************************************************/
#include "software/exceptions/TsInitializationException.hh"
#include "math/approximation/TsLinearInterpolator.hh"
#include "UtGunnsElectBatteryCell.hh"
#include "strings/UtResult.hh"

/// @details  Test identification number.
int UtGunnsElectBatteryCell::TEST_ID = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  This is the default constructor for the UtGunnsElectBatteryCell class.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtGunnsElectBatteryCell::UtGunnsElectBatteryCell()
    :
    CppUnit::TestFixture(),
    tConfigData(),
    tInputData(),
    tArticle(),
    tResistance(0.0),
    tMaxCapacity(0.0),
    tMalfOpenCircuit(false),
    tMalfShortCircuit(false),
    tSoc(0.0),
    tName(),
    tSocVocTable(0)
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  This is the default destructor for the UtGunnsElectBatteryCell class.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtGunnsElectBatteryCell::~UtGunnsElectBatteryCell()
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Executed before each unit test.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::setUp()
{
    /// - Create nominal configuration data.
    tResistance       = 0.1;
    tMaxCapacity      = 32.0;
    tConfigData       = new GunnsElectBatteryCellConfigData(tResistance, tMaxCapacity);

    /// - Create nominal input data.
    tMalfOpenCircuit  = false;
    tMalfShortCircuit = false;
    tSoc              = 0.9;
    tInputData        = new GunnsElectBatteryCellInputData(tMalfOpenCircuit, tMalfShortCircuit, tSoc);

    /// - Create the SOC/VOC table and set it up so it will interpolate to the same Voc output as
    ///   SOC in (0 - 1).
    const double socPoints[] = {0.0, 1.0};
    const double vocPoints[] = {0.0, 1.0};
    tSocVocTable      = new TsLinearInterpolator(socPoints, vocPoints, 2, 0.0, 1.0);

    /// - Create the test article.
    tName             = "tArticle";
    tArticle          = new FriendlyGunnsElectBatteryCell;

    /// - Increment the test identification number.
    ++TEST_ID;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Executed after each unit test.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::tearDown()
{
    /// - Deletes for news in setUp
    delete tArticle;
    delete tSocVocTable;
    delete tInputData;
    delete tConfigData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Tests for construction of config data.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testConfig()
{
    UT_RESULT_INITIAL("GUNNS Electrical Battery Classes");

    /// @test nominal config construction.
    CPPUNIT_ASSERT(tResistance  == tConfigData->mResistance);
    CPPUNIT_ASSERT(tMaxCapacity == tConfigData->mMaxCapacity);

    /// @test default config construction.
    GunnsElectBatteryCellConfigData defaultConfig;
    CPPUNIT_ASSERT(0.0 == defaultConfig.mResistance);
    CPPUNIT_ASSERT(0.0 == defaultConfig.mMaxCapacity);

    /// @test copy config construction.
    GunnsElectBatteryCellConfigData copyConfig(*tConfigData);
    CPPUNIT_ASSERT(tResistance  == copyConfig.mResistance);
    CPPUNIT_ASSERT(tMaxCapacity == copyConfig.mMaxCapacity);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Tests the input data class.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testInput()
{
    UT_RESULT;

    /// @test nominal input construction.
    GunnsElectBatteryCellInputData nominalInput(true, true, 1.0);
    CPPUNIT_ASSERT(true  == nominalInput.mMalfOpenCircuit);
    CPPUNIT_ASSERT(true  == nominalInput.mMalfShortCircuit);
    CPPUNIT_ASSERT(1.0   == nominalInput.mSoc);

    /// @test default input construction.
    GunnsElectBatteryCellInputData defaultInput;
    CPPUNIT_ASSERT(false == defaultInput.mMalfOpenCircuit);
    CPPUNIT_ASSERT(false == defaultInput.mMalfShortCircuit);
    CPPUNIT_ASSERT(0.0   == defaultInput.mSoc);

    /// @test copy input construction.
    GunnsElectBatteryCellInputData copyInput(nominalInput);
    CPPUNIT_ASSERT(true  == copyInput.mMalfOpenCircuit);
    CPPUNIT_ASSERT(true  == copyInput.mMalfShortCircuit);
    CPPUNIT_ASSERT(1.0   == copyInput.mSoc);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test for default construction without exceptions.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testDefaultConstruction()
{
    UT_RESULT;

    /// @test state data.
    CPPUNIT_ASSERT(false == tArticle->mMalfOpenCircuit);
    CPPUNIT_ASSERT(false == tArticle->mMalfShortCircuit);
    CPPUNIT_ASSERT(0.0   == tArticle->mResistance);
    CPPUNIT_ASSERT(0.0   == tArticle->mMaxCapacity);
    CPPUNIT_ASSERT(0.0   == tArticle->mSoc);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test for nominal initialization without exceptions.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testNominalInitialization()
{
    UT_RESULT;

    tMalfOpenCircuit              = true;
    tMalfShortCircuit             = true;
    tInputData->mMalfOpenCircuit  = tMalfOpenCircuit;
    tInputData->mMalfShortCircuit = tMalfShortCircuit;

    /// @test initialize with initialization data and no exceptions.
    CPPUNIT_ASSERT_NO_THROW(tArticle->initialize(*tConfigData, *tInputData, tName));
    CPPUNIT_ASSERT(tResistance       == tArticle->mResistance);
    CPPUNIT_ASSERT(tMaxCapacity      == tArticle->mMaxCapacity);
    CPPUNIT_ASSERT(tResistance       == tArticle->mResistance);
    CPPUNIT_ASSERT(tMalfOpenCircuit  == tArticle->mMalfOpenCircuit);
    CPPUNIT_ASSERT(tMalfShortCircuit == tArticle->mMalfShortCircuit);
    CPPUNIT_ASSERT(tSoc              == tArticle->mSoc);
    CPPUNIT_ASSERT(tName             == tArticle->mName);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test for initialization exceptions on invalid properties.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testInitializationExceptions()
{
    UT_RESULT;

    /// @test for exception on missing name.
    CPPUNIT_ASSERT_THROW(tArticle->initialize(*tConfigData, *tInputData, ""), TsInitializationException);

    /// @test for exception on invalid config data: resistance.
    tConfigData->mResistance = -DBL_EPSILON;
    CPPUNIT_ASSERT_THROW(tArticle->initialize(*tConfigData, *tInputData, tName), TsInitializationException);
    tConfigData->mResistance = tResistance;

    /// @test for exception on invalid config data: maximum capacity.
    tConfigData->mMaxCapacity = 0.0;
    CPPUNIT_ASSERT_THROW(tArticle->initialize(*tConfigData, *tInputData, tName), TsInitializationException);
    tConfigData->mMaxCapacity = tMaxCapacity;

    /// @test for exception on invalid config data: state of charge.
    tInputData->mSoc = -DBL_EPSILON;
    CPPUNIT_ASSERT_THROW(tArticle->initialize(*tConfigData, *tInputData, tName), TsInitializationException);
    tInputData->mSoc = 1.0 + DBL_EPSILON;
    CPPUNIT_ASSERT_THROW(tArticle->initialize(*tConfigData, *tInputData, tName), TsInitializationException);
    tInputData->mSoc = tSoc;

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test nominal updates with no malfunctions.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testUpdate()
{
    UT_RESULT;

    /// - Initialize default test article with nominal initialization data.
    tArticle->initialize(*tConfigData, *tInputData, tName);

    /// @test SOC drops with forward current.
    const double dt          =   0.1;
    double       current     = 100.0;
    double       expectedSoc = tSoc - current * dt / tMaxCapacity / 3600.0;
    double       expectedR   = tResistance;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedSoc, tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedSoc, tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedSoc, tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test SOC rises with reverse current.
    current = -100.0;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(tSoc,        tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(tSoc,        tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(tSoc,        tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test SOC limited to 1.0.
    current = -1.0e15;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,         tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,         tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,         tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test SOC limited to 0.0.
    current = 1.0e15;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test protects against divide-by-zero in max capacity.
    tArticle->mMaxCapacity = 0.0;
    tArticle->mSoc         = 1.0;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test updates with the open-circuit malfunction.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testUpdateMalfOpen()
{
    UT_RESULT;

    /// - Initialize default test article with nominal initialization data.
    tArticle->initialize(*tConfigData, *tInputData, tName);

    /// @test setting the open-circuit malfunction.
    tArticle->setMalfOpenCircuit(true);
    CPPUNIT_ASSERT(true == tArticle->mMalfOpenCircuit);

    /// @test SOC remains constant with forward current.
    const double dt          =   0.1;
    double       current     = 100.0;
    double       expectedSoc = tSoc;
    double       expectedR   = 1.0 / DBL_EPSILON;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedSoc, tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test SOC remains constant with reverse current.
    current = -100.0;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedSoc, tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR,   tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,         tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test resetting the open-circuit malfunction.
    tArticle->setMalfOpenCircuit();
    CPPUNIT_ASSERT(false == tArticle->mMalfOpenCircuit);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test updates with the short-circuit malfunction.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testUpdateMalfShort()
{
    UT_RESULT;

    /// - Initialize default test article with nominal initialization data.
    tArticle->initialize(*tConfigData, *tInputData, tName);

    /// @test setting the short-circuit malfunction.
    tArticle->setMalfShortCircuit(true);
    CPPUNIT_ASSERT(true == tArticle->mMalfShortCircuit);

    /// @test SOC goes to zero.
    const double dt          =   0.1;
    double       current     = 100.0;
    double       expectedR   = DBL_EPSILON;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,       tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,       tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR, tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,       tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    /// @test resetting the short-circuit malfunction.
    tArticle->setMalfShortCircuit();
    CPPUNIT_ASSERT(false == tArticle->mMalfShortCircuit);

    UT_PASS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Test updates with the both the open-circuit and short-circuit malfunctions.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtGunnsElectBatteryCell::testUpdateMalfBoth()
{
    UT_RESULT;

    /// - Initialize default test article with nominal initialization data.
    tArticle->initialize(*tConfigData, *tInputData, tName);

    /// - Set the open-circuit and short-circuit malfunctions.
    tArticle->setMalfOpenCircuit(true);
    tArticle->setMalfShortCircuit(true);

    /// @test SOC goes to zero.
    const double dt          =   0.1;
    double       current     = 100.0;
    double       expectedR   = DBL_EPSILON;
    tArticle->updateSoc(current, dt);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,       tArticle->mSoc,                              DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,       tArticle->getEffectiveSoc(),                 DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expectedR, tArticle->getEffectiveResistance(),          DBL_EPSILON);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0,       tArticle->getEffectiveVoltage(tSocVocTable), DBL_EPSILON);

    UT_PASS_LAST;
}
