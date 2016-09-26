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

#include "Player.h"
#include "../utils/MathHelper.h"
#include "../utils/Debug.h"

#define ROTATION_SPEED 1.4f
#define MOVEMENT_SPEED 0.1f
#define PITCH_MAX 90.0f

#ifdef DEBUG
	char* pChunkBuffer = NULL;
#endif


Player::Player()
{
	m_entityRenderer = new EntityRenderer(this);
	m_inventory = new CPlayerInventory();
	SetPlayer(true);
#ifdef DEBUG
	pChunkBuffer = new char[50];
#endif
}

Player::~Player()
{
	delete m_inventory;
}



void Player::Update()
{
	WiiPad* pad = Controller::GetInstance().GetInputHandler().GetPadByID( WII_PAD_0 );

	u32 padButtonHeld = pad->ButtonsHeld();
	u32 padButtonDown = pad->ButtonsDown();

#ifdef DEBUG
	auto pChunk = m_pWorld->GetChunkByWorldPosition( m_position );
	if ( pChunk )
	{
		sprintf(pChunkBuffer, "Current Chunk: %d/%d/%d", (unsigned int) pChunk->GetCenterPosition().GetX(), (unsigned int) pChunk->GetCenterPosition().GetY(), (unsigned int) pChunk->GetCenterPosition().GetZ() );
		Debug::GetInstance().Log( pChunkBuffer );
	}
#endif


	if ( pad->GetY() <= 15.0f )
	{
		this->Rotate( Vector3f( -ROTATION_SPEED, 0, 0 )); // top
	}
	else if ( pad->GetY() >= rmode->viHeight - 45.0f )
	{
		this->Rotate( Vector3f( ROTATION_SPEED, 0, 0 )); // bottom
	}

	if ( pad->GetX() >= rmode->viWidth - 120.0f )
	{
		this->Rotate( Vector3f( 0, -ROTATION_SPEED, 0 )); // right
	}
	else if ( pad->GetX() <= 120.0f )
	{
		this->Rotate( Vector3f( 0, ROTATION_SPEED, 0 )); // left
	}

	if ( padButtonHeld & WPAD_BUTTON_UP )
	{
		MoveForward();
	}
	if ( padButtonHeld & WPAD_BUTTON_DOWN )
	{
		MoveBackward();
	}
	if ( padButtonHeld & WPAD_BUTTON_LEFT )
	{
		MoveLeft();
	}
	if ( padButtonHeld & WPAD_BUTTON_RIGHT )
	{
		MoveRight();
	}

	Vector3f blockPositionUnderPlayer(m_position.GetX() + BLOCK_SIZE, 0.0f, m_position.GetZ() + BLOCK_SIZE);
	Vector3f newPosition = m_pWorld->GetNewPlayerPosition(blockPositionUnderPlayer);
	m_position.SetY(newPosition.GetY() + 2.0f);

	auto focusedBlockPos = MathHelper::CalculateNewWorldPositionByRotation(
							Vector3f(m_rotation.GetX(), m_rotation.GetY(), m_rotation.GetZ()),
							Vector3f(m_position.GetX() + BLOCK_SIZE, m_position.GetY(), m_position.GetZ() + BLOCK_SIZE),
							ROTATION_SPEED,
							Vector3f::Forward());


	m_pWorld->UpdateFocusedBlockByWorldPosition(focusedBlockPos);

	if ( padButtonDown & WPAD_BUTTON_B)
	{
		m_pWorld->RemoveBlockByWorldPosition( focusedBlockPos );
	}

	if ( padButtonDown & WPAD_BUTTON_A)
	{
		m_pWorld->AddBlockAtWorldPosition(focusedBlockPos, BlockType::DIRT );
	}

	if ( padButtonDown & WPAD_BUTTON_HOME)
	{
		Controller::GetInstance().End();
	}
}



void Player::MoveForward()
{
	m_position = MathHelper::CalculateNewWorldPositionByRotation(
			m_rotation.GetY(),
			m_position,
			MOVEMENT_SPEED,
			Vector3f::Forward());
}

void Player::MoveBackward()
{
	m_position = MathHelper::CalculateNewWorldPositionByRotation(
				m_rotation.GetY(),
				m_position,
				MOVEMENT_SPEED,
				Vector3f::Backward());
}

void Player::MoveLeft()
{
	m_position = MathHelper::CalculateNewWorldPositionByRotation(
					m_rotation.GetY() - 90,
					m_position,
					MOVEMENT_SPEED,
					Vector3f::Backward());

}

void Player::MoveRight()
{

	m_position = MathHelper::CalculateNewWorldPositionByRotation(
						m_rotation.GetY() + 90,
						m_position,
						MOVEMENT_SPEED,
						Vector3f::Backward());

}


void Player::Rotate( Vector3f rotation )
{
	if ( m_rotation.GetX() > 360 )
	{
		m_rotation.SetX(m_rotation.GetX() - 360);
	}
	else if(m_rotation.GetX() < -360)
	{
		m_rotation.SetX(m_rotation.GetX() + 360);
	}

	if ( m_rotation.GetY() > 360 )
	{
		m_rotation.SetY(m_rotation.GetY() - 360);
	}
	else if(m_rotation.GetY() < -360)
	{
		m_rotation.SetY(m_rotation.GetY() + 360);
	}

	if ( m_rotation.GetZ() > 360 )
	{
		m_rotation.SetZ(m_rotation.GetZ() - 360);
	}
	else if(rotation.GetZ() < -360)
	{
		m_rotation.SetZ(m_rotation.GetZ() + 360);
	}

	m_rotation.SetX( MathHelper::Clamp(m_rotation.GetX() + rotation.GetX(), -PITCH_MAX, PITCH_MAX));
	m_rotation.SetY( m_rotation.GetY() + rotation.GetY() );
	m_rotation.SetZ( m_rotation.GetZ() + rotation.GetZ() );

}

void Player::AddToInventory(IEquipable& item)
{
	m_inventory->AddToInventory(item);
}
