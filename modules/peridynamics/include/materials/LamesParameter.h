//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef LAMESPARAMETER_H
#define LAMESPARAMETER_H

#include "PDParametricMaterial.h"

class LamesParameter;

template <>
InputParameters validParams<LamesParameter>();

/**
 * Base material class for bond based peridynamic solid mechanics models
 */
class LamesParameter : public PDParametricMaterial
{
public:
  LamesParameter (const InputParameters & parameters);

virtual void computeBondForce() override;

protected:

  MaterialProperty<Real> & _lambda;
  MaterialProperty<Real> & _mu;
};

#endif // LAMESPARAMETER_H
