cd bin_test
del test\UT\bootloaderUTs.exe
mingw32-make -j8
test\UT\bootloaderUTs
cd ..