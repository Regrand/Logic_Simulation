propagation: main_propagation.cpp
	g++ -std=c++11 main_propagation.cpp -o propagation

inertial: main_inertial.cpp
	g++ -std=c++11 main_inertial.cpp -o inertial

clean:
	rm -f *~ *.o propagation inertial
	

