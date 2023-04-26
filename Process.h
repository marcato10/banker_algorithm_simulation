enum status{
    FINISHED,
    WAITING,
    EXECUTING
};

typedef struct{
    int PID;
    int* resources_required;
    enum status process_status;
}Process;