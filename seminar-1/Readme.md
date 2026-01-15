# Boykissers group
This repository is an official Boykissers-repo (Nikita Zhilin, Fedor Orlov, Daniil Podlyagin and Nikita Pichurin). 
![alt text](artifacts/Boykisser.png)

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