#include <bits/stdc++.h>
int Strlen(char *s){
  for(int i = 0;; ++i) if(s[i] == '\0') return i;
}
int main(){
  char s[100];
  scanf("%s", s);
  printf("%d %s\n", Strlen(s), s);
  return 0;
}