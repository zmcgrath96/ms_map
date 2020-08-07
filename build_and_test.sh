# chmod u+x build_and_test.sh to make executable

# first make the src file
echo "Compiling source directory..."
cd src 
make clean 
make 
cd .. 
echo "Done"

# make and run tests
echo "Building tests..."
cd tests 
make clean
make 
echo "Done"
echo "Running tests..."
./testmain 