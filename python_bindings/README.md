# ms_map
A hash map used for the sole purpose of storing mass spectrometry data
## Background 
### What is mass spectrometry data
If you hadn't heard of mass spectrometry, I doubt you will get much out of this datastructure, but feel free to stick around and learn!

Mass spectrometry data is data that is generated from a mass spectrometer (duh). More specifically, this data structure is meant for identify peptides (short sequences of amino acids) from the list of numbers (floats) from a mass spectrometer run. Amino acids are described as a sequence masses.

The primary use of this data structure, to be even MORE specific, is by using singly and doubly charged masses to identify a peptide. The output, at its most basic form, is a list of floating point numbers. It might look something like the following

```
[99.023, 140.743, 209.887, 288.115, 402.778]
```

This sequence of floating point numbers describe a particular sequence of amino acids. The way this works is as follows:

Say our sequence of amino acids is: `MALW` (don't shoot me I know the masses don't make sense). The above sequence of amino acids describe any arrangement of ion types and charges. For the sake of this example, we will limit our scope to what're called `b` and `y` ions with possible charges of `1` and `2`. The `b` ions describe amino acids in a left-to-right fashion, and `y` right-to-left. So for our example sequence, we can break it down to something like:

```
  b1  b2  b3
M | A | L | W
  y3  y2  y1
```

So M is described by both a `b` ion and a `y` ion. The difference is that `b` is the mass of `M` and `y` is really the mass of `ALW`. But you can see how these ions complement eachother.

To dive a bit deeper, charges, as the name suggests, are the actual charges of the molecules and amino acid chains from the mass spectrometer. The most common of which are 1 and 2. So we could have up to (in this case) 4 different combinations of ions (b+, b++, y+, y++) that describe each junction.

## Hash map with ms data
If you don't know anything about the hash map data structure, look through [this](https://en.wikipedia.org/wiki/Hash_table) wikipedia page.

The hash map works as follows:
#### Insertions
A pair of a mass (a floating point number) and a sequence (string of amino acids) are added. 
```
insert(mass, spectrum)
```
The integer value of the mass is used as the key. Then the pair of the mass, sequence, is inserted into the list at the entry of the integer mass. 
```
input: 123.456, ABC
key: 123
inserting value: 123.456, ABC
```
Any value with the SAME mass is attached to the same mass value to avoid redunancy
```
table: {123: [(123.456, [ABC])]}
insert: 123.456, XYZ
table: {123: [(123.456, [ABC, XYZ])]}
```
Values that do NOT have the same mass are not inserted in the same spot
```
table: {123: [(123.456, [ABC, XYZ])]}
insert: 567.890, LMNOP
table: {123: [(123.456, [ABC, XYZ])], 567: [(567.890, [LMNOP])]}
```
#### Lookups
A lookup on the table is a lookup on masses, not sequences. Much like an insertion, the lookup starts with taking the integer value of a mass. This is used as the search key. 
```
search(mass, tolerance)
```
The tolerance parameter is used to determine how much leeway is allowed when searching for a mass. Once the key is extracted, we can look through a list for values that fall within the upper and lower bounds of the search mass.
```
search parameters: 123.455, 20
tolerance: 20 ppm of 123.455 -> 0.0025
upper bound: 123.455 + .0025 = 123.4575
lower bound: 123.455 - .0025 =  123.4525
key: 123

table entries at 123: [(123.456, [ABC, XYZ]), (123.999, [YYY])]
table entries at 123 with values between 123.4525 and 123.4575: [(123.456, [ABC, XYZ])]
```
Then the seqeunces of the values that fall within the mass range are returned
```
output: [ABC, XYZ]
```

## Installation
To install the python bindings as a package, run 
```bash
pip install ms_map
```

To install the source code, run 
```bash
git clone https://github.com/zmcgrath96/ms_map.git
```

To build the C++ code, run tests and build the python bindings, run
```bash
cd ms_map
$ms_map> chmod u+x build_py.sh
$ms_map> ./build_py.sh
```

## Example
```python
from ms_map import PyMSMap

if __name__ == '__main__':

    map = PyMSMap()

    mass = 316.308 
    sequence = "ZAM" 

    print("Adding mass with sequence to the map")
    map.insert(mass, sequence) 

    mass = 218.095 
    sequence = "PSM" 

    print("Adding a different mass with a different sequence to the map")
    map.insert(mass, sequence) 

    print("Searching for mass that we put in there")
    results = map.search(316.302, 20) 

    print("Results:")
    for result in results: 
        print(result)

```

## API
* __insert(mass: float, sequence: str) -> None__: insert a mass with a sequence into the table
* __search(mass: float, ppm_tol: int) -> list__: search for the mass with an upper and lower bound value calculated from the ppm tolerance parameter. Returns all sequences with a mass in this range.