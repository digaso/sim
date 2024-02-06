#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cctype>

using namespace std;

//list of words for constructing country names
vector<string> words_beginning = { "Great", "Mighty","Holy Nation of", "Union of" };


// List of syllables for constructing city names
std::vector<std::string> syllables = {
    "al", "am", "an", "ar", "as", "ba", "bel", "ber", "bi", "bo", "br", "ca", "car", "ci", "co", "cor", "da",
    "di", "do", "dor", "fa", "fel", "fi", "fo", "gal", "go", "gu", "hor", "ja", "je", "ji", "jo", "la", "le",
    "li", "lo", "lou", "ma", "mar", "mi", "mo", "mor", "na", "ne", "ni", "no", "nor", "ol", "or", "pa", "pel",
    "pe", "pi", "po", "por", "qua", "ra", "re", "ri", "ro", "ru", "sa", "se", "si", "so", "son", "ta", "te",
    "ti", "to", "tor", "ul", "va", "ve", "vi", "vo", "vu", "xa", "xe", "xi", "xo", "za", "ze", "zi", "zo", "guim", "os", "mu", "mum",
    "mus", "tul", "tum", "tus", "bu", "bum", "bus", "dum", "dus", "fum", "fus", "gum", "gus", "hum", "hus", "jum", "jus", "kum", "kus",
    "lum", "lus", "mum", "mus", "num", "nus", "pum", "pus", "qum", "qus", "rum", "rus", "sum", "sus", "tum", "tus", "vum", "vus", "wum","wa","we",
    "jha", "ya", "ye", "yi", "yo", "yu", "za", "ze", "zi", "zo", "zu", "sha", "she", "shi", "sho", "shu", "cha", "che", "chi", "cho", "chu",
    "tha", "the", "thi", "tho", "thu", "pha", "phe", "phi", "pho", "phu", "gha", "ghe", "ghi", "gho", "ghu", "kha", "khe", "khi", "kho", "khu",
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

string generateCultureName(string city) {
  string cultureName = city + "ian";
  return cultureName;
}

string generateGodName() {

  string godName = generateWord(1, 3); // Generate word with 1 to 3 syllables


  return godName;
}

string generateReligionName() {
  int numWords = 1;
  std::string religionName;

  for (int i = 0; i < numWords; ++i) {
    religionName += generateWord(2, 4); // Generate word with 2 to 4syllables
    if (i < numWords - 1) {
      religionName += " ";
    }
  }
  religionName += "ism";
  return religionName;
}

std::string generateCountryName() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> numWordsDist(0, 12); // Randomly select 1 or 2 words
  int chance = numWordsDist(gen);
  int numWords = 1 * (chance < 11) + 2 * (chance >= 11);
  std::string countryName;

  for (int i = 0; i < numWords; ++i) {
    uint maxsyl = numWords == 1 ? 4 : 3;
    countryName += generateWord(2, maxsyl);
    if (i < numWords - 1) {
      countryName += " ";
    }
  }

  return countryName;
}

// City name generator function
std::string generateCityName() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> numWordsDist(0, 10); // Randomly select 1 or 2 words
  int chance = numWordsDist(gen);
  int numWords = 1 * (chance < 7) + 2 * (chance >= 7);
  std::string cityName;

  for (int i = 0; i < numWords; ++i) {
    cityName += generateWord(2, 4); // Generate word with 2 to 4syllables
    if (i < numWords - 1) {
      cityName += " ";
    }
  }

  return cityName;
}