/*
 *
 * Secure BATMAN Ring Buffer Class
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */

#include "secure-ring-buffer.h"
#include "ns3/log.h"

#define GLOBAL_WINDOW_SIZE				10

NS_LOG_COMPONENT_DEFINE ("SecureRingBuffer");

void sec_ring_buffer_set(uint8_t tq_recv[], uint8_t *tq_index, uint8_t value)
{
//	NS_LOG_DEBUG("old m_index: " << (uint16_t)*tq_index);
	tq_recv[*tq_index] = value;
	*tq_index = (*tq_index + 1) % GLOBAL_WINDOW_SIZE;
//	NS_LOG_DEBUG("new m_index: " << (uint16_t)*tq_index);
}

uint8_t sec_ring_buffer_avg(uint8_t tq_recv[])
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
