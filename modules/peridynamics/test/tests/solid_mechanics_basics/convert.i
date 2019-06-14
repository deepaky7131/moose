[Mesh]
  type = FileMesh
  file = plate_uniform.msh
[]

[Variables]
  [./empty]
  [../]
[]

[Kernels]
  [nothing]
    type = NullKernel
    variable = empty
  []
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = PJFNK
  line_search = none
[]

[Outputs]
  file_base = plate
  exodus = true
[]
