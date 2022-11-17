#ifndef _MAIN_H_
#define _MAIN_H_

#include <string>

int Function(int a);
int* Function(int *c);
const int& Function(int a,int &b);
int (*Function(const std::string &str))(int);
void Function(void(*callbackFunction)(void *),void *args);

#endif