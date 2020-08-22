#pragma once

#include <sstream>
#include <string>

#include "RGE/Math.hpp"

namespace RGE
{
	enum class EventType
	{
		Empty = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Event structure
	struct Event
	{
		Event() {}
		EventType type = EventType::Empty;
		union
		{
			struct
			{
				bool focused = false;
				RGE::Math::v2i size;
				RGE::Math::v2i pos;
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
				RGE::Math::v2i pos;
				RGE::Math::v2i offset;
			} mouse;
		};
	};

} // RGE
