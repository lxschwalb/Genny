#ifndef __INSTRUMENTS_H
#define __INSTRUMENTS_H

#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>

const int tonal_map[20] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24, 26, 27, 29, 31, 32};
const bool white_notes[20] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
const int count_colors1[5] = {0x000000, 0xFFFF00, 0xFF4F00, 0xFF1F00, 0xFF0000};
const int count_colors2[6] = {0x0000FF, 0x00FFFF, 0x00FF00, 0xFFFF00, 0xFF0000, 0xFF00FF};

enum velocity_mode {
  rand_uni = 0,
  rand_walk = 1,
  accent = 2,
  ascending = 3,
  descending = 4
};


class instruments
{
private:
    /* data */
    uint8_t _bar_num = 0;
    uint8_t _beat_num = 0;
    uint32_t is_note_playing;
    int vel = 0;
    int vel_prev = 0;
    Adafruit_NeoTrellisM4 *_trellis;
    unsigned long note_on_times[20];
    unsigned long note_off_times[20];

public:
    instruments();
    ~instruments();
    void begin(Adafruit_NeoTrellisM4 *trellis);

    void setTimePoint(uint8_t bar_num, uint8_t beat_num);
    int findMelodyEditColor(int note);
    void setNoteTimes(unsigned long last_beat, unsigned long beat_len);
    void playback();
    void setVel();
    void noteOn(int note, int velocity, bool write = false);
    void noteOff(int note, int velocity, bool write = false);
    int probColor();
    int velModeColor();
    int color();
    int showNote(int note);
    
    uint32_t note_on[16][8];
    uint32_t note_off[16][8];

    uint8_t num_beats = 15;
    bool free_running = false;
    uint8_t rand_time = 0;
    uint8_t bar_copy[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    uint8_t max_vel = 127;
    uint8_t min_vel = 0;
    uint8_t prob = 4;
    uint8_t octave = 3;
    uint8_t color_picker = 0;
    bool random_beat = false;
    bool black_keys = true;
    velocity_mode vel_mode = rand_uni;
    uint8_t vel_param = 7;
};




#endif