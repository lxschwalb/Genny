#include "instruments.h"

instruments::instruments(/* args */)
{
}

instruments::~instruments()
{
}

void instruments::begin(Adafruit_NeoTrellisM4 *trellis)
{
  _trellis = trellis;
}

void instruments::setTimePoint(uint8_t bar_num, uint8_t beat_num) {
  if (free_running)
  {
    _beat_num++;
    _beat_num %= num_beats+1;
    if (_beat_num == 0)
    {
      _bar_num = bar_num;
    }
  }
  else
  {
    _beat_num = beat_num % (num_beats + 1);
    _bar_num = bar_num;
  }
}

int instruments::findMelodyEditColor(int note) {
  int bar_alias = bar_copy[_bar_num];

  if (note_on[_beat_num][bar_alias] & 1<<note)
  {
    return ~count_colors2[color_picker];
  }
  if (note_off[_beat_num][bar_alias] & 1<<note)
  {
    return 0;
  }
  if (white_notes[note])
  {
    return count_colors2[color_picker];
  }
  return count_colors2[color_picker] & 0x0F0F0F;
}

int instruments::showNote(int note) {
  if (is_note_playing & (1 << note))
  {
    return count_colors2[color_picker];
  }
  return 0x000000;
}

void instruments::setNoteTimes(unsigned long last_beat, unsigned long beat_len) {
  int bar_alias = bar_copy[_bar_num];
  int beat_alias = random_beat ? random(16) : _beat_num;
  if (random(1, 4) <= prob)
  {
    long variation = (beat_len>>4)*rand_time;
    for(int i = 0; i < 20; i++) {
      long offset = random(-variation, variation);
      if(note_on[beat_alias][bar_alias] & (1<<i)) {
        note_on_times[i] = last_beat + (beat_len>>1) + offset;
      }
      else {
        note_on_times[i] = 0xFFFFFFFF;
      }

      if(note_off[beat_alias][bar_alias] & (1<<i)) {
        if (note_on_times[i] != 0xFFFFFFFF) {
          unsigned long margin = beat_len>>5;
          note_off_times[i] = random(note_on_times[i]+margin, last_beat+beat_len-margin);
        }
        else {
          note_off_times[i] = last_beat + (beat_len>>1) + offset;
        }
      }
      else {
        note_off_times[i] = 0xFFFFFFFF;
      }
    }
  }
  else {
    for(int i = 0; i < 20; i++) {
      note_on_times[i] = -1;
      note_off_times[i] = -1;
    }
  }
}

void instruments::setVel() {
  switch (vel_mode)
  {
  case rand_uni:
    vel = random(min_vel, max_vel);
    break;
  
  case rand_walk:
    vel = vel_prev + random(-vel_param, vel_param + 1);
    vel = max(min_vel, vel);
    vel = min(max_vel, vel);
    break;

  case accent:
    vel = (_beat_num % (vel_param + 1)) ? min_vel : max_vel;
    break;

  case ascending:
    vel = min_vel + ((max_vel - min_vel)>>4)*_beat_num; // TODO improve this
    break;

  case descending:
    vel = max_vel - ((max_vel - min_vel)>>4)*_beat_num; // TODO improve this
    break;
  
  default:
    break;
  }
  vel_prev = vel;
}

void instruments::playback() {
  unsigned long t = micros();
  for(int i = 0; i < 20; i++)
  {
    if (t >= note_on_times[i])
    {
      noteOn(i, vel);
      note_on_times[i] = 0xFFFFFFFF;
    }
    if (t >= note_off_times[i])
    {
      noteOff(i, vel);
      note_off_times[i] = 0xFFFFFFFF;
    }   
  }
}

void instruments::noteOn(int note, int velocity, bool write) {
  int real_note = black_keys ? 9+12*octave + note : 9+12*octave + tonal_map[note];
  _trellis->noteOn(real_note, velocity);
  is_note_playing |= 1 << note;

  if (write)
  {
    note_on[_beat_num][bar_copy[_bar_num]] ^= 1<<note;
  }
}

void instruments::noteOff(int note, int velocity, bool write) {
  int real_note = black_keys ? 9+12*octave + note : 9+12*octave + tonal_map[note];

  _trellis->noteOff(real_note, velocity);
  is_note_playing &= ~(1 << note);

  if (write)
  {
    note_off[_beat_num][bar_copy[_bar_num]] ^= 1<<note;
  }
}

int instruments::velModeColor() {
  return count_colors2[int(vel_mode)];
}

int instruments::color() {
  return count_colors2[color_picker];
}