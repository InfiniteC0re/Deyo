#pragma once
#include "File.h"

namespace Deyo
{
	class FileSystem;

	class FileManager
	{
	public:
		FileManager() = default;
		FileManager( const FileManager& ) = delete;

		// Mounts filesystem to the file manager
		void MountFileSystem( Ref<FileSystem> pFileSystem );

		// Unmounts filesystem from the file manager
		void UnmountFileSystem( Ref<FileSystem> pFileSystem );

		// Looks for a filesystem by name and returns it if found
		Ref<FileSystem> FindFileSystem( const std::string& name );

		// Sets verbose mode to new value
		static void SetVerbose( bool verbose ) { Instance().s_Verbose = verbose; }

		// Creates file in the last mounted filesystem
		static Ref<File> CreateFile( const std::wstring& filepath, File::CreateFlags flags );

		// Returns instance of FileManager
		static FileManager& Instance() { return *s_FileManager; }

	private:
		static Scope<FileManager> s_FileManager;
		static bool s_Verbose;

	private:
		std::vector<Ref<FileSystem>> m_FileSystems;
	};
}