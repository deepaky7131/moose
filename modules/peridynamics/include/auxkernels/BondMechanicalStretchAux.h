//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef BONDMECHANICALSTRETCHAUX_H
#define BONDMECHANICALSTRETCHAUX_H

#include "AuxKernel.h"

class BondMechanicalStretchAux;

template <>
InputParameters validParams<BondMechanicalStretchAux>();

/**
 * Aux Kernel class to output the bond elastic stretch value
 */
class BondMechanicalStretchAux : public AuxKernel
{
public:
  BondMechanicalStretchAux(const InputParameters & parameters);

protected:
  Real computeValue() override;

  /// Material property of bond mechanical stretch
  const MaterialProperty<Real> & _mechanical_stretch;
};

#endif // BONDMECHANICALSTRETCHAUX_H
