#include <stdio.h>
#include <dirent.h>

#include <vector>
#include <string>
#include <iostream>

#include <regex.h>        

#include <stdlib.h>

const char COMMENT_CHAR = '#';
const char NODE_BEGIN_CHAR = '{';
const char NODE_END_CHAR = '}';
const char FIELD_BEGIN_CHAR = '[';
const char FIELD_END_CHAR = ']';

int line_num; 



//----------------------------------------------------------------------------
//    Summary: scan a file from the current position until a particular string
//             is found.  It will exit (not return) if the EOF is encountered
//             before the search string is found.
//----------------------------------------------------------------------------


//------------------------------------------------------------------------------

unsigned char isFile =0x8;
using namespace std;

//int main(int argc, char **argv)
//{
//}

int main (int c, char *v[]) 
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

	vector<string> files;

    //if (c < 2) 
	//{
    //    printf ("Usage: testprog <dirname>\n");
    //    return 1;
    //}
    //pDir = opendir (v[1]);

	pDir = opendir ("./");

    if (pDir == NULL) 
	{
        printf ("Cannot open directory '%s'\n", v[1]);
        return 1;
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
         		printf ("[%s]\n", pDirEntry->d_name);
				files.push_back( filename);   
			}

		}
    }

	// Free compiled regular expression if you want to use the regex_t again 
    regfree(&re);
    closedir (pDir);
    return 0;

}


// int regexec(const regex_t *preg, const char *string,
//            size_t nmatch, regmatch_t *pmatch, int eflags);

// The regexec() function compares the null-ended string against the compiled 
// regular expression re to find a match between the two.
// The nmatch value is the number of substrings in string that the regexec() 
// function should try to match with subexpressions in re.  
// The array you supply for pmatch must have at least nmatch elements.
//
// The regexec() function fills in the elements of the array pmatch with offsets 
// of the substrings in string that correspond to the parenthesized subexpressions 
// of the original pattern given to the regcomp() function to create re. The zeroth 
// element of the array corresponds to the entire pattern. If there are more than 
// nmatch subexpressions, only the first (nmatch - 1) are stored. If nmatch is 0, or 
// if the REG_NOSUB flag was set when re was created with the regcomp() function, 
// the regexec() function ignores the pmatch argument.

// Data Type: regmatch_t
// rm_so
//    The offset in string of the beginning of a substring. 
//    Add this value to string to get the address of that part.
// rm_eo
//    The offset in string of the end of the substring. 

// printf
// .* The precision is not specified in the format string, 
// but as an additional integer value argument preceding the argument that has to be formatted.

/*
int main(void)
{
   regex_t    preg;
   char       *string = "a very simple simple simple string";
   char       *pattern = "\\(sim[a-z]le\\) \\1";
   int        rc;
   size_t     nmatch = 2;
   regmatch_t pmatch[2];
 
   if (0 != (rc = regcomp(&preg, pattern, 0))) {
      printf("regcomp() failed, returning nonzero (%d)\n", rc);
      exit(EXIT_FAILURE);
   }
 
   if (0 != (rc = regexec(&preg, string, nmatch, pmatch, 0))) {
      printf("Failed to match '%s' with '%s',returning %d.\n",
      string, pattern, rc);
   }
   else {
      printf("With the whole expression, "
             "a matched substring \"%.*s\" is found at position %d to %d.\n",
             pmatch[0].rm_eo - pmatch[0].rm_so, &string[pmatch[0].rm_so],
             pmatch[0].rm_so, pmatch[0].rm_eo - 1);
      printf("With the sub-expression, "
             "a matched substring \"%.*s\" is found at position %d to %d.\n",
             pmatch[1].rm_eo - pmatch[1].rm_so, &string[pmatch[1].rm_so],
             pmatch[1].rm_so, pmatch[1].rm_eo - 1);
   }
   regfree(&preg);
   return 0;
*/

// ^.*(.wrl)$
