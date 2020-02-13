/***********************************************************
 * @Description : P147_常数据成员
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/12 23:18
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
 #include <iostream>

 using namespace std;

 class Time{
     int const hour;
     int const minute;
     int const sec;
 public:
     Time(const int hour, const int minute, const int sec) : hour(hour), minute(minute), sec(sec) {}

     const int getHour() const {
         return hour;
     }

     const int getMinute() const {
         return minute;
     }

     const int getSec() const {
         return sec;
     }
 };

 int main(){

     return 0;
 }