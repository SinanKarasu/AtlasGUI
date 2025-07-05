
#include	"astream.h"
#include	"AtlasAST.h"

astream::astream():std::fstream(), binary(0), field_width(0){};
astream::astream( const char* a, std::ios::openmode mode ):std::fstream( a, mode ), binary(0), field_width(0){};
astream::astream(std::streambuf* sb) : binary(0), field_width(0) {
	this->init(sb);  // This is the correct way to assign a custom buffer
}
//astream::astream(std::streambuf* sb)
//: std::fstream(), binary(0), field_width(0) {
//	this->rdbuf(sb);
//}

void	astream::bin()			{ binary = 1; };
void	astream::reset()		{ binary = 0; };
			
void	astream::width( int &fw )	{ field_width = fw; std::fstream::width( fw ); };

astream	&operator<<( astream &s, const RWBitVec *x )
	{
		long	bit   = x->size() - 1;
		long	flag  = 1;

		// Strip leading zero's  [9.3.5 Paragraph 2]
		while ( bit >= 0  &&  ! (*x)[bit] )
			--bit;

		if ( s.binary ){
			
			s.std::fstream::width( 1 );
			
			while ( bit < (s.field_width-1) ){
				s.std::fstream::operator<<( ' ' );
				--s.field_width;
			}
			
			flag = ( s.field_width ? s.field_width-1 : bit );
			
			while ( (bit >= 0) && (flag >= 0) ){
			
				if ( bit > flag )
					s.std::fstream::operator<<( '#' );
				
				else if ( (*x)[bit] )
					s.std::fstream::operator<<( 1 );
					
				else
					s.std::fstream::operator<<( 0 );
				
				--flag;
				--bit;
			}
			
			s.reset();
		}else{
			long	value = 0;
		
			while ( bit >= 0 ){
			
				value = value << 1;
				if ( (*x)[bit] ) value |= 1;
				--bit;
			}

			s.std::fstream::operator<<( value );
		}
		return s;
	}
	
astream	&operator>>( astream &s, AST * a )
	{
		return a->operator>>( s );
	}
	
astream	&operator<<( astream &s, AST * a )
	{
		return a->operator<<( s );
	}

//sik fix this
astream& operator>>(astream& s, BitVec& b) {
	// Define how you want BitVec to be read from astream
	// For now, a stub to get it linking:
	return s;
}
