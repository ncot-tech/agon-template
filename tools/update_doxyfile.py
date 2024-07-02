#!/usr/bin/env python3

import re

version_file = 'src/version.h'
doxygen_file = 'Doxyfile'
readme_file = 'Readme.md'

# Read the version from version.h
with open(version_file, 'r') as f:
    content = f.read()
    major = re.search(r'#define PROJECT_VERSION_MAJOR (\d+)', content).group(1)
    minor = re.search(r'#define PROJECT_VERSION_MINOR (\d+)', content).group(1)
    patch = re.search(r'#define PROJECT_VERSION_PATCH (\d+)', content).group(1)
    version = f'{major}.{minor}.{patch}'

# Update the PROJECT_NUMBER in Doxyfile
with open(doxygen_file, 'r') as f:
    doxygen_content = f.read()

doxygen_content = re.sub(r'PROJECT_NUMBER\s*=\s*\S+', f'PROJECT_NUMBER = {version}', doxygen_content)

with open(doxygen_file, 'w') as f:
    f.write(doxygen_content)

# Update the version in README.md
with open(readme_file, 'r') as f:
    readme_content = f.read()

readme_content = re.sub(r'(Version:)\s*\S+', f'\\1 {version}', readme_content)

with open(readme_file, 'w') as f:
    f.write(readme_content)
