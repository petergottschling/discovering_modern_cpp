#include <iostream>
#include <string>

using namespace std;

class creature
{
    virtual void all_info() const= 0;
};


class person 
  : public creature
{
  public:
    person() = default;
    explicit person(const string& name) : name(name) {}

    void set_name(const string& n) { name= n; }
    string get_name() const { return name; }
    virtual void all_info() const override 
    { cout << "My name is " << name << endl; }
    
  protected:
    string name;
};



int main () 
{
    // creature some_beast;   // Error: abstract class

    person mark("Mark Markson");
    mark.all_info();

    return 0 ;
}

