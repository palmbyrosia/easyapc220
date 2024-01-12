#include "easyapc.h"

// constructor for SoftwareSerial apc with rx and tx
SoftwareAPC::SoftwareAPC(byte rxd, byte txd) {
    this->rx = rxd;
    this->tx = txd;
    this->s = SoftwareSerial(this->rx, this-> tx);
}

// constructor for SoftwareSerial apc with rx,tx and set
SoftwareAPC::SoftwareAPC(byte rxd, byte txd, byte setp) {
    this->rx = rxd;
    this->tx = txd;
    this->s = SoftwareSerial(this->rx, this-> tx);
    this->set = setp;
    this->setav = 1;
}

// constructor for SoftwareSerial apc with rx,tx,set and en
SoftwareAPC::SoftwareAPC(byte rxd, byte txd, byte setp, byte enp) {
    this->rx = rxd;
    this->tx = txd;
    this->s = SoftwareSerial(this->rx, this-> tx);
    this->set = setp;
    this->en = enp;
    this->setav = 1;
    this->enconn = 1;
}

// startup apc ensuring digital connections enabled
std::string SoftwareAPC::startup() {
    if ( this->enconn ) { digitalWrite(this->en, HIGH); }
    if ( this->setav ) { digitalWrite(this->set, HIGH); }
    delay(50);
    this->enabled = 1;
    return "Startup complete"
}

// attempts digital EN enable
std::string SoftwareAPC::enable() {
    if ( this->enconn ) { digitalWrite(this->en, HIGH); delay(50); this->enabled = 1; return "Enabled"; }
    else { return "No enable (EN) pin connected"; }
}

// attempts digital EN disable
std::string SoftwareAPC::disable() {
    if ( this->enconn ) { digitalWrite(this->en, LOW); delay(50); this->enabled = 0; return "Enabled"; }
    else { return "No enable (EN) pin connected"; }
}

// attempts SET mode activation
std::string SoftwareAPC::setmode() {
    if ( this->setav ) { digitalWrite(this->set, LOW); this->setmode = 1; return "Enabled"; }
    else { return "No set (SET) pin connected"; }
}

// requests current status of transceiver
std::string SoftwareAPC::current() {
    if ( this->setmode ) { this->s.print("RD"); return "Status Requested"; }
    else { return "Not in SET mode"; }
}

// assisted configuration using UART online setup
// frequency in MHz from 418 to 455
// rf baud rate: 1,2,3 and 4 refer to 2400,4800,9600,19200bps separetely.
// rf power: 0 to 9, 9 means 13dBm(20mW).
// uart baud rate: 0,1,2,3,4,5 and 6 refers to 1200,2400,4800,9600,19200,38400,57600bps separately.
// series check out/parity: Series checkout：0 means no check, 1 means even parity, 2 means odd parity.
std::string SoftwareAPC::configure(int freq, int rfrate, int rfpower, int uartrate, int parity) {
    if ( this->setmode ) {
        if ( freq>=418 && freq<=455 && rfrate>=1 && rfrate<=4 && rfpower>=0 && rfrate<=9 && uartrate>=0 && uartrate<=6 && parity>=0 && parity<=2 ) {
            this->s.print("WR_" + std::to_string(freq) + "000_" + std::to_string(rfrate) + "_" + std::to_string(rfpower) + "_" + std::to_string(uartrate) + "_" + std::to_string(parity))
            delay(200);
            this->inconfigure=1;
            return "Succesful request, read returned UART input and use confirm method for APC configuration";
        } else { return "Invalid configuration"; }
    } else { return "Not in SET mode"; }
}

std::string SoftwareAPC::defaultconfigure() {
    return this->configure(434, 3, 9, 4, 0);
}

// confirms configuration state
std::string SoftwareAPC::confirm() {
    if ( this->inconfigure ) { 
        digitalWrite(this->set, HIGH); 
        delay(10); 
        this->setmode = 0;
        this->inconfigure = 0;
        return "APC configuration attempt complete, ready for use";
    } else { return "No active configuration"; }
}


// HARDWARE SERIAL

// constructor for SoftwareSerial apc with rx,tx and set
HardwareAPC::HardwareAPC(byte setp) {
    this->set = setp;
    this->setav = 1;
}

// constructor for SoftwareSerial apc with rx,tx,set and en
HardwareAPC::HardwareAPC(byte setp, byte enp) {
    this->set = setp;
    this->en = enp;
    this->setav = 1;
    this->enconn = 1;
}

// startup apc ensuring digital connections enabled
std::string HardwareAPC::startup() {
    if ( this->enconn ) { digitalWrite(this->en, HIGH); }
    if ( this->setav ) { digitalWrite(this->set, HIGH); }
    delay(50);
    this->enabled = 1;
    return "Startup complete"
}

// attempts digital EN enable
std::string HardwareAPC::enable() {
    if ( this->enconn ) { digitalWrite(this->en, HIGH); delay(50); this->enabled = 1; return "Enabled"; }
    else { return "No enable (EN) pin connected"; }
}

// attempts digital EN disable
std::string HardwareAPC::disable() {
    if ( this->enconn ) { digitalWrite(this->en, LOW); delay(50); this->enabled = 0; return "Enabled"; }
    else { return "No enable (EN) pin connected"; }
}

// attempts SET mode activation
std::string HardwareAPC::setmode() {
    if ( this->setav ) { digitalWrite(this->set, LOW); this->setmode = 1; return "Enabled"; }
    else { return "No set (SET) pin connected"; }
}

// requests current status of transceiver
std::string HardwareAPC::current() {
    if ( this->setmode ) { Serial.print("RD"); return "Status Requested"; }
    else { return "Not in SET mode"; }
}

// assisted configuration using UART online setup
// frequency in MHz from 418 to 455
// rf baud rate: 1,2,3 and 4 refer to 2400,4800,9600,19200bps separetely.
// rf power: 0 to 9, 9 means 13dBm(20mW).
// uart baud rate: 0,1,2,3,4,5 and 6 refers to 1200,2400,4800,9600,19200,38400,57600bps separately.
// series check out/parity: Series checkout：0 means no check, 1 means even parity, 2 means odd parity.
std::string HardwareAPC::configure(int freq, int rfrate, int rfpower, int uartrate, int parity) {
    if ( this->setmode ) {
        if ( freq>=418 && freq<=455 && rfrate>=1 && rfrate<=4 && rfpower>=0 && rfrate<=9 && uartrate>=0 && uartrate<=6 && parity>=0 && parity<=2 ) {
            Serial.print("WR_" + std::to_string(freq) + "000_" + std::to_string(rfrate) + "_" + std::to_string(rfpower) + "_" + std::to_string(uartrate) + "_" + std::to_string(parity))
            delay(200);
            this->inconfigure=1;
            return "Succesful request, read returned UART input and use confirm method for APC configuration";
        } else { return "Invalid configuration"; }
    } else { return "Not in SET mode"; }
}

std::string HardwareAPC::defaultconfigure() {
    return this->configure(434, 3, 9, 4, 0);
}

// confirms configuration state
std::string HardwareAPC::confirm() {
    if ( this->inconfigure ) { 
        digitalWrite(this->set, HIGH); 
        delay(10); 
        this->setmode = 0;
        this->inconfigure = 0;
        return "APC configuration attempt complete, ready for use";
    } else { return "No active configuration"; }
}
