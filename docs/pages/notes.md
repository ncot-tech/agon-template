# General Notes

## VIM Commands

* Ctrl-w s, ctrl-w v - Split current window half horizontally or vertically with same file in it
* Ctrl-w n - Same thing, new buffer but horizontal
* :vnew - same thing, new buffer but vertical
* Ctrl-w q - Close
* Ctrl-w arrows - move between buffers
* :vs filename - open file in new vertical split

## Git

There is a git pre-commit hook that reminds me to update the changelog

## Python venv

Use a venv to make the python scripts not pollute your own Python install with their junk.

1. Run `python -m venv venv` from inside the main source directory
2. Activate the virtual env with `venv/bin/activate`
3. Install the dependences by typing `pip install -r tools/requirements.txt`
4. Deactivate it when you are done using `deactivate`