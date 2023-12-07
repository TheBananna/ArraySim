#pragma once
#include "Antenna.h"
#include "Constants.h"
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
#include <tuple>
#include <complex>

//operates in free space right now
//maybe come up with some method of handling how antennas will radiate differently down the antenna? Like they aren't actually point sources even if we model them as such
class Array
{
	std::vector<Antenna*> antennas;
	std::vector<std::tuple<float, float, float>> antenna_positions;

public:
	void add_antenna(Antenna* antenna, float x, float y, float z);//adds an antenna at a certain position in meters
	void remove_antenna(Antenna* antenna);//removes an antenna that was added
	void clear_antennas();//clears all antennas
	

	//el_count and az_count define the fidelity of the simulation, the returned 2D vector is el_count x az_count in size
	//intensity is linear
	float sim_el_az(float frequency, float el, float az);
	float sim_el_az2(float frequency, float el, float az);
	std::vector<std::vector<float>> simulate(float frequency, int el_count, int az_count, float az_start = -M_PI_2, float az_end = M_PI_2, float el_start = -M_PI_2, float el_end = M_PI_2);//does a pattern calculation at one frequency
	std::vector<std::vector<std::vector<float>>> simulate_sweep(float start_frequency, float stop_frequency, int freq_count, int el_count, int az_count, float az_start = 0, float az_end = M_PI, float el_start = -M_PI/2, float el_end = M_PI/2);
};