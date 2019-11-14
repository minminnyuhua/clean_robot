#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
class QueueList;
class QueueNode{
    friend class QueueList;
    pair data;
    QueueNode *next;
    QueueNode():data(0,0),next(0){};
    QueueNode(pair data_in):data(data_in),next(0){};
};

class QueueList{
private:
    QueueNode *front;
    QueueNode *back;
    int size;
public:
    QueueList():front(0),back(0),size(0){};
    void Push(pair());
    void Pop();
    bool IsEmpty();
    int getFront();
    int getBack();
    int getSize();
};

void QueueList::Push(int x){

    if (IsEmpty()) {
        front = new QueueNode(x);
        back = front;
        size++;
        return;
    }

    QueueNode *newNode = new QueueNode(x);
    back->next = newNode;
    back = newNode;         // update back pointer
    size++;
}

void QueueList::Pop(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    QueueNode *deletenode = front;
    front = front->next;    // update front pointer
    delete deletenode;
    deletenode = 0;
    size--;
}

int QueueList::getFront(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }

    return front->data;
}

int QueueList::getBack(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }

    return back->data;
}

bool QueueList::IsEmpty(){

//    return (size == 0);
    return ((front && back) == 0);
}

int QueueList::getSize(){

    return size;
}
class Pair{
    public:
        Pair():first(0),second(0){};
        Pair(int f, int s):first(f),second(s){};
        int first;
        int second;
}
wayTo=new int* [height];
    for(int i=0;i<height;i++){
        wayTo[i]=new int[width];
        for(int j=0;j<width;j++){
            if(curFloor[i][j]=='1')
                wayTo[i][j]=INT_MIN;
            else if(curFloor[i][j]=='0')
                wayTo[i][j]=INT_MAX;
            else if(curFloor[i][j]=='R')
                wayTo[i][j]=0;
        }

{
    curFloor=new char* [height];
    for(int i=0;i<height;i++){
        curFloor[i]=new char[width];
        for(int j=0;j<width;j++){
            curFloor[i][j]=Matrix[i][j];
        }
    }

#endif // QUEUE_H_INCLUDED
