#pragma once

struct Color {
  unsigned char r, g, b, a;

  Color();
  Color(unsigned int _r, unsigned int _g, unsigned int _b,
        unsigned int _a = 255);
};
