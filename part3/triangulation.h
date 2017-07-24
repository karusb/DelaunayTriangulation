
#include <vector>
#include <iostream>
#include <ostream>
#include <math.h>

/** \brief
 * Triangulation class: Holds vertices and triangle objects that are generated from a .tri file
 * \param T type of the data
 * \param char* filen is the file name where vertices and triangles are hold. Should be entered as "sample.tri"
 * \param vertices vertex class that will be built in constructor
 * \param triangles triangle class that will be built in constructor
 * \param triarea vector containing areas of the individual triangles
 * \param circumcentrex vector containing the x points of the circumcentre of the triangles
 * \param circumcentrey vector containing the y points of the circumcentre of the triangles
 * \param circumradius vector containing the circumradius of the triangles
 *  Methods:
 *
 *  setcircumcentre()                                   Sets circumcentre of every triangle
 *  vertex<T>& getvertices()                            Return vertices object
 *  triangle<T>& gettriangle()                          Return triangle object
 *  findtrianglearea()                                  Find the area of the triangles
 *  vector<T> Isthisintriangle(T pointx,T pointy)       Given points x = pointx , y=pointy returns a vector with triangleid's containing the triangles encapsulating the point
 *  T linearintegrate()                                 Linear integration method over the triangulation / prerequisites: #include "f.h" , run .findtrianglearea() before
 *  T constantintegrate()                               Constant value integration method over the triangulation / prerequisites: #include "f.h" , run .findtrianglearea() and .setcircumference() before
 *  T reachinverticesx(int element)                     Returns element point x of vertices
 *  T reachinverticesy(int element)                     Returns element point y of vertices
 *  T reachinverticesz(int element)                     Returns element point z of vertices
 *  T reachintrianglesx(int element)                    Returns element vertex x of triangles
 *  T reachintrianglesy(int element)                    Returns element vertex y of triangles
 *  T reachintrianglesz(int element)                    Returns element vertex z of triangles
 *  T reachintriarea(int element)                       Returns the area of the triangle element
 *  T reachincircumradius(int element)                  Returns the circumradius of the triangle element
 *  *  Operators:
 *  >>  Input type : >>vertices>>triangles
 *  <<  Output type : <<vertices<<triangles
 *
 *  \author Baris Tanyeri
 */

template<typename T>
class triangulation
{
public:
    /** Default constructor */
    triangulation<T>(){};
    triangulation<T>(vertex<T> newvertex,triangle<T> newtriangle);
    triangulation<T>(char* filen);
    /** Default destructor */
    virtual ~triangulation<T>() {}
    void setcircumcentre();
    T linearintegrate();
    T constantintegrate();
    inline vertex<T>* getvertices(){return &vertices;}
    inline triangle<T>* gettriangle(){return &triangles;}
    T reachinverticesx(int element){return (vertices.reachtx(element));}
    T reachinverticesy(int element){return (vertices.reachty(element));}
    T reachinverticesz(int element){return (vertices.reachtz(element));}
    T reachintrianglesx(int element){return (triangles.reachtx(element));}
    T reachintrianglesy(int element){return (triangles.reachty(element));}
    T reachintrianglesz(int element){return (triangles.reachtz(element));}
    T reachintriarea(int element){return triarea[element];}
    T reachincircumradius(int element){return circumradius[element];}
    T reachincircumcentrex(int element){return circumcentrex[element];}
    T reachincircumcentrey(int element){return circumcentrey[element];}
    void findtrianglearea();
    int Isthisintriangle(T pointx,T pointy);
    inline friend istream& operator>>(istream& in, triangulation<T> &c)
    {
        return in >> c.vertices >> c.triangles ;
    }

    inline friend ostream& operator<<(ostream& out, triangulation<T> &c)
    {
        return out << c.vertices <<endl<<c.triangles<<endl;
    }

protected:
private:
    vertex<T> vertices;
    triangle<T> triangles;
    vector<T> circumcentrex;
    vector<T> circumcentrey;
    vector<T> triarea;
    vector<T> circumradius;

};
template<typename T>triangulation<T>::triangulation(vertex<T> newvertex,triangle<T> newtriangle)
{
    vertices = newvertex;
    triangles = newtriangle;
}
template<typename T> triangulation<T>::triangulation(char* filen)
{
    vertices =  vertex<T>();
    triangles =  triangle<T>();
    ifstream filelocation(filen);
    //triangulation<float> triyangle = triangulation<float>();
    //ifstream filelocation (filen);
    if (filelocation.is_open()&&filen!="")
    {
        int vvisize,tvisize,vdimension,tdimension,vattrbs,tattrbs,vresultcount=0,tresultcount=0;

        filelocation>>vvisize>>vdimension>>vattrbs;

        cout<<vvisize<<" "<<vdimension<<" "<<vattrbs<<endl;

        vertices.setsize(vvisize);
        cout<<"Set size ok..."<<endl;
        vertices.setdim(vdimension);
        cout<<"Set dimension ok..."<<endl;
        while(vresultcount<=vvisize-1)
        {
            filelocation>>vertices ;
            vresultcount++;

        }
        if(filelocation.eof())
        {filelocation>>tvisize>>tdimension>>tattrbs;

        cout<<tvisize<<" "<<tdimension<<" "<<tattrbs<<endl;

        triangles.setsize(tvisize);
        cout<<"Set size ok..."<<endl;
        triangles.setdim(tdimension);
        cout<<"Set dimension ok..."<<endl;
        if(tattrbs!=0)triangles.setattrbsize(tattrbs-1);
        cout<<"Set attribute size ok..."<<endl;

        while(tresultcount<=tvisize-1)
        {
            filelocation>>triangles ;
            tresultcount++;
        }
        }
        filelocation.close();
    }
    else cout << "Unable to open file"<<endl;
}
template<typename T>
void triangulation<T>::setcircumcentre()
{
    T A(0),B(0),C(0),D(0),E(0),F(0),G(0),ccx(0),ccy(0);
    T x1(0),x2(0),x3(0),y1(0),y2(0),y3(0);
    for(int triangleid=0; triangleid!=triangles.returnsize(); ++triangleid)
    {


        x1 = vertices.reachvx(triangles.reachtx(triangleid));
        y1 = vertices.reachvy(triangles.reachtx(triangleid));
        x2 = vertices.reachvx(triangles.reachty(triangleid));
        y2 = vertices.reachvy(triangles.reachty(triangleid));
        x3 = vertices.reachvx(triangles.reachtz(triangleid));
        y3 = vertices.reachvy(triangles.reachtz(triangleid));
        A = x2 - x1;
        B = y2 - y1;
        C = x3 - x1;
        D = y3 - y1;
        E = A * (x1 + x2) + B * (y1 + y3);
        F = C * (x1 + x2) + D * (y1 + y3);
        G = 2.0 * (A * (y3 - y2) - B * (x3 - x2));
        ccx = (D * E - B * F) / G;
        ccy = (A * F - C * E) / G;
        circumcentrex.push_back(ccx);
        circumcentrey.push_back(ccy);
        circumradius.push_back(sqrt(((ccx*ccx)-(2*ccx*x1)-(x1*x1))-((ccy*ccy)-(2*ccy*y1)-(y1*y1)))); // I didn't want to use pow() function for speed issues
    }
    cout<<"Circumcentre & Circumradius set ok..."<<endl;
}
template<typename T>
int triangulation<T>::Isthisintriangle(T pointx,T pointy)
{
    vector<T> trianglescontainer;
    //trianglescontainer. resize(triangles.returnsize());
    bool b1, b2, b3;
    T x1(0),x2(0),x3(0),y1(0),y2(0),y3(0);
    for(int triangleid=0; triangleid!=triangles.returnsize(); ++triangleid)
    {
        x1 = vertices.reachvx(triangles.reachtx(triangleid));
        y1 = vertices.reachvy(triangles.reachtx(triangleid));
        x2 = vertices.reachvx(triangles.reachty(triangleid));
        y2 = vertices.reachvy(triangles.reachty(triangleid));
        x3 = vertices.reachvx(triangles.reachtz(triangleid));
        y3 = vertices.reachvy(triangles.reachtz(triangleid));

        b1 = (pointx - x2) * (y1 - y2) - (x1 - x2) * (pointy - y2) <0.0f;
        b2 = (pointx - x3) * (y2 - y3) - (x2 - x3) * (pointy - y3) <0.0f;
        b3 = (pointx - x1) * (y3 - y1) - (x3 - x1) * (pointy - y1) <0.0f;
        if((b1 == b2) && (b2 == b3))return(triangleid);
    }
    cout<<"Search Complete..."<<endl;
    return(-1);
}
template<typename T>
void triangulation<T>::findtrianglearea()
{
    T x1(0),x2(0),x3(0),y1(0),y2(0),y3(0);
        for(int triangleid=0; triangleid!=triangles.returnsize(); ++triangleid)
    {
    x1 = vertices.reachvx(triangles.reachtx(triangleid));
    y1 = vertices.reachvy(triangles.reachtx(triangleid));
    x2 = vertices.reachvx(triangles.reachty(triangleid));
    y2 = vertices.reachvy(triangles.reachty(triangleid));
    x3 = vertices.reachvx(triangles.reachtz(triangleid));
    y3 = vertices.reachvy(triangles.reachtz(triangleid));
    //T  result = (((x1 - x3) * (y2 - y3)) - ((x2 - x3) * (y1 - y3)));///2.0f;
    T result = ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2) ))/2.0f;

    if(result<0)result = result*(-1); // NO NEGATIVE AREA ALLOWED :)
    triarea.push_back(result);
    }
    cout<<"Area vector generated..."<<endl;
}
template<typename T>
T triangulation<T>::linearintegrate()
{
    T x1(0),x2(0),x3(0),y1(0),y2(0),y3(0),result(0);
    for(int triangleid=0; triangleid!=triangles.returnsize(); ++triangleid)
    {
        x1 = vertices.reachvx(triangles.reachtx(triangleid));
        y1 = vertices.reachvy(triangles.reachtx(triangleid));
        x2 = vertices.reachvx(triangles.reachty(triangleid));
        y2 = vertices.reachvy(triangles.reachty(triangleid));
        x3 = vertices.reachvx(triangles.reachtz(triangleid));
        y3 = vertices.reachvy(triangles.reachtz(triangleid));
        //cout<<triangleid<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<y1<<" "<<y2<<" "<<y3<<endl;
        result += (f<T>(x1,y1) + f<T>(x2,y2) + f<T>(x3,y3)) * triarea[triangleid]/3.0;
    }
    cout<<"Linear integration complete"<<endl;
    return result;
}
template<typename T>
T triangulation<T>::constantintegrate()
{
    T result(0);
    for(int triangleid=0; triangleid!=triangles.returnsize(); ++triangleid)
    {
        result += (f<T>(circumcentrex[triangleid],circumcentrey[triangleid]) * triarea[triangleid]);
    }
    cout<<"Constant integration complete"<<endl;
    return result;
}

