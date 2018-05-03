//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef CORRESPONDENCESMALLSTRAIN_H
#define CORRESPONDENCESMALLSTRAIN_H

#include "CorrespondenceMaterial.h"
#include "RankTwoTensor.h"

class CorrespondenceSmallStrain;

template <>
InputParameters validParams<CorrespondenceSmallStrain>();

/**
 * Material class for bond-associated correspondence material model for small strain
 */
class CorrespondenceSmallStrain : public CorrespondenceMaterial
{
public:
  CorrespondenceSmallStrain(const InputParameters & parameters);

protected:
  virtual void computeQpStrain() override;

  /**
   * Function to compute the total strain tensor for small strain case
   */
  virtual void computeQpTotalStrain();
};

#endif // CORRESPONDENCESMALLSTRAIN_H
