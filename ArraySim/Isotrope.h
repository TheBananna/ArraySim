#pragma once
#include "Antenna.h"

class Isotrope : public Antenna
{
private:
	double taper = 1;
	double phase = 0;

public:
	double get_gain(double el, double az, double frequency);//in radians, samples from linear, not logarithmic, gain pattern
	void set_taper(double taper);//taper is a static multiplier to use for the gain
	void set_phase(double phase);//the phase offset for array steering
	double get_phase(double el, double az, double frequency);//basic model would ignore arguments
};