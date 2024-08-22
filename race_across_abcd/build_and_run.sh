#!/bin/bash

# Define the source and output directories
SRC_DIR="/Users/jaecho01/Library/CloudStorage/OneDrive-Arm/Documents/ARMageddon/race_across_abcd"
OUTPUT_DIR="$SRC_DIR/output"
SOURCE_FILE="race.cpp"
EXECUTABLE="race"

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

# Compile the source file
g++ -Wall -Wextra -g3 -std=c++17 "$SRC_DIR/$SOURCE_FILE" -o "$OUTPUT_DIR/$EXECUTABLE"

# Check if compilation was successful
if [ $? -eq 0 ]; then
  echo "Compilation successful. Running the executable..."
  # Run the executable
  "$OUTPUT_DIR/$EXECUTABLE"
else
  echo "Compilation failed."
fi
