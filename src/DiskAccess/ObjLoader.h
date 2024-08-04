#ifndef OBJLOADER_H
#define OBJLOADER_H
#include "ObjParser.h"
#include "GeometryDao.h"
#include <memory>
#include <queue>

namespace DiskAccess {
    class ObjLoader {
    public:
        ObjLoader() = delete;
        explicit ObjLoader(const string& path) : _gDAO(Geometry::GeometryDao::getPtr()){
            if (path.ends_with(".obj")) {
                try {
                    _parser = make_unique<ObjParser>(path);
                } catch (runtime_error& e) {throw;}
            } else throw std::invalid_argument("File path must end with '.obj'");
            const vector<ObjParser::MeshDescription>_meshDescriptions = _parser->getAllMeshDescriptions();
            for(auto description : _meshDescriptions) {
                _meshIds.push(
                    _gDAO->reserveMesh(
                        description.vertexCount,
                        description.textCoordCount,
                        description.trianglesCount
                    )
                );
            }
        }

        bool load() {
            string instruction;
            bool firstMesh = true;
            while(!_parser->eof()) {
                _parser->getNextInstruction(instruction, _buffer.data());
                if (instruction == "o") {
                    if (firstMesh) firstMesh = false;   // avoid poping the first mesh instantly
                    else _meshIds.pop();
                    _resetCounters();
                } else if (instruction == "v") {
                    _loadVertex();
                } else if (instruction == "vn") {
                    _loadNormal();
                } else if (instruction == "vt") {
                    _loadUVCoordinates();
                } else if (instruction == "f") {
                    _loadTriangle();
                }
                //else nothing
            } // end while
            return true;
        }


    protected:
        unique_ptr<ObjParser> _parser;
        shared_ptr<Geometry::GeometryDao> _gDAO;
        array<string, 6> _buffer;
        unsigned short _currentVertex{}, _currentNormal{},
                       _currentTextureCoordinate{}, _currentColor{}, _currentTriangle{};
        queue<unsigned> _meshIds{};

        void _resetCounters() {
            _currentVertex = 0;
            _currentNormal = 0;
            _currentTextureCoordinate = 0;
            _currentColor = 0;
            _currentTriangle = 0;
        }

        void _loadVertex() {
            assert(!_buffer[0].empty());
            assert(!_buffer[1].empty());
            assert(!_buffer[2].empty());
            _gDAO->setVertex(_meshIds.front(), _currentVertex++,
                                     stof(_buffer[0]), stof(_buffer[1]), stof(_buffer[2]));
        }

        void _loadNormal() {
            assert(!_buffer[0].empty());
            assert(!_buffer[1].empty());
            assert(!_buffer[2].empty());
            _gDAO->setNormal(_meshIds.front(), _currentNormal++,
                        stof(_buffer[0]), stof(_buffer[1]), stof(_buffer[2]));
        }

        void _loadUVCoordinates() {
            assert(!_buffer[0].empty());
            assert(!_buffer[1].empty());
            _gDAO->setTextureCoordinates(_meshIds.front(), _currentTextureCoordinate++,
                                    stof(_buffer[0]), stof(_buffer[1]));
        }

        void _loadTriangle() {
            assert(!_buffer[0].empty());
            assert(!_buffer[1].empty());
            assert(!_buffer[2].empty());
            assert(!_buffer[3].empty());
            assert(!_buffer[4].empty());
            assert(!_buffer[5].empty());
            _gDAO->setTriangle(_meshIds.front(), _currentTriangle,
                                        stoul(_buffer[0]) - 1, stoul(_buffer[1]) - 1, stoul(_buffer[2]) - 1);   // obj index starts at 1. we use 0.
            _gDAO->setTriangleUVIds(_meshIds.front(), _currentTriangle,
                                    stoul(_buffer[3]) - 1, stoul(_buffer[4]) - 1, stoul(_buffer[5]) - 1);
            _currentTriangle++;
        }
    };

}// DiskAccess

#endif //OBJLOADER_H
