#include <vector>
#include <iostream>
#include <ostream>
#ifndef VERTEX_H
#define VERTEX_H
using namespace std;
/** \brief
 *  vertex class: Holds 3 vectors for vector points x,y,z and its dimension
 * \param T type of the data
 *
 *
 *  Methods:
 *
 *  T reachvx(int element1)                        Returns the point "x" for vertexid element1
 *  T reachvy(int element1)                        Returns the point "y" for vertexid element1
 *  T reachvz(int element1)                        Returns the point "z" for vertexid element1
 *  setvx(int value)                               Inserts the value into vector vx for points "x" of the vertex
 *  setvy(int value)                               Inserts the value into vector vy for points "y" of the vertex
 *  setvz(int value)                               Inserts the value into vector vz for points "z" of the vertex
 *  void setsize(unsigned int visize)              Allocates memory for visize vertices / Should be called before streaming elements
 *  void setdim(unsigned int dim)                  Sets the dimension of the object 2 for 2D 3 for 3D.
 *
 *  Operators:                                       vi: vertexid's vx: x vy: y  vz:z  // for all vertices
 *  >>  Input type : vi>>vx>>vy>>vz
 *  <<  Output type : <<vi<<" "<<vx<<" "<<vy<<" "<<vz
 *
 * \author Baris Tanyeri
 */

template<typename T>
class vertex
{
public:
    /** Default constructor */
    vertex<T>()
    {
    }
    inline T reachvx(int element1)
    {
        return(vx[element1]);
    }
    inline T reachvy(int element1)
    {
        return(vy[element1]);
    }
    inline T reachvz(int element1)
    {
        return(vz[element1]);
    }
    inline void setvx(int value)
    {
        vx.push_back(value);
    }
    inline void setvy(int value)
    {
        vy.push_back(value);
    }
    inline void setvz(int value)
    {
        vz.push_back(value);
    }
    /** Default destructor */
    virtual ~vertex<T>()
    {
        //delete dimension;
        //delete vi;
        //delete vx;
        //delete vy;
    }
    /** Copy constructor
     *  \param other Object to copy from
     */
    vertex<T>(const vertex& other) {
    *this = other;
    }
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    vertex& operator=(const vertex& other)
    {
        return *this;
    }
    void setsize(unsigned int visize)
    {
        vi.reserve(visize);
        vx.reserve(visize);
        vy.reserve(visize);
        vz.reserve(visize);
    }
    void setdim(unsigned int dim)
    {
        dimension = dim;
    }

    friend istream& operator>>(istream& in, vertex<T> &c)
    {

        T vitmp,vxtmp,vytmp,vztmp;
        in>>vitmp>>vxtmp>>vytmp;
        if(c.dimension == 3)
        {
            in>>vztmp;
        }
        c.vi.push_back(vitmp);
        c.vx.push_back(vxtmp);
        c.vy.push_back(vytmp);
        if(c.dimension == 3)
        {
            c.vz.push_back(vztmp);
        }

        return(in);
    }   //In & Out stream operator definitions
    friend ostream& operator<<(ostream& out, vertex &c)
    {
        vector<float>::iterator it  = (c.vi.begin());
        vector<float>::iterator it1 = c.vx.begin();
        vector<float>::iterator it2 = c.vy.begin();
        vector<float>::iterator it3 = c.vz.begin();
        while(it!=c.vi.end())
        {

            out<<*it<<" ";
            out<<*it1<<" ";
            out<<*it2<<" ";
            if(c.dimension==2)out<<endl;

            if(c.dimension==3)
            {
                out<<*it3<<" "<<endl;
            }
            it++;
            it1++;
            it2++;
            it3++;
        }
        return(out);
    }
protected:
private:
    int dimension;
    vector<T> vi;
    vector<T> vx;
    vector<T> vy;
    vector<T> vz;

};
#endif
