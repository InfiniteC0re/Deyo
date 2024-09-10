#pragma once
#include <Deyo/Core/Input.h>

namespace Deyo
{
	class WindowsInput : public Input
	{
	public:
		virtual bool IsKeyPressedImpl( int keyCode ) const override;
		virtual bool IsMouseButtonPressedImpl( int button ) const override;

		virtual std::pair<float, float> GetMousePositionImpl() const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;
	};
}