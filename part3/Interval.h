#ifndef INTERVAL_H
#define INTERVAL_H
#include <iostream>
using namespace std;
/** \brief
 * Interval class: holds 2 points of any type T
 * \param T type of the points
 * \param U type of the accuracy
 * \param lower first parameter of the interval
 * \param higher second parameter of the interval
 * \param offset offset between the first and second parameter
 *  Methods:
 *
 *  setlower()                             Sets lower limit of the interval or point 1
 *  sethigher()                            Sets higher limit of the interval or point 2
 *  setoffset()                            Sets the offset between the limits
 *  T getlower();                          Returns lower limit or point 1
 *  T gethigher();                         Return higher limit or point 2
 *  T getoffset();                         Returns the offset value
 *
 *
 *  *  Operators:
 *  >>  Input type : >>point1>>point2
 *  <<  Output type : <<point1<<point2
 *  +   Type: Interval or other std type U
 *  -   Type: Interval or other std type U
 *  *   Type: Interval or other std type U
 *  /   Type: Interval or other std type U
 *  +=  Type: Interval or other std type U
 *  -=  Type: Interval or other std type U
 *  *=  Type: Interval or other std type U
 *  /=  Type: Interval or other std type U
 *  ==  Type: Interval or other std type U
 *  !=  Type: Interval or other std type U
 *  <   Type: Interval or other std type U
 *  <=  Type: Interval or other std type U
 *  >   Type: Interval or other std type U
 *  >=  Type: Interval or other std type U
 *
 *  \author Baris Tanyeri
 */

template<typename T, typename U> // Typename T: Type for interval limits , Typename U: Offset and default type for operators
class Interval
{
public:
    //Constructors
    Interval();
    Interval(T = 0 ,T = 0 );
    Interval(T = 0 ,T = 0 ,U =0);
    virtual ~Interval();
    // Get methods
    T getdelta();
    T getlower();
    T gethigher();
    T getoffset();
    //Set methods
    void setlower(T newlower);
    void sethigher(T newhigher);
    void setoffset(T newoffset);
    //Operator Methods
    Interval<T,U>& operator=(Interval<T,U>& a);
    Interval<T,U>& operator+(Interval<T,U>& a);
    Interval<T,U>& operator*(Interval<T,U>& a);
    Interval<T,U>& operator-(Interval<T,U>& a);
    Interval<T,U>& operator/(Interval<T,U>& a);
    Interval<T,U>& operator+=(Interval<T,U>& a);
    Interval<T,U>& operator*=(Interval<T,U>& a);
    Interval<T,U>& operator-=(Interval<T,U>& a);
    Interval<T,U>& operator/=(Interval<T,U>& a);
    //Boolean requests for intervals
    bool operator<(Interval<T,U>& a);
    bool operator>(Interval<T,U>& a);
    bool operator<=(Interval<T,U>& a);
    bool operator>=(Interval<T,U>& a);
    bool operator==(Interval<T,U>& a);
    bool operator!=(Interval<T,U>& a);
    // Operator methods for type U
    Interval<T,U>& operator+(const U& additive);
    Interval<T,U>& operator*(const U& multiplicative);
    Interval<T,U>& operator-(const U& subtractive);
    Interval<T,U>& operator/(const U& dividible);
    Interval<T,U>& operator+=(const U& additive_eq);
    Interval<T,U>& operator*=(const U& multiplicative_eq);
    Interval<T,U>& operator-=(const U& subtractive_eq);
    Interval<T,U>& operator/=(const U& dividible_eq);

    // Boolean requests for U types
    bool operator<(const U& a);
    bool operator>(const U& a);
    bool operator<=(const U& a);
    bool operator>=(const U& a);
    bool operator==(const U& a);
    bool operator!=(const U& a);


    //Stream Methods
    friend istream& operator>> (istream& in, Interval<T,U> &c)   //In & Out stream operator definitions
    {
        return in>>c.lower>>c.higher;
    }
    friend ostream& operator<< (ostream& out, Interval<T,U> &c)
    {

        return(out<<c.lower<<" "<< c.higher<<endl);
    }



protected:
private:
    T lower;
    T higher;
    U offset;
};
// IMPLEMENTATIONS //
template<typename T, typename U>
Interval<T,U>::Interval()
{
    // Build a unity interval
    lower = 0;
    higher = 1;
    offset = 0;
}

template<typename T, typename U>
Interval<T,U>::Interval(T low,T high,U sett)
{
    // Build an interval with offset
    lower = low;
    higher = high;
    offset = sett;
}
template<typename T, typename U>
Interval<T,U>::Interval(T low,T high)
{
    // Build standard interval
    lower = low;
    higher = high;
    offset = 0;
}

template<typename T, typename U>
Interval<T,U>::~Interval()
{}
// get methods
template<typename T, typename U>
T Interval<T,U>::getdelta(){return T(std::max(lower,higher)-std::min(lower,higher));}
template<typename T, typename U>
T Interval<T,U>::getlower(){return T(lower);}
template<typename T, typename U>
T Interval<T,U>::gethigher(){return T(higher);}
template<typename T, typename U>
T Interval<T,U>::getoffset(){return T(offset);}
// set methods
template<typename T, typename U>
void Interval<T,U>::setlower(T newlower){lower = newlower;}
template<typename T, typename U>
void Interval<T,U>::sethigher(T newhigher){higher = newhigher;}
template<typename T, typename U>
void Interval<T,U>::setoffset(T newoffset){offset = newoffset;}

// OPERATOR IMPLEMENTATIONS
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator=(Interval<T,U>& a)
{
    if(this==&a) return(*this);
    if(higher !=a.higher || lower !=a.higher || offset !=a.offset)
    {
        higher =a.higher;
        lower = a.lower;
        offset = a.offset;
    }
    return(*this);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator+(Interval<T,U>& a)
{
        Interval<T,U> result = *this;
        result.lower = lower + a.lower;
        result.higher = higher + a.higher;
        result.offset = offset + a.offset;

    return (result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator+=(Interval<T,U>& a)
{

        lower = lower + a.lower;
        higher = higher + a.higher;
        offset = offset + a.offset;

    return (*this);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator-(Interval<T,U>& a)
{
        Interval<T,U> result = *this;
        result.lower = lower - a.lower;
        result.higher = higher - a.higher;
        result.offset = offset - a.offset;
    return(result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator-=(Interval<T,U>& a)
{

        lower = lower - a.lower;
        higher = higher - a.higher;
        offset = offset - a.offset;

    return (*this);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator*(Interval<T,U>& a)
{
        Interval<T,U> result = *this;
        result.lower = a.lower * lower;
        result.higher = a. higher * higher;
        result.offset = a.offset * offset;
    return(result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator*=(Interval<T,U>& a)
{

        lower = lower * a.lower;
        higher = higher * a.higher;
        offset = offset * a.offset;

    return (*this);

}

template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator/(Interval<T,U>& a)
{
        Interval<T,U> result = *this;

            result.lower = lower / a.lower;
            result.higher = higher / a.higher;
            result.offset = offset / a.offset;

        if(a.lower ==0)result.lower = lower;
        if(a.higher ==0)result.higher = higher;
        if(a.offset==0)result.offset = offset;
    return(result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator/=(Interval<T,U>& a)
{

        lower = lower / a.lower;
        higher = higher / a.higher;
        offset = offset / a.offset;

    return (*this);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator+(const U& a)
{
        Interval<T,U> result = *this;
        result.lower = lower +a;
        result.higher = higher + a;
        result.offset = offset + a;

    return (result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator+=(const U& a)
{

        lower = lower +a;
        higher = higher + a;
        offset = offset + a;

    return (*this);

}

template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator-(const U& a)
{
        Interval<T,U> result = *this;
        result.lower = lower -a;
        result.higher = higher - a;
        result.offset = offset - a;

    return (result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator-=(const U& a)
{

        lower = lower -a;
        higher = higher - a;
        offset = offset - a;

    return (*this);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator*(const U& a)
{
        Interval<T,U> result = *this;
        result.lower = lower * a;
        result.higher = higher * a;
        result.offset = offset * a;

    return (result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator*=(const U& a)
{

        lower = lower * a;
        higher = higher * a;
        offset = offset * a;

    return (*this);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator/(const U& a)
{
        Interval<T,U> result = *this;
        result.lower = lower / a;
        result.higher = higher / a;
        result.offset = offset / a;

    return (result);

}
template<typename T, typename U>
Interval<T,U>& Interval<T,U>::operator/=(const U& a)
{

        lower = lower /a;
        higher = higher / a;
        offset = offset / a;

    return (*this);

}
// BOOL RETURN METHODS for INTERVALS
template<typename T, typename U>
bool Interval<T,U>::operator<(Interval<T,U>& a)
{
    if(getdelta() < a.getdelta())return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator>(Interval<T,U>& a)
{
    if(getdelta() > a.getdelta())return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator>=(Interval<T,U>& a)
{
    if(getdelta() >= a.getdelta())return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator<=(Interval<T,U>& a)
{
    if(getdelta() <= a.getdelta())return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator==(Interval<T,U>& a)
{
    if(getdelta() == a.getdelta())return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator!=(Interval<T,U>& a)
{
    if(getdelta() != a.getdelta())return(true);
    else return(false);
}
// TYPE U BOOL IMPLEMENTATIONS
template<typename T, typename U>
bool Interval<T,U>::operator<(const U& a)
{
    if(getdelta() < a)return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator>(const U& a)
{
    if(getdelta() > a)return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator>=(const U& a)
{
    if(getdelta() >= a)return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator<=(const U& a)
{
    if(getdelta() <= a)return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator==(const U& a)
{
    if(getdelta() == a)return(true);
    else return(false);
}
template<typename T, typename U>
bool Interval<T,U>::operator!=(const U& a)
{
    if(getdelta() != a)return(true);
    else return(false);
}

#endif // INTERVAL_H
