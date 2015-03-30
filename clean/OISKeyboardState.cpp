#include "StdAfx.h"
#include "OISKeyboardState.h"

using namespace AABSEngine::Input;

OISKeyboardState::OISKeyboardState(OIS::Keyboard* keyboard)
{
	m_keyboard = keyboard;
}

bool OISKeyboardState::UpdateState()
{
	bool success = true;
	m_keyboard->capture();

	/* store a copy of last state */
	std::copy(std::begin(m_keyStates), std::end(m_keyStates), std::begin(m_oldKeyStates));

	/* update state */
	m_keyStates[A] = m_keyboard->isKeyDown(OIS::KC_A) ? true : false;
	m_keyStates[B] = m_keyboard->isKeyDown(OIS::KC_B) ? true : false;
	m_keyStates[C] = m_keyboard->isKeyDown(OIS::KC_C) ? true : false;
	m_keyStates[D] = m_keyboard->isKeyDown(OIS::KC_D) ? true : false;
	m_keyStates[E] = m_keyboard->isKeyDown(OIS::KC_E) ? true : false;
	m_keyStates[F] = m_keyboard->isKeyDown(OIS::KC_F) ? true : false;
	m_keyStates[G] = m_keyboard->isKeyDown(OIS::KC_G) ? true : false;
	m_keyStates[H] = m_keyboard->isKeyDown(OIS::KC_H) ? true : false;
	m_keyStates[I] = m_keyboard->isKeyDown(OIS::KC_I) ? true : false;
	m_keyStates[J] = m_keyboard->isKeyDown(OIS::KC_J) ? true : false;
	m_keyStates[K] = m_keyboard->isKeyDown(OIS::KC_K) ? true : false;
	m_keyStates[L] = m_keyboard->isKeyDown(OIS::KC_L) ? true : false;
	m_keyStates[M] = m_keyboard->isKeyDown(OIS::KC_M)  ? true : false;
	m_keyStates[N] = m_keyboard->isKeyDown(OIS::KC_N)  ? true : false;
	m_keyStates[O] = m_keyboard->isKeyDown(OIS::KC_O)  ? true : false;
	m_keyStates[P] = m_keyboard->isKeyDown(OIS::KC_P)  ? true : false;
	m_keyStates[Q] = m_keyboard->isKeyDown(OIS::KC_Q)  ? true : false;
	m_keyStates[R] = m_keyboard->isKeyDown(OIS::KC_R)  ? true : false;
	m_keyStates[S] = m_keyboard->isKeyDown(OIS::KC_S)  ? true : false;
	m_keyStates[T] = m_keyboard->isKeyDown(OIS::KC_T)  ? true : false;
	m_keyStates[U] = m_keyboard->isKeyDown(OIS::KC_U)  ? true : false;
	m_keyStates[V] = m_keyboard->isKeyDown(OIS::KC_V)  ? true : false;
	m_keyStates[W] = m_keyboard->isKeyDown(OIS::KC_W)  ? true : false;
	m_keyStates[X] = m_keyboard->isKeyDown(OIS::KC_X)  ? true : false;
	m_keyStates[Y] = m_keyboard->isKeyDown(OIS::KC_Y)  ? true : false;
	m_keyStates[Z] = m_keyboard->isKeyDown(OIS::KC_Z)  ? true : false;
	m_keyStates[LEFT] = m_keyboard->isKeyDown(OIS::KC_LEFT) ? true : false;
	m_keyStates[RIGHT] = m_keyboard->isKeyDown(OIS::KC_RIGHT) ? true : false;
	m_keyStates[UP] = m_keyboard->isKeyDown(OIS::KC_UP) ? true : false;
	m_keyStates[DOWN] = m_keyboard->isKeyDown(OIS::KC_DOWN) ? true : false;
	m_keyStates[SPACE] = m_keyboard->isKeyDown(OIS::KC_SPACE) ? true : false;
	m_keyStates[ENTER] = m_keyboard->isKeyDown(OIS::KC_RETURN) ? true : false;
	m_keyStates[ESC] = m_keyboard->isKeyDown(OIS::KC_ESCAPE) ? true : false;
	m_keyStates[KEY_0] = m_keyboard->isKeyDown(OIS::KC_0) ? true: false;
	m_keyStates[KEY_1] = m_keyboard->isKeyDown(OIS::KC_1) ? true: false;
	m_keyStates[KEY_2] = m_keyboard->isKeyDown(OIS::KC_2) ? true: false;
	m_keyStates[KEY_3] = m_keyboard->isKeyDown(OIS::KC_3) ? true: false;
	m_keyStates[KEY_4] = m_keyboard->isKeyDown(OIS::KC_4) ? true: false;
	m_keyStates[KEY_5] = m_keyboard->isKeyDown(OIS::KC_5) ? true: false;
	m_keyStates[KEY_6] = m_keyboard->isKeyDown(OIS::KC_6) ? true: false;
	m_keyStates[KEY_7] = m_keyboard->isKeyDown(OIS::KC_7) ? true: false;
	m_keyStates[KEY_8] = m_keyboard->isKeyDown(OIS::KC_8) ? true: false;
	m_keyStates[KEY_9] = m_keyboard->isKeyDown(OIS::KC_9) ? true: false;
	
	return success;
}

bool OISKeyboardState::Update()
{
	bool success = true;

	success = success && UpdateState();
	success = success && UpdateEvents();

	return success;
}