#ifndef OBJPARSER_H
#define OBJPARSER_H
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
namespace DiskAccess {
    class ObjParser {
        // Assumption (performances) : lines are short, as is common in an obj file.
    public:
        ObjParser() = delete;
        explicit ObjParser(const string& filePath, const unsigned& chunkSize = 4096) : _chunkSize(chunkSize) {
            _file = ifstream(filePath);
            if (!_file.is_open()) {
                throw runtime_error("couldn't read file: " + filePath);
            }
            assert(_file.good());
            _createMeshDescriptions();
        }

        ~ObjParser() {
            if (_file.is_open()) {
            _file.close();
            }
        }

        bool eof() const {
            return _file.eof() && _bufferLineToReturn == _buffer.size();
        }

        void getNextInstruction(string& instructionOut, string contentOut[6]) {
            const string line = _getNextValidLine();
            istringstream iss(line);
            iss >> instructionOut;
            string token{};
            unsigned short i = 0;
            if (instructionOut == "f") {
                getline(iss, contentOut[0], '/'); // get the triangle vertex index before the first '/'
                getline(iss, contentOut[3], ' '); // get the texture coordinate index after the second '/'
                getline(iss, contentOut[1], '/');
                getline(iss, contentOut[4], ' ');
                getline(iss, contentOut[2], '/');
                getline(iss, contentOut[5], ' ');
            }
            else while (getline(iss, token, ' ')) {
                if (!token.empty()) {
                    assert(i < 6);
                    contentOut[i++] = token;
                }
            }
        }

        struct MeshDescription {
            unsigned int positionInFile{};
            unsigned short vertexCount{};
            unsigned short trianglesCount{};
            unsigned short materialsCount{};
            unsigned short textCoordCount{};
        };

        [[nodiscard]] const MeshDescription& getMeshDescription(const unsigned short& i) const {
            return _fileMeshesDescriptions[i];
        }
        [[nodiscard]] const vector<MeshDescription>& getAllMeshDescriptions() const {
            return _fileMeshesDescriptions;
        }

    #ifndef TEST_MODE
    protected:
    #endif
        vector<MeshDescription> _fileMeshesDescriptions;

        ifstream _file;
        const unsigned _chunkSize;
        vector<string> _buffer;
        unsigned short _bufferLineToReturn{};

        string _lastLine{};

        unsigned short _updateBuffer() {
            int lineCount = 0;
            char chunk[_chunkSize];
            _buffer.clear();
            _file.read(chunk, _chunkSize);
            if (_file.gcount() > 0) {
                std::stringstream ss(std::string(chunk, _file.gcount()));
                std::string line;
                std::getline(ss, line);
                ++lineCount;
                _buffer.push_back(_lastLine + line);
                while (std::getline(ss, line)) {
                    _buffer.push_back(line);
                    ++lineCount;
                }
                // handle data read ended in the middle of a line
                if((chunk[_chunkSize-1] != '\n') && _file.good()) {
                    _lastLine = _buffer[_buffer.size() - 1];
                    _buffer.pop_back();
                } else _lastLine = "";
            }
            return lineCount;
        }

        const string& _getNextValidLine() {
                // handle case : all lines returned from buffer
                if (_bufferLineToReturn >= _buffer.size()) {
                    _updateBuffer();
                    _bufferLineToReturn = 0;
                }
                // skip empty lines and comments
                if (_buffer[_bufferLineToReturn].empty() || (_buffer[_bufferLineToReturn][0] == '#')) {
                    _bufferLineToReturn++;
                    return _getNextValidLine();
                }
                return _buffer[_bufferLineToReturn++];
            }

        // counts meshes in the file, and for each their vertex and triangles counts.
        void _createMeshDescriptions () {
            unsigned int positionFromBeginning = 0;
            string lastChar;
            while(_updateBuffer()) {
                for(const string& line : _buffer) {
                    if (line.empty()) {
                        positionFromBeginning += 1; // +1 accounts for the newline character
                        continue;
                    }
                    istringstream iss(line);
                    iss >> lastChar;
                    if (lastChar == "o") {
                        _fileMeshesDescriptions.emplace_back();
                        _fileMeshesDescriptions[_fileMeshesDescriptions.size()-1].positionInFile = positionFromBeginning;
                    } else if (lastChar == "v") {
                        _fileMeshesDescriptions[_fileMeshesDescriptions.size()-1].vertexCount++;
                    } else if (lastChar == "vt") {
                        _fileMeshesDescriptions[_fileMeshesDescriptions.size()-1].textCoordCount++;
                    } else if (lastChar == "f") {
                        _fileMeshesDescriptions[_fileMeshesDescriptions.size()-1].trianglesCount++;
                    }
                    // else nothing
                    positionFromBeginning += line.length() + 1; // +1 accounts for the newline character
                } // end for
            }// end while
            _file.clear(); // reached end of file, need to clear state to come back to the beginning
            _file.seekg(0, std::ios::beg);
            assert(_file.good());
            assert(!_file.eof());
        }
    };// objparser

}// DiskAccess


#endif //OBJPARSER_H
