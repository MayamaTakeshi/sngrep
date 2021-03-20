/**************************************************************************
 **
 ** sngrep - SIP Messages flow viewer
 **
 ** Copyright (C) 2013-2018 Ivan Alonso (Kaian)
 ** Copyright (C) 2013-2018 Irontec SL. All rights reserved.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
/**
 * @file telephone_event.c
 * @author mayamatakeshi@gmail.com
 *
 * @brief Functions to parse RFC4733 RTP packets
 *
 */

#include "telephone_event.h"
#include <stdio.h>

int
telephone_event_get_code(const u_char *payload, uint32_t payload_len, bool *end) {
    if(payload_len < 12) return -1;

    u_char v = payload[0] >> 6;
    if(v != 2) return -1;

    u_char cc = 0x0F & payload[0];

    int offset = 12 + (cc * 4);

    if(payload_len < offset + 4) return -1;

    int evt = payload[offset];

    *end = payload[offset+1] >> 7;

    return evt;
}

bool
telephone_event_parse(char *buf, size_t buf_len, const u_char *payload, uint32_t payload_len, bool *end, uint8_t *volume, uint16_t *duration) {
    if(payload_len < 12) {
        snprintf(buf, buf_len, "TelEvt (pkt too short)");
        return false;
    }

    u_char v = payload[0] >> 6;
    if(v != 2) {
        snprintf(buf, buf_len, "TelEvt (wrong RTP version)");
        return false;
    }

    u_char cc = 0x0F & payload[0];

    int offset = 12 + (cc * 4);

    if(payload_len < offset + 4) {
        snprintf(buf, buf_len, "TelEvt (pkt too short)");
        return false;
    }

    int evt = payload[offset];
    if(evt > 15) {
        snprintf(buf, buf_len, "TelEvt Unknown");
        return false;
    }

    *end = payload[offset+1] >> 7;

    u_char c;

    if(evt < 10) {
        c = '0' + evt;
    } else if(evt == 10) {
        c = 0x2a;
    } else if(evt == 11) {
        c = 0x23;
    } else {
        c = 'A' - 12 + evt;
    }
   
    if(*end) {
        snprintf(buf, buf_len, "TelEvt DTMF:%c (end)", c);
    } else {
        snprintf(buf, buf_len, "TelEvt DTMF:%c", c);
    }

    *volume = payload[offset+1] & 0x3F;

    *duration = ntohs(payload[offset+2]);

    return true;
}

