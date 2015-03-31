#pragma once

namespace AABSEngine
{
	namespace Input
	{
		typedef void (*KeyHandler)();
		typedef void (*MouseHandler)(int, int);

		enum MouseButtons
		{
		  BUTTON_LEFT = 0,
		  NUM_BUTTONS
		};
		enum MouseButtonStates
		{
		  BUTTON_UP = 0,
		  BUTTON_DOWN = 1
		};
		enum MouseButtonExecute
		{
		  BUTTON_ON_PRESS = 0,
		  BUTTON_ON_HOLD = 1
		};
		struct MouseButtonEvent
		{
		  MouseButtonEvent(MouseButtons b, MouseButtonStates s, MouseButtonExecute e) { button = b; state = s; execute = e; };
		  MouseButtons button;
		  MouseButtonStates state;
		  MouseButtonExecute execute;

		  bool operator==(const MouseButtonEvent& otherevent) const { return (button == otherevent.button) && (state == otherevent.state) && (execute == otherevent.execute); }
		  /* functions below here implemented for compatability with STL */
		  bool operator<(const MouseButtonEvent& otherevent) const { return (button < otherevent.button) && (state < otherevent.state) && (execute < otherevent.execute); }
		  bool operator>(const MouseButtonEvent& otherevent) const { return (button > otherevent.button) && (state > otherevent.state) && (execute > otherevent.execute); }
		};
    
	    enum KeyboardKeys
		{
		  A = 0, B, C, D,
		  E, F, G, H,
		  I, J, K, L,
		  M, N, O, P,
		  Q, R, S, T,
		  U, V, W, X,
		  Y, Z, LEFT, RIGHT,
		  UP, DOWN, SPACE, ENTER,
		  ESC,
		  KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
		  KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
		  NUM_KEYS
		};
		enum KeyboardKeyStates
		{
		  KEY_UP = 0,
		  KEY_DOWN = 1
		};
		enum KeyboardKeyExecute
		{
		  ON_PRESS = 0,
		  ON_HOLD = 1
		};
		struct KeyboardEvent
		{
		  KeyboardEvent(KeyboardKeys k, KeyboardKeyStates s, KeyboardKeyExecute e) { key = k; state = s; execute = e; }
		  KeyboardKeys key;
		  KeyboardKeyStates state;
		  KeyboardKeyExecute execute;

		  bool operator==(const KeyboardEvent& otherevent) const { return (key == otherevent.key) && (state == otherevent.state) && (execute == otherevent.execute); }
		  /* functions below here implemented for compatability with STL */
		  bool operator<(const KeyboardEvent& otherevent) const { return (key < otherevent.key) && (state < otherevent.state) && (execute == otherevent.execute); }
		  bool operator>(const KeyboardEvent& otherevent) const { return (key > otherevent.key) && (state > otherevent.state) && (execute == otherevent.execute); }
		};
	}
}