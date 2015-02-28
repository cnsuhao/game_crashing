#ifndef UNEQUALSTAFF_H
#define UNEQUALSTAFF_H
#include "staff.h"
template <class T,class P,class K>
class UnequalStaff:public Staff<T,P>
{
    K US_Style;
public:
    K Style(){return US_Style;}
    UnequalStaff(K S):US_Style(S){}
};

#endif // STAFF_H
