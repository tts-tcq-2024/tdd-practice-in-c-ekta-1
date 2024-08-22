#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>
 #include <ctype.h>

char getSoundexCode(char c) {
    c = toupper(c);
   static  const char chartable[]={'0','1','2','3','0','1','2','0','0','2',
'2','4','5','5','0','1','2','6','2','3',
'0','1','0','2','0','2'};
if (isalpha(c)){
 return chartable[c-'A'];
}
 return '0';
}
void Check_Soundex(char code,int sIndex, char prevcode,char *soundex)
{
 if (code != '0' && code != prevcode) {
            soundex[sIndex++] = code;
            prevcode=code;
        }
}
void updateSoundexArray(const char *name, int len, char *soundex)
{
        int sIndex=1;
        char prevcode =getSoundexCode(name[0]);
        soundex[0]=toupper(name[0]);

  for (int i = 1; i < len && sIndex < 4; i++) 
    {
     char code =getSoundexCode(name[i]);
       Check_Soundex(code, sIndex, prevcode,soundex);
  soundex[sIndex]='\0';
}
}
void finalizeSoundex(char *soundex)
{
 while (strlen(soundex)<4)
  {
   soundex[strlen(soundex)]='0';
  }
 soundex[4]='\0';
}
void generateSoundex(const char *name, char *soundex)
{
    int len = strlen(name);
    soundex[0] = '\0';
  updateSoundexArray(name,len,soundex);
  finalizeSoundex(soundex);
}
   

#endif // SOUNDEX_H
