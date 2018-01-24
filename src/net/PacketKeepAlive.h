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

#ifndef PACKETKEEPALIVE_H
#define PACKETKEEPALIVE_H

#include "Packet.h"

class PacketKeepAlive : public Packet
{
public:
    PacketKeepAlive(int32_t id = 0) : Packet(PACKET_KEEP_ALIVE), m_ID(id) {}
protected:
    void SendContent(const Session& session) override
    {
        session.SendUInt(m_ID);
    }
private:
    int32_t m_ID = 0;
};

#endif // PACKETKEEPALIVE_H
