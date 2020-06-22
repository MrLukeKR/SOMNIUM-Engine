#pragma once

#include <string>
#include <fstream>
#include <istream>
#include <vector>

#include "../Graphics/Mesh.h"
#include "../Graphics/Shaders/Shader.h"
#include "../Graphics/Buffers/VertexBuffer.h"
#include "../Graphics/Buffers/VertexArray.h"
#include "../Graphics/Buffers/IndexBuffer.h"

#ifdef _WIN32
	#define SSCANF sscanf_s
#else
	#define SSCANF sscanf
#endif

using namespace std;

/**
	SOMNIUM Engine, FileUtilities.h
	Description: Manages the I/O and parsing of various model files into meshes and their mappings

	@author Luke K. Rose
	@version 0.2 21/05/2018

*/

namespace Somnium
{
	namespace Utilities
	{
		namespace File
		{
			static string readFile(const char* filePath)
			{
				ifstream file(filePath, ios::binary);

				if(!file.is_open())
				{
					cerr << "Could not open file " << filePath << endl;
					return string("");
				}

				file.seekg(0, file.end);
				unsigned long length = static_cast<unsigned long>(file.tellg());
				file.seekg(0, file.beg);

				char *buffer = new char[length];

				file.read(buffer, length);

				file.close();

				string result(buffer, length);

				result.shrink_to_fit();

				delete[] buffer;

				return result;
			}

			static Graphics::Mesh loadOBJ(const char* filePath, Graphics::Shaders::Shader& shader)
			{
				ifstream file(filePath, ios::in);

				std::vector<Maths::Vector3> vertexPoints;
            	std::vector<Maths::Vector2> uvs;
            	std::vector<Maths::Vector3> normals;
				std::vector<Graphics::Texture> textures;

				std::vector<GLushort> vertexIndices;
				std::vector<GLushort> uvIndices;
				std::vector<GLushort> normalIndices;

				if (!file.is_open())
				{
					cerr << "Could not load OBJ file " << filePath << endl;
					//Return an empty Mesh object

					return Graphics::Mesh(new Graphics::Buffers::VertexArray, new Graphics::Buffers::IndexBuffer(nullptr, 0), textures, shader);
				}

				string line;
				string splitLine[5];

				while (getline(file, line))
				{
					size_t currPos = 0;

					//Determine what structure the current line represents (Vertex, Normal, Index, etc.)
					string header = line.substr(0, currPos = line.find(" "));
					string values = line.substr(currPos + 1, line.find("\n"));

					//If the structure is a Vertex...
					if (header == "v")
					{
						Maths::Vector3 newVert;

						SSCANF(line.c_str(),"v %f %f %f\n", &newVert.x, &newVert.y, &newVert.z);

						vertexPoints.push_back(newVert);
					}
					//If the structure is an Object Name...
					else if (header == "o")
					{
						cerr << "OBJECT NAMES NOT IMPLEMENTED YET!" << endl;
					}
					//If the structure is a Texture Coordinate...
					else if (header == "vt")
					{
                    	Maths::Vector2 uv;

						SSCANF(line.c_str(),"vt %f %f\n", &uv.x, &uv.y);

						uvs.push_back(uv);
					}
					//If the structure is a Normal...
					else if (header == "vn")
					{
                    	Maths::Vector3 normal;

						SSCANF(line.c_str(),"vn %f %f %f\n", &normal.x, &normal.y, &normal.z);

						normals.push_back(normal);
					}
					//If the structure is a Face...
					else if (header == "f")
					{
						unsigned int vertexIndex, texCoordIndex, normalIndex;
						size_t end = values.find("\n");
						string value;

						for(int ind = 0; ind < 3; ind++)
						{
							value = values.substr(0, values.find(' '));

							if (SSCANF(value.c_str(), "%d/%d/%d", &vertexIndex, &texCoordIndex, &normalIndex) != 3)
							{
								cerr << "Missing v/vt/vn value in OBJ file " << vertexIndex << "" << normalIndex << endl;
								break;
							}

							vertexIndices.push_back(vertexIndex);
							uvIndices.push_back(texCoordIndex);
							normalIndices.push_back(normalIndex);
							values = values.substr(values.find(' ') + 1, end); //TODO: This may be slightly/extremely inefficient; make it iterator based, not trim-reassignment based
						}
					}
					//If the structure is a Parameter Space Vertex...
					else if (header == "vp")
					{
						cerr << "PARAMETER SPACE VERTICES NOT IMPLEMENTED YET!" << endl;
					}
					//If the structure is a Line...
					else if (header == "l")
					{
						cerr << "LINES NOT IMPLEMENTED YET!" << endl;
					}
					//Ignore comments and check if the structure is unknown or invalid...
					else if (header != "#")
					{
						cerr << "UNKNOWN/INVALID STRUCTURE '" << header << "'!" << endl;
					}
				}

				file.close();

				for (unsigned long i = 0; i < vertexIndices.size(); i++) vertexIndices[i] -= 1;

				std::vector<GLfloat> vertexData = std::vector<GLfloat>();
				std::vector<GLfloat> normalData = std::vector<GLfloat>();
				std::vector<GLfloat> uvData = std::vector<GLfloat>();

				for (Maths::Vector3 point : vertexPoints)
				{
					vertexData.push_back(point.x);
					vertexData.push_back(point.y);
					vertexData.push_back(point.z);
				}

				for (Maths::Vector3 point : normals)
				{
					normalData.push_back(point.x);
					normalData.push_back(point.y);
					normalData.push_back(point.z);
				}

				for (Maths::Vector2 point : uvs)
				{
					uvData.push_back(point.x);
					uvData.push_back(point.y);
				}

				Graphics::Buffers::VertexBuffer* vbo = new Graphics::Buffers::VertexBuffer(vertexData, vertexPoints.size(), 3);
				Graphics::Buffers::VertexBuffer* nbo = new Graphics::Buffers::VertexBuffer(normalData, normals.size(), 3);
				Graphics::Buffers::VertexBuffer* uvbo = new Graphics::Buffers::VertexBuffer(uvData, uvs.size(), 2);

				Graphics::Buffers::VertexArray* vao = new Graphics::Buffers::VertexArray();
				Graphics::Buffers::IndexBuffer* ibo = new Graphics::Buffers::IndexBuffer(vertexIndices);

				vao->addBuffer(vbo, SHADER_POSITION_INDEX);
				vao->addBuffer(nbo, SHADER_NORMAL_INDEX);
				vao->addBuffer(uvbo, SHADER_TEXTURE_COORDINATE_INDEX);

				return Graphics::Mesh(vao, ibo, textures, shader);
			}
		}
	}
}
