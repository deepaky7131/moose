//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LamesParameter.h"

registerMooseObject("PeridynamicsApp", LamesParameter);
template <>
InputParameters
validParams<LamesParameter>()
{
  InputParameters params = validParams<PDParametricMaterial>();
  params.addClassDescription("Base class for PD Differential operator peridynamic mechanics models");

  return params;
}

LamesParameter::LamesParameter(const InputParameters & parameters)
  : PDParametricMaterial(parameters),
  _lambda(declareProperty<Real>("lambda")),
  _mu(declareProperty<Real>("mu"))
{
}

void
LamesParameter::computeBondForce()
{
  _lambda[0] = _lambda[1] = (_youngs_modulus*_poissons_ratio)/((1.0-_poissons_ratio)*(1.0-2.0*_poissons_ratio));
  _mu[0] = _mu[1] = _youngs_modulus/(3*(1+_poissons_ratio));
}
