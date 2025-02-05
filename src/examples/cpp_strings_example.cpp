// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <person.h>
#include <string>       //The C++ string class library


using namespace std;    //makes the std:: stuff optional

int main()
{
    /*
    int x = 42;
    float y = 3.14f;
    char name[32] = "Bob Jones";           //C-style
    const char* name2 = "Sally Smith";     //C-style (an unchangeable string literal)
    strcpy(name, "Robert Jones");          //Copy a new literal into name
    x = strlen(name);
    if (strlen(name, "mmmm") < 0)
        printf("name is alphabetically less than mmm\n");

    std::string cpp_name = "Bob Jones";    //internally the # of chars is still important
    cpp_name = "Robert Jones";             //no strcpy necessary
    if (cpp_name < "mmmm")
        std::cout << "cpp_name is alphabetically less than mmm\n";
    name2 = cpp_name.c_str();

    //Our goal with data structures will be to make constructs like this
    //that simplify the job of the user.

    cout << "x" << x << "Hello World!\n";*/

    //Some code that uses the Person class
    example::Person p(42, "Bob", "Jones");
    example::Person q(43, "Sally", "Smith");

    p.set_hourly_rate(15.0f);
    p.set_hours_worked(38);
    q.set_hourly_rate(16.75f);
    q.set_hours_worked(42);

    // We can also DYNAMICALLY allocate a person object
    example::Person* pptr = new example::Person(44, "Eric", "Davis");   //like mallac (new is preferred
                                                                // b/c it works with Classes
    pptr->set_hourly_rate(12.15f);
    pptr->set_hours_worked(23);
    (*pptr).set_hourly_rate(12.35f);                //Same as above line but uglier

    delete pptr;                                    // Like free -- frees up the memory
                                                    // pptr points to. The C++ runtime
                                                    // 
    pptr = NULL;        // NULL is just a macro for 0
    int y = NULL;       // valid but 



    std::cout << p.get_id() << " " << p.get_first_name() << "\n";

    // p and q were allocated on the STACK (an area of memory). STACK is 
    // where "temporary" variables (parameters in functions, p and q here.
    // HEAP memory is where dynamically allocated memory comes from. 
    // 
}