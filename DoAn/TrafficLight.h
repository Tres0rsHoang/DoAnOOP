#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_
#include <ctime>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "SetScreen.h"

using namespace std;

class TrafficLight {
    int status;
    int lane;
    int x;
    int baseTime;
    int time;
public:
    TrafficLight();
    TrafficLight(screen Light, int lane, int status, int time);
    void GotoXY(int x, int y);
    void SetColor(int backgound_color, int text_color);
    int GetStatus();
    void _show();
    void _changeAndShow();
};

#endif