#!/usr/bin/env python3

import sys, os, image_conv, io

def get_filename_without_extension(file_path):
    base_name = os.path.basename(file_path)
    filename, _ = os.path.splitext(base_name)
    return filename

# Check if the correct number of command line arguments is provided
if len(sys.argv) != 3:
    print("Usage: python png2rgb.py <input_image.png> <output_folder>")
else:
    # Get the input filename from the command line argument
    input_filename = sys.argv[1]
    output_folder = sys.argv[2]

    converted_image = image_conv.convert_file_to_2222(input_filename)

    output_filename = output_folder + "/" + get_filename_without_extension(input_filename) + ".222"

    with open(output_filename, 'wb') as f:
        f.write(converted_image.getvalue())

