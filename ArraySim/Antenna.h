#pragma once

//assumed LTI system
//at some point I might want to make an antenna variant that doesn't assume that and takes in the input wave as an input
class Antenna
{

public:
	//virtual void set_frequency(double freq);//sets the frequency of the antenna
	virtual double get_gain(double el, double az, double frequency);//in radians, samples from linear, not logarithmic, gain pattern
	virtual void set_taper(double taper);//taper is a static multiplier to use for the gain
	virtual void set_phase(double phase);//the phase offset for array steering
	virtual double get_phase(double el, double az, double frequency);//basic model would ignore arguments

};