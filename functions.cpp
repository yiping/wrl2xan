#include "functions.h"
unsigned char isFile =0x8;

const char COMMENT_CHAR = '#';
const char FIELD_BEGIN_CHAR = '[';
const char FIELD_END_CHAR = ']';


void scanWrlFiles(vector<string> &files, char* target_directory)
{
    int len;
    struct dirent *pDirEntry;
    DIR *pDir;

    regex_t re;
    int reti;

	// Compile regular expression 
    reti = regcomp(&re, ".*[.]wrl$", 0);
    if( reti )
	{ 
		fprintf(stderr, "Could not compile regex\n"); 
		exit(1); 
	}

	// pDir = opendir ("./");
	pDir = opendir (target_directory);

    if (pDir == NULL) 
	{
        printf ("Cannot open directory '%s'\n", target_directory);
        exit(1);
    }

    while ((pDirEntry = readdir(pDir)) != NULL) 
	{
		if ( pDirEntry->d_type == isFile)
		{
			string filename = string(pDirEntry->d_name);
			// Execute regular expression 
    		reti = regexec(&re, filename.c_str(), 0, NULL, 0);
			//printf ("filename = %s, reti = %d\n", filename.c_str(),reti);
    		if( !reti )
			{
         		//printf ("[%s]\n", pDirEntry->d_name);
				files.push_back( filename);   
			}

		}
    }
	//printf ("------------------\n");

	// Free compiled regular expression if you want to use the regex_t again 
    regfree(&re);
    closedir (pDir);
}




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


void convertWrlToXan(string filename_wrl, Matrix3f Rot)
{

	// open a .wrl file and grab model information
	filename_wrl = "./huboplus/huboplus/models/"+filename_wrl;
	ifstream fptr( filename_wrl.c_str()  );
	if (!fptr)
	{
		cerr << "Unable to open wrl file: "<<filename_wrl << endl;
		exit(7);
	}

	//typedef vector<float> Point;
	typedef vector<int> Index;

	vector<Vector3f> points;
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

	Vector3f p(0,0,0);
	char str[100];
	char cc;
	int i = 0;
	int numPoints, numIdx;
	bool KeepGoing = 1;
	while (KeepGoing)
	{

		fptr >> str;
		
		if (strncmp( str, "]", strlen("]")) == 0 )
		{
			printf("reach the end of point data block\n");
			KeepGoing = false;
		}
		else
		{
			sscanf (str,"%f", &p[0]);

			fptr >> p[1] >> p[2]; 
			cc = fptr.get();

			Vector3f p1 = Rot*p;	// convert to DH compliant coordinates

			points.push_back (p1);
			//printf("p[%d] = [%f %f %f ]\n",i, p[0], p[1], p[2]);
			
			i++;
		}
	}
	numPoints = i;



	readLabel(fptr, "coordIndex");
	readLabel(fptr, "[");

	KeepGoing = 1;
	i = 0;

	char str1[256];
	char * str2, *str3;

	fptr.getline(str1, 256);	// finish last line (once)
	//printf("-[%s]-\n",str1);
	while (KeepGoing)
	{
		fptr.getline(str1, 256); // get a whole line, stop at '\n'

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


	// reformat model information, write to .xan file

	// Note:
	// A good set of settings for a light source would be to set the Diffuse and Specular
	// components to the colour of the light source, and the Ambient to the same colour 
	// - but at MUCH reduced intensity, 10% to 40% seems reasonable in most cases. 

	ofstream ofs;
	size_t found;
	string fn = filename_wrl;
  	found = fn.find(".wrl");
	fn.erase(found, 4 );
	fn += ".xan";
	string filename_xan = fn;

	ofs.open(filename_xan.c_str(),ios::out|ios::trunc); 
    if( !ofs.is_open())
	{
		cerr<<"xan File not open! - Error: "<< filename_xan <<endl<<endl; 
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

	cout<<"-converted "<<filename_wrl<<" to "<<filename_xan<<endl; 

}



