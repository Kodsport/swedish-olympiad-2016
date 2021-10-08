#include <cstdio>

int main(){
  int ch;
  while( (ch = getchar()) != EOF ){
    if(ch != '#') putchar(ch);
    else putchar('e');
  }
}
