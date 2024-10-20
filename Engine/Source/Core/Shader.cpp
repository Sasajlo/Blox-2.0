#include <Core/Shader.hpp>
#include <Util/File.hpp>

#include <glad/glad.h>

using namespace blox;

Shader::Shader()
{

}

void Shader::Use()
{
	glUseProgram(this->programId);
}

void Shader::SetInt(std::string name, int value)
{
	GLint location = glGetUniformLocation(this->programId, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetBool(std::string name, bool value)
{

}

void Shader::SetVector3(std::string name, Vec3 vector)
{
	GLint location = glGetUniformLocation(this->programId, name.c_str());
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::SetUniformMat4(std::string name, glm::mat4 matrix)
{
	GLint location = glGetUniformLocation(this->programId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Load(Shader* shader, const std::string vertexShaderPath, const std::string fragmentShaderPath)
{
	try {
		// Load files
		std::string vertexShaderRaw = File::ToString(vertexShaderPath);
		const char* vertexShaderSource = vertexShaderRaw.c_str();

		std::string fragmentShaderRaw = File::ToString(fragmentShaderPath);
		const char* fragmentShaderSource = fragmentShaderRaw.c_str();

		int success;
		char infoLog[512];

		// Create vertex shader
		uint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShaderId);
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
			throw std::runtime_error(std::string("[Error] Failed to compile vertex shader:\n") + infoLog);
		};

		// Create fragment shader
		uint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
			throw std::runtime_error(std::string("[Error] Failed to compile fragment shader:\n") + infoLog);
		};

		// Create shader program
		shader->programId = glCreateProgram();
		glAttachShader(shader->programId, vertexShaderId);
		glAttachShader(shader->programId, fragmentShaderId);
		glLinkProgram(shader->programId);
		glGetProgramiv(shader->programId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader->programId, 512, NULL, infoLog);
			throw std::runtime_error(std::string("[Error] Failed to link shader program:\n") + infoLog);
		}

		// Delete shaders
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
	}
	catch (const std::runtime_error& error)
	{
		std::cerr << error.what() << std::endl;
		throw std::runtime_error("[Error] Failed to create shader");
	}
}
