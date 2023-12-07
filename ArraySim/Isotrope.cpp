#include "Isotrope.h"

double Isotrope::get_gain(double el, double az, double frequency)
{
    return 1 * taper;
}

void Isotrope::set_taper(double taper)
{
    this->taper = taper;
}

void Isotrope::set_phase(double phase)
{
    this->phase = phase;
}

double Isotrope::get_phase(double el, double az, double frequency)
{
    return this->phase;
}
