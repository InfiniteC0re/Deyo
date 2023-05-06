#pragma once
#include "Deyo/Core/Core.h"

#include <glm/matrix.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Deyo
{
	class Camera
	{
	public:
		enum class Mode
		{
			Perspective, Orthographic
		};

	public:
		Camera(float aspectRatio = 16.0f / 9.0f)
		{
			SetPosition(glm::vec3(0, 0, 0));
			SetRotation(glm::vec3(0, 0, 0));
			SetPerspectiveSettings(45.0f, aspectRatio, 0.1f, 200.0f);
			SetOrthographicSettings(-1.0f, 1.0f, -1.0f, 1.0f);
			SetCameraMode(Mode::Perspective);
			Update();
		}

		void SetPerspectiveSettings(float fov, float aspectRatio, float nearClip, float farClip);
		void SetOrthographicSettings(float left, float right, float bottom, float top);

		void Update();

		void SetCameraMode(Mode cameraMode)
		{
			if (m_Mode != cameraMode)
			{
				m_Mode = cameraMode;
				m_IsProjectionDirty = true;
			}
		}

		void SetFOV(float fov)
		{
			m_FOV = fov;
			m_IsProjectionDirty |= m_Mode == Mode::Perspective;
		}

		void SetAspectRatio(float aspectRatio)
		{
			m_AspectRatio = aspectRatio;
			m_IsProjectionDirty |= m_Mode == Mode::Perspective;
		}

		void SetNearClip(float nearClip)
		{
			m_NearClip = nearClip;
			m_IsProjectionDirty |= m_Mode == Mode::Perspective;
		}

		void SetFarClip(float farClip)
		{
			m_FarClip = farClip;
			m_IsProjectionDirty |= m_Mode == Mode::Perspective;
		}

		void SetPosition(const glm::vec3& position)
		{
			bool changed = m_Position != position;
			m_Position = position;
			m_IsViewDirty = changed;
		}

		void SetRotation(const glm::quat& rotation)
		{
			bool changed = m_Rotation != rotation;
			m_Rotation = rotation;
			m_IsViewDirty = changed;
		}

		const glm::vec3& GetPosition() const
		{
			return m_Position;
		}

		const glm::quat& GetRotation() const
		{
			return m_Rotation;
		}

		const glm::mat4& GetViewMatrix() const
		{
			return m_View;
		}

		const glm::mat4& GetProjectionMatrix() const
		{
			return m_Projection;
		}

		const glm::mat4& GetViewProjectionMatrix() const
		{
			return m_ViewProjection;
		}

	private:
		void RecalculateViewMatrix();
		void RecalculatePerspective();
		void RecalculateOrthographic();

	private:
		Mode m_Mode;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		glm::mat4 m_ViewProjection;
		glm::vec3 m_Position;
		glm::quat m_Rotation;
		
		// Perspective camera
		float m_FOV;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;

		// Ortographic camera
		float m_Left;
		float m_Right;
		float m_Bottom;
		float m_Top;

		// Current state
		bool m_IsProjectionDirty : 1;
		bool m_IsViewDirty : 1;
	};
}