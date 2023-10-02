#pragma once
#include "Antenna.h"

class Isotrope : Antenna
{
private:
	float taper;
	float phase;

public:
	float get_gain(float el, float az, float frequency);//in radians, samples from linear, not logarithmic, gain pattern
	void set_taper(float taper);//taper is a static multiplier to use for the gain
	void set_phase(float phase);//the phase offset for array steering
	float get_phase(float el, float az, float frequency);//basic model would ignore arguments
};