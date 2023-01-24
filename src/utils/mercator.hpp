#include <cmath>

double mercatorX(double lon) {
  return lon * 20037508.34 / 180;
}

double mercatorY(double lat) {
  double y = log(tan((90 + lat) * M_PI / 360)) / (M_PI / 180);
  return y * 20037508.34 / 180;
}
