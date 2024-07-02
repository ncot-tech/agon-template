#!/usr/bin/env python3

import argparse, csv, io
import sys, os, image_conv
import xml.etree.ElementTree as ET

def get_filename_without_extension(file_path):
    base_name = os.path.basename(file_path)
    filename, _ = os.path.splitext(base_name)
    return filename

def parse_csv_string(csv_string):
    # Create a file-like object from the CSV string
    csv_file = io.StringIO(csv_string)
    reader = csv.reader(csv_file)
    for row in reader:
        data = row

    return data

def parse_tsx(xml_file):
    # Parse the XML file
    tree = ET.parse(xml_file)
    root = tree.getroot()

    # Extract tile data
    tile_data = []
    tiles = root.findall('tile')
    for tile in tiles:
        tile_id = int(tile.attrib['id'])
        image_width = int(tile.find('image').attrib['width'])
        image_height = int(tile.find('image').attrib['height'])
        source = tile.find('image').attrib['source']
        tile_data.append({'id':tile_id, 'image_width':image_width, 'image:height':image_height, 'source':source })

    # return a list with all the tiles in
    return tile_data


def parse_tmx(xml_file):
    # Parse the XML file
    tree = ET.parse(xml_file)
    root = tree.getroot()

    # Extract tileset attributes
    map_attributes = root.attrib
    print(f"Width {map_attributes['width']} Height {map_attributes['height']} TileW {map_attributes['tilewidth']} TileH {map_attributes['tileheight']}")

    tileset = root.find("./tileset[@firstgid='1']")
    tileset_attributes = tileset.attrib
    print(f"Tileset {tileset_attributes['source']}")
    tileset_file = tileset_attributes['source']
 
    # Find the layer element containing the CSV data
    layer = root.find("./layer[@id='1']")

    # Extract the CSV data from the layer
    csv_data = layer.find('data').text.strip().replace("\n","").replace("\r","")

    # return a dict with the stuff in
    map_data = {}
    map_data['tileset_file'] = tileset_file
    map_data['map_width'] = int(map_attributes['width'])
    map_data['map_height'] = int(map_attributes['height'])
    map_data['tile_width'] = int(map_attributes['tilewidth'])
    map_data['tile_height'] = int(map_attributes['tileheight'])
    raw_map_data = parse_csv_string(csv_data)

    # Flip the map upside down because OS co-ords on the Agon are upside-down
    mw = map_data['map_width']
    mh = map_data['map_height']

    map_data['map_data'] = []
    for i in range(mh-1,-1,-1):
        row_start_index = i * mw
        row_data = []
        for j in range(mw):
            index = row_start_index + j
            row_data.append(raw_map_data[index])
        map_data['map_data'].extend(row_data)

    print(map_data['map_data'])

    return map_data

def main():
    parser = argparse.ArgumentParser(description="Convert Tiled tmx and tsx files.")
    parser.add_argument("input_tmx", help="Full path to the input TMX file.")
    parser.add_argument("output_directory", help="Where to put the converted tiles")
    parser.add_argument("bitmap_start_id", help="Starting bitmap ID")
    args = parser.parse_args()

    input_tmx_path = args.input_tmx
    tilemap_name = get_filename_without_extension(input_tmx_path)
    output_directory = args.output_directory
    input_directory = os.path.dirname(input_tmx_path)
    bitmap_start_id = int(args.bitmap_start_id)

    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)

    map_data = parse_tmx(input_tmx_path)
    tile_data = parse_tsx(input_directory + "/" + map_data['tileset_file'])

    buff = io.BytesIO()
    # 15 byte header
    buff.write(b"NCOTM")
    buff.write(map_data['map_width'].to_bytes(2, 'little'))
    buff.write(map_data['map_height'].to_bytes(2, 'little'))
    buff.write(map_data['tile_width'].to_bytes(1, 'little'))
    buff.write(map_data['tile_height'].to_bytes(1, 'little'))
    buff.write(bitmap_start_id.to_bytes(2, 'little'))
    buff.write(len(tile_data).to_bytes(2, 'little'))

    # Go through all the images and convert them to .222 and put them in a folder
    for tile in tile_data:
        converted_image = image_conv.convert_file_to_2222(input_directory + "/" + tile['source'])
        output_filename = get_filename_without_extension(tile['source']) + ".222"
        output_filepath = output_directory + "/" + output_filename
        internal_filepath = "tiles/" + output_filename

        with open(output_filepath, 'wb') as f:
            f.write(converted_image.getvalue())

        # And write a mapping between tile ID and image filename into the map file we're making
        buff.write(tile['id'].to_bytes(2, 'little'))
        buff.write(len(internal_filepath).to_bytes(2, 'little'))  # How long the filename is
        buff.write(internal_filepath.encode('ascii')) # Not null terminated

    # Go through the map data
    for m in map_data['map_data']:
        # -1 to write out the correct tile ID, see the tiled file format docs
        buff.write((int(m)-1).to_bytes(2,'little'))

    map_file = output_directory + "/" + tilemap_name + ".map"
    with open(map_file, 'wb') as f:
        f.write(buff.getvalue())

if __name__ == "__main__":
    main()
