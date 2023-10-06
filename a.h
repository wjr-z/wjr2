#ifndef WJR_CLOCK_H__
#define WJR_CLOCK_H__

#include "LCD.h"
#include "key.h"
#include <string.h>

typedef struct Time {
    volatile int v;
} Time;

typedef struct Limiter {
    volatile int down, up;
    const unsigned char x, y, width;
} Limiter;

Limiter limiter[7] = {
    {-1, -1, 10, 0, 4}, {1, 13, 15, 0, 2}, {1, 31, 18, 0, 2}, {0, 24, 11, 1, 2},
    {0, 60, 14, 1, 2},  {0, 60, 17, 1, 2}, {0, 1, 8, 1, 2},
};

typedef volatile int vint;

vint clock[7] = {2023, 10, 5, 19, 59, 55, 0};
// 0 : 24 hour, 1 : 12 hour
vint AP = 0;

vint stopwatch[7];

static inline void clock_init_stopwatch() {
    memset(stopwatch, -1, sizeof(stopwatch));
}

static inline void clock_copy_stopwatch() {
    memcpy(stopwatch, clock, sizeof(clock));
}

typedef enum VarCase {
    c_Year = 0,
    c_Month = 1,
    c_Day = 2,
    c_hour = 3,
    c_minute = 4,
    c_second = 5,
    c_AP = 6,
} VarCase;

static inline int clock_is_stopwatch() {
    int i = 0;
    int f ;
    if (clock[c_AP] == 1) {
        clock[c_hour] += 12;
    }
    if (stopwatch[c_AP] == 1) {
        clock[c_AP] += 12;
    }

    f = memcmp(clock, stopwatch, sizeof(vint) * 6) == 0;

    if (clock[c_AP] == 1) {
        clock[c_hour] += 12;
    }
    if (stopwatch[c_AP] == 1) {
        clock[c_AP] += 12;
    }

    return f;
}

typedef enum ClockMode {
    s_Year = 0,
    s_Month = 1,
    s_Day = 2,
    s_hour = 3,
    s_minute = 4,
    s_second = 5,
    s_Clock = 6,
    s_Stopwatch = 7,
} ClockMode;

void clock_show(vint *arr, VarCase c) {
    int idx = (int)c;
    vint *var = &arr[idx];
    Limiter *lim = &limiter[idx];
    if (c != c_AP) {
        LCD_write_number(lim->x, lim->y, *var, lim->width);
    } else {
        const char *str = AP == 0 ? "  " : *var == 0 ? "AM" : "PM";
        LCD_write_chars(lim->x, lim->y, str, 2);
    }
}

static inline void clock_set(vint *arr, VarCase c, volatile int v) {
    int idx = (int)c;
    vint *var = &arr[idx];
    Limiter *lim = &limiter[idx];
    *var = v;
    clock_show(arr, c);
}

static inline int clock_inc(vint *arr, VarCase c) {
    int idx = (int)c;
    vint *var = &arr[idx];
    Limiter *lim = &limiter[idx];
    volatile int x = *var + 1;
    int f = x == lim->up;
    x = f ? lim->down : x;
    clock_set(arr, c, x);
    return f;
}

static inline int clock_dec(vint *arr, VarCase c) {
    int idx = (int)c;
    vint *var = &arr[idx];
    Limiter *lim = &limiter[idx];
    volatile int x = *var;
    int f = x == lim->down;
    x = f ? lim->up : x;
    clock_set(arr, c, x - 1);
    return f;
}

static inline void clock_inc_c() {
    if (!clock_inc(clock, c_second))
        return;
    if (!clock_inc(clock, c_minute))
        return;
    if (!clock_inc(clock, c_hour))
        return;
    if (AP == 1) {
        if (!clock_inc(clock, c_AP))
            return;
    }
    if (!clock_inc(clock, c_Day))
        return;
    if (!clock_inc(clock, c_Month))
        return;
    (void)clock_inc(clock, c_Year);
}

static inline void clock_const_display() {
    LCD_write_char(14, 0, '-');
    LCD_write_char(17, 0, '-');
    LCD_write_char(13, 1, ':');
    LCD_write_char(16, 1, ':');
}

static inline void clock_mode_show(ClockMode mode) {
    switch (mode) {
    case s_Year: {
        LCD_write_chars(2, 0, "Year", 6);
        break;
    }
    case s_Month: {
        LCD_write_chars(2, 0, "Month", 6);
        break;
    }
    case s_Day: {
        LCD_write_chars(2, 0, "Day", 6);
        break;
    }
    case s_hour: {
        LCD_write_chars(2, 0, "hour", 6);
        break;
    }
    case s_minute: {
        LCD_write_chars(2, 0, "minute", 6);
        break;
    }
    case s_second: {
        LCD_write_chars(2, 0, "second", 6);
        break;
    }
    case s_Clock: {
        LCD_write_chars(2, 0, "clock", 6);
        break;
    }
    case s_Stopwatch: {
        LCD_write_chars(2, 0, "sw", 6);
        break;
    }
    }
}

static inline void clock_display() {
    clock_const_display();
    clock_mode_show(s_Clock);
    int i;
    for (i = 0; i < 7; ++i) {
        clock_show(clock, (VarCase)(i));
    }
}

static inline void clock_switch(vint *arr) {
    volatile KEY key = key_none;
    volatile ClockMode clock_mode = s_Year;
    clock_mode_show(clock_mode);
    do {
        key = get_key();
        switch (key) {
        case key_switch: {
            ++clock_mode;
            if (clock_mode == s_Clock) {
                return;
            }
            clock_mode_show(clock_mode);
            break;
        }
        case key_up: {
            (void)clock_inc(arr, (VarCase)(clock_mode));
            delay_ms(60);
            break;
        }
        case key_down: {
            (void)clock_dec(arr, (VarCase)(clock_mode));
            delay_ms(60);
            break;
        }
        }
    } while (1);
}

static inline void clock_tense() {
    vint *hour = &clock[(int)c_hour];
    Limiter* hour_lim = &limiter[(int)c_hour];
    vint *ap = &clock[(int)c_AP];
    Limiter* ap_lim = &limiter[(int)c_AP];
    if (AP == 0) {
        AP = 1;

        ap_lim->up = 2;
        hour_lim->up = 12;
        int f = *hour >= 12;
        *hour = f ? *hour - 12 : *hour;
        *ap = f ? 1 : 0;
    } else {
        AP = 0;
        ap_lim->up = 1;
        int f = *ap != 0;
        hour_lim->up = 24;
        *hour = f ? *hour + 12 : *hour;
        *ap = 0;
    }
    clock_show(clock, c_hour);
    clock_show(clock, c_AP);
}

static inline void clock_change() {
    volatile KEY key = get_key();

    switch (key) {
    case key_switch: {
        clock_switch(clock);
        break;
    }
    case key_tense: {
        clock_tense();
        break;
    }
    case key_stopwatch:{
        clock_copy_stopwatch();
        clock_switch(stopwatch);
        break;
    }
    }

    clock_mode_show(s_Clock);
}

#endif // WJR_CLOCK_H__
