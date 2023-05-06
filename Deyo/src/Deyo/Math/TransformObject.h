#pragma once
#include "Deyo/Math/Types.h"

#include <glm/gtx/quaternion.hpp>

namespace Deyo
{
	class TransformObject
	{
	public:
		TransformObject(
			const Vector3& position = Vector3(0.0f, 0.0f, 0.0f),
			const Quaternion& rotation = Vector3(0.0f, 0.0f, 0.0f),
			const Vector3& scale    = Vector3(1.0f, 1.0f, 1.0f)
		) : m_Position(position),
			m_Rotation(rotation),
			m_Scale(scale)
		{
			Recalculate();
		}

		void Recalculate()
		{
			m_ModelMatrix =
				glm::translate(Matrix4(1.0f), m_Position) *
				glm::toMat4(m_Rotation) *
				glm::scale(Matrix4(1.0f), m_Scale);
		}

		void Set(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
		{
			m_Position = position;
			m_Rotation = rotation;
			m_Scale = scale;
			Recalculate();
		}

		void SetPosition(const Vector3& position)
		{
			m_Position = position;
			Recalculate();
		}

		void SetRotation(const Quaternion& rotation)
		{
			m_Rotation = rotation;
			Recalculate();
		}

		void SetScale(float uniformScale)
		{
			m_Scale = { uniformScale, uniformScale, uniformScale };
			Recalculate();
		}

		void SetScale(const Vector3& scale)
		{
			m_Scale = scale;
			Recalculate();
		}

		Vector3& GetPosition()
		{
			return m_Position;
		}

		Quaternion& GetRotation()
		{
			return m_Rotation;
		}

		Vector3& GetScale()
		{
			return m_Scale;
		}

		const Matrix4& GetModelMatrix() const
		{
			return m_ModelMatrix;
		}

	private:
		Vector3 m_Position;
		Quaternion m_Rotation;
		Vector3 m_Scale;
		Matrix4 m_ModelMatrix;
	};
}