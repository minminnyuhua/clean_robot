#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int height,width,Battery,R_X,R_Y;char **Matrix;

class Robot;
class floor{
    friend Robot;
    private:
        char**posfloor;
        char **curFloor;
        int R_X,R_Y;
    public:
        bool returnState(int x,int y);
        void setCleaned(int x,int y);
        bool checkAllCleaned();
        int getDistanceR(int R_X,int R_Y);
        void setFloor();
};
void floor::setFloor(){
    curFloor=new char* [height];
    for(int i=0;i<height;i++){
        curFloor[i]=new char[width];
        for(int j=0;j<width;j++){
            curFloor[i][j]=Matrix[i][j];
        }
    }
    //print out to check
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            cout<<curFloor[i][j];
        }
        cout<<endl;
    }
}
bool floor::checkAllCleaned(){
    floor after;
    after.setFloor();
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            if(after.curFloor[i][j]!=2) return false;
    return true;

}


class Robot{
	friend class floor;
	private:
		int Battery;
		int lifeTime;
		int R_X,R_Y;
		int curX,curY;
		floor r;
	public:
        void printRobot();
	    void initState(int batt,int rx,int ry){
	        this->Battery=batt;this->R_X=rx;this->R_Y=ry;
            curX=R_X;curY=R_Y;lifeTime=Battery;
	    }
	    int getCurX(){
	        return this->curX;
        }
        int getCurY(){
	        return this->curY;
        }

		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();

        int getBattery(){
            return this->Battery;
        }
        int getLifeTime(){
            return this->lifeTime;
        }
        void goCharged(int R_X,int R_Y);
};
void Robot::printRobot(){ //print information
    cout<<"robot info: "<<endl;
    cout<<"battery: "<<Battery<<endl<<"lifetime: "<<lifeTime<<endl<<"(rx,ry): ("<<R_X<<","<<R_Y<<")"<<endl<<"(curX,curY): ("<<curX<<","<<curY<<")"<<endl;
}
void Robot::moveDown(){
    if((curX+1<height)||((curX+1==R_X)&&(curY==R_Y))){
        curX++;
        lifeTime--;
    }
}
void Robot::moveUp(){
    if((curX-1>0)||((curX-1==R_X)&&(curY==R_Y))){
        curX--;
        lifeTime--;
    }
}
void Robot::moveRight(){
    if((curY+1<width)||((curX==R_X)&&(curY+1==R_Y))){
        curY++;
        lifeTime--;
    }
}
void Robot::moveLeft(){
    if((curY-1>0)||((curX==R_X)&&(curY-1==R_Y))){
        curY--;
        lifeTime--;
    }
}
//*********************************************************************************

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
void toClean(){

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
}
