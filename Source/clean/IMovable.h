#pragma once

namespace AABSEngine
{
	namespace Core
	{
		/**
		 * @class IMovable
		 *
		 * @brief 
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class IMovable
		{
		public:

			virtual void MoveUp() = 0;
			virtual void MoveDown() = 0;
			virtual void MoveForward() = 0;
			virtual void MoveBackward() = 0;
			virtual void StrafeLeft() = 0;
			virtual void StrafeRight() = 0;
			virtual void RotateLeft() = 0;
			virtual void RotateRight() = 0;
		};
	}
}