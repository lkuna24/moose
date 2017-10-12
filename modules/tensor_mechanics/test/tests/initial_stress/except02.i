# Exception test: the incorrect number of initial stresses are supplied

[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 1
  ny = 1
  nz = 10
  xmin = -0.5
  xmax = 0.5
  ymin = -0.5
  ymax = 0.5
  zmin = -10
  zmax = 0
[]

[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
[]


[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
[]

[Kernels]
  [./TensorMechanics]
    displacements = 'disp_x disp_y disp_z'
  [../]
[]

[Materials]
  [./elasticity_tensor]
    type = ComputeElasticityTensor
    fill_method = symmetric_isotropic
    C_ijkl = '0.4 0.4' # young = 1, poisson = 0.25
  [../]
  [./strain]
    type = ComputeIncrementalSmallStrain
    eigenstrain_names = ini_stress
  [../]
  [./ini_stress]
    type = ComputeEigenstrainFromInitialStress
    initial_stress = '1 2 3 4 5 6 7 8 9'
    incremental_form = false
    eigenstrain_name = ini_stress
  [../]
  [./stress]
    type = ComputeFiniteStrainElasticStress
  [../]
[]


[Executioner]
  num_steps = 1
  solve_type = NEWTON
  type = Transient
[]
