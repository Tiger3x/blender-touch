/* SPDX-FileCopyrightText: 2026 Tiger3x. All rights reserved. */

/** \file
 * \ingroup GHOST
 *
 * Touch event identifiers for Blender Touch.
 */

#pragma once

/**
 * Touch events are kept separate initially so platform backends can be
 * integrated without changing existing mouse/keyboard event behavior.
 */
enum GHOST_TTouchEventType {
  GHOST_kEventTouchDown = 0,
  GHOST_kEventTouchMove,
  GHOST_kEventTouchUp,
  GHOST_kEventTouchCancel,
};
