//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef GENERALIZEDPLANESTRAINPDUSEROBJECT_H
#define GENERALIZEDPLANESTRAINPDUSEROBJECT_H

#include "PDElementUserObject.h"

class GeneralizedPlaneStrainPDUserObject;
class RankFourTensor;

template <>
InputParameters validParams<GeneralizedPlaneStrainPDUserObject>();

/**
 * Base userObject class to compute the residual and diagonal Jacobian components for scalar
 * out-of-plane strain variable of generalized plane strain model based on peridynamic models
 */
class GeneralizedPlaneStrainPDUserObject : public PDElementUserObject
{
public:
  GeneralizedPlaneStrainPDUserObject(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void threadJoin(const UserObject & uo) override;
  virtual void finalize() override;

  /**
   * Function to return the computed residual
   */
  Real returnResidual() const;

  /**
   * Function to return the computed diagonal Jacobian
   */
  Real returnJacobian() const;

protected:
  /// Elasticity tensor
  const MaterialProperty<RankFourTensor> & _Cijkl;

  ///@{ Applied out-of-plane force parameters
  Function & _pressure;
  const Real _factor;
  ///@}

  /// Residual parameter
  Real _residual;

  /// Jacobian parameter
  Real _jacobian;
};

#endif // GENERALIZEDPLANESTRAINPDUSEROBJECT_H
