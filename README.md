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

One can also play an instrument by pressing the buttons. The channel that is being played is selected by the 7th column.

### Edit Time (red):

The green buttons in the 2nd column sets the number of beats per bar in binary format. The next 2 columns of blue buttons sets the bpm as an 8 bit binary number. The purple pinkish buttons in the 5th column set the beat subdivisions (whether it plays crotchets, quavers, etc). The red buttons in the 6th column set the number of bars.

The button in the 6th column 4th row randomizes the sequence of the bars when engaged (yellow). That means each time a bar ends, a new one is picked at random.

The 7th column sets the variation in time between beats.

### Edit Melody (orange):

The 7th column is used to select the midi channel. The remaining buttons are used to input the melody.

TODO: explain details

### Edit Instrument 1 (yellow):

The 2nd column sets the maximum velocity and the 3rd sets the minimum velocity. The top button in the 4th column sets how the velocity varries, and he green buttons just below adjust different parameters depending the velocity mode. There are 5 modes:

**Random uniform (blue):**
Each note's velocity is sampled from a random uniform distribution between the minimum and maximum velocities.

**Random walk (cyan):**
Each note's velocity is slightly bigger or smaller than that of the previous note. The green buttons set the size of the steps.

**Accent strong beats (green):**
Strong beats are played at the max velocity, while the rest are played at the min velocity. The green buttons set the number of weak beats between each strong beat.

**Ascending (Yellow):**
The first note of each bar is played at the minimum velocity, and linearly increases so that the last note is played at the maximum velocity.

**Descending (Red):**
The first note of each bar is played at the maximum velocity, and linearly decreases so that the last note is played at the minimum velocity.

The top button in the 5th column sets the chance that a note is played. If the light is off, the chance is 0% and the instrument is effectivly turned off. Then each time the button is pressed the chance increases, until it's red and the chance is 100%, meaning every note plays.

The blue buttons just below set the octave of the notes.

The top button in the 6th column enables random note mode. If enabled (yellow), instead of playing the beats in sequence, a random beat within the bar is chosen every time. This allows generative melodies.

The 2nd button in the 6th column sets whether or not black keys are included. If they are included you can play any scale, but it's easy to play some inharmonious notes. When they are excluded, you can only play C major (or A minor), but most notes would sound harmonious.

The 3rd button in the 6th column is to send midi panic comands. If a note is stuck, send this command to stop it.

The bottom button in the 6th column sets the colour of the instrument.

The 7th column selects the intsrument to edit, the same as the 7th column in the Edit Melody page.

### Edit Instrument 2 (green):

The 2nd and 3rd columns set the bar repetition structure. The colour of each button sets which bar to play, and the location sets when to play in. For example, if every button is white, the current instrument would continuously play the firt bar. This is useful for having a repetitive drumbeat without having to write it for all 8 bars.

The 4th and 5th columns overwite the notes in the current instrument with something else. Starting from top left going to bottom right, these "something else's" are:

**Root note at start of bar:**
Replace the first note of each bar with just the root note. For the 8 bars, these are A, B, C, D, E, F, G, A.

**Root on every beat:**
The same as _Root note at start of bar_, but for every beat within the bar also.

**Chord at start of bar:**
The same as _Root note at start of bar_, but chords instead of root notes.

**Chord on every beat:**
The same as _Chord at start of bar_, but for every beat within the bar also.

**Arpegios:**
The same as _Chord on every beat_, but chords are arpegiated.

**Random Notes:**
A random note is placed on each beat.

**Clear All:**
All notes on the current instrument are deleted.

**Copy another instrument:**
The notes from another instrument are copied to the current instrument. The instrument to copy from is determined by the 6th column.

The 7th column selects the current intsrument, the same as the 7th column in the Edit Melody page.
