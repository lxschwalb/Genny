#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include <instruments.h>

// Permanent buttons
#define BEAT_NUM_0        0
#define BEAT_NUM_1        8
#define BEAT_NUM_2        16
#define BEAT_NUM_3        24
#define PLAY              7
#define BUMP_BEAT         15
#define BUMP_BAR          23
#define PAGE_SEL          31

// TIME BUTTONS
#define BAR_LEN_0         1
#define BAR_LEN_1         9
#define BAR_LEN_2         17
#define BAR_LEN_3         25
#define BPM_0             2
#define BPM_1             10
#define BPM_2             18
#define BPM_3             26
#define BPM_4             3
#define BPM_5             11
#define BPM_6             19
#define BPM_7             27
#define SUBDIV_0          4
#define SUBDIV_1          12
#define SUBDIV_2          20
#define SUBDIV_3          28
#define NUM_BAR_0         5
#define NUM_BAR_1         13
#define NUM_BAR_2         21
#define RAND_BAR          29
#define RAND_TIME_0       6
#define RAND_TIME_1       14
#define RAND_TIME_2       22
#define RAND_TIME_3       30

// MELODY BUTTONS
#define INSTRUMENT_SEL_0  6
#define INSTRUMENT_SEL_1  14
#define INSTRUMENT_SEL_2  22
#define INSTRUMENT_SEL_3  30
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

// ISTRUMENT BUTTONS 1
#define MAX_VEL_0         1
#define MAX_VEL_1         9
#define MAX_VEL_2         17
#define MAX_VEL_3         25
#define MIN_VEL_0         2
#define MIN_VEL_1         10
#define MIN_VEL_2         18
#define MIN_VEL_3         26
#define PROB              4
#define RANDOM_BEAT       5
#define INSTRUMENT_COLOR  29
#define OCTAVE_0          12
#define OCTAVE_1          20
#define OCTAVE_2          28
#define BLACK_KEYS        13
#define PANIC             21
#define VEL_MODE          3
#define VEL_PARAM_0       11
#define VEL_PARAM_1       19
#define VEL_PARAM_2       27

// ISTRUMENT BUTTONS 2
#define BAR_COPY_0        1
#define BAR_COPY_1        9
#define BAR_COPY_2        17
#define BAR_COPY_3        25
#define BAR_COPY_4        2
#define BAR_COPY_5        10
#define BAR_COPY_6        18
#define BAR_COPY_7        26
#define INS_COPY_0        5
#define INS_COPY_1        13
#define INS_COPY_2        21
#define INS_COPY_3        29
#define PRESET_ROOT_BAR   3
#define PRESET_ROOT_BEAT  4
#define PRESET_CHORD_BAR  11
#define PRESET_CHORD_BEAT 12
#define PRESET_ARPEG      19
#define PRESET_RAND       20
#define PRESET_CLEAR      27
#define PRESET_COPY       28



// MISC DEFINITIONS
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
const uint8_t bpm_buttons[8] = {BPM_0, BPM_1, BPM_2, BPM_3, BPM_4, BPM_5, BPM_6, BPM_7};
const uint8_t subdiv_buttons[4] = {SUBDIV_0, SUBDIV_1, SUBDIV_2, SUBDIV_3};
const uint8_t bar_len_buttons[4] = {BAR_LEN_0, BAR_LEN_1, BAR_LEN_2, BAR_LEN_3};
const uint8_t rand_time_buttons[4] = {RAND_TIME_0, RAND_TIME_1, RAND_TIME_2, RAND_TIME_3};
const uint8_t num_bar_buttons[3] = {NUM_BAR_0, NUM_BAR_1, NUM_BAR_2};

Adafruit_NeoTrellisM4 trellis;

// Time stuff
const int counter_color[8] = {0xFFFFFF, 0xFF0000, 0xFF3F00, 0xFFA500, 0x00FF00, 0x00FFC5, 0x0000FF, 0x8800FF};
uint8_t num_bars = MAX_BARS-1;       //One less than actual number for efficient binary implementation
uint8_t bar_num = 0;
uint8_t num_beats = MAX_BEATS-1;     //One less than actual number for efficient binary implementation
uint8_t beat_num = 0;
uint8_t bpm = 120;          //One less than actual number to avoid division by zero
uint8_t subdivision = 1;    //One less than actual number to avoid division by zero
uint8_t rand_time = 0;
bool rand_bar = false;
int perfect_time = 60000/(bpm + 1)/(subdivision + 1);
int beat_len = perfect_time;
unsigned long t0 = millis();

// Permanent stuff
bool play = true;

enum page {
  show_all = 0,
  edit_time = 1,
  edit_melody = 2,
  edit_instrument1 = 3,
  edit_instrument2 = 4
};
page page_select = show_all;

// Melody & instrument stuff
instruments ins[NUM_INS];
uint8_t instrument_selector = 0;
uint8_t ins_copy = 0;
const int frets[12] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19};

// FUNCTIONS
void takeStep() {
  t0 = millis();

  if (rand_time)
  {
    int deviation = (perfect_time * rand_time) >> 4;
    beat_len = perfect_time + random(-deviation, deviation);
  }
  else
  {
    beat_len = perfect_time;
  }
  
  beat_num++;
  beat_num %= num_beats + 1;
  if (beat_num == 0)
  {
    if (rand_bar)
    {
      bar_num = random(num_bars + 1);
    }
    else
    {
      bar_num++;
      bar_num %= num_bars + 1;
    }
  }
  
  for (int i = 0; i < NUM_INS; i++)
  {
    trellis.setUSBMIDIchannel(i);
    ins[i].setTimePoint(bar_num, beat_num);
    ins[i].send_midi(&trellis);
  }
}

int buttonColor(bool button_status, int button_color) {
  if (button_status)
  {
    return button_color;
  }
  return 0x000000;
}

void display() {
  for (int i = 0; i < 4; i++)
  {
    if (beat_num & (8>>i))
    {
      trellis.setPixelColor(i<<3, 0xFFFFFF);
    }
    else
    {
      trellis.setPixelColor(i<<3, 0x000000);
    }
  }

  if(play) trellis.setPixelColor(PLAY, 0x00FF00);
  else trellis.setPixelColor(PLAY, 0xFF0000);

  trellis.setPixelColor(BUMP_BEAT, counter_color[bar_num]);
  trellis.setPixelColor(BUMP_BAR, counter_color[bar_num]);
  trellis.setPixelColor(PAGE_SEL, counter_color[page_select]);

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
        trellis.setPixelColor(note_buttons[i], canvas[i]);
      }
      for (int i = 0; i < 4; i++)
      {
        trellis.setPixelColor(ins_sel_buttons[i], buttonColor(instrument_selector & (8>>i), 0x2F00FF));
      }
      
      break;

    case edit_melody: // EDIT MELODY
      for (int i = 0; i < NUM_NOTES; i++)
      {
        trellis.setPixelColor(note_buttons[i], ins[instrument_selector].findMelodyEditColor(i));
      }
      for (int i = 0; i < 4; i++)
      {
        trellis.setPixelColor(ins_sel_buttons[i], buttonColor(instrument_selector & (8>>i), 0x2F00FF));
      }
      
      break;

    case edit_instrument1: // EDIT INSTRUMENT 1
      for (int i = 0; i < 4; i++)
      {
        trellis.setPixelColor(ins_sel_buttons[i], buttonColor(instrument_selector & (8>>i), 0x2F00FF));
        trellis.setPixelColor(max_vel_buttons[i], buttonColor(ins[instrument_selector].max_vel & (64>>i), 0xFF3500));
        trellis.setPixelColor(min_vel_buttons[i], buttonColor(ins[instrument_selector].min_vel & (64>>i), 0xFF8800));
      }
      for (int i = 0; i < 3; i++)
      {
        trellis.setPixelColor(octave_buttons[i], buttonColor(ins[instrument_selector].octave & (4>>i), 0x00FFFF));
        trellis.setPixelColor(vel_param_buttons[i], buttonColor(ins[instrument_selector].vel_param & (4>>i), 0x00FF00));
      }
      trellis.setPixelColor(PROB, ins[instrument_selector].probColor());
      trellis.setPixelColor(VEL_MODE, ins[instrument_selector].velModeColor());
      trellis.setPixelColor(RANDOM_BEAT, buttonColor(ins[instrument_selector].random_beat, 0xFFFF00));
      trellis.setPixelColor(BLACK_KEYS, buttonColor(ins[instrument_selector].black_keys, 0xFFFFFF));
      trellis.setPixelColor(PANIC, 0xFF0000);
      trellis.setPixelColor(INSTRUMENT_COLOR, ins[instrument_selector].color());
      break;

    case edit_instrument2: // EDIT INSTRUMENT 2
      for (int i = 0; i < 8; i++)
      {
        trellis.setPixelColor(bar_copy_buttons[i], counter_color[ins[instrument_selector].bar_copy[i]]);
      }
      for (int i = 0; i < 4; i++)
      {
        trellis.setPixelColor(ins_sel_buttons[i], buttonColor(instrument_selector & (8>>i), 0x2F00FF));
        trellis.setPixelColor(ins_copy_buttons[i], buttonColor(ins_copy & (8>>i), 0xFF008F));
      }
      trellis.setPixelColor(PRESET_ROOT_BAR, 0xFF0000);
      trellis.setPixelColor(PRESET_ROOT_BEAT, 0xFF0000);
      trellis.setPixelColor(PRESET_CHORD_BAR, 0xFF0000);
      trellis.setPixelColor(PRESET_CHORD_BEAT, 0xFF0000);
      trellis.setPixelColor(PRESET_ARPEG, 0xFF0000);
      trellis.setPixelColor(PRESET_RAND, 0xFF0000);
      trellis.setPixelColor(PRESET_CLEAR, 0xFF0000);
      trellis.setPixelColor(PRESET_COPY, 0xFF0000);
      break;

    case edit_time: // EDIT TIME
      for (int i = 0; i < 8; i++)
      {
        trellis.setPixelColor(bpm_buttons[i], buttonColor(bpm & (128>>i), 0x0000FF));
      }
      for (int i = 0; i < 4; i++)
      {
        trellis.setPixelColor(subdiv_buttons[i], buttonColor(subdivision & (8>>i), 0x2F00FF));
        trellis.setPixelColor(bar_len_buttons[i], buttonColor(num_beats & (8>>i), 0x00FF00));
        trellis.setPixelColor(rand_time_buttons[i], buttonColor(rand_time & (8>>i), 0xFFFF00));
      }
      for (int i = 0; i < 3; i++)
      {
        trellis.setPixelColor(num_bar_buttons[i], buttonColor(num_bars & (4>>i), 0xFF0000));
      }
      trellis.setPixelColor(RAND_BAR, buttonColor(rand_bar, 0xFFFF00));           
      break;
    
    default:
      break;
  }
}

void setup() {
  trellis.begin();
  trellis.setBrightness(80);
  trellis.enableUSBMIDI(true);
  display();
}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();

  while (trellis.available())
  {
    keypadEvent e = trellis.read();
    uint8_t butt = e.bit.KEY;
    trellis.setUSBMIDIchannel(instrument_selector);

    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      bool tog = (page_select == edit_melody);
      bool next_beat = play && (millis() >= (t0+(beat_len>>1)));

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

        case PLAY:
          play ^= true;
          break;

        case BUMP_BEAT:
          takeStep();
          break;

        case BUMP_BAR:
          beat_num = -1;
          takeStep();
          break;
        
        case PAGE_SEL:
          page_select = (page) ((page_select + 1) % 5);
          break;

        default:
          break;
      }

      for (int i = 0; i < NUM_INS; i++)
      {
        ins[i].setTimePoint(bar_num, beat_num);
      }

      switch (page_select)
      {
      case show_all:
      case edit_melody:
        switch (butt)
        {
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

          case NOTE_0:
            ins[instrument_selector].noteOn(0, 80, &trellis, tog, next_beat);
            break;
          case NOTE_1:
            ins[instrument_selector].noteOn(1, 80, &trellis, tog, next_beat);
            break;
          case NOTE_2:
            ins[instrument_selector].noteOn(2, 80, &trellis, tog, next_beat);
            break;
          case NOTE_3:
            ins[instrument_selector].noteOn(3, 80, &trellis, tog, next_beat);
            break;
          case NOTE_4:
            ins[instrument_selector].noteOn(4, 80, &trellis, tog, next_beat);
            break;
          case NOTE_5:
            ins[instrument_selector].noteOn(5, 80, &trellis, tog, next_beat);
            break;
          case NOTE_6:
            ins[instrument_selector].noteOn(6, 80, &trellis, tog, next_beat);
            break;
          case NOTE_7:
            ins[instrument_selector].noteOn(7, 80, &trellis, tog, next_beat);
            break;
          case NOTE_8:
            ins[instrument_selector].noteOn(8, 80, &trellis, tog, next_beat);
            break;
          case NOTE_9:
            ins[instrument_selector].noteOn(9, 80, &trellis, tog, next_beat);
            break;
          case NOTE_10:
            ins[instrument_selector].noteOn(10, 80, &trellis, tog, next_beat);
            break;
          case NOTE_11:
            ins[instrument_selector].noteOn(11, 80, &trellis, tog, next_beat);
            break;
          case NOTE_12:
            ins[instrument_selector].noteOn(12, 80, &trellis, tog, next_beat);
            break;
          case NOTE_13:
            ins[instrument_selector].noteOn(13, 80, &trellis, tog, next_beat);
            break;
          case NOTE_14:
            ins[instrument_selector].noteOn(14, 80, &trellis, tog, next_beat);
            break;
          case NOTE_15:
            ins[instrument_selector].noteOn(15, 80, &trellis, tog, next_beat);
            break;
          case NOTE_16:
            ins[instrument_selector].noteOn(16, 80, &trellis, tog, next_beat);
            break;
          case NOTE_17:
            ins[instrument_selector].noteOn(17, 80, &trellis, tog, next_beat);
            break;
          case NOTE_18:
            ins[instrument_selector].noteOn(18, 80, &trellis, tog, next_beat);
            break;
          case NOTE_19:
            ins[instrument_selector].noteOn(19, 80, &trellis, tog, next_beat);
            break;

          default:
            break;
        }
        break;

      case edit_instrument1:
        switch (butt)
        {
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

          case PROB:
            ins[instrument_selector].prob++;
            ins[instrument_selector].prob %= 5;
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

          case INSTRUMENT_COLOR:
            ins[instrument_selector].color_picker++;
            ins[instrument_selector].color_picker %= 6;
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

      case edit_instrument2:
        switch (butt)
        {
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

          case BAR_COPY_0:
            ins[instrument_selector].bar_copy[0]++;
            ins[instrument_selector].bar_copy[0] &= 7;
            break;
          case BAR_COPY_1:
            ins[instrument_selector].bar_copy[1]++;
            ins[instrument_selector].bar_copy[1] &= 7;
            break;
          case BAR_COPY_2:
            ins[instrument_selector].bar_copy[2]++;
            ins[instrument_selector].bar_copy[2] &= 7;
            break;
          case BAR_COPY_3:
            ins[instrument_selector].bar_copy[3]++;
            ins[instrument_selector].bar_copy[3] &= 7;
            break;
          case BAR_COPY_4:
            ins[instrument_selector].bar_copy[4]++;
            ins[instrument_selector].bar_copy[4] &= 7;
            break;
          case BAR_COPY_5:
            ins[instrument_selector].bar_copy[5]++;
            ins[instrument_selector].bar_copy[5] &= 7;
            break;
          case BAR_COPY_6:
            ins[instrument_selector].bar_copy[6]++;
            ins[instrument_selector].bar_copy[6] &= 7;
            break;
          case BAR_COPY_7:
            ins[instrument_selector].bar_copy[7]++;
            ins[instrument_selector].bar_copy[7] &= 7;
            break;

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
                ins[instrument_selector].note_off[j][i] = ~(1<<frets[i]);
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
                ins[instrument_selector].note_off[j][i] = ~(root | third | fifth);
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
                ins[instrument_selector].note_off[j][i] = ~(note);
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
                ins[instrument_selector].note_off[j][i] = ~(1<<note);
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
          case BPM_0:
            bpm ^= 1<<7;
            break;
          case BPM_1:
            bpm ^= 1<<6;
            break;
          case BPM_2:
            bpm ^= 1<<5;
            break;
          case BPM_3:
            bpm ^= 1<<4;
            break;
          case BPM_4:
            bpm ^= 1<<3;
            break;
          case BPM_5:
            bpm ^= 1<<2;
            break;
          case BPM_6:
            bpm ^= 1<<1;
            break;
          case BPM_7:
            bpm ^= 1;
            break;

          case SUBDIV_0:
            subdivision ^= 1<<3;
            break;
          case SUBDIV_1:
            subdivision ^= 1<<2;
            break;
          case SUBDIV_2:
            subdivision ^= 1<<1;
            break;
          case SUBDIV_3:
            subdivision ^= 1;
            break;

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

          case NUM_BAR_0:
            num_bars ^= 1<<2;
            break;
          case NUM_BAR_1:
            num_bars ^= 1<<1;
            break;
          case NUM_BAR_2:
            num_bars ^= 1;
            break;

          case RAND_TIME_0:
            rand_time ^= 1<<3;
            break;
          case RAND_TIME_1:
            rand_time ^= 1<<2;
            break;
          case RAND_TIME_2:
            rand_time ^= 1<<1;
            break;
          case RAND_TIME_3:
            rand_time ^= 1;
            break;

          case RAND_BAR:
            rand_bar ^= true;
            break;
          
          default:
            break;
        }
        perfect_time = 60000/(bpm + 1)/(subdivision + 1);
        break;

      default:
        break;
      }
    }
  
    if (e.bit.EVENT == KEY_JUST_RELEASED)
    {
      if (page_select == edit_melody || page_select == show_all)
      {
        bool tog = (page_select == edit_melody);
        bool next_beat = play && (millis() >= (t0+(beat_len>>1)));
        switch (butt)
        {
          case NOTE_0:
            ins[instrument_selector].noteOff(0, 80, &trellis, tog, next_beat);
            break;
          case NOTE_1:
            ins[instrument_selector].noteOff(1, 80, &trellis, tog, next_beat);
            break;
          case NOTE_2:
            ins[instrument_selector].noteOff(2, 80, &trellis, tog, next_beat);
            break;
          case NOTE_3:
            ins[instrument_selector].noteOff(3, 80, &trellis, tog, next_beat);
            break;
          case NOTE_4:
            ins[instrument_selector].noteOff(4, 80, &trellis, tog, next_beat);
            break;
          case NOTE_5:
            ins[instrument_selector].noteOff(5, 80, &trellis, tog, next_beat);
            break;
          case NOTE_6:
            ins[instrument_selector].noteOff(6, 80, &trellis, tog, next_beat);
            break;
          case NOTE_7:
            ins[instrument_selector].noteOff(7, 80, &trellis, tog, next_beat);
            break;
          case NOTE_8:
            ins[instrument_selector].noteOff(8, 80, &trellis, tog, next_beat);
            break;
          case NOTE_9:
            ins[instrument_selector].noteOff(9, 80, &trellis, tog, next_beat);
            break;
          case NOTE_10:
            ins[instrument_selector].noteOff(10, 80, &trellis, tog, next_beat);
            break;
          case NOTE_11:
            ins[instrument_selector].noteOff(11, 80, &trellis, tog, next_beat);
            break;
          case NOTE_12:
            ins[instrument_selector].noteOff(12, 80, &trellis, tog, next_beat);
            break;
          case NOTE_13:
            ins[instrument_selector].noteOff(13, 80, &trellis, tog, next_beat);
            break;
          case NOTE_14:
            ins[instrument_selector].noteOff(14, 80, &trellis, tog, next_beat);
            break;
          case NOTE_15:
            ins[instrument_selector].noteOff(15, 80, &trellis, tog, next_beat);
            break;
          case NOTE_16:
            ins[instrument_selector].noteOff(16, 80, &trellis, tog, next_beat);
            break;
          case NOTE_17:
            ins[instrument_selector].noteOff(17, 80, &trellis, tog, next_beat);
            break;
          case NOTE_18:
            ins[instrument_selector].noteOff(18, 80, &trellis, tog, next_beat);
            break;
          case NOTE_19:
            ins[instrument_selector].noteOff(19, 80, &trellis, tog, next_beat);
            break;

          default:
            break;
        }
      }
    }
  }
  
  if (play && (millis() >= (t0+beat_len)))
  {
    takeStep();
  }

  display();
}