//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "BondStatusAux.h"

registerMooseObject("PeridynamicsApp", BondStatusAux);

template <>
InputParameters
validParams<BondStatusAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Class for updating the bond status based on the comparison between "
                             "bond mechanical stretch and bond critical stretch");
  params.addCoupledVar("critical_stretch", "Auxiliary variable for bond critical stretch");
  params.set<ExecFlagEnum>("execute_on") = EXEC_TIMESTEP_END;

  return params;
}

BondStatusAux::BondStatusAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _mechanical_stretch(getMaterialProperty<Real>("mechanical_stretch")),
    _critical_stretch(coupledValue("critical_stretch")),
    _bond_status_var(_subproblem.getVariable(_tid, "bond_status"))
{
}

Real
BondStatusAux::computeValue()
{
  if (std::abs(_bond_status_var.getElementalValue(_current_elem) - 1.0) < 0.01 &&
      _mechanical_stretch[0] < _critical_stretch[0])
    return 1.0; // unbroken and less than critical stretch, bond is still unbroken
  else
    return 0.0; // exceeds critical stretch, bond is taken as broken
}
