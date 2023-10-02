#pragma once

//assumed LTI system
//at some point I might want to make an antenna variant that doesn't assume that and takes in the input wave as an input
class Antenna
{

public:
	//virtual void set_frequency(float freq);//sets the frequency of the antenna
	virtual float get_gain(float el, float az, float frequency);//in radians, samples from linear, not logarithmic, gain pattern
	virtual void set_taper(float taper);//taper is a static multiplier to use for the gain
	virtual void set_phase(float phase);//the phase offset for array steering
	virtual float get_phase(float el, float az, float frequency);//basic model would ignore arguments

};