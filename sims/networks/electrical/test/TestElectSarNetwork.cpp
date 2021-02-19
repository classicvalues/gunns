/**
@file  TestElectSarNetwork.cpp
@brief TestElectSarNetwork GUNNS Basic Network implementation.

@copyright  Copyright 2019 United States Government as represented by the Administrator of the
            National Aeronautics and Space Administration. All Rights Reserved.

LIBRARY DEPENDENCY:
(
  (core/GunnsSensorAnalogWrapper.o)
  (aspects/electrical/Batt/GunnsElectBattery.o)
  (aspects/electrical/ConstantPowerLoad/EpsConstantPowerLoad.o)
  (aspects/electrical/SolarArray/SolarArray.o)
  (aspects/electrical/sar/GunnsSolarArrayRegulator.o)
  (core/GunnsBasicCapacitor.o)
  (core/GunnsBasicConductor.o)
  (core/GunnsBasicPotential.o)
  (core/network/GunnsNetworkBase.o)
)

PROGRAMMERS:
  ((Auto-generated by the GunnsDraw netexport script version beta 13) (2019-12-11 07:14:41.458047))
*/

#include "TestElectSarNetwork.hh"
#include "simulation/hs/TsHsMsg.hh"
#include "software/exceptions/TsInitializationException.hh"

// Tables data
const double TestElectSarNetwork::BattSocVocTableSOC[3] = {0.0,  0.5,  1.0};
const double TestElectSarNetwork::BattSocVocTableVOC[3] = {0.0,  12.5,  15.0};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] name    (--) Name of the network for H&S messages.
/// @param[in] network (--) Pointer to the main network object.
/// 
/// @details  Default constructs the TestElectSarNetwork Network Config Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
TestElectSarNetworkConfigData::TestElectSarNetworkConfigData(const std::string& name, TestElectSarNetwork* network)
    :
    netSolver(name + ".netSolver", 0.001, 0.001, 10, 10),
    // Spotter Config Data
    sarSensorVout(name + ".sarSensorVout", 0.0, 200.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0, UnitConversion::NO_CONVERSION, 0.0),
    sarSensorIout(name + ".sarSensorIout", 0.0, 200.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0, UnitConversion::NO_CONVERSION, 0.0),
    // Link Config Data
    cpl(name + ".cpl", &network->netNodeList, 0.0, 100.0, 0.0),
    conductor(name + ".conductor", &network->netNodeList, 0.01),
    potential(name + ".potential", &network->netNodeList, 0.0),
    capacitor(name + ".capacitor", &network->netNodeList),
    sa(name + ".sa", &network->netNodeList, 8, 10, 400, 0.07, 0.05, 8, .6152, .4996, -0.00191, 2.6355, 2.445, 0.001424, 1e-10, 300.0, 0.0, 0.017, 200.0, 0.0, 0.30, 0.0, 0.0),
    sar(name + ".sar", &network->netNodeList, &network->battery, &sarSensorVout.mSensor, &sarSensorIout.mSensor, 100.0, 1.0e-6, 1, 10.0, 2.0, 100.0, 140.0),
    battery(name + ".battery", &network->netNodeList, 8, false, 0.1, 0.2, 32.0, &network->BattSocVocTable)
{
    // Load config data vectors
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs the TestElectSarNetwork Network Config Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
TestElectSarNetworkConfigData::~TestElectSarNetworkConfigData()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] network (--) Pointer to the main network object.
///
/// @details  Default constructs the TestElectSarNetwork Network Input Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
TestElectSarNetworkInputData::TestElectSarNetworkInputData(TestElectSarNetwork* network)
    :
    // Spotter Input Data
    sarSensorVout(true, 0.0),
    sarSensorIout(false, 0.0),
    // Link Input Data
    cpl(false, 0.0),
    conductor(false, 0.0),
    potential( false,  0.0, 161.0),
    capacitor(false, 0.0, 1.0, 0.0),
    sa(false, 0.0, false, false, 0, false, false, 1.0, true),
    sar(false, 0.0, &sarSensorVout.mSensor, &sarSensorIout.mSensor, false, false, false, 124.5, 120.0, 0.9, 100.0, 150.0, false, false, 300.0, 1.0, false, false, 0.5, 0.01),
    battery(false, 0.0, 0.9)
{
    // Load input data vectors
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs the TestElectSarNetwork Network Input Data.
////////////////////////////////////////////////////////////////////////////////////////////////////
TestElectSarNetworkInputData::~TestElectSarNetworkInputData()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] name (--) Name of the network for H&S messages.
///
/// @details  Default constructs the TestElectSarNetwork Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
TestElectSarNetwork::TestElectSarNetwork(const std::string& name)
    :
    GunnsNetworkBase(name, N_NODES, netNodes),
    netNodes(),
    netConfig(name, this),
    netInput(this),
    // Data Tables 
    BattSocVocTable(BattSocVocTableSOC, BattSocVocTableVOC, 3, 0.0,  1.0),
    // Spotters
    sarSensorVout(),
    sarSensorIout(),
    // Links
    cpl(),
    conductor(),
    potential(),
    capacitor(),
    sa(),
    sar(),
    battery()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details Default destructs the TestElectSarNetwork Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
TestElectSarNetwork::~TestElectSarNetwork()
{
    // Nothing to do
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] name (--) Name of the network for H&S messages.
///
/// @details  Initializes the nodes with their config and input data objects.  The nodes are
///           initialized through the node list object, which may point to this network's nodes
///           (when this is a standalone network), or the super-network's nodes (as a sub-network).
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestElectSarNetwork::initNodes(const std::string& name)
{
    /// - Initialize the nodes.
    netNodeList.mNodes[0 + netSuperNodesOffset].initialize(name + createNodeName(0 + netSuperNodesOffset), 120);
    netNodeList.mNodes[1 + netSuperNodesOffset].initialize(name + createNodeName(1 + netSuperNodesOffset), 120);
    /// - Only init the Ground node if this is not a sub-network.
    if (!netIsSubNetwork) {
        netNodeList.mNodes[2].initialize(name + ".GROUND");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Initializes this network's links, spotters and solver with their config and input data
///           objects.
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestElectSarNetwork::initNetwork()
{
    const int groundOffset = netNodeList.mNumNodes - N_NODES;

    /// - Register sockets with the jumper plugs.

    /// - Initialize the links.
    netLinks.clear();
    cpl.initialize(netConfig.cpl, netInput.cpl, netLinks, Node1 + netSuperNodesOffset, GROUND + groundOffset);
    conductor.initialize(netConfig.conductor, netInput.conductor, netLinks, Node1 + netSuperNodesOffset, GROUND + groundOffset);
    potential.initialize(netConfig.potential, netInput.potential, netLinks, GROUND + groundOffset, GROUND + groundOffset);
    capacitor.initialize(netConfig.capacitor, netInput.capacitor, netLinks, GROUND + groundOffset, GROUND + groundOffset);
    sa.initialize(netConfig.sa, netInput.sa, netLinks, GROUND + groundOffset, Node0 + netSuperNodesOffset);
    sar.initialize(netConfig.sar, netInput.sar, netLinks, Node0 + netSuperNodesOffset, GROUND + groundOffset, Node1 + netSuperNodesOffset, GROUND + groundOffset);
    battery.initialize(netConfig.battery, netInput.battery, netLinks, GROUND + groundOffset, Node1 + netSuperNodesOffset);

    /// - Initialize the spotters.
    sarSensorVout.initialize(&netConfig.sarSensorVout, &netInput.sarSensorVout);
    sarSensorIout.initialize(&netConfig.sarSensorIout, &netInput.sarSensorIout);

    /// - Initialize the solver, only if this is not a sub-network.
    if (!netIsSubNetwork) {
        netSolver.initializeNodes(netNodeList);
        netSolver.initialize(netConfig.netSolver, netLinks);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] timeStep (s) Integration time step.
///
/// @details  Updates this network's spotters before solving the network.
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestElectSarNetwork::stepSpottersPre(const double timeStep)
{
    /// - Step network spotters prior to solver step.
    sarSensorVout.stepPreSolver(timeStep);
    sarSensorIout.stepPreSolver(timeStep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in]   timeStep (s) Integration time step.
///
/// @details  Updates this network's spotters after solving the network.
////////////////////////////////////////////////////////////////////////////////////////////////////
void TestElectSarNetwork::stepSpottersPost(const double timeStep)
{
    /// - Step network spotters after solver step.
    sarSensorVout.stepPostSolver(timeStep);
    sarSensorIout.stepPostSolver(timeStep);
}
