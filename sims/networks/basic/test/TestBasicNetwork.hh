#ifndef TestBasicNetwork_EXISTS
#define TestBasicNetwork_EXISTS

/**
@file  TestBasicNetwork.hh
@brief TestBasicNetwork GUNNS Basic Network declarations.

@copyright  Copyright 2019 United States Government as represented by the Administrator of the
            National Aeronautics and Space Administration. All Rights Reserved.

@defgroup  GUNNS_TESTBASICNETWORK TestBasicNetwork GUNNS Basic Network
@ingroup  GUNNS

@details
PURPOSE: (Provides classes for the TestBasicNetwork GUNNS Basic Network.)

REFERENCES:
  ()

ASSUMPTIONS AND LIMITATIONS:
  ()

LIBRARY DEPENDENCY:
  ((TestBasicNetwork.o))

PROGRAMMERS:
  ((Auto-generated by the GunnsDraw netexport script version beta 13) (2019-12-11 07:14:41.013707))

@{
*/

#include "software/SimCompatibility/TsSimCompatibility.hh"
#include "core/network/GunnsNetworkBase.hh"
#include "core/GunnsBasicConductor.hh"
#include "core/GunnsBasicPotential.hh"

// Forward-declare the main network class for use in the config data.
class TestBasicNetwork;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    TestBasicNetwork GUNNS Network Config Data
///
/// @details  Configuration data class for the TestBasicNetwork Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestBasicNetworkConfigData
{
    public:
        // Solver configuration data
        GunnsConfigData netSolver;    /**< (--) trick_chkpnt_io(**) Network solver config data. */ 
        // Spotters configuration data
        // Links configuration data
        GunnsBasicPotentialConfigData SimpleVoltageSource;    /**< (--) trick_chkpnt_io(**) SimpleVoltageSource config data. */
        GunnsBasicConductorConfigData Resistor1;    /**< (--) trick_chkpnt_io(**) Resistor1 config data. */
        GunnsBasicConductorConfigData Resistor2;    /**< (--) trick_chkpnt_io(**) Resistor2 config data. */
        /// @brief  Default constructs this network configuration data.
        TestBasicNetworkConfigData(const std::string& name, TestBasicNetwork* network);
        /// @brief  Default destructs this network configuration data.
        virtual ~TestBasicNetworkConfigData();

    private:
        /// @details  Copy constructor unavailable since declared private and not implemented.
        TestBasicNetworkConfigData(const TestBasicNetworkConfigData&);
        /// @details  Assignment operator unavailable since declared private and not implemented.
        TestBasicNetworkConfigData& operator =(const TestBasicNetworkConfigData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    TestBasicNetwork GUNNS Network Input Data
///
/// @details  Input data class for the TestBasicNetwork Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestBasicNetworkInputData
{
    public:
        // Spotters input data
        // Links input data
        GunnsBasicPotentialInputData SimpleVoltageSource;    /**< (--) trick_chkpnt_io(**) SimpleVoltageSource input data. */
        GunnsBasicConductorInputData Resistor1;    /**< (--) trick_chkpnt_io(**) Resistor1 input data. */
        GunnsBasicConductorInputData Resistor2;    /**< (--) trick_chkpnt_io(**) Resistor2 input data. */
        /// @brief  Default constructs this network input data.
        TestBasicNetworkInputData(TestBasicNetwork* network);
        /// @brief  Default destructs this network input data.
        virtual ~TestBasicNetworkInputData();

    private:
        /// @details  Copy constructor unavailable since declared private and not implemented.
        TestBasicNetworkInputData(const TestBasicNetworkInputData&);
        /// @details  Assignment operator unavailable since declared private and not implemented.
        TestBasicNetworkInputData& operator =(const TestBasicNetworkInputData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    TestBasicNetwork GUNNS Network
///
/// @details  Main class for the TestBasicNetwork Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
class TestBasicNetwork : public GunnsNetworkBase
{
    TS_MAKE_SIM_COMPATIBLE(TestBasicNetwork);
    public:
        /// @brief  Enumeration of the TestBasicNetwork Network nodes.
        enum Nodes
        {
            Node0 = 0,    ///< Node 0
            Node1 = 1,    ///< Node 1
            GROUND = 2,    ///< Ground Node
            N_NODES = 3    ///< Number of nodes including Ground
        };
        // Network declarations
        GunnsBasicNode netNodes[TestBasicNetwork::N_NODES];    /**< (--) Network nodes array. */
        TestBasicNetworkConfigData netConfig;    /**< (--) trick_chkpnt_io(**) Network config data. */
        TestBasicNetworkInputData netInput;    /**< (--) trick_chkpnt_io(**) Network input data. */
        // Data Tables
        // Spotters
        // Links
        GunnsBasicPotential SimpleVoltageSource;    /**< (--) SimpleVoltageSource instance. */
        GunnsBasicConductor Resistor1;    /**< (--) Resistor1 instance. */
        GunnsBasicConductor Resistor2;    /**< (--) Resistor2 instance. */
        /// @brief  Default constructs this network.
        TestBasicNetwork(const std::string& name = "");
        /// @brief  Default destructs this network.
        virtual ~TestBasicNetwork();
        /// @brief  Network nodes initialization task.
        virtual void initNodes(const std::string& name);
        /// @brief  Network links & spotters initialization task.
        virtual void initNetwork();
        /// @brief  Update network spotters before the solver solution.
        virtual void stepSpottersPre(const double timeStep);
        /// @brief  Update network spotters after the solver solution.
        virtual void stepSpottersPost(const double timeStep);

    private:
        /// @details  Copy constructor unavailable since declared private and not implemented.
        TestBasicNetwork(const TestBasicNetwork&);
        /// @details  Assignment operator unavailable since declared private and not implemented.
        TestBasicNetwork& operator =(const TestBasicNetwork&);
};

/// @}  

#endif
