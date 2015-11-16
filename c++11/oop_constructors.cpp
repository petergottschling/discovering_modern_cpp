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
    void all_info() const { cout << "My name is " << name << endl; }
    
  private:
    string name;
};

class student 
  : public person
{
  public:
    student() = default;
    student(const string& name, const string& passed) 
      : person(name), passed(passed) {}
    void all_info() const { 
	cout << "My name is " << get_name() << endl; 
	cout << "I passed the following grades: " << passed << endl;
    }
  private:
    string passed;
};

class physics_student
  : public student
{
  public:
    physics_student(const string& name, const string& passed) 
      : student(name, passed) {}
};

// class physics_student
//   : public student
// {
//     using student::student;
// };


int main () 
{
    physics_student rick("Rick Rickby", "Mechanics, Experimental");
    rick.all_info();

    return 0 ;
}
