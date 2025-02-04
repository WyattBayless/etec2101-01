#include <iostream>
#include <string>
#include <fstream>				// Access to fstream, offstream, ifstream

#define MAIN_MODE 1				// 0=output, 1=input
#define FNAME "..\\..\\media\\test.txt"

int main(int argc, char** argv)
{
#if MAIN_MODE == 1
	//std::ofstream fout;
	//fout.open(*test.txt);

	int x = 52;
	float y = 4.15f;
	std::string s = "Hello World";
	//std::ofstream fout("test.txt");		// Have a connection to that file (makes
										// the file no matter what, or overwrites it)
	std::ofstream fout(FNAME);
	fout << x << ":" << y << ":" << s << "\n";
	x++;
	y++;
	s += "xxx";
	fout << x << ":" << y << ":" << s << "\n";

	fout.close();
#else
	//Alternate main program (for output)
	std::ifstream fin(FNAME);
	if (!fin.is_open())
	{
		std::cout << "Error opening file '" << FNAME << "'\n";
		return 1;
	}

	int x2;
	float y2;
	std::string s2;

	//This would have worked if we had white space
	//fin >> x2 >> y2 >> s2;
	while (!fin.eof())
	{
		// Note: the end of file (eof) function doesn't become true
		// until we try to read past the end of the file.
		fin >> x2;
		if (fin.eof())
			break;

		fin.ignore(1000, ':');
		fin >> y2;
		fin.ignore(1000, ':');
		//fin >> s2;
		std::getline(fin, s2);
	}

	std::cout << "Values read in: \n\tx2=" << x2 << "\n\ty2=" << y2 << "\n\ts2='" << s2 << "'\n";

#endif

	return 0;
}