#include "Header.h"

// Default constructor
Header::Header () {
  this->MAGIC = "";
  this->W = 0;
  this->H = 0;
  this->MC = 0;
}

// Copy constructor
Header::Header (const Header& HDR) {
  this->MAGIC = HDR.MAGIC; // Why can I access private data here?
  this->W = HDR.W;
  this->H = HDR.H;
  this->MC = HDR.MC;
}

// Param constructor
Header::Header (std::string m, int w, int h, int mc) {
  this->MAGIC = m;
  this->W = w;
  this->H = h;
  this->MC = mc;
}

// Destructor
Header::~Header () {}

// Simple getter
std::string Header::magic () const { return this->MAGIC; }
int Header::width () const { return this->W; }
int Header::height () const { return this->H; }
int Header::max_color () const { return this->MC; }

// Simple setter
void Header::set_magic(string magic) { this->MAGIC = magic; }
void Header::set_width(int w) { this->W = w; }
void Header::set_height(int h) { this->H = h; }
void Header::set_max_color(int mc) { this->MC = mc; }

// Assignment
Header& Header::operator= (const Header& hdr) {
  if (this == &hdr) return *this;  // What does this line do?
  this->MAGIC = hdr.MAGIC;
  this->W     = hdr.W;
  this->H     = hdr.H;
  this->MC    = hdr.MC;
  return *this;
}

// Output
std::ostream& operator<< (std::ostream& out, const Header& hdr) {
  return out  << hdr.magic() << std::endl
              << hdr.width() << std::endl
              << hdr.height() << std::endl
              << hdr.max_color() << std::endl;
}
