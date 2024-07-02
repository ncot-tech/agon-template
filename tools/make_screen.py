#!/usr/bin/env python3

import os
import string

def create_project(name):
    # Read template files
    with open('../../templates/screen_template.h', 'r') as file:
        template_header = file.read()

    with open('../../templates/screen_template.c', 'r') as file:
        template_source = file.read()

    # Prepare substitution mapping
    mapping = {
        'PROGNAME': name,
        'PROGNAME_UPPER': name.upper(),
        'PROGNAME_LOWER': name.lower()
    }

    # Perform template substitution
    header_content = string.Template(template_header).substitute(mapping)
    source_content = string.Template(template_source).substitute(mapping)

    # Create new files with substituted content
    header_filename = f'{name}.h'
    source_filename = f'{name}.c'

    with open(header_filename, 'w') as file:
        file.write(header_content)

    with open(source_filename, 'w') as file:
        file.write(source_content)

    print(f"Created files: {header_filename}, {source_filename}")

def main():
    # Get user input for project name
    project_name = input("Enter a name for your project: ")

    # Call function to create project files
    create_project(project_name)

if __name__ == "__main__":
    main()