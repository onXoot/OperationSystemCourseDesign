#ifndef CAL_H
#define CAL_H
double exec(char *b);
int create(char a[],int n);
int deal(char a[],int n1);
int match_kuohao(char c[]);
double readnumber(char f[],int *i);
int priority(char op);
int is_operation(char op);
void postfix(char e[],char f[]);
double evalpost(char f[]);
#endif
