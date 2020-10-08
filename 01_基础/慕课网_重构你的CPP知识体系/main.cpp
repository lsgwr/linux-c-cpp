#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


// 存钱
void Deposit(mutex& m, int& money)
{
    // 锁的粒度尽可能的最小化
    for(int index = 0; index < 100; index++)
    {
        m.lock();
        money += 1;
        m.unlock();
    }
}
// 取钱
void Withdraw(mutex& m, int& money)
{
    // 锁的粒度尽可能的最小化
    for (int index = 0; index < 100; index++)
    {
        m.lock();
        money -= 2;
        m.unlock();
    }
}

int main()
{
    // 银行存取款
    int money = 2000;
    mutex m;
    cout << "Current money is: " << money << endl;
    thread t1(Deposit, ref(m), ref(money));
    thread t2(Withdraw, ref(m), ref(money));
    t1.join();
    t2.join();
    cout << "Finally money is: " << money << endl;

    //线程交换
    thread tW1([]()
    {
    	cout << "ThreadSwap1 " << endl;
    });
    thread tW2([]()
    {
    	cout << "ThreadSwap2 " << endl;
    });
    cout << "ThreadSwap1' id is " << tW1.get_id() << endl;
    cout << "ThreadSwap2' id is " << tW2.get_id() << endl;

    cout << "Swap after:" << endl;
    swap(tW1, tW2);
    cout << "ThreadSwap1' id is " << tW1.get_id() << endl;
    cout << "ThreadSwap2' id is " << tW2.get_id() << endl;
    tW1.join();
    tW2.join();

    //// 线程移动
    thread tM1( []() { ; } );
    //tM1.join();
    cout << "ThreadMove1' id is " << tM1.get_id() << endl;
    cout << "Move after:" << endl;
    thread tM2 = move(tM1);
    cout << "ThreadMove2' id is " << tM2.get_id() << endl;
    cout << "ThreadMove1' id is " << tM1.get_id() << endl;
    tM2.join();

    return 0;
}