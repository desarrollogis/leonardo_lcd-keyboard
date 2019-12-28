#ifndef __button_h__
#define __button_h__

class button {
  private:
    static char sC;
    static unsigned long sT;
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    int mColor;
    void erase();
  protected:
    char mC;
    void setChar(char c);
    virtual void fire();
  public:
    button(int x, int y, int width, int height, unsigned int color, char c);
    static void init();
    void draw();
    void stroke(int x, int y);
};
#endif
