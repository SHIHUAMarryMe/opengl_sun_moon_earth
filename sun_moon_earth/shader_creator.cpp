
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_creator.h"

#include <iostream>


void ShaderCreator::createShadersAndLink(const std::string & vertexShaderSource, const std::string & fragmentShaderSource)
{
	vertex_shader_source_ = vertexShaderSource;
	fragment_shader_source_ = fragmentShaderSource;

	const char* const vertexShaderSourcePtr{ vertex_shader_source_.c_str() };
	const char* const fragmentShaderSourcePtr{ fragment_shader_source_.c_str() };

	int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSourcePtr, nullptr);
	glCompileShader(vertexShaderId);

	GLint success{};
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar infoLog[1024]{};
		glGetShaderInfoLog(vertexShaderId, 1024, nullptr, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}



	int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSourcePtr, nullptr);
	glCompileShader(fragmentShaderId);

	GLint success{};
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar infoLog[1024]{};
		glGetShaderInfoLog(fragmentShaderId, 1024, nullptr, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}


	GLuint programId{ glCreateProgram() };
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024]{};
		glGetProgramInfoLog(programId, 1024, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}


	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}
