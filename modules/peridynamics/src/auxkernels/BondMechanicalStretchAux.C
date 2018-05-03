//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "BondMechanicalStretchAux.h"

registerMooseObject("PeridynamicsApp", BondMechanicalStretchAux);

template <>
InputParameters
validParams<BondMechanicalStretchAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Class for outputing bond mechanical stretch value");
  params.set<ExecFlagEnum>("execute_on") = EXEC_TIMESTEP_END;

  return params;
}

BondMechanicalStretchAux::BondMechanicalStretchAux(const InputParameters & parameters)
  : AuxKernel(parameters), _mechanical_stretch(getMaterialProperty<Real>("mechanical_stretch"))
{
}

Real
BondMechanicalStretchAux::computeValue()
{
  return _mechanical_stretch[0];
}
