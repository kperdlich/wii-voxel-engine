/*
 * Logo.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "Logo.h"


Logo::Logo(const char* name,
		BasicTexture* tex) : UITextureElement(0, 0, name, tex) {

	m_texture->SetX( (rmode->viWidth / 2) - (m_texture->GetWidth() / 2) );
	m_texture->SetY( (rmode->viHeight / 2) - ( m_texture->GetHeight() / 2 ) );
}

Logo::~Logo() {
}

void Logo::Load() {
}

void Logo::Unload() {
}


