#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "vertex.h"
using namespace std;

vector<string> ParseString(string str);
int StringToInt(string str);
void ReadData(string filename, vector<VERTEX*>& vertexes, unsigned int& truckcapacity, unsigned int& trucksamount);
void setcur(int x, int y);
void ReadDataFromConsole(vector<VERTEX*>& vertexes, unsigned int& truckCapacity, unsigned int& trucksAmount, unsigned int& vertexAmount);
void PrintWayToFile(vector<EDGE> way, string filename);

string& convert_String_To_string(System::String^ s, string& os);
System::String^ convert_string_To_String(string& os, System::String^ s);