#include <iostream>
#include <fstream>
//Include needed components
#include "f.h"
#include "vertex.h"
#include "triangle.h"
#include "triangulation.h"
#include "Interval.h"
using namespace std;
// Just another implementation of class member function of triangulation.Isthisintriangle
bool CircumcircleContains(triangulation<float>* t, int trianglelement,Interval<float,float> inter);

int main()
{
    //char* file = "vertices.node";
    //Initilization of the objects
    triangulation<float> generated = triangulation<float>("vertices1.node");
    vertex<float>* aquiredvertex=generated.getvertices();
    triangle<float>* generatedtriangle = generated.gettriangle();
    vertex<float> newvertex = vertex<float>();
    triangle<float> newtriangle = triangle<float>();
    triangle<float> badtriangle = triangle<float>();

    badtriangle.setdim(3);
    badtriangle.setattrbsize(0);
    newvertex.setsize(4);
    newvertex.setdim(2);
    generatedtriangle->setattrbsize(0);
    generatedtriangle->setdim(3);

    int triangleid(0),usedid(-1);
    float boundaryx(0),boundaryy(0);
    float p1(0),p2(0);
    bool p1f(false),p2f(false);

    // Find the boundaries of the vertices
    for(int i=0; i<aquiredvertex->reachsize(); ++i)
    {

        p1 = aquiredvertex->reachvx(i);
        p2 = aquiredvertex->reachvy(i);
        if(p1<0)
        {
            p1=p1*(-1.);
            p1f=true;
        }
        if(p2<0)
        {
            p2=p2*(-1.);
            p2f=true;
        }
        if(p1>boundaryx)
        {
            switch (p1f)
            {
            case true:
                boundaryx = (p1+1)*(-1.);
                break;
            case false:
                boundaryx = p1+1;
                break;
            }
        }
        if(p2>boundaryy)
        {
            switch (p2f)
            {
            case true:
                boundaryy = (p2+1)*(-1.);
                break;
            case false:
                boundaryy = p2+1;
                break;
            }
        }
    }
    // Set boundaries to be bigger than the original

    //cout<<boundaryx<<boundaryy<<endl;
    //cout << generated << endl;
    //cout<< *aquiredvertex<<endl;



    newvertex.setvx(0);
    newvertex.setvy(0);
    newvertex.setvx(boundaryx);
    newvertex.setvy(0);
    newvertex.setvx(boundaryx);
    newvertex.setvy(boundaryy);
    newvertex.setvx(0);
    newvertex.setvy(boundaryy);

    newtriangle.setsize(10);
    newtriangle.setdim(3);
    newtriangle.setattrbsize(0);

    newtriangle.settx(0);
    newtriangle.settx(2);
    newtriangle.setty(3);
    newtriangle.setty(1);
    newtriangle.settz(1);
    newtriangle.settz(3);
    //cout<<newvertex.reachvx(1)<<endl;
    //cout<<generatedtriangle->reachtx(1)<<endl;
    triangulation<float> newtriangulation = triangulation<float>(newvertex,newtriangle);
    cout<<*aquiredvertex<<endl;
    cout<<*generatedtriangle<<endl;
    cout<<newvertex<<endl;
    //cout<<newtriangulation<<endl;

    for(int i=0; i<=aquiredvertex->reachsize()-1; i++)
    {
        //cout<<aquiredvertex->reachvx(i)<<endl;
        triangleid = newtriangulation.Isthisintriangle(aquiredvertex->reachvx(i),aquiredvertex->reachvy(i));
        //cout<<triangleid<<endl;

        //Interval to be used for the other implementation
        //Interval<float,float> circuminter = Interval<float,float>(aquiredvertex->reachvx(i),aquiredvertex->reachvy(i),0);



        if(usedid!=triangleid && triangleid>-1) // small check for not adding the same triangle
        {
            badtriangle.setti(triangleid);
            badtriangle.settx(newtriangle.reachtx(triangleid));
            badtriangle.setty(newtriangle.reachty(triangleid));
            badtriangle.settz(newtriangle.reachtz(triangleid));
            usedid=triangleid;
        }


    }
    cout<<badtriangle<<endl;

// Erase the first bad triangle, this should be in the loop above with finding boundaries and adding triangles function
    newtriangle.erasetx(badtriangle.reachti(0));
    newtriangle.erasety(badtriangle.reachti(0));
    newtriangle.erasetz(badtriangle.reachti(0));

    cout<<newtriangle<<endl;
    return 0;
}
// Check whether the circumcirlce of T contains p
bool CircumcircleContains(triangulation<float>* t, int trianglelement,Interval<float,float> inter) // Another application of isthisintriangle with intervals
{
    t->setcircumcentre();
    float r2 = t->reachincircumradius(trianglelement);

    return (((inter.getlower()-t->reachincircumcentrex(trianglelement))* (inter.gethigher()-t->reachincircumcentrey(trianglelement)) <= r2));
}
