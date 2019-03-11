#include "include/zoomodbus.h"

zooModbus::zooModbus(const char* Host,int Port,int address):host_(Host),port(Port),serverAddress(address)
{
    modb_ = nullptr;
}

zooModbus::~zooModbus(){
    if(host_ != NULL)
        host_ = NULL;
    modbus_close(modb_);
    modbus_free(modb_);
}

bool zooModbus::init(){
    modb_ = modbus_new_tcp(host_,port);
    if (modb_ == NULL) {
       // zError("main","unable to allocate libmodbus context");
        return false;
    }
    int rc =  modbus_set_slave(modb_,serverAddress);
    if (rc == -1) {
       // zError("main","Invalid slave ID");
        modbus_free(modb_);
        return false;
    }
    if (modbus_connect(modb_) == -1) {
      //  zError("main","connection failed: %s",modbus_strerror(errno));
        modbus_free(modb_);
        return false;
    }
    return true;
}

int zooModbus::readInputRegisters(int addr, int nb, uint16_t *dest){
    // 发送请求
    // 超时，结束事件循环;
    int res = modbus_read_registers(modb_,addr,nb,dest);
    if(res < 0){
        modbus_close(modb_);
        modbus_connect(modb_);
        res = modbus_read_registers(modb_,addr,nb,dest);
    }
    return res;
}
// true 0 false -1
int zooModbus::timeOut(uint32_t tv){
    timeout_ = tv * 1000;
    return  modbus_set_response_timeout(modb_,tv,0);
}

