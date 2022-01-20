#include "dummy_class.h"

class Singleton
{
private:
    Singleton(){};
    Singleton(const Singleton& other);
    ~Singleton() {};
    
    static Singleton* instance;

    static void Destroy()
    {
        delete instance;
    }

public:
    static Singleton* GetInstance()
    {
        if(instance == NULL) instance = new Singleton();
        return instance;
    }
};

static class DestroyerClass
{
public:
    ~DestoryerClass()
    {
        
    }
}

Singleton* Singleton::instance = nullptr;
