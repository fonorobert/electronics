/**
 * @file ESP8266.h
 * @brief The definition of class ESP8266.
 * @author Wu Pengfei<pengfei.wu@itead.cc>
 * @date 2015.02
 *
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "Arduino.h"

#define ESP8266_USE_SOFTWARE_SERIAL

#ifdef ESP8266_USE_SOFTWARE_SERIAL
#include "SoftwareSerial.h"
#endif

#define  VERSION_18   		0X18
#define  VERSION_22   		0X22
#define  DEFAULT_PATTERN	3

/**
 * You can modify the macro to choose a different version
 */

#define  USER_SEL_VERSION         VERSION_18

/**
 * Provide an easy-to-use way to manipulate ESP8266.
 */
class ESP8266 {
 public:

#ifdef ESP8266_USE_SOFTWARE_SERIAL
    /*
     * Constuctor.
     *
     * @param uart - an reference of SoftwareSerial object.
     * @param baud - the buad rate to communicate with ESP8266(default:9600).
     *
     * @warning parameter baud depends on the AT firmware. 9600 is an common value.
     */
#if (USER_SEL_VERSION == VERSION_22)
    ESP8266(SoftwareSerial &uart, uint32_t baud = 115200);
#elif (USER_SEL_VERSION == VERSION_18)
    ESP8266(SoftwareSerial &uart, uint32_t baud = 9600);
#endif  /* #if(USER_SEL_VERSION==VERSION_22) */

#else /* HardwareSerial */
    /*
     * Constuctor.
     *
     * @param uart - an reference of HardwareSerial object.
     * @param baud - the buad rate to communicate with ESP8266(default:9600).
     *
     * @warning parameter baud depends on the AT firmware. 9600 is an common value.
     */
#if (USER_SEL_VERSION == VERSION_22)
    ESP8266(HardwareSerial &uart, uint32_t baud = 115200);
#elif (USER_SEL_VERSION == VERSION_18)
    ESP8266(HardwareSerial &uart, uint32_t baud = 9600);
#endif /* #if(USER_SEL_VERSION == VERSION_22) */


#endif /* #ifdef ESP8266_USE_SOFTWARE_SERIAL */


    /**
     * Verify ESP8266 whether live or not.
     *
     * Actually, this method will send command "AT" to ESP8266 and waiting for "OK".
     *
     * @retval true - alive.
     * @retval false - dead.
     */
    bool kick(void);

    /**
     * Restart ESP8266 by "AT+RST".
     *
     * This method will take 3 seconds or more.
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool restart(void);

    /**
     * Get the version of AT Command Set.
     *
     * @return the string of version.
     */
    String getVersion(void);

    /**
     * Start function of deep sleep.
     *
     *  @param time - the sleep time.
     *  @retval true - success.
     *  @retval false - failure.
     *  @note the feature requires hardware support.
     */
    bool deepSleep(uint32_t time);

    /**
     * Switch the echo function.
     *
     *  @param mode - 1 start echo -0 stop echo
     *  @retval true - success.
     *  @retval false - failure.
     *
     */
    bool setEcho(uint8_t mode);

    /**
      *  Restore factory.
      *  @retval true - success.
      *  @retval false - failure.
      *  @note  The operation can lead to restart the machine.
      */
    bool restore(void);

    /**
     * Set up a serial port configuration.
     *
     * @param pattern -1 send "AT+UART=", -2 send "AT+UART_CUR=", -3 send "AT+UART_DEF=".
     * @param baudrate - the uart baudrate.
     * @retval true - success.
     * @retval false - failure.
     * @note  Only allows baud rate design, for the other parameters:databits- 8,stopbits -1,parity -0,flow control -0 .
     */
    bool setUart(uint32_t baudrate,uint8_t pattern);

    /**
     * Set operation mode to station.
     *
     * @param   pattern1 -1, send "AT+CWMODE_DEF?",-2,send "AT+CWMODE_CUR?",-3,send "AT+CWMODE?".
     * @param   pattern2 -1, send "AT+CWMODE_DEF=",-2,send "AT+CWMODE_CUR=",-3,send "AT+CWMODE=".
     * @retval true - success.
     * @retval false - failure.
     *
     */
    bool setOprToStation(uint8_t pattern1=DEFAULT_PATTERN,uint8_t pattern2=DEFAULT_PATTERN);

    /**
     * Get the model values list.
     *
     * @return the list of model.
     */
    String getWifiModeList(void);

    /**
     * Set operation mode to softap.
     * @param   pattern1 -1, send "AT+CWMODE_DEF?",-2,send "AT+CWMODE_CUR?",-3,send "AT+CWMODE?".
     * @param   pattern2 -1, send "AT+CWMODE_DEF=",-2,send "AT+CWMODE_CUR=",-3,send "AT+CWMODE=".
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool setOprToSoftAP(uint8_t pattern1=DEFAULT_PATTERN,uint8_t pattern2=DEFAULT_PATTERN);

    /**
     * Set operation mode to station + softap.
     * @param   pattern1 -1, send "AT+CWMODE_DEF?",-2,send  "AT+CWMODE_CUR?",-3,send "AT+CWMODE?".
     * @param   pattern2 -1, send "AT+CWMODE_DEF=",-2,send "AT+CWMODE_CUR=",-3,send "AT+CWMODE=".
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool setOprToStationSoftAP(uint8_t pattern1=DEFAULT_PATTERN,uint8_t pattern2=DEFAULT_PATTERN);

    /**
     * Get the operation mode.
     * @param   pattern1 -1, send "AT+CWMODE_DEF?",-2,send  "AT+CWMODE_CUR?",-3,send "AT+CWMODE?".
     *
     * @retval 0 - failure.
     * @retval 1 - mode Station.
     * @retval 2 - mode AP.
     * @retval 3 - mode AP + station.
     */
    uint8_t getOprMode(uint8_t pattern1=DEFAULT_PATTERN);

    /**
     * Search available AP list and return it.
     *
     * @return the list of available APs.
     * @note This method will occupy a lot of memeory(hundreds of Bytes to a couple of KBytes).
     *  Do not call this method unless you must and ensure that your board has enough memery left.
     */
    String getAPList(void);

    /**
     * Search and returns the current connect AP.
     *
     * @param pattern -1, send "AT+CWJAP_DEF?",-2,send "AT+CWJAP_CUR?",-3,send "AT+CWJAP?".
     * @return the ssid of AP connected now.
     */
    String getNowConecAp(uint8_t pattern=DEFAULT_PATTERN);

    /**
     * Join in AP.
     *
     * @param pattern -1 send "AT+CWJAP_DEF=" -2 send "AT+CWJAP_CUR=" -3 send "AT+CWJAP=".
     * @param ssid - SSID of AP to join in.
     * @param pwd - Password of AP to join in.
     * @retval true - success.
     * @retval false - failure.
     * @note This method will take a couple of seconds.
     */
    bool joinAP(String ssid, String pwd,uint8_t pattern=DEFAULT_PATTERN);

    /**
     * Leave AP joined before.
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool leaveAP(void);

    /**
     * Set SoftAP parameters.
     *
     * @param pattern -1 send "AT+CWSAP_DEF=" -2 send "AT+CWSAP_CUR=" -3 send "AT+CWSAP=".
     * @param ssid - SSID of SoftAP.
     * @param pwd - PASSWORD of SoftAP.
     * @param chl - the channel (1 - 13, default: 7).
     * @param ecn - the way of encrypstion (0 - OPEN, 1 - WEP,
     *  2 - WPA_PSK, 3 - WPA2_PSK, 4 - WPA_WPA2_PSK, default: 4).
     * @retval true - success.
     * @retval false - failure.
     * @note This method should not be called when station mode.
     */
    bool setSoftAPParam(String ssid, String pwd, uint8_t chl = 7, uint8_t ecn = 4,uint8_t pattern=DEFAULT_PATTERN);

    /**
     * get SoftAP parameters.
     *
     * @param pattern -1 send "AT+CWSAP_DEF?" -2 send "AT+CWSAP_CUR?" -3 send "AT+CWSAP?".
     * @note This method should not be called when station mode.
     */
    String getSoftAPParam(uint8_t pattern=DEFAULT_PATTERN);

    /**
     * Get the IP list of devices connected to SoftAP.
     *
     * @return the list of IP.
     * @note This method should not be called when station mode.
     */
    String getJoinedDeviceIP(void);

    /**
     * Get the current state of DHCP.
     *
     * @param pattern -1 send "AT+CWDHCP_DEF?" -2 send "AT+CWDHCP_CUR?"  -3 send "AT+CWDHCP?".
     * @return the state of DHCP.
     *
     */
    String getDHCP(uint8_t pattern=DEFAULT_PATTERN);

     /**
     * Set the  state of DHCP.
     * @param pattern -1 send "AT+CWDHCP_DEF=" -2 send "AT+CWDHCP_CUR=" -3 send "AT+CWDHCP=".
     * @param mode - set ap or set station or set ap + station.
     * @param en - 0 disable DHCP  - 1 enable DHCP.
     * @retval true - success.
     * @retval false - failure.
     */
     bool setDHCP(uint8_t mode, uint8_t en, uint8_t pattern=DEFAULT_PATTERN);

     /**
     * make boot automatically connected.
     * @param en -1 enable  -0 disable.
     * @retval true - success.
     * @retval false - failure.
     */
     bool setAutoConnect(uint8_t en);

     /**
     * Get the station's MAC address.
     * @param pattern -1 send "AT+CIPSTAMAC_DEF?=" -2 send "AT+CIPSTAMAC_CUR?" -3 send "AT+CIPSTAMAC?".
     * @return mac address.
     * @note This method should not be called when ap mode.
     */
     String getStationMac(uint8_t pattern=DEFAULT_PATTERN);

     /**
     * Set the station's MAC address.
     * @param pattern -1 send "AT+CIPSTAMAC_DEF=" -2 send "AT+CIPSTAMAC_CUR=" -3 send "AT+CIPSTAMAC=".
     * @param mac - the mac address of station.
     * @retval true - success.
     * @retval false - failure.
     */
     bool setStationMac(String mac,uint8_t pattern=DEFAULT_PATTERN);

     /**
     * Get the station's IP.
     * @param pattern -1 send "AT+CIPSTA_DEF?" -2 send "AT+CIPSTA_CUR?" -3 send "AT+CIPSTA?".
     * @return the station's IP.
     * @note This method should not be called when ap mode.
     */
     String getStationIp(uint8_t pattern=DEFAULT_PATTERN);

      /**
     * Set the station's IP.
     * @param pattern -1 send "AT+CIPSTA_DEF=" -2 send "AT+CIPSTA_CUR=" -3 send "AT+CIPSTA=".
     * @param ip - the ip of station.
     * @param gateway -the gateway of station.
     * @param netmask -the netmask of station.
     * @retval true - success.
     * @retval false - failure.
     * @note This method should not be called when ap mode.
     */
     bool setStationIp(String ip,String gateway,String netmask,uint8_t pattern=DEFAULT_PATTERN);

     /**
     * Get the AP's IP.
     * @param pattern -1 send "AT+CIPAP_DEF?" -2 send "AT+CIPAP_CUR?" -3 send "AT+CIPAP?".
     * @return ap's ip.
     * @note This method should not be called when station mode.
     *
     */
     String getAPIp(uint8_t pattern=DEFAULT_PATTERN);

     /**
     * Set the AP IP.
     * @param pattern -1 send "AT+CIPAP_DEF=" -2 send "AT+CIPAP_CUR=" -3 send "AT+CIPAP=".
     * @param ip - the ip of AP.
     * @retval true - success.
     * @retval false - failure.
     * @note This method should not be called when station mode.
     */
     bool setAPIp(String ip,uint8_t pattern=DEFAULT_PATTERN);

     /**
     * start smartconfig.
     * @param type -1:ESP_TOUCH  -2:AirKiss.
     * @retval true - success.
     * @retval false - failure.
     */
     bool startSmartConfig(uint8_t type);

     /**
     * stop smartconfig.
     *
     * @retval true - success.
     * @retval false - failure.
     */
     bool stopSmartConfig(void);

    /**
     * Get the current status of connection(UDP and TCP).
     *
     * @return the status.
     */
    String getIPStatus(void);

    /**
     * Get the IP address of ESP8266.
     *
     * @return the IP list.
     */
    String getLocalIP(void);

    /**
     * Enable IP MUX(multiple connection mode).
     *
     * In multiple connection mode, a couple of TCP and UDP communication can be builded.
     * They can be distinguished by the identifier of TCP or UDP named mux_id.
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool enableMUX(void);

    /**
     * Disable IP MUX(single connection mode).
     *
     * In single connection mode, only one TCP or UDP communication can be builded.
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool disableMUX(void);

    /**
     * Create TCP connection in single mode.
     *
     * @param addr - the IP or domain name of the target host.
     * @param port - the port number of the target host.
     * @retval true - success.
     * @retval false - failure.
     */
    bool createTCP(String addr, uint32_t port);

    /**
     * Release TCP connection in single mode.
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool releaseTCP(void);

    /**
     * Register UDP port number in single mode.
     *
     * @param addr - the IP or domain name of the target host.
     * @param port - the port number of the target host.
     * @retval true - success.
     * @retval false - failure.
     */
    bool registerUDP(String addr, uint32_t port);

    /**
     * Unregister UDP port number in single mode.
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool unregisterUDP(void);

    /**
     * Create TCP connection in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @param addr - the IP or domain name of the target host.
     * @param port - the port number of the target host.
     * @retval true - success.
     * @retval false - failure.
     */
    bool createTCP(uint8_t mux_id, String addr, uint32_t port);

    /**
     * Release TCP connection in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @retval true - success.
     * @retval false - failure.
     */
    bool releaseTCP(uint8_t mux_id);

    /**
     * Register UDP port number in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @param addr - the IP or domain name of the target host.
     * @param port - the port number of the target host.
     * @retval true - success.
     * @retval false - failure.
     */
    bool registerUDP(uint8_t mux_id, String addr, uint32_t port);

    /**
     * Unregister UDP port number in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @retval true - success.
     * @retval false - failure.
     */
    bool unregisterUDP(uint8_t mux_id);

    /**
     * Set the timeout of TCP Server.
     *
     * @param timeout - the duration for timeout by second(0 ~ 28800, default:180).
     * @retval true - success.
     * @retval false - failure.
     */
    bool setTCPServerTimeout(uint32_t timeout = 180);

    /**
     * Start TCP Server(Only in multiple mode).
     *
     * After started, user should call method: getIPStatus to know the status of TCP connections.
     * The methods of receiving data can be called for user's any purpose. After communication,
     * release the TCP connection is needed by calling method: releaseTCP with mux_id.
     *
     * @param port - the port number to listen(default: 333).
     * @retval true - success.
     * @retval false - failure.
     *
     * @see String getIPStatus(void);
     * @see uint32_t recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t len, uint32_t timeout);
     * @see bool releaseTCP(uint8_t mux_id);
     */
    bool startTCPServer(uint32_t port = 333);

    /**
     * Stop TCP Server(Only in multiple mode).
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool stopTCPServer(void);

    /**
     *Set the module transfer mode
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool setCIPMODE(uint8_t mode);

    /**
     * Start Server(Only in multiple mode).
     *
     * @param port - the port number to listen(default: 333).
     * @retval true - success.
     * @retval false - failure.
     *
     * @see String getIPStatus(void);
     * @see uint32_t recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t len, uint32_t timeout);
     */
    bool startServer(uint32_t port = 333);

    /**
     * Stop Server(Only in multiple mode).
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool stopServer(void);
    /**
     * Save the passthrough links
     *
     * @retval true - success.
     * @retval false - failure.
     */
    bool saveTransLink (uint8_t mode,String ip,uint32_t port);

   /**
    * PING COMMAND.
    *
    * @retval true - success.
    * @retval false - failure.
    */
    bool setPing(String ip);

    /**
     * Send data based on TCP or UDP builded already in single mode.
     *
     * @param buffer - the buffer of data to send.
     * @param len - the length of data to send.
     * @retval true - success.
     * @retval false - failure.
     */
    bool send(const uint8_t *buffer, uint32_t len);

    /**
     * Send data based on one of TCP or UDP builded already in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @param buffer - the buffer of data to send.
     * @param len - the length of data to send.
     * @retval true - success.
     * @retval false - failure.
     */
    bool send(uint8_t mux_id, const uint8_t *buffer, uint32_t len);

    /**
     * Send data based on TCP or UDP builded already in single mode.
     *
     * @param buffer - the buffer of data to send from flash memeory.
     * @param len - the length of data to send.
     * @retval true - success.
     * @retval false - failure.
     */
    bool sendFromFlash(const uint8_t *buffer, uint32_t len);

    /**
     * Send data based on one of TCP or UDP builded already in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @param buffer - the buffer of data to send from flash memeory.
     * @param len - the length of data to send.
     * @retval true - success.
     * @retval false - failure.
     */
    bool sendFromFlash(uint8_t mux_id, const uint8_t *buffer, uint32_t len);

    /**
     * Receive data from TCP or UDP builded already in single mode.
     *
     * @param buffer - the buffer for storing data.
     * @param buffer_size - the length of the buffer.
     * @param timeout - the time waiting data.
     * @return the length of data received actually.
     */
    uint32_t recv(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = 1000);

    /**
     * Receive data from one of TCP or UDP builded already in multiple mode.
     *
     * @param mux_id - the identifier of this TCP(available value: 0 - 4).
     * @param buffer - the buffer for storing data.
     * @param buffer_size - the length of the buffer.
     * @param timeout - the time waiting data.
     * @return the length of data received actually.
     */
    uint32_t recv(uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = 1000);

    /**
     * Receive data from all of TCP or UDP builded already in multiple mode.
     *
     * After return, coming_mux_id store the id of TCP or UDP from which data coming.
     * User should read the value of coming_mux_id and decide what next to do.
     *
     * @param coming_mux_id - the identifier of TCP or UDP.
     * @param buffer - the buffer for storing data.
     * @param buffer_size - the length of the buffer.
     * @param timeout - the time waiting data.
     * @return the length of data received actually.
     */
    uint32_t recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout = 1000);

 private:

    /*
     * Empty the buffer or UART RX.
     */
    void rx_empty(void);

    /*
     * Recvive data from uart. Return all received data if target found or timeout.
     */
    String recvString(String target, uint32_t timeout = 1000);

    /*
     * Recvive data from uart. Return all received data if one of target1 and target2 found or timeout.
     */
    String recvString(String target1, String target2, uint32_t timeout = 1000);

    /*
     * Recvive data from uart. Return all received data if one of target1, target2 and target3 found or timeout.
     */
    String recvString(String target1, String target2, String target3, uint32_t timeout = 1000);

    /*
     * Recvive data from uart and search first target. Return true if target found, false for timeout.
     */
    bool recvFind(String target, uint32_t timeout = 1000);

    /*
     * Recvive data from uart and search first target and cut out the substring between begin and end(excluding begin and end self).
     * Return true if target found, false for timeout.
     */
    bool recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout = 1000);

    /*
     * Receive a package from uart.
     *
     * @param buffer - the buffer storing data.
     * @param buffer_size - guess what!
     * @param data_len - the length of data actually received(maybe more than buffer_size, the remained data will be abandoned).
     * @param timeout - the duration waitting data comming.
     * @param coming_mux_id - in single connection mode, should be NULL and not NULL in multiple.
     */
    uint32_t recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id);


    bool eAT(void);
    bool eATRST(void);
    bool eATGMR(String &version);
    bool eATGSLP(uint32_t time);
    bool eATE(uint8_t mode);
    bool eATRESTORE(void);
    bool eATSETUART(uint32_t baudrate,uint8_t pattern);

    bool qATCWMODE(uint8_t *mode,uint8_t pattern=3);
    bool eATCWMODE(String &list) ;
    bool sATCWMODE(uint8_t mode,uint8_t pattern=3);
    bool qATCWJAP(String &ssid,uint8_t pattern=3) ;
    bool sATCWJAP(String ssid, String pwd,uint8_t pattern=3);
    bool eATCWLAP(String &list);
    bool eATCWQAP(void);
    bool qATCWSAP(String &List,uint8_t pattern=3);
    bool sATCWSAP(String ssid, String pwd, uint8_t chl, uint8_t ecn,uint8_t pattern=3);
    bool eATCWLIF(String &list);
    bool qATCWDHCP(String &List,uint8_t pattern=3);
    bool sATCWDHCP(uint8_t mode, uint8_t en, uint8_t pattern=3);
    bool eATCWAUTOCONN(uint8_t en);
    bool qATCIPSTAMAC(String &mac,uint8_t pattern=3);
    bool eATCIPSTAMAC(String mac,uint8_t pattern=3);
    bool qATCIPSTAIP(String &ip,uint8_t pattern=3);
    bool eATCIPSTAIP(String ip,String gateway,String netmask,uint8_t pattern=3);
    bool qATCIPAP(String &ip,uint8_t pattern=3);
    bool eATCIPAP(String ip,uint8_t pattern=3);
    bool eCWSTARTSMART(uint8_t type);
    bool eCWSTOPSMART(void);


    bool eATCIPSTATUS(String &list);
    bool sATCIPSTARTSingle(String type, String addr, uint32_t port);
    bool sATCIPSTARTMultiple(uint8_t mux_id, String type, String addr, uint32_t port);
    bool sATCIPSENDSingle(const uint8_t *buffer, uint32_t len);
    bool sATCIPSENDMultiple(uint8_t mux_id, const uint8_t *buffer, uint32_t len);
    bool sATCIPSENDSingleFromFlash(const uint8_t *buffer, uint32_t len);
    bool sATCIPSENDMultipleFromFlash(uint8_t mux_id, const uint8_t *buffer, uint32_t len);
    bool sATCIPCLOSEMulitple(uint8_t mux_id);
    bool eATCIPCLOSESingle(void);
    bool eATCIFSR(String &list);
    bool sATCIPMUX(uint8_t mode);
    bool sATCIPSERVER(uint8_t mode, uint32_t port = 333);
    bool sATCIPMODE(uint8_t mode);
    bool eATSAVETRANSLINK(uint8_t mode,String ip,uint32_t port);
    bool eATPING(String ip);
    bool sATCIPSTO(uint32_t timeout);

    /*
     * +IPD,len:data
     * +IPD,id,len:data
     */

#ifdef ESP8266_USE_SOFTWARE_SERIAL
    SoftwareSerial *m_puart; /* The UART to communicate with ESP8266 */
#else
    HardwareSerial *m_puart; /* The UART to communicate with ESP8266 */
#endif
};

#endif /* #ifndef __ESP8266_H__ */


/**
 * @file ESP8266.cpp
 * @brief The implementation of class ESP8266.
 * @author Wu Pengfei<pengfei.wu@itead.cc>
 * @date 2015.02
 *
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
// #include "ESP8266.h"
// #include <avr/pgmspace.h>

#define LOG_OUTPUT_DEBUG            (1)
#define LOG_OUTPUT_DEBUG_PREFIX     (1)

#define logDebug(arg)\
    do {\
        if (LOG_OUTPUT_DEBUG)\
        {\
            if (LOG_OUTPUT_DEBUG_PREFIX)\
            {\
                Serial.print("[LOG Debug: ");\
                Serial.print((const char*)__FILE__);\
                Serial.print(",");\
                Serial.print((unsigned int)__LINE__);\
                Serial.print(",");\
                Serial.print((const char*)__FUNCTION__);\
                Serial.print("] ");\
            }\
            Serial.print(arg);\
        }\
    } while(0)

#ifdef ESP8266_USE_SOFTWARE_SERIAL
ESP8266::ESP8266(SoftwareSerial &uart, uint32_t baud): m_puart(&uart)
{
    m_puart->begin(baud);
    rx_empty();
}
#else
ESP8266::ESP8266(HardwareSerial &uart, uint32_t baud): m_puart(&uart)
{
    m_puart->begin(baud);
    rx_empty();
}
#endif

bool ESP8266::kick(void)
{
    return eAT();
}

bool ESP8266::restart(void)
{
    unsigned long start;
    if (eATRST()) {
        delay(2000);
        start = millis();
        while (millis() - start < 3000) {
            if (eAT()) {
                delay(1500); /* Waiting for stable */
                return true;
            }
            delay(100);
        }
    }
    return false;
}

String ESP8266::getVersion(void)
{
    String version;
    eATGMR(version);
    return version;
}

bool ESP8266::setEcho(uint8_t mode)
{
    return eATE(mode);
}

bool ESP8266::restore(void)
{
    return eATRESTORE();
}
bool ESP8266::setUart(uint32_t baudrate,uint8_t pattern)
{
    return eATSETUART(baudrate,pattern);
}

bool ESP8266::deepSleep(uint32_t time)
{
    return eATGSLP(time);
}


bool ESP8266::setOprToStation(uint8_t pattern1,uint8_t pattern2)
{
    uint8_t mode;
    if (!qATCWMODE(&mode,pattern1)) {
        return false;
    }
    if (mode == 1) {
        return true;
    } else {
        if (sATCWMODE(1,pattern2)){
            return true;
        } else {
            return false;
        }
    }
}
String ESP8266::getWifiModeList(void)
{
     String list;
     eATCWMODE(list);
     return list;
}
bool ESP8266::setOprToSoftAP(uint8_t pattern1,uint8_t pattern2)
{
    uint8_t mode;
    if (!qATCWMODE(&mode,pattern1)) {
        return false;
    }
    if (mode == 2) {
        return true;
    } else {
        if (sATCWMODE(2,pattern2) ){
            return true;
        } else {
            return false;
        }
    }
}

bool ESP8266::setOprToStationSoftAP(uint8_t pattern1,uint8_t pattern2)
{
    uint8_t mode;
    if (!qATCWMODE(&mode,pattern1)) {
        return false;
    }
    if (mode == 3) {
        return true;
    } else {
        if (sATCWMODE(3,pattern2) ){
            return true;
        } else {
            return false;
        }
    }
}

uint8_t ESP8266::getOprMode(uint8_t pattern1)
{
	uint8_t mode;
	if (!qATCWMODE(&mode,pattern1)) {
        return 0;
    } else {
		return mode;
    }
}

String ESP8266::getNowConecAp(uint8_t pattern)
{
     String ssid;
     qATCWJAP(ssid,pattern);
     return ssid;
}


String ESP8266::getAPList(void)
{
    String list;
    eATCWLAP(list);
    return list;
}

bool ESP8266::joinAP(String ssid, String pwd,uint8_t pattern)
{
    return sATCWJAP(ssid, pwd,pattern);
}

bool ESP8266::leaveAP(void)
{
    return eATCWQAP();
}

String ESP8266::getSoftAPParam(uint8_t pattern)
{
     String list;
     qATCWSAP(list,pattern);
     return list;
}



bool ESP8266::setSoftAPParam(String ssid, String pwd, uint8_t chl, uint8_t ecn,uint8_t pattern)
{
    return sATCWSAP(ssid, pwd, chl, ecn,pattern);
}

String ESP8266::getJoinedDeviceIP(void)
{
    String list;
    eATCWLIF(list);
    return list;
}

String ESP8266::getDHCP(uint8_t pattern)
{
     String dhcp;
     qATCWDHCP(dhcp,pattern);
     return dhcp;
}
bool ESP8266::setDHCP(uint8_t mode, uint8_t en, uint8_t pattern)
{
    return sATCWDHCP(mode, en, pattern);
}

bool ESP8266::setAutoConnect(uint8_t en)
{
    return eATCWAUTOCONN(en);
}
String ESP8266::getStationMac(uint8_t pattern)
{
    String mac;
    qATCIPSTAMAC(mac,pattern);
    return mac;
}


bool ESP8266::setStationMac(String mac,uint8_t pattern)
{
   return eATCIPSTAMAC(mac,pattern);
}

String ESP8266::getStationIp(uint8_t pattern)
{
    String ip;
    qATCIPSTAIP(ip,pattern);
    return ip;
}

bool ESP8266::setStationIp(String ip,String gateway,String netmask,uint8_t pattern)
{
   return eATCIPSTAIP(ip,gateway,netmask,pattern);
}

String ESP8266::getAPIp(uint8_t pattern)
{
    String ip;
    qATCIPAP(ip,pattern);
    return ip;
}

bool ESP8266::setAPIp(String ip,uint8_t pattern)
{
   return eATCIPAP(ip,pattern);
}

bool ESP8266::startSmartConfig(uint8_t type)
{
    return eCWSTARTSMART(type);
}

bool ESP8266::stopSmartConfig(void)
{
    return eCWSTOPSMART();
}




String ESP8266::getIPStatus(void)
{
    String list;
    eATCIPSTATUS(list);
    return list;
}

String ESP8266::getLocalIP(void)
{
    String list;
    eATCIFSR(list);
    return list;
}

bool ESP8266::enableMUX(void)
{
    return sATCIPMUX(1);
}

bool ESP8266::disableMUX(void)
{
    return sATCIPMUX(0);
}

bool ESP8266::createTCP(String addr, uint32_t port)
{
    return sATCIPSTARTSingle("TCP", addr, port);
}

bool ESP8266::releaseTCP(void)
{
    return eATCIPCLOSESingle();
}

bool ESP8266::registerUDP(String addr, uint32_t port)
{
    return sATCIPSTARTSingle("UDP", addr, port);
}

bool ESP8266::unregisterUDP(void)
{
    return eATCIPCLOSESingle();
}

bool ESP8266::createTCP(uint8_t mux_id, String addr, uint32_t port)
{
    return sATCIPSTARTMultiple(mux_id, "TCP", addr, port);
}

bool ESP8266::releaseTCP(uint8_t mux_id)
{
    return sATCIPCLOSEMulitple(mux_id);
}

bool ESP8266::registerUDP(uint8_t mux_id, String addr, uint32_t port)
{
    return sATCIPSTARTMultiple(mux_id, "UDP", addr, port);
}

bool ESP8266::unregisterUDP(uint8_t mux_id)
{
    return sATCIPCLOSEMulitple(mux_id);
}

bool ESP8266::setTCPServerTimeout(uint32_t timeout)
{
    return sATCIPSTO(timeout);
}

bool ESP8266::startTCPServer(uint32_t port)
{
    if (sATCIPSERVER(1, port)) {
        return true;
    }
    return false;
}

bool ESP8266::stopTCPServer(void)
{
    sATCIPSERVER(0);
    restart();
    return false;
}

bool ESP8266::setCIPMODE(uint8_t mode)
{
    return sATCIPMODE(mode);
}

bool ESP8266::saveTransLink (uint8_t mode,String ip,uint32_t port)
{
    return eATSAVETRANSLINK(mode,ip,port);
}

bool ESP8266::setPing(String ip)
{
    return eATPING(ip);
}




bool ESP8266::startServer(uint32_t port)
{
    return startTCPServer(port);
}

bool ESP8266::stopServer(void)
{
    return stopTCPServer();
}

bool ESP8266::send(const uint8_t *buffer, uint32_t len)
{
    return sATCIPSENDSingle(buffer, len);
}

bool ESP8266::sendFromFlash(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
{
    return sATCIPSENDMultipleFromFlash(mux_id, buffer, len);
}

bool ESP8266::sendFromFlash(const uint8_t *buffer, uint32_t len)
{
    return sATCIPSENDSingleFromFlash(buffer, len);
}

bool ESP8266::send(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
{
    return sATCIPSENDMultiple(mux_id, buffer, len);
}

uint32_t ESP8266::recv(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    return recvPkg(buffer, buffer_size, NULL, timeout, NULL);
}

uint32_t ESP8266::recv(uint8_t mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    uint8_t id;
    uint32_t ret;
    ret = recvPkg(buffer, buffer_size, NULL, timeout, &id);
    if (ret > 0 && id == mux_id) {
        return ret;
    }
    return 0;
}

uint32_t ESP8266::recv(uint8_t *coming_mux_id, uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    return recvPkg(buffer, buffer_size, NULL, timeout, coming_mux_id);
}

/*----------------------------------------------------------------------------*/
/* +IPD,<id>,<len>:<data> */
/* +IPD,<len>:<data> */

uint32_t ESP8266::recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id)
{
    String data;
    char a;
    int32_t index_PIPDcomma = -1;
    int32_t index_colon = -1; /* : */
    int32_t index_comma = -1; /* , */
    int32_t len = -1;
    int8_t id = -1;
    bool has_data = false;
    uint32_t ret;
    unsigned long start;
    uint32_t i;

    if (buffer == NULL) {
        return 0;
    }

    start = millis();
    while (millis() - start < timeout) {
        if(m_puart->available() > 0) {
            a = m_puart->read();
            data += a;
        }

        index_PIPDcomma = data.indexOf("+IPD,");
        if (index_PIPDcomma != -1) {
            index_colon = data.indexOf(':', index_PIPDcomma + 5);
            if (index_colon != -1) {
                index_comma = data.indexOf(',', index_PIPDcomma + 5);
                /* +IPD,id,len:data */
                if (index_comma != -1 && index_comma < index_colon) {
                    id = data.substring(index_PIPDcomma + 5, index_comma).toInt();
                    if (id < 0 || id > 4) {
                        return 0;
                    }
                    len = data.substring(index_comma + 1, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                } else { /* +IPD,len:data */
                    len = data.substring(index_PIPDcomma + 5, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                }
                has_data = true;
                break;
            }
        }
    }

    if (has_data) {
        i = 0;
        ret = len > buffer_size ? buffer_size : len;
        start = millis();
        while (millis() - start < 3000) {
            while(m_puart->available() > 0 && i < ret) {
                a = m_puart->read();
                buffer[i++] = a;
            }
            if (i == ret) {
                rx_empty();
                if (data_len) {
                    *data_len = len;
                }
                if (index_comma != -1 && coming_mux_id) {
                    *coming_mux_id = id;
                }
                return ret;
            }
        }
    }
    return 0;
}

void ESP8266::rx_empty(void)
{
    while(m_puart->available() > 0) {
        m_puart->read();
    }
}

String ESP8266::recvString(String target, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_puart->available() > 0) {
            a = m_puart->read();
			if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target) != -1) {
            break;
        }
    }

    return data;
}

String ESP8266::recvString(String target1, String target2, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_puart->available() > 0) {
            a = m_puart->read();
			if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            break;
        } else if (data.indexOf(target2) != -1) {
            break;
        }
    }
    return data;
}

String ESP8266::recvString(String target1, String target2, String target3, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(m_puart->available() > 0) {
            a = m_puart->read();
			if(a == '\0') continue;
            data += a;
        }
        if (data.indexOf(target1) != -1) {
            break;
        } else if (data.indexOf(target2) != -1) {
            break;
        } else if (data.indexOf(target3) != -1) {
            break;
        }
    }
    return data;
}

bool ESP8266::recvFind(String target, uint32_t timeout)
{
    String data_tmp;
    data_tmp = recvString(target, timeout);
    if (data_tmp.indexOf(target) != -1) {
        return true;
    }
    return false;
}

bool ESP8266::recvFindAndFilter(String target, String begin, String end, String &data, uint32_t timeout)
{
    String data_tmp;
    data_tmp = recvString(target, timeout);
    if (data_tmp.indexOf(target) != -1) {
        int32_t index1 = data_tmp.indexOf(begin);
        int32_t index2 = data_tmp.indexOf(end);
        if (index1 != -1 && index2 != -1) {
            index1 += begin.length();
            data = data_tmp.substring(index1, index2);
            return true;
        }
    }
    data = data_tmp;
    return false;
}

bool ESP8266::eAT(void)
{
    rx_empty();
    m_puart->println(F("AT"));
    return recvFind("OK");
}

bool ESP8266::eATRST(void)
{
    rx_empty();
    m_puart->println(F("AT+RST"));
    return recvFind("OK");
}

bool ESP8266::eATGMR(String &version)
{
    rx_empty();
    delay(3000);
    m_puart->println(F("AT+GMR"));
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", version,10000);
}

bool ESP8266::eATGSLP(uint32_t time)
{
    rx_empty();
    m_puart->print(F("AT+GSLP="));
    m_puart->println(time);
    return recvFind("OK");
}


bool ESP8266::eATE(uint8_t mode)
{
    rx_empty();
    m_puart->print(F("ATE"));
    m_puart->println(mode);
    return recvFind("OK");
}

bool ESP8266::eATRESTORE(void)
{
    rx_empty();
    m_puart->println(F("AT+RESTORE"));
    return recvFind("OK");
}


bool ESP8266::eATSETUART(uint32_t baudrate,uint8_t pattern)
{
    rx_empty();
    if(pattern>3||pattern<1){
        return false;
        }
    switch(pattern){
        case 1:
            m_puart->print(F("AT+UART="));
            break;
        case 2:
            m_puart->print(F("AT+UART_CUR="));
            break;
        case 3:
             m_puart->print(F("AT+UART_DEF="));
             break;
    }
    m_puart->print(baudrate);
    m_puart->print(F(","));
    m_puart->print(8);
    m_puart->print(F(","));
    m_puart->print(1);
    m_puart->print(F(","));
    m_puart->print(0);
    m_puart->print(F(","));
    m_puart->println(0);
    if(recvFind("OK",5000)){

    m_puart->begin(baudrate);
    return true;
    }
    else{
    return false;
    }

}


bool ESP8266::qATCWMODE(uint8_t *mode,uint8_t pattern)
{
    String str_mode;
    bool ret;
    if (!mode||!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern)
    {
        case 1 :
            m_puart->println(F("AT+CWMODE_DEF?"));
            break;
        case 2:
            m_puart->println(F("AT+CWMODE_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CWMODE?"));
    }
    ret = recvFindAndFilter("OK", ":", "\r\n\r\nOK", str_mode);
    if (ret) {
        *mode = (uint8_t)str_mode.toInt();
        return true;
    } else {
        return false;
    }
}
bool ESP8266::eATCWMODE(String &list)
{
    rx_empty();
    m_puart->println(F("AT+CWMODE=?"));
    return recvFindAndFilter("OK", "+CWMODE:(", ")\r\n\r\nOK", list);
}

bool ESP8266::sATCWMODE(uint8_t mode,uint8_t pattern)
{
    if(!pattern){
        return false;
        }
    String data;
    rx_empty();
    switch(pattern)
    {
        case 1 :
            m_puart->print(F("AT+CWMODE_DEF="));
            break;
        case 2:
            m_puart->print(F("AT+CWMODE_CUR="));
            break;
        default:
            m_puart->print(F("AT+CWMODE="));
    }
    m_puart->println(mode);
    data = recvString("OK", "no change");

    if (data.indexOf("OK") != -1 || data.indexOf("no change") != -1) {
        return true;
    }
    return false;
}


bool ESP8266::qATCWJAP(String &ssid,uint8_t pattern)
{

    bool ret;
    if (!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern)
    {
        case 1 :
            m_puart->println(F("AT+CWJAP_DEF?"));
            break;
        case 2:
            m_puart->println(F("AT+CWJAP_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CWJAP?"));
    }
    ssid = recvString("OK", "No AP");
    if (ssid.indexOf("OK") != -1 || ssid.indexOf("No AP") != -1) {
        return true;
    }
    return false;

}

bool ESP8266::sATCWJAP(String ssid, String pwd,uint8_t pattern)
{
    String data;
    if (!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern)
    {
        case 1 :
            m_puart->print(F("AT+CWJAP_DEF=\""));

            break;
        case 2:
            m_puart->print(F("AT+CWJAP_CUR=\""));
            break;
        default:
            m_puart->print(F("AT+CWJAP=\""));
    }

    m_puart->print(ssid);
    m_puart->print(F("\",\""));
    m_puart->print(pwd);
    m_puart->println(F("\""));

    data = recvString("OK", "FAIL", 10000);
    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}

bool ESP8266::eATCWLAP(String &list)
{
    String data;
    rx_empty();
    m_puart->println(F("AT+CWLAP"));
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list, 15000);
}




bool ESP8266::eATCWQAP(void)
{
    String data;
    rx_empty();
    m_puart->println(F("AT+CWQAP"));
    return recvFind("OK");
}


bool ESP8266::qATCWSAP(String &List,uint8_t pattern)
{
    if (!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern)
    {
        case 1 :
            m_puart->println(F("AT+CWSAP_DEF?"));

            break;
        case 2:
            m_puart->println(F("AT+CWSAP_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CWSAP?"));
    }
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", List,10000);

}

bool ESP8266::sATCWSAP(String ssid, String pwd, uint8_t chl, uint8_t ecn,uint8_t pattern)
{
    String data;
    if (!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern){
         case 1 :
            m_puart->print(F("AT+CWSAP_DEF=\""));

            break;
        case 2:
            m_puart->print(F("AT+CWSAP_CUR=\""));
            break;
        default:
            m_puart->print(F("AT+CWSAP=\""));

    }
    m_puart->print(ssid);
    m_puart->print(F("\",\""));
    m_puart->print(pwd);
    m_puart->print(F("\","));
    m_puart->print(chl);
    m_puart->print(F(","));
    m_puart->println(ecn);

    data = recvString("OK", "ERROR", 5000);
    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}

bool ESP8266::eATCWLIF(String &list)
{
    String data;
    rx_empty();
    m_puart->println(F("AT+CWLIF"));
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}

bool ESP8266::qATCWDHCP(String &List,uint8_t pattern)
{
    if (!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern)
    {
        case 1 :
            m_puart->println(F("AT+CWDHCP_DEF?"));
            break;
        case 2:
            m_puart->println(F("AT+CWDHCP_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CWDHCP?"));
    }

    return recvFindAndFilter("OK", "\r\r\n", "\r\nOK", List,10000);

}


bool ESP8266::sATCWDHCP(uint8_t mode, uint8_t en, uint8_t pattern)
{
    String data;
    if (!pattern) {
        return false;
    }
    rx_empty();
    switch(pattern){
         case 1 :
            m_puart->print(F("AT+CWDHCP_DEF="));

            break;
        case 2:
            m_puart->print(F("AT+CWDHCP_CUR="));
            break;
        default:
            m_puart->print(F("AT+CWDHCP="));

    }
    m_puart->print(mode);
    m_puart->print(F(","));
    m_puart->println(en);
    data = recvString("OK", "ERROR", 2000);

    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}


bool ESP8266::eATCWAUTOCONN(uint8_t en)
{

    rx_empty();
    if(en>1||en<0){
        return false;
    }
    m_puart->print(F("AT+CWAUTOCONN="));
    m_puart->println(en);
    return recvFind("OK");

}

bool ESP8266::qATCIPSTAMAC(String &mac,uint8_t pattern)
{

    rx_empty();
    if (!pattern) {
        return false;
    }
    switch(pattern){
         case 1 :
            m_puart->println(F("AT+CIPSTAMAC_DEF?"));

            break;
        case 2:
            m_puart->println(F("AT+CIPSTAMAC_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CIPSTAMAC?"));

    }
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", mac,2000);

}



bool ESP8266::eATCIPSTAMAC(String mac,uint8_t pattern)
{

    rx_empty();
    if (!pattern) {
        return false;
    }
    switch(pattern){
         case 1 :
            m_puart->print(F("AT+CIPSTAMAC_DEF="));

            break;
        case 2:
            m_puart->print(F("AT+CIPSTAMAC_CUR="));
            break;
        default:
            m_puart->print(F("AT+CIPSTAMAC="));

    }
    m_puart->print(F("\""));
    m_puart->print(mac);
    m_puart->println(F("\""));
    return recvFind("OK");

}

bool ESP8266::qATCIPSTAIP(String &ip,uint8_t pattern)
{

    rx_empty();
    if (!pattern) {
        return false;
    }
    switch(pattern){
         case 1 :
            m_puart->println(F("AT+CIPSTA_DEF?"));

            break;
        case 2:
            m_puart->println(F("AT+CIPSTA_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CIPSTA?"));

    }
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", ip,2000);

}

bool ESP8266::eATCIPSTAIP(String ip,String gateway,String netmask,uint8_t pattern)
{

    rx_empty();
    if (!pattern) {
        return false;
    }
    switch(pattern){
         case 1 :
            m_puart->print(F("AT+CIPSTA_DEF="));

            break;
        case 2:
            m_puart->print(F("AT+CIPSTA_CUR="));
            break;
        default:
            m_puart->print(F("AT+CIPSTA="));

    }
    m_puart->print(F("\""));
    m_puart->print(ip);
    m_puart->print(F("\",\""));
    m_puart->print(gateway);
    m_puart->print(F("\",\""));
    m_puart->print(netmask);
    m_puart->println(F("\""));
    return recvFind("OK");

}


bool ESP8266::qATCIPAP(String &ip,uint8_t pattern)
{

    rx_empty();
    if (!pattern) {
        return false;
    }
    switch(pattern){
         case 1 :
            m_puart->println(F("AT+CIPAP_DEF?"));

            break;
        case 2:
            m_puart->println(F("AT+CIPAP_CUR?"));
            break;
        default:
            m_puart->println(F("AT+CIPAP?"));

    }
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", ip,2000);

}


bool ESP8266::eATCIPAP(String ip,uint8_t pattern)
{

    rx_empty();
    if (!pattern) {
        return false;
    }
    switch(pattern){
         case 1 :
            m_puart->print(F("AT+CIPAP_DEF="));

            break;
        case 2:
            m_puart->print(F("AT+CIPAP_CUR="));
            break;
        default:
            m_puart->print(F("AT+CIPAP="));

    }
    m_puart->print(F("\""));
    m_puart->print(ip);
    m_puart->println(F("\""));
    return recvFind("OK");

}


bool ESP8266::eCWSTARTSMART(uint8_t type)
{
    rx_empty();
    m_puart->print(F("AT+CWSTARTSMART="));
    m_puart->println(type);
    return recvFind("OK");
}

bool ESP8266::eCWSTOPSMART(void)
{
    rx_empty();
    m_puart->println(F("AT+CWSTOPSMART"));
    return recvFind("OK");
}

bool ESP8266::eATCIPSTATUS(String &list)
{
    String data;
    delay(100);
    rx_empty();
    m_puart->println(F("AT+CIPSTATUS"));
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}
bool ESP8266::sATCIPSTARTSingle(String type, String addr, uint32_t port)
{
    String data;
    rx_empty();
    m_puart->print(F("AT+CIPSTART=\""));
    m_puart->print(type);
    m_puart->print(F("\",\""));
    m_puart->print(addr);
    m_puart->print(F("\","));
    m_puart->println(port);

    data = recvString("OK", "ERROR", "ALREADY CONNECT", 10000);
    if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1) {
        return true;
    }
    return false;
}
bool ESP8266::sATCIPSTARTMultiple(uint8_t mux_id, String type, String addr, uint32_t port)
{
    String data;
    rx_empty();
    m_puart->print(F("AT+CIPSTART="));
    m_puart->print(mux_id);
    m_puart->print(F(",\""));
    m_puart->print(type);
    m_puart->print(F("\",\""));
    m_puart->print(addr);
    m_puart->print(F("\","));
    m_puart->println(port);

    data = recvString("OK", "ERROR", "ALREADY CONNECT", 10000);
    if (data.indexOf("OK") != -1 || data.indexOf("ALREADY CONNECT") != -1) {
        return true;
    }
    return false;
}
bool ESP8266::sATCIPSENDSingle(const uint8_t *buffer, uint32_t len)
{
    rx_empty();
    m_puart->print(F("AT+CIPSEND="));
    m_puart->println(len);
    if (recvFind(">", 5000)) {
        rx_empty();
        for (uint32_t i = 0; i < len; i++) {
            m_puart->write(buffer[i]);
        }
        return recvFind("SEND OK", 10000);
    }
    return false;
}
bool ESP8266::sATCIPSENDMultiple(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
{
    rx_empty();
    m_puart->print(F("AT+CIPSEND="));
    m_puart->print(mux_id);
    m_puart->print(F(","));
    m_puart->println(len);
    if (recvFind(">", 5000)) {
        rx_empty();
        for (uint32_t i = 0; i < len; i++) {
            m_puart->write(buffer[i]);
        }
        return recvFind("SEND OK", 10000);
    }
    return false;
}
bool ESP8266::sATCIPSENDSingleFromFlash(const uint8_t *buffer, uint32_t len)
{
    rx_empty();
    m_puart->print(F("AT+CIPSEND="));
    m_puart->println(len);
    if (recvFind(">", 5000)) {
        rx_empty();
        for (uint32_t i = 0; i < len; i++) {
            m_puart->write((char) pgm_read_byte(&buffer[i]));
        }
        return recvFind("SEND OK", 10000);
    }
    return false;
}
bool ESP8266::sATCIPSENDMultipleFromFlash(uint8_t mux_id, const uint8_t *buffer, uint32_t len)
{
    rx_empty();
    m_puart->print(F("AT+CIPSEND="));
    m_puart->print(mux_id);
    m_puart->print(F(","));
    m_puart->println(len);
    if (recvFind(">", 5000)) {
        rx_empty();
        for (uint32_t i = 0; i < len; i++) {
            m_puart->write((char) pgm_read_byte(&buffer[i]));
        }
        return recvFind("SEND OK", 10000);
    }
    return false;
}
bool ESP8266::sATCIPCLOSEMulitple(uint8_t mux_id)
{
    String data;
    rx_empty();
    m_puart->print(F("AT+CIPCLOSE="));
    m_puart->println(mux_id);

    data = recvString("OK", "link is not", 5000);
    if (data.indexOf("OK") != -1 || data.indexOf("link is not") != -1) {
        return true;
    }
    return false;
}
bool ESP8266::eATCIPCLOSESingle(void)
{
    rx_empty();
    m_puart->println(F("AT+CIPCLOSE"));
    return recvFind("OK", 5000);
}
bool ESP8266::eATCIFSR(String &list)
{
    rx_empty();
    m_puart->println(F("AT+CIFSR"));
    return recvFindAndFilter("OK", "\r\r\n", "\r\n\r\nOK", list);
}
bool ESP8266::sATCIPMUX(uint8_t mode)
{
    String data;
    rx_empty();
    m_puart->print(F("AT+CIPMUX="));
    m_puart->println(mode);

    data = recvString("OK", "Link is builded");
    if (data.indexOf("OK") != -1) {
        return true;
    }
    return false;
}
bool ESP8266::sATCIPSERVER(uint8_t mode, uint32_t port)
{
    String data;
    if (mode) {
        rx_empty();
        m_puart->print(F("AT+CIPSERVER=1,"));
        m_puart->println(port);

        data = recvString("OK", "no change");
        if (data.indexOf("OK") != -1 || data.indexOf("no change") != -1) {
            return true;
        }
        return false;
    } else {
        rx_empty();
        m_puart->println(F("AT+CIPSERVER=0"));
        return recvFind("\r\r\n");
    }
}


bool ESP8266::sATCIPMODE(uint8_t mode)
{
    String data;
    if(mode>1||mode<0){
        return false;
        }
    rx_empty();
    m_puart->print(F("AT+CIPMODE="));
    m_puart->println(mode);

    data = recvString("OK", "Link is builded",2000);
    if (data.indexOf("OK") != -1 ) {
        return true;
    }
    return false;
}




bool ESP8266::eATSAVETRANSLINK(uint8_t mode,String ip,uint32_t port)
{

    String data;
    rx_empty();
    m_puart->print(F("AT+SAVETRANSLINK="));
    m_puart->print(mode);
    m_puart->print(F(",\""));
    m_puart->print(ip);
    m_puart->print(F("\","));
    m_puart->println(port);
    data = recvString("OK", "ERROR",2000);
    if (data.indexOf("OK") != -1 ) {
        return true;
    }
    return false;
}



bool ESP8266::eATPING(String ip)
{
    rx_empty();
    m_puart->print(F("AT+PING="));
    m_puart->print(F("\""));
    m_puart->print(ip);
    m_puart->println(F("\""));
    return recvFind("OK",2000);
}



bool ESP8266::sATCIPSTO(uint32_t timeout)
{
    rx_empty();
    m_puart->print(F("AT+CIPSTO="));
    m_puart->println(timeout);
    return recvFind("OK");
}
