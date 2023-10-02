#pragma once
#include "Antenna.h"
#include "Constants.h"
#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
#include <tuple>
using namespace std;

//operates in free space right now
//maybe come up with some method of handling how antennas will radiate differently down the antenna? Like they aren't actually point sources even if we model them as such
class Array
{
	vector<Antenna*> antennas;
	vector<tuple<float, float, float>> antenna_positions;

public:
	void add_antenna(Antenna* antenna, float x, float y, float z);//adds an antenna at a certain position in meters
	void remove_antenna(Antenna* antenna);//removes an antenna that was added
	void clear_antennas();//clears all antennas
	

	//el_count and az_count define the fidelity of the simulation, the returned 2D vector is el_count x az_count in size
	//intensity is linear
	vector<vector<float>> simulate(float frequency, int el_count, int az_count, float az_start = 0, float az_end = M_PI, float el_start = 0, float el_end = M_PI);//does a pattern calculation at one frequency
	vector<vector<vector<float>>> simulate_sweep(float start_frequency, float stop_frequency, int freq_count, int el_count, int az_count, float az_start = 0, float az_end = M_PI, float el_start = 0, float el_end = M_PI);
};