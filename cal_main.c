#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cal.h"

char* exec(char *b){
	int n;
	char b[100]={'\0'},f[100],c;
	printf("input a string ,end with =:\n");
	gets(b);
	deal(b,strlen(b));
	match_kuohao(b);
	postfix(b,f);
	evalpost(f);
	printf("%f\n",evalpost(f));
}

int main(){
	exec();
	return;
		
 }
