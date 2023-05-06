#include "pch.h"
#include "OpenGLShader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace Deyo
{
	namespace Utils
	{
		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex") return GL_VERTEX_SHADER;
			else if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

			DEYO_ASSERT(false, "Unknown shader type");
			return NULL;
		}

		static std::string ReadFile(const std::string& filepath)
		{
			std::ifstream file(filepath, std::ios::in | std::ios::binary);

			if (file)
			{
				std::string result;
				
				file.seekg(0, std::ios::end);
				long fileSize = file.tellg();
				file.seekg(0, std::ios::beg);
				result.resize(fileSize);

				file.read(&result[0], fileSize);

				return result;
			}
			else
			{
				DEYO_CORE_ERROR("Unable to read file {0}", filepath);
				return "";
			}
		}

		static std::map<GLenum, std::string> ParseShaderFile(const std::string& source)
		{
			std::map<GLenum, std::string> shadersSource;
			
			const char* typeKeyword = "#type";
			uint32_t typeKeywordLength = strlen(typeKeyword);
			size_t typeStart = source.find(typeKeyword);

			while (typeStart != std::string::npos)
			{
				size_t eol = source.find_first_of("\r\n", typeStart);
				DEYO_ASSERT(eol != std::string::npos, "Expected end of line");

				size_t typeNameBegin = typeStart + typeKeywordLength + 1;
				std::string typeName = source.substr(typeNameBegin, eol - typeNameBegin);
				GLenum shaderType = Utils::ShaderTypeFromString(typeName);

				// look for the next shader in file
				typeStart = source.find(typeKeyword, eol);
				
				shadersSource[shaderType] = typeStart == std::string::npos ?
					source.substr(eol)
					:
					source.substr(eol, typeStart - eol);
			}

			return shadersSource;
		}

		static GLuint GetCompiledShader(GLenum shaderType, const std::string& shaderSrc)
		{
			GLuint shaderId = glCreateShader(shaderType);

			if (shaderId == 0)
			{
				DEYO_CORE_ERROR("glCreateShader returned NULL");
				return 0;
			}

			const char* c_source = shaderSrc.c_str();
			glShaderSource(shaderId, 1, &c_source, nullptr);
			glCompileShader(shaderId);

			GLint compileSuccess = 0;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileSuccess);

			if (compileSuccess == GL_FALSE)
			{
				GLint logLength;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

				// the last character is \n, we don't want it to be in log
				GLchar* log = new GLchar[logLength - 1];
				glGetShaderInfoLog(shaderId, logLength - 1, nullptr, log);

				DEYO_CORE_ERROR("Unable to compile shader");
				DEYO_CORE_ERROR("Error: {0}", log);
				delete[] log;

				return 0;
			}

			return shaderId;
		}
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = Utils::ReadFile(filepath);
		auto shaderSources = Utils::ParseShaderFile(source);

		CreateProgram(shaderSources);

		// get shader name
		size_t fileNameStart = filepath.find_last_of("/\\");
		fileNameStart = fileNameStart == std::string::npos ? 0 : fileNameStart + 1;
		size_t dotPos = filepath.rfind('.', fileNameStart);
		m_Name = filepath.substr(fileNameStart, fileNameStart - dotPos);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc)
		: m_Name(name)
	{
		std::map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = pixelSrc;

		CreateProgram(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		Destroy();
	}

	void OpenGLShader::CreateProgram(const std::map<GLenum, std::string>& shaders)
	{
		m_ProgramId = glCreateProgram();

		for (auto& [type, src] : shaders)
		{
			GLuint shader = Utils::GetCompiledShader(type, src);

			if (shader == 0)
			{
				DEYO_CORE_ERROR("Failed to compile shader: {0}", src);
				Destroy();
				return;
			}
			else
			{
				glAttachShader(m_ProgramId, shader);
				m_ShaderIDs.push_back(shader);
			}
		}

		// validate our program
		glLinkProgram(m_ProgramId);
		glValidateProgram(m_ProgramId);
	}

	void OpenGLShader::Destroy()
	{
		glDeleteProgram(m_ProgramId);
		for (auto& id : m_ShaderIDs) glDeleteShader(id);
		m_ShaderIDs.clear();
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ProgramId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(NULL);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetVec2(const std::string& name, const Vector2& value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetVec3(const std::string& name, const Vector3& value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetVec4(const std::string& name, const Vector4& value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const Matrix3& value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const std::string& name, const Matrix4& value)
	{
		GLuint location = glGetUniformLocation(m_ProgramId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	const std::string& OpenGLShader::GetName() const
	{
		return m_Name;
	}
}
