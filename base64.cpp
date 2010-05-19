#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

namespace base64
{
	using namespace std;
	
	/* Decoding */
	static const char cd64[]="|***}rstuvwxyz{*******>?@ABCDEFGHIJKLMNOPQRSTUVW******XYZ[\\]^_`abcdefghijklmnopq";

	void decodeblock( unsigned char in[4], unsigned char out[3] )
	{   
		out[0] = (in[0] << 2 | in[1] >> 4);
		out[1] = (in[1] << 4 | in[2] >> 2);
		out[2] = (((in[2] << 6) & 0xc0) | in[3]);
	}

	const string decode( const string strInput )
	{
		unsigned char in[4], out[3];
		unsigned int len = strInput.length( );
		unsigned char blocklen = 0;
		stringstream ret;

		for( unsigned int c = 0; c < len; ++ c )
		{
			unsigned char v = strInput[c];
			if( v >= 43 && v <= 122 )
			{
				v = cd64[v-43];
				if( v > 0 )
					v = (unsigned char) (( v == '*' ) ? 0 : v - 61 );
				if( v > 0 )
					in[blocklen++] = (unsigned char) ( v - 1 );

				if( blocklen == 4 )
				{
					decodeblock( in, out );
					for( unsigned int o = 0; o < 3; ++ o )
					{
						ret << out[o];
						out[o] = 0;
					}
					blocklen = 0;
				}
			}
		}
		if( blocklen > 0 )
		{
			for( ; blocklen < 4; ++ blocklen )
				in[ blocklen ] = 0;

			decodeblock( in, out );

			for( unsigned int o = 0; o < 3; ++ o )
				ret << out[o];
		}
		return ret.str( );
	}

	/* Encoding */
	static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	void encodeblock( unsigned char in[3], unsigned char out[4], int len )
	{
		out[0] = cb64[ in[0] >> 2 ];
		out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
		out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
		out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
	}

	const string encode( const string strInput )
	{
		unsigned char in[3], out[4];
		unsigned int len = strInput.length( );
		unsigned char blocklen = 0;
		stringstream ret;

		for( unsigned char c = 0; c < len; ++ c )
		{
			in[ blocklen++ ] = strInput[ c ];
			if( blocklen == 3 )
			{
				encodeblock( in, out, blocklen );
				for( unsigned int o = 0; o < 4; ++ o )
				{
					ret << out[o];
					out[o] = 0;
				}
				blocklen = 0;
			}
		}

		if( blocklen > 0 )
		{
			for( unsigned char c = blocklen; c < 3; ++ c )
				in[ c ] = 0;

			encodeblock( in, out, blocklen );

			for( unsigned int o = 0; o < 4; ++ o )
				ret << out[o];
		}

		return ret.str( );
	}
}
