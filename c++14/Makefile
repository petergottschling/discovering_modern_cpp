
CXXFLAGS+=  -std=c++14
# CXXFLAGS+=  -I. 
# CXXFLAGS+=  -I${BOOST_ROOT} 
# CXXFLAGS+=  -I${HOME}/projects/boost/boost_1_53_0
# CXXFLAGS+=  -g # -Wno-long-double
CXXFLAGS+=  -I${MTL} -DMTL_WITH_INITLIST -DMTL_WITH_MOVE -DMTL_WITH_VARIADIC_TEMPLATE \
            -DMTL_WITH_STATICASSERT -DMTL_WITH_TEMPLATE_ALIAS -DMTL_WITH_DEFAULTIMPL \
            -DMTL_WITH_AUTO -DMTL_WITH_RANGEDFOR 




# CXX=        clang++
# CXX=        clang++-3.5
# CXX=	    g++-4.9
CXX=	    g++-5

%:	%.cpp
	clang++-3.5 ${CXXFLAGS} -o $@ $?
	@ $@
	${CXX} ${CXXFLAGS} -o $@ $?
