# AtlasGUI

**AtlasGUI** is a macOS SwiftUI application that serves as a lightweight front-end to the Atlas 626 Interpreter — a legacy avionics interpreter system originally written in C++ using PCCTS. This GUI launches and communicates with the `AtlasCL` command-line tool, capturing its output and displaying it in a SwiftUI-based window.

---

## 🚀 Features

- ✅ Launches `AtlasCL` as a subprocess via `Process`
- ✅ Captures both `stdout` and `stderr` in real time
- ✅ Displays output using a clean monospaced SwiftUI interface
- ✅ Built with Swift 6 and supports macOS 14+
- ✅ Modular design for future expansion (file selection, status views, etc.)

---

## 🛠 Requirements

- macOS 14 or later (tested on Apple Silicon)
- Xcode 15+
- `AtlasCL` binary must be available at:  
  `~/bin/AtlasCL`

---

## 🧩 Project Structure

```text
AtlasGUI/
├── AtlasGUI.xcodeproj/         # Xcode project for GUI
├── AtlasGUI/                   # Swift source files
│   ├── AtlasGUIApp.swift
│   ├── ContentView.swift
│   └── PipeReader.swift
├── Assets.xcassets/            # UI icons & colors
├── Info.plist
└── README.md                   # You're reading it!
```

---

## 🔗 Relation to AtlasCL

This GUI wraps the **AtlasCL** command-line tool, which lives in a separate repository:
> GitHub: [`SinanKarasu/AtlasInterpreter`](https://github.com/SinanKarasu/AtlasInterpreter)

`AtlasCL` is expected to:
- Be independently built via CMake/make
- Be copied into `~/bin/AtlasCL` manually

---

## ⚙️ Building

From Xcode:
1. Open `AtlasGUI.xcodeproj`
2. Build & Run
3. Output from `AtlasCL` appears in the window

From Terminal:
```bash
open AtlasGUI.xcodeproj
```

---

## 🧼 TODO / Future Work

- [ ] Add file selection and input redirection
- [ ] Allow dynamic path to `AtlasCL`
- [ ] Highlight or categorize message types
- [ ] Wrap command-line arguments from GUI controls
- [ ] Support saving output or logs

---

## 🧠 Historical Context

This is part of a larger effort to modernize the original **Atlas 626 Interpreter** written in the 1990s. The CLI interpreter has been refactored into a standalone tool, and this GUI is a clean, native frontend meant to ease experimentation and visualization.

---

## 📜 License

MIT License — © Sinan Karasu
