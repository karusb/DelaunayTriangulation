#include <vector>
#include <iostream>
#include <ostream>
using namespace std;
/** \brief
 *  vertex class: Holds 3 vectors for vector points x,y,z and its dimension
 * \param T type of the data
 *
 *
 *  Methods:
 *  T reachvi(int element1)                        Returns the point "i" for vertexid element1
 *  T reachvx(int element1)                        Returns the point "x" for vertexid element1
 *  T reachvy(int element1)                        Returns the point "y" for vertexid element1
 *  T reachvz(int element1)                        Returns the point "z" for vertexid element1
 *  int reachsize()                                Returns the size of "vx" hence vector size
 *  setvi(T value)                                 Inserts the value into vector vi for points "x" of the vertex
 *  setvx(T value)                                 Inserts the value into vector vx for points "x" of the vertex
 *  setvy(T value)                                 Inserts the value into vector vy for points "y" of the vertex
 *  setvz(T value)                                 Inserts the value into vector vz for points "z" of the vertex
 *  erasevi(int value)                             Deletes the value element in vector vi
 *  erasevx(int value)                             Deletes the value element in vector vx
 *  erasevy(int value)                             Deletes the value element in vector vy
 *  erasevz(int value)                             Deletes the value element in vector vz
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
    inline T reachvi(int element1)
    {
        return(vi[element1]);
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
    inline void setvi(T value)
    {
        vi.push_back(value);
    }
    inline void setvx(T value)
    {
        vx.push_back(value);
    }
    inline void setvy(T value)
    {
        vy.push_back(value);
    }
    inline void setvz(T value)
    {
        vz.push_back(value);
    }
    inline int reachsize()
    {
        return vx.size();
    }
    inline void erasevi(int value)
    {
        vi.erase(vi.begin()+value);
    }
    inline void erasevx(int value)
    {
        vx.erase(vx.begin()+value);
    }
    inline void erasevy(int value)
    {
        vy.erase(vy.begin()+value);
    }
    inline void erasevz(int value)
    {
        vz.erase(vz.begin()+value);
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
        vi.reserve(other.vx.size());
        vx.reserve(other.vx.size());
        vy.reserve(other.vy.size());
        vz.reserve(other.vz.size());
        vi = other.vi;
        vx = other.vx;
        vy = other.vy;
        vz = other.vz;
        dimension = other.dimension;
        //int wow=other.reachsize();

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
        while(it1!=c.vx.end())
        {

            if(c.vi.size()>0)out<<*it<<" ";
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
