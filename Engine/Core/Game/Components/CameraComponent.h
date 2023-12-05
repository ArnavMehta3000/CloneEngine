#pragma once
#include "Core/Game/Components/ComponentBase.h"
#include "Math/SimpleMath.h"

namespace Clone::Component
{
	class Transform;

	class Camera : public ComponentBase
	{
		enum class ProjectionType
		{
			Perspective,
			Orthographic
		};
	public:
		Camera();
		~Camera() override;
		void Update([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e) override;

		CLONE_PROPERTY(float, FOV);
		CLONE_PROPERTY(float, NearPlane);
		CLONE_PROPERTY(float, FarPlane);
		CLONE_PROPERTY(ProjectionType, Projection);
		CLONE_CONST_GET_ONLY_PROPERTY(float, AspectRatio);
		CLONE_CONST_GET_ONLY_PROPERTY(Math::Matrix, ViewMatrix);
		CLONE_CONST_GET_ONLY_PROPERTY(Math::Matrix, ProjectionMatrix);

	private:
		float m_orthoWidth;
		float m_orthoHeight;

		void UpdateViewMatrix(const Component::Transform* transform);
		void UpdateProjectionMatrix(const Component::Transform* transform);
	};
}