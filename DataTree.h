#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;
//语法分析树节点
typedef struct DataNode {
    int nodetype;//1、原数据；2、表名；3、字段名；4、视图类型；5、集合(嵌套的sql语句)；
    int datasize=0;//节点中数据的总长度
    int nodesize=0;//子节点数
    char *data;
//该节点名(每一段的内容)，头结点此处为空
    struct ListNode *dataList;//(一个双向链表),节点中的数据为DataNode
    struct ListNode *tailnode;
//节点的叶子节点们
} DataNode, DataHeadNode;

typedef struct ListNode {
    DataNode *treenode;
//数据
    struct ListNode *next;
//下一个节点
    struct ListNode *pre;
//上一个节点
} ListNode;

DataHeadNode *createDataTree(char *sql);//创建语法分析树

vector<char *> getSqldatas(const char *data);//拆分sql语句

int selectAllNode(DataHeadNode *treehead, char ** datas,int start);//遍历语法分析树的所有子节点中的数据