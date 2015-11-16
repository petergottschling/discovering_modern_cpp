#include <iostream>
#include <string>

using namespace std;

class person 
{
  public:
    person() {} // not implicitly generated
    explicit person(const string& name) : name(name) {}

    void set_name(const string& n) { name= n; }
    string get_name() const { return name; }
    void all_info() const { cout << "[person]   My name is " << name << endl; }
    
  private:
    string name;
};

class student 
  : public person
{
    using person::person;
};

void spy_on(const person& p)
{    p.all_info(); }

int main () 
{
    person mark("Mark Markson");
    mark.all_info();

    student tom("Tom Tomson");
    tom.all_info();

    return 0 ;
}
