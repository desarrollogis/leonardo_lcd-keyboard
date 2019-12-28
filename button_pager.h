#ifndef __button_pager_h__
#define __button_pager_h__

#define PAGER_LESS -1
#define PAGER_PAGE 0
#define PAGER_MORE 1

class button_pager : public button {
  private:
    static int sPage;
    int mType;
    void updateDisplay();
  protected:
    void fire();
  public:
    button_pager(int x, int y, int width, int height, unsigned int color, int type);
    static int getPage();
    void parse(const String& buffer);
};
#endif
