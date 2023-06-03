#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cctype>

// List of syllables for constructing city names
std::vector<std::string> syllables = {
    "al", "am", "an", "ar", "as", "ba", "bel", "ber", "bi", "bo", "br", "ca", "car", "ci", "co", "cor", "da",
    "di", "do", "dor", "fa", "fel", "fi", "fo", "gal", "go", "gu", "hor", "ja", "je", "ji", "jo", "la", "le",
    "li", "lo", "lou", "ma", "mar", "mi", "mo", "mor", "na", "ne", "ni", "no", "nor", "o", "or", "pa", "pel",
    "pe", "pi", "po", "por", "qua", "ra", "re", "ri", "ro", "ru", "sa", "se", "si", "so", "son", "ta", "te",
    "ti", "to", "tor", "u", "va", "ve", "vi", "vo", "vu", "xa", "xe", "xi", "xo", "za", "ze", "zi", "zo", "guim"
};

// Generate a random number of syllables between minSyllables and maxSyllables
std::string generateWord(int minSyllables, int maxSyllables) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> numSyllablesDist(minSyllables, maxSyllables);

  int numSyllables = numSyllablesDist(gen);
  std::string word;

  for (int i = 0; i < numSyllables; ++i) {
    std::uniform_int_distribution<> syllableDist(0, syllables.size() - 1);
    std::string syllable = syllables[ syllableDist(gen) ];
    word += syllable;
  }

  word[ 0 ] = std::toupper(word[ 0 ]); // Capitalize the first letter

  return word;
}

// City name generator function
std::string generateCityName() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> numWordsDist(1, 2); // Randomly select 1 or 2 words

  int numWords = numWordsDist(gen);
  std::string cityName;

  for (int i = 0; i < numWords; ++i) {
    cityName += generateWord(2, 4); // Generate word with 2 to 4syllables
    if (i < numWords - 1) {
      cityName += " ";
    }
  }

  return cityName;
}