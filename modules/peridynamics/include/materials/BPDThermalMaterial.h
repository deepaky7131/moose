//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef BPDTHERMALMATERIAL_H
#define BPDTHERMALMATERIAL_H

#include "PDMaterialBase.h"

class BPDThermalMaterial;
class Function;

template <>
InputParameters validParams<BPDThermalMaterial>();

/**
 * Base material class for bond based peridynamic heat conduction models
 */
class BPDThermalMaterial : public PDMaterialBase
{
public:
  BPDThermalMaterial(const InputParameters & parameters);

protected:
  virtual void computeProperties() override;

  /**
   * Function to compute heat flow for a bond
   */
  void computeBondHeatFlow();

  /**
   * Function to fetch the nodal temperature value
   */
  void computeNodalTemperature();

  /**
   * Function to compute micro-conductivity
   */
  virtual void computePDMicroConductivity() = 0;

  ///@{ Temperature variable and values
  MooseVariableFEBase & _temp_var;
  std::vector<Real> _temp;
  ///@}

  /// Constant thermal conductivity
  const Real _thermal_conductivity;

  /// Functional thermal conductivity
  Function * _thermal_conductivity_function;

  ///@{ Material properties to be stored
  MaterialProperty<Real> & _bond_heat_flow;
  MaterialProperty<Real> & _bond_dQdT;
  ///@}

  /// Thermal conductivity
  Real _kappa;

  /// Micro-conductivity
  Real _Kij;
};

#endif // BPDTHERMALMATERIAL_H
