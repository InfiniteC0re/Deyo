#include "pch.h"
#include "SmallAllocator.h"

namespace Deyo
{

	void AllocatorSmall::Initialise()
	{
		if ( m_pAllPages )
			return;

		// Preallocate all pages
		m_pAllPages = reinterpret_cast<Page*>( ::new uint8_t[ ALLOCATOR_TOTAL_SIZE ] );

		// Initialise page freelists
		for ( int i = 0; i < NUM_FREELISTS; i++ )
		{
			size_t uiFreeListAllocSize = ALLOC_MIN_SIZE * ( i + 1 );
			int uiPageMaxAllocs = int( PAGE_SIZE / uiFreeListAllocSize );

			PageFreeList* pFreeList = &m_aFreeList[ i ];

			pFreeList->uiAllocSize = uiFreeListAllocSize;
			pFreeList->uiPageMaxAllocs = uiPageMaxAllocs;

			// Initialise info about pages
			for ( int k = 0; k < FREELIST_MAX_PAGES; k++ )
			{
				PageFreeList::PageInfo* pPageInfo = &pFreeList->aPages[ k ];
				pPageInfo->pPage = GetPage( i * FREELIST_MAX_PAGES + k );;

				// Initialise freelist of the page
				for ( int j = 0; j < uiPageMaxAllocs - 1; j++ )
					pFreeList->GetAllocation( k, j )->pNext = pFreeList->GetAllocation( k, j + 1 );

				// Set the last node's next node to null
				pFreeList->GetAllocation( k, uiPageMaxAllocs - 1 )->pNext = nullptr;

				// Update head free alloc in the info object
				pPageInfo->pHeadFreeAlloc = pFreeList->GetAllocation( k, 0 );
			}
		}
	}

	void AllocatorSmall::Deinitialise()
	{
		::delete[]( m_pAllPages );
		m_pAllPages = nullptr;
	}

	int AllocatorSmall::MapSizeToFreeList( size_t uiSize )
	{
		return int( uiSize / ALLOC_MIN_SIZE - 1 );
	}

	void* AllocatorSmall::Allocate( size_t uiSize, size_t uiAlignment /*= alignof( void* ) */ )
	{
		// Align size to the alignment to make sure we can align it later
		uiSize = ( uiSize + ( uiAlignment - 1 ) ) & ( std::numeric_limits<size_t>::max() - ( uiAlignment - 1 ) );

		return m_aFreeList[ MapSizeToFreeList( uiSize ) ].Allocate( uiAlignment );
	}

	void AllocatorSmall::Deallocate( void* pAllocMem )
	{
		// Calculate at which page the pointer points
		int iPageAbs = int( ( reinterpret_cast<uintptr_t>( pAllocMem ) - reinterpret_cast<uintptr_t>( m_pAllPages ) ) / PAGE_SIZE );

		int iPageFreeList = iPageAbs / FREELIST_MAX_PAGES;
		int iPageID = iPageAbs - ( iPageFreeList * FREELIST_MAX_PAGES );

		PageFreeList* pFreeList = &m_aFreeList[ iPageFreeList ];
		pFreeList->Deallocate( iPageID, pAllocMem );
	}

	AllocatorSmall::Page* AllocatorSmall::GetPage( int iPage /*= 0 */ ) const
	{
		return reinterpret_cast<Page*>( reinterpret_cast<uintptr_t>( m_pAllPages ) + PAGE_SIZE * iPage );
	}

	void* AllocatorSmall::PageFreeList::Allocate( size_t uiAlignment )
	{
		// TODO: take alignment into account

		for ( int i = 0; i < FREELIST_MAX_PAGES; i++ )
		{
			PageAllocation* pAllocation = aPages[ i ].pHeadFreeAlloc;

			// This page seems to be fully used so let's try another one
			if ( !pAllocation )
				continue;

			// Set head to the next free alloc
			aPages[ i ].pHeadFreeAlloc = pAllocation->pNext;

			// Return the allocation that can be used
			return pAllocation;
		}

		return nullptr;
	}

	void AllocatorSmall::PageFreeList::Deallocate( int iPage, void* pAllocMem )
	{
		int iAllocIndex = int( ( reinterpret_cast<uintptr_t>( pAllocMem ) - reinterpret_cast<uintptr_t>( aPages[ iPage ].pPage ) ) / uiAllocSize );

		PageAllocation* pAllocation = GetAllocation( iPage, iAllocIndex );

		// Link this allocation before the current head
		pAllocation->pNext = aPages[ iPage ].pHeadFreeAlloc;

		// Make this allocation the head
		aPages[ iPage ].pHeadFreeAlloc = pAllocation;
	}

	AllocatorSmall::PageAllocation* AllocatorSmall::PageFreeList::GetAllocation( int iPage, int iAllocIndex ) const
	{
		return reinterpret_cast<PageAllocation*>( reinterpret_cast<uintptr_t>( aPages[ iPage ].pPage ) + uiAllocSize * iAllocIndex );
	}

}

