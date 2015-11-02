#ifndef L_SPARSE_SET
#define L_SPARSE_SET

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

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
