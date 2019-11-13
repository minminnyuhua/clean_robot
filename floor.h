#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED
#include "Robot.h"
#include <iostream>
#include<fstream>
#include<string>
using namespace std;
class floor{
	//friend class Robot;
    private:
        int width;
        int height;
        char* posfloor;
        char **Matrix;
        Robot r;
        //int R_X,R_Y;
    public:
        int readData();
        void printFloor();
        int getHeight(){
            return this->height;
        }
        int getWidth(){
            return this->width;
        }
        /*void setHeight(int heig){
            this->height=heig;
        }
        void setWidth(int wid){
            this->width=wid;
        }
        void setRindex(int rx,int ry){
            this->R_X=rx;
            this->R_Y=ry;

        }*/

        bool returnState(int x,int y);
        void setCleaned(int x,int y);
        bool checkAllCleaned(int x,int y);
        int getDistanceR(int R_X,int R_Y);
};


#endif // FLOOR_H_INCLUDED
