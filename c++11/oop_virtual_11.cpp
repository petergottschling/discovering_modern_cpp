#include <iostream>
#include <string>

using namespace std;

class person 
{
  public:
    person() = default;
    explicit person(const string& name) : name(name) {}

    void set_name(const string& n) { name= n; }
    string get_name() const { return name; }
    virtual void all_info() const { cout << "My name is " << name << endl; }
    
  private:
    string name;
};

class student 
  : public person
{
  public:
    student(const string& name, const string& passed) 
      : person(name), passed(passed) {}
    virtual void all_info() const override final { 
	person::all_info(); 
	cout << "I passed the following grades: " << passed << endl;
    }
  private:
    string passed;
};

class math_student 
  : public student
{
  public:
    virtual void all_info() const override {  }
};

void spy_on(const person& p)
{    p.all_info(); }

int main () 
{
    person mark("Mark Markson");
    mark.all_info();

    student tom("Tom Tomson", "Algebra, Analysis");
    tom.all_info();

    person  p(tom);
    person& pr= tom; // or pr(tom)
    person* pp= &tom; // or pp(&tom)

    p.all_info();
    pr.all_info();
    pp->all_info(); 

    spy_on(tom);

    return 0 ;
}
