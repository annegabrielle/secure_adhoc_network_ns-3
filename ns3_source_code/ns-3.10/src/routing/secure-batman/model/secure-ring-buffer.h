/*
 *
 * Secure BATMAN Bit Array Class
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */

#include <stdint.h>
#include "secure-batman-rtable.h"



void sec_ring_buffer_set(uint8_t tq_recv[], uint8_t *tq_index, uint8_t value);
uint8_t sec_ring_buffer_avg(uint8_t tq_recv[]);
