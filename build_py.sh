
# make this script executable with
# $> chmod u+x build_py.sh
# then run with ./build_py.sh
# build the cpp files
chmod u+x build_and_test.sh 
./build_and_test.sh 

# build the python distribution
echo "Compiling the cython wrapper and creating a distribution package..."
cd python_bindings
rm -rf build dist 
python3 setup.py build_ext --inplace
python3 setup.py sdist bdist_wheel 
echo "Done"