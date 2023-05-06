#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

#include <Deyo/Core/Core.h>

namespace Deyo
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetVec2(const std::string& name, const Vector2& value) = 0;
		virtual void SetVec3(const std::string& name, const Vector3& value) = 0;
		virtual void SetVec4(const std::string& name, const Vector4& value) = 0;
		virtual void SetMat3(const std::string& name, const Matrix3& value) = 0;
		virtual void SetMat4(const std::string& name, const Matrix4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name) const;

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}