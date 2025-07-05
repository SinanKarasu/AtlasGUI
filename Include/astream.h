#pragma once

#include	<iostream>
#include	<iomanip>
#include	"Std.h"

#include	"ASTBase.h"

class	astream : public std::fstream {
		friend std::fstream	&operator>>( std::fstream&, astream& );
		friend std::fstream	&operator<<( std::fstream&, const astream& );
		
		public:
			astream();
			//astream( const char* a, int x );
	astream(const char* filename, std::ios::openmode mode);
	astream(std::streambuf* sb);  // << new one
			void	bin();
			void	reset();
			void	width( int &fw );
			
			int	binary;
			int	field_width;
	};

astream		&operator<<( astream &s, const RWBitVec *x );

astream		&operator>>( astream &s, AST *a );
astream		&operator<<( astream &s, AST *a );

// dummied up, so it will link
astream &operator>>(astream &s, BitVec &vec);

