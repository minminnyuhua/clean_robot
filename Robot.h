#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED
#include <iostream>
#include<fstream>
#include<string>
using namespace std;
class Robot{
	friend class floor;
	private:
		int Battery;
		int R_X,R_Y;
		int curX,curY;
	public:
	    Robot(int posX,int posY,int life){
            posX=R_X; posY=R_Y; life=Battery;
        }

        Robot(const Robot &cleaning)
        {
            curX=cleaning.curX, curY=cleaning.curY, Battery=cleaning.Battery;
        }
	    void initState(){
            curX=R_X;curY=R_Y;
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
		void setBattery(int battery){
            this->Battery=battery;
        }
        int getBattery(){
            return this->Battery;
        }
        void setRindex(int rx,int ry){
            this->R_X=rx;
            this->R_Y=ry;
        }
};


#endif // ROBOT_H_INCLUDED
