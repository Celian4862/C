#ifndef TP_H
#define TP_H

typedef struct {
    int duration; // active duration of the lane in seconds
    char lane[5]; // main or alt
} Traffic;

#endif