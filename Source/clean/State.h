#pragma once

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @class State
		*
		* @brief Templated base class for agent states
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		template <typename T>
		class State
		{
		private:
		protected:
		public:
			virtual ~State() { }
			/**
			* @brief Enter state
			*/
			virtual void Enter(T*) = 0;
			/**
			* @brief Execute state
			*/
			virtual void Execute(T*) = 0;
			/**
			* @brief Exit state
			*/
			virtual void Exit(T*) = 0;
		};
	}
}