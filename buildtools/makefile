all: fluxer

fluxer.o:	fluxer.cpp mesher.hpp solver.hpp
	g++ fluxer.cpp -c -o fluxer.o

.cpp.o: 
	${CXX} ${CXXFLAGS} $^ -c -o $@

libmesher.a: mesher.o # ...
	ar cr $@ $^

libsolver.a: solver.o # ...
	ar cr $@ $^

fluxer: fluxer.o libmesher.a libsolver.a
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	rm -f fluxer *.o *.a *~

