# Pico LED demo

See terminal output on linux computer: `minicom -b 115200 -o -D /dev/ttyACM0`

## Building first time preporations
```
mkdir build
cd build
export PICO_SDK_PATH=../../pico-sdk
cmake ..
```
## Building
```
cd build/project
make -j4
```
