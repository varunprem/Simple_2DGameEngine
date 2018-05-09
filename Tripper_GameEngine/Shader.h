
#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <GL/glew.h>

class Shader {
public:

	GLuint Program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertexFile;
		std::ifstream fragmentFile;

		vertexFile.exceptions(std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::badbit);

		try {

			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vertexFile.rdbuf();
			fShaderStream << fragmentFile.rdbuf();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure e) {
			std::cout << "Error Shader File not successfully read" << std::endl;
		}

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		//Compile Shaders

		//VertexShader
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];

		//Compile vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "Unable to compile vertex Shader" << infoLog << std::endl;
		}


		//Compile fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "Unable to compile fragment Shader" << infoLog << std::endl;
		}

		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);

		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "The program was unable to Link" << infoLog <<std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void Use() {
		glUseProgram(this->Program);

		

	}
	

};

#endif
