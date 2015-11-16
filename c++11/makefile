BUGGY  = 'variadic_sum_left' # separate by \|
ALLEXE = $(shell ls *.cpp | sed -e 's/\.cpp//'| grep -v ${BUGGY})


# optional flags
#CXXFLAGS+=  -I${BOOST_ROOT} 
#CXXFLAGS+= -Wall -pedantic -Wno-unused-variable
# CXXFLAGS+= -m32
 # CXXFLAGS+= -Wno-missing-braces # affects only clang++, ignored by g++
#CXXFLAGS+= -Wno-c++11-narrowing
CXXFLAGS+= -g -O0
#CXXFLAGS+= -O3 -DNDEBUG
#CXXFLAGS+= -ffast-math
#CXXFLAGS+= -funroll-loops
# CXXFLAGS+= -v # really verbose
#CXXFLAGS+= -I/home/pgottsch/projects/boost/boost_1_55_0
CXXFLAGS+= -I${MTL}
#CXXFLAGS+= -I/home/pgottsch/projects/mtl4-branches/pro
CXXFLAGS+= -DMTL_WITH_INITLIST -DMTL_WITH_AUTO -DMTL_WITH_RANGEDFOR -DMTL_WITH_VARIADIC_TEMPLATE
CXXFLAGS+= -DMTL_WITH_DEFAULTIMPL -DMTL_WITH_TEMPLATE_ALIAS -DMTL_WITH_STATICASSERT -DMTL_WITH_MOVE
#CXXFLAGS+= -Wno-unused-local-typedefs

# for the OCCI example
# CXXFLAGS+=  -I/u01/app/oracle/product/11.2.0/xe/rdbms/public
# LOADLIBES+=   -L/u01/app/oracle/product/11.2.0/xe/lib/
# LOADLIBES+=   -locci -lclntsh -lnnz11
#### needs: # export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/u01/app/oracle/product/11.2.0/xe/lib

# turn on C++11
# CXXFLAGS+= -std=c++14 # for quick experiments
CXXFLAGS+= -std=c++11
# CXXFLAGS+= -std=c++0x

# library must be indicated  with clang <= 3.2
# CXXFLAGS+= -stdlib=libc++

#CXX= g++-4.8
CXX= g++-4.9
#CXX= g++-5
#CXX= clang++-3.4

%:	%.cpp
	clang++-3.5 ${CXXFLAGS} -o $@ $? ${LOADLIBES}
	@ $@
	${CXX} ${CXXFLAGS} -o $@ $? ${LOADLIBES} # -Wno-unused-but-set-variable

# additional flags for binary installation of clang 3.3, shouldn't be needed :-!
# CXXFLAGS+= -I/usr/local/clang+llvm-3.3/lib/c++/v1 
# LDFLAGS+= -nodefaultlibs -lstdc++ -lm -lc -lgcc_s -lgcc

# For SDL 1.2
SDL_FLAGS= -D_GNU_SOURCE=1 -D_REENTRANT -lSDL 
MTL_FLAGS= -I${MTL}

default: ${ALLEXE}
	 echo "${BUGGY} -- ${ALLEXE}"

clean:
	rm -rf ${ALLEXE}

instance1:	instance1.cpp instance2.cpp
	clang++-3.4 ${CXXFLAGS} -o $@ $? 

mandelbrot:	mandelbrot.cpp
	${CXX} -O3 -DNDEBUG -std=c++11 -o $@ $? ${SDL_FLAGS}

julia:	julia.cpp
	${CXX} -O3 -DNDEBUG -std=c++11 -o $@ $? ${SDL_FLAGS}

random_timing:	random_timing.cpp
	${CXX} -O3 -DNDEBUG -std=c++11 -o $@ $? 

mangling_example: mangling_example.cpp dings.o
	${CXX} -o $@ $?

multiref_example: multiref1.cpp multiref2.cpp multiref.hpp
	${CXX} -o $@ multiref1.cpp multiref2.cpp

# fibonacci:        fibonacci.cpp
# 	g++-5 -std=c++0x -o $@ $?
