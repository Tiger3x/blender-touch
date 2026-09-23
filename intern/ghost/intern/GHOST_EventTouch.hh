/* SPDX-FileCopyrightText: 2026 Blender Touch contributors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup GHOST
 * Declaration of GHOST_EventTouch class.
 */

#pragma once

#include "GHOST_Event.hh"

/** Native multi-touch contact event. */
class GHOST_EventTouch : public GHOST_Event {
 public:
  GHOST_EventTouch(uint64_t msec,
                   GHOST_TEventType type,
                   GHOST_IWindow *window,
                   const GHOST_TEventTouchData &touch_data)
      : GHOST_Event(msec, type, window), touch_event_data_(touch_data)
  {
    data_ = &touch_event_data_;
  }

 protected:
  GHOST_TEventTouchData touch_event_data_;
};
