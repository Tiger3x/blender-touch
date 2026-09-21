/* SPDX-FileCopyrightText: 2026 Tiger3x. All rights reserved. */

/** \file
 * \ingroup GHOST
 *
 * Touch event data definitions for Blender Touch.
 */

#pragma once

#include "GHOST_ITouchDevice.hh"

/** Data transported by touch events. */
struct GHOST_TTouchEventData {
  GHOST_TTouchPhase phase = GHOST_kTouchDown;
  GHOST_TouchContact contact;

  /** Number of active contacts in the gesture. */
  uint32_t contact_count = 1;
};
