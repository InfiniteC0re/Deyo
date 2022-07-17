#pragma once
#include <vector>
#include "Layer.h"

namespace Deyo
{
	class DEYO_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		// Pushes layer
		void PushLayer(Layer* layer);
		
		// Pushes overlay
		void PushOverlay(Layer* overlay);
		
		// Pops layer
		void PopLayer(Layer* layer);
		
		// Pops overlay
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		// using this to add layers always before overlays
		std::vector<Layer*>::iterator m_LastLayer;
		std::vector<Layer*> m_Layers;
	};
}