#include <iostream>
#include "DataTree.h"

using namespace std;

typedef struct ResultSet {

} ResultSet;


ResultSet doSelect(char *sql) {

}

int main() {
    /*char * sql="";
     *
    DataHeadNode * node=createDataTree(sql);
    cout<<node->data<<"\t"<<node->nodetype<<endl;*/
    char str[] = "select * from xxx where in (select * from yyy where in (select * from where in (select * from ppp)) and (select * from ppp)))";

    char* data="GoldenGlobalView";
    char * temp=(char *) malloc(strlen(data)-2);
    memset(temp, 0, strlen(data)-2);
    memcpy(temp,data+1, strlen(data)-2);
    cout<<temp<<endl;
    return 0;
    char *buff;
    buff = str;
    /*vector<char *> datas= getSqldatas(buff);
    for (int i = 0; i < datas.size(); ++i) {
        cout<<datas[i]<<endl;
    }*/
    /*char *p;
    char *buff;
    buff = str;
    p = strsep(&buff, " ");
    char *temp = (char *) malloc(sizeof(char *));
    memset(temp, 0, sizeof(char *));
    int i = 0;
    while (p != NULL) {
        if (i != 0 || p[0] == '(') {

            if (p[0] == '(') {
                if (i == 0) {
                    strcpy(strcat(temp, " "), p);
                } else {
                    strcat(strcat(temp, " "), p);
                }
                i += 1;
            }

            if (p[0] != '(' && i != 0) {
                strcat(strcat(temp, " "), p);
                int j = 1;
                while (p[strlen(p) - j] == ')') {
                    i -= 1;
                    j++;
                    if (i == 0)
                        printf("%s\n", temp);
                }
            }
            p = strsep(&buff, " ");
        } else {
            printf("%s\n", p);
            p = strsep(&buff, " ");
        }
    }*/
    return 0;
}
