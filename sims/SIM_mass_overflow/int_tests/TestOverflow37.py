# @copyright Copyright 2019 United States Government as represented by the Administrator of the
#            National Aeronautics and Space Administration.  All Rights Reserved. */
#
import socket
import datetime

from trick.unit_test import *

#===============================================================================================
# Integration test includes
#===============================================================================================
execfile("int_tests/FluidTypes.py")
execfile("int_tests/FluidNetworkConstants.py")

#===============================================================================================
# GUNNS SIM_mass_overflow Test 37
#===============================================================================================
class TestOverflow37(Test):
    """ A network test class that derives from the Test base class.
        The typical use is to derive from the Test base class, override setup and possibly
        tearDown. Be sure to call registerEventBasedTest in the setup function to schedule when
        your test functions are called. See example below.

        The Test base class also has utility test functions that you can call to make comparisons.
        There are several examples below. See Test.py for more comparisons.
    """
    total_mass     = 0.0
    #total_enthalpy = 0.0
    total_mass_N2  = 0.0
    total_mass_O2  = 0.0
    total_mass_H2O = 0.0
    total_mass_WATER = 0.0
    total_mass_ICE = 0.0 

    def __init__(self, testName, testStartMessage, testFinishMessage):
       """ Class constructor that overrides its parent class constructor"""
       # Invokes the class constructor of the parent class #
       super(TestOverflow37, self).__init__(testName, testStartMessage, testFinishMessage)

    def setup(self):
       """ Test setup function. Called before activating the test event.
           This is where you setup your test environment prior to running all tests.
           This is also where you want to schedule when your test functions are called.
       """
       # Register all test events and schedule the times they are run at
       self.registerEventBasedTest("Nodes Initial State Check", 0.0125, self.noOp, 0.0125, self.checkNodesInitState)
       self.registerEventBasedTest("Nodes Final State Check",   12.0,   self.noOp, 12.0,   self.checkNodesFinalState)

       # Call the parent class setup to complete the test setup
       super(TestOverflow37, self).setup()

    # This stores total fluid quantities of all nodes for comparison against in the final test.
    # This isn't actually testing any values, rather just storing values for later test.
    def checkNodesInitState(self):
       sub14ICE_mass       = massOverflow.fluid37.sub14.getIceMass()
       self.total_mass_ICE =  sub14ICE_mass

       for node in range(0,self.getNumNodes()):
          mass     = self.nodeMass(node)
          mass_H2O = mass * self.nodeMassFraction(node, "GUNNS_H2O")
          mass_WATER = mass * self.nodeMassFraction(node, "GUNNS_WATER")

          self.total_mass     = self.total_mass     + mass
          self.total_mass_H2O = self.total_mass_H2O + mass_H2O
          self.total_mass_WATER = self.total_mass_WATER + mass_WATER

       for fluid in self.accumFluids():
          self.total_mass       = self.total_mass       + fluid.getMass()
          self.total_mass_WATER = self.total_mass_WATER + fluid.getMass() * fluid.getMassFraction(fluidTypes["GUNNS_WATER"])

    # Tests final total fluid quantities in all nodes against the stored values from the start of
    # the test, for conservation of mass & energy.
    def checkNodesFinalState(self):
       sub14ICE_mass        = massOverflow.fluid37.sub14.getIceMass()
       final_total_mass_ICE = sub14ICE_mass
       final_total_mass     = 0.0
       final_total_mass_H2O = 0.0
       final_total_mass_WATER = 0.0
       final_total_mass_vaporization = 0.0 

       for node in range(0,self.getNumNodes()):
          mass     = self.nodeMass(node)
          mass_H2O  = mass * self.nodeMassFraction(node, "GUNNS_H2O")
          mass_WATER = mass * self.nodeMassFraction(node, "GUNNS_WATER")

          final_total_mass     = final_total_mass     + mass
          final_total_mass_H2O = final_total_mass_H2O + mass_H2O
          final_total_mass_WATER = final_total_mass_WATER + mass_WATER

       for fluid in self.accumFluids():
          final_total_mass       = final_total_mass       + fluid.getMass()
          final_total_mass_WATER = final_total_mass_WATER + fluid.getMass() * fluid.getMassFraction(fluidTypes["GUNNS_WATER"])

          final_total_mass_vaporization = (final_total_mass_WATER - self.total_mass_WATER) + (final_total_mass_H2O  - self.total_mass_H2O)

       print("-------------------------------------------------------------------------------------------------")
       # Comparing relative error (final - start / start) to tolerance
       # vaporization and sublimation is tested for sublimator link to account for H2O and ice creation
       # Enthalpy testing is commented out because the link being tested (Sublimator) does not conserve energy
       self.testNear((final_total_mass     - self.total_mass) + (final_total_mass_ICE - self.total_mass_ICE),     0.0, (1.0E-16 + tolerance * self.total_mass),     " mass error fraction ::")
       self.testNear(final_total_mass_vaporization + (final_total_mass_ICE - self.total_mass_ICE), 0.0, (1.0E-16 + tolerance * self.total_mass_WATER),  " mass Sublimator error fraction ::")

    """ This is where you setup all your getters/setters for the parameters you need for int testing.
    """
    # Getter for number of nodes
    def getNumNodes(self):
        return massOverflow.fluid37.getNumLocalNodes() - 1
    # Getter for node 
    def node(self,node):
        return massOverflow.fluid37.netNodes[node]
    # Getter for node fluid
    def nodeFluid(self,node):
        return self.node(node).getContent()
    # Getter for node mass
    def nodeMass(self,node):
        return self.nodeFluid(node).getMass()
    # Getter for node enthalpy
    def nodeEnthalpy(self,node):
        return self.nodeFluid(node).getSpecificEnthalpy()
    # Getter for node Mass Fraction
    def nodeMassFraction(self,node,fluidType):
        return self.nodeFluid(node).getMassFraction(fluidTypes[fluidType])
    # Get a list of accumulator fluid objects
    def accumFluids(self):
        return [massOverflow.fluid37.accum0.getInternalFluid(),
                massOverflow.fluid37.accum2.getInternalFluid()]

