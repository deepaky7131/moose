//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef NODALVARIABLEINTEGRAL_H
#define NODALVARIABLEINTEGRAL_H

#include "PDNodalIntegralPostprocessor.h"

class NodalVariableIntegral;

template <>
InputParameters validParams<NodalVariableIntegral>();

/**
 * Postprocessor class to compute nodal variable integral in peridynamic discretization
 */
class NodalVariableIntegral : public PDNodalIntegralPostprocessor
{
public:
  NodalVariableIntegral(const InputParameters & parameters);

protected:
  virtual Real computeNodalValue() override;

  /// Nodal variable to be integrated
  MooseVariableFEBase & _var;
};

#endif // NODALVARIABLEINTEGRAL_H
