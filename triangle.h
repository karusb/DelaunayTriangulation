#include <vector>
#include <iostream>
#include <ostream>
#ifndef TRIANGLE_H
#define TRIANGLE_H
/** \brief
 *  triangle class: Holds 3 vectors for vector points x,y,z and its dimension.Holds 2 dimensional vector for each triangle for its attributes and its size attrbsize.
 * \param T type of the data
 *
 *
 *  Methods:
 *
 *  T reachtx(int triangleid)                        Returns the vertexid "x" for triangleid
 *  T reachty(int triangleid)                        Returns the vertexid "y" for triangleid
 *  T reachtz(int triangleid)                        Returns the vertexid "z" for triangleid
 *  T reachattrb(int triangleid,int attribute)       Returns the attribute value of the triangle triangleid's attribute
 *  settx(int value)                                 Inserts the value into vector tx for points "x" of the triangle
 *  setty(int value)                                 Inserts the value into vector ty for points "y" of the triangle
 *  settz(int value)                                 Inserts the value into vector tz for points "z" of the triangle
 *  setattrb(vector<T> value)                        Inserts a vector (attributes of 1 triangle) as attributes of the triangle
 *  void setsize(unsigned int visize)                Allocates memory for visize triangles / Should be called before streaming elements
 *  void setdim(unsigned int dim)                    Sets the dimension of the object 2 for 2D 3 for 3D.
 *
 *  Operators:                                       ti: triangleid's tx:vertex 1 ty:vertex 2 tz:vertex3 atrs:attributes // for all triangles
 *  >>  Input type : ti>>tx>>ty>>tz>>atrs
 *  <<  Output type : <<ti<<" "<<tx<<" "<<ty<<" "<<tz<<" "<<atrs[ti]
 *
 * \author Baris Tanyeri
 */

template<typename T>
class triangle
{
public:
    /** Default constructor */
    triangle<T>() {}
    /** Default destructor */
    virtual ~triangle<T> () {}
    inline T reachtx(int triangleid)
    {
        return(tx[triangleid]);
    }
    inline T reachty(int triangleid)
    {
        return(ty[triangleid]);
    }
    inline T reachtz(int triangleid)
    {
        return(tz[triangleid]);
    }
    inline T reachattrb(int triangleid,int attribute)
    {
        return(attrs[triangleid][attribute]);
    }
    inline int returnsize()
    {
        return(ti.size());
    }
    inline void settx(int value)
    {
        tx.push_back(value);
    }
    inline void setty(int value)
    {
        ty.push_back(value);
    }
    inline void settz(int value)
    {
        tz.push_back(value);
    }
    inline void setattrb(vector<T> value)
    {
        attrs.push_back(value);
    }
    /** Copy constructor
     *  \param other Object to copy from
     */
    triangle<T>(const triangle& other) {
    *this = other;}
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    inline triangle& operator=(const triangle& other)
    {
        return *this;
    }
    void setsize(int visize)
    {
        ti.reserve(visize);
        tx.reserve(visize);
        ty.reserve(visize);
        tz.reserve(visize);
    }
    inline void setdim(unsigned int dim)
    {
        dimension = dim;
    }
    void setattrbsize(unsigned int atsize)
    {
        if(atsize!=0)attrs.reserve(atsize); // No use reserving 0
        attrbsize = atsize;
    }
    friend istream& operator>>(istream& in, triangle<T> &c)
    {

        T vitmp,vxtmp,vytmp,vztmp;
        T attrb;
        vector<T> attrtype;
        if(c.attrbsize!=0)attrtype.reserve(c.attrbsize);

        in>>vitmp>>vxtmp>>vytmp>>vztmp;
        c.ti.push_back(vitmp);
        c.tx.push_back(vxtmp);
        c.ty.push_back(vytmp);
        c.tz.push_back(vztmp);
        int curpos=0;
        if(c.attrbsize!=0)
        {
            while(curpos<=c.attrbsize)
            {
                in>>attrb;
                attrtype.push_back(attrb); // Push attributes of triangle
                curpos++;
            }
            c.attrs.push_back(attrtype); //push to triangle id
        }






        //in>>c.vi.push_back>>c.vx.push_back>>c.vy.push_back>>c.vz.push_back;
        return(in);
    }   //In & Out stream operator definitions

    friend ostream& operator<<(ostream& out, triangle &c)
    {
        vector<float>::iterator it  = c.ti.begin();
        vector<float>::iterator it1 = c.tx.begin();
        vector<float>::iterator it2 = c.ty.begin();
        vector<float>::iterator it3 = c.tz.begin();
        vector<float>::iterator atrbit;
        vector<vector<float> >::iterator atrbig;

        int id=0;
        while(it!=c.ti.end())
        {
            out<<*it<<" ";
            out<<*it1<<" ";
            out<<*it2<<" ";

            if(c.dimension==2 && c.attrbsize==0)out<<endl;
            if(c.dimension==3)
            {
                out<<*it3<<" ";
            }

            if(c.attrbsize==0)out<<endl;
            if(c.attrbsize!=0)
            {
                atrbig = c.attrs.begin();
                atrbit = c.attrs[id].begin();

                for(int i =0; i<=c.attrbsize; ++i)
                {
                    out<<c.attrs[id][i]<<" ";
                }
            }
            it++;
            it1++;
            it2++;
            it3++;
            id++;
            atrbig++;
            out<<endl;
        }

        return(out);
    }
protected:
private:
    vector<T> ti;
    vector<T> tx;
    vector<T> ty;
    vector<T> tz;

    vector<vector<T> > attrs;
    int dimension;
    int attrbsize;
};
#endif
