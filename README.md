# Simple time puzzle

This is a simple game I made, designed as a kind of virtual escape room. It should be mostly configurable by editing the config file.

The code is messy and full of holes, but perhaps it will be of use to someone. Be warned, there are buffer overflows everywhere.

### Instructions

To build the project there is a makefile included. To customize the game modify the `config/config-sample` file, and rename it to `config/config`. Editing it should be fairly self explanatory.

To allow someone to play it, simply run the program. I recommend switching to a virtual console, so the game can be played in getty. This will allow the most authentic experience, and prevent the player from resizing the window or otherwise messing things up.
