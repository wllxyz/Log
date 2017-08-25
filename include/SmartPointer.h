#ifndef	SMART_POINTER_H
#define SMART_POINTER_H

#include <cstdlib>

template <typename T>  
class SmartPointer {  
public:  
    //构造函数  
    SmartPointer(T* p=0): ptr(p), reference_count(new int(1)){}  
    //拷贝构造函数  
    SmartPointer(const SmartPointer& src) {  
        if(this!=&src) {  
            ptr = src.ptr;  
            reference_count = src.reference_count;  
            (*reference_count)++;  
        }  
    }  
    //重载赋值操作符  
    SmartPointer& operator=(const SmartPointer& src) {  
        if(ptr==src.ptr) {  
            return *this;  
        }  
        releaseCount();  
        ptr = src.ptr;  
        reference_count = src.reference_count;  
        (*reference_count)++;  
        return *this;  
    }  
  
    //重载操作符  
    T& operator*() {  
        if(ptr) {  
            return *ptr;  
        }  
        //throw exception  
    }

    const T& operator*() const {
	if(ptr) {
		return *ptr;
	}
    }  

    //重载操作符  
    T* operator->() {  
            return ptr;  
        //throw exception  
    }
    const T* operator->() const {
	return ptr;
    }
  
    //析构函数  
    ~SmartPointer() {  
        if (--(*reference_count) == 0) {  
            delete ptr;  
            delete reference_count;  
        }  
    }  
private:  
    T *ptr;  
    int *reference_count;  
    void releaseCount() {  
        (*reference_count)--;  
        if((*reference_count)==0) {
		if(ptr) delete ptr;  
        	delete reference_count;  
        }  
    }  
};  
  
#endif

