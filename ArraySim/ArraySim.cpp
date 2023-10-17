// ArraySim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Array.h"
#include "Isotrope.h"
#include "Constants.h"
#include <string>



int main()
{
    float frequency = 2e9;//2 GHZ
    float wavelength = c0 / frequency;
    Array array;
    Isotrope a1;
    a1.set_phase(2.5);
    Isotrope a2;
    a2.set_phase(5);
    Isotrope a3;
    a3.set_phase(7.5);
    Isotrope a4;
    a4.set_phase(10);
    //array.add_antenna(&a1, -wavelength / 4, 0, -wavelength / 4);
    //array.add_antenna(&a1, -wavelength / 4, 0, wavelength / 4);
    //array.add_antenna(&a1, wavelength / 4, 0, -wavelength / 4);
    //array.add_antenna(&a1, wavelength / 4, 0, wavelength / 4);

    array.add_antenna(&a1, -3 * wavelength / 4, 0, 0);
    array.add_antenna(&a2, -wavelength / 4, 0, 0);
    array.add_antenna(&a3, wavelength / 4, 0, 0);
    array.add_antenna(&a4, 3 * wavelength / 4, 0, 0);



    auto results = array.simulate(frequency, 2, 60);
    for (float f : results[0])
    {
        std::cout << f << std::endl;
    }
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
