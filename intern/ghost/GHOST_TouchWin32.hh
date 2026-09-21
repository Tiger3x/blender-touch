/* SPDX-FileCopyrightText: 2026 Tiger3x. All rights reserved. */

/** \file
 * \ingroup GHOST
 *
 * Windows touch backend abstraction for Blender Touch.
 *
 * This file intentionally keeps native Windows pointer handling separated
 * from the generic GHOST touch event layer.
 */

#pragma once

#include "GHOST_ITouchDevice.hh"

/**
 * Windows touch device bridge.
 *
 * The platform implementation will translate WM_POINTER messages into
 * GHOST touch events in a later stage.
 */
class GHOST_WindowsTouchDevice : public GHOST_ITouchDevice {
 public:
  bool isTouchSupported() const override;

  /** Enable native Windows touch processing. */
  void initialize();
};
