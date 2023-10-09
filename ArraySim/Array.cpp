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
//coordinates are based off ISO 80000-2:2019 as seen at https://en.wikipedia.org/wiki/Spherical_coordinate_system
//theta is 90 degrees minus elevation, phi is azimuth starting from the positive x axis
vector<vector<float>> Array::simulate(float frequency, int el_count, int az_count, float az_start, float az_end, float el_start, float el_end)
{
	vector<vector<float>> results;
	//sweep across the sphere
	float wavelength = c0 / frequency;
	float quarter_wavelength = c0 / frequency / 4;
	//2 * D^2 / lambda
	float radius = 2 * 100 * wavelength * wavelength / 2 / wavelength;//I know it's not simplified
	int pos = 0;
	for (float el = el_start; el < el_end; el += (el_end - el_start) / el_count)
	{
		vector<float> el_line;
		for (float az = az_start; az < az_end; az += (az_end - az_start) / az_count)
		{
			//elevation/azumith of 0 is pointing towards positive y
			float x = radius * cos(az) * cos(el);
			float y = radius * cos(az) * sin(el);
			float z = radius * cos(az);

			float i_sum = 0;
			float q_sum = 0;
			for (size_t i = 0; i < antennas.size(); i++)
			{
				float a_x = std::get<0>(antenna_positions[i]);
				float a_y = std::get<1>(antenna_positions[i]);
				float a_z = std::get<2>(antenna_positions[i]);

				float dx = x - a_x;
				float dy = y - a_y;
				float dz = z - a_z;
				float distance = sqrt(dx * dx + dy * dy + dz * dz);
				float phase_shift_distance = fmod(distance, wavelength);
				float phase_rad = phase_shift_distance / wavelength + antennas[i]->get_phase(el, az, frequency);

				float i_mag = cos(phase_rad) * antennas[i]->get_gain(el, az, frequency);
				float q_mag = sin(phase_rad) * antennas[i]->get_gain(el, az, frequency);

				i_sum += i_mag;
				q_sum += q_mag;
			}
			el_line.push_back(sqrt(i_sum * i_sum + q_sum * q_sum));
		}
		results.push_back(el_line);
	}



	return results;
}

vector<vector<vector<float>>> Array::simulate_sweep(float start_frequency, float stop_frequency, int freq_count, int el_count, int az_count, float az_start, float az_end, float el_start, float el_end)
{
	return vector<vector<vector<float>>>();
}
