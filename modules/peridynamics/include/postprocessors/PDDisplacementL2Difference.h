//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PDDISPLACEMENTL2DIFFERENCE_H
#define PDDISPLACEMENTL2DIFFERENCE_H

#include "PDNodalIntegralPostprocessor.h"

class PDDisplacementL2Difference;

template <>
InputParameters validParams<PDDisplacementL2Difference>();

/**
 * Postprocessor class to compute L2 norm of displacements difference between prediction and
 * analytical solution for peridynamic model
 */
class PDDisplacementL2Difference : public PDNodalIntegralPostprocessor
{
public:
  PDDisplacementL2Difference(const InputParameters & parameters);

  virtual Real getValue() override;

protected:
  virtual Real computeNodalValue() override;

  ///@{ Known displacements analytical solutions
  const bool _has_func_0;
  Function * _func_0;

  const bool _has_func_1;
  Function * _func_1;

  const bool _has_func_2;
  Function * _func_2;
  ///@}

  /// Displacement variables
  std::vector<MooseVariableFEBase *> _disp_var;
};

#endif // PDDISPLACEMENTL2DIFFERENCE
