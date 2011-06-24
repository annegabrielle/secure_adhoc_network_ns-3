/*
 * Copyright (C) 2007-2009 B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */



#include "ring-buffer.h"
#include "ns3/log.h"

#define GLOBAL_WINDOW_SIZE				10

NS_LOG_COMPONENT_DEFINE ("RingBuffer");

void ring_buffer_set(uint8_t tq_recv[], uint8_t *tq_index, uint8_t value)
{
//	NS_LOG_DEBUG("old m_index: " << (uint16_t)*tq_index);
	tq_recv[*tq_index] = value;
	*tq_index = (*tq_index + 1) % GLOBAL_WINDOW_SIZE;
//	NS_LOG_DEBUG("new m_index: " << (uint16_t)*tq_index);
}

uint8_t ring_buffer_avg(uint8_t tq_recv[])
{
	uint8_t *ptr;
	uint16_t count = 0, i = 0;
	uint32_t sum = 0;

	ptr = tq_recv;

	while (i < GLOBAL_WINDOW_SIZE) {

		if (*ptr != 0) {
			count++;
//			NS_LOG_DEBUG((uint16_t)*ptr);
			sum += *ptr;
		}

		i++;
		ptr++;

	}

	if (count == 0)
		return 0;

//	NS_LOG_DEBUG("AVG: " << (sum / count));
	return (uint8_t)(sum / count);
}
