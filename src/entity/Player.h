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

#pragma once

#include "Entity.h"
#include "../event/eventlistener.h"
#include "../utils/Vector3.h"
#include "../utils/Debug.h"
#include "PlayerInventory.h"
#include "IEquipable.h"

class CPlayer: public Entity, public IEventListener {
public:
    CPlayer();
    virtual ~CPlayer();
    void Update(float deltaSeconds);
	void AddToInventory(IEquipable& item);
    class Vector3 Move(float x, float y, float deltaTime);
	void Rotate( const Vector3& rotation );    
    virtual void OnEvent(Event event) override;

    void SetPosition( const Vector3& position ) override
    {
        Entity::SetPosition(position);        
    }

    inline bool IsPlayerSpawned()
    {
        return m_bPlayerSpawned;
    }

    inline void SetStance(double value) {  m_Stance = value; }
    inline double Stance() const {  return m_Stance; }

    inline void SetPlayerSpawned(bool value)
    {
        m_LastPlayerServerUpdate = ticks_to_millisecs(gettime());
        m_bPlayerSpawned = value;        
        LOG("Spawned player pos: %f, %f, %f Stance: %f", m_position.GetX(), m_position.GetY(), m_position.GetZ(), m_Stance);
    }

    inline bool IsOnTheGround() const
    {
        return m_bOnTheGround;
    }

    inline void SetOnTheGround(bool value)
    {
        m_bOnTheGround = value;
    }

    void SendUpdateToServer();

private:
    void UpdateInventory();
    PlayerInventory* m_pInventory;
    bool m_bPlayerSpawned = false, m_bOnTheGround = false, m_bIsPlayerJumping = false,  m_bIsFalling = false;
    float m_playerJumpOffset = 0.0f;
    double m_Stance = 0.1;
    uint64_t m_LastPlayerServerUpdate;
};
