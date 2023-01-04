#define API_MASTER 0
#define API_RED 0
#define API_GREEN 1
#define API_OFF 2
#define API_PING 3
#define API_ACK 4
#define API_STATUS 5
#define API_TIME 6


int* getApiMessage(int message, int entryNumber, int targetEntryNumber) {
    int arr[4] = {entryNumber, message, targetEntryNumber, entryNumber + message + targetEntryNumber};
    return arr;
}


int* getApiMessageResponse(int message, int entryNumber, int requestEntryNumber, int status) {
    switch (message) {
        case API_PING:
            int arr[5] = {entryNumber, API_STATUS, requestEntryNumber, status, entryNumber + status + API_STATUS};
            return arr;  
        default:
            int arr[4] = {entryNumber, API_ACK, requestEntryNumber, entryNumber + API_ACK + entryNumber};
    }
}


int getApiMaster() {
    return API_MASTER;
}

int getApiRed() {
    return API_RED;
}

int getApiGreen() {
    return API_GREEN;
}

int getApiOff() {
    return API_OFF;
}

int getApiPing() {
    return API_PING;
}

int getApiAck() {
    return API_ACK;
}

int getApiStatus() {
    return API_STATUS;
}

int getApiTime() {
    return API_TIME;
}