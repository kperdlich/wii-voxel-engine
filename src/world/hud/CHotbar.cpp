/*
 * CHotbar.cpp
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#include "CHotbar.h"

CHotbar::CHotbar( const char* name, BasicTexture* tex ) : UITextureElement(0, 0, name, tex ) {

	tex->SetX( (rmode->viWidth / 2) - (m_texture->GetWidth() / 2) );
	tex->SetY( rmode->viHeight - m_texture->GetHeight() );

}

CHotbar::~CHotbar() {
}
