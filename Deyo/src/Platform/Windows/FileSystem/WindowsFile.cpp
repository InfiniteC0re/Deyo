#include "pch.h"
#include "WindowsFile.h"

namespace Deyo
{
	bool WindowsFile::Open( const std::wstring filepath, CreateFlags flags )
	{
		DWORD dwCreationDisposition = OPEN_EXISTING;
		DWORD dwDesiredAccess = 0;
		DWORD dwShareMode = 0;

		dwDesiredAccess |= flags & CreateFlags_Read ? GENERIC_READ : dwDesiredAccess;
		dwDesiredAccess |= flags & CreateFlags_Write ? GENERIC_WRITE : dwDesiredAccess;

		if ( flags & CreateFlags_CreateNew )
		{
			dwShareMode = FILE_SHARE_READ;
			dwCreationDisposition = CREATE_ALWAYS;
			dwDesiredAccess |= GENERIC_WRITE;
		}

		m_Handle = CreateFileW( filepath.c_str(), dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, NULL, NULL );

		if ( m_Handle != INVALID_HANDLE_VALUE )
		{
			m_Position = 0;
			m_FilePointer = -1;
			CreateBuffer();

			return true;
		}

		return false;
	}

	void WindowsFile::Close()
	{
		CloseHandle( m_Handle );
		DestroyBuffer();
		Reset();
	}

	size_t WindowsFile::Read( LPVOID dst, size_t size )
	{
		if ( size < 1 ) return 0;

		DWORD readedCount = 0;
		DWORD curReadBufferIndex = m_Position / READ_BUFFER_SIZE * READ_BUFFER_SIZE;
		DWORD newReadBufferIndex = ( m_Position + size - 1 ) / READ_BUFFER_SIZE * READ_BUFFER_SIZE;
		DWORD readBufferPos = m_Position - curReadBufferIndex;

		UpdateReadBuffer( curReadBufferIndex );

		if ( curReadBufferIndex != newReadBufferIndex )
		{
			// m_ReadBuffer doesn't have all the required data
			DWORD readSize = READ_BUFFER_SIZE - readBufferPos;
			readSize = ( m_ReadBufferSize < readSize ) ? m_ReadBufferSize : readSize;

			std::memcpy( dst, m_ReadBuffer + readBufferPos, readSize );

			readedCount += readSize;
			m_Position += readedCount;

			readedCount += Read( reinterpret_cast<LPVOID>( (uintptr_t)dst + readSize ), size - readSize );
		}
		else
		{
			size = ( size > m_ReadBufferSize ) ? m_ReadBufferSize : size;
			std::memcpy( dst, m_ReadBuffer + readBufferPos, size );
			m_Position += size;
			readedCount += size;
		}

		m_ReadBufferIndex = newReadBufferIndex;

		return readedCount;
	}

	size_t WindowsFile::Write( LPVOID src, size_t size )
	{
		return size_t();
	}

	bool WindowsFile::Seek( SeekMode seekMode, size_t pos )
	{
		return false;
	}

	size_t WindowsFile::Tell()
	{
		return m_Position;
	}

	size_t WindowsFile::Size()
	{
		DWORD size = SetFilePointer( m_Handle, 0, NULL, FILE_END );

		if ( size == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR ) size = 0;
		SetFilePointer( m_Handle, m_FilePointer, NULL, FILE_BEGIN );

		return size;
	}

	bool WindowsFile::UpdateReadBuffer( size_t bufferIndex )
	{
		if ( m_ReadBufferIndex != bufferIndex )
		{
			if ( m_FilePointer != bufferIndex )
			{
				m_FilePointer = SetFilePointer( m_Handle, bufferIndex, NULL, FILE_BEGIN );
				if ( m_FilePointer != bufferIndex ) return false;
			}

			DWORD numberOfBytesRead = 0;

			if ( ReadFile( m_Handle, m_ReadBuffer, READ_BUFFER_SIZE, &numberOfBytesRead, NULL ) == FALSE )
			{
				return false;
			}

			m_ReadBufferSize = numberOfBytesRead;
			m_ReadBufferIndex = bufferIndex;
			m_FilePointer += numberOfBytesRead;
		}

		return true;
	}
}