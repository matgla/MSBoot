rmdir /Q /S bin_test
mkdir bin_test
cd bin_test
cmake .. -G"Unix Makefiles" -DBUILD_TESTS=ON
cd ..