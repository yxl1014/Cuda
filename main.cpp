#include <iostream>
#include "DataTree.h"

using namespace std;

typedef struct ResultSet {

} ResultSet;


ResultSet doSelect(char *sql) {

}

int main() {
   char sql1[] = "select * from xxx where in (select * from yyy where in (select * from where in (select * from ppp)) and (select * from ppp))";
    /* const char * sql=sql1;
     vector<char *> datas = getSqldatas(sql);//获取到拆分sql语句后的集合
     for (vector<char *>::iterator it = datas.begin(); it != datas.end(); it++) {//遍历集合
         cout<<*it<<endl;
   }
 /*
     char *sql2="(select * from yyy where in (select * from where in (select * from ppp)) and (select * from ppp))";
     char * temp=(char *) malloc(strlen(sql2)-2);
     memset(temp, 0, strlen(sql2)-2);
     memcpy(temp,sql2+1, strlen(sql2)-2);
     cout<<temp<<endl<<endl;*/

/*    const char * sql3="select * from yyy where in (select * from where in (select * from ppp)) and (select * from ppp)";
    vector<char *> dats2 = getSqldatas(sql3);//获取到拆分sql语句后的集合
    for (vector<char *>::iterator it = dats2.begin(); it != dats2.end(); it++) {//遍历集合
        cout<<*it<<endl;
    }*/
    char *sql = sql1;
    DataHeadNode *node = createDataTree(sql);
    cout << node->data << "\t" << node->nodetype << endl;


/*    char* data="GoldenGlobalView";
    char * temp=(char *) malloc(strlen(data)-2);
    memset(temp, 0, strlen(data)-2);
    memcpy(temp,data+1, strlen(data)-2);
    cout<<temp<<endl;
    return 0;
    char *buff;
    buff = str;*/
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
