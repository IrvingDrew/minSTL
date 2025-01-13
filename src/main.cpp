#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <type_traits>
#include <type_traits.h>

template <typename T>
class BlobPtr;

template <typename T>
class Blob
{
    template <typename X>
    friend class BlobPtr;

public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob();
    Blob(std::initializer_list<T> il);

    template <typename It>
    Blob(It b, It e);

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    T &back();
    T &operator[](size_type i);

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
    {
        throw std::out_of_range(msg);
    }
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
T &Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e))
{
}

template <typename T>
class BlobPtr
{
public:
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    // 解引用得到底层vector中对应位置元素的引用
    T &operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    BlobPtr &operator++();
    BlobPtr &operator--();
    BlobPtr operator++(int);

private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};
template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++()
{
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t, const std::string &) const
{
    return nullptr;
}

typedef Blob<std::string> StrBlob;
template <typename T>
using twin = std::pair<T, T>;

template <typename T>
using partNo = std::pair<T, unsigned>;

template <typename T = std::vector<int>>
typename T::value_type top(const T &c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type(); // 告知编译器，T::value_type是一个类型
}

class DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}
    template <typename T>
    void operator()(T *p) const
    {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};

template class BlobPtr<int>;
extern template class BlobPtr<std::string>;

template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);

template <typename It>
auto fcn(It beg, It end) -> typename std::remove_reference<decltype(*beg)>::type
{
    return *beg;
}

template <typename T>
void f3(T &&);

template <typename T>
void f3(const T &);

template <typename T>
typename std::remove_reference<T>::type &&move(T &&t)
{
    return static_cast<typename std::remove_reference<T>::type &&>(t);
}

template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void g(int &&i, int &j)
{ // 传入i是右值引用，不可接受左值
    std::cout << i << " " << j << std::endl;
}

template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    return os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args &...rest)
{
    os << t << ", ";
    return print(os, rest...);
}

using std::make_shared;
using std::shared_ptr;

shared_ptr<int> factory(int a)
{
    return make_shared<int>(a);
}

namespace myoop
{
    class Quote
    {
    public:
        Quote() = default;
        Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
        std::string isbn() const { return bookNo; }

        virtual double net_price(std::size_t n) const { return n * price; }
        virtual ~Quote() = default;

    private:
        std::string bookNo;

    protected:
        double price = 0.0;
    };

    class Bulk_quote final : public Quote
    {
    public:
        Bulk_quote() = default;
        Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double count);

        double net_price(std::size_t n) const override;

    private:
        std::size_t min_qty = 0;
        double discount = 0.0;
    };

    Bulk_quote::Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double count) : Quote(book, sales_price), min_qty(qty), discount(count) {}

}

int main()
{
    shared_ptr<int> aa = make_shared<int>(34444);

    std::vector<int> *p = new std::vector<int>({1, 2, 3, 4, 5, 6});
    std::cout << *aa << std::endl;
    std::cout << minstl::m_true_type::value << std::endl;
}