/*
 Copyright (C) 2013-2014 Masakazu Ohtsuka
  
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
  
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __KEYS_H__
#define __KEYS_H__

#include "GSwifi_const.h"
#include <inttypes.h>

// SSID is max 32 bytes
// see 7.3.1.2 of IEEE 802.11
#define MAX_WIFI_SSID_LENGTH     32

// password is max 63 characters
// see H.4.1 of IEEE 802.11
#define MAX_WIFI_PASSWORD_LENGTH 63

// EAP user name
#define MAX_WIFI_EAPUSER_LENGTH  63

// it's an UUID (without '-')
#define MAX_KEY_LENGTH           32

enum KeysFillerState {
    KeysFillerStateSecurity  = 0,
    KeysFillerStateSSID      = 1,
    KeysFillerStatePassword  = 2,
    KeysFillerStateKey       = 3,
    KeysFillerStateRegdomain = 4,
    KeysFillerStateEapOuter  = 5,
    KeysFillerStateEapInner  = 6,
    KeysFillerStateEapUser   = 7,
    KeysFillerStateReserved5 = 8,
    KeysFillerStateReserved6 = 9,
    KeysFillerStateCRC       = 10,
};

#define REGDOMAIN_FCC   '0'
#define REGDOMAIN_ETSI  '1' 
#define REGDOMAIN_TELEC '2' 
#define REGDOMAIN_MIN   REGDOMAIN_FCC
#define REGDOMAIN_MAX   REGDOMAIN_TELEC

class KeysFiller {
 public:
    KeysFiller();

    KeysFillerState state;
    uint8_t index;
};

class Keys {
 public:
    Keys();

    void load();
    bool isWifiCredentialsSet();
    bool isAPIKeySet();
    bool isValid();
    bool wasWifiValid();
    GSSECURITY getSecurity();
    const char* getSSID();
    const char* getPassword();
    const char* getKey();
    char getRegDomain();
    GSEAPOUTER getEapOuter();
    GSEAPINNER getEapInner();
    const char* getEapUser();
    void set(GSSECURITY security, const char *ssid, const char *pass);
    void setKey(const char *key);
    void setWifiWasValid(bool valid);
    void setKeyValid(bool valid);
    void save();
    void save2();
    void clear();
    void clearKey();
    int8_t put(char dat);
    int8_t putDone();

    void dump();

    // Both KeysShared and KeysIndependent are saved in EEPROM
    // KeysShared includes Wifi credentials, which is only needed
    // when we lost Wifi connection or haven't established it,
    // and no other classes will use global.buffer without Wifi connection.
    // So KeysShared area is shared with global.buffer.
    // KeysIndependent is used to store key,
    // which is needed to communicate with server,
    // and that's going to happen when other classes (ex: IR) uses global.buffer.
    // CRC is used to detect EEPROM corruption and corruption during Morse communication

    // sizeof -> 200 // EEPROM_INDEPENDENT_OFFSET in const.h
    struct KeysShared
    {
        uint8_t    security;
        char       ssid    [MAX_WIFI_SSID_LENGTH     + 1];
        char       password[MAX_WIFI_PASSWORD_LENGTH + 1];
        bool       wifi_is_set;

        // wifi credentials was once valid.
        // if it was valid previously, we won't clear nor start morse communication
        // if it was never valid (false),
        // we clear credentials when 1st attempt to join infrastructure fails
        bool       wifi_was_valid;

        // temp_key is only used when
        // receiving key through morse communication.
        // when morse communication is done, we copy key to KeysIndependent area
        // and key is accessed through KeysIndependent afterwards
        char       temp_key[MAX_KEY_LENGTH           + 1];

        uint8_t    eapouter;
        uint8_t    eapinner;
        char       eapuser [MAX_WIFI_EAPUSER_LENGTH  + 1];

        uint8_t    crc8;
    } __attribute__ ((packed));

    struct KeysCRCed
    {
        uint8_t    security;
        char       ssid    [MAX_WIFI_SSID_LENGTH     + 1];
        char       password[MAX_WIFI_PASSWORD_LENGTH + 1];
        char       eapuser [MAX_WIFI_EAPUSER_LENGTH  + 1];
        uint8_t    eapouter;
        uint8_t    eapinner;
        bool       wifi_is_set;
        bool       wifi_was_valid;

        char       temp_key[MAX_KEY_LENGTH           + 1];
    } __attribute__ ((packed));

    // sizeof -> 35
    struct KeysIndependent
    {
        char       key     [MAX_KEY_LENGTH           + 1];
        bool       key_is_set;
        bool       key_is_valid; // POST /door succeeded
    } __attribute__ ((packed));

    // don't need to remember in EEPROM
    // GS saves this value to Flash
    // factory default is '0',
    // iphone sends it's domain over morse,
    // if regdomain information is not included in morse (ex: old version iOS SDK doesn't have this code)
    // regdomain defaults to '2'
    // WiFi access points automatically choose band within allowed bands,
    // and Japanese WiFi access points might choose one from 13-14, which
    // GS1011MIPS can't connect if in FCC regdomain, 
    char regdomain;  // '0': FCC, '1': ETSI, '2': TELEC (factory default: FCC)

 private:
    bool isCRCOK();

    KeysShared      *data;
    KeysIndependent  data2;
    KeysFiller       filler;
};

#endif
