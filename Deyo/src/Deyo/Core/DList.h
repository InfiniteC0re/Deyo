#pragma once

namespace Deyo
{
	class GenericDList
	{
	public:
		class Node
		{
		protected:
			Node() { Reset(); }

			inline Node* Next() const { return m_Next; }
			inline Node* Prev() const { return m_Prev; }
			inline bool IsLinked() const { return this != m_Next; }
			inline void Reset() { m_Next = this; m_Prev = this; }

			void InsertAfter(Node* node)
			{
				m_Prev = node;
				m_Next = node->m_Next;
				node->m_Next = this;
				m_Next->m_Prev = this;
			}

			void InsertBefore(Node* node)
			{
				m_Next = node;
				m_Prev = node->m_Prev;
				node->m_Prev = this;
				m_Prev->m_Next = this;
			}

			void Remove()
			{
				m_Prev->m_Next = m_Next;
				m_Next->m_Prev = m_Prev;
				Reset();
			}

			Node& operator=(const Node& node)
			{
				m_Next = node.m_Next;
				m_Prev = node.m_Prev;
				return *this;
			}

		public:
			template<class T>
			friend class DList;
			
			friend GenericDList;

		public:
			template<typename T>
			inline T* As() { return static_cast<T*>(this); }

		protected:
			Node* m_Next;
			Node* m_Prev;
		};

	public:
		inline void InsertHead(Node* node) { node->InsertAfter(&m_Root); }
		inline void InsertTail(Node* node) { node->InsertBefore(&m_Root); }
		inline void RemoveHead()            { if (!IsEmpty()) m_Root.Next()->Remove(); }
		inline void RemoveTail()            { if (!IsEmpty()) m_Root.Prev()->Remove(); }
		inline bool IsEmpty()               { return m_Root.Next() == &m_Root; }
		inline Node* Head()                { return m_Root.Next(); }
		inline Node* Tail()                { return m_Root.Prev(); }
		inline Node* Begin()               { return m_Root.Next(); }
		inline Node* End()                 { return &m_Root; }

		void RemoveAll()
		{
			auto pNode = m_Root.Next();

			while (pNode != &m_Root)
			{
				pNode->Remove();
				pNode = m_Root.Next();
			}
		}

	protected:
		GenericDList() = default;
		~GenericDList() { RemoveAll(); }

	protected:
		Node m_Root;
	};

	template <class T>
	class DList : public GenericDList
	{
	public:
		DList() { }

		inline T* Head()         { return GenericDList::Head()->As<T>(); }
		inline T* Tail()         { return GenericDList::Tail()->As<T>(); }
		inline T* Begin()        { return GenericDList::Begin()->As<T>(); }
		inline T* End()          { return GenericDList::End()->As<T>(); }
		inline bool IsEmpty()    { return GenericDList::IsEmpty(); }
		inline bool IsLinked()   { return m_Root.IsLinked(); }
		inline void RemoveHead() { GenericDList::RemoveHead(); }
		inline void RemoveTail() { GenericDList::RemoveTail(); }
	};
}