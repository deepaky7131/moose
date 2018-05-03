//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef NODALRANKTWOSCALARUSEROBJECT_H
#define NODALRANKTWOSCALARUSEROBJECT_H

#include "NodalRankTwoTensorUserObject.h"

class NodalRankTwoScalarUserObject;

template <>
InputParameters validParams<NodalRankTwoScalarUserObject>();

/**
 * Userobject class to compute the equivalent scalar values for rank two tensor at individual
 * material point
 */
class NodalRankTwoScalarUserObject : public NodalRankTwoTensorUserObject
{
public:
  NodalRankTwoScalarUserObject(const InputParameters & parameters);

  virtual void
  assembleValue(unsigned int id, Real ib_dof, Real vbsum, Real vnsum, Real bond_status) override;

protected:
  /**
   * Determines the information to be extracted from the tensor by using the
   * RankTwoScalarTools namespace, e.g., vonMisesStress, EquivalentPlasticStrain,
   * L2norm, MaxPrincipal eigenvalue, etc.
   */
  MooseEnum _scalar_type;

  /// Start point for axis used to calculate some cylinderical material tensor quantities
  const Point _point1;

  /// End point for axis used to calculate some cylinderical material tensor quantities
  const Point _point2;

  /// Direction vector used to calculate some material tensor quantities
  Point _input_direction;
};

#endif // NODALRANKTWOSCALARUSEROBJECT_H
