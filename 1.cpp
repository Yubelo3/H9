#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>

//元素个数
std::map<std::string, int> E;
//方程式
std::string expr;
std::string left;
std::string right;

std::vector<std::string> split(const std::string& str)
{
    std::vector<std::string> subExpr;
    int begin=0;
    for(int i=0;i<str.size();i++)
        if(str[i]=='+')
        {
            subExpr.push_back(str.substr(begin,i-begin));
            begin=i+1;
        }
    subExpr.push_back(str.substr(begin));
    return subExpr;
}

int readInt(const std::string& str,int &i)
{
    if(i>=str.size()) return 1;
    int start=i;
    while(isdigit(str[i]))
        i++;
    if(start==i)
        return 1;
    return std::stoi(str.substr(start,i-start));
}

void solve(const std::string& str,int t)
{
    int coeffEnd=0;
    while(isdigit(str[coeffEnd]))
        coeffEnd++;
    if(coeffEnd)
        t*=std::stoi(str.substr(0,coeffEnd));

    //读完系数读元素
    for(int i=coeffEnd;i<str.size();i++)
    {
        //如果读到大写字母，可能是元素开头，可能就是一个元素
        if(isupper(str[i]))
        {
            int elemEnd=i+1;
            if(i+1<str.size()&&islower(str[i+1]))
                elemEnd++;
            std::string elem=str.substr(i,elemEnd-i);
            i=elemEnd;
            int multiCoeff=readInt(str,i);
            E[elem]+=t*multiCoeff;
            // std::cout<<elem<<": +"<<t*multiCoeff<<std::endl;
        }
        //如果读到括号，需要递归
        else if(str[i]=='(')
        {
            std::stack<int> S;
            int begin=i+1;
            S.push(i);
            i++;
            while(!S.empty())
            {
                if(str[i]=='(')
                    S.push(i);
                else if(str[i]==')')
                    S.pop();
                i++;
            }
            int end=i-1;
            int multiCoeff=readInt(str,i);
            solve(str.substr(begin,end-begin),t*multiCoeff);
        }
        i--;
    }
}

//统计元素个数。如果遇到括号，会递归eval
// t是该表达式系数
void eval(std::string e, int t)
{
    auto elem=split(e);
    for(const std::string& str:elem)
        solve(str,t);
}

int main()
{
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    std::ios::sync_with_stdio(0);
    int n;
    std::cin >> n;
    while (n--)
    {
        bool flag=true;
        E.clear();
        std::cin >> expr;
        left = expr.substr(0, expr.find('='));
        right = expr.substr(expr.find('=') + 1);
        eval(left, 1);
        eval(right,-1);
        for(auto it=E.begin();it!=E.end();it++)
            if(it->second!=0)
            {
                flag=false;
                break;
            }
        if(flag)
            std::cout<<"Y"<<std::endl;
        else
            std::cout<<"N"<<std::endl;
    }
    // auto vec=split(left);
    // std::cout<<"left"<<std::endl;
    // for(auto& s:vec)
    //     std::cout<<s<<" ";
    // std::cout<<"\nright"<<std::endl;
    // vec=split(right);
    // for(auto& s:vec)
    //     std::cout<<s<<" ";
    // std::cout<<std::endl;
    


    return 0;
}