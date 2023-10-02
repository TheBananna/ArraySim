#include "Isotrope.h"

float Isotrope::get_gain(float el, float az, float frequency)
{
    return 1;
}

void Isotrope::set_taper(float taper)
{
    this->taper = taper;
}

void Isotrope::set_phase(float phase)
{
    this->phase = phase;
}

float Isotrope::get_phase(float el, float az, float frequency)
{
    return phase;
}
