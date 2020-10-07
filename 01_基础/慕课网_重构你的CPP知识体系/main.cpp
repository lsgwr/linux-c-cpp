#include <iostream>
#include <vector>

using namespace std;

//测试错误的Map删除元素
void mapTest()
{
    map<int, string> dataMap;


    for (int i = 0; i < 100; i++)
    {
        string strValue = "Hello, World";

        stringstream ss;
        ss<<i;
        string tmpStrCount;
        ss>>tmpStrCount;
        strValue += tmpStrCount;
        dataMap.insert(make_pair(i, strValue));
    }

    cout<<"MAP元素内容为："<<endl;
    map<int, string>::iterator iter;
    for (iter = dataMap.begin(); iter != dataMap.end(); iter++)
    {
        int nKey = iter->first;
        string strValue = iter->second;
        cout<<strValue<<endl;
    }

    cout<<"内容开始删除："<<endl;
    //删除操作引发迭代器失效
    for (iter = dataMap.begin(); iter != dataMap.end();iter++)
    {
        int nKey = iter->first;
        string strValue = iter->second;

        if (nKey % 2 == 0)
        {
            dataMap.erase(iter);    //错误

        }
        /* cout<<iter->second<<endl;*/
    }
}

int main() {
    for (iter = cont.begin(); it != cont.end();)
    {
        (*iter)->doSomething();
        if (shouldDelete(*iter))
            cont.erase(iter++);
        else
            ++iter;
    }
    return 0;
}
