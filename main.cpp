#include <iostream>
#include "DataTree.h"

using namespace std;

typedef struct ResultSet {

} ResultSet;


ResultSet doSelect(char *sql) {

}

int main() {
    char sql1[] = "select * from xxx where in (select * from yyy where in (select * from where in (select * from ppp)) and (select * from ppp))";
    DataHeadNode *headNode = createDataTree(sql1);
    cout<<headNode->datasize<<endl;
    cout<<headNode->data<<endl;
    cout<<headNode->nodesize<<endl;
    char * data[headNode->nodesize];
    int  ii=0;
    int size=selectAllNode(headNode,data,ii);
    cout<<size<<endl;
    for (int i=0;i<headNode->nodesize;i++) {//遍历集合
        cout<<data[i]<<" ";
    }
    cout<<endl;
    return 0;
}
