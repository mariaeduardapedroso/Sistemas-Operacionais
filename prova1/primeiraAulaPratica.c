#include<unistd.h>
#include <stdlib.h>

int main(){

  char *msg = (char *)(malloc(20*sizeof(char)));
  msg = "0i";
 // write(1,"oi mensagem");
  write(1,msg,2);
  return 0;
}
