#ifndef ZOOMODBUS_H
#define ZOOMODBUS_H

#include <QObject>
#include <include/modbus-tcp.h>
#include <include/modbus.h>
#include <time.h>
#include <sys/time.h>
class zooModbus:public QObject
{
    Q_OBJECT
public:
    zooModbus(const char* Host,int Port,int address);
    ~zooModbus();
public:
    bool init();
    int timeOut(uint32_t tv);
    int readInputRegisters(int addr,int nb,uint16_t *dest);
    int readInputBits();
private:
    modbus_t *modb_;
    const char* host_;
    int port;
    int serverAddress;
    int timeout_;
};

#endif // ZOOMODBUS_H
