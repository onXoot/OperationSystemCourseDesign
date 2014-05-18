#include "stack.h"
#include "cal.h"
#include <stdio.h>
#include <string.h>

double exec(char *b){
	char f[100];
	deal(b,strlen(b));
	match_kuohao(b);
	postfix(b,f);
	return evalpost(f);
}
   
/*******************************************************/
/*  函数功能: 对输入的字符串中的负号进行处理!          */
/*******************************************************/
int deal(char a[],int n1)
{
 int i=0,k,k1;
 while(i<=n1){
	 if(a[0]=='-'){             //当多项式中第一个字符就为负号时!
		 for(k=n1;k>=0;k--)
		  a[k+2]=a[k];      //将所有字符的元素后移2个单位!
          n1=n1+2;
     a[0]='(';                //第一个位置插入'(';
     a[1]='0';                //第二个位置插入'0';
     k=4;
     while(1){
	   if(((a[k]>='0')&&(a[k]<='9'))||(a[k]=='.')) k++;
	   else break;
	 }
     for(k1=n1;k1>=k;k1--)
	   a[k1+1]=a[k1];
     n1++;
     a[k]=')';               //插入相应的')';
  }
	 if((a[i]=='(')&&(a[i+1]=='-')){  //当负号在其他位置的情况:相应的只需在负号前插入一个'0'即可;
	     for(k=n1;k>i;k--)
		      a[k+1]=a[k];
	     a[i+1]='0';
	     n1++;
	 }
  else i++;
 }
  a[n1+1]='\0';
  k=n1+1;
  return k;                  //字符串的实际长度发生变化，故将其返回!
}
 /******************************************************/
 /* 函数功能:判断表达式括号是否匹配                    */
 /* 函数参数:char类型数组c                         	   */
 /* 函数返回值:int类型。返回1为匹配,返回0为不匹配	   */
 /******************************************************/
int match_kuohao(char c[])
 {
   int i=0;
   sequence_stack s;
   init(&s);
   while(c[i]!='=')
   {
     switch(c[i])
     {
       case '{':
       case '[':
       case '(':push(&s,c[i]);break;
       case '}':if(!empty(s)&&read(s)=='{'  )
              {pop(&s);break;}
             else return 0;
       case ']':if(!empty(s)&&read(s)=='['  )
              {pop(&s);break;}
             else return 0;
       case ')':if(!empty(s)&&read(s)=='('  )
                  {pop(&s);break;}
             else return 0;
     }
     i++;
   }
   return (empty(s));/*栈为空则匹配，否则不匹配*/
 }
/****************************************************/
/*  函数功能：将数字字符串转变成相应的数            */
/*  函数参数：char类型数组f，指向int类型变量的指针i */
/*  函数返回值：double类型。返回数字字符串对应的数  */
/****************************************************/
 double readnumber(char f[],int *i)
 { double x=0.0;
   int k=0;
   while(f[*i]>='0'&&f[*i]<='9') /*处理整数部分*/
   { x=x*10+(f[*i]-'0');
     (*i)++;
   }
   if (f[*i]=='.') /*处理小数部分*/
       {  (*i)++;
         while (f[*i]>='0' && f[*i]<='9')
             {x=x*10+(f[*i]-'0');
          (*i)++;
           k++;
             }
      }
   while (k!=0)
    { x=x/10.0;
      k=k-1;
    }
   return(x);
 }
 /**************************************************/
/*  函数功能：求运算符的优先级                   */
/*  函数参数：char类型变量op                     */
/*  函数返回值：int类型。返回各中运算符的优先级。 */
/**************************************************/
 int priority(char op)
 {
   switch(op)
   {
     case '=':return -1;
     case '(':return 0;
     case '+':
     case '-':return 1;
     case '*':
     case '/':return 2;
     default: return -1;
   }
 }
 /*******************************************************/
/*  函数功能：判断一个字符是否为运算符                 */
/*  函数参数：char类型变量op                           */
/*  函数返回值：int类型。返回1表示op运算符，否则不是。*/
/********************************************************/
int is_operation(char op)
 {
   switch(op)
   { case '+':
     case '-':
     case '*':
     case '/':return 1;
     default:return 0;
    }
 }
/**************************************************************/
/*  函数功能：将一个中缀表达式e转换为与它等价的后缀表达式f   */
/*  函数参数：char类型数组变量e和f                           */
/*  函数返回值：空                                            */
/****************************************************** ********/
void postfix(char e[],char f[])
 { int i=0,j=0;
   char opst[100];
   int top,t;
   top=0;
   opst[top]='=';top++;
   while(e[i]!='=')
   {
     if ((e[i]>='0'&&e[i]<='9')||e[i]=='.')
       f[j++]=e[i];                  /*遇到数字和小数点直接写入后缀表达式*/
     else if (e[i]=='(')                /*遇到左括号进入操作符栈*/
           { opst[top]=e[i];top++;}
          else if (e[i]==')')
            /*遇到右括号将其对应的左括号后的操作符全部写入后缀表达式*/
            { 
              t=top-1;
              while (opst[t]!='(') {f[j++]=opst[--top];t=top-1;}
              top--;            /*'('出栈*/
            }
            else if (is_operation(e[i]))         /* '+ ,-, *, /' */
                  {
                    f[j++]=' ';           /*用空格分开两个操作数*/
                    while (priority(opst[top-1])>=priority(e[i]))
                    f[j++]=opst[--top];
                    opst[top]=e[i];top++;     /*当前元素进栈*/
                  }
       i++;  /*处理下一个元素*/
    }
    while (top) f[j++]=opst[--top];
  }
/****************************************************/
/*  函数功能：求一个后缀表达式的值                  */
/*  函数参数：char类型数组f                         */
/*  函数返回值：double类型。返回后缀表达式的值      */
/*  文件名：evalpost.c，函数名：evalpost()              */
/****************************************************/
double evalpost(char f[])
 { double obst[100]; /*操作数栈*/
   int top=0;
   int i=0;
   double x1,x2;
   while (f[i]!='=')
       { if (f[i]>='0' && f[i]<='9')
       { obst[top]=readnumber(f,&i);top++;}
        else if (f[i]==' ')  i++;
          else if (f[i]=='+')
            { x2=obst[--top];
              x1=obst[--top];
              obst[top]=x1+x2;top++;
              i++;
                    }
              else if (f[i]=='-')
            {
              x2=obst[--top];
              x1=obst[--top];
              obst[top]=x1-x2;top++;
                      i++;
                    }
              else if (f[i]=='*')
            { x2=obst[--top];
              x1=obst[--top];
              obst[top]=x1*x2;top++;
              i++;
                    }
              else if (f[i]=='/')
            { x2=obst[--top];
              x1=obst[--top];
              obst[top]=x1/x2;top++;
              i++;
                    }
          }
    return obst[0];
  }

