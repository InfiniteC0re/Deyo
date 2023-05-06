#pragma once
#include "Deyo/FileSystem/File.h"

namespace Deyo
{
	class WindowsFile : public File
	{
	public:
		static constexpr size_t READ_BUFFER_SIZE = 2048;

	public:
		WindowsFile(FileSystem* pFileSystem) : File(pFileSystem) { Reset(); }

		~WindowsFile() { DestroyBuffer(); }

		virtual bool Open(const std::wstring filepath, CreateFlags flags) override;
		virtual void Close() override;
		virtual size_t Read(LPVOID dst, size_t size) override;
		virtual size_t Write(LPVOID src, size_t size) override;
		virtual bool Seek(SeekMode seekMode, size_t pos) override;
		virtual size_t Tell() override;
		virtual size_t Size() override;

		bool UpdateReadBuffer(size_t bufferIndex);

		void DestroyBuffer()
		{
			delete[] m_ReadBuffer;
			m_ReadBuffer = nullptr;
			m_ReadBufferIndex = -1;
			m_ReadBufferSize = 0;
		}

		void CreateBuffer()
		{
			DestroyBuffer();
			m_ReadBuffer = new char[READ_BUFFER_SIZE];
		}

		void Reset()
		{
			m_Handle = INVALID_HANDLE_VALUE;
			m_Position = 0;
			m_ReadBuffer = nullptr;
			m_FilePointer = 0;
			m_ReadBufferSize = 0;
			m_ReadBufferIndex = -1;
		}

	private:
		HANDLE m_Handle;
		DWORD m_Position;
		DWORD m_FilePointer;
		char* m_ReadBuffer;
		DWORD m_ReadBufferSize;
		DWORD m_ReadBufferIndex;
	};
}