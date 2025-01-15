#include "person.h"    //why "" instead of <>??

//We're providing the BODY / DEFINITION of the method we declared in our h file
float Person::calculate_wage()
{
	//In any (non-static) method, we have access to all atrributes for this
	//instance. Our job in this method is to tell the compiler HOW to 
	//calculate a wage using our attributes
	return hourly_rate * hours_worked;
}