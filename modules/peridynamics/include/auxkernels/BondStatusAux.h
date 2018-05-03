//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef BONDSTATUSAUX_H
#define BONDSTATUSAUX_H

#include "AuxKernel.h"

class BondStatusAux;

template <>
InputParameters validParams<BondStatusAux>();

/**
 * Aux Kernel class to update the bond status during fracture modeling
 * A bond is broken and the bond_status variable has value of 0, if its elastic stretch exceeds the
 * critical value. If a bond is intact during previous time step and its elastic stretch is less
 * than the critical value, the bond is taken as intact and the bond_status variable has value of 1.
 */
class BondStatusAux : public AuxKernel
{
public:
  BondStatusAux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  /// Material property of bond mechanical stretch
  const MaterialProperty<Real> & _mechanical_stretch;

  /// Aux variable of bond critical stretch
  const VariableValue & _critical_stretch;

  /// Bond_status variable
  const MooseVariableFEBase & _bond_status_var;
};

#endif // BONDSTATUSAUX_H
