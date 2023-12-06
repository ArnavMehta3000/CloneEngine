#pragma once
#include "Common/Includes.h"
#include "Math/SimpleMath.h"

namespace Clone::Game
{

	class Camera
	{
		enum class ProjectionType
		{
			Perspective,
			Orthographic
		};
	public:
		void CreatePerspective(unsigned int width, unsigned int height, float fov, float nearPlane = 0.1f, float farPlane = 100.0f);
		void CreateOrthographic(unsigned int width, unsigned int height, float nearPlane = 0.1f, float farPlane = 100.0f);


		Camera() {}
		Camera(float fov, ProjectionType type, float nearPlane = 0.1f, float farPlane = 100.0f);
		~Camera() = default;
		Camera& operator=(const Camera& other);

		void Update();

		CLONE_PROPERTY(Math::Vector3, Position);
		CLONE_PROPERTY(Math::Vector3, Rotation);
		CLONE_CONST_GET_ONLY_PROPERTY(Math::Matrix, ViewMatrix);
		CLONE_CONST_GET_ONLY_PROPERTY(Math::Matrix, ProjectionMatrix);
		CLONE_PROPERTY(float, FOV) { 45.0f };
		CLONE_PROPERTY(float, NearPlane) { 0.1f };
		CLONE_PROPERTY(float, FarPlane) { 100.0f };
		CLONE_PROPERTY(ProjectionType, Projection);

	private:
		float m_isDirty{ true };
		float m_width{ 0.0f };
		float m_height{ 0.0f };
	};
}