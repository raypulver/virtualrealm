# virtualrealm

## build

Set `BOOST_ROOT` in `CMakeLists.txt` to wherever you have Boost installed. Make a build directory then run `cmake` to generate Makefile, then run `make`.

```
mkdir build
cd build
cmake ..
make
```


## test
Tests are built with the application. To run the tests, perform the same steps as above then run `make test`.

```
mkdir build
cd build
cmake ..
make
make test
```
