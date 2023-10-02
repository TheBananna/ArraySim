#include "Dipole.h"

float Dipole::get_gain(float el, float az, float frequency)
{
    return 0.0f;
}

void Dipole::set_taper(float taper)
{
    this->taper = taper;
}

void Dipole::set_phase(float phase)
{
    this->phase = phase;
}

float Dipole::get_phase(float el, float az, float frequency)
{
    return phase;
}
