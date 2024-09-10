#include "pch.h"
#include "FileManager.h"
#include "FileSystem.h"

namespace Deyo
{
	Scope<FileManager> FileManager::s_FileManager = CreateScope<FileManager>();
	bool FileManager::s_Verbose = false;

	void FileManager::MountFileSystem( Ref<FileSystem> pFileSystem )
	{
		DEYO_ASSERT(
			FindFileSystem( pFileSystem->GetName() ) == nullptr,
			"FileManager: trying to mount filesystem twice"
		);

		m_FileSystems.push_back( pFileSystem );
	}

	void FileManager::UnmountFileSystem( Ref<FileSystem> pFileSystem )
	{
		for ( auto it = m_FileSystems.begin(); it != m_FileSystems.end();)
		{
			if ( *it == pFileSystem )
			{
				m_FileSystems.erase( it );
				return;
			}
			else
			{
				it++;
			}
		}
	}

	Ref<File> FileManager::CreateFile( const std::wstring& filepath, File::CreateFlags flags )
	{
		auto& manager = Instance();
		DEYO_ASSERT( manager.m_FileSystems.size() > 0, "FileManager: no filesystems are mounted" );

		auto& fileSystem = manager.m_FileSystems.front();
		auto file = fileSystem->CreateFile( filepath, flags );

		if ( s_Verbose )
		{
			if ( file )
			{
				DEYO_CORE_TRACE( L"Created file {0} with flags {1}", filepath, flags );
			}
			else
			{
				DEYO_CORE_TRACE( L"Unable to create file {0} with flags {1}", filepath, flags );
			}
		}

		return file;
	}

	Ref<FileSystem> FileManager::FindFileSystem( const std::string& name )
	{
		for ( auto& pFileSystem : m_FileSystems )
		{
			if ( pFileSystem->GetName() == name ) return pFileSystem;
		}

		return nullptr;
	}
}
