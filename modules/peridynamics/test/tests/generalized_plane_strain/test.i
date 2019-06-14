[Mesh]
  type = PeridynamicsMesh
  dim =2
  shape =2
  nr = 50
  R =4.1
  partitioner = centriod
  centroid_partinoner_direction = y
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
    initial_condition = 300.0
  [../]
[]

[AuxVariables]
  [./axial_force]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stiff_elem]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./bond_status]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./bond_strech]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./critical_stretch]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./nodal_power]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Materials]
  [./linelast]
    type = PeridynamicBond
    block = 0
    disp_x = disp_x
    disp_y = disp_y
    temp = temp
    PDdim = 2
    youngs_modulus = 200000
    poissions_ratio = 0.345
    MeshSpacing = 0.08118812
    ThicknessPerLayer = 1.0
    CriticalStretch = 0.0005
    StandardDeviation = 0.0001
    reference_temp = 300.0
    thermal_expansion = 0.00001
    thermal_conductivity = 5.0
  [../]
[]
