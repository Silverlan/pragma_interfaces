#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__

#undef GetMessage

#include <boost/system/error_code.hpp>
#include <string>
#include <iostream>

class __declspec(dllimport) ErrorCode
{
protected:
	std::string m_message;
	int m_value;
	std::unique_ptr<boost::system::error_code> m_error;
public:
	ErrorCode();
	ErrorCode(const std::string &msg,unsigned int value);
	ErrorCode(const boost::system::error_code &err);
	ErrorCode(const ErrorCode &other);
	bool IsError() const;
	std::string GetMessage() const;
	int GetValue() const;
};

__declspec(dllimport) std::ostream &operator<<(std::ostream &out,const ErrorCode &err);

#endif