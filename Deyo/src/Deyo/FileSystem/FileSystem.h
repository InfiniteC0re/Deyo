#pragma once
#include "Deyo/Core/DList.h"
#include "FileManager.h"
#include "File.h"

namespace Deyo
{
	class FileSystem : public std::enable_shared_from_this<FileSystem>
	{
	public:
		FileSystem(const std::string& name);
		FileSystem(const FileSystem& other) = delete;
		virtual ~FileSystem();

		Ref<File> CreateFile(const std::wstring& filepath, File::CreateFlags flags);
		void DestroyFile(Ref<File> pFile);
		void Unmount() { FileManager::Instance().UnmountFileSystem(shared_from_this()); }
		void Destroy();

		const std::string& GetName() const { return m_Name; }

		static Ref<FileSystem> Create(const std::string& name);

	private:
		virtual Ref<File> CreateFile_impl(const std::wstring& filepath, File::CreateFlags flags) = 0;

	private:
		std::string m_Name;
		std::vector<Ref<File>> m_Files;
	};
}