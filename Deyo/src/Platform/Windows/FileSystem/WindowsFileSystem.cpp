#include "pch.h"
#include "WindowsFileSystem.h"
#include "WindowsFile.h"

namespace Deyo
{
	WindowsFileSystem::WindowsFileSystem(const std::string& name) : FileSystem(name) { }

	Ref<File> WindowsFileSystem::CreateFile_impl(const std::wstring& filepath, File::CreateFlags flags)
	{
		auto file = CreateRef<WindowsFile>(this);
		file->Open(filepath, flags);

		return file;
	}
}
