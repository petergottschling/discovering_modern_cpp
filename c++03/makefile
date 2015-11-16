ALLEXE = 
#CXX= g++-4.4
#CXX= g++-4.8
#CXX= clang++-3.4
#CXX= mpiCC
CXXFLAGS+=  -I${BOOST_ROOT} 
CXXFLAGS+=  -I${MTL} 
CXXFLAGS+= -Wall -pedantic
#CXXFLAGS+= -w               # no warnings at all

CXXFLAGS+= -Wall -g -O0
#CXXFLAGS+= -Wall -O3 -DNDEBUG -ffast-math
CXXFLAGS+= -funroll-loops
#CXXFLAGS+= -L/usr/local/lib -lboost_mpi-gcc41-mt -lboost_serialization-gcc41-mt # for boost::mpi
#CXXFLAGS+= -L/home/pgottsch/projects/boost/boost_1_38_0/bin.v2/libs/mpi/build/gcc-4.3.3/release/link-static/threading-multi -lboost_mpi -L/home/pgottsch/projects/boost/boost_1_38_0/bin.v2/libs/serialization/build/gcc-4.3.3/release/link-static/threading-multi -lboost_serialization # for boost::mpi

# For OCCI example
# CXXFLAGS+=  -I/u01/app/oracle/product/11.2.0/xe/rdbms/public
# LOADLIBES+=   -L/u01/app/oracle/product/11.2.0/xe/lib/
# LOADLIBES+=   -locci -lclntsh
#### needs: # export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/u01/app/oracle/product/11.2.0/xe/lib

static_main:	static_main.cpp static_f.cpp
	g++ static_main.cpp static_f.cpp -o static_main

hello42:	hello42.cpp
	g++ hello42.cpp -o hello42 -static

