//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PDNODALPOSTPROCESSOR_H
#define PDNODALPOSTPROCESSOR_H

#include "NodalPostprocessor.h"
#include "PeridynamicMesh.h"

// Forward Declarations
class PDNodalPostprocessor;

template <>
InputParameters validParams<PDNodalPostprocessor>();

/**
 * Base postprocessor class for peridynamic calculation
 */
class PDNodalPostprocessor : public NodalPostprocessor
{
public:
  PDNodalPostprocessor(const InputParameters & parameters);

protected:
  /// Reference to peridynamic mesh object
  PeridynamicMesh & _pdmesh;

  /// Mesh dimension
  const unsigned int _dim;
};

#endif // PDNODALPOSTPROCESSOR
