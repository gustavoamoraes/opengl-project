#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	const std::string vertexShader;
	const std::string fragmentShader;
};

class Shader
{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniforms4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformsMat4f(const std::string& name, const glm::mat4& mat);
		void SetUniforms1i(const std::string& name, int i0);

	private:
		unsigned int CompileShader(unsigned int type, const std::string& source) const;
		int GetUniformLocation(const std::string& name);
		ShaderProgramSource ParseShader(const std::string& dir) const;
};