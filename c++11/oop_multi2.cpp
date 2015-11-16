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
    virtual void all_info() const { cout << "[person]   My name is " << name << endl; }
    
  protected:
    string name;
};

class student 
  : public person
{
  public:
    student(const string& name, const string& passed) 
      : person(name), passed(passed) {}
    virtual void all_info() const override { 
	cout << "[student]  My name is " << get_name() << endl; 
	cout << "    I passed the following grades: " << passed << endl;
    }
  protected:
    string passed;
};

class mathematician
  : public person
{
  public:
    mathematician(const string& name, const string& proved) 
      : person(name), proved(proved) {}
    virtual void all_info() const override {
	person::all_info();
	cout << "    I proved: " << proved << endl;
    }
  protected:
    string proved;
};

class math_student
  : public student, public mathematician
{
  public:
    math_student(const string& name, const string& passed, const string& proved)
      : student(name, passed), mathematician(name, proved) {}
    virtual void all_info() const override {
	student::all_info();
	cout << "    I proved: " << proved << endl;
	// person::all_info();   // Error: ambiguous
    }
};

int main () 
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();

    math_student* bp= &bob;
    cout << hex 
	 << "bp           = " << bp 
	 << "\nmath         = " << static_cast<mathematician*>(bp) 
	 << "\nperson math  = " << static_cast<person*>(static_cast<mathematician*>(bp))
	 << "\nstudi        = " << static_cast<student*>(bp) 
	 << "\nperson studi = " << static_cast<person*>(static_cast<student*>(bp))
	// << "\nperson       = " << static_cast<person*>(bp)   // Error: ambiguous
	 << "\n";

    return 0;
}

