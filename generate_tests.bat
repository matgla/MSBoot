rmdir /Q /S bin_test
mkdir bin_test
cd bin_test
cmake .. -G"MinGW Makefiles" -DBUILD_TESTS=ON
cd ..