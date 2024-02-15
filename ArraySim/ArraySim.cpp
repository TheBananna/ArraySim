// ArraySim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Array.h"
#include "Isotrope.h"
#include "Constants.h"
#include <string>
#include <matplot/matplot.h>
#include <cmath>
#include "ArrayUtil.h"

using namespace matplot;

int main()
{
    double frequency = 2e9;//2 GHZ
    double wavelength = c_0 / frequency;
    Array array;
    Isotrope a1;
    a1.set_phase(0);
    Isotrope a2;
    a2.set_phase(0);
    Isotrope a3;
    a3.set_phase(0);
    Isotrope a4;
    a4.set_phase(0);
    //array.add_antenna(&a1, -wavelength / 4, 0, -wavelength / 4);
    //array.add_antenna(&a1, -wavelength / 4, 0, wavelength / 4);
    //array.add_antenna(&a1, wavelength / 4, 0, -wavelength / 4);
    //array.add_antenna(&a1, wavelength / 4, 0, wavelength / 4);

    //array.add_antenna(&a1, -3 * wavelength / 4, 0, 0);
    //array.add_antenna(&a2, -wavelength / 4, 0, 0);
    //array.add_antenna(&a3, wavelength / 4, 0, 0);
    //array.add_antenna(&a4, 3 * wavelength / 4, 0, 0);
    
    int size = 8;
    ////for odd numbers of elements
    //for (int z = -size; z <= size; z++)
    //{
    //    
    //    for (int x = -size; x <= size; x++)
    //    {
    //        //isotrope* a = new isotrope();
    //        //a->set_phase(m_pi_4 * x);
    //        array.add_antenna(&a1, wavelength / 2 * x, 0, wavelength / 2 * z);
    //    }
    //}
    //for even numbers of elements

    add_equitri_array(&array, { 0,0,0 }, { 0,0,0 }, { 2,2 }, 1);
    return 0;

    for (int z = 0; z < size * 2; z++)
    {
        //array.add_antenna(&a1, 0, 0, -wavelength / 4 - wavelength / 2 * (size - 1) + wavelength / 2 * z);
        for (int x = 0; x < size * 2; x++)
        {
            array.add_antenna(&a1, { -wavelength / 1 - wavelength * 2 * (size - 1) + wavelength * 2 * x, 0, -wavelength / 1 - wavelength * 2 * (size - 1) + wavelength * 2 * z });
        }
    }


    const int el_count = 150, az_count = 150;
    //auto results = array.simulate(frequency, el_count, az_count);
    
    auto [X, Y] = meshgrid(linspace(-M_PI / 3, M_PI / 3, el_count), linspace(-M_PI / 3, M_PI / 3, az_count));
    vector_2d Z = transform(X, Y, [&](double az, double el) { return 20 * log10(array.sim_el_az(frequency, el, az)); });
    surf(X, Y, Z);
    //xlabel("Elevation");
    //ylabel("Azimuth");
    //zlabel("Linear Gain");
    show();
}