#pragma once

#include <Util/Common.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace blox
{
	class Math
	{
	public:
		static glm::mat4 OrthographicProjection(float left, float right, float bottom, float top, float near, float far)
		{
			return glm::ortho(left, right, bottom, top, near, far);
		}

		static glm::mat4 Create2DProjectionMatrix(float aspect)
		{
			glm::mat4 matrix(1.0f); // Initialize as an identity matrix
			matrix[0][0] = 1.0f / aspect; // Scale the X-axis based on the aspect ratio
			return matrix;
		}

		static float Min(float a, float b)
		{
			return a < b ? a : b;
		}

		static float Max(float a, float b)
		{
			return a > b ? a : b;
		}
	};
}