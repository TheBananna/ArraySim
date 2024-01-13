#need to import matplotlib
import matplotlib.pyplot as plt
import numpy as np

c0 = 299792458
#this will be a test simulation of a linear equispaced array
frequency = 2.e9
wavelength = c0 / frequency
spacing = wavelength / 2
AF = []