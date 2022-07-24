#pragma once
#include <Deyo/Core/Core.h>

namespace Deyo
{
	enum class ShaderDataType : uint32_t
	{
		//////////////////////////////////////////
		// ---------------------------------------
		// Structure:
		// Size:				uint16_t
		// Index:				uint8_t
		// Component count:		uint8_t
		// ---------------------------------------
		//////////////////////////////////////////

		None	 = 0x00000000,
		Float	 = 0x00040101,
		Float2	 = 0x00080202,
		Float3	 = 0x000C0303,
		Float4	 = 0x00100404,
		Mat3	 = 0x00240503,
		Mat4	 = 0x00400604,
		Int		 = 0x00040701,
		Int2	 = 0x00080802,
		Int3	 = 0x000C0903,
		Int4	 = 0x00100A04,
		Bool	 = 0x00010B01
	};

	class BufferElement
	{
	public:
		BufferElement() = default;
		BufferElement(ShaderDataType type, bool normalized) : Type(type), Normalized(normalized) { }
		
		inline void SetOffset(uint32_t offset)			  { Offset = offset; }
		
		inline bool GetNormalized()					const { return Normalized; }
		inline uint32_t GetOffset()					const { return Offset; }
		inline ShaderDataType GetType()				const { return Type; }

		inline uint8_t GetIndex()			const { return ((uint32_t)Type & 0x0000FF00) >> 8; }
		inline uint16_t GetSize()			const { return ((uint32_t)Type & 0xFFFF0000) >> 16; }
		inline uint8_t GetComponentCount()	const { return ((uint32_t)Type & 0x000000FF); }

	private:
		ShaderDataType Type = ShaderDataType::None;
		uint32_t Offset = 0;
		bool Normalized = false;
	};

	class BufferLayout
	{
	public:
		BufferLayout() { }
		BufferLayout(std::initializer_list<BufferElement> list) : m_Elements(list)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;

			for (auto& element : m_Elements)
			{
				element.SetOffset(offset);
				offset += element.GetSize();
			}

			m_Stride = offset;
		}

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		// Updates sub data
		virtual void SetData(const void* data, uint32_t offset, uint32_t dataSize) = 0;

		// Updates whole data
		virtual void SetData(const void* data, uint32_t dataSize) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(uint32_t size = 0);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	};
}