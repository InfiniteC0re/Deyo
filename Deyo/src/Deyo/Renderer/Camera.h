#pragma once
#include "Deyo/Core/Core.h"

#include "Deyo/Math/Types.h"

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
		Camera( float aspectRatio = 16.0f / 9.0f )
		{
			SetPosition( Vector3( 0, 0, 0 ) );
			SetRotation( Vector3( 0, 0, 0 ) );
			SetPerspectiveSettings( 45.0f, aspectRatio, 0.1f, 200.0f );
			SetOrthographicSettings( -1.0f, 1.0f, -1.0f, 1.0f );
			SetCameraMode( Mode::Perspective );
			Update();
		}

		void SetPerspectiveSettings( float fov, float aspectRatio, float nearClip, float farClip );
		void SetOrthographicSettings( float left, float right, float bottom, float top );

		void Update();

		void SetCameraMode( Mode cameraMode )
		{
			if ( m_Mode != cameraMode )
			{
				m_Mode = cameraMode;
				m_IsProjectionDirty = true;
			}
		}

		void SetFOV( float fov )
		{
			if ( m_FOV != fov )
			{
				m_FOV = fov;
				m_IsProjectionDirty |= m_Mode == Mode::Perspective;
			}
		}

		void SetAspectRatio( float aspectRatio )
		{
			if ( m_AspectRatio != aspectRatio )
			{
				m_AspectRatio = aspectRatio;
				m_IsProjectionDirty |= m_Mode == Mode::Perspective;
			}
		}

		void SetNearClip( float nearClip )
		{
			if ( m_NearClip != nearClip )
			{
				m_NearClip = nearClip;
				m_IsProjectionDirty |= m_Mode == Mode::Perspective;
			}
		}

		void SetFarClip( float farClip )
		{
			if ( m_FarClip != farClip )
			{
				m_FarClip = farClip;
				m_IsProjectionDirty |= m_Mode == Mode::Perspective;
			}
		}

		void SetPosition( const Vector3& position )
		{
			if ( m_Position != position )
			{
				m_Position = position;
				m_IsViewDirty = true;
			}
		}

		void SetRotation( const Quaternion& rotation )
		{
			if ( m_Rotation != rotation )
			{
				m_Rotation = rotation;
				m_IsViewDirty = true;
			}
		}

		const Vector3& GetPosition() const
		{
			return m_Position;
		}

		const Quaternion& GetRotation() const
		{
			return m_Rotation;
		}

		const Matrix4& GetViewMatrix() const
		{
			return m_View;
		}

		const Matrix4& GetProjectionMatrix() const
		{
			return m_Projection;
		}

		const Matrix4& GetViewProjectionMatrix() const
		{
			return m_ViewProjection;
		}

	private:
		void RecalculateViewMatrix();
		void RecalculatePerspective();
		void RecalculateOrthographic();

	private:
		Mode m_Mode;
		Matrix4 m_View;
		Matrix4 m_Projection;
		Matrix4 m_ViewProjection;
		Vector3 m_Position;
		Quaternion m_Rotation;

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