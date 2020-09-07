#pragma once

#include <sstream>
#include <string>

#include "RGE/Math/Vector.hpp"

namespace RGE
{
	enum class RGE_EXPORT EventType
	{
		Empty = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Event structure
	struct RGE_EXPORT Event
	{
		Event() {}
		EventType type = EventType::Empty;
		union
		{
			struct
			{
				bool focused = false;
				RGE::Math::Vector2<int> size;
				RGE::Math::Vector2<int> pos;
			} window;

			// KeyPressed/KeyReleased
			struct
			{
				int keycode;
				bool repeated = false;
			} key;

			// MouseButtonPressed/MouseButtonReleased/MouseMoved/MouseScrolled
			struct
			{
				int button;
				RGE::Math::Vector2<double> pos;
				RGE::Math::Vector2<int> offset;
			} mouse;
		};
	};

} // RGE
