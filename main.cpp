#include <iostream>
#include <fstream>
#include <omp.h>

#include "f.h"
#include "vertex.h"
#include "triangle.h"
#include "triangulation.h"
//#include "triangulation.cpp"



using namespace std;

int main()
{


    triangulation<float> triyangle = triangulation<float>("triangulation.tri");



    triyangle.setcircumcentre();
    triyangle.findtrianglearea();

    cout<<"Found triangle: "<<triyangle.Isthisintriangle(-145.,-5.)<<endl;

    cout<<triyangle.linearintegrate()<<endl;
    cout<<triyangle.constantintegrate() <<endl;
    //cout<<triyangle.gettriangle()<<endl;


    //cin>>result;
    //std::ofstream opfile;
    //cout<<triyangle;

    return 0;
}
