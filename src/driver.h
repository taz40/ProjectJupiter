#ifndef __DRIVER_H
#define __DRIVER_H

class Driver{
public:
    Driver();
    ~Driver();
    
    virtual void Activate();
    virtual int Reset();
    virtual void Deactivate();
};

class DriverManager{
public:
    Driver* drivers[265];
    int numDrivers;
public:
    DriverManager();
    ~DriverManager();
    
    void AddDriver(Driver*);
    void ActivateAll();
};

#endif
