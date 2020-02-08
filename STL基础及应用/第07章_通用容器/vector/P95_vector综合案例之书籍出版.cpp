/***********************************************************
 * @Description : P95_vector综合案例之书籍出版
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/2/8 15:54
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Book {
    string no;    // 书号
    string name;  // 书名
    string pub;   // 出版社
public:
    Book(string no, string name, string pub) : no(std::move(no)), name(std::move(name)), pub(std::move(pub)) {}
};

class Writer {
    string no; // 作者编号
    string name; //作者姓名
    vector<Book> bookVec; //  当前作者所拥有树的向量集合

public:
    Writer(string no, string name) : no(std::move(no)), name(std::move(name)) {}

    void addBook(Book &book) {
        bookVec.push_back(book);
    }
};

class WriterCollect {
    vector<Writer> writerVec;

public:
    void addWriter(Writer &writer) {
        writerVec.push_back(writer);
    }
};

int main() {
    Writer w1("w001", "列夫托尔斯泰");
    Book b1("b001", "战争与和平", "商务出办社");
    Book b2("b002", "安娜", "邮电出版社");
    w1.addBook(b1);
    w1.addBook(b2);

    Writer w2("w002", "刘慈欣");
    Book b3("b003", "三体", "西安出版社");
    Book b4("b004", "流浪地球", "清华出版社");
    w2.addBook(b3);
    w2.addBook(b4);

    WriterCollect collect;
    collect.addWriter(w1);
    collect.addWriter(w2);
    return 0;
}