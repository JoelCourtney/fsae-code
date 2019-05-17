#ifndef SEG_H
#define SEG_H

class Seg {
  static unsigned short int plex;

  static bool active;
  
public:
  static void initialize();
  static void write(unsigned int n);

  static bool isActive();
};

#endif
