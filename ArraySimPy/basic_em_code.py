#=============================================
import constants
#---------------------------------------------------------------------------------------
#=======================================================================================
#                                       Class EM  
#=======================================================================================
#---------------------------------------------------------------------------------------
class EM():
    """Establishes the base electromagnetic problem"""



    #=============================================
    #=============================================
    def __init__(self):
        #-------------------------------------------

        #-------------------------------------------
        self.EM_data                        = {}
        self.EM_data["design_frequency"]    = -1.0
        self.EM_data["material_defined"]    = False

    def get_wavelength(self, **kwargs):
        f = kwargs.get('freq', 0.)
        eps_r = kwargs.get('eps_r', 1)
        mu_r = kwargs.get('mu_r', 1)
        if f > 0:
            wavelength = constants.EM_DATA['c0']/f/np.sqrt(eps_r)/np.sqrt(mu_r)
        else:
            wavelength = 1e16
        return 

    


if __name__ == "__main__":
    pass