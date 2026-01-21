## Build
````
cmake -S . -B build # only first time for configuration
cmake --build build # do this each time you need to build
````

## Run
````
./build/100_percentil
````

## Unit-Testing
````
cmake --build build --target run-tests
````