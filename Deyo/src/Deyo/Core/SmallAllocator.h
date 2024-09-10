#pragma once
#include <cstdint>
#include <limits>

namespace Deyo
{

	//-----------------------------------------------------------------------------
	// Purpose: This allocator is used for small allocations without fragmentation.
	// It preallocates a fixed sized area of memory which is divided into
	// NUM_FREELISTS freelists with FREELIST_MAX_PAGES pages in each.
	// Each freelist is initialised for a specific sized allocations to avoid
	// the fragmentation issue.
	//-----------------------------------------------------------------------------
	class AllocatorSmall
	{
	public:
		static constexpr size_t PAGE_SIZE = 16 * 1024;
		static constexpr size_t ALLOC_MIN_SIZE = sizeof( void* );
		static constexpr size_t ALLOC_MAX_SIZE = 2048;
		static constexpr int NUM_FREELISTS = ALLOC_MAX_SIZE / ALLOC_MIN_SIZE;
		static constexpr int FREELIST_MAX_PAGES = 16;
		static constexpr size_t ALLOCATOR_TOTAL_SIZE = FREELIST_MAX_PAGES * PAGE_SIZE * NUM_FREELISTS;

		struct PageAllocation
		{
			PageAllocation* pNext;
		};

		struct Page {};

		struct PageFreeList
		{
			struct PageInfo
			{
				Page* pPage;
				PageAllocation* pHeadFreeAlloc;
			};

			size_t uiAllocSize = 0;
			int uiPageMaxAllocs = 0;
			PageInfo aPages[ FREELIST_MAX_PAGES ];

			void* Allocate( size_t uiAlignment );
			void Deallocate( int iPage, void* pAllocMem );

			PageAllocation* GetAllocation( int iPage, int iAllocIndex ) const;
		};

	public:
		AllocatorSmall() = default;
		~AllocatorSmall() = default;

		void Initialise();
		void Deinitialise();

		void* Allocate( size_t uiSize, size_t uiAlignment = alignof( void* ) );
		void Deallocate( void* pAllocMem );

	private:
		Page* GetPage( int iPage = 0 ) const;
		int MapSizeToFreeList( size_t uiSize );

	private:
		Page* m_pAllPages = nullptr;
		PageFreeList m_aFreeList[ NUM_FREELISTS ];
	};

}
