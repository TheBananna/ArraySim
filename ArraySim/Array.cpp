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

float Array::sim_el_az(float frequency, float el, float az)
{
	float wavelength = c0 / frequency;
	float radius = 2 * 1000 * wavelength * wavelength / wavelength;

	float y = radius * cos(el) * cos(az);
	float x = radius * sin(az) * cos(el);
	float z = radius * sin(el);

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
		float phase_shift_distance = fmod(distance / wavelength, 1);
		float phase_shift_rad = phase_shift_distance * 2 * M_PI + antennas[i]->get_phase(el, az, frequency);

		float i_mag = cos(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);
		float q_mag = sin(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);

		i_sum += i_mag;
		q_sum += q_mag;
	}
	return sqrt(i_sum * i_sum + q_sum * q_sum);
}

float Array::sim_el_az2(float frequency, float el, float az)
{
	float wavelength = c0 / frequency;
	float radius = 2 * 1000 * wavelength * wavelength / wavelength;

	float y = radius * cos(el) * cos(az);
	float x = radius * sin(az) * cos(el);
	float z = radius * sin(el);

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
		float phase_shift_distance = fmod(distance / wavelength, 1);
		float phase_shift_rad = phase_shift_distance * 2 * M_PI + antennas[i]->get_phase(el, az, frequency);

		float i_mag = cos(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);
		float q_mag = sin(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);

		i_sum += i_mag;
		q_sum += q_mag;
	}
	return sqrt(i_sum * i_sum + q_sum * q_sum);
}

//right now assuming all antennas are less than 10 x the wavelength through free space
//coordinates are based off of this image https://mathinsight.org/media/image/image/spherical_coordinates_cartesian.png
std::vector<std::vector<float>> Array::simulate(float frequency, int el_count, int az_count, float az_start, float az_end, float el_start, float el_end)
{
	std::vector<std::vector<float>> results;
	//sweep across the sphere
	float wavelength = c0 / frequency;
	float quarter_wavelength = wavelength / 4;
	//2 * D^2 / lambda	an approximation of far field sphere
	float radius = 2 * 1000 * wavelength * wavelength / wavelength;//I know it's not simplified
	int pos = 0;
	float el_step = (el_end - el_start) / (el_count - 1);
	float az_step = (az_end - az_start) / (az_count - 1);
	for (int i = 0; i < el_count; i++)
	{
		float el = el_start + i * el_step;
		std::vector<float> el_line;
		for (float j = 0; j < az_count; j++)
		{
			float az = az_start + j * az_step;
			//z is up
			float y = radius * cos(el) * cos(az);
			float x = radius * sin(az) * cos(el);
			float z = radius * sin(el);

			//float u = cos(el) * sin(az);
			//float v = sin(el);
			//std::complex<float> af;

			//for (size_t i = 0; i < antennas.size(); i++)
			//{
			//	float a_x = std::get<0>(antenna_positions[i]);
			//	float a_y = std::get<1>(antenna_positions[i]);
			//	float a_z = std::get<2>(antenna_positions[i]);

			//	float a_el = 
			//}

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
				float phase_shift_distance = fmod(distance / wavelength, 1);
				float phase_shift_rad = phase_shift_distance * 2 * M_PI + antennas[i]->get_phase(el, az, frequency);

				float i_mag = cos(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);
				float q_mag = sin(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);

				i_sum += i_mag;
				q_sum += q_mag;
			}
			el_line.push_back(sqrt(i_sum * i_sum + q_sum * q_sum));
		}
		results.push_back(el_line);
	}



	return results;
}

std::vector<std::vector<std::vector<float>>> Array::simulate_sweep(float start_frequency, float stop_frequency, int freq_count, int el_count, int az_count, float az_start, float az_end, float el_start, float el_end)
{
	return std::vector<std::vector<std::vector<float>>>();
}
