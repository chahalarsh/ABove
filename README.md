# ABove (Beta Preview)

**ABove** is a minimalist Windows utility that lets you pin any window **Always on Top** using a hotkey.  
It is designed to consume **very few system resources** and run silently in the background.

```
  This is just a Beta Preview and is not yet a final product.
```

## Features

- Toggle **Always on Top** for the currently focused window
- Global hotkey support
- No GUI, no tray icon, no background polling
- Near-zero CPU usage when idle
- Extremely lightweight
- Supports **Windows 10 and Windows 11**


## Default Hotkey

`Alt + T`

- Press once to pin the active window
- Press again to unpin it


## How It Works

ABove uses a pure Win32 approach:

- Registers a global hotkey using `RegisterHotKey`
- Waits for events using a standard message loop (`GetMessage`)
- Detects the foreground window
- Toggles the `WS_EX_TOPMOST` flag using `SetWindowPos`

There are:
- No keyboard hooks
- No background threads
- No timers

This ensures maximum efficiency and stability.

## Build Instructions (MinGW)

### Requirements
- MinGW (GCC)
- Windows 10 or Windows 11

### Compile

```
g++ Above_sourceCode.cpp -mwindows -O2 -o ABove.exe
```
  - mwindows builds a GUI application (no console window)
  - O2 enables compiler optimizations

### Usage
  1. Run ABove.exe
  2. Focus the window you want to pin
  3. Press Alt + T
  4. Press Alt + T again to remove Always-on-Top

The application runs silently in the background.

### Limitations
  - No visual indicator (by design)
  - Hotkey is hardcoded

Known limitations are work under progress.


## Philosophy
ABove follows a minimalist, single-purpose design:
- One feature
- Minimal code
- Minimal resource usage
- No unnecessary UI or complexity
