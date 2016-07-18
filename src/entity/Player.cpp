/*
 * Player.cpp
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#include "Player.h"
#include "../utils/MathHelper.h"
#include "../utils/Debug.h"

#define ROTATION_SPEED 1.4f
#define MOVEMENT_SPEED 0.3f
#define PITCH_MAX 80.0f

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
	delete m_entityRenderer;
	delete m_inventory;
}



void Player::update()
{
	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

	u32 padButtonHeld = pad->buttonsHeld();
	u32 padButtonDown = pad->buttonsDown();

#ifdef DEBUG
	auto pChunk = m_pWorld->GetChunkByWorldPosition( m_position );
	if ( pChunk )
	{
		sprintf(pChunkBuffer, "Current Chunk: %d/%d/%d", (unsigned int) chunk->GetCenterPosition().GetX(), (unsigned int) chunk->GetCenterPosition().GetY(), (unsigned int) chunk->GetCenterPosition().GetZ() );
		Debug::getInstance().log( pChunkBuffer );
	}
#endif


	if ( pad->getY() <= 15.0f )
	{
		this->rotate( Vector3f( -ROTATION_SPEED, 0, 0 )); // top
	}
	else if ( pad->getY() >= rmode->viHeight - 45.0f )
	{
		this->rotate( Vector3f( ROTATION_SPEED, 0, 0 )); // bottom
	}

	if ( pad->getX() >= rmode->viWidth - 120.0f )
	{
		this->rotate( Vector3f( 0, -ROTATION_SPEED, 0 )); // right
	}
	else if ( pad->getX() <= 120.0f )
	{
		this->rotate( Vector3f( 0, ROTATION_SPEED, 0 )); // left
	}

	if ( padButtonHeld & WPAD_BUTTON_UP )
	{
		moveForward();
	}
	if ( padButtonHeld & WPAD_BUTTON_DOWN )
	{
		moveBackward();
	}
	if ( padButtonHeld & WPAD_BUTTON_LEFT )
	{
		moveLeft();
	}
	if ( padButtonHeld & WPAD_BUTTON_RIGHT )
	{
		moveRight();
	}

	if ( padButtonDown & WPAD_BUTTON_B)
	{
		auto blockPos = MathHelper::calculateNewWorldPositionByRotation(
					m_rotation.GetY(),
					Vector3f(m_position.GetX() + .5f, m_position.GetY(), m_position.GetZ() + .5f),
					ROTATION_SPEED,
					Vector3f::Forward());

		m_pWorld->RemoveBlockByWorldPosition( Vector3f( blockPos.GetX(), m_position.GetY() - 2, blockPos.GetZ() ));
	}

	if ( padButtonDown & WPAD_BUTTON_HOME )
	{
		Controller::getInstance().end();
	}

}



void Player::moveForward()
{
	m_position = MathHelper::calculateNewWorldPositionByRotation(
			m_rotation.GetY(),
			m_position,
			MOVEMENT_SPEED,
			Vector3f::Forward());
}

void Player::moveBackward()
{
	m_position = MathHelper::calculateNewWorldPositionByRotation(
				m_rotation.GetY(),
				m_position,
				MOVEMENT_SPEED,
				Vector3f::Backward());
}

void Player::moveLeft()
{
	m_position = MathHelper::calculateNewWorldPositionByRotation(
					m_rotation.GetY() - 90,
					m_position,
					MOVEMENT_SPEED,
					Vector3f::Backward());

}

void Player::moveRight()
{

	m_position = MathHelper::calculateNewWorldPositionByRotation(
						m_rotation.GetY() + 90,
						m_position,
						MOVEMENT_SPEED,
						Vector3f::Backward());

}


void Player::rotate( Vector3f rotation )
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
