#pragma once
#include <fstream>
#include <string>
#include <random>

namespace example
{
	/// This class is meant to open a file when an instance of the class is created
	/// where the file is a text file containing multiple words, one per line.  This
	/// class instance will then extract one word at random when requested 
	class WordReader
	{
	private:
		/// <summary>
		/// This file handle will be connected to a file that is given to us in the constructor.
		/// The file will stay open until this instance's destructor is called
		/// </summary>
		std::ifstream mFileHandle;

		/// <summary>
		/// The length of the open file, in bytes
		/// </summary>
		int mFileLength;

		/// <summary>
		/// The random "device" used for RNG
		/// </summary>
		std::random_device mRandomDevice;

		/// <summary>
		/// The generator algorithm used for RNG
		/// </summary>
		/// <param name="dev"></param>
		/// <returns></returns>
		std::mt19937 mRandomAlgorithm;

		/// <summary>
		/// The distribution object used in RNG
		/// </summary>
		std::uniform_int_distribution<std::mt19937::result_type> mRandomDistribution;

	public:
		WordReader(std::string filename);
		~WordReader();
		bool is_open() const;
		std::string extract_word();
	};
}
