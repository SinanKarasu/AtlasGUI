#!/bin/bash
set -e

echo "🔧 Generating sources for AtlasCL..."

# PCCTS/SMC tools expected to be installed and in $PATH
GRAMMAR_DIR="${SRCROOT}/Grammar"
FSM_DIR="${SRCROOT}/FSM"
OUT_DIR="${SRCROOT}/Generated"

mkdir -p "$OUT_DIR"

# === Example: Generate from PCCTS grammar files ===
for gfile in "$GRAMMAR_DIR"/*.g; do
  if [ -f "$gfile" ]; then
    echo "📜 Running PCCTS on $(basename "$gfile")"
    "${ANTLR}" -o "$OUT_DIR" "$gfile"  # Replace with correct PCCTS command
  fi
done

# === Example: Compile FSMs ===
for smfile in "$FSM_DIR"/*.sm; do
  if [ -f "$smfile" ]; then
    echo "⚙️  Running SMC on $(basename "$smfile")"
    "${SMC}" -d "$OUT_DIR" "$smfile"   # Adjust command/options as needed
  fi
done

echo "✅ All sources generated successfully."
