/* data struct and its operration */

typedef struct DataNode
{
    char* cmd;
    char* desc;
    int   (*handler)();
    struct DataNode *next;
} tDataNode;

/* find a cmd in the linklist and return the datanote pointer */

tDataNode* FindCmd(tDataNode * head, char * cmd);
/* show all cmd in the list */

int ShowAllCmd(tDataNode * head);
