#include "StdAfx.h"
#include "State.h"

namespace AABSEngine
{
  namespace AI
  {
    template <typename T>
    /**
	* @class StateMachine
	*
	* @brief State machine used by agents
	*
	* @author AABS
	* @version X
	* @date October 2013
	*
	*/
	class StateMachine
    {
    private:
      T* m_owner;
      State<T>* m_currentState;
      State<T>* m_previousState;
    protected:
    public:
      StateMachine(T* owner);
      /**
	  * @brief Set the current state to specified state
	  */
	  void SetCurrentState(State<T>* state);
      /**
	  * @brief Set the current state to specified state
	  */
      void SetPreviousState(State<T>* state);
      /**
	  * @brief Main update for states
	  */
      void Update() const;
      /**
	  * @brief Change the state to specified state
	  */
      void ChangeState(State<T>* newstate);
      /**
	  * @brief Change state to previous state
	  */
      void RevertToPreviousState();

      State<T>* CurrentState() const;
      State<T>* PreviousState() const;

      /**
	  * @brief Returns whether or not there is a state
	  */
      bool IsInState(const State<T>* state) const;
    };
  }
}

using namespace AABSEngine::AI;
template <typename T>
StateMachine<T>::StateMachine(T* owner) { m_owner = owner; }

template <typename T>
void StateMachine<T>::SetCurrentState(State<T>* state) { m_currentState = state; }

template <typename T>
void StateMachine<T>::SetPreviousState(State<T>* state) { m_currentState = state; }

template <typename T>
void StateMachine<T>::Update() const
{
  if (m_currentState)
    m_currentState->Execute(m_owner);
}

template <typename T>
void StateMachine<T>::ChangeState(State<T>* newstate)
{
  if (m_currentState && newstate)
  {
    m_previousState = m_currentState;
    m_currentState->Exit(m_owner);
    m_currentState = newstate;
    m_currentState->Enter(m_owner);
  }
}

template <typename T>
void StateMachine<T>::RevertToPreviousState()
{
  ChangeState(m_previousState);
}

template <typename T>
State<T>* StateMachine<T>::CurrentState() const { return m_currentState; }

template <typename T>
State<T>* StateMachine<T>::PreviousState() const { return m_previousState; }

template <typename T>
bool StateMachine<T>::IsInState(const State<T>* state) const { return state == m_currentState; } // NOTE assumes states are singletons 