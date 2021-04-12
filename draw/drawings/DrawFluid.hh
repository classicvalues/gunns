#ifndef DrawFluid_EXISTS
#define DrawFluid_EXISTS

/**
@file  DrawFluid.hh
@brief DrawFluid GUNNS Fluid Network declarations.

@copyright  Copyright 2019 United States Government as represented by the Administrator of the
            National Aeronautics and Space Administration. All Rights Reserved.

@defgroup  GUNNS_DRAWFLUID DrawFluid GUNNS Fluid Network
@ingroup  GUNNS

@details
PURPOSE: (Provides classes for the DrawFluid GUNNS Fluid Network.)

REFERENCES:
  ()

ASSUMPTIONS AND LIMITATIONS:
  ()

LIBRARY DEPENDENCY:
  ((DrawFluid.o))

PROGRAMMERS:
  ((Auto-generated by the GunnsDraw netexport script version 19.2.0) (2021-04-12 05:55:38.268361))

@{
*/

#include "software/SimCompatibility/TsSimCompatibility.hh"
#include "core/network/GunnsNetworkBase.hh"
#include "core/GunnsFluidVolumeMonitor.hh"
#include "core/GunnsFluidCapacitor.hh"
#include "core/GunnsFluidConductor.hh"
#include "core/GunnsFluidPotential.hh"

// Forward-declare the main network class for use in the config data.
class DrawFluid;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Data structure for DrawFluid GUNNS network mass fractions.
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct DrawFluidFractions {
    double GUNNS_N2;
    double GUNNS_O2;
    double GUNNS_WATER;
} DrawFluidFractions;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Union for DrawFluid GUNNS network mass fractions as scalars and as an array.
///         The array is used as an argument in the PolyFluidInputData constructor. 
////////////////////////////////////////////////////////////////////////////////////////////////////
union DrawFluidMassFractions {
    DrawFluidFractions scalar;
    double array[sizeof(DrawFluidFractions)/sizeof(double)];
    DrawFluidMassFractions(
        const double iGUNNS_N2,
        const double iGUNNS_O2,
        const double iGUNNS_WATER);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    DrawFluid GUNNS Network Config Data
///
/// @details  Configuration data class for the DrawFluid Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
class DrawFluidConfigData
{
    public:
        /// @brief  Enumeration of the number of internal constituent fluids in this network.
        enum {N_INTERNAL_FLUIDS = 3};
        // Network fluid configurations
        static FluidProperties::FluidType netInternalFluidTypes[DrawFluidConfigData::N_INTERNAL_FLUIDS];    /**< (--) trick_chkpnt_io(**) Network internal fluid types array. */
        // Solver configuration data
        GunnsConfigData netSolver;    /**< (--) trick_chkpnt_io(**) Network solver config data. */ 
        // Spotters configuration data
        GunnsFluidVolumeMonitorConfigData tankVolumeMonitor;    /**< (--) trick_chkpnt_io(**) tankVolumeMonitor config data. */
        // Links configuration data
        GunnsFluidConductorConfigData pipe;    /**< (--) trick_chkpnt_io(**) pipe config data. */
        GunnsFluidCapacitorConfigData tank;    /**< (--) trick_chkpnt_io(**) tank config data. */
        GunnsFluidPotentialConfigData ambient;    /**< (--) trick_chkpnt_io(**) ambient config data. */
        /// @brief  Default constructs this network configuration data.
        DrawFluidConfigData(const std::string& name, DrawFluid* network);
        /// @brief  Default destructs this network configuration data.
        virtual ~DrawFluidConfigData();

    private:
        /// @details  Copy constructor unavailable since declared private and not implemented.
        DrawFluidConfigData(const DrawFluidConfigData&);
        /// @details  Assignment operator unavailable since declared private and not implemented.
        DrawFluidConfigData& operator =(const DrawFluidConfigData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    DrawFluid GUNNS Network Input Data
///
/// @details  Input data class for the DrawFluid Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
class DrawFluidInputData
{
    public:
        // Internal network fluids
        DrawFluidMassFractions fluidWaterFractions;    /**< (--) trick_chkpnt_io(**) Fluid mass fractions. */
        PolyFluidInputData fluidWater;    /**< (--) trick_chkpnt_io(**) Fluid input data. */
        DrawFluidMassFractions fluidAirFractions;    /**< (--) trick_chkpnt_io(**) Fluid mass fractions. */
        PolyFluidInputData fluidAir;    /**< (--) trick_chkpnt_io(**) Fluid input data. */
        // Spotters input data
        GunnsFluidVolumeMonitorInputData tankVolumeMonitor;    /**< (--) trick_chkpnt_io(**) tankVolumeMonitor input data. */
        // Links input data
        GunnsFluidConductorInputData pipe;    /**< (--) trick_chkpnt_io(**) pipe input data. */
        GunnsFluidCapacitorInputData tank;    /**< (--) trick_chkpnt_io(**) tank input data. */
        GunnsFluidPotentialInputData ambient;    /**< (--) trick_chkpnt_io(**) ambient input data. */
        /// @brief  Default constructs this network input data.
        DrawFluidInputData(DrawFluid* network);
        /// @brief  Default destructs this network input data.
        virtual ~DrawFluidInputData();

    private:
        /// @details  Copy constructor unavailable since declared private and not implemented.
        DrawFluidInputData(const DrawFluidInputData&);
        /// @details  Assignment operator unavailable since declared private and not implemented.
        DrawFluidInputData& operator =(const DrawFluidInputData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    DrawFluid GUNNS Network
///
/// @details  Main class for the DrawFluid Network.
////////////////////////////////////////////////////////////////////////////////////////////////////
class DrawFluid : public GunnsNetworkBase
{
    TS_MAKE_SIM_COMPATIBLE(DrawFluid);
    public:
        /// @brief  Enumeration of the DrawFluid Network nodes.
        enum Nodes
        {
            Node0 = 0,    ///< Node 0
            Node1 = 1,    ///< Node 1
            GROUND = 2,    ///< Ground Node
            N_NODES = 3    ///< Number of nodes including Ground
        };
        // Network declarations
        GunnsFluidNode netNodes[DrawFluid::N_NODES];    /**< (--) Network nodes array. */
        DrawFluidConfigData netConfig;    /**< (--) trick_chkpnt_io(**) Network config data. */
        DrawFluidInputData netInput;    /**< (--) trick_chkpnt_io(**) Network input data. */
        const DefinedFluidProperties netFluidProperties;        /**< (--) trick_chkpnt_io(**) Network defined fluid properties. */
        PolyFluidConfigData          netInternalFluidConfig;    /**< (--) trick_chkpnt_io(**) Network internal fluid config. */
        // Data Tables
        // Spotters
        GunnsFluidVolumeMonitor tankVolumeMonitor;    /**< (--) tankVolumeMonitor instance. */
        // Links
        GunnsFluidConductor pipe;    /**< (--) pipe instance. */
        GunnsFluidCapacitor tank;    /**< (--) tank instance. */
        GunnsFluidPotential ambient;    /**< (--) ambient instance. */
        /// @brief  Default constructs this network.
        DrawFluid(const std::string& name = "");
        /// @brief  Default destructs this network.
        virtual ~DrawFluid();
        /// @brief  Network nodes initialization task.
        virtual void initNodes(const std::string& name);
        /// @brief  Network links & spotters initialization task.
        virtual void initNetwork();
        /// @brief  Update network spotters before the solver solution.
        virtual void stepSpottersPre(const double timeStep);
        /// @brief  Update network spotters after the solver solution.
        virtual void stepSpottersPost(const double timeStep);
        /// @brief  Returns this network's fluid configuration.
        virtual const PolyFluidConfigData* getFluidConfig() const;

    private:
        /// @details  Copy constructor unavailable since declared private and not implemented.
        DrawFluid(const DrawFluid&);
        /// @details  Assignment operator unavailable since declared private and not implemented.
        DrawFluid& operator =(const DrawFluid&);
};

/// @}  

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns  PolyFluidConfigData* (--) Pointer to this network's fluid configuration.
///
/// @details  Returns this network's fluid configuration.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline const PolyFluidConfigData* DrawFluid::getFluidConfig() const
{
    return &netInternalFluidConfig;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] iGUNNS_N2 (--) Mass fraction of the GUNNS_N2 constituent in the composite fluid.
/// @param[in] iGUNNS_O2 (--) Mass fraction of the GUNNS_O2 constituent in the composite fluid.
/// @param[in] iGUNNS_WATER (--) Mass fraction of the GUNNS_WATER constituent in the composite fluid.
///
/// @details  Constructs the mass fraction union from the scalar mass fraction arguments.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline DrawFluidMassFractions::DrawFluidMassFractions (
    const double iGUNNS_N2,
    const double iGUNNS_O2,
    const double iGUNNS_WATER)
{
    scalar.GUNNS_N2 = iGUNNS_N2;
    scalar.GUNNS_O2 = iGUNNS_O2;
    scalar.GUNNS_WATER = iGUNNS_WATER;
}

#endif
