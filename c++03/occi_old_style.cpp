#include <iostream>
#include <string>
#include <occi.h>

using namespace std;            // import names (@\sref{sec:namespaces}@)
using namespace oracle::occi;

int main() 
{
    string dbConn= "172.17.42.1", user= "herbert", 
           password= "NSA_go_away";
    Environment *env = Environment::createEnvironment();
    Connection *conn = env->createConnection(user, password, 
                                             dbConn);
    string query= "select problem from my_solutions"
	          "  where award_worthy != 0";
    Statement *stmt = conn->createStatement(query);
    ResultSet *rs = stmt->executeQuery();

    while (rs->next()) 
	cout << rs->getString(1) << endl;

    stmt->closeResultSet(rs);
    conn->terminateStatement(stmt);
    env->terminateConnection(conn); 
    Environment::terminateEnvironment(env);
}

// Oracle queries
#if 0
create user herbert identified by NSA_go_away ;
grant create session, create table to herbert;
alter user herbert quota 10m on system;

create table my_solutions (
  problem varchar2(100),
  award_worthy number(1)
);

insert into my_solutions values ( 'Gauss circle', 1 );
insert into my_solutions values ( 'Congruent numbers', 0 );
insert into my_solutions values ( 'Amicable numbers', 1 );
#endif
