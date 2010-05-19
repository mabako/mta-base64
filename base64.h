#ifndef __BASE64_H
#define __BASE64_H

#include <string>

namespace base64
{
	const std::string decode( const std::string strInput );
	const std::string encode( const std::string strInput );
}

#endif