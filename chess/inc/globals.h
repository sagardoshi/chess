#ifndef GLOBALS_H
#define GLOBALS_H

// No cstring will be >7 characters (biggest are 'Bishop\0' and 'Knight\0')
const int MAX_LEN = 7;
// Longest possible: "Black’s Bishop moves from B4 to C3 taking White’s Knight"
const int MSG_MAX = 56;

const bool WHITE = true;
const bool BLACK = false;

const int FILES = 8;
const int RANKS = 8;


#endif
