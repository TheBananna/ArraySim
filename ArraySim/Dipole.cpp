#include "Dipole.h"

double Dipole::get_gain(double el, double az, double frequency)
{
    return 0.0f;
}

void Dipole::set_taper(double taper)
{
    this->taper = taper;
}

void Dipole::set_phase(double phase)
{
    this->phase = phase;
}

double Dipole::get_phase(double el, double az, double frequency)
{
    return phase;
}
