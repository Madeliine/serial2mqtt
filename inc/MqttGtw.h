#ifndef MQTTGTW_H
#define MQTTGTW_H

#include "MQTTAsync.h"
#include <Cbor.h>
#include <EventBus.h>


#define ADDRESS     "tcp://limero.ddns.net:1883"
#define CLIENTID    "ExampleClientSub"
#define TOPIC       "stm32/alive"
#define PAYLOAD     "true"
#define QOS         1
#define TIMEOUT     10000L

class MqttGtw : public Actor
{
private:
    MQTTAsync_token _deliveredtoken;
    MQTTAsync _client;
    Str _host;
    uint16_t _port;
    Str _clientId;
    Str _user;
    Str _password;
    Str _willTopic;
    Str _willMessage;
    int _willQos;
    bool _willRetain;
    uint32_t _keepAlive;
    int _cleanSession;
    bool _connected;
    uint16_t _msgid;
    uint16_t _lastSrc;
    int _fd[2];   // pipe fd to wakeup in select

public:

    MqttGtw();
    virtual ~MqttGtw();
    void setup();
    void onEvent(Cbor& cbor);
    void onActorRegister(Cbor& cbor);

    static void onConnectionLost(void *context, char *cause);
    static int onMessage(void *context, char *topicName, int topicLen, MQTTAsync_message *message);
    static void onDisconnect(void* context, MQTTAsync_successData* response);
    static void onSubscribe(void* context, MQTTAsync_successData* response);
    static void onSubscribeFailure(void* context, MQTTAsync_failureData* response);
    static void onConnectFailure(void* context, MQTTAsync_failureData* response);
    static void onConnect(void* context, MQTTAsync_successData* response);
    static void onPublishSuccess(void* context, MQTTAsync_successData* response);
    static void onPublishFailure(void* context, MQTTAsync_failureData* response);
    void connect(Cbor& cbor);
    void loadConfig(Cbor& cbor);
    void disconnect(Cbor& cbor);
    void publish(Cbor& cbor);
    void subscribe(Cbor& cbor);

    int fd();
    void wakeup();

};


#endif // MQTTGTW_H
