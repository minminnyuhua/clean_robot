#include<iostream>
#include<fstream>
#include<string>
//#include "floor.h"
using namespace std;
//int height,width,Battery;char **Matrix;

class Robot;
class floor{
    friend Robot;
    private:
        int width;
        int height;
        int Battery;
        char**posfloor;
        char **Matrix;
        char **floorState;
        int R_X,R_Y;
    public:

        int readData();
        void printFloor();
        /*int getHeight(){
            return this->height;
        }
        int getWidth(){
            return this->width;
        }
        */
        int getBattery(){
            return this->Battery;
        }
        bool returnState(int x,int y);
        void setCleaned(int x,int y);
        bool checkAllCleaned(int x,int y);
        int getDistanceR(int R_X,int R_Y);
        void setFloor();
};

void floor::printFloor(){ //print information
   cout<<"floor info:"<<endl<<"Matrix:"<<endl<<endl;
   for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            cout<<Matrix[i][j];
        }
        cout<<endl;
    }
    cout<<"height: "<<this->height<<endl<<"width: "<<width<<endl<<"Battery: "<<this->Battery<<endl<<"(rx,ry): ("<<R_X<<","<<R_Y<<")"<<endl;

}
int floor::readData(){  //set height width battery rx ry Matrix
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

    this->R_X=rx;
    this->R_Y=ry;

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
	    void initState(){
	        setBattery();setLifeTime();setRindex();
            curX=R_X;curY=R_Y;lifeTime=Battery;
	    }
	    int getCurX(){
	        return this->curX;
            }
        int getCurY(){
	        return this->curY;
            }
		void goCharged(int R_X,int R_Y);
		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
		void setBattery(){
            r.readData();
            this->Battery=r.Battery;
        }
        int getBattery(){
            return this->Battery;
        }
        void setLifeTime(){
            this->lifeTime=this->Battery;
        }
        void setRindex(){
            r.readData();
            this->R_X=r.R_X;
            this->R_Y=r.R_Y;
        }
};
void Robot::printRobot(){ //print information
    cout<<"robot info: "<<endl;
    cout<<"battery: "<<Battery<<endl<<"lifetime: "<<lifeTime<<endl<<"(rx,ry): ("<<R_X<<","<<R_Y<<")"<<endl<<"(curX,curY): ("<<curX<<","<<curY<<")";
}
void Robot::moveDown(){
    curX++;
    lifeTime--;
}
void Robot::moveUp(){
    curX--;
    lifeTime--;
}
void Robot::moveRight(){
    curY++;
    lifeTime--;
}
void Robot::moveLeft(){
    curY--;
    lifeTime--;
}

int main()
{

    floor f;
    f.readData();
    f.printFloor();
    Robot r;
    r.initState();
    r.printRobot();

}
