// Blackhart headers.
#include "foundation/BkColor3.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkColor3 BkColor3_White(void) {
  return (struct BkColor3){.r = 255, .g = 255, .b = 255};
}

struct BkColor3 BkColor3_FromRGB(uint8 const r, uint8 const g, uint8 const b) {
  return (struct BkColor3){.r = r, .g = g, .b = b};
}
