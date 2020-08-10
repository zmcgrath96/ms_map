from libcpp.vector cimport vector
from libcpp.string cimport string 

cdef extern from "../src/MSMap.hpp":
    cdef cppclass MSMap:
        MSMap() except +
        void insert(float, string) except *
        vector[string] search(float, int)