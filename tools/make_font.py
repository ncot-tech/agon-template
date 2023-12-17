#!/usr/bin/env python3

import argparse
from PIL import Image
import os

fontname = ""

def convert_to_2222(image, filename):

    width, height = image.size
    pixel_depth = image.mode

    print(f"Pixel Depth: {pixel_depth}")

    # Extract pixel data
    pixel_data = list(image.getdata())

    # Convert pixel data to RGB2222 format
    rgb2222_data = bytearray()
    for pixel in pixel_data:
        r, g, b, a = pixel
        pixel_value = ((r >> 6) & 0x03 | (((g >> 6) & 0x03) << 2) | (((b >> 6) & 0x03) << 4) | (((a >> 6) & 0x03) << 6))
        rgb2222_data.append(pixel_value)

    # Save the RGB2222 data to a binary file
    output_filename, _ = os.path.splitext(filename)
    output_filename += ".222"
    with open(output_filename, 'wb') as f:
        f.write(b"NCOTB")
        f.write(width.to_bytes(2, 'little'))
        f.write(height.to_bytes(2, 'little'))
        f.write((1).to_bytes(1, 'little'));
        f.write(rgb2222_data)

    print(f"RGB2222 data saved to '{output_filename}'")


def get_filename_without_extension(file_path):
    base_name = os.path.basename(file_path)
    filename, _ = os.path.splitext(base_name)
    return filename

def slice_image(input_image_path, output_directory, slice_width, slice_height):
    original_image = Image.open(input_image_path)
    # Quantize to 64 colours
    original_image = original_image.point(lambda p: p // 85 * 85)
    width, height = original_image.size
    count = 0  # Initialize the count

    for y in range(0, height, slice_height):
        for x in range(0, width, slice_width):
            box = (x, y, x + slice_width, y + slice_height)
            slice = original_image.crop(box)
            output_path = os.path.join(output_directory, f"{fontname}_{count:02}.png")  # Use count for naming
            convert_to_2222(slice, output_path)
            slice.save(output_path)
            count += 1  # Increment the count

    # Write a definition file to go with it
    data_file = os.path.join(output_directory, f"{fontname}.dat");
    with open(data_file, 'wb') as f:
        f.write(b"NCOTF")
        f.write(len(fontname).to_bytes(2, 'little'))  # How long the fontname is
        f.write(fontname.encode('ascii')) # Not null terminated
        f.write(count.to_bytes(1, 'little'))
        f.write(slice_width.to_bytes(1, 'little'))
        f.write(slice_height.to_bytes(1, 'little'))

def main():
    global fontname
    parser = argparse.ArgumentParser(description="Slice a PNG image of a font into regular-sized pieces and a datafile.")
    parser.add_argument("input_image", help="Path to the input PNG image.")
    parser.add_argument("slice_width", type=int, help="Width of each character in pixels")
    parser.add_argument("slice_height", type=int, help="Height of each character in pixels")
    args = parser.parse_args()

    input_image_path = args.input_image
    fontname = get_filename_without_extension(input_image_path)
    output_directory = f"{fontname}"
    slice_width = int(args.slice_width)
    slice_height = int(args.slice_height)

    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)

    slice_image(input_image_path, output_directory, slice_width, slice_height)

if __name__ == "__main__":
    main()
