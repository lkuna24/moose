/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "GasFreeEnergyBase.h"

template <>
InputParameters
validParams<GasFreeEnergyBase>()
{
  InputParameters params = validParams<DerivativeParsedMaterialHelper>();
  params.addRequiredCoupledVar("T", "Temperature");
  // MooseEnum molecule("MONOATOMIC DIATOMIC", "MONOATOMIC");
  // params.addParam<MooseEnum>("molecule", molecule, "Gas molecule size");
  params.addRequiredCoupledVar("c", "Concentration variable");
  params.addRequiredParam<Real>(
      "omega", "Lattice site volume (default mass_unit_conversion requires this to be in [Ang^3])");
  params.addRequiredParam<Real>(
      "m", "Gas atom mass (the default mass_unit_conversion requires this to be in [u])");
  params.addParam<Real>("mass_unit_conversion",
                        1.0364271410595204e-28,
                        "Conversion factor to get the gas atom mass in [eV*s^2/Ang^2] (defaults "
                        "to [eV*s^2/(Ang^2*u)])");
  params.addParam<Real>("h",
                        4.135667662e-15,
                        "Planck constant - units need to be consistent with "
                        "the units of omega (default in [eV*s])");
  params.addParam<Real>("kB", 8.6173303e-5, "Boltzmann constant (default in [eV/K])");
  params.addParamNamesToGroup("mass_unit_conversion h kB", "Units");
  return params;
}

GasFreeEnergyBase::GasFreeEnergyBase(const InputParameters & parameters)
  : DerivativeParsedMaterialHelper(parameters),
    _T("T"),
    _c("c"),
    _omega(getParam<Real>("omega")),
    _m(getParam<Real>("m") * getParam<Real>("mass_unit_conversion")),
    _h(getParam<Real>("h")),
    _kB(getParam<Real>("kB")),
    _n(_c / _omega),
    _nq(pow(2.0 * libMesh::pi * _m * _kB * _T / (_h * _h), 3.0 / 2.0))
{
}
