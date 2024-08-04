#ifndef DISKDAO_H
#define DISKDAO_H
#include <fstream>
#include <sstream>

using namespace std;
namespace DiskAccess {
	class Utilities {
    	public :
    	[[nodiscard]] static string TryReadFileAsString(const string& filePath) {
	        ifstream file(filePath);
	        if (file.is_open()) {
	            stringstream buffer;
	            buffer << file.rdbuf();
	            return buffer.str();
	        }
	        throw runtime_error("Failed to open file: " + filePath);
	    }
	};  // DiskUtilities
}	// DiskAccess

#endif //DISKDAO_H
