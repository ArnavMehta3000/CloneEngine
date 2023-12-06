#include "Camera.h"
#include "Core/Game/Components/TransformComponent.h"
#include "Core/Game/Entity.h"
#include "Core/Input/Event.h"

namespace Clone::Game
{
	void Camera::CreatePerspective(unsigned int width, unsigned int height, float fov, float nearPlane, float farPlane)
	{
		m_Position         = Math::Vector3::Zero;
		m_Rotation         = Math::Vector3::Zero;
		m_FOV              = fov;
		m_Projection       = ProjectionType::Perspective;
		m_NearPlane        = nearPlane;
		m_FarPlane         = farPlane;
		m_width            = static_cast<float>(width);
		m_height           = static_cast<float>(height);
		m_ViewMatrix       = Math::Matrix::CreateFromYawPitchRoll(m_Position) * Math::Matrix::CreateTranslation(m_Rotation);
		m_ProjectionMatrix = DX::XMMatrixPerspectiveFovLH(fov, (float)width / (float)height, nearPlane, farPlane);
	}

	void Camera::CreateOrthographic(unsigned int width, unsigned int height, float nearPlane, float farPlane)
	{
		m_Position         = Math::Vector3::Zero;
		m_Rotation         = Math::Vector3::Zero;
		m_FOV              = -1.0f;
		m_Projection       = ProjectionType::Orthographic;
		m_NearPlane        = nearPlane;
		m_FarPlane         = farPlane;
		m_width            = static_cast<float>(width);
		m_height           = static_cast<float>(height);
		m_ViewMatrix       = Math::Matrix::CreateFromYawPitchRoll(m_Position) * Math::Matrix::CreateTranslation(m_Rotation);
		m_ProjectionMatrix = DX::XMMatrixOrthographicLH((float)width, (float)height, nearPlane, farPlane);
	}

	Camera& Camera::operator=(const Camera& other) = default;


	void Camera::Update()
	{
		// Update view an projection matrices if dirty
		if (m_isDirty)
		{
			// View matrix remains the same regardless of projection type
			m_ViewMatrix = Math::Matrix::CreateFromYawPitchRoll(m_Position) * Math::Matrix::CreateTranslation(m_Rotation);
			
			switch (m_Projection)
			{
			case Clone::Game::Camera::ProjectionType::Perspective:
				m_ProjectionMatrix = DX::XMMatrixPerspectiveFovLH(m_FOV, m_width / m_height, m_NearPlane, m_FarPlane);
				break;

			case Clone::Game::Camera::ProjectionType::Orthographic:
				m_ProjectionMatrix = DX::XMMatrixOrthographicLH(m_width, m_height, m_NearPlane, m_FarPlane);
				break;
			}

			m_isDirty = false;
		}
	}

	void Camera::SetPosition(const Math::Vector3& value)
	{
		m_Position = value;
		m_isDirty = true;
	}

	void Camera::SetRotation(const Math::Vector3& value)
	{
		m_Rotation = value;
		m_isDirty = true;
	}	

	void Camera::SetFOV(const float& value)
	{
		m_FOV = value;
		m_isDirty = true;
	}

	void Camera::SetNearPlane(const float& value)
	{
		m_NearPlane = value;
		m_isDirty = true;
	}

	void Camera::SetFarPlane(const float& value)
	{
		m_FarPlane = value;
		m_isDirty = true;
	}

	void Camera::SetProjection(const ProjectionType& value)
	{
		m_Projection = value;
		m_isDirty = true;
	}
}