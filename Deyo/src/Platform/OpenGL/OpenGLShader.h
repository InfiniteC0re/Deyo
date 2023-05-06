#pragma once
#include <Deyo/Renderer/Shader.h>
#include <map>

namespace Deyo
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc);
		~OpenGLShader();

		void CreateProgram(const std::map<GLenum, std::string>& shaders);
		void Destroy();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetVec2(const std::string& name, const Vector2& value) override;
		virtual void SetVec3(const std::string& name, const Vector3& value) override;
		virtual void SetVec4(const std::string& name, const Vector4& value) override;
		virtual void SetMat3(const std::string& name, const Matrix3& value) override;
		virtual void SetMat4(const std::string& name, const Matrix4& value) override;

		virtual const std::string& GetName() const override;

	private:
		std::string m_Name;
		std::vector<GLuint> m_ShaderIDs;
		GLuint m_ProgramId;
	};
}