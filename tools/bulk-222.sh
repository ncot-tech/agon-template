#!/bin/bash

# Check if the directory argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Set the directory from the command line argument
directory="$1"

# Check if the specified directory exists
if [ ! -d "$directory" ]; then
    echo "Directory '$directory' does not exist."
    exit 1
fi

# Iterate over files in the directory
for file in "$directory"/*; do
    # Check if the item is a file (not a directory)
    if [ -f "$file" ]; then
        # Run your program with the current file
        ./png2rgb.py "$file"
    fi
done

