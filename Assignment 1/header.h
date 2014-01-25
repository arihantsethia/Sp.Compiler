#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

#define RCOUNT      12
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[1;31m"
#define KGRN  "\x1B[1;32m"
#define KYEL  "\x1B[1;33m"
#define KBLU  "\x1B[1;34m"
#define KMAG  "\x1B[1;35m"
#define KCYN  "\x1B[1;36m"
#define KWHT  "\x1B[1;37m"

static map<string,int> registers ;
static int registerCount = 0;

#endif // HEADER_H_INCLUDED
