//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PDDIFFERENTIALOPERATOR_H
#define PDDIFFERENTIALOPERATOR_H

#include "PDMechanicKernel.h"
#include "libmesh/dense_matrix_base.h"

class PDDifferentialOperator;
class PeridynamicMesh;

template <>
InputParameters validParams<PDDifferentialOperator>();

class PDDifferentialOperator : public PDMechanicKernel
{
public:
  PDDifferentialOperator(const InputParameters & parameters);

  virtual void prepare() override;

protected:
  virtual void computeLocalResidual() override;
  virtual void computeLocalJacobian() override;

  void computeLocalOffDiagJacobian(unsigned int coupled_component) override;
  void ComputeABC(Node * node1, Node * node2, unsigned int row);
  void ComputeKMatrix(Node * cur_node,
                      DenseMatrix<Real> & K11_temp,
                      DenseMatrix<Real> & K12_temp,
                      DenseMatrix<Real> & K21_temp,
                      DenseMatrix<Real> & K22_temp);

  const MaterialProperty<Real> & _lambda;
  const MaterialProperty<Real> & _mu;

  const unsigned int _component;

  DenseMatrix<Real> _ABC_Matrix_coeff;
};

#endif // PDDIFFERENTIALOPERATOR_H
