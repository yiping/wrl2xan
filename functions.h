
#ifndef __FUNCTIONS__
#define __FUNCTIONS__


#include <stdio.h>
#include <dirent.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
#include <regex.h>        

#include <stdlib.h>
#include <Eigen/Dense>
#include <iomanip>

using namespace std;
using namespace Eigen;



void scanWrlFiles(vector<string> &files, char* target_directory = "./");
void readLabel(ifstream &cfg_ptr, const char *label);
void convertWrlToXan(string filename_wrl, Matrix3f Rot);

#endif
