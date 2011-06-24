/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#ifndef HIGH_PRECISION_H
#define HIGH_PRECISION_H

#include <stdint.h>
#include "ns3/simulator-config.h"

#if defined (USE_HIGH_PRECISION_DOUBLE)
#include "high-precision-double.h"
#elif defined (USE_HIGH_PRECISION_128)
#include "high-precision-128.h"
#elif defined (USE_HIGH_PRECISION_CAIRO)
#include "high-precision-cairo.h"
#endif

namespace ns3 {

HighPrecision Abs (HighPrecision const &value);
inline HighPrecision Max (HighPrecision const &a, HighPrecision const &b);
inline HighPrecision Min (HighPrecision const &a, HighPrecision const &b);


inline HighPrecision Max (HighPrecision const &a, HighPrecision const &b)
{
  if (a.Compare (b) >= 0)
    {
      return a;
    }
  else
    {
      return b;
    }
}
inline HighPrecision Min (HighPrecision const &a, HighPrecision const &b)
{
  if (a.Compare (b) <= 0)
    {
      return a;
    }
  else
    {
      return b;
    }
}

} /* namespace ns3 */

#endif /* HIGH_PRECISION_H */
