#ifndef STRINGSTREAM_H
#define STRINGSTREAM_H

//************Converting an Arbitrary Type to String**************
//Our first function template takes a value of an arbitrary type T,
//converts it to string, and writes the result to a user-supplied
//string called val. We use the stringstream::str() member function
//to obtain a copy of the stream's internal string:

#include <sstream>
#include <string>
using namespace std;

namespace bellshire{
template <class T>
void string_fmt(string & val, const T & t)
{
 ostringstream oss; // create a stream
 oss << t; // insert value to stream
 val=oss.str(); // extract string and copy
}

//In the following example, we use the string_fmt() function
//template to convert the value 10.76 to string and write the
//result to val:
//
//
//string val;
//string_fmt(val,10.76);


//************Converting from One Arbitrary Type to Another************
//Our second function template is called cast_stream().
//It converts a variable of type in_value to a variable
//of type out_type (in_value and out_value are template parameters):

template <class out_type, class in_value>
out_type cast_stream(const in_value & t)
{
 stringstream ss;
 ss << t; // first insert value to stream
 out_type result; // value will be converted to out_type
 ss >> result; // write value to result
 return result;
}
//In the following example, cast_stream() converts
//a string with the value "18.67" to double using cast_stream():
//
//string s="18.67";
//double d=cast_stream < double > (s); // assign 18.67 to d

}//namespace bellshire

#endif // STRINGSTREAM_H
