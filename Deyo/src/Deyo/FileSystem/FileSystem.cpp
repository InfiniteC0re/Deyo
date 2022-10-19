#include "pch.h"
#include "FileSystem.h"
#include "Platform/Windows/FileSystem/WindowsFileSystem.h"

namespace Deyo
{
	FileSystem::FileSystem(const std::string& name)
	{
		m_Name = name;
	}

	FileSystem::~FileSystem()
	{
		Destroy();
	}

	Ref<File> FileSystem::CreateFile(const std::wstring& filepath, File::CreateFlags flags)
	{
		auto pFile = CreateFile_impl(filepath, flags);
		
		if (pFile)
		{
			m_Files.push_back(pFile);
		}

		return pFile;
	}

	void FileSystem::Destroy()
	{
		// close and destroy every opened file of this filesystem
		for (auto pFile : m_Files)
		{
			FileSystem::DestroyFile(pFile);
		}
	}

	Ref<FileSystem> FileSystem::Create(const std::string& name)
	{
		#ifdef DEYO_PLATFORM_WINDOWS
			return CreateRef<WindowsFileSystem>(name);
		#endif

		return nullptr;
	}

	void FileSystem::DestroyFile(Ref<File> pFile)
	{
		if (pFile)
		{
			for (auto it = m_Files.begin(); it != m_Files.end();)
			{
				if (*it == pFile)
				{
					pFile->Close();
					m_Files.erase(it);
					return;
				}
				else
				{
					it++;
				}
			}
		}
	}
}
