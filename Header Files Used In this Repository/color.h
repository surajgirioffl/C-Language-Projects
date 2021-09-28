/* SIMPLE COLOR 3 bit*/
#include<stdio.h>
//argument ~ 'f' or 'F' for foreground and 'b' or 'B' for background
//if user give wrong argument then foreground will work

void black(char ch); //ch for f/F or b/B
void red(char ch);
void green(char ch);
void yellow(char ch);
void blue(char ch);
void magenta(char ch);
void cyan(char ch);
void white(char ch);
void random_color();
void advcolor(char ch, int n);

void underline();
void reset(); //to reset all text colors and back to normal

//Definition part
void black(char ch) 
{
  if(ch == 'b' || ch == 'B')
  printf("\033[1;40m");
  else
  printf("\033[1;30m");
}

void red(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;41m");
  else
  printf("\033[1;31m");
}

void green(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;42m");
  else
  printf("\033[1;32m");
}

void yellow(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;43m");
  else
  printf("\033[1;33m");
}

void blue(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;44m");
  else
  printf("\033[1;34m");
}

void magenta(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;45m");
  else
  printf("\033[1;35m");
}

void cyan(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;46m");
  else
  printf("\033[1;36m");
}

void white(char ch) {
  if(ch == 'b' || ch == 'B')
  printf("\033[1;47m");
  else
  printf("\033[1;37m");
}

void underline() {
  printf("\033[4m");
}
void reset() {
  printf("\033[0m");
}


/*taken from advcolor.h header file*/
/* Advance 8 bit Colors combinations*/
void advcolor(char ch, int n) //ch for background or foreground and n for color option and n must be in 0 to 255. ch must be 'b' or 'B' for background or any other character for foreground
{
  if((ch == 'b' || ch == 'B') && (n >= 0 && n < 256))
  printf("\033[48;5;%dm", n);
  else
  printf("\033[38;5;%dm", n);
}