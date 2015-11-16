template < typename Matrix, typename Vector,
	   typename Preconditioner >
int conjugate_gradient(const Matrix& A, Vector& x, const Vector& b, 
		       const Preconditioner& L, const double& eps)
{
    typedef typename Collection<Vector>::value_type Scalar;
    Scalar rho= 0, rho_1= 0, alpha= 0;
    Vector p(resource(x)), q(resource(x)), r(resource(x)), z(resource(x));
  
    r= b - A * x;
    int iter = 0 ;

    while (one_norm(size, r) >= eps) {
	prec( r, z );
	rho = dot(r, z);
    
	if (iter.first())
	    p = z;
	else 
	    p = z + (rho / rho_1) * p;      
	q= A * p;
	alpha = rho / dot(p, q);
      
	x += alpha * p;
	r -= alpha * q;
	rho_1 = rho;      
	++iter;
    }
    return iter;
}

int main (int argc, char* argv[]) 
{
    // initiate A, x and b
    conjugate_gradient(A, x, b, diag_prec, 1.e-5);    
    return 0 ;
}
