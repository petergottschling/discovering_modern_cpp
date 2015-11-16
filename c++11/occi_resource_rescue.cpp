#include <iostream>
#include <string>
#include <memory>
#include <occi.h>

using namespace std;
using namespace oracle::occi;

struct environment_deleter {
    void operator()( Environment* env ) 
    { Environment::terminateEnvironment(env); }
};

struct connection_deleter
{
    connection_deleter(shared_ptr<Environment> env) 
      : env(env) {}
    void operator()(Connection* conn) 
    { env->terminateConnection(conn); }
    shared_ptr<Environment> env;
};

struct result_set_deleter
{
    result_set_deleter(shared_ptr<Connection> conn, 
		       Statement* stmt) 
      : conn(conn), stmt(stmt) {}
    void operator()( ResultSet *rs ) 
    {
        stmt->closeResultSet(rs);
        conn->terminateStatement(stmt);
    }
    shared_ptr<Connection> conn;
    Statement*             stmt;
};

class db_manager 
{
  public:
    using ResultSetSharedPtr= std::shared_ptr<ResultSet>;
    
    db_manager(string const& dbConnection, string const& dbUser,
	       string const& dbPw)
      : environment(Environment::createEnvironment(), 
		    environment_deleter{}),
	connection(environment->createConnection(dbUser, dbPw, 
						 dbConnection),
		   connection_deleter{environment} )
    {}

    shared_ptr<Environment> get_environment() 
    { return environment; }
    shared_ptr<Connection> get_connection() 
    { return connection; }
    
    ResultSetSharedPtr query(const std::string& q) const
    {
	Statement *stmt= connection->createStatement(q);
	ResultSet *rs = stmt->executeQuery();
	auto deleter= result_set_deleter{connection, stmt};
	return ResultSetSharedPtr{rs, deleter};
    }    
  private:
    shared_ptr<Environment> environment;
    shared_ptr<Connection> connection;
};


int main(int argc, char** argv) 
{
    db_manager db("172.17.42.1", "herbert", "NSA_go_away");
    auto rs= db.query("select problem from my_solutions "
		      "   where award_worthy != 0");
    while (rs->next()) 
	cout << rs->getString(1) << endl;
}



// Oracle queries, see c++03/occi_old_style.cpp
