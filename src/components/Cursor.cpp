/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#include "Engine.h"
#include "components/Cursor.h"
#include "utils/Debug.h"


Cursor::Cursor( const char* name, Sprite* sprite ) : UiTextureElement( 0, 0, name, sprite )
{
	SetX( rmode->viWidth / 2 );
	SetY( rmode->viHeight / 2 );
}


Cursor::~Cursor() {}

void Cursor::Update()
{
    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID( WII_PAD_0 );
	SetX( pad->GetX());
	SetY( pad->GetY());
}
