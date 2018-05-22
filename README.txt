Required libraries:
1. Boost

Build all files:
mkdir cmake-build-release && cd cmake-build-release && cmake ../ -DCMAKE_BUILD_TYPE=Release && make

Run server (inside 'cmake-build-release' folder):
./shellserver <port>

Run user (inside 'cmake-build-release' folder):
./shelluser <host> <port>

Rebuild (inside 'cmake-build-release' folder):
make clean && make

Developed by:
Vasyl Borsuk, Marian Petruk, Anton Borkivskyi
