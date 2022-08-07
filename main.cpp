#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include "instruments.h"

// Permanent buttons
#define BEAT_NUM_0        0
#define BEAT_NUM_1        8
#define BEAT_NUM_2        16
#define BEAT_NUM_3        24
#define PLAY              7
#define BUMP_BEAT         15
#define BUMP_BAR          23
#define PAGE_SEL          31
#define INSTRUMENT_SEL_0  6
#define INSTRUMENT_SEL_1  14
#define INSTRUMENT_SEL_2  22
#define INSTRUMENT_SEL_3  30

// Time buttons
#define BAR_LEN_0         1
#define BAR_LEN_1         9
#define BAR_LEN_2         17
#define BAR_LEN_3         25
#define CLOCK_SYNC        2
#define RAND_TIME_0       10
#define RAND_TIME_1       18
#define RAND_TIME_2       26
#define TAP_TEMPO_0       3
#define TAP_TEMPO_1       11
#define TAP_TEMPO_2       19
#define TAP_TEMPO_3       27
#define LOCAL_BAR_LEN_0   4
#define LOCAL_BAR_LEN_1   12
#define LOCAL_BAR_LEN_2   20
#define LOCAL_BAR_LEN_3   28
#define FREE_RUNNING      5
#define LOCAL_RAND_TIME_0 13
#define LOCAL_RAND_TIME_1 21
#define LOCAL_RAND_TIME_2 29

// Record buttons
#define NOTE_0            25
#define NOTE_1            26
#define NOTE_2            27
#define NOTE_3            28
#define NOTE_4            29
#define NOTE_5            17
#define NOTE_6            18
#define NOTE_7            19
#define NOTE_8            20
#define NOTE_9            21
#define NOTE_10           9
#define NOTE_11           10
#define NOTE_12           11
#define NOTE_13           12
#define NOTE_14           13
#define NOTE_15           1
#define NOTE_16           2
#define NOTE_17           3
#define NOTE_18           4
#define NOTE_19           5

// Bars 
#define BAR_COPY_0        4
#define BAR_COPY_1        5
#define BAR_COPY_2        12
#define BAR_COPY_3        13
#define BAR_COPY_4        20
#define BAR_COPY_5        21
#define BAR_COPY_6        28
#define BAR_COPY_7        29
#define RAND_BAR          1
#define NUM_BAR_0         9
#define NUM_BAR_1         17
#define NUM_BAR_2         25
#define GROUP_SIZE_0      10
#define GROUP_SIZE_1      18
#define GROUP_SIZE_2      26
#define GROUP_REPEAT_0    11
#define GROUP_REPEAT_1    19
#define GROUP_REPEAT_2    27
#define APPLY_ALL         2
#define EXCLUDE           3


// Other buttons
#define MAX_VEL_0         2
#define MAX_VEL_1         10
#define MAX_VEL_2         18
#define MAX_VEL_3         26
#define MIN_VEL_0         1
#define MIN_VEL_1         9
#define MIN_VEL_2         17
#define MIN_VEL_3         25
#define RANDOM_BEAT       21
#define OCTAVE_0          12
#define OCTAVE_1          20
#define OCTAVE_2          28
#define BLACK_KEYS        4
#define PANIC             29
#define VEL_MODE          3
#define VEL_PARAM_0       11
#define VEL_PARAM_1       19
#define VEL_PARAM_2       27
#define PROB_0            13
#define PROB_1            5

// Preset buttons
#define INS_COPY_0        3
#define INS_COPY_1        11
#define INS_COPY_2        19
#define INS_COPY_3        27
#define PRESET_ROOT_BAR   1
#define PRESET_ROOT_BEAT  2
#define PRESET_CHORD_BAR  9
#define PRESET_CHORD_BEAT 10
#define PRESET_ARPEG      17
#define PRESET_RAND       26
#define PRESET_CLEAR      25
#define PRESET_COPY       18
#define BAR_PRESET_UP     29
#define BAR_PRESET_BLUESM 5
#define BAR_PRESET_CO5    21
#define BAR_PRESET_BLUES  13
#define BAR_PRESET_POP    12
#define BAR_PRESET_RAND   28
#define BAR_PRESET_MON    4
#define BAR_PRESET_COPY   20


// Misc definitions
#define NUM_INS           16
#define NUM_NOTES         20
#define MAX_BARS          8
#define MAX_BEATS         16

const uint8_t ins_sel_buttons[4] = {INSTRUMENT_SEL_0, INSTRUMENT_SEL_1, INSTRUMENT_SEL_2, INSTRUMENT_SEL_3};
const uint8_t max_vel_buttons[4] = {MAX_VEL_0, MAX_VEL_1, MAX_VEL_2, MAX_VEL_3};
const uint8_t min_vel_buttons[4] = {MIN_VEL_0, MIN_VEL_1, MIN_VEL_2, MIN_VEL_3};
const uint8_t octave_buttons[3] = {OCTAVE_0, OCTAVE_1, OCTAVE_2};
const uint8_t vel_param_buttons[3] = {VEL_PARAM_0, VEL_PARAM_1, VEL_PARAM_2};
const uint8_t bar_copy_buttons[8] = {BAR_COPY_0, BAR_COPY_1, BAR_COPY_2, BAR_COPY_3, BAR_COPY_4, BAR_COPY_5, BAR_COPY_6, BAR_COPY_7};
const uint8_t ins_copy_buttons[4] = {INS_COPY_0, INS_COPY_1, INS_COPY_2, INS_COPY_3};
const uint8_t note_buttons[NUM_NOTES] = {NOTE_0, NOTE_1, NOTE_2, NOTE_3, NOTE_4, NOTE_5, NOTE_6, NOTE_7, NOTE_8, NOTE_9, NOTE_10, NOTE_11, NOTE_12, NOTE_13, NOTE_14, NOTE_15, NOTE_16, NOTE_17, NOTE_18, NOTE_19};
const uint8_t bar_len_buttons[4] = {BAR_LEN_0, BAR_LEN_1, BAR_LEN_2, BAR_LEN_3};
const uint8_t local_bar_len_buttons[4] = {LOCAL_BAR_LEN_0, LOCAL_BAR_LEN_1, LOCAL_BAR_LEN_2, LOCAL_BAR_LEN_3};
const uint8_t num_bar_buttons[3] = {NUM_BAR_0, NUM_BAR_1, NUM_BAR_2};
const uint8_t group_size_buttons[3] = {GROUP_SIZE_0, GROUP_SIZE_1, GROUP_SIZE_2};
const uint8_t group_repeat_buttons[3] = {GROUP_REPEAT_0, GROUP_REPEAT_1, GROUP_REPEAT_2};
const uint8_t tap_tempo_buttons[4] = {TAP_TEMPO_0, TAP_TEMPO_1, TAP_TEMPO_2, TAP_TEMPO_3};
const uint8_t rand_time_buttons[3] = {RAND_TIME_0, RAND_TIME_1, RAND_TIME_2};
const uint8_t local_rand_time_buttons[3] = {LOCAL_RAND_TIME_0, LOCAL_RAND_TIME_1, LOCAL_RAND_TIME_2};

Adafruit_NeoTrellisM4 trellis;

bool letter[6][20] = {{0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
                      {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0},
                      {0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
                      {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
                      {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0},
                      {0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0}};

// Bar stuff
const int counter_color[8] = {0xFF0000, 0xFF2000, 0xFF4800, 0xFF8500, 0xFFAF00, 0xAFFF00, 0x60FF00, 0x00FF00};
uint8_t num_bars = MAX_BARS-1;
uint8_t group_size = 0;
uint8_t group_repeats = 0;
uint8_t bar_num = 0;
bool rand_bar = false;
bool apply_all = false;
int group_size_counter = group_size + 1;
int group_repeats_counter = group_repeats + 1;

// Time stuff
uint8_t num_beats = MAX_BEATS-1;
uint8_t beat_num = 0;
uint8_t clock_sync = 0;
uint8_t rand_time = 0;
unsigned long beat_len = 125000;  // Corresponds to 120 bpm 16th notes
unsigned long off_beat_len = 125000;
unsigned long last_beat = micros();
unsigned long tap_timer = 0;
bool tapping = false;
unsigned long clk_timer = 0;
uint8_t clock_counter = 0;
midiEventPacket_t clock_packet = {0x0F, 0xF8};

// Permanent stuff
bool play = true;
bool show_mode = false;

enum page {
  show_all = 0,
  edit_time = 1,
  edit_notes = 2,
  edit_other = 3,
  edit_bars = 4,
  edit_presets = 5
};
page page_select = show_all;

// Melody & instrument stuff
instruments ins[NUM_INS];
int bar_to_copy = -1;
uint8_t instrument_selector = 0;
uint8_t ins_copy = 0;
const int frets[12] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19};

// FUNCTIONS
void takeStep() {
  last_beat = micros();
  beat_num++;
  beat_num %= num_beats + 1;
  if (beat_num == 0)
  {
    group_size_counter--;
    if (group_size_counter <= 0)
    {
      group_size_counter = group_size + 1;
      group_repeats_counter--;
      if (group_repeats_counter <= 0)
      {
        group_repeats_counter = group_repeats + 1;
        if (rand_bar)
        {
          bar_num = random(num_bars + 1);
        }
        else
        {
          bar_num++;
        }
      }
      else
      {
        bar_num-= group_size;
      }
    }
    else
    {
      bar_num++;
    }
    bar_num += num_bars + 1;
    bar_num %= num_bars + 1;
  }
  int variation = beat_len * rand_time / 14;
  off_beat_len = beat_len + random(-variation, variation);
  for (int i = 0; i < NUM_INS; i++)
  {
    ins[i].setTimePoint(bar_num, beat_num);
    ins[i].setNoteTimes(last_beat, off_beat_len);
    ins[i].setVel();
  }
}

int conditionalColor(bool button_status, int button_color) {
  if (button_status)
  {
    return button_color;
  }
  return 0x000000;
}

void setPixelColor(uint32_t p, uint32_t c) {
  static uint32_t prev_c[32];

  if(prev_c[p] != c)
  {
    trellis.setPixelColor(p, c);
    prev_c[p] = c;
  }
}

void display() {
  for (int i = 0; i < 4; i++)
  {
    if (beat_num & (8>>i))
    {
      setPixelColor(i<<3, 0xFFFFFF);
    }
    else
    {
      setPixelColor(i<<3, 0x000000);
    }
    setPixelColor(ins_sel_buttons[i], conditionalColor(instrument_selector & (8>>i), 0xFF8FFF));
  }

  if(play) setPixelColor(PLAY, 0x00FF00);
  else setPixelColor(PLAY, 0xFF0000);

  setPixelColor(BUMP_BEAT, counter_color[bar_num]);
  setPixelColor(BUMP_BAR, counter_color[bar_num]);
  setPixelColor(PAGE_SEL, counter_color[page_select]);

  if (show_mode)
  {
    for (int i = 0; i < NUM_NOTES; i++)
    {
      setPixelColor(note_buttons[i], conditionalColor(letter[page_select][i], 0xFFFFFF));
    }
  }
  else
  {
    int canvas[NUM_NOTES] = {0};
    switch (page_select)
    {
      case show_all: // SHOW ALL MELODIES
        for (int i = 0; i < NUM_NOTES; i++)
        {
          for (int j = 0; j < NUM_INS; j++)
          {
            canvas[i] |= ins[j].showNote(i);
          }
          setPixelColor(note_buttons[i], canvas[i]);
        }
        
        break;

      case edit_notes: // EDIT NOTES
        for (int i = 0; i < NUM_NOTES; i++)
        {
          setPixelColor(note_buttons[i], ins[instrument_selector].findMelodyEditColor(i));
        }
        
        break;

      case edit_other: // EDIT OTHER
        for (int i = 0; i < 4; i++)
        {
          setPixelColor(max_vel_buttons[i], conditionalColor(ins[instrument_selector].max_vel & (64>>i), 0xFF3500));
          setPixelColor(min_vel_buttons[i], conditionalColor(ins[instrument_selector].min_vel & (64>>i), 0xFF8800));
        }
        for (int i = 0; i < 3; i++)
        {
          setPixelColor(octave_buttons[i], conditionalColor(ins[instrument_selector].octave & (4>>i), 0x00FFFF));
          setPixelColor(vel_param_buttons[i], conditionalColor(ins[instrument_selector].vel_param & (4>>i), 0xFF0F00));
        }
        setPixelColor(PROB_0, conditionalColor(ins[instrument_selector].prob & 1, 0xFF2F2F));
        setPixelColor(PROB_1, conditionalColor(ins[instrument_selector].prob & 2, 0xFF2F2F));
        setPixelColor(VEL_MODE, ins[instrument_selector].velModeColor());
        setPixelColor(RANDOM_BEAT, conditionalColor(ins[instrument_selector].random_beat, 0xFFFF00));
        setPixelColor(BLACK_KEYS, conditionalColor(ins[instrument_selector].black_keys, 0xFFFFFF));
        setPixelColor(PANIC, 0xFF0000);
        break;

      case edit_presets: // EDIT PRESETS
        for (int i = 0; i < 4; i++)
        {
          setPixelColor(ins_copy_buttons[i], conditionalColor(ins_copy & (8>>i), 0xFF4FFF));
        }
        setPixelColor(PRESET_ROOT_BAR, 0x0000FF);
        setPixelColor(PRESET_ROOT_BEAT, 0x4000FF);
        setPixelColor(PRESET_CHORD_BAR, 0x0000FF);
        setPixelColor(PRESET_CHORD_BEAT, 0x4000FF);
        setPixelColor(PRESET_ARPEG, 0x00A01A);
        setPixelColor(PRESET_RAND, 0xFFFF00);
        setPixelColor(PRESET_CLEAR, 0xFF0000);
        setPixelColor(PRESET_COPY, 0xFF1FFF);
        setPixelColor(BAR_PRESET_UP, 0xFF0000);
        setPixelColor(BAR_PRESET_BLUESM, 0x0000FF);
        setPixelColor(BAR_PRESET_CO5, 0x00A01A);
        setPixelColor(BAR_PRESET_BLUES, 0x0000FF);
        setPixelColor(BAR_PRESET_POP, 0x4000FF);
        setPixelColor(BAR_PRESET_RAND, 0xFFFF00);
        setPixelColor(BAR_PRESET_MON, 0x4000FF);
        setPixelColor(BAR_PRESET_COPY, 0xFF1FFF);
        break;

      case edit_bars: // EDIT BARS
        for (int i = 0; i < 8; i++)
        {
          if ((i == bar_num) & !(beat_num%2))
          {
            setPixelColor(bar_copy_buttons[i], 0x000000);
          }
          else
          {
            setPixelColor(bar_copy_buttons[i], counter_color[ins[instrument_selector].bar_copy[i]]);
          }
        }
        for (int i = 0; i < 3; i++)
        {
          setPixelColor(num_bar_buttons[i], conditionalColor(num_bars & (4>>i), 0xFF0AA0));
          setPixelColor(group_size_buttons[i], conditionalColor(group_size & (4>>i), 0x4F0AFF));
          setPixelColor(group_repeat_buttons[i], conditionalColor(group_repeats & (4>>i), 0x1F0AFF));
        }
        setPixelColor(RAND_BAR, conditionalColor(rand_bar, 0xFFFF00));
        setPixelColor(APPLY_ALL, conditionalColor(apply_all, 0xFF4F1F));
        setPixelColor(EXCLUDE, conditionalColor(ins[instrument_selector].lock_bars, 0xFF1F1F));
        break;

      case edit_time: // EDIT TIME
        for (int i = 0; i < 4; i++)
        {
          setPixelColor(bar_len_buttons[i], conditionalColor(num_beats & (8>>i), 0x0FFF0A));
          setPixelColor(local_bar_len_buttons[i], conditionalColor(ins[instrument_selector].num_beats & (8>>i), 0x0FFF0A));
          setPixelColor(tap_tempo_buttons[i], conditionalColor(!tapping, 0xFF000F));
        }
        for (int i = 0; i < 3; i++)
        {
          setPixelColor(rand_time_buttons[i], conditionalColor(rand_time & (4>>i), 0x00FFFF));
          setPixelColor(local_rand_time_buttons[i], conditionalColor(ins[instrument_selector].rand_time & (4>>i), 0x00FFFF));
        }
        switch (clock_sync)
        {
        case 0:
          setPixelColor(CLOCK_SYNC, 0xFF0000);
          break;

        case 1:
          setPixelColor(CLOCK_SYNC, 0x00FF00);
          break;

        case 2:
          setPixelColor(CLOCK_SYNC, 0xFFFF00);
          break;
        
        default:
          break;
        }
        setPixelColor(FREE_RUNNING, conditionalColor(ins[instrument_selector].free_running, 0xFF4F00));
        break;
      
      default:
        break;
    }
  }
}

void update_bar_to_copy() {
  if (bar_to_copy == -1) {
    if(trellis.isPressed(BAR_COPY_0)) bar_to_copy = 0;
    else if (trellis.isPressed(BAR_COPY_1)) bar_to_copy = 1;
    else if (trellis.isPressed(BAR_COPY_2)) bar_to_copy = 2;
    else if (trellis.isPressed(BAR_COPY_3)) bar_to_copy = 3;
    else if (trellis.isPressed(BAR_COPY_4)) bar_to_copy = 4;
    else if (trellis.isPressed(BAR_COPY_5)) bar_to_copy = 5;
    else if (trellis.isPressed(BAR_COPY_6)) bar_to_copy = 6;
    else if (trellis.isPressed(BAR_COPY_7)) bar_to_copy = 7;
  }
  else {
    if(!trellis.isPressed(bar_copy_buttons[bar_to_copy])){
      bar_to_copy = -1;
    }
  }
}

void set_bar(int bar_num) {
  update_bar_to_copy();
  if (bar_to_copy != -1  & !ins[instrument_selector].lock_bars)
  {
    if (apply_all)
    {
      for (int i = 0; i < NUM_INS; i++)
      {
        if (!ins[i].lock_bars)
        {
          ins[i].bar_copy[bar_num] = bar_to_copy;
        }
      }
    }
    else
    {
      ins[instrument_selector].bar_copy[bar_num] = bar_to_copy;
    }
  }

}

void setup() {
  Serial.begin(9600);
  trellis.begin();
  trellis.setBrightness(80);
  trellis.enableUSBMIDI(true);
  for (int i = 0; i < NUM_INS; i++)
  {
    ins[i].begin(&trellis);
    ins[i].color_picker = i%6;
  }
  
  display();
}

void loop() {
  trellis.tick();
  display();

  while (trellis.available())
  {
    keypadEvent e = trellis.read();
    uint8_t butt = e.bit.KEY;
    trellis.setUSBMIDIchannel(instrument_selector);

    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      switch (butt)
      {        
        case BEAT_NUM_0:
          beat_num ^= 1 << 3;
          break;
        case BEAT_NUM_1:
          beat_num ^= 1 << 2;
          break;
        case BEAT_NUM_2:
          beat_num ^= 1 << 1;
          break;
        case BEAT_NUM_3:
          beat_num ^= 1;
          break;
        
        case INSTRUMENT_SEL_0:
            instrument_selector ^= 1 << 3;
            break;
        case INSTRUMENT_SEL_1:
          instrument_selector ^= 1 << 2;
          break;
        case INSTRUMENT_SEL_2:
          instrument_selector ^= 1 << 1;
          break;
        case INSTRUMENT_SEL_3:
          instrument_selector ^= 1;
          break;

        case PLAY:
          play ^= true;
          group_repeats_counter = group_repeats + 1;
          group_size_counter = group_size + 1;
          break;

        case BUMP_BEAT:
          takeStep();
          break;

        case BUMP_BAR:
          beat_num = -1;
          takeStep();
          break;
        
        case PAGE_SEL:
          page_select = (page) ((page_select + 1) % 6);
          show_mode = true;
          break;

        default:
          break;
      }

      if (show_mode)
      {
        // TODO add quick way to pick mode
      }
      else
      {
        switch (page_select)
        {
        case edit_notes:
          ins[instrument_selector].setTimePoint(bar_num, beat_num);
          // It is intentional that there is no break statement here
        case show_all:
          switch (butt)
          {
            case NOTE_0:
              ins[instrument_selector].noteOn(0, 80, (page_select == edit_notes));
              break;
            case NOTE_1:
              ins[instrument_selector].noteOn(1, 80, (page_select == edit_notes));
              break;
            case NOTE_2:
              ins[instrument_selector].noteOn(2, 80, (page_select == edit_notes));
              break;
            case NOTE_3:
              ins[instrument_selector].noteOn(3, 80, (page_select == edit_notes));
              break;
            case NOTE_4:
              ins[instrument_selector].noteOn(4, 80, (page_select == edit_notes));
              break;
            case NOTE_5:
              ins[instrument_selector].noteOn(5, 80, (page_select == edit_notes));
              break;
            case NOTE_6:
              ins[instrument_selector].noteOn(6, 80, (page_select == edit_notes));
              break;
            case NOTE_7:
              ins[instrument_selector].noteOn(7, 80, (page_select == edit_notes));
              break;
            case NOTE_8:
              ins[instrument_selector].noteOn(8, 80, (page_select == edit_notes));
              break;
            case NOTE_9:
              ins[instrument_selector].noteOn(9, 80, (page_select == edit_notes));
              break;
            case NOTE_10:
              ins[instrument_selector].noteOn(10, 80, (page_select == edit_notes));
              break;
            case NOTE_11:
              ins[instrument_selector].noteOn(11, 80, (page_select == edit_notes));
              break;
            case NOTE_12:
              ins[instrument_selector].noteOn(12, 80, (page_select == edit_notes));
              break;
            case NOTE_13:
              ins[instrument_selector].noteOn(13, 80, (page_select == edit_notes));
              break;
            case NOTE_14:
              ins[instrument_selector].noteOn(14, 80, (page_select == edit_notes));
              break;
            case NOTE_15:
              ins[instrument_selector].noteOn(15, 80, (page_select == edit_notes));
              break;
            case NOTE_16:
              ins[instrument_selector].noteOn(16, 80, (page_select == edit_notes));
              break;
            case NOTE_17:
              ins[instrument_selector].noteOn(17, 80, (page_select == edit_notes));
              break;
            case NOTE_18:
              ins[instrument_selector].noteOn(18, 80, (page_select == edit_notes));
              break;
            case NOTE_19:
              ins[instrument_selector].noteOn(19, 80, (page_select == edit_notes));
              break;

            default:
              break;
          }
          break;

        case edit_other:
          switch (butt)
          {
            case MAX_VEL_0:
              ins[instrument_selector].max_vel ^= 1<<6;
              break;
            case MAX_VEL_1:
              ins[instrument_selector].max_vel ^= 1<<5;
              break;
            case MAX_VEL_2:
              ins[instrument_selector].max_vel ^= 1<<4;
              break;
            case MAX_VEL_3:
              ins[instrument_selector].max_vel ^= 1<<3;
              break;

            case PROB_0:
              ins[instrument_selector].prob ^= 1;
              break;
            case PROB_1:
              ins[instrument_selector].prob ^= 2;
              break;

            case VEL_MODE:
              ins[instrument_selector].vel_mode = (velocity_mode) ((ins[instrument_selector].vel_mode + 1) % 5);
              break;

            case RANDOM_BEAT:
              ins[instrument_selector].random_beat ^= true;
              break;

            case PANIC:
              trellis.controlChange(123, 123);
              break;

            case BLACK_KEYS:
              ins[instrument_selector].black_keys ^= true;
              break;

            case MIN_VEL_0:
              ins[instrument_selector].min_vel ^= 1<<6;
              break;
            case MIN_VEL_1:
              ins[instrument_selector].min_vel ^= 1<<5;
              break;
            case MIN_VEL_2:
              ins[instrument_selector].min_vel ^= 1<<4;
              break;
            case MIN_VEL_3:
              ins[instrument_selector].min_vel ^= 1<<3;
              break;

            case OCTAVE_0:
              ins[instrument_selector].octave ^= 1<<2;
              break;
            case OCTAVE_1:
              ins[instrument_selector].octave ^= 1<<1;
              break;
            case OCTAVE_2:
              ins[instrument_selector].octave ^= 1;
              break;

            case VEL_PARAM_0:
              ins[instrument_selector].vel_param ^= 1<<2;
              break;
            case VEL_PARAM_1:
              ins[instrument_selector].vel_param ^= 1<<1;
              break;
            case VEL_PARAM_2:
              ins[instrument_selector].vel_param ^= 1;
              break;

            default:
              break;
          }
          ins[instrument_selector].min_vel = min(ins[instrument_selector].min_vel, ins[instrument_selector].max_vel);
          break;

        case edit_bars:
          switch (butt)
          {
            case BAR_COPY_0:
              set_bar(0);
              break;
            case BAR_COPY_1:
              set_bar(1);
              break;
            case BAR_COPY_2:
              set_bar(2);
              break;
            case BAR_COPY_3:
              set_bar(3);
              break;
            case BAR_COPY_4:
              set_bar(4);
              break;
            case BAR_COPY_5:
              set_bar(5);
              break;
            case BAR_COPY_6:
              set_bar(6);
              break;
            case BAR_COPY_7:
              set_bar(7);
              break;

            case RAND_BAR:
              rand_bar ^= true;
              break;

            case APPLY_ALL:
              apply_all ^= true;
              break;
            case EXCLUDE:
              ins[instrument_selector].lock_bars ^= true;
              break;

            case NUM_BAR_0:
              num_bars ^= 1<<2;
              break;
            case NUM_BAR_1:
              num_bars ^= 1<<1;
              break;
            case NUM_BAR_2:
              num_bars ^= 1;
              break;

            case GROUP_SIZE_0:
              group_size ^= 1<<2;
              break;
            case GROUP_SIZE_1:
              group_size ^= 1<<1;
              break;
            case GROUP_SIZE_2:
              group_size ^= 1;
              break;

            case GROUP_REPEAT_0:
              group_repeats ^= 1<<2;
              break;
            case GROUP_REPEAT_1:
              group_repeats ^= 1<<1;
              break;
            case GROUP_REPEAT_2:
              group_repeats ^= 1;
              break;
          }
          break;

        case edit_presets:
          switch (butt)
          {
            case PRESET_ROOT_BAR:
              for (int i = 0; i < MAX_BARS; i++)
              {
                ins[instrument_selector].note_on[0][i] = 1<<frets[i];
                ins[instrument_selector].note_off[0][i] = ~(1<<frets[i]);
              }
              break;

            case PRESET_ROOT_BEAT:
              for (int i = 0; i < MAX_BARS; i++)
              {
                for (int j = 0; j < MAX_BEATS; j++)
                {
                  ins[instrument_selector].note_on[j][i] = 1<<frets[i];
                  ins[instrument_selector].note_off[j][i] = 1<<frets[i];
                }
              }
              break;

            case PRESET_CHORD_BAR:
              for (int i = 0; i < MAX_BARS; i++)
              {
                uint32_t root = 1<<frets[i];
                uint32_t third = i < 6 ? 1<<frets[i+2] : 1<<frets[i-5];
                uint32_t fifth = i < 4 ? 1<<frets[i+4] : 1<<frets[i-3];
                ins[instrument_selector].note_on[0][i] = root | third | fifth;
                ins[instrument_selector].note_off[0][i] = ~(root | third | fifth);
              }
              break;

            case PRESET_CHORD_BEAT:
              for (int i = 0; i < MAX_BARS; i++)
              {
                uint32_t root = 1<<frets[i];
                uint32_t third = i < 6 ? 1<<frets[i+2] : 1<<frets[i-5];
                uint32_t fifth = i < 4 ? 1<<frets[i+4] : 1<<frets[i-3];
                for (int j = 0; j < MAX_BEATS; j++)
                {
                  ins[instrument_selector].note_on[j][i] = root | third | fifth;
                  ins[instrument_selector].note_off[j][i] = root | third | fifth;
                }
              }
              break;

            case PRESET_ARPEG:
              for (int i = 0; i < MAX_BARS; i++)
              {
                for (int j = 0; j < MAX_BEATS; j++)
                {
                  int note = 1<<frets[i + (j%3)*2];
                  ins[instrument_selector].note_on[j][i] = note;
                  ins[instrument_selector].note_off[j][i] = note;
                }
              }
              break;

            case PRESET_RAND:
              for (int i = 0; i < MAX_BARS; i++)
              {
                for (int j = 0; j < MAX_BEATS; j++)
                {
                  int note = random(NUM_NOTES);
                  ins[instrument_selector].note_on[j][i] = 1<<note;
                  ins[instrument_selector].note_off[j][i] = 1<<note;
                }
              }
              break;

            case PRESET_CLEAR:
              for (int i = 0; i < MAX_BARS; i++)
              {
                for (int j = 0; j < MAX_BEATS; j++)
                {
                  ins[instrument_selector].note_on[j][i] = 0;
                  ins[instrument_selector].note_off[j][i] = 0;
                }
              }
              break;

            case PRESET_COPY:
              for (int i = 0; i < MAX_BARS; i++)
              {
                for (int j = 0; j < MAX_BEATS; j++)
                {
                  ins[instrument_selector].note_on[j][i] = ins[ins_copy].note_on[j][i];
                  ins[instrument_selector].note_off[j][i] = ins[ins_copy].note_off[j][i];
                }
              }
              break;

            case BAR_PRESET_UP:
              for (int i = 0; i < MAX_BARS; i++)
              {
                ins[instrument_selector].bar_copy[i] = i;
              }
              break;
            case BAR_PRESET_BLUESM:
              ins[instrument_selector].bar_copy[0] = 0;
              ins[instrument_selector].bar_copy[1] = 0;
              ins[instrument_selector].bar_copy[2] = 3;
              ins[instrument_selector].bar_copy[3] = 0;
              ins[instrument_selector].bar_copy[4] = 4;
              ins[instrument_selector].bar_copy[5] = 3;
              ins[instrument_selector].bar_copy[6] = 0;
              ins[instrument_selector].bar_copy[7] = 0;
              break;
            case BAR_PRESET_CO5:
              ins[instrument_selector].bar_copy[0] = 0;
              ins[instrument_selector].bar_copy[1] = 3;
              ins[instrument_selector].bar_copy[2] = 6;
              ins[instrument_selector].bar_copy[3] = 2;
              ins[instrument_selector].bar_copy[4] = 5;
              ins[instrument_selector].bar_copy[5] = 1;
              ins[instrument_selector].bar_copy[6] = 4;
              ins[instrument_selector].bar_copy[7] = 7;
              break;
            case BAR_PRESET_BLUES:
              ins[instrument_selector].bar_copy[0] = 2;
              ins[instrument_selector].bar_copy[1] = 2;
              ins[instrument_selector].bar_copy[2] = 5;
              ins[instrument_selector].bar_copy[3] = 2;
              ins[instrument_selector].bar_copy[4] = 6;
              ins[instrument_selector].bar_copy[5] = 5;
              ins[instrument_selector].bar_copy[6] = 2;
              ins[instrument_selector].bar_copy[7] = 2;
              break;
            case BAR_PRESET_POP:
              ins[instrument_selector].bar_copy[0] = 2;
              ins[instrument_selector].bar_copy[1] = 6;
              ins[instrument_selector].bar_copy[2] = 0;
              ins[instrument_selector].bar_copy[3] = 5;
              ins[instrument_selector].bar_copy[4] = 2;
              ins[instrument_selector].bar_copy[5] = 6;
              ins[instrument_selector].bar_copy[6] = 0;
              ins[instrument_selector].bar_copy[7] = 5;
              break;
            case BAR_PRESET_RAND:
              for (int i = 0; i < MAX_BARS; i++)
              {
                ins[instrument_selector].bar_copy[i] = random(0, 8);
              }
              break;
            case BAR_PRESET_MON:
              for (int i = 0; i < MAX_BARS; i++)
              {
                ins[instrument_selector].bar_copy[i] = 0;
              }
              break;
            case BAR_PRESET_COPY:
              for (int i = 0; i < MAX_BARS; i++)
              {
                ins[instrument_selector].bar_copy[i] = ins[ins_copy].bar_copy[i];
              }
              break;

            case INS_COPY_0:
              ins_copy ^= 1 << 3;
              break;
            case INS_COPY_1:
              ins_copy ^= 1 << 2;
              break;
            case INS_COPY_2:
              ins_copy ^= 1 << 1;
              break;
            case INS_COPY_3:
              ins_copy ^= 1;
              break;

            default:
              break;
          }
          break;
        
        case edit_time:
          switch (butt)
          {
            case BAR_LEN_0:
              num_beats ^= 1<<3;
              break;
            case BAR_LEN_1:
              num_beats ^= 1<<2;
              break;
            case BAR_LEN_2:
              num_beats ^= 1<<1;
              break;
            case BAR_LEN_3:
              num_beats ^= 1;
              break;

            case TAP_TEMPO_0:
            case TAP_TEMPO_1:
            case TAP_TEMPO_2:
            case TAP_TEMPO_3:
              tap_timer = micros();
              tapping = true;
              break;

            case LOCAL_BAR_LEN_0:
              ins[instrument_selector].num_beats ^= 1<<3;
              break;
            case LOCAL_BAR_LEN_1:
              ins[instrument_selector].num_beats ^= 1<<2;
              break;
            case LOCAL_BAR_LEN_2:
              ins[instrument_selector].num_beats ^= 1<<1;
              break;
            case LOCAL_BAR_LEN_3:
              ins[instrument_selector].num_beats ^= 1;
              break;

            case FREE_RUNNING:
              ins[instrument_selector].free_running ^= true;
              break;

            case LOCAL_RAND_TIME_0:
              ins[instrument_selector].rand_time ^= 1<<2;
              break;
            case LOCAL_RAND_TIME_1:
              ins[instrument_selector].rand_time ^= 1<<1;
              break;
            case LOCAL_RAND_TIME_2:
              ins[instrument_selector].rand_time ^= 1;
              break;

            case RAND_TIME_0:
              rand_time ^= 1<<2;
              break;
            case RAND_TIME_1:
              rand_time ^= 1<<1;
              break;
            case RAND_TIME_2:
              rand_time ^= 1;
              break;

            case CLOCK_SYNC:
              clock_sync++;
              clock_sync %= 3;
              break;
            
            default:
              break;
          }
          break;

        default:
          break;
        }
      }
    }
  
    if (e.bit.EVENT == KEY_JUST_RELEASED)
    {
      if (butt == PAGE_SEL)
      {
        show_mode = false;
      }
      else
      {
        if (page_select == edit_notes || page_select == show_all)
        {
          switch (butt)
          {
            case NOTE_0:
              ins[instrument_selector].noteOff(0, 80, (page_select == edit_notes));
              break;
            case NOTE_1:
              ins[instrument_selector].noteOff(1, 80, (page_select == edit_notes));
              break;
            case NOTE_2:
              ins[instrument_selector].noteOff(2, 80, (page_select == edit_notes));
              break;
            case NOTE_3:
              ins[instrument_selector].noteOff(3, 80, (page_select == edit_notes));
              break;
            case NOTE_4:
              ins[instrument_selector].noteOff(4, 80, (page_select == edit_notes));
              break;
            case NOTE_5:
              ins[instrument_selector].noteOff(5, 80, (page_select == edit_notes));
              break;
            case NOTE_6:
              ins[instrument_selector].noteOff(6, 80, (page_select == edit_notes));
              break;
            case NOTE_7:
              ins[instrument_selector].noteOff(7, 80, (page_select == edit_notes));
              break;
            case NOTE_8:
              ins[instrument_selector].noteOff(8, 80, (page_select == edit_notes));
              break;
            case NOTE_9:
              ins[instrument_selector].noteOff(9, 80, (page_select == edit_notes));
              break;
            case NOTE_10:
              ins[instrument_selector].noteOff(10, 80, (page_select == edit_notes));
              break;
            case NOTE_11:
              ins[instrument_selector].noteOff(11, 80, (page_select == edit_notes));
              break;
            case NOTE_12:
              ins[instrument_selector].noteOff(12, 80, (page_select == edit_notes));
              break;
            case NOTE_13:
              ins[instrument_selector].noteOff(13, 80, (page_select == edit_notes));
              break;
            case NOTE_14:
              ins[instrument_selector].noteOff(14, 80, (page_select == edit_notes));
              break;
            case NOTE_15:
              ins[instrument_selector].noteOff(15, 80, (page_select == edit_notes));
              break;
            case NOTE_16:
              ins[instrument_selector].noteOff(16, 80, (page_select == edit_notes));
              break;
            case NOTE_17:
              ins[instrument_selector].noteOff(17, 80, (page_select == edit_notes));
              break;
            case NOTE_18:
              ins[instrument_selector].noteOff(18, 80, (page_select == edit_notes));
              break;
            case NOTE_19:
              ins[instrument_selector].noteOff(19, 80, (page_select == edit_notes));
              break;

            default:
              break;
          }
        }
        if (page_select == edit_bars) {
          for (int i = 0; i < MAX_BARS; i++) {
            if(butt == bar_copy_buttons[i]) {
              bar_to_copy = -1;
              update_bar_to_copy();
            }
          }
        }
        if ((page_select == edit_time))
        {
          switch (butt)
          {
          case TAP_TEMPO_0:
            beat_len = (micros()-tap_timer);
            last_beat = tap_timer;
            tapping = false;
            break;

          case TAP_TEMPO_1:
            beat_len = (micros()-tap_timer)/2;
            last_beat = tap_timer;
            tapping = false;
            break;

          case TAP_TEMPO_2:
            beat_len = (micros()-tap_timer)/3;
            last_beat = tap_timer;
            tapping = false;
            break;

          case TAP_TEMPO_3:
            beat_len = (micros()-tap_timer)/4;
            last_beat = tap_timer;
            tapping = false;
            break;
          
          default:
            break;
          }
        }
      }
    }
  }
  
  midiEventPacket_t midi_read = MidiUSB.read();

  if (play)
  {
    if (micros() >= (last_beat+off_beat_len*(1+clock_counter)/6.0)) // TODO: This is kind of bad logic. Rethink this
    {
      clock_counter++;
      if (clock_sync == 1) MidiUSB.sendMIDI(clock_packet);
    }
    if (clock_counter >= 6)
    {
      clock_counter = 0;
      takeStep();
    }
  }

  if ((clock_sync == 2) & (midi_read.byte1 == clock_packet.byte1))
  {
    beat_len = (micros()-clk_timer)*6;
    clk_timer = micros();
  }
  
  for (int i = 0; i < NUM_INS; i++)
  {
    trellis.setUSBMIDIchannel(i);
    ins[i].playback();
  }
}
