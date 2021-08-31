#include "instruments.h"

instruments::instruments(/* args */)
{
}

instruments::~instruments()
{
}

void instruments::setTimePoint(uint8_t bar_num, uint8_t beat_num) {
  _bar_num = bar_num;
  _beat_num = beat_num;
}

int instruments::findMelodyEditColor(int note) {
  int bar_alias = bar_copy[_bar_num];

  if (note_on[_beat_num][bar_alias] & 1<<note)
  {
    return ~count_colors2[color_picker];
  }
  if (note_off[_beat_num][bar_alias] & 1<<note)
  {
    return 0xFFFFFF;
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

void instruments::send_midi(Adafruit_NeoTrellisM4 *trellis) {
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
    vel = min_vel + ((max_vel - min_vel)>>4)*_beat_num;
    break;

  case descending:
    vel = max_vel - ((max_vel - min_vel)>>4)*_beat_num;
    break;
  
  default:
    break;
  }
  vel_prev = vel;

  if (random(1, 5) <= prob)
  {
    int bar_alias = bar_copy[_bar_num];
    int beat_alias = random_beat ? random(16) : _beat_num;

    for (int i = 0; i < 20; i++)
    {
      if (note_on[beat_alias][bar_alias] & 1 << i)
      {
        noteOn(i, vel, trellis);
      }
      else if (note_off[beat_alias][bar_alias] & 1 << i)
      {
        noteOff(i, vel, trellis);
      }
    }
  }
}

void instruments::noteOn(int note, int velocity, Adafruit_NeoTrellisM4 *trellis, bool toggle, bool next_beat) {
  int real_note = black_keys ? 9+12*octave + note : 9+12*octave + tonal_map[note];
  trellis->noteOn(real_note, velocity);
  is_note_playing |= 1 << note;

  if (toggle)
  {
    int bar_alias;
    int beat_alias;
    beat_alias = next_beat ? _beat_num + 1 : _beat_num;
    if(beat_alias & 0x10)
    {
      beat_alias &= 0xF;
      bar_alias = bar_copy[(_bar_num + 1) & 0x7];
    }
    else
    {
      bar_alias = bar_copy[_bar_num];
    }
    
    toggle_flag |= note_on[beat_alias][bar_alias] & (1<<note);
    note_on[beat_alias][bar_alias] |= 1<<note;
    note_off[beat_alias][bar_alias] &= ~(1<<note);
  }
  
}

void instruments::noteOff(int note, int velocity, Adafruit_NeoTrellisM4 *trellis, bool toggle, bool next_beat) {
  int real_note = black_keys ? 9+12*octave + note : 9+12*octave + tonal_map[note];

  trellis->noteOff(real_note, velocity);
  is_note_playing &= ~(1 << note);

  if (toggle)
  {
    int bar_alias;
    int beat_alias;
    beat_alias = next_beat ? _beat_num + 1 : _beat_num;
    if(beat_alias & 0x10)
    {
      beat_alias &= 0xF;
      bar_alias = bar_copy[(_bar_num + 1) & 0x7];
    }
    else
    {
      bar_alias = bar_copy[_bar_num];
    }

    if (!(note_on[beat_alias][bar_alias] & (1 << note)))
    {
      note_off[beat_alias][bar_alias] |= 1<<note;
    }
    else if (toggle_flag & (1<<note))
    {
      note_on[beat_alias][bar_alias] &= ~(1<<note);
      note_off[beat_alias][bar_alias] &= ~(1<<note);
      toggle_flag &= ~(1<<note);
    }
  }
}

int instruments::probColor() {
  return count_colors1[prob];
}

int instruments::velModeColor() {
  return count_colors2[int(vel_mode)];
}

int instruments::color() {
  return count_colors2[color_picker];
}