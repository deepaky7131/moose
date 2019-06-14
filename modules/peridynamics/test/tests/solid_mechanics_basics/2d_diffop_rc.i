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
  file = plate_hole.e
  horizon_number = 3
[]

[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[AuxVariables]
  [./bond_status]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 1
  [../]
  [./von_mises]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[BCs]
  [./top_dy]
    type = DirichletBC
    variable = disp_y
    boundary = 2
    value = 0.0
  [../]
  [./left_dx]
    type = DirichletBC
    variable = disp_x
    boundary = 3
    value = 0.0
  [../]
  [./bottom_dy]
    type = FunctionPresetBC
    variable = disp_y
    boundary = 4
    function = '-0.01*t'
  [../]
[]

[Kernels]
  [./disp_x]
    type = PDDifferentialOperator
    variable = disp_x
    component = 0
  [../]
  [./disp_y]
    type = PDDifferentialOperator
    variable = disp_y
    component = 1
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
    type = LamesParameter
    youngs_modulus = 2e5
    poissons_ratio = 0.33
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
    ksp_norm = default
  [../]
[]

[Executioner]
  type = Transient
  solve_type = PJFNK
  line_search = none
  petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'
  petsc_options_value = 'lu     superlu_dist'
  start_time = 0
  end_time = 1
[]

[Outputs]
  file_base = 2d_diffop_rc
  exodus = true
[]
