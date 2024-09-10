#include "pch.h"
#include "Camera.h"

namespace Deyo
{
	void Camera::SetPerspectiveSettings( float fov, float aspectRatio, float nearClip, float farClip )
	{
		m_FOV = fov;
		m_AspectRatio = aspectRatio;
		m_NearClip = nearClip;
		m_FarClip = farClip;

		m_IsProjectionDirty |= m_Mode == Mode::Perspective;
	}

	void Camera::SetOrthographicSettings( float left, float right, float bottom, float top )
	{
		m_Left = left;
		m_Right = right;
		m_Bottom = bottom;
		m_Top = top;

		m_IsProjectionDirty |= m_Mode == Mode::Orthographic;
	}

	void Camera::Update()
	{
		if ( m_IsProjectionDirty )
		{
			switch ( m_Mode )
			{
			case Mode::Perspective:
				DEYO_ASSERT( m_AspectRatio != 0, "Aspect ratio is not set" );
				DEYO_ASSERT( m_FOV > 0.0f && m_FOV < 180.0f, "FOV is out of range" );

				RecalculatePerspective();
				break;
			case Mode::Orthographic:
				RecalculateOrthographic();
				break;
			}

			m_IsProjectionDirty = false;
			m_IsViewDirty = false;
		}
		else if ( m_IsViewDirty )
		{
			RecalculateViewMatrix();
			m_IsViewDirty = false;
		}
	}

	void Camera::RecalculateViewMatrix()
	{
		Matrix4 transform = glm::translate( Matrix4( 1.0f ), m_Position ) * glm::toMat4( m_Rotation );
		m_View = glm::inverse( transform );
		m_ViewProjection = m_Projection * m_View;
	}

	void Camera::RecalculatePerspective()
	{
		m_Projection = glm::perspective( m_FOV, m_AspectRatio, m_NearClip, m_FarClip );
		m_ViewProjection = m_Projection * m_View;
		RecalculateViewMatrix();
	}

	void Camera::RecalculateOrthographic()
	{
		m_Projection = glm::ortho( m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f );
		m_ViewProjection = m_Projection * m_View;
		RecalculateViewMatrix();
	}
}