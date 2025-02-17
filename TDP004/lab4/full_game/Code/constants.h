#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
  Konstanter för olika aspekter av spelet. Dessa borde läsas från en fil.

  (inline använd för att slippa lägga definitionen av konstanterna i en cc-fil. Ej en del av
  kursen!)
 */
inline int const WIDTH  { 19 };
inline int const HEIGHT { 22 };
inline int TILE_SIZE { 20 };

inline int const SCREEN_WIDTH  { WIDTH  * (TILE_SIZE + 1) };
inline int const SCREEN_HEIGHT { HEIGHT * (TILE_SIZE + 1) };
inline int const FPS { 60 };

#endif
