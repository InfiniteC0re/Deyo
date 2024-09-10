#include "pch.h"
#include "FileSystem.h"

namespace Deyo
{
	void File::Destroy()
	{
		m_FileSystem->DestroyFile( shared_from_this() );
	}
}
