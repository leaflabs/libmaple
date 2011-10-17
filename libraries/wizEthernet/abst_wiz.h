//abst_wiz.h

/*
* The purpose of this class is so that the lower level 
* wiz820io and higher level sockets can have an instance of each other
* without including wiz820io in socket and socket in wiz820io
*/

#ifndef __ABST_WIZ_H__
#define __ABST_WIZ_H__

class abst_wiz{

	public:
	abst_wiz(){};
	//override me!
	void socket_interrupt();
};

#endif
