#pragma once
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

typedef vector < unordered_map<string, string>> hashMap;

hashMap read_csv(string filename) {
  hashMap data;
  ifstream file(filename);
  string line, key, value;
  if (file.is_open()) {
    while (getline(file, line)) {
      stringstream ss(line);
      getline(ss, key, ',');
      while (getline(ss, value, ',')) {
        data[ key ].push_back(value);
      }
    }
    file.close();

  }
  return data;
}

void print_csv(hashMap data) {
  for (auto& x : data) {
    cout << " " << x.first << " ";
    for (auto& y : x.second) {
      cout << y << " ";
    }
    cout << endl;
  }

}