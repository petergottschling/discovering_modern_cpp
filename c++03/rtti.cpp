#include <iostream>
#include <typeinfo>
#include <stack>

using namespace std;

class figur {
  public:
    virtual ~figur() {}
};
class kreis : public figur {};
class viereck : public figur {};
class dreieck : public figur {};



int main(int argc, char** argv) 
{
    stack<figur*> s;

    for (int i= 0; i < 12; i++)
	switch(i % 3) {
	  case 0: s.push(new kreis); break;
	  case 1: s.push(new viereck); break;
	  case 2: s.push(new dreieck); break;
	}

    int nkreis= 0, nviereck= 0, ndreieck= 0;
    while (!s.empty()) {
	figur* f= s.top();
	cout << typeid(*f).name() << " erzeugt.\n";
#if 1
	if (dynamic_cast<kreis*>(f)) nkreis++; // kind of hack nevertheless
	if (dynamic_cast<viereck*>(f)) nviereck++;
	if (dynamic_cast<dreieck*>(f)) ndreieck++;
#else
	if (typeid(*f) == typeid(kreis)) nkreis++;
	if (typeid(*f) == typeid(viereck)) nviereck++;
	if (typeid(*f) == typeid(dreieck)) ndreieck++;
#endif
	s.pop();
    }
    cout << "Es wurden " << nkreis << " Kreise, " << nviereck << " Vierecke und " 
	 << ndreieck << " Dreiecke erzeugt.\n";

    return 0;
}
