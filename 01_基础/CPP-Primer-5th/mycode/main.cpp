#include <iostream>
#include <memory>

using namespace std;

struct dest {
};
struct conn {
};;

conn connect(dest *pd) {
    cout << "打开连接" << endl;
    return conn();
}

void disconnect(conn c) {
    cout << "关闭连接" << endl;
}

// 未使用shared_ptr的版本
void f(dest &d) {
    cout << "直接管理连接" << endl;
    conn c = connect(&d);
    // Todo:忘记调用disconnect关闭连接
    cout << endl;
}

void end_connection(conn *p) {
    disconnect(*p);
}

// 使用shared_ptr的版本
void f1(dest &d) {

}

int main() {

    return 0;
}