# Pico LED demo

My first c project with rasberry pi pico. Show a pattern on 8 leds, change pattern with button. 

See terminal output on linux computer: `minicom -b 115200 -o -D /dev/ttyACM0`

## Building first time preporations
Make sure the pico-sdk is located next to this repository, then change to this
repository.
```
mkdir build
cd build
export PICO_SDK_PATH=../../pico-sdk
cmake ..
```
## Building
```
cd build/code
make -j4
```
