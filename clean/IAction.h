#pragma once

namespace AABSEngine
{
	namespace Core
	{
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
		class IAction
		{
		public:
			virtual ~IAction(){}
			/**
			* @brief 
			*/
			virtual void Begin()=0;
			/**
			* @brief 
			*/
			virtual void Execute()=0;
			/**
			* @brief 
			*/
			virtual void End()=0;
		};
	}
}