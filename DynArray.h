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
    ~DynArray()
    {
        num_items = 0;
        delete [] data;
    }
    int length() { return size; }
    bool is_empty(){ return (num_items == 0); }
    inline const T& operator[](int i) const { return data[i]; }
    inline T& operator[](int i) { return data[i]; }
    bool append(T item)
    {
        data[num_items++] = item;
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
        return true;
    }
    bool truncate()
    {
        if (num_items < size)
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

};

#endif
