/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }

  char str1[] ="./huboplus/model/Boday_LWY_1.xan|./huboplus/model/Boday_LWY_2.xan";
  //char str1[] ="./huboplus/model/Boday_LWY_1.xan";
  printf ("Original string is \"%s\" \n",str1);
  char * pch1;
  pch1 = strtok (str1,"|");
  while (pch1 != NULL)
  {
    printf ("%s\n",pch1);
    pch1 = strtok (NULL, "|");
  }
  return 0;
}
