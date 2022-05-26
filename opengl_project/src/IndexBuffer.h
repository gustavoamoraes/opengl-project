#pragma once

class IndexBuffer
{
	private:
		unsigned int m_RendererID;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
};