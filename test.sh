cd bin_test
rm -rf test/UT/bootloaderUTs
make -j2
test/UT/bootloaderUTs
cd ..
cd test/ST
behave