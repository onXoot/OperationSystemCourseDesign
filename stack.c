#include"stack.h"
#include<stdio.h>
#include<stdlib.h>
/**************************************************/
/*  �������ܣ�ջ��˳��洢����ʼ��                */
/*  ����������ָ��sequence_stack�ͱ�����ָ�����st */
/*  ��������ֵ����                                */
/**************************************************/ 
 void init(sequence_stack *st)
 {
   st->top=0;
 }
/***************************************************/
/*  �������ܣ��ж�ջ��˳��洢���Ƿ�Ϊ��           */
/*  ����������sequence_stack�ͱ���st                */
/*  ��������ֵ��int���͡�1��ʾ�գ�0��ʾ�ǿ�       */
/***************************************************/
 int empty(sequence_stack st)
 {
   return(st.top? 0:1);
 }
/***************************************************/
/*  �������ܣ���ջ����˳��洢�����ֵ             */
/*  ����������sequence_stack�ͱ���st                */
/*  ��������ֵ��datatype���͡�����ջ�����ֵ        */
/***************************************************/
 datatype read(sequence_stack st)
 {
   if (empty(st))
   {
   	printf("\nstack is null!");
    exit(1);
   }
   else
     return st.a[st.top-1];
 }
 
/***************************************************/
/*  �������ܣ�ջ��˳��洢���Ĳ��루��ջ������     */
/*  ����������ָ��sequence_stack�ͱ�����ָ�����st */
/*            datatype�ͱ���x                      */
/*  ��������ֵ����                                 */
/***************************************************/
void push(sequence_stack *st,datatype x)
{
	   if(st->top==MAXSIZE)
	   {
		   printf("The sequence_stack is full!\n");
		   exit(1);
	   }
	   st->a[st->top]=x;
	   st->top++;
}
/***************************************************/
/*  �������ܣ�ջ��˳��洢����ɾ������ջ������     */
/*  ����������ָ��sequence_stack�ͱ�����ָ�����st */
/*  ��������ֵ����                                 */
/*  �ļ�����seqstack.c��������pop()                */
/***************************************************/
void pop(sequence_stack *st)
{
      if(st->top==0)
	  {
		  printf("\nThe sequence stack is empty!");
		  exit(1);
	  }
   st->top--;
}


 