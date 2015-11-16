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
    
  private:
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
  private:
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
  private:
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
	mathematician::all_info();
	// person::all_info(); // cannot call member function ‘virtual void person::all_info() const’ without object
    }
};

int main () 
{
    math_student bob("Robert Robson", "Algebra", "Fermat's Last Theorem");
    bob.all_info();

    return 0 ;
}
