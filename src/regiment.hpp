#include <string>

using namespace std;

enum type_regiment {
  militia,
  artillery,
  archers,
  light_infantry,
  light_cavalry,
  heavy_infantry,
  heavy_cavalry,
};

class Regiment {
  uint id;
  uint size = 100;
  uint morale = 100;
  uint discipline = 100;
  uint drill = 0;
  uint experience = 0;
  type_regiment type;
  uint num_soldiers = 200;
public:
  Regiment();
  ~Regiment();
};

class Lancer : public Regiment {
public:
  Lancer();
  ~Lancer();
};

class Infantry : public Regiment {
public:
  Infantry();
  ~Infantry();
};

class Artillery : public Regiment {
public:
  Artillery();
  ~Artillery();
};

class Cavalry : public Regiment {
public:
  Cavalry();
  ~Cavalry();
};

class Archer : public Regiment {
public:
  Archer();
  ~Archer();
};

class Militia : public Regiment {
public:
  Militia();
  ~Militia();
};
