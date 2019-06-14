# Test for bond-based peridynamic formulation
# for regular grid from generated mesh with const bond constants

# Square plate with Dirichlet boundary conditions applied
# at the left, top and bottom edges

[GlobalParams]
  displacements = 'disp_x disp_y'
  poissons_ratio = 0.33
  youngs_modulus = 2e5
[]

[Mesh]
  type = FileMeshPD
  file = plate.e
  horizon_number = 3
[]



[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[AuxVariables]
  [./von_mises]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[BCs]
  [./top_dy]
    type = DirichletBC
    variable = disp_x
    boundary = 2
    value = 0.0
  [../]
  [./bottom_dy]
    type = FunctionPresetBC
    variable = disp_x
    boundary = 4
    function = '-0.01*t'
  [../]
[]

[Modules]
  [./Peridynamics]
    [./Mechanics]
    [../]
  [../]
[]

[AuxKernels]
  [./vonmises]
    type = NodalStressStrainAux
    rank_two_tensor = stress
    variable = von_mises
    quantity_type = VonMisesStress
  [../]
[]


[Materials]
  [./linelast]
    type = BPDSmallStrainConstantHorizon
    youngs_modulus = 2e5
    poissons_ratio = 0.33
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  solve_type = PJFNK
  line_search = none
  petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'
  petsc_options_value = 'lu     superlu_dist'
  start_time = 0
  end_time = 2
[]

[Outputs]
  file_base = 2d_bond_test1
  exodus = true
[]
