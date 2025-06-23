# AtlasCL Parallel Development Notes (README\_DEV.md)

This guide explains how to develop AtlasCL using two synchronized workflows:

1. The **Makefile-based command-line build** ("AtlasCL-Makefile")
2. The **Xcode-based GUI project** ("AtlasCL")

Both build systems operate on the **same source tree** and should produce the **same output binary**: `bin/AtlasCL`.

---

## 📁 Project Structure

```
AtlasGUI/
├── AtlasCL/                        # Xcode project and sources
│   ├── AtlasCL.xcodeproj/         # Xcode GUI project
│   └── Sources/, Include/, ...    # Shared sources
├── AtlasCL-Makefile.xcodeproj/    # External build system project
├── DevTools/                      # ANTLR, dlg, smc toolchain
├── Makefile                       # Root Makefile for CLI builds
└── bin/AtlasCL                    # Output binary (same for both)
```

---

## 🛠 Makefile Build (AtlasCL-Makefile)

- Run `make -j 20` from the top-level `AtlasGUI` folder.
- Generates all `.cc`, `.h`, and `.o` files.
- Builds the binary in `bin/AtlasCL`.
- Supports `clean` and `scrub` targets.

### Example:

```sh
cd AtlasGUI
make -j 20      # Fast parallel build
make clean      # Remove .o files and binary
make scrub      # Also remove generated .cc/.h files
```

---

## 🧪 Xcode Build (AtlasCL.xcodeproj)

- Located in `AtlasGUI/AtlasCL/AtlasCL.xcodeproj`
- Uses the **same source and generated folders** as the Makefile
- Run `make -j 20` automatically via a **pre-build Run Script Phase**

### Add a Run Script Build Phase

In Xcode, select the `AtlasCL` target → **Build Phases** → **+ Run Script**:

```sh
make -C "${SRCROOT}/.." -j 20
```

This ensures that the grammar and state machine outputs exist before Xcode tries to compile.

---

## 🧼 Git Hygiene

- `.gitignore` excludes:
  - `bin/`
  - `*.o`, `DerivedData`, and other intermediates
- Keep your Xcode workspace files clean — only commit meaningful `.xcodeproj` changes.

---

## ⚠️ Gotchas

- Do **not** open both Xcode projects (`AtlasCL` and `AtlasCL-Makefile`) in different windows simultaneously
- You **can** switch between them — just don’t edit `.xcodeproj` files at the same time
- If something gets messed up: `git restore`, or blow away and unzip from backup zip

---

## 🤝 Sync Strategy

At day’s end, ensure:

- Any source changes are reflected in both Makefile and Xcode usage
- Both builds produce a working `bin/AtlasCL`
- Run `make scrub` if switching to a clean rebuild from CLI

---

## 👨‍💻 Legacy Note

This setup is designed to support future migration to a unified Swift workspace or a SwiftPM package.

---

## 🧭 Reference Commands

```sh
# Fast full build
make -j 20

# Remove binary and all objects
make clean

# Also remove generated .cc/.h
make scrub

# Check what's changed
git status

# Add everything staged and untracked
git add -u . && git add .

# Commit
git commit -m "Synced Xcode and Makefile build systems"
```

Happy hacking — and yes, your past self will thank you.

