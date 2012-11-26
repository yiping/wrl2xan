#include <stdio.h>

#include <vector>
#include <string>
#include <iostream>   
#include <fstream> 
#include <stdlib.h>
#include <string.h>

#include <iomanip>

#include <Eigen/Dense>
#include <map>
#include "functions.h"

const char COMMENT_CHAR = '#';
const char FIELD_BEGIN_CHAR = '[';
const char FIELD_END_CHAR = ']';


using namespace std;
using namespace Eigen;




int main (int c, char *v[]) 
{
	map<string, Matrix3f> Rotations;
  	map<string, Matrix3f>::iterator it;

	Rotations["Body_Hip"] = Matrix3f::Identity();
    Rotations["Body_Torso"] = Matrix3f::Identity();

	Rotations["Body_HNP"] = Matrix3f::Identity();

	Rotations["Body_LHY"] <<0,1,0, -1,0,0, 0,0,1;

	Rotations["Body_LHR"] <<0,1,0, 0,0,1, 1,0,0;
	Rotations["Body_LHP"] <<0,0,1, 1,0,0, 0,1,0;
	Rotations["Body_LKP"] <<0,0,1, 1,0,0, 0,1,0;
	Rotations["Body_LAP"] <<0,0,1, 1,0,0, 0,1,0;
	Rotations["Body_LAR"] <<0,0,1, 0,-1,0, 1,0,0;

	Rotations["Body_LSP"] <<1,0,0, 0,0,-1, 0,1,0;
	Rotations["Body_LSR"] <<0,0,-1, 0,1,0, 1,0,0;
	Rotations["Body_LSY"] <<0,1,0, -1,0,0, 0,0,1;
	Rotations["Body_LEP"] <<1,0,0, 0,0,-1, 0,1,0;
	Rotations["Body_LWY"] <<1,0,0, 0,1,0, 0,0,1;
	Rotations["Body_LWP"] <<1,0,0, 0,0,-1, 0,1,0;

	Rotations["Body_RHY"] <<0,1,0, -1,0,0, 0,0,1;
	Rotations["Body_RHR"] <<0,1,0, 0,0,1, 1,0,0;
	Rotations["Body_RHP"] <<0,0,1, 1,0,0, 0,1,0;
	Rotations["Body_RKP"] <<0,0,1, 1,0,0, 0,1,0;
	Rotations["Body_RAP"] <<0,0,1, 1,0,0, 0,1,0;
	Rotations["Body_RAR"] <<0,0,1, 0,-1,0, 1,0,0;

	Rotations["Body_RSP"] <<1,0,0, 0,0,-1, 0,1,0;
	Rotations["Body_RSR"] <<0,0,-1, 0,1,0, 1,0,0;
	Rotations["Body_RSY"] <<0,1,0, -1,0,0, 0,0,1;
	Rotations["Body_REP"] <<1,0,0, 0,0,-1, 0,1,0;
	Rotations["Body_RWY"] <<1,0,0, 0,1,0, 0,0,1;
	Rotations["Body_RWP"] <<1,0,0, 0,0,-1, 0,1,0;


	//cout<< Rotations["Body_Hip"] <<endl<<endl;
	//cout<< Rotations["Body_LHY"] <<endl<<endl;

	// show content:
	//for ( it=Rotations.begin() ; it != Rotations.end(); it++ )
	//	cout << "["<<(*it).first << "]"<<endl << (*it).second << endl<<endl;



	vector<string> files;
	scanWrlFiles(files, "./huboplus/huboplus/models");

	for (int i = 0; i<files.size(); i++)
	{
		cout<<files[i]<<endl;
		for ( it = Rotations.begin() ; it != Rotations.end(); it++ )
		{
			if (files[i].find((*it).first) != string::npos)
			{
				cout << "["<<(*it).first << "]"<<endl <<endl;
				
				Matrix3f R = (*it).second;
				convertWrlToXan(files[i], R);
				break;
			}
		}
	}


	return 0;
}
