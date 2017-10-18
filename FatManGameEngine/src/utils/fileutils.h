#pragma once

#include <string>
namespace fatman {
	//Will be a function when using _ 
	std::string read_file(const char* filepath) {
		FILE* file = fopen(filepath, "rt");
		//below code comes from C libraries which is why acts as functional instead of oo, finds end of file then gets length afer being found
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		//The plus 1 at the end is a termination character to say the buffer has been fully read
		char* data = new char[length + 1];
		//Removes artifacts from the end of the file
		memset(data, 0, length + 1);
		//move back to begin of file
		fseek(file, 0, SEEK_SET);
		//Read close and retrieve
		fread(data, 1, length, file);
		fclose(file);
		std::string result(data);
		delete[] data;
		return result;
	}
}