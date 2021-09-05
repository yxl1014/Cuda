//
// Created by yxl on 2021/9/4.
//
#include <iostream>
#include "DataTree.h"

vector<char *> getSqldatas(const char *data) {
    vector<char *> datas;//申明一个集合
    char *p;//临时字符串
    char *buff = (char *) malloc(strlen(data));//申明一个字符串
    memset(buff, 0, strlen(data));
    strcpy(buff, data);//将data字符串拷贝到buff里，防止源字符串变化
    p = strsep(&buff, " ");//获取遇到空格之前的字符
    char *temp = (char *) malloc(strlen(data));//申明一个临时字符串
    memset(temp, 0, strlen(data));

    int i = 0;//拆分状态
    while (p != NULL) {//若拆分出来的字符串为空，则结束
        if (i != 0 || p[0] == '(') {//若字符串第一个为(说明之后的数据为嵌套sql

            if (p[0] == '(') {//若为(
                if (i == 0) {//若i==0说明这是遇到的第一个(
                    strcpy(strcat(temp, " "), p);//则将p加上空格拷贝到temp中
                } else {
                    strcat(strcat(temp, " "), p);//否则直接拼接到temp中
                }
                i += 1;//然后i+1，若遇到多重嵌套不会则这是一个data
            }

            if (p[0] != '(' && i != 0) {//若第一个字符不为(且i！=0,说明这还是在嵌套sql内部的数据，继续拼接
                strcat(strcat(temp, " "), p);
                int j = 1;//临时数
                while (p[strlen(p) - j] == ')') {//循环判断p的最后一个字符是不是)
                    i -= 1;//若是则i-1
                    j++;//j++，防止出现两个))连载一起的情况；如：select * from xxx where in (select * from yyy where in (select * from where in (select * from ppp)) and (select * from ppp)))
                    if (i == 0) {//若i=0，则说明嵌套sql结束，向集合的最后添加数据temp
                        char *ok = (char *) malloc(strlen(temp));
                        strcpy(ok, temp);
                        datas.push_back(ok);
                    }
                }
            }

            p = strsep(&buff, " ");//继续拆分字符串
        } else {
            datas.push_back(p);//若不是sql嵌套，则直接向集合添加数据
            p = strsep(&buff, " ");//再次拆分
        }
    }
    return datas;//返回集合
}

void addNode(DataHeadNode *head, char *data) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));//申请一块链表内存
    memset(node, 0, sizeof(ListNode));//清空内存
    DataNode *dataNode;//申明一个树节点


    if (data[0] == '(') {//若数据是sql则创建子节点
        char *temp = (char *) malloc(strlen(data) - 2);//申请比data小2的临时内存
        memset(temp, 0, strlen(data) - 2);//清空内存
        memcpy(temp, data + 1, strlen(data) - 2);//将data掐头去尾拷贝到temp里
        dataNode = createDataTree(temp);//将data再次分解
    } else {
        dataNode = (DataNode *) malloc(sizeof(DataNode));//申请一个treenode
        memset(dataNode, 0, sizeof(DataNode));//清空内存
        int len=strlen(data);
        dataNode->data = (char *) malloc(len);
        strcpy(dataNode->data, data);//拷贝data
        dataNode->datasize=len;
        dataNode->nodesize++;
        //cout << dataNode->treenode << endl;
    }


    head->datasize += dataNode->datasize;
    head->nodesize += dataNode->nodesize;

    node->treenode = dataNode;//将treenode赋值给listnode的data
    if (head->dataList == nullptr) {//若这个listnode是第一个
        head->dataList = node;
        head->tailnode = node;
        return;
    }
    head->tailnode->next = node;//若不是使用尾插法插入listnode节点
    node->pre = head->tailnode;
    head->tailnode = node;
    node->next = nullptr;
}

DataHeadNode *createDataTree(char *sql) {
    DataHeadNode *headNode = (DataHeadNode *) malloc(sizeof(DataHeadNode));//申明一个新的treenode头结点
    memset(headNode, 0, sizeof(DataHeadNode));//清空内存
    headNode->nodetype = 5;//设置该节点类型为 集合 及 嵌套的sql语句

    headNode->data = (char *) malloc(strlen(sql));
    memset(headNode->data, 0, strlen(sql));
    //cout << headNode->treenode << endl;

    strcpy(headNode->data, sql);//将数据拷贝到节点
/*
    cout<<"指向null前的树节点："<<headNode<<endl;
    cout<<"指向null前的树节点中的链表头结点："<<headNode->dataList<<endl;
    cout<<"指向null前的树节点中的链表尾结点："<<headNode->tailnode<<endl;
    cout<<"指向null前的树节点中的数据："<<headNode->data<<endl;
    printf("指向null前的树节点中数据的地址：%x\n",(long)headNode->data);
*/
    headNode->dataList = nullptr;//初始化treenode头结点
    headNode->tailnode = nullptr;
/*    printf("指向null后的树节点中数据的地址：%x\n",(long)headNode->data);
    cout<<"指向null后的树节点中的数据："<<headNode->data<<endl;
    cout<<"指向null后的树节点："<<headNode<<endl;
    cout<<"指向null后的树节点中的链表头结点："<<headNode->dataList<<endl;
    cout<<"指向null后的树节点中的链表尾结点："<<headNode->tailnode<<endl;*/
    //cout<<headNode->data<<endl;

    //memset(headNode->dataList, 0, sizeof(headNode->dataList));
    const char *treenode = headNode->data;

    vector<char *> datas = getSqldatas(treenode);//获取到拆分sql语句后的集合
    for (vector<char *>::iterator it = datas.begin(); it != datas.end(); it++) {//遍历集合
        addNode(headNode, *it);//添加子节点
    }

    return headNode;//返回头结点
}

int selectAllNode(DataHeadNode *treehead, char * datas[],int start) {
    ListNode *head = treehead->dataList;//获得树节点中的子节点的头结点
    ListNode *temp;//定义一个临时指针
    int index=start;//获取开始位置
    if (treehead->nodetype != 5) {//若此树节点为无子节点  节点，则直接添加数据返回
        datas[index]=(char *) malloc(strlen(treehead->data));//申明内存
        memset(datas[index], 0, strlen(treehead->data));//初始化内存
        strcpy(datas[index],treehead->data);//拷贝内存
        index++;//下标索引加一
        return index;//返回索引值
    }
    for (temp = head; temp != nullptr; temp = temp->next) {//遍历子节点链表的所有节点
        if (temp->treenode->nodetype == 5) {//若子节点中有 有节点树
            index=selectAllNode(temp->treenode, datas,index);//则递归调用，获取返回索引
            continue;//继续循环
        }
        datas[index]=(char *) malloc(strlen(temp->treenode->data));//申明内存
        memset(datas[index], 0, strlen(temp->treenode->data));//初始化内存
        strcpy(datas[index],temp->treenode->data);//拷贝内存
        index++;//下标索引加一
    }
    return index;//返回索引值
}

