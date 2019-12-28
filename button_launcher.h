#ifndef __button_launcher_h__
#define __button_launcher_h__

class button_launcher : public button {
  private:
    String mLaunch[4];
  protected:
    void fire();
  public:
    button_launcher(int x, int y, int width, int height, unsigned int color, char c);
    static void init();
    void parse(const String& buffer);
};
#endif
