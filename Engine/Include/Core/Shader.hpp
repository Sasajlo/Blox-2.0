#pragma once

#include <Util/Common.hpp>
#include <Util/Math.hpp>

namespace blox
{
	class Shader
	{
	private:
		uint programId;

	public:
		Shader();

		void Use();
		void SetInt(std::string name, int value);
		void SetBool(std::string name, bool value);
		void SetVector3(std::string name, Vec3 vector);
		void SetUniformMat4(std::string name, glm::mat4 matrix);

		static void Load(Shader* shader, const std::string vertexShaderPath, const std::string fragmentShaderPath);
	};
}