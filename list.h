#ifndef LIST_H
#define LIST_H
#include<vector>
#include <stdexcept>

using std::vector;
using std::out_of_range;
template<class T>
class List
{

    vector<T> nodes;

    typename vector<T>::iterator iter;
   void initialize();
public:
    List(){
        iter = nodes.begin();

    }
    void insert(int i,  T *node);
    void find(int item);
    void append( T const& node);
    const T &erase(int i);
    int size();
    int indexOf(const T &node);
   T at(unsigned int i);
};

template <class T>
void List<T>::insert(int i,  T *node)
{
    for( int j=0;j<i;j++)
    {
        ++iter;
    }
  nodes.insert(iter, node);

}

template <class T>
void List<T>::append(const T &node)
{
     nodes.push_back(node);
    }


template <class T>
T List<T>::at(unsigned int i)
{
    if(i>nodes.size()){
     // throw out_of_range("List<>::at(): out_of_range");
    }
    else{
     return  nodes.at(i);
    }

   }
template <class T>
int List<T>::size(){
    return nodes.size();
}
template <class T>
const T& List<T>::erase(int i){
    T item = nodes[i];
    iter = nodes.begin();
    nodes.erase(iter+i);
    return item ;
}
template <class T>
int  List<T>::indexOf(const T& node)
{
    int index = -1;
    for(int i =0;i<size();i++)
    {
        if(nodes[i]==node)
        {
            index = i;
        }
    }
    return index;
}

#endif // LIST_H
