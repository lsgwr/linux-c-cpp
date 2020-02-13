/***********************************************************
 * @Description : P197_抽象类中虚函数的重写
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/13 14:36
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <iostream>

using namespace std;

class Animal {
public:
    virtual char *getType() const {
        return "Animal";
    }

    virtual char *getVoice() const {
        return "Voice";
    }
};

class Dog : public Animal {
public:
    char *getType() const {
        return "Dog";
    }

    char *getVoice() const {
        return "Woot";
    }
};

void type(Animal &a) {
    cout << a.getType() << endl;
}

void speak(Animal &a) {
    cout << a.getVoice() << endl;
}

int main() {
    Dog d;
    cout << "type:";
    type(d);
    cout << endl;
    cout << "speak";
    speak(d);
    cout << endl;
    return 0;
}

