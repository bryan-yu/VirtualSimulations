#pragma once

namespace AABSEngine
{
	namespace Input
	{
		class InputManager;
	}

	namespace Core
	{
		class Actor;

		/**
		* @class IAction
		*
		* @brief 
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		template<class UserType>
		class InputCallback
		{
		public:

			InputCallback(UserType& user) : m_user(user){} 
	
			virtual ~InputCallback(){}

			virtual void Begin()=0;

			virtual void Execute()=0;

			virtual void End()=0;

		protected:
			UserType& m_user;
			

		private:
			InputCallback(const InputCallback& other) : m_user(other.m_user){}
			InputCallback& operator=(const InputCallback& ){return *this;}
		};
	}
}