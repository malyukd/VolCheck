#include "StringHandler.h"
#include <cstring> 
#include <iostream>
#include <cstdio> 

StringHandler::StringHandler(char* str) {
    strcpy(this->str, str);
    try {
        divide(this->str);
    }
    catch (std::exception ex) {
        sprintf(this->error, "Request is invalid. Invalid format");
        valid = false;
    }
}

void StringHandler::divide(char* str) {
    char* context = nullptr;
    char* token = strtok(str, ":/");
    int i = 0;
    
    while (token != nullptr) {
        if (i >= 4) {
            throw std::invalid_argument("invalid format");
        }
        if (strlen(token) <= this->sizes[i]) {
            sprintf(this->format[i], "%s", token);
        }
        else {
            sprintf(this->error, "Request is invalid. Wrong parameter %s: %s\n", name[i], token);
            validation[i] = false;
        }
        token = strtok(nullptr, ":/");
        i++;
    }
}


bool StringHandler::isProtocolValid() {
    if (!strcmp(this->protocol, "tcp") || !strcmp(this->protocol, "iscsi") || !strcmp(this->protocol, "nbd"))
        return true;
    return false;
}

bool StringHandler::isIPValid() {
    char ip[4][4];
    int ind=0;
    char buffer[4];
    for (int i = 0; i < 4; i++) {
        int count = 0;
        while (this->ip_a[ind] && this->ip_a[ind] != '.') {
            if(count>2)
                return false;
            buffer[count++] = this->ip_a[ind++];
        }
        buffer[count] = '\0';
        strcpy(ip[i], buffer);
        ind++;
    }
    for (int i = 0; i < 4; i++) {
            if (atoi(ip[i]) < 0 || atoi(ip[i]) > 255)
                return false;
            if (ip[i][0] != '0' && atoi(ip[i]) == 0)
                return false;
    }
    return true;
}

bool StringHandler::isPortValid() {
    int i = atoi(this->port);
    if (this->port[0] == '0' || i > 0 && i < 65536)
        return true;
    return false;
}

bool StringHandler::isVolumeNameValid() {
    if (strlen(this->volume_name)==0)
        return false;
    for (int i = 0; i < strlen(this->volume_name); i++) {
        char tmp = this->volume_name[i];
        if (!(tmp >= '0' && tmp <= '9' || tmp>='a' && tmp <= 'z' || tmp>='A' && tmp <= 'Z' || tmp == '_'))
            return false;
    }
    return true;
}

bool StringHandler::isValid() {
    if (!valid)
        return false;
    if (!isProtocolValid()) {
        if(validation[0]!=false)
            sprintf(this->error, "Request is invalid. Wrong parameter %s: %s\n", name[0], this->protocol);
        return false;
    }
    if (!isIPValid()) {
        if (validation[1] != false)
            sprintf(this->error, "Request is invalid. Wrong parameter %s: %s\n", name[1], this->ip_a);
        return false;
    }
    if (!isPortValid()) {
        if (validation[2] != false)
            sprintf(this->error, "Request is invalid. Wrong parameter %s: %s\n", name[2], this->port);
        return false;
    }
    if (!isVolumeNameValid()) {
        if (validation[3] != false)
            sprintf(this->error, "Request is invalid. Wrong parameter %s: %s\n", name[3], this->volume_name);
        return false;
    }
    return true;
}

