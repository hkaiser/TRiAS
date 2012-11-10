
#ifndef _date_h_
#define _date_h_





/*
 *
 *          Copyright (C) 1995, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1995. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */



// This class represents a particular date. Only dates on or after
// Sep 14, 1752 are permitted. The class provides for conversion to and from
// a string representation in one of the following forms, encoded by
// the {\tt DatePrintForm} enumeration, as illustrated below:
// \par\medskip{\tt \begin{tabular}{ll}
//            Date_American   &   October 17, 1992\\
//            Date_Terse      &   17-Oct-1992\\
//            Date_Numbers    &   10/17/92 \\
//            Date_European   &   17 October 1992\\
//            Date_EuroNumbers&   17/10/92\\
// \end{tabular}
// }\par\medskip
// \noindent
// By default, the Date class uses English names of the months and weekdays.
// The Date class supports some rudimentary internationalization. You
// can set the week-day and month names via static methods {\tt
// SetWeekdayNames}, {\tt SetMonthNames} and {\tt SetShortMonthNames}.
//
// As with other YACL classes, the methods that modify the Date object are
// declared virtual. They also provide notification support.


#ifdef __GNUC__
#pragma interface
#endif


#include "base/defs.h"
#include "base/string.h"

//[ Global
enum DatePrintForm { Date_American, Date_Terse, Date_Numbers,
                     Date_European, Date_EuroNumbers };
// {\tt DatePrintForm} is declared in global scope; it defines the different
// date formats.
//] Global

class YACL_BASE  CL_Date: public CL_Object {

public:

    //[ Local
    enum MonthEnum { InvalidMonth = 0, January, February, March, April,
                     May, June, July, August, September, October,
                     November, December};

    enum WeekdayEnum {InvalidDay = 0, Sunday, Monday, Tuesday, Wednesday,
                      Thursday, Friday, Saturday};
    //] Local
    
    //
    // ------------- Constructors and destructors ----------------------
    //

    CL_Date ();
    // Construct a Date object containing an invalid date.

    CL_Date (short year, short month, short day);
    // Construct the given date, assuming that the year is given as 1992,
    // not 92, and the month is indexed from 1 (e.g. January is month 1).

    CL_Date (short year, const char* month, short day);
    // Construct the given date, assuming the month specified as a
    // string, e.g., {\tt March}. Assume case-sensitive comparison and
    // completely-specified month names (e.g. {\tt Oct} is not allowed). The
    // month must match one of the month names currently used; the set of
    // month names can be changed by the {\tt SetMonthNames} method.

    CL_Date (const char* s);
    // Construct a date from the given string containing the
    // representation, in one of the forms {\tt Date_American}, {\tt
    // Date_Terse} or {\tt Date_Numbers}.
    

    CL_Date (const CL_Date&);

    ~CL_Date ();

    //
    // ---------------------- Access ----------------------------------
    //

    bool IsLegal () const;
    // Is this a legal date?
    
    short Year() const;
    // Return our year.

    MonthEnum Month () const;
    // Return our month.

    short Day () const;
    // Return our day of month.

    WeekdayEnum DayOfWeek () const;
    // Return our day of week as a {\tt WeekdayEnum}.
    
    CL_String WeekdayName () const {return DayName (DayOfWeek());}
    // Return the name of the weekday of this Date.
    
    short DaysInMonth () const;
    // Return the number of days in our month.
    
    CL_String PrintString (DatePrintForm form = Date_American) const;
    // Return a printable form of this object, according to the
    // parameter.

    bool IsLeapYear () const;
    // Tell if this Date is in a leap year.

    CL_Date NextWeekday (const char* weekday_name) const;
    // Return the date of the next weekday given. For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).NextWeekday ("Monday")
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 17, 1995.
    //
    // The method returns an invalid Date if {\tt weekday_name} is not one
    // of the currently-recognized week-day names (as specified by the {\tt
    // SetWeekdayNames} method).
    

    CL_Date PreviousWeekday (const char* weekday_name) const;
    // Return the date of the previous weekday given. For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).PreviousWeekday ("Monday")
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 10, 1995.
    
    CL_Date NextWeekday (WeekdayEnum weekday_num) const;
    // Return the date of the next weekday given. For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).NextWeekday (CL_Date::Monday)
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 17, 1995.

    CL_Date PreviousWeekday (WeekdayEnum weekday_num) const;
    // Return the date of the previous weekday given.  For example, since July
    // 11, 1995 was a Tuesday, the expression
    // \par\begin{verbatim}
    //          CL_Date (1995, 7, 11).PreviousWeekday (CL_Date::Monday)
    // \end{verbatim}
    // \par\noindent
    // returns a Date object containing July 10, 1995.
    

    //
    // --------------------- Comparison ------------------------------
    //

    bool operator<  (const CL_Date& d) const
        {return _days < d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is earlier than the parameter, and FALSE
    // otherwise.
    
    bool operator<= (const CL_Date& d) const
        {return _days <= d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is earlier than or equal to the parameter,
    // and FALSE otherwise.
    
    bool operator>  (const CL_Date& d) const
        {return _days > d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is later than the parameter, and FALSE
    // otherwise.

    bool operator>= (const CL_Date& d) const
        {return _days >= d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is later than or equal to the parameter, and
    // FALSE otherwise.

    bool operator== (const CL_Date& d) const
        {return _days == d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is equal to the parameter, and FALSE
    // otherwise.

    bool operator!= (const CL_Date& d) const
        {return _days != d._days ? TRUE : FALSE;};
    // Return TRUE if this Date is not equal to the parameter, and FALSE
    // otherwise.

    bool operator<  (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator<}.

    bool operator<= (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator<=}.

    bool operator>  (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator>}.

    bool operator>= (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator>=}.

    bool operator== (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator==}.

    bool operator!= (const CL_Object& obj) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // operator!=}.

    short Compare (const CL_Date&) const;
    // Return $-1$, 0 or $+1$ according to whether this Date is earlier
    // than, equal to or later than the parameter.

    short Compare (const CL_Object&) const;
    // Cast down the parameter to a Date and use the Date-specific {\tt
    // Compare} method. This overrides the inherited virtual method.

    bool IsBetween (const CL_Date& d1, const CL_Date& d2) const;
    // Return TRUE if this date is between the two given dates. The two
    // parameters need not be in ascending order.
    
    //
    // -------------------------- Modification ----------------------
    //

    // Assignment
    
    virtual void operator= (const CL_Date&);
    // Assign the given date to this object.

    virtual void operator= (const char*);
    // Assign our value from a string. The string must be in one of
    // the forms of Date_American, Date_Terse, or Date_Numbers, or
    // else must be six digits (characters) of the form yymmdd or
    // mmddyy. In the former three cases, the year can be either of
    // the form 92 or 1992.

    //
    // -------------------------- Date arithmetic -------------------
    //

    
    CL_Date  operator+  (short num_days) const;
    // Return the result of adding  {\tt num_days} days to this Date.

    virtual CL_Date& operator+= (short num_days);
    // Add  {\tt num_days} days to this Date. Return this Date.

    CL_Date  operator-  (short num_days) const;
    // Subtract {\tt num_days} days and return the result.

    virtual CL_Date& operator-= (short num_days);
    // Subtract {\tt num_days} days from this Date. Return this Date.

    long operator-   (const CL_Date& date) const;
    // Return the number of days between us and the given date (which
    // may be positive or negative).
    
    CL_Date AddMonths (short num_months) const;
    // Return the Date obtained by adding {\tt num_months} to this Date's
    // month. The parameter can be positive or negative.

    CL_Date AddYears (short num_years) const;
    // Return the Date obtained by adding {\tt num_years} to this Date's
    // year. The parameter can be positive or negative.

    //
    // --------------------- Static methods ---------------------------
    //

    static CL_Date Today ();
    // Return a Date with today's date in it.

    static CL_String DayName (WeekdayEnum weekday_num);
    // Return name of given weekday. For example, {\tt CL_Date::DayName
    // (CL_Date::Monday)} returns ``{\tt Monday}'' in the default English
    // setting. Returns the empty string if the parameter is invalid.

    static WeekdayEnum  DayNumber (const char* weekday_name);
    // Return the week-day with name {\tt weekday_name}. 

    static CL_String MonthName (short month_num);
    // Return month name of given month (1 = ``{\tt January},'' etc.).
    // Return the empty String for an invalid month number.

    static CL_String ShortMonthName (short month_num);
    // Return the short (3-character) month name of given month.
    // Return the empty string for an invalid month number. 

    static MonthEnum MonthNumber (const char* month_name);
    // Return the month with name {\tt month_name}. Return $-1$ for an
    // invalid month name.

    static bool IsLeapYear (short year);
    // Return TRUE if {\tt year} is a leap year, and FALSE otherwise.

    static short DaysInMonth  (short month, short year);
    // Return the number of days in the given month and year. For example,
    // {\tt CL_Date::DaysInMonth (2, 1996)} returns 29.
    
    static long ParseAndConvert (const char* date);
    // Validate the given string as representing a date, and return
    // either $-1$ if it's not a valid date, and a positive value otherwise.
    // (This return value can be used to construct a Date object.). The
    // string must be in one of
    // the forms of Date_American, Date_Terse, or Date_Numbers, or
    // else must be six digits (characters) of the form yymmdd or
    // mmddyy. In the former three cases, the year can be either of
    // the form 92 or 1992, and the month names can be mixed case. In the
    // case of six digits of the form yymmdd, the year must be 13 or
    // greater, indicating the year 1913 or later.


    static bool SetMonthNames (char* month_names[12]);
    // Set the names of the months to be used by the Date class. This is for
    // rudimentary support of internationalization. This method need be
    // called only once in an application. If it is not called, the English
    // versions of the month names are used.
    //
    // The method returns TRUE on success, FALSE if the parameter did not
    // have twelve non-null pointers.
    //
    // The implementation simply copies the
    // passed pointers into a local data structure; so the storage for the
    // character strings is still owned by the caller of this method.

    static bool SetShortMonthNames (char* month_names[12]);
    // Set the short (typically 3-character) names of the months to be used
    // by the Date class. This is for rudimentary support of
    // internationalization. This method need be
    // called only once in an application. If it is not called, the English
    // versions of the short month names are used.
    //
    // The method returns TRUE on success, FALSE if the parameter did not
    // have twelve non-null pointers.
    //
    // The implementation simply copies the
    // passed pointers into a local data structure; so the storage for the
    // character strings is still owned by the caller of this method.

    static bool SetWeekdayNames (char* day_names[7]);
    // Set the names of the week days to be used by the Date class. This is for
    // rudimentary support of internationalization. This method need be
    // called only once in an application. If it is not called, the English
    // versions of the week-day names are used.
    //
    // The method returns TRUE on success, FALSE if the parameter did not
    // have seven non-null pointers.
    //
    // The implementation simply copies the
    // passed pointers into a local data structure; so the storage for the
    // character strings is still owned by the caller of this method.

    
    // ----------------------- Storage and restoration ----------------
    
    CL_String AsString () const
        { return PrintString (Date_Numbers);};
    // Return a String that contains this Date's value in {\tt Date_Numbers}
    // form. This method overrides the method inherited from Object.


    void FromStream (istream& strm);
    // Overrides the method inherited from Object. The
    // implementation skips fill characters, and then collects slashes,
    // dashes, and alphabetic and numeric 
    // characters and attempts to parse the result as a date. If successful,
    // this date is modified; otherwise, the collected characters are put
    // back and this date becomes invalid.
    
    long StorableFormWidth () const;
    // Overrides the method inherited from Object.

    bool ReadFrom (const CL_Stream&);
    // Overrides the method inherited from Object.

    bool WriteTo  (CL_Stream&) const;
    // Overrides the method inherited from Object.


    // -------------------------- Assignment ------------------------
    

    virtual void operator= (const CL_Object&);
    // Overrides the method inherited from Object.

    // ------------------------ Basic methods ----------------------
    
    const char* ClassName() const { return "CL_Date";};
    // Overrides the method inherited from Object. Returns the
    // string ``{\tt CL_Date}.''
    
    CL_ClassId ClassId () const {return _CL_Date_CLASSID;};
    // Overrides the method inherited from Object.

    CL_Object* Clone() const {return new CL_Date (*this);};
    // Overrides the method inherited from Object.


    
protected:

    // The representation used is the number of days since Jan 1,
    // 1752??
    long _days;
    
    CL_Date (long num_days);
    
};




inline void CL_Date::operator= (const CL_Object& obj)
{
    if (CheckClassType (obj, "CL_Date::op= (CL_Object&)"))
        *this = (const CL_Date&) obj;
}



inline short CL_Date::Compare (const CL_Object& obj) const
{
    return !IsA(obj) ? (this < (CL_Date*) &obj ? -1 :  1) 
        : Compare ((const CL_Date&) obj);
}


inline bool CL_Date::IsLegal () const
{
    return _days > 0;
}

#endif
