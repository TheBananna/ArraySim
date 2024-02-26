#pragma once
#include "Antenna.h"
#include "Constants.h"
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
#include <tuple>
#include <complex>
#include "Types.h"

//operates in free space right now
//maybe come up with some method of handling how antennas will radiate differently down the antenna? Like they aren't actually point sources even if we model them as such
class Array
{
	std::vector<Antenna*> antennas;
	std::vector<vec3d> antenna_positions;

public:
	void add_antenna(Antenna* antenna, vec3d pos);//adds an antenna at a certain position in meters
	void remove_antenna(Antenna* antenna);//removes an antenna that was added
	void clear_antennas();//clears all antennas
	

	//el_count and az_count define the fidelity of the simulation, the returned 2D vector is el_count x az_count in size
	//intensity is linear
	double sim_el_az(double frequency, double el, double az);
	double sim_el_az2(double frequency, double el, double az, double spacing);
	std::vector<std::vector<double>> simulate(double frequency, int el_count, int az_count, double az_start = -M_PI_2, double az_end = M_PI_2, double el_start = -M_PI_2, double el_end = M_PI_2);//does a pattern calculation at one frequency
	std::vector<std::vector<std::vector<double>>> simulate_sweep(double start_frequency, double stop_frequency, int freq_count, int el_count, int az_count, double az_start = 0, double az_end = M_PI, double el_start = -M_PI/2, double el_end = M_PI/2);
};