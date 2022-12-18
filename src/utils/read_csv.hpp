#pragma once
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

typedef vector < unordered_map<string, string>> hashMap;

hashMap read_csv(string filename) {
  hashMap data;
  ifstream file(filename);
  // Read the column names
  string line;
  getline(file, line);
  stringstream ss(line);
  string col_name;
  vector<string> col_names;
  while (getline(ss, col_name, ',')) {
    col_names.push_back(col_name);
  }
  // Read data, line by line
  while (getline(file, line)) {
    stringstream ss(line);
    string val;
    unordered_map<string, string> row;
    int col_idx = 0;
    while (getline(ss, val, ',')) {
      row[ col_names[ col_idx ] ] = val;
      col_idx++;
    }
    data.push_back(row);
  }
  return data;

}

void print_csv(hashMap data) {
  for (auto row : data) {
    for (auto col : row) {
      cout << col.first << " : " << col.second << " ";
    }
    cout << endl;
  }

}