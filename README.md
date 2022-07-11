## Overview:

Genny is a generative midi sequencer using a Neotrellis M4. Patterns of up to 8 bars, each containing up to 16 beats can be programmed for up to 16 midi channels. There are then some features to randomise the playback to create some generative music.

## Uploading the firmware:

There are many different ways to upload the firmware. One option is to create a PlatformIO project in VS Code, copy the .cpp and .h files into the src folder, and press the upload button from PlatformIO. Another option is to create an Arduino project, copy the .cpp and .h files into the project folder, rename main.cpp to the name of the project, and press the Arduino upload button.

## Representing numbers:

Numbers are represented in 2 ways. The first is in binary format, where one colour represents a 1 and another represents a 0. Multiple buttons are grouped together to represent the whole number.

The second is to associate a colour to a specific number. We generally want to count up to 8, so we start with white followed by the 7 colours of the rainbow. This is useful to count using only one button.

## Tuning:
TODO add picture

## Making Music:

The 1st, 7th and 8th column permanently have the same function, while the rest of the buttons' functions vary depending on the selected page.

The 1st column permanently represents the current beat number as a 4 bit binary number. Since it is a 4 bit binary number it counts from 0 to 15, instead of 1 to 16 (as would usually be done in music).

The 7th column permanently represents which midi channel is selected as a 4 bit binary number.

The top right button permanently functions as the play/stop button. The colour represents the current state. Green means it is playing, red means it stopped.

In the 8th column, pressing the 2nd button causes an immediate jump to the next beat, while pressing the 3rd button causes an immediate jump to the next bar. The colour of these buttons represents the bar number.

The bottom right button selects the page to display. The page number is represented by the colour and as the button is pressed a letter is displayed to indicate the current page. The function of each page is described below.

### Show All (A):

In this page, all the melodies are simultaneously displayed. The colours of each instrument are summed together (as RGB), so if a blue instrument and a red instrument plays the same note at the same time, the button is purple.

One can also play an instrument by pressing the buttons. The channel that is being played is selected by the 7th column.

### Edit Time (t):

This page is used to edit various time parameters. TODO add details

### Record (R):

This page is used to record melodies. Pressing a button puts a midi NoteOn command on the current beat, and releasing a button puts a midi NoteOff command on the current beat. You can either record a melody in realtime while the system is playing(top right button green),or you could manually input a melody by navigating to the time point(beat and bar) you want to edit and then pressing or releasing the button corresponding to the note you want.

### Edit Bars (b):

TODO add details
The 2nd and 3rd columns set the bar repetition structure. The colour of each button sets which bar to play, and the location sets when to play it. For example, if every button is white, the current instrument would continuously play the firt bar. This is useful for having a repetitive drumbeat without having to manually program it for all 8 bars.

Changing the colours in this _bar repetition structure_ section is kind of counter intuitive, but once you get it you can put in patterns very fast. First press and hold the button that represents the bar number you want to set the other buttons to. Then press all the buttons you want to set to that bar number while still holding down the first button.

### Other (O)
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

The top button in the 5th column ssets whether black keys are included or nor. When they are included you can make more emotionally complex sounds, but when they are excluded you are guaranteed that every note is in CMaj/Amin.

The 3 cyan buttons just below set the octave of the notes.

The top 2 buttons in the 6th column set the probability of a note being played. When both buttons are on each not plaes 100% of the time, and when both are off it is 0% and the current channel is essentially switched off. It sounds cool to have it inbeyween, so only some, but not all, notes play.

The 3rd button in the 6th column enables random note mode. If enabled (yellow), instead of playing the beats in sequence, a random beat within the bar is chosen every time. This allows generative melodies.

The 4th button in the 6th column is to send midi panic comands. If a note is stuck, send this command to stop it.

### Presets (P):

This page is used to quickly write presets to the current channel so you don't have to manually input every time.

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
