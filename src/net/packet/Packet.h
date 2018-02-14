/***
 *
 * Copyright (C) 2018 DaeFennek
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

#ifndef PACKET_H
#define PACKET_H

#include <cstring>
#include <vector>
#include <cstdio>
#include "../Session.h"

struct SlotData
{
    int16_t BlockID;
    char ItemCount;
    int16_t ItemDamage;
    char NBT;
};


class Packet
{
public:
    Packet(unsigned char id) : m_ID(id) {}
    virtual ~Packet() {}
    void Send() const;
    virtual void Read(const Session& session) = 0;
    virtual void Action() = 0;
    virtual Packet* CreateInstance() const = 0;
protected:
    virtual void SendContent(const Session& session) const = 0;

    void ReadSlotData(std::vector<SlotData>& slotData, int16_t count, const Session& session) const
    {
        slotData.clear();
        SlotData data;
        for (int16_t i = 0; i < count; ++i)
        {
            ReadSlotData(data, session);
            slotData.emplace_back(data);
        }
    }

    void ReadSlotData(SlotData& data, const Session& session) const
    {
        memset(&data, 0, sizeof(data));
        data.BlockID = session.Read<int16_t>();
        if (data.BlockID != -1)
        {
            data.ItemCount = session.Read<char>();
            data.ItemDamage = session.Read<int16_t>();
            data.NBT = session.Read<char>(); // todo handle nbt correctly
        }
    }

    char m_ID;

};

#endif // PACKET_H
