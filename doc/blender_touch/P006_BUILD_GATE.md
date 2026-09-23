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
- [x] Windows Lite build succeeds locally with Ninja (`C:\btlite\portable\blender.exe`).
- [x] Windows normal build succeeds locally with Ninja (`C:\btfull\portable\blender.exe`).
- [x] Local portable build starts with its bundled data and DLLs.
- [x] Mouse regression smoke test passes on the Galaxy Book touchpad (user-observed).
- [x] Keyboard regression smoke test passes on the Galaxy Book (`G` / `Esc`, user-observed).
- [x] Windows Ink / pen regression smoke test passes (normal interaction and stylus telemetry verified on the Galaxy Book).
- [x] Physical touchscreen smoke test passes on the target 2-in-1 device (one, two and three contacts; cancellation retested after the fix).

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

P006 is complete when both local build gates and all smoke tests above pass.
GitHub Actions is optional and runs only when manually dispatched.
Gesture implementation must not begin before this gate is green.

Hardware smoke test on September 22, 2026: the Galaxy Book reported up to three
simultaneous contacts with distinct IDs. After holding a finger and switching
windows, contact 2081 ended with `TOUCH_CANCEL` and emitted no later move or up
events. A fresh touch used ID 2082 and completed with `TOUCH_UP`. No duplicate
mouse click appeared with these contacts. Mouse, keyboard, S Pen pressure and
eraser behavior looked normal to the user. With Windows Ink selected, a focused
event probe recorded pen pressure and changing, nonzero tilt values, including
`(0.1222, 0.0778)` and `(0.0000, 0.1222)`. A separate run with Windows Ink but
without the modal probe confirmed that touchpad clicks and S Pen clicks both
work normally. The modal probe itself interfered with normal interaction, so
its apparent UI freeze is not evidence of a Blender runtime regression. A brush
response to tilt was not assessed in Object Mode; this gate verifies that tilt
data reaches Blender. Both Lite and full portable builds were rebuilt locally
with Ninja after the cancellation fix and started successfully. The full build
also passed the physical tests above. The CI Build #12 artifact predates the
fix, but an updated CI artifact is not required for this gate.

The revised sequence and completed P006 validation are recorded in
[ROADMAP.md](ROADMAP.md).
