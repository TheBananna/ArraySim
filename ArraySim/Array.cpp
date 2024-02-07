#include "Array.h"
#include <iostream>
void Array::add_antenna(Antenna* antenna, double x, double y, double z)
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

double Array::sim_el_az(double frequency, double el, double az)
{
	double wavelength = c0 / frequency;
	//this technically only works if the spacing is less than sqrt(10) wavelengths I think. I should come up with something better than this.
	//It comes from assuming this is an endfire array, D will be ~spacing * antenna count. Far field ~= 2 * D^2 / wavelength = 2 * n^2 * wavelength where n is the spacing coefficient with spacing = n * wavelength
	double radius = 20 * antennas.size() * antennas.size() * wavelength; //conservative far field distance approximation

	//elevation and azimuth here are 0 normal to the xz plane or down boresight, I've verified this is correct
	double x = radius * sin(az) * cos(el);
	double y = radius * cos(el) * cos(az);
	double z = radius * sin(el);
	

	double i_sum = 0;
	double q_sum = 0;
	for (size_t i = 0; i < antennas.size(); i++)
	{
		double a_x = std::get<0>(antenna_positions[i]);
		double a_y = std::get<1>(antenna_positions[i]);
		double a_z = std::get<2>(antenna_positions[i]);

		double dx = x - a_x;
		double dy = y - a_y;
		double dz = z - a_z;
		double distance = sqrt(dx * dx + dy * dy + dz * dz);
		double phase_shift_rad = distance / wavelength * 2 * M_PI + antennas[i]->get_phase(el, az, frequency); //cosine repeats so no need to do % 1 of the division result

		double i_mag = cos(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);
		double q_mag = sin(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);

		i_sum += i_mag;
		q_sum += q_mag;
	}
	return sqrt(i_sum * i_sum + q_sum * q_sum);
}

//based off of https://mathinsight.org/distance_point_plane for plane math
//double Array::sim_el_az(double frequency, double el, double az)
//{
//	double wavelength = c0 / frequency;
//	double radius = 2000 * wavelength; //conservative far field distance approximation
//
//	//elevation and azimuth here are 0 normal to the xz plane or down boresight
//	double y = radius * cos(el) * cos(az);
//	double x = radius * cos(el) * sin(az);
//	double z = radius * sin(el);
//
//	//plane wave coefficients, no normalization as that doesn't affect direction or location
//	double A = x / radius;
//	double B = y / radius;
//	double C = z / radius;
//	double D = -A * x - B * y - C * z;
//
//
//	double i_sum = 0;
//	double q_sum = 0;
//	for (size_t i = 0; i < antennas.size(); i++)
//	{
//		double a_x = std::get<0>(antenna_positions[i]);
//		double a_y = std::get<1>(antenna_positions[i]);
//		double a_z = std::get<2>(antenna_positions[i]);
//
//		double dx = x - a_x;
//		double dy = y - a_y;
//		double dz = z - a_z;
//
//		double distance = std::abs(A * dx + B * dy + C * dz) / std::sqrt(A * A + B * B + C * C);//get the distance from the antenna to the far field plane, the plane maybe needs to be in the near field touching an element?
//		double phase_shift_rad = distance / wavelength * 2 * M_PI + antennas[i]->get_phase(el, az, frequency); //cosine repeats so no need to do % 1 of the division result
//
//		double i_mag = cos(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);
//		double q_mag = sin(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency);
//
//		i_sum += i_mag;
//		q_sum += q_mag;
//	}
//	return sqrt(i_sum * i_sum + q_sum * q_sum);
//}


double Array::sim_el_az2(double frequency, double el, double az, double spacing)
{
	std::complex<double> j(0, 1);
	double wavelength = c0 / frequency;
	double radius = 2 * 1000 * wavelength * wavelength / wavelength;

	double y = radius * cos(el) * cos(az);
	double x = radius * sin(az) * cos(el);
	double z = radius * sin(el);

	double y_n = cos(el) * cos(az);
	double x_n = sin(az) * cos(el);
	double z_n = sin(el);

	std::complex<double> sum;
	double ref = -M_PI_2;
	for (size_t i = 0; i < antennas.size(); i++)
	{
		double a_x = std::get<0>(antenna_positions[i]);
		double a_y = std::get<1>(antenna_positions[i]);
		double a_z = std::get<2>(antenna_positions[i]);

		double dx = x - a_x;
		double dy = y - a_y;
		double dz = z - a_z;
		double distance = sqrt(dx * dx + dy * dy + dz * dz);

		sum += std::exp(j * (x_n * dx / distance + y_n * dy / distance + z_n * dz / distance));
	}
	return std::abs(sum);
}

//right now assuming all antennas are less than 10 x the wavelength through free space
//coordinates are based off of this image https://mathinsight.org/media/image/image/spherical_coordinates_cartesian.png
std::vector<std::vector<double>> Array::simulate(double frequency, int el_count, int az_count, double az_start, double az_end, double el_start, double el_end)
{
	std::vector<std::vector<double>> results;
	//sweep across the sphere
	double wavelength = c0 / frequency;
	double quarter_wavelength = wavelength / 4;
	//2 * D^2 / lambda	an approximation of far field sphere
	double radius = 2 * 1000 * wavelength * wavelength / wavelength;//I know it's not simplified
	int pos = 0;
	double el_step = (el_end - el_start) / (el_count - 1);
	double az_step = (az_end - az_start) / (az_count - 1);
	for (int i = 0; i < el_count; i++)
	{
		double el = el_start + i * el_step;
		std::vector<double> el_line;
		for (double j = 0; j < az_count; j++)
		{
			double az = az_start + j * az_step;
			//z is up
			double y = radius * cos(el) * cos(az);
			double x = radius * sin(az) * cos(el);
			double z = radius * sin(el);

			//double u = cos(el) * sin(az);
			//double v = sin(el);
			//std::complex<double> af;

			//for (size_t i = 0; i < antennas.size(); i++)
			//{
			//	double a_x = std::get<0>(antenna_positions[i]);
			//	double a_y = std::get<1>(antenna_positions[i]);
			//	double a_z = std::get<2>(antenna_positions[i]);

			//	double a_el = 
			//}

			double i_sum = 0;
			double q_sum = 0;
			for (size_t i = 0; i < antennas.size(); i++)
			{
				double a_x = std::get<0>(antenna_positions[i]);
				double a_y = std::get<1>(antenna_positions[i]);
				double a_z = std::get<2>(antenna_positions[i]);

				double dx = x - a_x;
				double dy = y - a_y;
				double dz = z - a_z;
				double distance = sqrt(dx * dx + dy * dy + dz * dz);
				double phase_shift_distance = fmod(distance / wavelength, 1);
				double phase_shift_rad = phase_shift_distance * 2 * M_PI + antennas[i]->get_phase(el, az, frequency);

				double i_mag = cos(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency) / distance / distance / 4 / M_PI;
				double q_mag = sin(phase_shift_rad) * antennas[i]->get_gain(el, az, frequency) / distance / distance / 4 / M_PI;

				i_sum += i_mag;
				q_sum += q_mag;
			}
			el_line.push_back(sqrt(i_sum * i_sum + q_sum * q_sum));
		}
		results.push_back(el_line);
	}



	return results;
}

std::vector<std::vector<std::vector<double>>> Array::simulate_sweep(double start_frequency, double stop_frequency, int freq_count, int el_count, int az_count, double az_start, double az_end, double el_start, double el_end)
{
	return std::vector<std::vector<std::vector<double>>>();
}
