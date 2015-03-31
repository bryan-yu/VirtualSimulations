#pragma once

#include "types.h"
#include "OgreTexture.h"
#include "OgreOverlayManager.h"
#include "OgrePanelOverlayElement.h"
#include "OgreTextureManager.h"
#include "OgreMaterialManager.h"

namespace AABSEngine
{
	namespace Rendering
	{
		/**
		 * @class MouseCursor
		 *
		 * @brief Mouse cursor class
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class MouseCursor
		{
		public:
			~MouseCursor(){}

			MouseCursor();

			void SetTexture(std::string filename);

			void SetWindowDimensions(size_t width, size_t height);

			void SetVisible(bool visible);

			void UpdatePosition(int x, int y);			
	
			void AlignCenter();

		private:

			Ogre::Overlay* m_guiOverlay;
			Ogre::OverlayContainer* m_cursorList;
			Ogre::TexturePtr m_texture;
			Ogre::MaterialPtr m_material;
 
			Decimal m_windowHeight;
			Decimal m_windowWidth;
		};
	}
}