#include "stdafx.h"
#include "LSparseSet.h"

int LSparseSet::get(int index)
{
	SparseSet<int> *s = dynamic_cast <SparseSet<int> *>(this);
	return ((*s)[index]);
}

void LSparseSet::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<SparseSet<int> >("JSparseSet")
		,
		class_<LSparseSet, bases<SparseSet<int> > >("SparseSet")
				.def(constructor<const SparseSet<int> &>())
				.def(constructor<>())
				.def("clear", &SparseSet<int>::clear)
				.def("isEmpty", &SparseSet<int>::isEmpty)
				.def("size", &SparseSet<int>::size)
				.def("contains", &SparseSet<int>::contains)
				.def("getNumRanges", &SparseSet<int>::getNumRanges)
				.def("getRange", &SparseSet<int>::getRange)
				.def("getTotalRange", &SparseSet<int>::getTotalRange)
				.def("addRange", &SparseSet<int>::addRange)
				.def("removeRange", &SparseSet<int>::removeRange)
				.def("invertRange", &SparseSet<int>::invertRange)
				.def("overlapsRange", &SparseSet<int>::overlapsRange)
				.def("containsRange", &SparseSet<int>::containsRange)
				.def("get", &LSparseSet::get)
	];
}