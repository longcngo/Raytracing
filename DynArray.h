#pragma once
#ifndef DYNARRAYH
#define DYNARRAYH

template <class T> class DynArray
{
public:
    T *data;
    int num_items;
    int size;

    DynArray()
    {
        num_items = 0;
        size = 4;
        data = new T[size];
    }
    DynArray(int s)
    {
        num_items = 0;
        size = s;
        data = new T[size];
    }
    void clear() { num_items = 0; }
    int length() { return num_items; }
    bool is_empty(){ return (num_items == 0); }
    const T& operator[](int i) const { return data[i]; }
    T& operator[](int i) { return data[i]; }
    bool append(T item);
    bool truncate();

};

template <class T> bool DynArray<T>::append(T item)
{
    if (num_items == size)
    {
        size *= 2;
        T* temp = data;
        if(!(data = new T[size])) { return false; }

        for (int i = 0; i < num_items; i++)
        {
            data[i] = temp[i];
        }

        delete [] temp;

    }

    data[num_items++] = item;
    return true;
}
template <class T> bool DynArray<T>::truncate()
{
    if (num_items != size)
    {
        size = num_items;
        T* temp = data;
        if(!(data = new T[size])) { return false; }

        for (int i = 0; i < num_items; i++)
        {
            data[i] = temp[i];
        }

        delete [] temp;
    }
    return true;
}

#endif
