#include<iostream>
#include<fstream>
#include<string>
#include<limits.h>
using namespace std;
int height,width,Battery,R_X,R_Y;char **Matrix;int **wayTo;bool **visit;int uncleanFloor=0;int oo=0;

//*****************************START OF QUEUE*********************************
//*****************************START OF QUEUE*********************************
class Pair{
    public:
        Pair():first(0),second(0){};
        Pair(int f, int s):first(f),second(s){};
        int first;
        int second;
};

class QueueList;
class QueueNode{
    friend class QueueList;
    Pair data;
    QueueNode():data(0,0),next(0),pre(0){};
    QueueNode(Pair data_in):data(data_in),next(0),pre(0){};
    QueueNode *next ,*pre;

};


class QueueList{
private:
    QueueNode *front;
    QueueNode *back;
    int size;
public:
    QueueList():front(0),back(0),size(0){};
    void Push(Pair);
    void Pop();
    void PopB();
    bool IsEmpty();
    Pair getFront();
    Pair getBack();
    int getSize();
};

void QueueList::Push(Pair x){
    if (IsEmpty()) {
        front = new QueueNode(x);
        back = front;
        size++;
        return;
    }

    QueueNode *newNode = new QueueNode(x);
    back->next = newNode;
    back ->next->pre=back;
    back=back->next;        // update back pointer
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
void QueueList::PopB(){

    if(front!=back)
    {
        back=back->pre;
        delete back->next;
    }
    else{
        delete front;
        front=back=NULL;
    }

    size--;
}



Pair QueueList::getFront(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
    } else {
        return front->data;
    }

}

Pair QueueList::getBack(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
    }
    else {
        return back->data;
    }
}

bool QueueList::IsEmpty(){

//    return (size == 0);
    return ((front && back) == 0);
}

int QueueList::getSize(){

    return size;
}
//************************END OF QUEUE**************************************************************
//************************END OF QUEUE**************************************************************

//***********************START OF FLOOR*************************************************************
//***********************START OF FLOOR*************************************************************
class Robot;
class floor{
    friend class Robot;
    private:
        //char**posfloor;
        char **curFloor;
        int RX,RY;
        bool **visited;
        //Robot* rrr;
    public:
        bool returnState(int x,int y);
        void setStep(); //v
        void setFloor(); //v
};

//**********************************************************
void floor::setFloor(){
    curFloor=new char* [height];
    for(int i=0;i<height;i++){
        curFloor[i]=new char[width];
        for(int j=0;j<width;j++){
            curFloor[i][j]=Matrix[i][j];
        }
    }
}
//**********************************************************
void floor::setStep(){
    wayTo=new int* [height];
    for(int i=0;i<height;i++){
        wayTo[i]=new int[width];
        for(int j=0;j<width;j++){
            if(curFloor[i][j]=='1')
                wayTo[i][j]=-1;
            else if(curFloor[i][j]=='0')
               {
                   wayTo[i][j]=INT_MAX;
                   uncleanFloor++;

               }
            else if(curFloor[i][j]=='R')
                wayTo[i][j]=0;
        }
    }
    visited=new bool*[height];
    for(int i=0;i<height;i++){
        visited[i]=new bool[width];
        for(int j=0;j<width;j++){
            visited[i][j]=false;
        }
    }

    QueueList q;
    visited[R_X][R_Y] = true;
    q.Push(Pair(R_X, R_Y));
    while(!q.IsEmpty()) {
        Pair a = q.getFront();
        q.Pop();

        if(a.first - 1 >= 0 && wayTo[a.first - 1][a.second]!= -1 && visited[a.first - 1][a.second] == false) {
            q.Push(Pair(a.first - 1, a.second));
            wayTo[a.first - 1][a.second] = wayTo[a.first][a.second] + 1;
            visited[a.first - 1][a.second] = true;
        }

        if(a.first + 1 < height && wayTo[a.first + 1][a.second]!= -1 && visited[a.first + 1][a.second] == false) {
            q.Push(Pair(a.first + 1, a.second));
            wayTo[a.first + 1][a.second] = wayTo[a.first][a.second] + 1;
            visited[a.first + 1][a.second] = true;
        }

        if(a.second - 1 >= 0  && wayTo[a.first ][a.second- 1]!= -1 && visited[a.first][a.second - 1] == false) {
            q.Push(Pair(a.first, a.second -1));
            wayTo[a.first][a.second -1] = wayTo[a.first][a.second] + 1;
            visited[a.first][a.second -1] = true;
        }

        if(a.second + 1 < width && wayTo[a.first ][a.second+ 1]!= -1 && visited[a.first][a.second + 1] == false) {
            q.Push(Pair(a.first, a.second + 1));
            wayTo[a.first][a.second + 1] = wayTo[a.first][a.second] + 1;
            visited[a.first][a.second + 1] = true;
        }
    }
    //print out to check
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            cout<<wayTo[i][j]<<"  ";
        }
        cout<<endl;
    }
}
//*****************************************************


//********************************END OF FLOOR********************************************************
//********************************END OF FLOOR********************************************************

//***********************************START OF ROBOT***************************************************
//***********************************START OF ROBOT***************************************************
class Robot{
	friend class floor;
	private:
		int battery;
		int lifeTime;
		int r_X,r_Y;
		int curX,curY;
		//bool **visit;
	public:
	    QueueList qq,line,backR,toDel;
	    void getDistanceR();
	    bool checkAllCleaned();
	    void goCharged();
	    void printRobot();
	    int getCurX() {return this->curX;}
        int getCurY() {return this->curY;}
		void moveRight();
		void moveLeft();
		void moveDown();
		void moveUp();
        int getBattery()  {return this->battery;}
        int getLifeTime() {return this->lifeTime;}
        void initState(int batt,int rx,int ry){
	        this->battery=batt;
	        this->r_X=rx;this->r_Y=ry;
            curX=r_X;curY=r_Y;lifeTime=battery;
	    }
};

void Robot::getDistanceR(){
    oo++;
    int maxi=wayTo[0][0];  //to check where is the maxi step
    Pair record;           //to record the position of maxi
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(wayTo[i][j]>maxi){
              maxi=wayTo[i][j];
              record.first=i;
              record.second=j;
            }
        }
    }
    cout<<maxi<<" "<<record.first<<" ,"<<record.second<<endl; //print to check

    visit=new bool*[height+1];
    for(int i=0;i<height;i++){
        visit[i]=new bool[width];
        for(int j=0;j<=width;j++){
            visit[i][j]=false;
        }
    }
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            if(wayTo[i][j]==-1)
                visit[i][j]==true;

    //QueueList qq,line,backR;            //用 qq 存目前位址
    visit[R_X][R_Y] = true;
    qq.Push(Pair(R_X, R_Y));
    line.Push(Pair(R_X, R_Y));  //line 存走過的path

    Pair path;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    for(int i=0;i<=maxi;i++)
    {
        path = qq.getFront();
        if (path.first< height-1 && path.first > 0 && path.second > 0 && path.second < width-1)
        {

           if (wayTo[path.first+1][path.second]<wayTo[path.first][path.second]&&wayTo[path.first-1][path.second]<wayTo[path.first][path.second]&&
                wayTo[path.first][path.second+1]<wayTo[path.first][path.second]&&wayTo[path.first][path.second-1]<wayTo[path.first][path.second]) { break;}
        }


       qq.Pop();
       if(path.first + 1 < height-1 )
            {
                //if(visit[path.first + 1][path.second] == false)
                //{
                    if( wayTo[path.first + 1][path.second] != -1 &&(wayTo[path.first + 1][path.second]-1 == wayTo[path.first][path.second]) )
                    {
                        cout << "moveDown" << endl;
                        moveDown();
                        visit[path.first + 1][path.second] = true;
                        qq.Push(Pair(path.first + 1,path.second));
                        line.Push(Pair(path.first + 1,path.second));
                        backR.Push(Pair(path.first + 1,path.second));
                        toDel.Push(Pair(path.first + 1,path.second));
                        continue;
                    }
                //}
            }
            if(path.first - 1 > 0 )
            {
               // if( visit[path.first - 1][path.second] == false)
                //{
                    if(  wayTo[path.first - 1][path.second] != -1 && (wayTo[path.first - 1][path.second]-1 == wayTo[path.first][path.second]) )
                    {
                        cout << "moveUp" << endl;
                        moveUp();
                        visit[path.first - 1][path.second] = true;
                        qq.Push(Pair(path.first - 1,path.second));
                        line.Push(Pair(path.first - 1,path.second));
                        backR.Push(Pair(path.first - 1,path.second));
                        toDel.Push(Pair(path.first - 1,path.second));
                        continue;
                    }
                //}
            }
            if(path.second - 1 > 0 )
            {
               // if( visit[path.first][path.second - 1] == false)
                //{
                    if( wayTo[path.first][path.second - 1] != -1 && (wayTo[path.first][path.second - 1]-1 == wayTo[path.first][path.second]) )
                    {
                        cout << "moveLeft" << endl;
                        moveLeft();
                        visit[path.first][path.second - 1] = true;
                        qq.Push(Pair(path.first,path.second - 1));
                        line.Push(Pair(path.first,path.second - 1));
                        backR.Push(Pair(path.first,path.second - 1));
                        toDel.Push(Pair(path.first,path.second - 1));
                        continue;
                    }
                //}
            }
            if(path.second + 1 < width-1  )
            {
                //if( visit[path.first][path.second + 1] == false)
                //{
                    if (wayTo[path.first][path.second + 1] != -1 && (wayTo[path.first][path.second + 1]-1 == wayTo[path.first][path.second]) )
                    {
                        cout << "moveRight" << endl;
                        moveRight();
                        visit[path.first][path.second + 1] = true;
                        qq.Push(Pair(path.first,path.second + 1));
                        line.Push(Pair(path.first,path.second + 1));
                        backR.Push(Pair(path.first,path.second + 1));
                        toDel.Push(Pair(path.first,path.second + 1));
                        continue;
                    }
                //}
            }


       }

        //把list裡面最大的兩個設為-1

            int x=toDel.getSize();
            if(x>3)
            {
                for(int i=0;i<x-2;i++)toDel.Pop();
                while(!toDel.IsEmpty())
                {
                    wayTo[toDel.getFront().first][toDel.getFront().second]=-1;
                    uncleanFloor--;
                    toDel.Pop();
                }
            }
            else
            {
                toDel.Pop();
                while(!toDel.IsEmpty())
                {
                    wayTo[toDel.getFront().first][toDel.getFront().second]=-1;
                    uncleanFloor--;
                    toDel.Pop();
                }
            }


        printRobot();
        goCharged();

}

void Robot::goCharged(){

    backR.Pop();
    //backR.PopB();backR.Pop();
    int s=backR.getSize();
    for(int i=1;i<s;i++) {
        backR.PopB();

        line.Push(backR.getBack());
    }
    this->curX=this->r_X;
    this->curY=this->r_Y;
    this->lifeTime=battery;


}
bool Robot::checkAllCleaned()
{
//cout<<"eee"<<endl;
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            if(wayTo[i][j]!=-1&&i!=R_X&&j!=R_Y)
                return false;
    return true;
}

void Robot::printRobot(){ //print information
    cout<<"robot info: "<<endl;
    cout<<"battery: "<<battery<<endl<<"lifetime: "<<lifeTime<<endl<<"(rx,ry): ("<<R_X<<","<<R_Y<<")"<<endl<<"(curX,curY): ("<<curX<<","<<curY<<")"<<endl;
}
void Robot::moveDown(){
    if((curX+1<height)||((curX+1==r_X)&&(curY==r_Y))){
        curX++;
        lifeTime--;
    }
}
void Robot::moveUp(){
    if((curX-1>0)||((curX-1==r_X)&&(curY==r_Y))){
        curX--;
        lifeTime--;
    }
}
void Robot::moveRight(){
    if((curY+1<width)||((curX==r_X)&&(curY+1==r_Y))){
        curY++;
        lifeTime--;
    }
}
void Robot::moveLeft(){
    if((curY-1>0)||((curX==r_X)&&(curY-1==r_Y))){
        curY--;
        lifeTime--;
    }
}
//*******************************************END OF ROBOT****************************************************
//*******************************************END OF ROBOT****************************************************
void printFloor(){ //print information
   cout<<"floor info:"<<endl<<"Matrix:"<<endl<<endl;
   for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            cout<<Matrix[i][j];
        }
        cout<<endl;
    }
    cout<<"height: "<<height<<endl<<"width: "<<width<<endl<<"Battery: "<<Battery<<endl<<"(rx,ry): ("<<R_X<<","<<R_Y<<")"<<endl;

}
int readData(){  //set height width battery rx ry Matrix
    string heig,wid,battery;char data;int rx,ry;
    ifstream infile("floor.data",ios::in);
    if(!infile)
    {
        cout<<"can't open datafile"<<endl;
        return 1;
    }
    infile>>heig>>wid>>battery;
    height=std::stoi(heig);width=std::stoi(wid);Battery=std::stoi(battery); //assign to private variable
  //***************************
    Matrix = new char *[height];//create the row
    for(int i=0;i<height;i++)
    {
        Matrix[i]=new char[width]; //create the col
        for(int j=0;j<width;j++)
        {
            infile>>data;
            if(data=='R'){
                rx=i;ry=j;
                Matrix[i][j]='R';
            }
            else
                Matrix[i][j]=data;
        }
    }
    infile.close();

    R_X=rx;R_Y=ry;

}


//*****************************************************************************
int main()
{

    floor f;
    readData();
    printFloor();
    Robot r;
    r.initState(Battery,R_X,R_Y);

    r.printRobot();
    f.setFloor();
    f.setStep();
  /*  r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();
    r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();r.getDistanceR();*/
   r.getDistanceR();//r.getDistanceR();//r.getDistanceR();
    bool vv=false;
    while(vv!=true){
    //for(int i=0;i<2;i++){
        vv=r.checkAllCleaned();
         r.getDistanceR();

    }

    ofstream outf("final.path",ios::out);
    if(!outf)
    {
        cout<<"can't open final.path"<<endl;
        return 1;
    }


    r.line.Push(Pair(R_X,R_Y));
    int countPath=r.line.getSize()-(oo-1);  //總步數為getsixe-呼叫distance的次數
   // cout<<countPath+(oo-1)<<"woow"<<endl;
    outf<<countPath+(oo-1)<<endl;

     for(int i=0;i<countPath+(oo-1);i++)
    {

       // cout<<r.line.getFront().first<<" "<<r.line.getFront().second<<endl;
        Pair mat=r.line.getFront();
        outf<<mat.first<<" "<<mat.second<<endl;

        r.line.Pop();
    }






    outf.close();



    for(int i=0;i<height;i++)
    {
        delete[]wayTo[i];
        delete[]visit[i];
        delete[]Matrix[i];
    }

    delete[]wayTo;
    delete[]visit;
    delete[]Matrix;

}
