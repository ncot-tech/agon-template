This uses Commitizen to handle changelogs and stuff, do this:

1. Write code as normal
2. When it comes time to commit, use "cz commit" instead
3. When it's time to go up a version, use "cz bump" and it'll do the rest

When is it time to go up a version? Probably something like this:

The remote repo contains the latest version and history
My machine contains bleeding edge code that might not work
Don't push to the remote repo until it builds
Don't bump the version until it works
If I can figure out how to make a tag for a test, use that when trying things out.


VIM Commands

Ctrl-w s, ctrl-w v - Split current window half horizontally or vertically with same file in it
Ctrl-w n - Same thing, new buffer but horizontal
:vnew - same thing, new buffer but vertical
Ctrl-w q - Close
Ctrl-w arrows - move between buffers
:vs filename - open file in new vertical split
