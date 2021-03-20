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
 * @file telephone_event.h
 * @author mayamatakeshi@gmail.com
 *
 * @brief Functions parse RFC4733 RTP packets
 *
 *
 */

#ifndef __SNGREP_TELEPHONE_EVENT_H
#define __SNGREP_TELEPHONE_EVENT_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdint.h>
#include <arpa/inet.h>

/**
 * @brief Extracts RFC4733 event code
 *
 * @param payload
 * @param payload_len
 * @param end : pointer to receive value of end
 * @return event code or -1 on error
 */

int
telephone_event_get_code(const u_char *payload, uint32_t payload_len, bool *end);


/**
 * @brief Parse RFC4733 RTP packet payload
 *
 * @param buf
 * @param buf_len
 * @param payload
 * @param payload_len
 * @return true if parse was successful
 */
bool
telephone_event_parse(char *buf, size_t buf_len, const u_char *payload, uint32_t payload_len, bool *end, uint8_t *volume, uint16_t *duration);

#endif /* __SNGREP_TELEPHONE_EVENT_H */
