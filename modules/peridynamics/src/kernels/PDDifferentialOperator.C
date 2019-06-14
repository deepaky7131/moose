//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PDDifferentialOperator.h"
#include "PeridynamicMesh.h"
#include "libmesh/dense_matrix_base.h"

registerMooseObject("PeridynamicsApp", PDDifferentialOperator);

template <>
InputParameters
validParams<PDDifferentialOperator>()
{
  InputParameters params = validParams<PDMechanicKernel>();
  params.addClassDescription("Base class for calculating residual and Jacobian for peridynamic "
                             "differential operator kernel");
  params.addRequiredParam<unsigned int>(
      "component",
      "An integer corresponding to the variable this kernel acts on (0 for x, 1 for y, 2 for z)");

  return params;
}

PDDifferentialOperator::PDDifferentialOperator(const InputParameters & parameters)
  : PDMechanicKernel(parameters),
    _lambda(getMaterialProperty<Real>("lambda")),
    _mu(getMaterialProperty<Real>("mu")),
    _component(getParam<unsigned int>("component"))
{
}

void
PDDifferentialOperator::prepare()
{
  PDMechanicKernel::prepare();

  _ABC_Matrix_coeff.resize(2, 3);
  _ABC_Matrix_coeff.zero();
  ComputeABC(_nodes_ij[0], _nodes_ij[1], 0);
  ComputeABC(_nodes_ij[1], _nodes_ij[0], 1);
}

void
PDDifferentialOperator::computeLocalResidual()
{

  if (_dim == 2)
  {

    Real ux1 = _disp_var[0]->getNodalValue(*_nodes_ij[0]);
    Real uy1 = _disp_var[1]->getNodalValue(*_nodes_ij[0]);
    Real ux2 = _disp_var[0]->getNodalValue(*_nodes_ij[1]);
    Real uy2 = _disp_var[1]->getNodalValue(*_nodes_ij[1]);

    if (_component == 0)
    {
      _local_re(0) = ((-_ABC_Matrix_coeff(0, 0) * ux2) + (-_ABC_Matrix_coeff(0, 1) * uy2) +
                      (_ABC_Matrix_coeff(0, 0) * ux1) + (_ABC_Matrix_coeff(0, 1) * uy1));

      _local_re(1) = ((-_ABC_Matrix_coeff(1, 0) * ux1) + (-_ABC_Matrix_coeff(1, 1) * uy1) +
                      (_ABC_Matrix_coeff(1, 0) * ux2) + (_ABC_Matrix_coeff(1, 1) * uy2));
    }
    if (_component == 1)
    {

      _local_re(0) = ((-_ABC_Matrix_coeff(0, 1) * ux2) + (-_ABC_Matrix_coeff(0, 2) * uy2) +
                      (_ABC_Matrix_coeff(0, 1) * ux1) + (_ABC_Matrix_coeff(0, 2) * uy1));

      _local_re(1) = ((-_ABC_Matrix_coeff(1, 1) * ux1) + (-_ABC_Matrix_coeff(1, 2) * uy1) +
                      (_ABC_Matrix_coeff(1, 1) * ux2) + (_ABC_Matrix_coeff(1, 2) * uy2));
    }
  }
}

void
PDDifferentialOperator::computeLocalJacobian()
{

  if (_dim == 2)
  {
    if (_component == 0)
    {

      _local_ke(0, 0) = _ABC_Matrix_coeff(0, 0);
      _local_ke(0, 1) = -_ABC_Matrix_coeff(0, 0);

      _local_ke(1, 0) = -_ABC_Matrix_coeff(1, 0);
      _local_ke(1, 1) = _ABC_Matrix_coeff(1, 0);
    }
    if (_component == 1)
    {

      _local_ke(0, 0) = _ABC_Matrix_coeff(0, 2);
      _local_ke(0, 1) = -_ABC_Matrix_coeff(0, 2);

      _local_ke(1, 0) = -_ABC_Matrix_coeff(1, 2);
      _local_ke(1, 1) = _ABC_Matrix_coeff(1, 2);
    }
  }
}

void
PDDifferentialOperator::computeLocalOffDiagJacobian(unsigned int coupled_component)
{

  if (_dim == 2)
  {
    if (coupled_component == 0)
    {

      _local_ke(0, 0) = _ABC_Matrix_coeff(0, 1);
      _local_ke(0, 1) = -_ABC_Matrix_coeff(0, 1);

      _local_ke(1, 0) = -_ABC_Matrix_coeff(1, 1);
      _local_ke(1, 1) = _ABC_Matrix_coeff(1, 1);
    }
    if (coupled_component == 1)
    {

      _local_ke(0, 0) = _ABC_Matrix_coeff(0, 1);
      _local_ke(0, 1) = -_ABC_Matrix_coeff(0, 1);

      _local_ke(1, 0) = -_ABC_Matrix_coeff(1, 1);
      _local_ke(1, 1) = _ABC_Matrix_coeff(1, 1);
    }
  }
}

void
PDDifferentialOperator::ComputeABC(Node * node1, Node * node2, unsigned int row)
{
  DenseVector<Real> Xi(_dim);
  DenseVector<Real> Xihat(_dim * (_dim + 1) / 2);
  DenseVector<Real> dVector;
  DenseVector<Real> gVector;
  DenseMatrix<Real> K11_mat(_dim, _dim);
  DenseMatrix<Real> K12_mat(_dim, _dim * (_dim + 1) / 2);
  DenseMatrix<Real> K21_mat(_dim * (_dim + 1) / 2, _dim);
  DenseMatrix<Real> K22_mat(_dim * (_dim + 1) / 2, _dim * (_dim + 1) / 2);
  Xi.zero();
  Xihat.zero();
  K11_mat.zero();
  K12_mat.zero();
  K21_mat.zero();
  K22_mat.zero();

  for (unsigned int i = 0; i < _dim; ++i)
  {
    Xi(i) = _pdmesh.coord(node2->id())(i) - _pdmesh.coord(node1->id())(i);
  }

  if (_dim == 2)
  {
    Xihat(0) = Xi(0) * Xi(0);
    Xihat(1) = Xi(1) * Xi(1);
    Xihat(2) = Xi(0) * Xi(1);
  }
  else
  {
    Xihat(0) = Xi(0) * Xi(0);
    Xihat(1) = Xi(1) * Xi(1);
    Xihat(2) = Xi(2) * Xi(2);
    Xihat(3) = Xi(0) * Xi(1);
    Xihat(4) = Xi(0) * Xi(2);
    Xihat(5) = Xi(1) * Xi(2);
  }

  ComputeKMatrix(node1, K11_mat, K12_mat, K21_mat, K22_mat);
  dVector.resize(_dim * (_dim + 1) / 2);
  gVector.resize(_dim);
  dVector.zero();
  gVector.zero();

  for (unsigned int ii = 0; ii < _dim * (_dim + 1) / 2; ++ii)
  {

    for (unsigned int jj = 0; jj < _dim; ++jj)
    {
      dVector(ii) += K21_mat(ii, jj) * Xi(jj);
    }
    for (unsigned int kk = 0; kk < _dim * (_dim + 1) / 2; ++kk)
    {
      dVector(ii) += K22_mat(ii, kk) * Xihat(kk);
    }
  }

  for (unsigned int ii = 0; ii < _dim; ++ii)
  {
    for (unsigned int jj = 0; jj < _dim; ++jj)
    {
      gVector(ii) += K11_mat(ii, jj) * Xi(jj);
    }
    for (unsigned int kk = 0; kk < _dim * (_dim + 1) / 2; ++kk)
    {
      gVector(ii) += K12_mat(ii, kk) * Xihat(kk);
    }
  }
  Real horizon = _pdmesh.horizon(node1->id());
  Real Xi_mag = Xi.l2_norm();
  Real weight = pow(exp(-4 * (Xi_mag / horizon)), 2); // horizon / Xi_mag;

  Real curr_bond_status = _bond_status_var.getElementalValue(_current_elem);

  Real vol_j = _pdmesh.volume(node2->id());

  ///normal vector
  DenseVector<Real> normal(_dim);
  for (unsigned int ii = 0; ii < _dim; ++ii)
  {
    normal(ii) = Xi(ii) / Xi.l2_norm();
  }

  // if (_pdmesh.on_boundary(node1->id()) == false)
  //{
  _ABC_Matrix_coeff(row, 0) = curr_bond_status * weight * vol_j *
                              ((_lambda[0] + (2.0 * _mu[0])) * dVector(0) + (_mu[0] * dVector(1)));
  _ABC_Matrix_coeff(row, 1) =
      curr_bond_status * weight * vol_j * (_lambda[0] + _mu[0]) * dVector(2);
  _ABC_Matrix_coeff(row, 2) = curr_bond_status * weight * vol_j *
                              ((_lambda[0] + (2.0 * _mu[0])) * dVector(1) + (_mu[0] * dVector(0)));
  //}
  // else
  //{
  //_ABC_Matrix_coeff(row, 0) = -curr_bond_status * weight * vol_j *
  //                            ((_lambda[0] + (2.0 * _mu[0])) * normal(0) * gVector(0) +
  //                             (_mu[0] * normal(1) * gVector(1)));
  //  _ABC_Matrix_coeff(row, 1) =
  //      -curr_bond_status * weight * vol_j *
  //      (_lambda[0] * gVector(1) * normal(0) + _mu[0] * gVector(0) * normal(1));
  //  _ABC_Matrix_coeff(row, 2) = -curr_bond_status * weight * vol_j *
  //                              ((_lambda[0] + (2.0 * _mu[0])) * normal(1) * gVector(1) +
  //                               (_mu[0] * normal(1) * gVector(0)));
  //}
}

/////////////////////////////////////////////////////////////////

void
PDDifferentialOperator::ComputeKMatrix(Node * cur_node,
                                       DenseMatrix<Real> & K11_temp,
                                       DenseMatrix<Real> & K12_temp,
                                       DenseMatrix<Real> & K21_temp,
                                       DenseMatrix<Real> & K22_temp)
{
  //// Declare local Variables
  unsigned int dimstar = _dim * (_dim + 1) / 2;

  DenseMatrix<Real> A11_mat;
  DenseMatrix<Real> A12_mat;
  DenseMatrix<Real> A21_mat;
  DenseMatrix<Real> A22_mat;
  DenseMatrix<Real> M_Matrix;
  M_Matrix.resize(dimstar, dimstar);
  DenseVector<Real> Xi;
  Xi.resize(_dim);
  DenseVector<Real> Xihat;
  Xihat.resize(dimstar);
  DenseMatrix<Real> TempMatrix1;
  DenseMatrix<Real> TempMatrix2;
  DenseMatrix<Real> TempMatrix;
  DenseMatrix<Real> A11_inv;
  A11_mat.resize(_dim, _dim);
  A12_mat.resize(_dim, dimstar);
  A21_mat.resize(dimstar, _dim);
  A22_mat.resize(dimstar, dimstar);
  A11_mat.zero();
  A12_mat.zero();
  A21_mat.zero();
  A22_mat.zero();
  Xi.zero();
  Xihat.zero();

  K11_temp.resize(_dim, _dim);
  K12_temp.resize(_dim, dimstar);
  K21_temp.resize(dimstar, _dim);
  K22_temp.resize(dimstar, dimstar);
  ///

  ///calculate the local matrices
  std::vector<dof_id_type> neighbors = _pdmesh.neighbors(cur_node->id());
  Real horizon = _pdmesh.horizon(cur_node->id());

  for (unsigned int k = 0; k < neighbors.size(); ++k)
  {

    for (unsigned int j = 0; j < _dim; ++j)
    {

      Xi(j) = _pdmesh.coord(neighbors[k])(j) - _pdmesh.coord(cur_node->id())(j);
    }

    if (_dim == 2)
    {
      Xihat(0) = Xi(0) * Xi(0);
      Xihat(1) = Xi(1) * Xi(1);
      Xihat(2) = Xi(0) * Xi(1);
    }
    if (_dim == 3)
    {
      Xihat(0) = Xi(0) * Xi(0);
      Xihat(1) = Xi(1) * Xi(1);
      Xihat(2) = Xi(2) * Xi(2);
      Xihat(3) = Xi(0) * Xi(1);
      Xihat(4) = Xi(0) * Xi(2);
      Xihat(5) = Xi(1) * Xi(2);
    }

    // A11 Matrix
    Real vol_k = _pdmesh.volume(neighbors[k]);

    Real Xi_mag = Xi.l2_norm();
    Real weight = pow(exp(-4 * (Xi_mag / horizon)), 2); // horizon / Xi_mag;

    for (unsigned int ii = 0; ii < _dim; ++ii)
    {

      for (unsigned int jj = 0; jj < _dim; ++jj)
      {

        A11_mat(ii, jj) += weight * Xi(ii) * Xi(jj) * vol_k;
      }
    }

    // A12 Matrix
    for (unsigned int ii = 0; ii < _dim; ++ii)
    {

      for (unsigned int jj = 0; jj < dimstar; ++jj)
      {

        if (jj < _dim)
        {
          A12_mat(ii, jj) += 0.5 * weight * Xi(ii) * Xihat(jj) * vol_k;
        }
        else
        {
          A12_mat(ii, jj) += weight * Xi(ii) * Xihat(jj) * vol_k;
        }
      }
    }

    // A21 Matrix

    for (unsigned int ii = 0; ii < dimstar; ++ii)
    {

      for (unsigned int jj = 0; jj < _dim; ++jj)
      {

        A21_mat(ii, jj) += weight * Xihat(ii) * Xi(jj) * vol_k;
      }
    }

    // A22 Matrix

    for (unsigned int ii = 0; ii < dimstar; ++ii)
    {

      for (unsigned int jj = 0; jj < dimstar; ++jj)
      {

        if (jj < _dim)
        {
          A22_mat(ii, jj) += 0.5 * weight * Xihat(ii) * Xihat(jj) * vol_k;
        }
        else
        {
          A22_mat(ii, jj) += weight * Xihat(ii) * Xihat(jj) * vol_k;
        }
      }
    }
  }

  ////////////////////////

  Real rcond = std::numeric_limits<Real>::epsilon();

  A11_mat.svdinv(A11_inv, rcond);

  // Ma Matrix calculation
  TempMatrix.resize(dimstar, _dim);
  TempMatrix.zero();

  TempMatrix = A21_mat;
  TempMatrix.right_multiply(A11_inv);
  TempMatrix.right_multiply(A12_mat);

  for (unsigned int ii = 0; ii < dimstar; ++ii)
  {

    for (unsigned int jj = 0; jj < dimstar; ++jj)
    {

      M_Matrix(ii, jj) = A22_mat(ii, jj) - TempMatrix(ii, jj);
    }
  }

  // K Matrix Calculation

  // K11 and K12 calculation

  DenseMatrix<Real> M_inv;
  M_Matrix.svdinv(M_inv, rcond);
  TempMatrix1.resize(_dim, _dim);
  TempMatrix1.zero();
  TempMatrix1 = A11_inv;
  TempMatrix1.right_multiply(A12_mat);
  TempMatrix1.right_multiply(M_inv);

  for (unsigned int ii = 0; ii < _dim; ++ii)
  {

    for (unsigned int jj = 0; jj < dimstar; ++jj)
    {
      K12_temp(ii, jj) = -1.0 * TempMatrix1(ii, jj);
    }
  }

  TempMatrix1.right_multiply(A21_mat);
  TempMatrix1.right_multiply(A11_inv);

  for (unsigned int ii = 0; ii < _dim; ++ii)
  {

    for (unsigned int jj = 0; jj < _dim; ++jj)
    {
      K11_temp(ii, jj) = TempMatrix1(ii, jj) + A11_inv(ii, jj);
    }
  }

  ////// K21 and K22 Calculation

  K22_temp = M_inv;
  TempMatrix2.resize(dimstar, dimstar);
  TempMatrix2.zero();

  TempMatrix2 = M_inv;
  TempMatrix2.right_multiply(A21_mat);
  TempMatrix2.right_multiply(A11_inv);

  for (unsigned int ii = 0; ii < dimstar; ++ii)
  {

    for (unsigned int jj = 0; jj < _dim; ++jj)
    {
      K21_temp(ii, jj) = -1.0 * TempMatrix2(ii, jj);
    }
  }
}
