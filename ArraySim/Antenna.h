#pragma once

//assumed LTI system
class Antenna
{

public:
	virtual void set_frequency(float freq);//sets the frequency of the antenna
	virtual float get_gain(float el, float az, float frequency);//in radians, samples from linear, not logarithmic, gain pattern
	virtual void set_taper(float taper);//taper is a static multiplier to use for the gain

};