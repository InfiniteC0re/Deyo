#pragma once

#ifdef CreateFile
#undef CreateFile
#endif

namespace Deyo
{
	class FileSystem;

	class File : public std::enable_shared_from_this<File>
	{
	public:
		typedef uint8_t SeekMode;
		enum SeekMode_ : SeekMode
		{
			SeekMode_Set,
			SeekMode_Cur,
			SeekMode_End,
		};

		typedef uint8_t CreateFlags;
		enum CreateFlags_ : CreateFlags
		{
			CreateFlags_Read      = BIT(0),
			CreateFlags_Write     = BIT(1),
			CreateFlags_CreateNew = BIT(2),
			CreateFlags_ReadWrite = CreateFlags_Read | CreateFlags_Write,
		};

	public:
		File(FileSystem* pFileSystem) : m_FileSystem(pFileSystem) { }
		virtual ~File() { }

		virtual bool Open(const std::wstring filepath, CreateFlags flags) = 0;
		virtual void Close() = 0;
		virtual size_t Read(void* dst, size_t size) = 0;
		virtual size_t Write(void* src, size_t size) = 0;
		virtual bool Seek(SeekMode seekMode, size_t pos) = 0;
		virtual size_t Tell() = 0;
		virtual size_t Size() = 0;

		void Destroy();

	protected:
		FileSystem* m_FileSystem;
	};
}