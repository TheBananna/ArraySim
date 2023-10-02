#include "Array.h"

void Array::add_antenna(Antenna* antenna, float x, float y, float z)
{
	antennas.push_back(antenna);
	antenna_positions.push_back(std::make_tuple(x, y, z));
}

void Array::remove_antenna(Antenna* antenna)
{
	for (size_t i = 0; i < antennas.size(); i++)
	{
		if (antenna == antennas[i])
		{
			antennas.erase(antennas.begin() + i);
			antenna_positions.erase(antenna_positions.begin() + i);
		}
	}
}

void Array::clear_antennas()
{
	antennas.clear();
	antenna_positions.clear();
}

//right now assuming all antennas are less than 10 x the wavelength through free space
vector<vector<float>> Array::simulate(float frequency, int el_count, int az_count, float az_start, float az_end, float el_start, float el_end)
{
	//sweep across the sphere
	float wavelength = 
	float radius = 
	for (float az = az_start; az < az_end; az++)
	{
		for (float el = el_start; el < el_end; el++)
		{

		}
	}



	return vector<vector<float>>();
}

vector<vector<vector<float>>> Array::simulate_sweep(float start_frequency, float stop_frequency, int freq_count, int el_count, int az_count, float az_start, float az_end, float el_start, float el_end)
{
	return vector<vector<vector<float>>>();
}
