from PIL import Image
import os, io

def convert_imagedata_to_2222(source_image):

    width, height = source_image.size
    pixel_depth = source_image.mode

    # Extract pixel data
    pixel_data = list(source_image.getdata())

    # Convert pixel data to RGB2222 format
    rgb2222_data = bytearray()
    for pixel in pixel_data:
        r, g, b, a = pixel
        pixel_value = ((r >> 6) & 0x03 | (((g >> 6) & 0x03) << 2) | (((b >> 6) & 0x03) << 4) | (((a >> 6) & 0x03) << 6))
        rgb2222_data.append(pixel_value)

    buff = io.BytesIO()
    buff.write(b"NCOTB")
    buff.write(width.to_bytes(2, 'little'))
    buff.write(height.to_bytes(2, 'little'))
    buff.write((1).to_bytes(1, 'little'));
    buff.write(rgb2222_data)

    return buff

def convert_file_to_2222(source_file):
    # Open the input PNG file
    try:
        image = Image.open(source_file)
      
        # Convert the image to RGBA format first
        image = image.convert('RGBA')

        # Quantize the image down to 64 colours
        image = image.point(lambda p: p // 85 * 85)

        # Convert to 2222 format
        converted_data = convert_imagedata_to_2222(image)
        
        return converted_data
        
    except FileNotFoundError:
        print(f"Error: File '{input_filename}' not found.")
    except Exception as e:
        print(f"Error: {e}")


