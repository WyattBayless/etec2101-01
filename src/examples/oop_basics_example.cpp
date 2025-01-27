#include <person.h>
#include <iostream>
using namespace std;
using namespace example;

int main(int argc, char** argv)
{
	example::Person p(42, "Bob", "Jones");
	example::Person q(43, "Sally", "Smith");
	example::Person r;							// <- Using the default consturctor

	p.set_hourly_rate(15.0f);
	p.set_hours_worked(38);
	q.set_hourly_rate(16.75f);
	q.set_hours_worked(42);

	// This is EXCEPTION HANDLING -- we see if an error happens, and if the
	// error does occur, we can run some other bit of code
	try
	{
		r.set_hourly_rate(-1.5f);
		r.set_hourly_rate(9999.99f);	// <- we never get here!
	}
	catch (std::out_of_range e)
	{
		// This code is run if a out_of_range error is triggered in that
		// code (it's not)
	}
	catch (std::runtime_error e)
	{
		// This code is run if a runtime error is triggered in that
		// code (it is)
		std::cout << "Sorry that was invalid\n\t";
		std::cout << e.what() << "\n";		// <- the string we passed when
						// we made the exception in set_hourly_rate
	}
	catch (int e)
	{
		// The 7 would go into this
	}
	catch (...)
	{
		// This is some other exception not handled
		std::cout << "some other error";
	}

	std::cout << p.get_id() << " " << p.get_first_name() << "\n";
}