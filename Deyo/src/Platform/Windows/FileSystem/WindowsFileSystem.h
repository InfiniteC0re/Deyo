#pragma once
#include "Deyo/FileSystem/FileSystem.h"

namespace Deyo
{
	class WindowsFileSystem : public FileSystem
	{
	public:
		WindowsFileSystem(const std::string& name);

	private:
		virtual Ref<File> CreateFile_impl(const std::wstring& filepath, File::CreateFlags flags) override;
	};
}