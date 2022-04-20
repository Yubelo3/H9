#include <iostream>
#include <string>
#include <vector>

struct file
{
    std::string name;
    bool isDir=false;
    //目录配额
    long long LD=0;
    //已用目录配额
    long long LDoccupied=0;
    //后代配额
    long long LR=0;
    //已用后代配额
    long long LRoccupied=0;
    //大小
    long long size=0;
    //后代文件
    std::vector<
};

file root;

std::vector<std::string> split(const std::string& path)
{
    std::vector<std::string> ret;
    int begin=1,len;
    while(len=path.find('/',begin)!=std::string::npos)
    {
        ret.push_back(path.substr(begin,len));
        begin+=(len+1);
    }
    ret.push_back(path.substr(begin));
    return ret;
}

//创建文件
//对于每级目录，判断是否创建了同名目录，是否超出后代配额
bool C()
{
    file& f=root;

}

int main()
{
    root.name="/";

    // std::string path="/A/B/C/D/E";
    // auto vec=split(path);
    // for(auto& str:vec)
    //     std::cout<<str<<std::endl;

    return 0;
}