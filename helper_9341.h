#ifndef __helper_9341__
#define __helper_9341__

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

class helper_9341 {
  protected:
    static bool s_started;
    static TouchScreen s_ts;
    static bool draw(const bool& force = true);
    static void fix();
  public:
    static Adafruit_TFTLCD s_tft;
    static TSPoint s_point;
    static bool setup();
    static bool loop();
};
#endif
