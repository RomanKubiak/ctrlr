#ifndef __L_SPARSE_SET__
#define __L_SPARSE_SET__

#include "CtrlrLuaManager.h"

class LSparseSet : public SparseSet<int>
{
	public:
		LSparseSet()
		{}
		LSparseSet(const SparseSet<int> &other) : SparseSet<int>(other)
		{}
		int get(int index);
		static void wrapForLua (lua_State *L);
};

#endif