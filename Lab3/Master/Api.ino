#define API_MASTER 0
#define API_RED 0
#define API_GREEN 1
#define API_OFF 2
#define API_PING 3
#define API_ACK 4
#define API_STATUS 5
#define API_TIME 6

int* getApiMessage(int message, int entryNumber, int targetEntryNumber) {
    int *array = new int[4];
    array[0] = entryNumber;
    array[1] = message;
    array[2] = targetEntryNumber;
    array[3] = entryNumber + message + targetEntryNumber;
    return array;
}

int* getApiMessageResponse(int message, int entryNumber, int requestEntryNumber, int status) {
    switch (message) {
        case API_PING:
        {
            int *array = new int[5];
            array[0] = entryNumber;
            array[1] = API_STATUS;
            array[2] = requestEntryNumber;
            array[3] = status;
            array[4] = entryNumber + status + API_STATUS;
            return array;
        }
        default:
        {
            int *array = new int[4];
            array[0] = entryNumber;
            array[1] = API_ACK;
            array[2] = requestEntryNumber;
            array[3] = entryNumber + API_ACK + entryNumber;
            return array;
        }
    }
}