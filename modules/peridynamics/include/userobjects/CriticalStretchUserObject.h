//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef CRITICALSTRETCHUSEROBJECT_H
#define CRITICALSTRETCHUSEROBJECT_H

#include "GeneralUserObject.h"
#include "PeridynamicMesh.h"

class CriticalStretchUserObject;

template <>
InputParameters validParams<CriticalStretchUserObject>();

/**
 * Userobject class to assign value to the bond critical stretch aux variable for fracture modeling
 * and simulation
 */
class CriticalStretchUserObject : public GeneralUserObject
{
public:
  CriticalStretchUserObject(const InputParameters & parameters);

  virtual void initialize() override{};
  virtual void execute() override;
  virtual void finalize() override;

protected:
  ///@{ Peridynamic mesh information
  MooseMesh & _mesh;
  PeridynamicMesh & _pdmesh;
  ///@}

  AuxiliarySystem & _aux;

  /// Solution vector for all aux variables
  NumericVector<Number> & _aux_sln;

  /// Critical stretch aux variable
  MooseVariableFEBase * _critical_stretch_var;

  ///@{ Paramters for Gaussian distribution
  const Real _mean;
  const Real _standard_deviation;
  ///@}
};

#endif // CRITICALSTRETCHUSEROBJECT_H
