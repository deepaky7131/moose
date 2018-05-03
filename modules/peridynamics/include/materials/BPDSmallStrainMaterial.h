//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef BPDSMALLSTRAINMATERIAL_H
#define BPDSMALLSTRAINMATERIAL_H

#include "PDParametricMaterial.h"

class BPDSmallStrainMaterial;

template <>
InputParameters validParams<BPDSmallStrainMaterial>();

/**
 * Base material class for bond based peridynamic solid mechanics models
 */
class BPDSmallStrainMaterial : public PDParametricMaterial
{
public:
  BPDSmallStrainMaterial(const InputParameters & parameters);

protected:
  virtual void computeBondForce() override;

  /**
   * Function to compute the micro-modulus for bond-based models
   */
  virtual void computePDMicroModuli() = 0;

  /// Micro-modulus
  Real _Cij;
};

#endif // BPDSMALLSTRAINMATERIAL_H
