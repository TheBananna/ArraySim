#pragma once
#include "Array.h"
#include "Antenna.h"
#include "Constants.h"
#include "Types.h"
#include "Eigen/Dense"

//Adds a equalateral triangle spacing planar array to an array
//dims is the dimension of the longest edges
//dir is yaw, pitch, roll; standard Tait-Bryan angles


void add_equitri_array(Array* arr, vec3d center, vec3d dir, vec2i dims, double spacing)
{
	//yaw, pitch, roll
	double c1 = cos(dir(0)), c2 = cos(dir(1)), c3 = cos(dir(2));
	double s1 = sin(dir(0)), s2 = sin(dir(1)), s3 = sin(dir(2));
	//zyx / yaw, pitch, roll rotation 
	/*Eigen::Matrix<double, 3, 3> rot_mat;
	rot_mat(0, 0) = c1 * c2;
	rot_mat(1, 0) = c1 * s2 * s3 - c3 * s1;
	rot_mat(2, 0) = s1 * s3 + c1 * c3 * s2;
	rot_mat(0, 1) = c2 * s1;
	rot_mat(1, 1) = c1 * c3 + s1 * s2 * s3;
	rot_mat(2, 1) = c3 * s1 * s2 - c1 * s3;
	rot_mat(0, 2) = -s2;
	rot_mat(1, 2) = c2 * s3;
	rot_mat(2, 2) = c2 * c3;*/
	//accounts for even numbers of elements requiring a spacing / 2 offest
	double offsetx = (dims(0) % 2 - 1) * spacing / 2, offsety = (dims(1) & 2 - 1) * spacing / 2;
	int row = 0;
	//goes left to right top to bottom
	for (double y = spacing * (dims(0) - 1) / 2.; y >= -spacing * (dims(1) - 1) / 2.; y -= spacing)
	{
		for (double x = -spacing * (dims(1) - 1 - row % 2) / 2.; x < spacing * (dims(1) - 1 - row % 2) / 2.; x++)
		{
			std::cout << x << " ";
		}
		row++;
		std::cout << std::endl;
	}
}

//Adds a rectangular array to an array
void add_equirec_array(Array* arr, vec3d center, vec3d dir, vec2i dims, double spacing);

//These are circularly bound equalateral triangle and rectangular arrays
void add_equitri_circ_array(Array* arr, vec3d center, vec3d dir, int diameter, double spacing);
void add_equirec_circ_array(Array* arr, vec3d center, vec3d dir, int diameter, double spacing);


void save_array(Array* arr, std::string path);
Array* load_array(std::string path);
Array* concat_arrays(Array* arr1, Array* arr2);