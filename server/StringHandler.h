#include <cstddef>



class StringHandler {
public:
    char str[110]="";
    char protocol[10]="";
    char ip_a[18]="";
    char port[6]="";
    char volume_name[64]="";
    char* format[4]{protocol,ip_a,port,volume_name };
    const char* name[4]{ "protocol","ip_a", "port", "volume_name"};
    char error[300];
    bool valid = true;
    const int sizes[4]{ 10,     
        18,         
        6,         
        64  
    };
    bool validation[4]{ true,true,true,true };


    StringHandler(char* str);
    bool isValid();
    void divide(char* str);
    bool isProtocolValid();
    bool isIPValid();
    bool isPortValid();
    bool isVolumeNameValid();
}; 
