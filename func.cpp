#include"func.h"


int instack(string c)//堆栈内部的运算符优先级
{
    int priority;
    if(c=="(")
        priority=0;
    if(c=="+"||c=="-")
        priority=1;
    if(c=="*"||c=="/")
        priority=2;
    if(c=="#")
        priority=0;
    return priority;
}
int outstack(string c)//堆栈外的运算符优先级
{
    int priority;
    if(c=="(")
        priority=3;
    if(c=="+"||c=="-")
        priority=1;
    if(c=="*"||c=="/")
        priority=2;
    return priority;
}

vector<string> InfixToPostfix(string str)
{
    vector<string> exp,res;
    string tstr="";
    for(std::size_t  i=0;i < str.length();i++)
    {
        //cout<<i<<endl;
        if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')')
        {
            if(tstr.length()!=0)
            {
                exp.push_back(tstr);
                tstr="";
            }
            tstr+=str[i];
            exp.push_back(tstr);
            tstr="";
        }
        else
        {
            tstr+=str[i];
        }
    }
    if(tstr.length()!=0)
        exp.push_back(tstr);
    exp.push_back("#");
    stack<string> stk;//存放 运算符和括号的栈
    stk.push("#");
    //string test="#";
    string st="";
    //cout<<exp.size()<<endl;
    //int i=0;
    for(std::size_t  i=0;i<exp.size()-1;i++)//for(i=0,st=exp[i];exp[i]!="#";i++,st=exp[i])
    {
        st=exp[i];
        if(st==")")
        {
            while(stk.top()!="(")
            {
                res.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
        }
        else if(st=="+"||st=="-"||st=="*"||st=="/"||st=="("||st=="#")
        {
            while(instack(stk.top())>=outstack(st))
            {
                res.push_back(stk.top());
                stk.pop();
            }
            stk.push(st);
        }
        else
        {
            res.push_back(st);
        }
    }
    while(!stk.empty())
    {
        if(stk.top()!="#")
        {
            res.push_back(stk.top());
        }
        stk.pop();
    }
    return res;
}

bool operation(string tmp,stack<double> &stk)
{
    double a=0,b=0;//操作数
    if(stk.size()<2)
    {
        cout<<"miss operator number"<<endl;
    }
    else
    {
        a=stk.top();
        stk.pop();
        b=stk.top();
        stk.pop();
        if(tmp=="+")
        {
            stk.push(b+a);
        }
        else if(tmp=="-")
        {
            stk.push(b-a);
        }
        else if(tmp=="*")
        {
            stk.push(b*a);
        }
        else if(tmp=="/")
        {
            if(a==0)
            {
                cout<<"denominator is 0!!!"<<endl;
                return false;
            }
            else
            {
                stk.push(b/a);
            }
        }
    }
    return true;
}

double postfix2ans(vector<string> exp)
{
    string tmp;//临时存放后缀表达式的每一项
    bool flag=true;
    stack<double> stk;
    for(std::size_t  i=0;i<exp.size();i++)
    {
        tmp=exp[i];
        if(tmp=="+"||tmp=="-"||tmp=="*"||tmp=="/")
        {
            flag=operation(tmp,stk);
            if(!flag)
                return 0;
        }
        else
        {
            stk.push(atof(tmp.c_str()));//c_str是Borland封装的String类中的一个函数，它返回当前字符串的首字符地址。
        }
    }
    return stk.top();
}

