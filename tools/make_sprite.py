#!/usr/bin/env python3

import argparse
from PIL import Image
import image_conv
import os, json, io

spritename = ""

def get_filename_without_extension(file_path):
    base_name = os.path.basename(file_path)
    filename, _ = os.path.splitext(base_name)
    return filename

def slice_image(input_image_path, slice_width, slice_height):
    original_image = Image.open(input_image_path)
    # Quantize to 64 colours
    original_image = original_image.point(lambda p: p // 85 * 85)
    width, height = original_image.size

    buff = io.BytesIO()

    for y in range(0, height, slice_height):
        for x in range(0, width, slice_width):
            box = (x, y, x + slice_width, y + slice_height)
            slice = original_image.crop(box)
            image_data = image_conv.convert_imagedata_to_2222(slice)
            buff.write(image_data.getvalue())

    return buff

def main():
    global spritename
    parser = argparse.ArgumentParser(description="Convert an Aseprite json file and spritesheet into sprites.")
    parser.add_argument("input_json", help="Path to the input json file.")
    parser.add_argument("output_folder", help="Path to the output folder.")
    args = parser.parse_args()

    input_json_path = args.input_json
    source_dir = os.path.dirname(input_json_path)
    spritename = get_filename_without_extension(input_json_path)
    output_directory = args.output_folder
    
    with open(input_json_path, 'r') as file:
        json_data = json.load(file)
    
    sprite_image_filename = source_dir + "/" + json_data["meta"]["image"]
    slice_width = int(json_data["frames"][0]["sourceSize"]["w"])
    slice_height = int(json_data["frames"][0]["sourceSize"]["h"])
    sprite_count = len(json_data["frames"])
    state_count = len(json_data["meta"]["frameTags"])

    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)

    image_data = slice_image(sprite_image_filename, slice_width, slice_height)

    # Write a definition file to go with it
    data_file = os.path.join(output_directory, f"{spritename}.spr");
    with open(data_file, 'wb') as f:
        f.write(b"NCOTS")
        f.write(slice_width.to_bytes(2, 'little'))
        f.write(slice_height.to_bytes(2, 'little'))
        f.write(sprite_count.to_bytes(2, 'little'))
        f.write(state_count.to_bytes(2, 'little'))
        for tag in json_data["meta"]["frameTags"]:            
            length = int(tag["to"])-int(tag["from"])+1
            f.write(length.to_bytes(2,'little'))
            for x in range(int(tag["from"]),int(tag["to"])+1):
                f.write(x.to_bytes(2,'little'))
                f.write((int(json_data["frames"][x]["duration"])//10).to_bytes(2, 'little'))
        f.write(image_data.getvalue())
    
    
if __name__ == "__main__":
    main()
