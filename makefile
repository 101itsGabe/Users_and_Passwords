all: proj5.x sproj5.x

sproj5.x: sproj5.cpp passserver.cpp
	g++6 -lcrypt -o sproj5.x sproj5.cpp passserver.cpp

proj5.x: proj5.cpp passserver.cpp
	g++6 -lcrypt -o proj5.x proj5.cpp passserver.cpp

clean:
	rm *.0 proj5.x sproj5.x
