#include "CameraComponent.h"
#include "Core/Game/Components/TransformComponent.h"
#include "Core/Game/Entity.h"
#include "Core/Input/Event.h"

namespace Clone::Component
{
	Camera::Camera() : ComponentBase("Camera")
	{
		SetAttribute(Attribute::IsDirty, true);		
	}

	Camera::~Camera() = default;

	void Camera::Update(double deltaTime, const Input::Event& e)
	{
		if (GetAttribute(Attribute::IsDirty))
		{
			Transform* tf = Owner.lock()->GetComponent<Transform>();
			UpdateViewMatrix(tf);
			UpdateProjectionMatrix(tf);
		}
	}
	void Camera::SetFOV(const float& fov)
	{
		m_FOV = fov;
		SetAttribute(Attribute::IsDirty, true);
	}

	void Camera::SetNearPlane(const float& nearPlane)
	{
		m_NearPlane = nearPlane;
		SetAttribute(Attribute::IsDirty, true);
	}

	void Camera::SetFarPlane(const float& farPlane)
	{
		m_FarPlane = farPlane;
		SetAttribute(Attribute::IsDirty, true);
	}

	void Camera::SetProjection(const ProjectionType& type)
	{
		m_Projection = type;
		SetAttribute(Attribute::IsDirty, true);
	}

	void Camera::UpdateViewMatrix(const Component::Transform* transform)
	{
	}

	void Camera::UpdateProjectionMatrix(const Component::Transform* transform)
	{
	}
}