# File Formats

## RGBA2222 format images

Save images inside the data/images directory

If you run `make images` the `png2rgb.py` tool will turn them into RGBA2222 format image data. This data contains the following

Header: 10 bytes
 * NCOTB - magic string meaning RGB2222 bitmap image
 * WIDTH - 16 bit little endian
 * HEIGHT - 16 bit little endian
 * BPP - 1 byte

Pixel Data: Rest of file
 * 1 byte per pixel, RGBA 2 bits each

To use this, read the first 10 bytes, check it starts with "NCOTB".
Then use the width * height * bpp to know the size of the image data in bytes.

## Fonts

Fonts are made from image atlas files containing each character in ASCII order. Each character is turned into its own RGBA2222 format image, and a `.fon` definition file is created to go along with it.

## Tilemaps

These work with Tiled format tmx and tsx files. The conversion tool will read the Tiled tmx file and create a directory of relevant image data, map data and definition files.

