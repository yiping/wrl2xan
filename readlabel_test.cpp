#include <stdio.h>

#include <vector>
#include <string>
#include <iostream>   
#include <fstream> 
#include <stdlib.h>
#include <string.h>

#include <iomanip>

const char COMMENT_CHAR = '#';
const char FIELD_BEGIN_CHAR = '[';
const char FIELD_END_CHAR = ']';

using namespace std;
void readLabel(ifstream &cfg_ptr, const char *label)
{
	register int i;
	register unsigned char c = '\0';
	char line[100];

	bool stop = false;

	// Strip off blank lines and comment lines.
	// int get() -> Extracts a character from the stream and returns its value (casted to an integer).
	while (!stop && ((i = cfg_ptr.get()) != EOF))
	{
		c = (unsigned char) i;

		if ((c == '\n') || (c == COMMENT_CHAR))
		{
			while ((c != '\n') && ((i = cfg_ptr.get()) != EOF))
			{
				c = (unsigned char) i;
			}
		}
		else
		{
			stop = true;
		}
	}

	if (!stop) 
	{
		cerr << "Error: file EOF encountered before " << label <<
		      " found. - 1 \n";
		exit(4);
	}

	cfg_ptr.putback(c); //rewind (put character back)
						// Decrements the internal get pointer by one, 
						// and c becomes the character to be read 
						// at that position by the next input operation.

	// Read in the strings until label is found or EOF encountered.
	// The skipws flag (skip whitespaces) is set in standard streams on initialization
	while ((cfg_ptr >> line)) // will automatically skip all the spaces and enters 
	{
		cout<<"[unprocessed line] "<<line<<endl;
		if ((line[0] != COMMENT_CHAR) && (line[0] != '\n'))
		{
			if (strncmp(line, label, strlen(label)) == 0)
			{
				printf("found %s \n", label);
				return;
			}
		}
		c = '\0';
		// if '\n' or '#' are not the first character of a line
		while ((c != '\n') && ((i = cfg_ptr.get()) != EOF))  
		{
	 		c =  (unsigned char) i;
		}
	}

	cerr << "Error: file EOF encountered before " << label
			<< " found. - 2\n";
	exit(4);
}


char *getNextToken(ifstream &cfg_ptr )
{
	const char *delim =" ,\n\t\r"; 
	static char line[256] = "\0";    // initialize the line to empty

	if (cfg_ptr.eof())
	{
		cerr << "|- getNextToken error: unexpected EOF encountered - 1"
		   << endl;
		exit(1);
	}

	char *tok = strtok(NULL, delim);

	while ((tok == NULL) || (tok[0] == COMMENT_CHAR))
	{
		if (!cfg_ptr.eof())
		{
			cfg_ptr.getline(line, 256);
			tok = strtok(line, delim);
	  	}
	  	else
  		{
		 	cerr << "|- getNextToken error: unexpected EOF encountered - 2" << endl;
		 	exit(1);
	  	}
	}

	return tok;
}


int main (int c, char *v[]) 
{
	//ifstream fptr("Body_Torso_1.wrl");
	//ifstream fptr("convhull_Torso_1.wrl");
	//ifstream fptr("Body_Hip_1.wrl");
	//ifstream fptr("Body_RWY_1.wrl");

	ifstream fptr("Body_LWY_1.wrl");
	if (!fptr)
	{
		cerr << "Unable to open wrl file" << endl;
		exit(7);
	}

	typedef vector<float> Point;
	typedef vector<int> Index;

	vector<Point> points;
	vector<Index> indexVec;

	float ambIntensity;
	float shine;
	float scolor[3] = {0.0, 0.0, 0.0};
	float dcolor[3] = {0.0, 0.0, 0.0};
	readLabel(fptr, "ambientIntensity");
	fptr >> ambIntensity;
	readLabel(fptr, "diffuseColor");
	fptr >> dcolor[0] >> dcolor[1] >> dcolor[2]; 
	readLabel(fptr, "specularColor");
	fptr >> scolor[0] >> scolor[1] >> scolor[2];
	readLabel(fptr, "shininess");
	fptr >> shine;
	readLabel(fptr, "point");
	readLabel(fptr, "[");

	Point p(3,0);
	char str[100];
	char cc;
	int i = 0;
	int numPoints, numIdx;
	bool KeepGoing = 1;
	while (KeepGoing)
	{

		fptr >> str;
		//printf("--%s--\n", str);

		if (strncmp( str, "]", strlen("]")) == 0 )
		{
			printf("reach the end of point data block\n");
			KeepGoing = false;
		}
		else
		{
			sscanf (str,"%f", &p[0]);

			fptr >> p[1] >> p[2]; 
			//cc = fptr.peek();
			cc = fptr.get();//printf("%c\n", cc);
			points.push_back (p);
			//printf("p[%d] = [%f %f %f ]\n",i, p[0], p[1], p[2]);
			
			i++;
		}
	}
	numPoints = i;



	readLabel(fptr, "coordIndex");
	readLabel(fptr, "[");

/*	KeepGoing = 1;
	i = 0;

	char str1[256];
	char * str2;
	//fptr.getline(str1, 256);
	//printf("-[%s]-\n",str1);
	//fptr.getline(str1, 256);
	//printf("-[%s]-\n",str1);

	Index idx(4,0);
	while (KeepGoing)
	{

		//fptr >> str; // not robust! - failed case: 39,0, 27,-1,
		//printf("--%s--\n", str);

		fptr.getline(str1, 256);	// finish last line
		printf("-[%s]-\n",str1);
		fptr.getline(str1, 256, ','); // stop at first ','


  		// Trim leading space
		str2 = str1;
		int j = 0;
		// printf("{%c}", str1[0]);
		while (str1[j]==' '|| str1[j]=='\t')
		{
			// printf("check point");
			str2++;
			j++;
		}			

		printf("-[%s]-\n",str2);

		//printf("%c\n", fptr.peek());
		

		if (strncmp( str2, "]", strlen("]")) == 0 )
		{
			printf("reach the end of coordinate index data block\n");
			KeepGoing = false;
		}
		else
		{
			sscanf (str2,"%d", &idx[0]);
			//fptr.get();
			fptr >> idx[1];printf("%c\n", fptr.peek());
			fptr.get();
			fptr >> idx[2]; printf("%c\n", fptr.peek());
			fptr.get();
			fptr >> idx[3]; printf("%c\n", fptr.peek());
			//cc = fptr.peek();
			cc = fptr.get();
			indexVec.push_back (idx);
			printf("idx[%d] = [%d %d %d %d]\n",i, idx[0], idx[1], idx[2], idx[3]);
		for( int u = 0; u<MyVec.size();u++)
		{			printf("%c\n", cc);
			i++;
		}
	}
	numIdx = i;*/




	KeepGoing = 1;
	i = 0;

	char str1[256];
	char * str2, *str3;


	fptr.getline(str1, 256);	// finish last line (once)
	//printf("-[%s]-\n",str1);
	while (KeepGoing)
	{
		fptr.getline(str1, 256); // stop at '\n'

		// Trim str2 leading space
		str2 = str1;
		int j = 0;
		while (str1[j]==' '|| str1[j]=='\t')
		{
			str2++;
			j++;
		}	
		//printf("-[%s]-\n",str2);

		if (strncmp( str2, "]", strlen("]")) == 0 )
		{
			printf("reach the end of coordinate index data block\n");
			KeepGoing = false;
		}

		if (KeepGoing == 1)
		{
			Index idx;
			int temp;
			str3 = strtok(str2, ",");
			
			sscanf (str3,"%d", &temp); //printf("%d\n",temp);
			idx.push_back(temp);

			while (str3 != NULL)
			{
				str3 = strtok (NULL, ",");
				if (str3 != NULL)
				{
					sscanf (str3,"%d", &temp); //printf ("%d\n",temp);
					idx.push_back(temp);
				}
			} 

			indexVec.push_back (idx);
		}
	}

	numIdx = indexVec.size();


	fptr.close();


// A good set of settings for a light source would be to set the Diffuse and Specular
// components to the colour of the light source, and the Ambient to the same colour 
// - but at MUCH reduced intensity, 10% to 40% seems reasonable in most cases. 

	//ofstream ofs ("Body_Torso_1.xan");
	//ofs.width(12);
	//ofs.precision(5);

	ofstream ofs;

	//ofs.open("Body_Torso_1.xan",ios::out|ios::trunc); 
	//ofs.open("convhull_Torso_1.xan",ios::out|ios::trunc); 

	//ofs.open("Body_Hip_1.xan",ios::out|ios::trunc); 
	//ofs.open("Body_RWY_1.xan",ios::out|ios::trunc); 

	ofs.open("Body_LWY_1.xan",ios::out|ios::trunc); 
    if( !ofs.is_open())
	{
		cerr<<"xan File not open! - Error"<<endl<<endl; 
	}
	else
	{ 
		ofs.setf(ios::fixed,ios::floatfield); 
		ofs<<setw(12)<< double(0.000) <<setw(12)<< 0.000 <<setw(12)<< 0.000<<endl;	// emission
		ofs<<setw(12)<< ambIntensity*dcolor[0]<<setw(12)<<ambIntensity*dcolor[1]<<setw(12)<<ambIntensity*dcolor[2]<<endl;	// ambient
		ofs<<setw(12)<<dcolor[0]<<setw(12)<<dcolor[1]<<setw(12)<<dcolor[2]<<endl;	// diffuse
		ofs<<setw(12)<<scolor[0]<<setw(12)<<scolor[1]<<setw(12)<<scolor[2]<<endl;	// specular
		ofs<<setw(12)<<shine<<endl;		// shininess
		ofs<<setw(12)<<1.0<<endl;		// alpha
		ofs<<setw(12)<<1.0<<setw(12)<<1.0<<setw(12)<<1.0<<endl<<endl; // scale

		ofs<<setw(12)<< points.size() <<setw(12)<<indexVec.size()<<endl<<endl; // #_of_verteces  #_of_faces
		for( int u = 0; u<points.size();u++)	// verteces
		{
			ofs<<setw(15)<<points[u][0];
			ofs<<setw(15)<<points[u][1];
			ofs<<setw(15)<<points[u][2]<<endl;
		}

		ofs<<endl;

		for( int u = 0; u<indexVec.size();u++)	// verteces
		{
			ofs<<setw(2)<<indexVec[u].size() - 1;
		}
		ofs<<endl<<endl;

		for( int u = 0; u<indexVec.size();u++)	// verteces
		{
			ofs<<setw(15)<<indexVec[u][0];
			ofs<<setw(15)<<indexVec[u][1];
			ofs<<setw(15)<<indexVec[u][2]<<endl;
		}


		ofs.close();
	}





	printf("\n--- checking results: ---\n");
	printf("ambient intensity = %f\n ", ambIntensity);
	printf("shininess         = %f\n ", shine);
	printf("specular color    = %f, %f, %f\n ", scolor[0], scolor[1], scolor[2]);
	printf("diffuse color     = %f, %f, %f\n ", dcolor[0], dcolor[1], dcolor[2]);
	printf("number of verteces: %d\n", numPoints);
	printf("number of verteces: %d\n", numIdx);
	return 0;
}
