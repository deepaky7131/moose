[GlobalParams]
  displacements = 'disp_x disp_y'
  temperature = temp
[]

[Mesh]
  type = FileMeshPD
  file = disk_tri.e
  horizon_number = 3
[]

[Variables]
  [./disp_x]
    order = FIRST
    family = LAGRANGE
  [../]
  [./disp_y]
    order = FIRST
    family = LAGRANGE
  [../]

  [./temp]
    order = FIRST
    family = LAGRANGE
    initial_condition = 300.0
  [../]
[]

[AuxVariables]
  [./bond_status]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 1.0
  [../]

  [./creep_strain_xx]
    order = FIRST
    family = LAGRANGE
  [../]
  [./creep_strain_yy]
    order = FIRST
    family = LAGRANGE
  [../]
  [./creep_strain_xy]
    order = FIRST
    family = LAGRANGE
  [../]

  [./vonmises]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./solid_x]
    type = FiniteSNOSPDKernel
    variable = disp_x
    component = 0
    eigenstrain_names = thermal_strain
    use_displaced_mesh = true
  [../]
  [./solid_y]
    type = FiniteSNOSPDKernel
    variable = disp_y
    component = 1
    eigenstrain_names = thermal_strain
    use_displaced_mesh = true
  [../]
  [./heatconduction]
    type = HeatConductionBPD
    variable = temp
  [../]
  [./heatsource]
    type = HeatSourceBPD
    variable = temp
    power_density_function = power_func
  [../]
[]

[Materials]
  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 2.0e5
    poissons_ratio = 0.345
  [../]
  [./strain]
    type = CorrespondencePlaneFiniteStrain
    eigenstrain_names = thermal_strain
  [../]
  [./thermal_strain]
    type = ComputeThermalExpansionEigenstrain
    eigenstrain_name = thermal_strain
    stress_free_temperature = 300.0
    thermal_expansion_coeff = 1.0e-5
  [../]
  [./stress]
    type = ComputeMultipleInelasticStress
    inelastic_models = 'power_law_creep'
  [../]
  [./power_law_creep]
    type = PowerLawCreepStressUpdate
    coefficient = 3.125e-14
    n_exponent = 5.0
    m_exponent = 0.0
    activation_energy = 1000.0
    max_inelastic_increment = 0.01
  [../]

  [./thermal_material]
    type = BPDThermalVariableHorizon
    thermal_conductivity = 5.0
  [../]
[]

[UserObjects]
  [./creep_strain_xx_uo]
    type = NodalRankTwoComponentUserObject
    rank_two_tensor = creep_strain
    aux_variable = creep_strain_xx
    index_i = 0
    index_j = 0
  [../]
  [./creep_strain_yy_uo]
    type = NodalRankTwoComponentUserObject
    rank_two_tensor = creep_strain
    aux_variable = creep_strain_yy
    index_i = 1
    index_j = 1
  [../]
  [./creep_strain_xy_uo]
    type = NodalRankTwoComponentUserObject
    rank_two_tensor = creep_strain
    aux_variable = creep_strain_xy
    index_i = 0
    index_j = 1
  [../]

  [./vonmises_uo]
    type = NodalRankTwoScalarUserObject
    rank_two_tensor = stress
    scalar_type = VonMisesStress
    aux_variable = vonmises
  [../]

  [./Ghost_elem_uo]
    type = GhostElemPDUserObject
  [../]
[]

[Functions]
  [./power_func]
    type = PiecewiseLinear
    x = '0  1.0e4    1.0e8'
    y = '0  473.39 473.39' # mW/mm3
  [../]
  [./temp_bc]
    type = PiecewiseLinear
    xy_data = '0.0000000e+000  3.0000000e+002
               1.0000000e+002  5.7602620e+002
               2.0000000e+002  5.8868136e+002
               3.0000000e+002  5.9354501e+002
               4.0000000e+002  5.9803698e+002
               5.0000000e+002  6.0246166e+002
               6.0000000e+002  6.0683317e+002
               7.0000000e+002  6.1115311e+002
               8.0000000e+002  6.1542251e+002
               9.0000000e+002  6.1964236e+002
               1.0000000e+003  6.2381358e+002
               1.1000000e+003  6.2793709e+002
               1.2000000e+003  6.3201376e+002
               1.3000000e+003  6.3604445e+002
               1.4000000e+003  6.4002998e+002
               1.5000000e+003  6.4397114e+002
               1.6000000e+003  6.4786872e+002
               1.7000000e+003  6.5172346e+002
               1.8000000e+003  6.5553611e+002
               1.9000000e+003  6.5930737e+002
               2.0000000e+003  6.6303796e+002
               2.1000000e+003  6.6672853e+002
               2.2000000e+003  6.7037976e+002
               2.3000000e+003  6.7399234e+002
               2.4000000e+003  6.7756681e+002
               2.5000000e+003  6.8110388e+002
               2.6000000e+003  6.8460411e+002
               2.7000000e+003  6.8806812e+002
               2.8000000e+003  6.9149648e+002
               2.9000000e+003  6.9488976e+002
               3.0000000e+003  6.9824854e+002
               3.1000000e+003  7.0157338e+002
               3.2000000e+003  7.0486476e+002
               3.3000000e+003  7.0812322e+002
               3.4000000e+003  7.1134929e+002
               3.5000000e+003  7.1454345e+002
               3.6000000e+003  7.1770619e+002
               3.7000000e+003  7.2083798e+002
               3.8000000e+003  7.2393919e+002
               3.9000000e+003  7.2701042e+002
               4.0000000e+003  7.3005203e+002
               4.1000000e+003  7.3306446e+002
               4.2000000e+003  7.3604808e+002
               4.3000000e+003  7.3900325e+002
               4.4000000e+003  7.4193037e+002
               4.5000000e+003  7.4482980e+002
               4.6000000e+003  7.4770188e+002
               4.7000000e+003  7.5054697e+002
               4.8000000e+003  7.5336536e+002
               4.9000000e+003  7.5615738e+002
               5.0000000e+003  7.5892332e+002
               5.1000000e+003  7.6166351e+002
               5.2000000e+003  7.6437809e+002
               5.3000000e+003  7.6706738e+002
               5.4000000e+003  7.6973168e+002
               5.5000000e+003  7.7237121e+002
               5.6000000e+003  7.7498620e+002
               5.7000000e+003  7.7757687e+002
               5.8000000e+003  7.8014344e+002
               5.9000000e+003  7.8268613e+002
               6.0000000e+003  7.8520510e+002
               6.1000000e+003  7.8770060e+002
               6.2000000e+003  7.9017276e+002
               6.3000000e+003  7.9262179e+002
               6.4000000e+003  7.9504785e+002
               6.5000000e+003  7.9745112e+002
               6.6000000e+003  7.9983176e+002
               6.7000000e+003  8.0218986e+002
               6.8000000e+003  8.0452571e+002
               6.9000000e+003  8.0683937e+002
               7.0000000e+003  8.0913095e+002
               7.1000000e+003  8.1140067e+002
               7.2000000e+003  8.1364861e+002
               7.3000000e+003  8.1587485e+002
               7.4000000e+003  8.1807958e+002
               7.5000000e+003  8.2026287e+002
               7.6000000e+003  8.2242480e+002
               7.7000000e+003  8.2456544e+002
               7.8000000e+003  8.2668483e+002
               7.9000000e+003  8.2047428e+002
               8.0000000e+003  8.1649166e+002
               8.1000000e+003  8.1519224e+002
               8.2000000e+003  8.1470729e+002
               8.3000000e+003  8.1459804e+002
               8.4000000e+003  8.1471836e+002
               8.5000000e+003  8.1499084e+002
               8.6000000e+003  8.1536815e+002
               8.7000000e+003  8.1582063e+002
               8.8000000e+003  8.1632844e+002
               8.9000000e+003  8.1687609e+002
               9.0000000e+003  8.1745282e+002
               9.1000000e+003  8.1805006e+002
               9.2000000e+003  8.1866094e+002
               9.3000000e+003  8.1927988e+002
               9.4000000e+003  8.1990224e+002
               9.5000000e+003  8.2052362e+002
               9.6000000e+003  8.2114187e+002
               9.7000000e+003  8.2175388e+002
               9.8000000e+003  8.2235750e+002
               9.9000000e+003  8.2295103e+002
               1.0000000e+004  8.2353311e+002
               1.0100000e+004  8.2350435e+002
               1.0200000e+004  8.2344182e+002
               1.0300000e+004  8.2338339e+002
               1.0400000e+004  8.2332938e+002
               1.0500000e+004  8.2327904e+002
               1.0600000e+004  8.2323176e+002
               1.0700000e+004  8.2318705e+002
               1.0800000e+004  8.2314457e+002
               1.0900000e+004  8.2310404e+002
               1.1000000e+004  8.2306521e+002
               1.1100000e+004  8.2302790e+002
               1.1200000e+004  8.2299193e+002
               1.1300000e+004  8.2295719e+002
               1.1400000e+004  8.2292354e+002
               1.1500000e+004  8.2289090e+002
               1.1600000e+004  8.2285919e+002
               1.1700000e+004  8.2282831e+002
               1.1800000e+004  8.2279822e+002
               1.1900000e+004  8.2276885e+002
               1.2000000e+004  8.2274015e+002
               1.2100000e+004  8.2271209e+002
               1.2200000e+004  8.2268460e+002
               1.2300000e+004  8.2265767e+002
               1.2400000e+004  8.2263126e+002
               1.2500000e+004  8.2260534e+002
               1.2600000e+004  8.2257988e+002
               1.2700000e+004  8.2255485e+002
               1.2800000e+004  8.2253024e+002
               1.2900000e+004  8.2250602e+002
               1.3000000e+004  8.2248217e+002
               1.3100000e+004  8.2245868e+002
               1.3200000e+004  8.2243553e+002
               1.3300000e+004  8.2241270e+002
               1.3400000e+004  8.2239019e+002
               1.3500000e+004  8.2236797e+002
               1.3600000e+004  8.2234604e+002
               1.3700000e+004  8.2232439e+002
               1.3800000e+004  8.2230300e+002
               1.3900000e+004  8.2228186e+002
               1.4000000e+004  8.2226096e+002
               1.4100000e+004  8.2224031e+002
               1.4200000e+004  8.2221987e+002
               1.4300000e+004  8.2219966e+002
               1.4400000e+004  8.2217966e+002
               1.4500000e+004  8.2215986e+002
               1.4600000e+004  8.2214027e+002
               1.4700000e+004  8.2212086e+002
               1.4800000e+004  8.2210165e+002
               1.4900000e+004  8.2208262e+002
               1.5000000e+004  8.2206375e+002'
  [../]
[]

[BCs]
  [./outer_temp]
    type = FunctionPresetBC
    variable = temp
    boundary = 1
    function = temp_bc
  [../]
  [./center_fix_x]
    type = DirichletBC
    variable = disp_x
    boundary = 100
    value = 0.0
  [../]
  [./center_fix_y]
    type = DirichletBC
    variable = disp_y
    boundary = 100
    value = 0.0
  [../]
  [./right_fix_y]
    type = DirichletBC
    variable = disp_y
    boundary = 101
    value = 0.0
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

  petsc_options = '-snes_ksp_ew'
  petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'
  petsc_options_value = 'lu superlu_dist'

  l_max_its = 20
  l_tol = 1e-08
  nl_max_its = 50
  nl_abs_tol = 1e-08
  dt = 50
  dtmin = 10
  end_time = 1.5e4
[]

[Outputs]
  exodus = true
[]
