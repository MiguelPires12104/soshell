#include "shell.h"

void calc(char *value1, char *op, char *value2)
{
  double val1 = atof(value1);
  double val2 = atof(value2);
  double res;

  if (*op == '+')
  {
    res = val1 + val2;
  }
  else if (*op == '-')
  {
    res = val1 - val2;
  }
  else if (*op == '*')
  {
    res = val1 * val2;
  }
  else if (*op == '/')
  {
    if (val2 == 0)
    {
      printf("erro: val2 não pode ser 0\n");
      return ;
    }
    else  
    {
      res = val1 / val2;
    }
  }
  else if (*op == '^')
  {
    res = pow(val1, val2);
  }
  else
  {
    printf("erro de operador");
  }

  printf("resultado: %f\n", res);
}

//Calculadora de bits
void bits(char *op1, char *op, char *op2)
{
  long val1 = atoi(op1);
  long val2 = atoi(op2);
  long res;

  if(*op=='&'){
    res=val1 & val2;
  }else if (*op=='^')   
  {
    res=val1 ^ val2;
  }else if (*op=='|')
  {
    res= val1 | val2;
  }else if (*op=='<')
  {
    res= val1 << val2;
  }else if (*op=='>')
  {
    res= val1 >> val2;
  }else
  {
    printf("erro de operador");
  }
  printf("resultado: %ld\n", res);
}
