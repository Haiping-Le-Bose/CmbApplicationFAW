

#include "CART.h"
#include "_CMB.h"
#include "CMB_TYPES.h"
#include "CMB_Message_Helper.h"
//#include "CMB_Socket_Helper.h"
#include "CMB_Logger.h"

CART_STATUS Tuning_Adaptor_initialize(CMB* ccb, void* reserved);
CART_Cmd_Ret Tuning_Adaptor_sendMessageToRemote(CMB* ccb, CART_Message* msg);
CART_STATUS Tuning_Adaptor_deinitialize(CMB* ccb, void* arg);
CART_Cmd_Ret Tuning_Adaptor_tcp_recv(uint8_t* buffer, const uint32_t len, ssize_t* recv_length);
CART_Cmd_Ret Tuning_Adaptor_receiveFromRemote(uint8_t* buffer, const uint32_t len, ssize_t* recv_length);
CART_Cmd_Ret Tuning_Adaptor_sendToBus(CMB* ccb, unsigned char *payload, const uint32_t reqPayloadSize);
CART_Cmd_Ret Tuning_Adaptor_addDestination(CMB* ccb, void* cfg);


