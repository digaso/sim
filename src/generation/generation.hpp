#include <iostream>
#include <random>
#include <vector>
#include <list>
#include "FastNoiseLite.h"


vector<float> generate_noise(int rows, int cols, float frequency, int seed, int octaves) {
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
  noise.SetFractalType(FastNoiseLite::FractalType_FBm);
  noise.SetSeed(seed);
  noise.SetFrequency(frequency);
  noise.SetFractalOctaves(octaves);
  noise.SetFractalLacunarity(2.0f);
  noise.SetFractalGain(0.5f);
  noise.SetFractalWeightedStrength(0.0f);



  vector<float> noiseData(rows * cols);
  int index = 0;
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      noiseData[ index++ ] = noise.GetNoise((float)x, (float)y);
    }
  }
  return noiseData;
}



float** setup(int rows, int cols, float frequency, int seed, int octaves) {

  float** tiles = new float* [ rows ];
  for (int i = 0; i < rows; i++) {
    tiles[ i ] = new float[ cols ];
  }

  vector<float> noiseData = generate_noise(rows, cols, frequency, seed, octaves);
  int index = 0;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      tiles[ row ][ col ] = noiseData[ index++ ];
    }
  }

  return tiles;
}