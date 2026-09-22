# P006 — Integration & Build Gate

P006 is the hard gate between the Blender Touch input foundation and gesture work.

## Goal

Prove that the native touch foundation is integrated into Blender without regressing existing input.

## Required gates

- [x] Touch lifecycle lives in the official GHOST event type system.
- [x] Touch event payload is owned safely across the GHOST -> Window Manager boundary.
- [x] Touch event implementation is registered in GHOST CMake sources.
- [x] Win32 PT_TOUCH is separated from PT_PEN and PT_MOUSE.
- [x] Multiple contacts keep stable pointer IDs and per-window active-contact state.
- [x] Windows compatibility mouse promotion is suppressed for handled touch input.
- [x] Cancellation is handled for native cancel flags, pointer-capture loss, window deactivation and display changes.
- [x] Raw touch events reach wmEvent as TOUCHDOWN / TOUCHMOVE / TOUCHUP / TOUCHCANCEL.
- [x] Raw touch events do not mutate the persistent mouse cursor state.
- [x] RNA and event debug output know the new touch event types.
- [x] Keymap infrastructure classifies raw touch as pointing-device input.
- [x] Windows Lite build succeeds ([Build #12](https://github.com/Tiger3x/blender-touch/actions/runs/35758654170); also verified locally with Ninja).
- [x] Windows normal build succeeds ([Build #12](https://github.com/Tiger3x/blender-touch/actions/runs/35758654170); also verified locally with Ninja and a headless startup test).
- [x] Portable artifact is published by CI (`Blender-Touch-Windows-x64-P006-12`).
- [ ] Mouse regression smoke test passes.
- [ ] Keyboard regression smoke test passes.
- [ ] Windows Ink / pen regression smoke test passes.
- [ ] Physical touchscreen smoke test passes on the target 2-in-1 device.

## Windows validation commands

From a Visual Studio-capable Windows checkout:

```bat
git checkout feature/touch-input-layer
make.bat update
make.bat lite
```

After Lite succeeds, run the normal build:

```bat
make.bat
```

## Runtime smoke test

Run Blender with event debugging enabled and verify:

1. Mouse movement/clicks behave exactly as upstream.
2. Keyboard shortcuts behave exactly as upstream.
3. Pen still reports stylus/eraser, pressure and tilt.
4. One finger produces TOUCHDOWN -> TOUCHMOVE* -> TOUCHUP.
5. Two or more fingers retain distinct contact IDs.
6. Cancelled contacts emit TOUCHCANCEL and do not remain active.
7. A touchscreen contact does not also create a duplicate mouse click.

## Exit criterion

P006 is complete only when both build gates and all smoke tests above pass.
Gesture implementation must not begin before this gate is green.

The revised sequence and the distinction between completed build gates and
pending hardware validation are recorded in [ROADMAP.md](ROADMAP.md).
