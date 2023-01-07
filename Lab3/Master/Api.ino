#define API_MASTER 0
#define API_RED 0
#define API_GREEN 1
#define API_OFF 2
#define API_PING 3
#define API_ACK 4
#define API_STATUS 5
#define API_TIME 6

int getMessageResponseSize(int message){
    switch (message) {
        case API_PING:
        { 
            return 5;
        }
        default:
        {
            return 4;
        }
}

// what to send in the initial request
int* getApiMessage(int message, int entryNumber, int targetEntryNumber) {
    int *array = new int[5];
    array[0] = 5;
    array[1] = entryNumber;
    array[2] = message;
    array[3] = targetEntryNumber;
    array[4] = entryNumber + message + targetEntryNumber;
    return array;
}


//what to respond to the message
int* getApiMessageResponse(int message, int entryNumber, int requestEntryNumber, int status) {
    switch (message) {
        case API_PING:
        {
            int *array = new int[6];
            array[0] = 6;
            array[1] = entryNumber;
            array[2] = API_STATUS;
            array[3] = requestEntryNumber;
            array[4] = status;
            array[5] = entryNumber + status + API_STATUS;
            return array;
        }
        default:
        {
            int *array = new int[5];
            array[0] = 5;
            array[1] = entryNumber;
            array[2] = API_ACK;
            array[3] = requestEntryNumber;
            array[4] = entryNumber + API_ACK + entryNumber;
            return array;
        }
    }
}