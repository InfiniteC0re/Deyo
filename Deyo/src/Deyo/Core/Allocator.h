#pragma once

namespace Deyo
{

	class IAllocator
	{
	public:
		virtual void* Allocate( size_t uiSize, size_t uiAlignment ) = 0;
		virtual void Deallocate( void* pAllocMem ) = 0;
	};

}
