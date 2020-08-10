# distutils: language = c++
# distutils: sources = ../src/MSMap.cpp ../src/utils.cpp

from libcpp.string cimport string
from libcpp.vector cimport vector

from MSMap cimport MSMap 

cdef class PyMSMap:
    cdef MSMap * ms_map     # pointer to the cpp class instance

    def __cinit__(self):
        self.ms_map = new MSMap()

    def __dealloc__(self):
        del self.ms_map

    def insert(self, mass: float, sequence: str) -> None:
        '''
        Insert a mass and its associated sequence into the map

        Inputs:
            mass:       float   the mass of the amino acid sequence
            sequence:   str     the amino acid sequence
        Outputs:
            None
        '''
        cdef input_sequence = str.encode(sequence)
        self.ms_map.insert(mass, input_sequence)

    def search(self, mass: float, ppm_tol: int) -> list:
        '''
        Get all sequences that have a value mass +- the tolerance

        Inputs:
            mass:       float   the mass to search for
            ppm_tol:    int     the tolerance in parts per million to allow in the search
        Outputs:
            (list of strings) the sequences found with this mass range
        '''
        results = self.ms_map.search(mass, ppm_tol)
        return [result.decode() for result in results]