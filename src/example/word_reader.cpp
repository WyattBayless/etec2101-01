#include <word_reader.h>

example::WordReader::WordReader(std::string filename) : mFileHandle(filename, std::ios::binary), mRandomAlgorithm(mRandomDevice())
{
	if (mFileHandle.is_open())
	{
		mFileHandle.seekg(0, std::ios::end);
		mFileLength = static_cast<int>(mFileHandle.tellg());
	}
	else
		throw std::ios_base::failure("Could not open file '" + filename + "'");

	// Reference: https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
	mRandomDistribution = std::uniform_int_distribution<std::mt19937::result_type>(0, mFileLength - 1);
}



example::WordReader::~WordReader()
{
	mFileHandle.close();
}



bool example::WordReader::is_open() const
{
	return mFileHandle.is_open();
}




std::string example::WordReader::extract_word()
{
	// Get the initial position
	unsigned int long pos = mRandomDistribution(mRandomAlgorithm);
	mFileHandle.seekg(pos, std::ios::beg);

	// Now, step backwards, byte-by-byte, until we see a \n
	while (pos > 0 && mFileHandle.peek() != '\n')
	{
		mFileHandle.seekg(-1, std::ios::cur);
		pos--;
	}

	// We should either be at file position 0 or just *at* the newline (ie the start
	// of the next line).  If it's the former, we need to advance one to go to the byte
	// after the newline.  Then use getline to read that line and return it
	if (pos > 0)
	{
		mFileHandle.seekg(1, std::ios::cur);
		pos++;
	}
	std::string temp_string;
	//std::getline(mFileHandle, temp_string);
	mFileHandle >> temp_string;
	return temp_string;
}