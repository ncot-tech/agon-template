# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [refactoring/0.2.0] - 2 July 2024

### Added

- Sprite structs
- Sprite instantiation, drawing and updating functions
- Rectangle structure
- Global variables structure
- Sprite animations
- Parsing Aseprite JSON files

### Changed

- Moved Point into its own file
- Moved bitmap loading into the correct file
- Updated docs

### Removed

## [refactoring/0.1.0] - 15 June 2024

### Added

- Doxygen config for making documentation
- Semantic versioning with version.h
- update_doxyfile.py tool to keep the doxygen version and code version the same
- Documentation
- Fatal error handling

### Changed

- Moved files into their own folders for better reuse
- Makefile now generates docs and update version strings
- Complete reorganisation of all the code, renamed a lot to be more consistent

### Removed

