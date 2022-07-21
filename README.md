# Overview:

Genny is a generative midi sequencer using a Neotrellis M4. Patterns of up to 8 bars, each containing up to 16 beats can be programmed for up to 16 midi channels. There are then some features to randomise the playback to create some generative music.

# Uploading the firmware:

There are many different ways to upload the firmware. One option is to create a PlatformIO project in VS Code, copy the .cpp and .h files into the src folder. Press the upload button from PlatformIO.

Another option is to create an Arduino project, copy the .cpp and .h files into the project folder, rename main.cpp to the name of the project, and change the file type from .cpp to .ino. Press the Arduino upload button.

# Representing numbers:

Numbers are represented in 2 ways. The first is in binary format, where one colour represents a 1 and another represents a 0. Multiple buttons are grouped together to represent the whole number.

The second is to associate a colour to a specific number. We generally want to count up to 8, so we start with white followed by the 7 colours of the rainbow. This is useful to count using only one button.

# Making Music:

The 1st, 7th and 8th column permanently have the same function, while the rest of the buttons' functions vary depending on the selected page.

|beat3||||||instr3|play|
|-|-|-|-|-|-|-|-|
|beat2||||||instri2|nextBeat|
|beat1||||||instr1|nextBar|
|beat0||||||instr0|page|

[beat] permanently represents the current beat number as a 4 bit binary number. Since it is a 4 bit binary number it counts from 0 to 15, instead of 1 to 16 (as would usually be done in music).

[instr] permanently represents which midi channel is selected as a 4 bit binary number.

[play] permanently functions as the play/stop button. The colour represents the current state. Green means it is playing, red means it stopped.

Pressing [nextBeat] causes an immediate jump to the next beat, while pressing [nextBar] causes an immediate jump to the next bar. The colour of these buttons represents the bar number.

[page] selects the page to display. The page number is represented by the colour and as the button is pressed a letter is displayed to indicate the current page. The function of each page is described below.

## Show All (A):

In this page, all the melodies are simultaneously displayed. The colours of each instrument are summed together (as RGB), so if a blue instrument and a red instrument plays the same note at the same time, the button is purple.

One can also play an instrument by pressing the buttons. The channel that is being played is selected by the 7th column.

If black keys are included for the current channel(default), the tuning is as follows. The lowest note is an A on the bottom left, and then it chromatically increases to the right. The next row up is a 4th higher, just like many string instruments (such as guitar).
||C|C#|D|D#|E|||
|-|-|-|-|-|-|-|-|
||G|G#|A|A#|B|||
||D|D#|E|F|F#|||
||A|A#|B|C|C#|||


If black keys are excluded from the current channel, the tuning is as follows. Again the lowest note is an A on the bottom left.
||B|C|D|E|F|||
|-|-|-|-|-|-|-|-|
||D|E|F|G|A|||
||F|G|A|B|C|||
||A|B|C|D|E|||

## Edit Time (t):
||globalNumBeats3|clockMode|tap3|localNumBeats3|runFree|||
|-|-|-|-|-|-|-|-|
||globalNumBeats2|globalTimeDeviance2|tap2|localNumBeats2|localTimeDeviance2|||
||globalNumBeats1|globalTimeDeviance1|tap1|localNumBeats1|localTimeDeviance1|||
||globalNumBeats0|globalTimeDeviance0|tap0|localNumBeats0|localTimeDeviance0|||

This page is used to edit various time parameters. TODO add details

## Record (R):

This page is used to record melodies. Pressing a button puts a midi NoteOn command on the current beat, and releasing a button puts a midi NoteOff command on the current beat. You can either record a melody in realtime while the system is playing,or you could manually input a melody by navigating to the time point(beat and bar) you want to edit and then pressing or releasing the button corresponding to the note you want. The tuning is the same as described for the Show All section.

## Edit Bars (b):
||bar0|bar1|randomBar|groupRepeats1|instrange3|||
|-|-|-|-|-|-|-|-|
||bar2|bar3|numBar2|groupRepeats0|instrange2|||
||bar4|bar5|numBar1|groupSize1|instrange1|||
||bar6|bar7|numBar0|groupSize0|instrange0|||

[bar] is used to set the bar repetition structure. The colour of each button sets which bar to play, and the location sets when to play it. For example, if every button is white, the current instrument would continuously play the firt bar. This is useful for having a repetitive drumbeat without having to manually program it for all 8 bars.

Changing the colours in this _bar repetition structure_ section is kind of counter intuitive, but once you get it you can put in patterns very fast. First press and hold the button that represents the bar number you want to set the other buttons to. Then press all the buttons you want to set to that bar number while still holding down the first button.

If [randomBar] is enabled, a new bar is selected at random at the end of each bar.

You can change the number of bars with [numBar]. The default is 8, which is the maximum.

TODO implement rest

## Other (O)
||velMax3|velMin3|velMode|blackKeys|prob1|||
|-|-|-|-|-|-|-|-|
||velMax2|velMin2|velParam2|octave2|prob0|||
||velMax1|velMin1|velParam1|octave1|randomNote|||
||velMax0|velMin0|velParam0|octave0|midiPanic|||

[velMax] sets the maximum velocity and the [velMin] sets the minimum velocity. [velMode] sets how the velocity varries, and [velParam] adjusts different parameters depending the velocity mode. There are 5 modes:

- **Random uniform (blue):**
Each note's velocity is sampled from a random uniform distribution between the minimum and maximum velocities.

- **Random walk (cyan):**
Each note's velocity is slightly bigger or smaller than that of the previous note. [velParam] sets the size of the steps.

- **Accent strong beats (green):**
Strong beats are played at the max velocity, while the rest are played at the min velocity. [velParam] sets the number of weak beats between each strong beat.

- **Ascending (Yellow):**
The first note of each bar is played at the minimum velocity, and linearly increases so that the last note is played at the maximum velocity.

- **Descending (Red):**
The first note of each bar is played at the maximum velocity, and linearly decreases so that the last note is played at the minimum velocity.

[blackKeys] sets whether black keys are included or not. When they are included you can make more emotionally complex sounds, but when they are excluded you are guaranteed that every note is in CMaj/Amin. It is enabled by default.

[octave] sets the octave of the notes.

[prob] sets the probability of a note being played. When both buttons are on each note plays 100% of the time, and when both are off it is 0% and the current channel is essentially switched off. It sounds cool to have it inbetween, so only some, but not all, notes play.

[randomNote] enables random note mode. If enabled, instead of playing the beats in sequence, a random beat within the bar is chosen every time. This allows generative melodies.

[midiPanic] sends the midi panic command. If a note is stuck, send this command to stop it.

## Presets (P):
||ascending|descending|root|roots|copySource3|||
|-|-|-|-|-|-|-|-|
||blues|pop|chord|chords|copySource2|||
||Co5|randomBars|arpegios|randomNotes|copySource1|||
||mono|copyBars|clearNotes|copyNotes|copySource0|||

This page is used to quickly write presets to the current channel so you don't have to manually input it every time. The 2nd and 3rd columns are used to set the bar repetition structure, and the 4th and 5th columns are used to set the notes within the bars. Take note, most of these buttons will overwrite whatever is currently written into the selected instrument.

It is assumed that the bars are associated with the following chords:
|Bar 1|Bar 2|Bar 3|Bar 4|Bar 5|Bar 6|Bar 7|Bar 8|
|-|-|-|-|-|-|-|-|
|Am|B|C|Dm|Em|F|G|Am|

The bar presets are as follows:
- [ascending] puts the bars in the following order: 1, 2, 3, 4, 5, 6, 7, 8. This is the default order.
- [descending] puts the bars in the following order: 8, 7, 6, 5, 4, 3, 2, 1.
- [blues] puts the bars in the following order: 1, 1, 4, 1, 5, 4, 1, 1. This is an 8 bar version of the 12 bar blues.
- [pop] puts the bars in the following order: TODO. These 4 chords are often used in pop songs.
- [Co5] puts the bars in the following order: TODO. This follows the circle of 5ths, and is also the progression used in Autumn Leaves.
- [mono] puts the bars in the following order: 1, 1, 1, 1, 1, 1, 1, 1. This is useful for something such as a drum beat that repeats for every bar.
- [copyBars] copies into the selected instrument(7th column) the bar repetition structure of the instrument indicated by [copySource] (6th column).

The note presets are as follows:
- [root] overwrites the first beat of each bar with just the root note corresponding to that bar.
- [roots] overwrites every beat with the root note of the corresponding bar.
- [chord] overwrites the first beat of each bar with the chord corresponding to that bar.
- [chords] overwrites every beat with the chord of the corresponding bar.
- [arpegios] same as [chords], except the notes are arpegiated.
- [randomNotes] places a random note on each beat.
- [clearNotes] deletes all the notes in the current instrument.
- [copyNotes] overwrites all the notes in the selected instrument(7th column) with the notes from the instrument indicated by [copySource] (6th column).

