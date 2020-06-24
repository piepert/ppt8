#!/bin/bash

cd bin/
i586-pc-msdosdjgpp-g++ -O2 -Wall -I.. -c ../*/*.cpp
i586-pc-msdosdjgpp-g++ -O2 -Wall -I.. -c ../main.cpp
i586-pc-msdosdjgpp-g++ -O2 -Wall -I.. -o ppt8e.exe *.o