#include "BT_MatML_StringValidator.h"

using namespace bellshire;


bool StringValidator::ValidateString(
	::std::string input,
	::std::string Format,
	::std::string Delimiter,
	bool NewLineRemoval,
	::std::string* msg
)
{
	//Validate Data
	bool rtn = true;//default true;
	std::list<std::string> result;

	//remove newline characters for validation.
	if (NewLineRemoval)
		input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

	//Split up the input string into data items.
	if (!Delimiter.empty()) {
		boost::split(result, input, boost::is_any_of(Delimiter));
	}
	else {
		boost::split(result, input, boost::is_any_of(","));//default delimiter.
	}

	size_t n = result.size();

	//Iterate over the data items and validate.
	size_t i = 0;
	::std::list<::std::string>::iterator itor(result.begin());
	for (; itor != result.end(); ++itor, ++i) {
		if (Format == "float" && !isValid<float>(*itor)) 
		{
			msg->append(*itor + " ( data item " + ::std::to_string(i + 1) + " of "+::std::to_string(n)+") is NOT a float");
			rtn = false;
			break;
		}
		else if (Format == "integer" && !isValid<int>(*itor))
		{
			msg->append(*itor + " ( data item " + ::std::to_string(i + 1) + " of " + ::std::to_string(n) + ") is NOT a integer");
			rtn = false;
			break;
		}
		else if (Format == "string" && !isValid<::std::string>(*itor)) 
		{
			msg->append(*itor + " ( data item " + std::to_string(i + 1) + " of " + ::std::to_string(n) + ") is NOT a string");
			rtn = false;
			break;
		}
		else if (Format == "exponential" 
			&& (!isValid<float>(*itor)
			|| ((itor->find(std::string("e")) == std::string::npos) && (itor->find(std::string("E")) == std::string::npos))
				)
			)
		{
			msg->append(*itor + " ( data item " + ::std::to_string(i + 1) + " of " + ::std::to_string(n) + ") is NOT a exponential");
			rtn = false;
			break;
		}
	}

	if (rtn) msg->append("Validated " + ::std::to_string(n) + " data items");

	return rtn;
}


template<typename T>
bool StringValidator::isValid(const std::string& num)
{

	bool res = true;

	try {
		T tmp = boost::lexical_cast<T>(num);
	}
	catch (boost::bad_lexical_cast&) {
		res = false;
	}

	return(res);
}
