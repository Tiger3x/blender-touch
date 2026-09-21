/* SPDX-FileCopyrightText: 2026 Tiger3x. All rights reserved. */

/** \file
 * \ingroup GHOST
 *
 * Initial touch input abstraction for Blender Touch.
 */

#pragma once

#include <cstdint>

/**
 * Basic touch contact information.
 *
 * This first implementation intentionally keeps the platform layer simple.
 * Backends can translate native touch APIs into this structure.
 */
struct GHOST_TouchContact {
  uint64_t id = 0;
  float x = 0.0f;
  float y = 0.0f;
  float pressure = 1.0f;
};

/** Touch contact lifecycle. */
enum GHOST_TTouchPhase {
  GHOST_kTouchDown = 0,
  GHOST_kTouchMove,
  GHOST_kTouchUp,
  GHOST_kTouchCancel,
};

/**
 * Interface placeholder for future native touch devices.
 *
 * The goal is to keep Windows Pointer API, Apple Touch and Linux tablet
 * backends independent from Blender event handling.
 */
class GHOST_ITouchDevice {
 public:
  virtual ~GHOST_ITouchDevice() = default;

  virtual bool isTouchSupported() const = 0;
};
