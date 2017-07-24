#include <omp.h>
#include <vector>
#include <iostream>
#include <ostream>

#ifndef TRIANGULATION_H
#define TRIANGULATION_H
/** \brief
 * Triangulation class: Holds vertices and triangle objects that are generated from a .tri file
 * \param T type of the data
 * \param char* filen is the file name where vertices and triangles are hold. Should be entered as "sample.tri"

 *  Methods:
 *
 *  setcircumcentre()                                   Sets circumcentre of every triangle
 *  vertex<T>& getvertices()                            Return vertices object
 *  triangle<T>& gettriangle()                          Return triangle object
 *  findtrianglearea()                                  Find the area of the triangles
 *  vector<T> Isthisintriangle(T pointx,T pointy)       Given points x = pointx , y=pointy returns a vector with triangleid's containing the triangles encapsulating the point
 *  T linearintegrate()                                 Linear integration method over the triangulation / prerequisites: #include "f.h" , run .findtrianglearea() before
 *  T constantintegrate()                               Constant value integration method over the triangulation / prerequisites: #include "f.h" , run .findtrianglearea() and .setcircumference() before
 *
 *  *  Operators:
 *  >>  Input type : >>vertices>>triangles
 *  <<  Output type : <<vertices<<triangles
 * \version 1.0
 *  \author Baris Tanyeri
 */

template<typename T>
class triangulation
{
public:
    /** Default constructor */
    triangulation<T>(char* filen);
    /** Default destructor */
    virtual ~triangulation<T>() {}
    void setcircumcentre();
    T linearintegrate();
    T constantintegrate();
    inline vertex<T>& getvertices()
    {
        return vertices;
    }
    inline triangle<T>& gettriangle()
    {
        return triangles;
    }
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

};
template<typename T> triangulation<T>::triangulation(char* filen)
{
    vertices =  vertex<T>();
    triangles =  triangle<T>();
    ifstream filelocation(filen);
    //triangulation<float> triyangle = triangulation<float>();
    //ifstream filelocation (filen);
    if (filelocation.is_open())
    {
        int vvisize,tvisize,vdimension,tdimension,vattrbs,tattrbs,vresultcount=0,tresultcount=0;

                //cout<<filelocation.gcount<<endl;
                filelocation>>vvisize>>vdimension>>vattrbs;
                //filelocation.seekg(((((vvisize)*(vdimension+2))*2))+1);
                filelocation.seekg(38420);
                filelocation>>tvisize>>tdimension>>tattrbs;
                cout<<vvisize<<" "<<vdimension<<" "<<vattrbs<<endl;

                vertices.setsize(vvisize);
                cout<<"Set size ok..."<<endl;
                vertices.setdim(vdimension);
                cout<<"Set dimension ok..."<<endl;
                cout<<tvisize<<" "<<tdimension<<" "<<tattrbs<<endl;

                triangles.setsize(tvisize);
                cout<<"Set size ok..."<<endl;
                triangles.setdim(tdimension);
                cout<<"Set dimension ok..."<<endl;
                if(tattrbs!=0)triangles.setattrbsize(tattrbs-1);
                cout<<"Set attribute size ok..."<<endl;

        //Parallelized File reading // this works
        #pragma omp parallel shared(vvisize,tvisize,vdimension,tdimension,vattrbs,tattrbs,filelocation) private(vresultcount,tresultcount)
        {
            #pragma omp sections // Threads to run on different cores
            {
                #pragma omp section //Thread
                {


                filelocation.seekg(8);
                for(vresultcount =0; vresultcount<=vvisize-1; vresultcount++)
                {
                    filelocation>>vertices ;

                }
                }
                #pragma omp section
                {

                //filelocation.seekg(((((vvisize+1)*(vdimension+2))*2))+1);
                filelocation.seekg(38431);
                for(tresultcount=0; tresultcount<=tvisize-1; tresultcount++)
                {
                    filelocation>>triangles ;
                }
                }

                }
                }
                filelocation.close();


    }
    else cout << "Unable to open file"<<endl;

}
template<typename T>
void triangulation<T>::setcircumcentre()
{
    T A=0,B=0,C=0,D=0,E=0,F=0,G=0;
    T x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;
    int triangleid=0;
    //Cannot be parallelized with this data structure, vector.insert could be used
    for(triangleid=0; triangleid<triangles.returnsize(); triangleid++)
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
        circumcentrex.push_back((D * E - B * F) / G);
        circumcentrey.push_back((A * F - C * E) / G);
    }
    cout<<"Circumcentre set ok..."<<endl;
}
template<typename T>
int triangulation<T>::Isthisintriangle(T pointx,T pointy)
{
    bool b1, b2, b3;
    T x1(0),x2(0),x3(0),y1(0),y2(0),y3(0);
    int triangleid(0);
    int foundtriangle(0);
    //Parallelize checking triangles
    #pragma omp parallel default(shared) private(triangleid,x1,x2,x3,y1,y2,y3,b1,b2,b3) //
    {
        //Divide for loop
        #pragma omp for schedule(static)
        for(triangleid=0; triangleid<=triangles.returnsize(); triangleid++)
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
            if((b1 == b2) && (b2 == b3)&&(triangleid<=triangles.returnsize()-1))foundtriangle=triangleid;
        }
    }
    if(triangleid==0)cout<<"Triangle not found..."<<endl;
    return(foundtriangle);
}
template<typename T>
void triangulation<T>::findtrianglearea()
{
    T x1=0,x2=0,x3=0,y1=0,y2=0,y3=0,result=0;
    int triangleid=0;
    //Cannot be parallelized with this data structure, vector.insert could be used along with i
    for(triangleid=0; triangleid<=triangles.returnsize(); triangleid++)
    {
        x1 = vertices.reachvx(triangles.reachtx(triangleid));
        y1 = vertices.reachvy(triangles.reachtx(triangleid));
        x2 = vertices.reachvx(triangles.reachty(triangleid));
        y2 = vertices.reachvy(triangles.reachty(triangleid));
        x3 = vertices.reachvx(triangles.reachtz(triangleid));
        y3 = vertices.reachvy(triangles.reachtz(triangleid));
        //T  result = (((x1 - x3) * (y2 - y3)) - ((x2 - x3) * (y1 - y3)));///2.0f;
        result = ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2) ))/2.0f;

        if(result<0)result = result*(-1); // NO NEGATIVE AREA ALLOWED :)
        triarea.push_back(result);
    }

    cout<<"Area vector generated..."<<endl;
}
template<typename T>
T triangulation<T>::linearintegrate()
{
    T x1=0,x2=0,x3=0,y1=0,y2=0,y3=0,result=0;
    int triangleid=0;
    //Parallelize linear integration
    #pragma omp parallel default(shared) shared(result) private(triangleid,x1,x2,x3,y1,y2,y3)
    {
        //Divide for loop
        #pragma omp for schedule(static)
        for(triangleid=0; triangleid<=triangles.returnsize(); triangleid++)
        {
            x1 = vertices.reachvx(triangles.reachtx(triangleid));
            y1 = vertices.reachvy(triangles.reachtx(triangleid));
            x2 = vertices.reachvx(triangles.reachty(triangleid));
            y2 = vertices.reachvy(triangles.reachty(triangleid));
            x3 = vertices.reachvx(triangles.reachtz(triangleid));
            y3 = vertices.reachvy(triangles.reachtz(triangleid));
            //cout<<triangleid<<" "<<x1<<" "<<x2<<" "<<x3<<" "<<y1<<" "<<y2<<" "<<y3<<endl;
            result = result + (f<T>(x1,y1) + f<T>(x2,y2) + f<T>(x3,y3)) * triarea[triangleid]/3.0;
        }
        #pragma omp barrier
    }
    cout<<"Linear integration complete"<<endl;
    return result;
}
template<typename T>
T triangulation<T>::constantintegrate()
{
    T result=0;
    int triangleid=0;
    // Parallelize constant integration
    #pragma omp parallel default(shared) shared(result) private(triangleid)
    {
        //Divide for loop
        #pragma omp for schedule(static)
        for(triangleid=0; triangleid<=triangles.returnsize(); triangleid++)
        {
            result = result + (f<T>(circumcentrex[triangleid],circumcentrey[triangleid]) * triarea[triangleid]);
        }
        #pragma omp barrier
    }
    cout<<"Constant integration complete"<<endl;
    return result;
}
#endif
