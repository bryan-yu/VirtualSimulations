#pragma once

namespace AABSEngine
{
	namespace AI
	{
		/**
		* @struct MessagePacket
		*
		* @brief Message packet data
		*
		*/
		struct MessagePacket
		{
			int m_msg;
			int m_srcID;
			int m_destID;
			void* m_data;
		};

		/**
		* @class IInteractable
		*
		* @brief 
		*
		* @author AABS
		* @version X
		* @date October 2013
		*
		*/
		class IInteractable
		{
		public:
			virtual ~IInteractable(){}
			virtual void Process(const MessagePacket& message)=0;
		};
	}
}



