#include "StdAfx.h"
#include "Cursor.h"

AABSEngine::Rendering::MouseCursor::MouseCursor() : m_guiOverlay(0), m_cursorList(0)
{
	m_material = Ogre::MaterialManager::getSingleton().create("MouseCursor", "General");
			
	m_cursorList = (Ogre::OverlayContainer*) Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "MouseCursor");
	m_cursorList->setMaterialName(m_material->getName());
	m_cursorList->setPosition(0,0);

	m_guiOverlay = Ogre::OverlayManager::getSingletonPtr()->create("MouseCursor");		
	m_guiOverlay->setZOrder(650);		
	m_guiOverlay->add2D(m_cursorList);
	m_guiOverlay->show();
}

void AABSEngine::Rendering::MouseCursor::AlignCenter()
{
	Decimal x = m_windowWidth / 2.0;
	Decimal y = m_windowHeight / 2.0;

	x -= (m_texture->getWidth() / 2.0f);
	y -= (m_texture->getHeight() / 2.0f);

	UpdatePosition(x,y);
}

void AABSEngine::Rendering::MouseCursor::SetTexture(std::string filename)
{
	m_texture = Ogre::TextureManager::getSingleton().load(filename, "General");
	
	Ogre::TextureUnitState *texState = 0;
	
	if(m_material->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
	{
		m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTexture(m_texture);
		SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
	else
	{	
		texState = m_material->getTechnique(0)->getPass(0)->createTextureUnitState(m_texture->getName());
		m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTexture(m_texture);
		texState->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);	
	}
	
	/*
	if(!m_material->getTechnique(0)->getPass(0)->getNumTextureUnitStates())
	{
		texState = m_material->getTechnique(0)->getPass(0)->createTextureUnitState( m_texture->getName() );		
	}	

	texState = m_material->getTechnique(0)->getPass(0)->getTextureUnitState(0);
	texState->removeAllEffects();
	*/	
	m_material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);	
	AlignCenter();
}

void AABSEngine::Rendering::MouseCursor::SetWindowDimensions(size_t width, size_t height)
{
	m_windowWidth = width > 0 ? width : 1;	
	m_windowHeight = height > 0 ? height : 1;
		
	m_cursorList->setWidth(m_texture->getWidth() / m_windowWidth);	
	m_cursorList->setHeight(m_texture->getHeight() / m_windowHeight);
}

void AABSEngine::Rendering::MouseCursor::SetVisible(bool visible)
{
	if(visible) 
	{
		m_cursorList->show();
	}
	else
	{
		m_cursorList->hide();
	}
}

void AABSEngine::Rendering::MouseCursor::UpdatePosition(int x, int y)
{
	double rx = x / m_windowWidth;
	double ry = y / m_windowHeight;
		
	rx = rx < 0.0 ? 0.0 : rx > 1.0 ? 1.0 : rx;
	ry = ry < 0.0 ? 0.0 : ry > 1.0 ? 1,0 : ry;

	m_cursorList->setPosition(rx,ry);
}