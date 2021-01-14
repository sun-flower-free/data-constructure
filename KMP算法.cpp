#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

////////////KMP算法实现
void get_next(string T,int *next){
    int i = 1,j = 0;
    next[1] = 0;
    while(i < T.length()){
        if(j == 0 || T[i] == T[j]){
            /*T[i]表示后缀单个字符,T[j]表示前缀单个字符*/
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
        
    }
}

void get_nextval(string T,int *nextval){
    int i = 1,j = 0;
    nextval[1] = 0;
    while(i < T.length()){
        if(j == 0 || T[i] == T[j]){
            ++i;
            ++j;
            if(T[i] != T[j])
                nextval[i] == j;
            else
                nextval[i] = nextval[j];
            
        }
        else 
            j = nextval[j];
    }
}
/*返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0.*/
/*T非空，1 ≤ pos ≤ T.length().*/
int Index_KMP(string S,string T,int pos){
    int i = pos;    /*i用于主串S当前位置下标值，若pos不为1，则从pos位置开始匹配*/
    int j = 1;      /*j用于子串T中当前位置下标值*/
    int next[255];
    get_next(T,next);
    while(i <= S.length() && j <= T.length()){
        if (j == 0 || S[i] == T[j])      //两子母相等则继续，
            ++i,++j;
        else                             //指针退后重新开始匹配
            j = next[j];                 //j退回合适的位置，i值不变
    }
    if (j > T.length())
        return i - T.length();
    else 
        return 0;

}
