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

using namespace matplot;

int main()
{
    double frequency = 2e9;//2 GHZ
    double wavelength = c0 / frequency;
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
    
    int size = 3;
    for (int z = -size; z < size; z++)
    {
        for (int x = -size; x < size; x++)
        {
            array.add_antenna(&a1, wavelength / 2 * x, 0, wavelength / 2 * z);
        }
    }


    const int el_count = 100, az_count = 100;
    auto results = array.simulate(frequency, el_count, az_count);
    
    auto [X, Y] = meshgrid(linspace(-M_PI_2, M_PI_2, el_count), linspace(-M_PI_2, M_PI_2, az_count));
    auto Z = transform(X, Y, [&](double el, double az) { return (array.sim_el_az(frequency, el, az)); });
    surf(X, Y, Z);
    xlabel("Elevation");
    ylabel("Azimuth");
    //zlabel("Linear Gain");
    show();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
