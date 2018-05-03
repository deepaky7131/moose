//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef NODALAREAAUX_H
#define NODALAREAAUX_H

#include "AuxKernel.h"

class NodalAreaAux;
class PeridynamicMesh;

template <>
InputParameters validParams<NodalAreaAux>();

/**
 * Aux Kernel class to output the area/volume of material points
 */
class NodalAreaAux : public AuxKernel
{
public:
  NodalAreaAux(const InputParameters & parameters);

protected:
  Real computeValue() override;

  /// Reference to peridynamic mesh object
  PeridynamicMesh & _pdmesh;
};

#endif // NODALAREAAUX_H
