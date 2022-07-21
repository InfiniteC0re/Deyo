#include "pch.h"
#include "LayerStack.h"

namespace Deyo
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : *this) delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LastLayerIndex, layer);
		m_LastLayerIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto res = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (res != m_Layers.end())
		{
			m_Layers.erase(res);
			m_LastLayerIndex--;
			
			layer->OnDettach();
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto res = std::find(m_Layers.begin(), m_Layers.end(), overlay);

		if (res != m_Layers.end())
		{
			m_Layers.erase(res);
			overlay->OnDettach();
		}
	}
}