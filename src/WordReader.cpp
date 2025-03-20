#include <WordReader.h>

WordReader::WordReader()
{
	file_path_input = "???";
	throw std::runtime_error("No valid file path was given");
}

WordReader::~WordReader()
{
	fp.close();
}

WordReader::WordReader(std::string file_path) : file_path_input(file_path)
{
	srand(time(NULL));
	std::ifstream fp(file_path_input,std::ios::binary);
	fp.seekg(0, std::ios::end);
	file_len = fp.tellg();
	if (!fp.is_open())
		throw std::runtime_error("Could not open file.");
}

std::string WordReader::getWord()
{
	std::ifstream fp(file_path_input, std::ios::binary);
	int random_spot = rand() % (file_len - 1) + 1;
	fp.seekg(random_spot, std::ios::beg);
	char c = fp.peek();
	while (file_len > 0)
	{
		fp.seekg(-1, std::ios::cur);
		c = fp.peek();
		if (c == '\n')
		{
			fp.seekg(1, std::ios::cur);
			break;
		}
	}
	std::string read_word;
	std::getline(fp, read_word);
	return read_word;

}