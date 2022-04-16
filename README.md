# generative_sequencer_m4
Midi sequencer using a neotrellis m4 with some randomization options to make generative music

# How to use:

## Overview:

Patterns of up to 8 bars, each containing up to 16 beats can be programmed for up to 16 midi channels. There are then some features to randomise the playback to create some generative music.

## Representing numbers:

Numbers are represented in 2 ways. The first is in binary format, where one colour represents a 1 and another represents a 0. Multiple buttons are grouped together to represent the whole number.

The second is to associate a colour to a specific number. We generally want to count up to 8, so we start with white followed by the 7 colours of the rainbow. This is useful to count using only one button.

## Pages:

The left most and right most columns always represent the same information, while the columns in the middle represent different information depending on what page is selected.

### Permanent:

The left most column permanently represents the current step number in the bar as a 4 bit binary number. Since it is a 4 bit binary number it counts from 0 to 15, instead of 1 to 16 (as would usually be done in music)

The top right button permanently functions as the play/stop button. The colour represents the current state. Green means it is playing, red means it stopped.

in the right most column, pressing the 2nd button causes an immediate jump to the next beat, while pressing the 3rd button causes an immediate jump to the next bar. The colour of these buttons represents the bar number.

The bottom right button selects the page to display. The page number is represented by the colour.

### Display (white):

In this page, all the melodies are simultaneously displayed. The colours of each instrument are summed together (as RGB), so if a blue instrument and a red instrument plays the same note at the same time, the button is purple.

One can also play an instrument by pressing the buttons. The channel that is being played is selected by the second to right column using the binary format.

### Edit Time (red):

The green buttons in the 2nd column sets the number of beats per bar in binary format. The next 2 columns of blue buttons sets the bpm as an 8 bit binary number. The purple pinkish buttons in the 5th column set the beat subdivisions (whether it plays crotchets, quavers, etc). The red buttons in the 6th column set the number of bars.

The button in the 6th column 4th row randomizes the sequence of the bars when engaged (yellow). That means each time a bar ends, a new one is picked at random.

The 7th column sets the variation in time between beats.

### Edit Melody (orange):

The 7th column is used to select the midi channel. The remaining buttons are used to input the melody.

TODO: explain details

### Edit Instrument 1 (yellow):

The 2nd column sets the maximum velocity and the 3rd sets the minimum velocity.
### Edit Instrument 2 (green):
