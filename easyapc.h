
#ifndef EASYAPC220
#define EASYAPC220
#include <Arduino.h> 
#include <SoftwareSerial.h>

class SoftwareAPC {
    private:
        byte rx;
        byte tx;
        byte set;
        byte en;
        bool setav = 0;
        bool setmode = 0;
        bool enconn = 0;
        bool enabled = 0;
        bool inconfigure = 0;

    public:
        SoftwareSerial s;
        SoftwareAPC(byte, byte);
        SoftwareAPC(byte, byte, byte);
        SoftwareAPC(byte, byte, byte, byte);

        std::string startup();
        std::string enable();
        std::string disable();
        std::string setm();
        std::string configure(int, int, int, int, bool);
        std::string defaultconfigure();
        std::string current();
        std::string confirm();
}

class HardwareAPC {
    private:
        byte set;
        byte en;
        bool setav = 0;
        bool setmode = 0;
        bool enconn = 0;
        bool enabled = 0;
        bool inconfigure = 0;

    public:
        SoftwareAPC(byte);
        SoftwareAPC(byte, byte);

        std::string startup();
        std::string enable();
        std::string disable();
        std::string setm();
        std::string configure(int, int, int, int, bool);
        std::string defaultconfigure();
        std::string current();
        std::string confirm();
}
