//
// Created by martin on 5/23/21.
//

#ifndef TESTSOCKET_MESSAGE_H
#define TESTSOCKET_MESSAGE_H

struct MessageHeader;

const uint MAX_MESSAGE_STRING_SIZE = 1000;

#pragma pack(1)
enum MessageType {
    CHAT_MESSAGE = 1000
};


struct MessageHeader {
    size_t length_;
    uint32_t messageType_;
};

const size_t HEADER_BUFFER_SIZE = sizeof (MessageHeader);

struct ChatMessage {
    MessageHeader header_;
    char message_[MAX_MESSAGE_STRING_SIZE];
};

#pragma pack()
#endif //TESTSOCKET_MESSAGE_H
