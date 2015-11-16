#include <iostream>
#include <string>

using namespace std;

class student 
{
  public:
    student(const string& name, const string& passed) 
      : name(name), passed(passed) {}
    virtual void all_info() const { 
	cout << "[student]  My name is " << name << endl; 
	cout << "    I passed the following grades: " << passed << endl;
    }
  private:
    string name, passed;
};

class mathematician
{
  public:
    mathematician(const string& name, const string& proved) 
      : name(name), proved(proved) {}
    virtual void all_info() const {
	cout << "[mathman]  My name is " << name << endl;
	cout << "    I proved: " << proved << endl;
    }
  private:
    string name, proved;
};

class math_student
  : public student, public mathematician
{
  public:
    math_student(const string& name, const string& passed, const string& proved)
      : student(name, passed), mathematician(name, proved) {}
};

int main () 
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.student::all_info();

    return 0 ;
}
