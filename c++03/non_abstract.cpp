#include <iostream>
#include <string>

using namespace std;

class person 
{
  public:
    person() /* : name() */ {} // automatisch generiert, wenn kein Ktor definiert ist
    explicit person(const string& name) : name(name) { /* this->name= name; */ }

    void set_name(const string& n) { name= n; }
    string get_name() const { return name; }
    void alle_infos() const { cout << "Mein Name ist " << name << endl; }
    
  private:
    string name;
};

class student : public person
{
  public:
    student(const string& name, const string& b) : person(name), bestandenes(b) {}
    void alle_infos() const { 
	cout << "Mein Name ist " << get_name() << endl; 
	cout << "Ich habe folgendes bestanden: " << bestandenes << endl;
    }

  private:
    string bestandenes;
};

int main (int argc, char* argv[]) 
{
    // person mark; // ruft Default-Konstruktor 
    // mark.set_name("Mark Markson");
    person mark("Mark Markson");
    // mark.alle_infos();

    student tom("Tom Tomson", "Algebra, Analysis");
    // tom.alle_infos();

    person  p(tom);
    person& pr= tom; // oder pr(tom)
    person* pp= &tom; // oder pp(&tom)

    p.alle_infos();
    pr.alle_infos();
    pp->alle_infos();            // (*pp).alle_infos();
    
    return 0 ;
}
