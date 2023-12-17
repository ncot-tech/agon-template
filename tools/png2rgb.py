#!/usr/bin/env python3

import sys, os
from PIL import Image

# Check if the correct number of command line arguments is provided
if len(sys.argv) != 2:
    print("Usage: python script.py <input_image.png>")
else:
    # Get the input filename from the command line argument
    input_filename = sys.argv[1]

    # Open the input PNG file
    try:
        image = Image.open(input_filename)

        # Get image size
        width, height = image.size

        
        # Convert the image to RGB2222 format
#        image = image.convert('RGB')

        # Quantize the image down to 64 colours
        image = image.point(lambda p: p // 85 * 85)

        pixel_depth = image.mode

        print(f"Pixel Depth: {pixel_depth}")

        image.save(f"64{input_filename}")
        # Extract pixel data
        pixel_data = list(image.getdata())

        # Convert pixel data to RGB2222 format
        rgb2222_data = bytearray()
        for pixel in pixel_data:
            r, g, b, a = pixel
            pixel_value = ((r >> 6) & 0x03 | (((g >> 6) & 0x03) << 2) | (((b >> 6) & 0x03) << 4) | (((a >> 6) & 0x03) << 6))
            rgb2222_data.append(pixel_value)

        # Save the RGB2222 data to a binary file
        output_filename, _ = os.path.splitext(input_filename)
        output_filename += ".222"
        with open(output_filename, 'wb') as f:
            f.write(b"NCOTB")
            f.write(width.to_bytes(2, 'little'))
            f.write(height.to_bytes(2, 'little'))
            f.write((1).to_bytes(1, 'little'));
            f.write(rgb2222_data)

        print(f"RGB2222 data saved to '{output_filename}'")

    except FileNotFoundError:
        print(f"Error: File '{input_filename}' not found.")
    except Exception as e:
        print(f"Error: {e}")

