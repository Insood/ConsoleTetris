#pragma once

enum SpaceType
{
	EMPTY,
	LONG_PIECE =1,   // the XXXX

                     //       @	
	REGULAR_L  =2,   // the @@@

                     //     0
	REVERSE_L  =3,   // the 000

				     //     NN
	SQUARE     =4,   // the NN

                     // the ZZZ
	T_SHAPE    =5,   //      Z

	S_SHAPE    =6,   // the  QQ
	                 //     QQ

	Z_SHAPE    =7    // the ##
	                 //      ##
};  
