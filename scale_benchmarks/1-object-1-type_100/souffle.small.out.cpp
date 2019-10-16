
#include "souffle/CompiledSouffle.h"
#include <mutex>
#include "souffle/Explain.h"

extern "C" {
}

namespace souffle {
using namespace ram;
struct t_btree_3__0_1_2__1__7 {
using t_tuple = Tuple<RamDomain, 3>;
struct updater_t_btree_3__0_1_2__1__7 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[1] = new_t[1];
old_t[2] = new_t[2];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0>, updater_t_btree_3__0_1_2__1__7>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[3];
std::copy(ramDomain, ramDomain + 3, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2) {
RamDomain data[3] = {a0,a1,a2};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_3__0_1_2__1__7& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 3 direct b-tree index [0,1,2]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31 {
using t_tuple = Tuple<RamDomain, 5>;
struct updater_t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] = new_t[3];
old_t[4] = new_t[4];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,4,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<0,2,1,3,4>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,2,1>, updater_t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31>;
t_ind_1 ind_1;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
ind_1.insert(t, h.hints_1);
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31& other) {
ind_0.insertAll(other.ind_0);
ind_1.insertAll(other.ind_1);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_1::iterator> equalRange_5(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_5(const t_tuple& t) const {
context h;
return equalRange_5(t, h);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_1::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_1.find(t, h.hints_1);
auto fin = ind_1.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_1::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,1,2,4,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
const auto& stats_1 = ind_1.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,2,1,3,4]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_1.inserts.getHits() << "/" << stats_1.inserts.getMisses() << "/" << stats_1.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_1.contains.getHits() << "/" << stats_1.contains.getMisses() << "/" << stats_1.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_1.lower_bound.getHits() << "/" << stats_1.lower_bound.getMisses() << "/" << stats_1.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_1.upper_bound.getHits() << "/" << stats_1.upper_bound.getMisses() << "/" << stats_1.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255 {
using t_tuple = Tuple<RamDomain, 8>;
struct updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[6] = new_t[6];
old_t[7] = new_t[7];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<2,3,5,0,1,4,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<2,3,5,0,1,4>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<1,2,5,3,0,4,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,2,5,3,0,4>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_1 ind_1;
using t_ind_2 = btree_set<t_tuple, index_utils::comparator<0,2,5,1,3,4,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,2,5,1,3,4>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_2 ind_2;
using t_ind_3 = btree_set<t_tuple, index_utils::comparator<0,1,4,5,2,3,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,4,5,2,3>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_3 ind_3;
using t_ind_4 = btree_set<t_tuple, index_utils::comparator<0,2,4,5,1,3,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,2,4,5,1,3>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_4 ind_4;
using t_ind_5 = btree_set<t_tuple, index_utils::comparator<1,2,4,5,0,3,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,2,4,5,0,3>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_5 ind_5;
using t_ind_6 = btree_set<t_tuple, index_utils::comparator<0,2,4,1,5,3,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,2,4,1,5,3>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_6 ind_6;
using t_ind_7 = btree_set<t_tuple, index_utils::comparator<0,3,4,5,1,2,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,3,4,5,1,2>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_7 ind_7;
using t_ind_8 = btree_set<t_tuple, index_utils::comparator<1,3,4,5,0,2,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,3,4,5,0,2>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_8 ind_8;
using t_ind_9 = btree_set<t_tuple, index_utils::comparator<0,3,4,1,5,2,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,3,4,1,5,2>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_9 ind_9;
using t_ind_10 = btree_set<t_tuple, index_utils::comparator<0,2,3,4,5,1,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,2,3,4,5,1>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_10 ind_10;
using t_ind_11 = btree_set<t_tuple, index_utils::comparator<1,2,4,3,5,0,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,2,4,3,5,0>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_11 ind_11;
using t_ind_12 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4,5,7,6>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2,3,4,5>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_12 ind_12;
using t_ind_13 = btree_set<t_tuple, index_utils::comparator<0,1,3,5,2,4,6,7>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,3,5,2,4>, updater_t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>;
t_ind_13 ind_13;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
t_ind_1::operation_hints hints_1;
t_ind_2::operation_hints hints_2;
t_ind_3::operation_hints hints_3;
t_ind_4::operation_hints hints_4;
t_ind_5::operation_hints hints_5;
t_ind_6::operation_hints hints_6;
t_ind_7::operation_hints hints_7;
t_ind_8::operation_hints hints_8;
t_ind_9::operation_hints hints_9;
t_ind_10::operation_hints hints_10;
t_ind_11::operation_hints hints_11;
t_ind_12::operation_hints hints_12;
t_ind_13::operation_hints hints_13;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
ind_1.insert(t, h.hints_1);
ind_2.insert(t, h.hints_2);
ind_3.insert(t, h.hints_3);
ind_4.insert(t, h.hints_4);
ind_5.insert(t, h.hints_5);
ind_6.insert(t, h.hints_6);
ind_7.insert(t, h.hints_7);
ind_8.insert(t, h.hints_8);
ind_9.insert(t, h.hints_9);
ind_10.insert(t, h.hints_10);
ind_11.insert(t, h.hints_11);
ind_12.insert(t, h.hints_12);
ind_13.insert(t, h.hints_13);
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[8];
std::copy(ramDomain, ramDomain + 8, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4,RamDomain a5,RamDomain a6,RamDomain a7) {
RamDomain data[8] = {a0,a1,a2,a3,a4,a5,a6,a7};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255& other) {
ind_0.insertAll(other.ind_0);
ind_1.insertAll(other.ind_1);
ind_2.insertAll(other.ind_2);
ind_3.insertAll(other.ind_3);
ind_4.insertAll(other.ind_4);
ind_5.insertAll(other.ind_5);
ind_6.insertAll(other.ind_6);
ind_7.insertAll(other.ind_7);
ind_8.insertAll(other.ind_8);
ind_9.insertAll(other.ind_9);
ind_10.insertAll(other.ind_10);
ind_11.insertAll(other.ind_11);
ind_12.insertAll(other.ind_12);
ind_13.insertAll(other.ind_13);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_12::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_12.lower_bound(low, h.hints_12), ind_12.upper_bound(high, h.hints_12));
}
range<t_ind_12::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_10::iterator> equalRange_13(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_10.lower_bound(low, h.hints_10), ind_10.upper_bound(high, h.hints_10));
}
range<t_ind_10::iterator> equalRange_13(const t_tuple& t) const {
context h;
return equalRange_13(t, h);
}
range<t_ind_12::iterator> equalRange_15(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_12.lower_bound(low, h.hints_12), ind_12.upper_bound(high, h.hints_12));
}
range<t_ind_12::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
range<t_ind_6::iterator> equalRange_21(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_6.lower_bound(low, h.hints_6), ind_6.upper_bound(high, h.hints_6));
}
range<t_ind_6::iterator> equalRange_21(const t_tuple& t) const {
context h;
return equalRange_21(t, h);
}
range<t_ind_11::iterator> equalRange_22(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_11.lower_bound(low, h.hints_11), ind_11.upper_bound(high, h.hints_11));
}
range<t_ind_11::iterator> equalRange_22(const t_tuple& t) const {
context h;
return equalRange_22(t, h);
}
range<t_ind_6::iterator> equalRange_23(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_6.lower_bound(low, h.hints_6), ind_6.upper_bound(high, h.hints_6));
}
range<t_ind_6::iterator> equalRange_23(const t_tuple& t) const {
context h;
return equalRange_23(t, h);
}
range<t_ind_9::iterator> equalRange_25(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_9.lower_bound(low, h.hints_9), ind_9.upper_bound(high, h.hints_9));
}
range<t_ind_9::iterator> equalRange_25(const t_tuple& t) const {
context h;
return equalRange_25(t, h);
}
range<t_ind_8::iterator> equalRange_26(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_8.lower_bound(low, h.hints_8), ind_8.upper_bound(high, h.hints_8));
}
range<t_ind_8::iterator> equalRange_26(const t_tuple& t) const {
context h;
return equalRange_26(t, h);
}
range<t_ind_9::iterator> equalRange_27(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_9.lower_bound(low, h.hints_9), ind_9.upper_bound(high, h.hints_9));
}
range<t_ind_9::iterator> equalRange_27(const t_tuple& t) const {
context h;
return equalRange_27(t, h);
}
range<t_ind_10::iterator> equalRange_29(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_10.lower_bound(low, h.hints_10), ind_10.upper_bound(high, h.hints_10));
}
range<t_ind_10::iterator> equalRange_29(const t_tuple& t) const {
context h;
return equalRange_29(t, h);
}
range<t_ind_11::iterator> equalRange_30(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_11.lower_bound(low, h.hints_11), ind_11.upper_bound(high, h.hints_11));
}
range<t_ind_11::iterator> equalRange_30(const t_tuple& t) const {
context h;
return equalRange_30(t, h);
}
range<t_ind_12::iterator> equalRange_31(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[5] = MIN_RAM_DOMAIN;
high[5] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_12.lower_bound(low, h.hints_12), ind_12.upper_bound(high, h.hints_12));
}
range<t_ind_12::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
range<t_ind_2::iterator> equalRange_37(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_37(const t_tuple& t) const {
context h;
return equalRange_37(t, h);
}
range<t_ind_1::iterator> equalRange_38(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_38(const t_tuple& t) const {
context h;
return equalRange_38(t, h);
}
range<t_ind_2::iterator> equalRange_39(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_39(const t_tuple& t) const {
context h;
return equalRange_39(t, h);
}
range<t_ind_13::iterator> equalRange_43(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_13.lower_bound(low, h.hints_13), ind_13.upper_bound(high, h.hints_13));
}
range<t_ind_13::iterator> equalRange_43(const t_tuple& t) const {
context h;
return equalRange_43(t, h);
}
range<t_ind_0::iterator> equalRange_44(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_44(const t_tuple& t) const {
context h;
return equalRange_44(t, h);
}
range<t_ind_0::iterator> equalRange_45(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_45(const t_tuple& t) const {
context h;
return equalRange_45(t, h);
}
range<t_ind_1::iterator> equalRange_46(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_46(const t_tuple& t) const {
context h;
return equalRange_46(t, h);
}
range<t_ind_2::iterator> equalRange_47(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_2.lower_bound(low, h.hints_2), ind_2.upper_bound(high, h.hints_2));
}
range<t_ind_2::iterator> equalRange_47(const t_tuple& t) const {
context h;
return equalRange_47(t, h);
}
range<t_ind_3::iterator> equalRange_51(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_3.lower_bound(low, h.hints_3), ind_3.upper_bound(high, h.hints_3));
}
range<t_ind_3::iterator> equalRange_51(const t_tuple& t) const {
context h;
return equalRange_51(t, h);
}
range<t_ind_4::iterator> equalRange_53(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_4.lower_bound(low, h.hints_4), ind_4.upper_bound(high, h.hints_4));
}
range<t_ind_4::iterator> equalRange_53(const t_tuple& t) const {
context h;
return equalRange_53(t, h);
}
range<t_ind_5::iterator> equalRange_54(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_5.lower_bound(low, h.hints_5), ind_5.upper_bound(high, h.hints_5));
}
range<t_ind_5::iterator> equalRange_54(const t_tuple& t) const {
context h;
return equalRange_54(t, h);
}
range<t_ind_6::iterator> equalRange_55(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_6.lower_bound(low, h.hints_6), ind_6.upper_bound(high, h.hints_6));
}
range<t_ind_6::iterator> equalRange_55(const t_tuple& t) const {
context h;
return equalRange_55(t, h);
}
range<t_ind_7::iterator> equalRange_57(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_7.lower_bound(low, h.hints_7), ind_7.upper_bound(high, h.hints_7));
}
range<t_ind_7::iterator> equalRange_57(const t_tuple& t) const {
context h;
return equalRange_57(t, h);
}
range<t_ind_8::iterator> equalRange_58(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_8.lower_bound(low, h.hints_8), ind_8.upper_bound(high, h.hints_8));
}
range<t_ind_8::iterator> equalRange_58(const t_tuple& t) const {
context h;
return equalRange_58(t, h);
}
range<t_ind_9::iterator> equalRange_59(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_9.lower_bound(low, h.hints_9), ind_9.upper_bound(high, h.hints_9));
}
range<t_ind_9::iterator> equalRange_59(const t_tuple& t) const {
context h;
return equalRange_59(t, h);
}
range<t_ind_10::iterator> equalRange_61(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_10.lower_bound(low, h.hints_10), ind_10.upper_bound(high, h.hints_10));
}
range<t_ind_10::iterator> equalRange_61(const t_tuple& t) const {
context h;
return equalRange_61(t, h);
}
range<t_ind_11::iterator> equalRange_62(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_11.lower_bound(low, h.hints_11), ind_11.upper_bound(high, h.hints_11));
}
range<t_ind_11::iterator> equalRange_62(const t_tuple& t) const {
context h;
return equalRange_62(t, h);
}
range<t_ind_12::iterator> equalRange_63(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[6] = MIN_RAM_DOMAIN;
high[6] = MAX_RAM_DOMAIN;
low[7] = MIN_RAM_DOMAIN;
high[7] = MAX_RAM_DOMAIN;
return make_range(ind_12.lower_bound(low, h.hints_12), ind_12.upper_bound(high, h.hints_12));
}
range<t_ind_12::iterator> equalRange_63(const t_tuple& t) const {
context h;
return equalRange_63(t, h);
}
range<t_ind_13::iterator> equalRange_255(const t_tuple& t, context& h) const {
auto pos = ind_13.find(t, h.hints_13);
auto fin = ind_13.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_13::iterator> equalRange_255(const t_tuple& t) const {
context h;
return equalRange_255(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
ind_1.clear();
ind_2.clear();
ind_3.clear();
ind_4.clear();
ind_5.clear();
ind_6.clear();
ind_7.clear();
ind_8.clear();
ind_9.clear();
ind_10.clear();
ind_11.clear();
ind_12.clear();
ind_13.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [2,3,5,0,1,4,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
const auto& stats_1 = ind_1.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [1,2,5,3,0,4,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_1.inserts.getHits() << "/" << stats_1.inserts.getMisses() << "/" << stats_1.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_1.contains.getHits() << "/" << stats_1.contains.getMisses() << "/" << stats_1.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_1.lower_bound.getHits() << "/" << stats_1.lower_bound.getMisses() << "/" << stats_1.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_1.upper_bound.getHits() << "/" << stats_1.upper_bound.getMisses() << "/" << stats_1.upper_bound.getAccesses() << "\n";
const auto& stats_2 = ind_2.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,2,5,1,3,4,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_2.inserts.getHits() << "/" << stats_2.inserts.getMisses() << "/" << stats_2.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_2.contains.getHits() << "/" << stats_2.contains.getMisses() << "/" << stats_2.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_2.lower_bound.getHits() << "/" << stats_2.lower_bound.getMisses() << "/" << stats_2.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_2.upper_bound.getHits() << "/" << stats_2.upper_bound.getMisses() << "/" << stats_2.upper_bound.getAccesses() << "\n";
const auto& stats_3 = ind_3.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,1,4,5,2,3,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_3.inserts.getHits() << "/" << stats_3.inserts.getMisses() << "/" << stats_3.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_3.contains.getHits() << "/" << stats_3.contains.getMisses() << "/" << stats_3.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_3.lower_bound.getHits() << "/" << stats_3.lower_bound.getMisses() << "/" << stats_3.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_3.upper_bound.getHits() << "/" << stats_3.upper_bound.getMisses() << "/" << stats_3.upper_bound.getAccesses() << "\n";
const auto& stats_4 = ind_4.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,2,4,5,1,3,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_4.inserts.getHits() << "/" << stats_4.inserts.getMisses() << "/" << stats_4.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_4.contains.getHits() << "/" << stats_4.contains.getMisses() << "/" << stats_4.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_4.lower_bound.getHits() << "/" << stats_4.lower_bound.getMisses() << "/" << stats_4.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_4.upper_bound.getHits() << "/" << stats_4.upper_bound.getMisses() << "/" << stats_4.upper_bound.getAccesses() << "\n";
const auto& stats_5 = ind_5.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [1,2,4,5,0,3,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_5.inserts.getHits() << "/" << stats_5.inserts.getMisses() << "/" << stats_5.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_5.contains.getHits() << "/" << stats_5.contains.getMisses() << "/" << stats_5.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_5.lower_bound.getHits() << "/" << stats_5.lower_bound.getMisses() << "/" << stats_5.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_5.upper_bound.getHits() << "/" << stats_5.upper_bound.getMisses() << "/" << stats_5.upper_bound.getAccesses() << "\n";
const auto& stats_6 = ind_6.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,2,4,1,5,3,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_6.inserts.getHits() << "/" << stats_6.inserts.getMisses() << "/" << stats_6.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_6.contains.getHits() << "/" << stats_6.contains.getMisses() << "/" << stats_6.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_6.lower_bound.getHits() << "/" << stats_6.lower_bound.getMisses() << "/" << stats_6.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_6.upper_bound.getHits() << "/" << stats_6.upper_bound.getMisses() << "/" << stats_6.upper_bound.getAccesses() << "\n";
const auto& stats_7 = ind_7.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,3,4,5,1,2,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_7.inserts.getHits() << "/" << stats_7.inserts.getMisses() << "/" << stats_7.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_7.contains.getHits() << "/" << stats_7.contains.getMisses() << "/" << stats_7.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_7.lower_bound.getHits() << "/" << stats_7.lower_bound.getMisses() << "/" << stats_7.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_7.upper_bound.getHits() << "/" << stats_7.upper_bound.getMisses() << "/" << stats_7.upper_bound.getAccesses() << "\n";
const auto& stats_8 = ind_8.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [1,3,4,5,0,2,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_8.inserts.getHits() << "/" << stats_8.inserts.getMisses() << "/" << stats_8.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_8.contains.getHits() << "/" << stats_8.contains.getMisses() << "/" << stats_8.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_8.lower_bound.getHits() << "/" << stats_8.lower_bound.getMisses() << "/" << stats_8.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_8.upper_bound.getHits() << "/" << stats_8.upper_bound.getMisses() << "/" << stats_8.upper_bound.getAccesses() << "\n";
const auto& stats_9 = ind_9.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,3,4,1,5,2,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_9.inserts.getHits() << "/" << stats_9.inserts.getMisses() << "/" << stats_9.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_9.contains.getHits() << "/" << stats_9.contains.getMisses() << "/" << stats_9.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_9.lower_bound.getHits() << "/" << stats_9.lower_bound.getMisses() << "/" << stats_9.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_9.upper_bound.getHits() << "/" << stats_9.upper_bound.getMisses() << "/" << stats_9.upper_bound.getAccesses() << "\n";
const auto& stats_10 = ind_10.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,2,3,4,5,1,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_10.inserts.getHits() << "/" << stats_10.inserts.getMisses() << "/" << stats_10.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_10.contains.getHits() << "/" << stats_10.contains.getMisses() << "/" << stats_10.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_10.lower_bound.getHits() << "/" << stats_10.lower_bound.getMisses() << "/" << stats_10.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_10.upper_bound.getHits() << "/" << stats_10.upper_bound.getMisses() << "/" << stats_10.upper_bound.getAccesses() << "\n";
const auto& stats_11 = ind_11.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [1,2,4,3,5,0,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_11.inserts.getHits() << "/" << stats_11.inserts.getMisses() << "/" << stats_11.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_11.contains.getHits() << "/" << stats_11.contains.getMisses() << "/" << stats_11.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_11.lower_bound.getHits() << "/" << stats_11.lower_bound.getMisses() << "/" << stats_11.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_11.upper_bound.getHits() << "/" << stats_11.upper_bound.getMisses() << "/" << stats_11.upper_bound.getAccesses() << "\n";
const auto& stats_12 = ind_12.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,1,2,3,4,5,7,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_12.inserts.getHits() << "/" << stats_12.inserts.getMisses() << "/" << stats_12.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_12.contains.getHits() << "/" << stats_12.contains.getMisses() << "/" << stats_12.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_12.lower_bound.getHits() << "/" << stats_12.lower_bound.getMisses() << "/" << stats_12.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_12.upper_bound.getHits() << "/" << stats_12.upper_bound.getMisses() << "/" << stats_12.upper_bound.getAccesses() << "\n";
const auto& stats_13 = ind_13.getHintStatistics();
o << prefix << "arity 8 direct b-tree index [0,1,3,5,2,4,6,7]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_13.inserts.getHits() << "/" << stats_13.inserts.getMisses() << "/" << stats_13.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_13.contains.getHits() << "/" << stats_13.contains.getMisses() << "/" << stats_13.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_13.lower_bound.getHits() << "/" << stats_13.lower_bound.getMisses() << "/" << stats_13.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_13.upper_bound.getHits() << "/" << stats_13.upper_bound.getMisses() << "/" << stats_13.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_4__0_1_2_3__3__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__3__15 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[2] = new_t[2];
old_t[3] = new_t[3];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1>, updater_t_btree_4__0_1_2_3__3__15>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_4__0_1_2_3__3__15& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [0,1,2,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_5__0_1_2_3_4__31 {
using t_tuple = Tuple<RamDomain, 5>;
struct updater_t_btree_5__0_1_2_3_4__31 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] = new_t[3];
old_t[4] = new_t[4];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_5__0_1_2_3_4__31>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_5__0_1_2_3_4__31& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,1,2,3,4]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_4__0_1_2_3__1__3__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_2_3__1__3__15 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[2] = new_t[2];
old_t[3] = new_t[3];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1>, updater_t_btree_4__0_1_2_3__1__3__15>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_4__0_1_2_3__1__3__15& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[1] = MIN_RAM_DOMAIN;
high[1] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_1(const t_tuple& t) const {
context h;
return equalRange_1(t, h);
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [0,1,2,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_5__0_1_2_3_4__3__7__31 {
using t_tuple = Tuple<RamDomain, 5>;
struct updater_t_btree_5__0_1_2_3_4__3__7__31 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] = new_t[3];
old_t[4] = new_t[4];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_5__0_1_2_3_4__3__7__31>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_5__0_1_2_3_4__3__7__31& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,1,2,3,4]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_4__1_0_2_3__2__3__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__1_0_2_3__2__3__15 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[2] = new_t[2];
old_t[3] = new_t[3];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<1,0,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,0>, updater_t_btree_4__1_0_2_3__2__3__15>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_4__1_0_2_3__2__3__15& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_2(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_2(const t_tuple& t) const {
context h;
return equalRange_2(t, h);
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_15(const t_tuple& t) const {
context h;
return equalRange_15(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [1,0,2,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_6__0_1_2_3_4_5__63 {
using t_tuple = Tuple<RamDomain, 6>;
struct updater_t_btree_6__0_1_2_3_4_5__63 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[4] = new_t[4];
old_t[5] = new_t[5];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4,5>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2,3>, updater_t_btree_6__0_1_2_3_4_5__63>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[6];
std::copy(ramDomain, ramDomain + 6, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4,RamDomain a5) {
RamDomain data[6] = {a0,a1,a2,a3,a4,a5};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_6__0_1_2_3_4_5__63& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_63(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_63(const t_tuple& t) const {
context h;
return equalRange_63(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 6 direct b-tree index [0,1,2,3,4,5]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_5__0_1_2_3_4__7__31 {
using t_tuple = Tuple<RamDomain, 5>;
struct updater_t_btree_5__0_1_2_3_4__7__31 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] = new_t[3];
old_t[4] = new_t[4];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_5__0_1_2_3_4__7__31>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_5__0_1_2_3_4__7__31& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_7(const t_tuple& t) const {
context h;
return equalRange_7(t, h);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,1,2,3,4]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_5__0_1_2_3_4__3__31 {
using t_tuple = Tuple<RamDomain, 5>;
struct updater_t_btree_5__0_1_2_3_4__3__31 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[3] = new_t[3];
old_t[4] = new_t[4];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1,2>, updater_t_btree_5__0_1_2_3_4__3__31>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0)) {
return true;
} else return false;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[5];
std::copy(ramDomain, ramDomain + 5, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4) {
RamDomain data[5] = {a0,a1,a2,a3,a4};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
void insertAll(t_btree_5__0_1_2_3_4__3__31& other) {
ind_0.insertAll(other.ind_0);
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0);
}
iterator find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> equalRange_0(const t_tuple& t, context& h) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> equalRange_0(const t_tuple& t) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
low[4] = MIN_RAM_DOMAIN;
high[4] = MAX_RAM_DOMAIN;
return make_range(ind_0.lower_bound(low, h.hints_0), ind_0.upper_bound(high, h.hints_0));
}
range<t_ind_0::iterator> equalRange_3(const t_tuple& t) const {
context h;
return equalRange_3(t, h);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t, context& h) const {
auto pos = ind_0.find(t, h.hints_0);
auto fin = ind_0.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_0::iterator> equalRange_31(const t_tuple& t) const {
context h;
return equalRange_31(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
return ind_0.getChunks(400);
}
void purge() {
ind_0.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 5 direct b-tree index [0,1,2,3,4]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};

class Sf_souffle_small : public SouffleProgram {
private:
static inline bool regex_wrapper(const std::string& pattern, const std::string& text) {
   bool result = false; 
   try { result = std::regex_match(text, std::regex(pattern)); } catch(...) { 
     std::cerr << "warning: wrong pattern provided for match(\"" << pattern << "\",\"" << text << "\").\n";
}
   return result;
}
private:
static inline std::string substr_wrapper(const std::string& str, size_t idx, size_t len) {
   std::string result; 
   try { result = str.substr(idx,len); } catch(...) { 
     std::cerr << "warning: wrong index position provided by substr(\"";
     std::cerr << str << "\"," << (int32_t)idx << "," << (int32_t)len << ") functor.\n";
   } return result;
}
private:
static inline RamDomain wrapper_tonumber(const std::string& str) {
   RamDomain result=0; 
   try { result = stord(str); } catch(...) { 
     std::cerr << "error: wrong string provided by to_number(\"";
     std::cerr << str << "\") functor.\n";
     raise(SIGFPE);
   } return result;
}
public:
// -- initialize symbol table --
SymbolTable symTable
{
	R"_(v0,v2,v1)_",
	R"_(Rule)_",
	R"_(points_initial,v0,v1)_",
	R"_(receiver_formal,v1,v2)_",
	R"_(pointsto_objcont(v0,v2,v1) :- 
   Rule(10),
   points_initial(v0,v1),
   receiver_formal(v1,v2).)_",
	R"_(v2,v0,v1)_",
	R"_(store,v1,v0,v2)_",
	R"_(pointsto_objcont(v2,v0,v1) :- 
   Rule(6),
   points_initial(v0,v1),
   store(v1,v0,v2).)_",
	R"_(v0,v1,v2)_",
	R"_(actual,v0,v1,v2)_",
	R"_(points_initial,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(11),
   actual(v0,v1,v2),
   points_initial(v0,v2).)_",
	R"_(pointsto_objcont,v0,v1,v2)_",
	R"_(receiver_formal,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(2),
   pointsto_objcont(v0,v1,v2),
   receiver_formal(v2,v0).)_",
	R"_(v1,v0,v2)_",
	R"_(load,v0,v1,v2)_",
	R"_(points_initial,v2,v0)_",
	R"_(pointsto_objcont(v1,v0,v2) :- 
   Rule(0),
   load(v0,v1,v2),
   points_initial(v2,v0).)_",
	R"_(pointsto_objcont(v1,v0,v2) :- 
   Rule(4),
   pointsto_objcont(v0,v1,v2),
   receiver_formal(v2,v0).)_",
	R"_(pointsto_objcont(v2,v0,v1) :- 
   Rule(8),
   points_initial(v0,v1),
   receiver_formal(v1,v2).)_",
	R"_(points_initial,v2,v1)_",
	R"_(pointsto_objcont(v0,v2,v1) :- 
   Rule(9),
   points_initial(v0,v1),
   points_initial(v2,v1).)_",
	R"_(pointsto_objcont,v1,v0,v2)_",
	R"_(pointsto_objcont(v2,v0,v1) :- 
   Rule(5),
   points_initial(v0,v1),
   pointsto_objcont(v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v2,v1) :- 
   Rule(1),
   points_initial(v0,v1),
   store(v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(3),
   load(v0,v1,v2),
   points_initial(v2,v0).)_",
	R"_(pointsto_objcont(v0,v2,v1) :- 
   Rule(7),
   points_initial(v0,v1),
   pointsto_objcont(v1,v0,v2).)_",
	R"_(enclosing_type,v0,v1)_",
	R"_(assign,v2,v0,v1,v1,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(69300),
   enclosing_type(v0,v1),
   assign(v2,v0,v1,v1,v0,v2).)_",
	R"_(enclosing_type,v0,v2)_",
	R"_(assign,v1,v0,v2,v2,v1,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(56630),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v1,v0).)_",
	R"_(assign,v0,v1,v1,v0,v2,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(34295),
   enclosing_type(v0,v2),
   assign(v0,v1,v1,v0,v2,v1).)_",
	R"_(enclosing_type,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(19791),
   enclosing_type(v2,v0),
   actual(v0,v1,v2).)_",
	R"_(assign,v0,v1,v2,v0,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(48017),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(13813),
   enclosing_type(v0,v1),
   load(v0,v1,v2).)_",
	R"_(enclosing_type,v1,v0)_",
	R"_(assign,v0,v2,v1,v2,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(28791),
   enclosing_type(v1,v0),
   assign(v0,v2,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(36691),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(invocation,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(15217),
   enclosing_type(v0,v1),
   invocation(v0,v2).)_",
	R"_(assign,v0,v2,v1,v1,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(27895),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(35837),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(enclosing_type,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(86626),
   enclosing_type(v1,v2),
   assign(v1,v0,v2,v2,v1,v0).)_",
	R"_(assign,v0,v1,v1,v0,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(22946),
   enclosing_type(v1,v0),
   assign(v0,v1,v1,v0,v2,v0).)_",
	R"_(assign,v2,v0,v1,v2,v1,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(84399),
   enclosing_type(v0,v2),
   assign(v2,v0,v1,v2,v1,v0).)_",
	R"_(actual,v1,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(18672),
   enclosing_type(v0,v1),
   actual(v1,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(73858),
   enclosing_type(v1,v0),
   assign(v2,v0,v1,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(28989),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(78609),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(35569),
   enclosing_type(v0,v1),
   assign(v0,v2,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(62907),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v1,v0,v2).)_",
	R"_(assign,v1,v2,v1,v0,v2,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(40656),
   enclosing_type(v0,v2),
   assign(v1,v2,v1,v0,v2,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(19390),
   enclosing_type(v1,v0),
   actual(v0,v1,v2).)_",
	R"_(assign,v0,v2,v0,v0,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(41025),
   enclosing_type(v2,v0),
   assign(v0,v2,v0,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(36249),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v2,v0,v1,v2,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(62351),
   enclosing_type(v0,v1),
   assign(v2,v0,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(2567),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v0,v1,v2,v1,v2,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(40179),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v2,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(59120),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v1,v0,v2,v2,v0,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(78420),
   enclosing_type(v0,v1),
   assign(v1,v0,v2,v2,v0,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(64858),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v0,v1,v2,v1,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(28441),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(47932),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(40777),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v1,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(38959),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(assign,v1,v0,v2,v1,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(52193),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v1,v2,v0).)_",
	R"_(assign,v1,v0,v2,v1,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(5063),
   assign(v1,v0,v2,v1,v0,v2).)_",
	R"_(assign,v0,v1,v2,v1,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(63698),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v2,v0).)_",
	R"_(assign,v2,v1,v0,v2,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(53306),
   enclosing_type(v0,v2),
   assign(v2,v1,v0,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(64812),
   enclosing_type(v0,v2),
   assign(v0,v2,v0,v0,v1,v2).)_",
	R"_(assign,v0,v2,v1,v0,v2,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(79085),
   enclosing_type(v0,v1),
   assign(v0,v2,v1,v0,v2,v2).)_",
	R"_(assign,v0,v0,v1,v2,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(35495),
   enclosing_type(v0,v1),
   assign(v0,v0,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(43610),
   enclosing_type(v1,v0),
   assign(v1,v0,v2,v1,v2,v0).)_",
	R"_(enclosing_type,v2,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(33581),
   enclosing_type(v2,v1),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(assign,v1,v2,v0,v1,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(88964),
   enclosing_type(v0,v2),
   assign(v1,v2,v0,v1,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(41537),
   enclosing_type(v0,v1),
   assign(v0,v2,v1,v0,v2,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(6139),
   assign(v0,v2,v1,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(66026),
   enclosing_type(v0,v2),
   assign(v0,v0,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(78281),
   enclosing_type(v0,v2),
   assign(v0,v0,v1,v2,v1,v2).)_",
	R"_(assign,v0,v2,v0,v1,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(34234),
   enclosing_type(v1,v2),
   assign(v0,v2,v0,v1,v2,v0).)_",
	R"_(assign,v0,v2,v1,v2,v0,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(48347),
   enclosing_type(v1,v2),
   assign(v0,v2,v1,v2,v0,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(36826),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(19964),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(70583),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v0,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(9423),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v1,v2,v1,v0,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(59394),
   enclosing_type(v0,v2),
   assign(v1,v2,v1,v0,v2,v0).)_",
	R"_(assign,v0,v0,v1,v1,v0,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(8227),
   assign(v0,v0,v1,v1,v0,v2).)_",
	R"_(assign,v1,v1,v0,v2,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(22304),
   enclosing_type(v0,v2),
   assign(v1,v1,v0,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(21947),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(82029),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(79077),
   enclosing_type(v1,v0),
   assign(v1,v0,v2,v2,v1,v0).)_",
	R"_(assign,v0,v0,v1,v2,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(4839),
   assign(v0,v0,v1,v2,v2,v0).)_",
	R"_(assign,v0,v2,v1,v2,v1,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(20846),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v2,v1,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(10458),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(25015),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(65996),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(34638),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(27604),
   enclosing_type(v2,v0),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(67769),
   enclosing_type(v0,v2),
   assign(v0,v1,v1,v0,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(63016),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v1,v0,v0,v1,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(42257),
   enclosing_type(v0,v2),
   assign(v1,v0,v0,v1,v2,v0).)_",
	R"_(assign,v1,v0,v2,v0,v1,v2)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(24992),
   enclosing_type(v1,v0),
   assign(v1,v0,v2,v0,v1,v2).)_",
	R"_(assign,v1,v0,v2,v2,v2,v0)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(32795),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(3548),
   assign(v0,v0,v1,v2,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(41694),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v0,v2,v0,v1,v2,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(64161),
   enclosing_type(v2,v0),
   assign(v0,v2,v0,v1,v2,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(14576),
   enclosing_type(v0,v1),
   load(v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(43687),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v0,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(7005),
   assign(v0,v1,v2,v1,v0,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(22493),
   enclosing_type(v1,v2),
   assign(v0,v1,v1,v0,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(40917),
   enclosing_type(v0,v2),
   assign(v1,v2,v0,v1,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(67708),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(90086),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(assign,v1,v2,v0,v1,v2,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(47927),
   enclosing_type(v0,v2),
   assign(v1,v2,v0,v1,v2,v1).)_",
	R"_(assign,v2,v1,v0,v2,v2,v1)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(86220),
   enclosing_type(v1,v0),
   assign(v2,v1,v0,v2,v2,v1).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(87963),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(20685),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(39726),
   enclosing_type(v1,v0),
   assign(v0,v1,v2,v1,v2,v0).)_",
	R"_(pointsto_objcont(v0,v1,v2) :- 
   Rule(73695),
   enclosing_type(v2,v1),
   assign(v2,v0,v1,v2,v1,v2).)_",
};// -- Table: Rule
std::unique_ptr<t_btree_3__0_1_2__1__7> rel_1_Rule = std::make_unique<t_btree_3__0_1_2__1__7>();
souffle::RelationWrapper<0,t_btree_3__0_1_2__1__7,Tuple<RamDomain,3>,3> wrapper_rel_1_Rule;
// -- Table: actual
std::unique_ptr<t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31> rel_2_actual = std::make_unique<t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31>();
souffle::RelationWrapper<1,t_btree_5__0_1_2_4_3__0_2_1_3_4__3__5__7__31,Tuple<RamDomain,5>,5> wrapper_rel_2_actual;
// -- Table: assign
std::unique_ptr<t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255> rel_3_assign = std::make_unique<t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255>();
souffle::RelationWrapper<2,t_btree_8__2_3_5_0_1_4_7_6__1_2_5_3_0_4_7_6__0_2_5_1_3_4_7_6__0_1_4_5_2_3_7_6__0_2_4_5_1_3_7_6__1_2_4_5_0_3_7_6__0_2_4_1_5_3_7_6__0_3_4_5_1_2_7_6__1_3_4_5_0_2_7_6__0_3_4_1_5_2_7_6__0_2_3_4_5_1_7_6__1_2_4_3_5_0_7_6__0_1_2_3_4_5_7_6__0_1_3_5_2_4_6_7__7__13__15__21__22__23__25__26__27__29__30__31__37__38__39__43__44__45__46__47__51__53__54__55__57__58__59__61__62__63__255,Tuple<RamDomain,8>,8> wrapper_rel_3_assign;
// -- Table: enclosing_type
std::unique_ptr<t_btree_4__0_1_2_3__3__15> rel_4_enclosing_type = std::make_unique<t_btree_4__0_1_2_3__3__15>();
souffle::RelationWrapper<3,t_btree_4__0_1_2_3__3__15,Tuple<RamDomain,4>,4> wrapper_rel_4_enclosing_type;
// -- Table: heappointsto
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_5_heappointsto = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<4,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_5_heappointsto;
// -- Table: invocation
std::unique_ptr<t_btree_4__0_1_2_3__1__3__15> rel_6_invocation = std::make_unique<t_btree_4__0_1_2_3__1__3__15>();
souffle::RelationWrapper<5,t_btree_4__0_1_2_3__1__3__15,Tuple<RamDomain,4>,4> wrapper_rel_6_invocation;
// -- Table: load
std::unique_ptr<t_btree_5__0_1_2_3_4__3__7__31> rel_7_load = std::make_unique<t_btree_5__0_1_2_3_4__3__7__31>();
souffle::RelationWrapper<6,t_btree_5__0_1_2_3_4__3__7__31,Tuple<RamDomain,5>,5> wrapper_rel_7_load;
// -- Table: points_initial
std::unique_ptr<t_btree_4__1_0_2_3__2__3__15> rel_8_points_initial = std::make_unique<t_btree_4__1_0_2_3__2__3__15>();
souffle::RelationWrapper<7,t_btree_4__1_0_2_3__2__3__15,Tuple<RamDomain,4>,4> wrapper_rel_8_points_initial;
// -- Table: pointsto
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_9_pointsto = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<8,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_9_pointsto;
// -- Table: receiver_formal
std::unique_ptr<t_btree_4__0_1_2_3__1__3__15> rel_10_receiver_formal = std::make_unique<t_btree_4__0_1_2_3__1__3__15>();
souffle::RelationWrapper<9,t_btree_4__0_1_2_3__1__3__15,Tuple<RamDomain,4>,4> wrapper_rel_10_receiver_formal;
// -- Table: store
std::unique_ptr<t_btree_5__0_1_2_3_4__3__7__31> rel_11_store = std::make_unique<t_btree_5__0_1_2_3_4__3__7__31>();
souffle::RelationWrapper<10,t_btree_5__0_1_2_3_4__3__7__31,Tuple<RamDomain,5>,5> wrapper_rel_11_store;
// -- Table: pointsto_objcont
std::unique_ptr<t_btree_5__0_1_2_3_4__7__31> rel_12_pointsto_objcont = std::make_unique<t_btree_5__0_1_2_3_4__7__31>();
souffle::RelationWrapper<11,t_btree_5__0_1_2_3_4__7__31,Tuple<RamDomain,5>,5> wrapper_rel_12_pointsto_objcont;
// -- Table: @delta_pointsto_objcont
std::unique_ptr<t_btree_5__0_1_2_3_4__3__31> rel_13_delta_pointsto_objcont = std::make_unique<t_btree_5__0_1_2_3_4__3__31>();
// -- Table: @new_pointsto_objcont
std::unique_ptr<t_btree_5__0_1_2_3_4__3__31> rel_14_new_pointsto_objcont = std::make_unique<t_btree_5__0_1_2_3_4__3__31>();
// -- Table: pointsto_objcont.@info.1
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_15_pointsto_objcont_info_1 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<12,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_15_pointsto_objcont_info_1;
// -- Table: pointsto_objcont.@info.10
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_16_pointsto_objcont_info_10 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<13,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_16_pointsto_objcont_info_10;
// -- Table: pointsto_objcont.@info.100
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_17_pointsto_objcont_info_100 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<14,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_17_pointsto_objcont_info_100;
// -- Table: pointsto_objcont.@info.11
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_18_pointsto_objcont_info_11 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<15,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_18_pointsto_objcont_info_11;
// -- Table: pointsto_objcont.@info.12
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_19_pointsto_objcont_info_12 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<16,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_19_pointsto_objcont_info_12;
// -- Table: pointsto_objcont.@info.13
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_20_pointsto_objcont_info_13 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<17,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_20_pointsto_objcont_info_13;
// -- Table: pointsto_objcont.@info.14
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_21_pointsto_objcont_info_14 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<18,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_21_pointsto_objcont_info_14;
// -- Table: pointsto_objcont.@info.15
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_22_pointsto_objcont_info_15 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<19,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_22_pointsto_objcont_info_15;
// -- Table: pointsto_objcont.@info.16
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_23_pointsto_objcont_info_16 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<20,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_23_pointsto_objcont_info_16;
// -- Table: pointsto_objcont.@info.17
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_24_pointsto_objcont_info_17 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<21,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_24_pointsto_objcont_info_17;
// -- Table: pointsto_objcont.@info.18
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_25_pointsto_objcont_info_18 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<22,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_25_pointsto_objcont_info_18;
// -- Table: pointsto_objcont.@info.19
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_26_pointsto_objcont_info_19 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<23,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_26_pointsto_objcont_info_19;
// -- Table: pointsto_objcont.@info.2
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_27_pointsto_objcont_info_2 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<24,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_27_pointsto_objcont_info_2;
// -- Table: pointsto_objcont.@info.20
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_28_pointsto_objcont_info_20 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<25,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_28_pointsto_objcont_info_20;
// -- Table: pointsto_objcont.@info.21
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_29_pointsto_objcont_info_21 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<26,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_29_pointsto_objcont_info_21;
// -- Table: pointsto_objcont.@info.22
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_30_pointsto_objcont_info_22 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<27,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_30_pointsto_objcont_info_22;
// -- Table: pointsto_objcont.@info.23
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_31_pointsto_objcont_info_23 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<28,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_31_pointsto_objcont_info_23;
// -- Table: pointsto_objcont.@info.24
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_32_pointsto_objcont_info_24 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<29,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_32_pointsto_objcont_info_24;
// -- Table: pointsto_objcont.@info.25
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_33_pointsto_objcont_info_25 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<30,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_33_pointsto_objcont_info_25;
// -- Table: pointsto_objcont.@info.26
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_34_pointsto_objcont_info_26 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<31,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_34_pointsto_objcont_info_26;
// -- Table: pointsto_objcont.@info.27
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_35_pointsto_objcont_info_27 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<32,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_35_pointsto_objcont_info_27;
// -- Table: pointsto_objcont.@info.28
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_36_pointsto_objcont_info_28 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<33,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_36_pointsto_objcont_info_28;
// -- Table: pointsto_objcont.@info.29
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_37_pointsto_objcont_info_29 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<34,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_37_pointsto_objcont_info_29;
// -- Table: pointsto_objcont.@info.3
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_38_pointsto_objcont_info_3 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<35,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_38_pointsto_objcont_info_3;
// -- Table: pointsto_objcont.@info.30
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_39_pointsto_objcont_info_30 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<36,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_39_pointsto_objcont_info_30;
// -- Table: pointsto_objcont.@info.31
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_40_pointsto_objcont_info_31 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<37,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_40_pointsto_objcont_info_31;
// -- Table: pointsto_objcont.@info.32
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_41_pointsto_objcont_info_32 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<38,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_41_pointsto_objcont_info_32;
// -- Table: pointsto_objcont.@info.33
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_42_pointsto_objcont_info_33 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<39,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_42_pointsto_objcont_info_33;
// -- Table: pointsto_objcont.@info.34
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_43_pointsto_objcont_info_34 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<40,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_43_pointsto_objcont_info_34;
// -- Table: pointsto_objcont.@info.35
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_44_pointsto_objcont_info_35 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<41,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_44_pointsto_objcont_info_35;
// -- Table: pointsto_objcont.@info.36
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_45_pointsto_objcont_info_36 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<42,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_45_pointsto_objcont_info_36;
// -- Table: pointsto_objcont.@info.37
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_46_pointsto_objcont_info_37 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<43,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_46_pointsto_objcont_info_37;
// -- Table: pointsto_objcont.@info.38
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_47_pointsto_objcont_info_38 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<44,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_47_pointsto_objcont_info_38;
// -- Table: pointsto_objcont.@info.39
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_48_pointsto_objcont_info_39 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<45,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_48_pointsto_objcont_info_39;
// -- Table: pointsto_objcont.@info.4
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_49_pointsto_objcont_info_4 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<46,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_49_pointsto_objcont_info_4;
// -- Table: pointsto_objcont.@info.40
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_50_pointsto_objcont_info_40 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<47,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_50_pointsto_objcont_info_40;
// -- Table: pointsto_objcont.@info.41
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_51_pointsto_objcont_info_41 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<48,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_51_pointsto_objcont_info_41;
// -- Table: pointsto_objcont.@info.42
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_52_pointsto_objcont_info_42 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<49,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_52_pointsto_objcont_info_42;
// -- Table: pointsto_objcont.@info.43
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_53_pointsto_objcont_info_43 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<50,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_53_pointsto_objcont_info_43;
// -- Table: pointsto_objcont.@info.44
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_54_pointsto_objcont_info_44 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<51,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_54_pointsto_objcont_info_44;
// -- Table: pointsto_objcont.@info.45
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_55_pointsto_objcont_info_45 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<52,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_55_pointsto_objcont_info_45;
// -- Table: pointsto_objcont.@info.46
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_56_pointsto_objcont_info_46 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<53,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_56_pointsto_objcont_info_46;
// -- Table: pointsto_objcont.@info.47
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_57_pointsto_objcont_info_47 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<54,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_57_pointsto_objcont_info_47;
// -- Table: pointsto_objcont.@info.48
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_58_pointsto_objcont_info_48 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<55,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_58_pointsto_objcont_info_48;
// -- Table: pointsto_objcont.@info.49
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_59_pointsto_objcont_info_49 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<56,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_59_pointsto_objcont_info_49;
// -- Table: pointsto_objcont.@info.5
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_60_pointsto_objcont_info_5 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<57,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_60_pointsto_objcont_info_5;
// -- Table: pointsto_objcont.@info.50
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_61_pointsto_objcont_info_50 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<58,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_61_pointsto_objcont_info_50;
// -- Table: pointsto_objcont.@info.51
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_62_pointsto_objcont_info_51 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<59,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_62_pointsto_objcont_info_51;
// -- Table: pointsto_objcont.@info.52
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_63_pointsto_objcont_info_52 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<60,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_63_pointsto_objcont_info_52;
// -- Table: pointsto_objcont.@info.53
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_64_pointsto_objcont_info_53 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<61,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_64_pointsto_objcont_info_53;
// -- Table: pointsto_objcont.@info.54
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_65_pointsto_objcont_info_54 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<62,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_65_pointsto_objcont_info_54;
// -- Table: pointsto_objcont.@info.55
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_66_pointsto_objcont_info_55 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<63,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_66_pointsto_objcont_info_55;
// -- Table: pointsto_objcont.@info.56
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_67_pointsto_objcont_info_56 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<64,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_67_pointsto_objcont_info_56;
// -- Table: pointsto_objcont.@info.57
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_68_pointsto_objcont_info_57 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<65,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_68_pointsto_objcont_info_57;
// -- Table: pointsto_objcont.@info.58
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_69_pointsto_objcont_info_58 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<66,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_69_pointsto_objcont_info_58;
// -- Table: pointsto_objcont.@info.59
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_70_pointsto_objcont_info_59 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<67,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_70_pointsto_objcont_info_59;
// -- Table: pointsto_objcont.@info.6
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_71_pointsto_objcont_info_6 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<68,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_71_pointsto_objcont_info_6;
// -- Table: pointsto_objcont.@info.60
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_72_pointsto_objcont_info_60 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<69,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_72_pointsto_objcont_info_60;
// -- Table: pointsto_objcont.@info.61
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_73_pointsto_objcont_info_61 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<70,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_73_pointsto_objcont_info_61;
// -- Table: pointsto_objcont.@info.62
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_74_pointsto_objcont_info_62 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<71,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_74_pointsto_objcont_info_62;
// -- Table: pointsto_objcont.@info.63
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_75_pointsto_objcont_info_63 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<72,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_75_pointsto_objcont_info_63;
// -- Table: pointsto_objcont.@info.64
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_76_pointsto_objcont_info_64 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<73,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_76_pointsto_objcont_info_64;
// -- Table: pointsto_objcont.@info.65
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_77_pointsto_objcont_info_65 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<74,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_77_pointsto_objcont_info_65;
// -- Table: pointsto_objcont.@info.66
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_78_pointsto_objcont_info_66 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<75,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_78_pointsto_objcont_info_66;
// -- Table: pointsto_objcont.@info.67
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_79_pointsto_objcont_info_67 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<76,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_79_pointsto_objcont_info_67;
// -- Table: pointsto_objcont.@info.68
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_80_pointsto_objcont_info_68 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<77,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_80_pointsto_objcont_info_68;
// -- Table: pointsto_objcont.@info.69
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_81_pointsto_objcont_info_69 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<78,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_81_pointsto_objcont_info_69;
// -- Table: pointsto_objcont.@info.7
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_82_pointsto_objcont_info_7 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<79,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_82_pointsto_objcont_info_7;
// -- Table: pointsto_objcont.@info.70
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_83_pointsto_objcont_info_70 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<80,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_83_pointsto_objcont_info_70;
// -- Table: pointsto_objcont.@info.71
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_84_pointsto_objcont_info_71 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<81,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_84_pointsto_objcont_info_71;
// -- Table: pointsto_objcont.@info.72
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_85_pointsto_objcont_info_72 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<82,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_85_pointsto_objcont_info_72;
// -- Table: pointsto_objcont.@info.73
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_86_pointsto_objcont_info_73 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<83,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_86_pointsto_objcont_info_73;
// -- Table: pointsto_objcont.@info.74
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_87_pointsto_objcont_info_74 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<84,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_87_pointsto_objcont_info_74;
// -- Table: pointsto_objcont.@info.75
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_88_pointsto_objcont_info_75 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<85,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_88_pointsto_objcont_info_75;
// -- Table: pointsto_objcont.@info.76
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_89_pointsto_objcont_info_76 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<86,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_89_pointsto_objcont_info_76;
// -- Table: pointsto_objcont.@info.77
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_90_pointsto_objcont_info_77 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<87,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_90_pointsto_objcont_info_77;
// -- Table: pointsto_objcont.@info.78
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_91_pointsto_objcont_info_78 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<88,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_91_pointsto_objcont_info_78;
// -- Table: pointsto_objcont.@info.79
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_92_pointsto_objcont_info_79 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<89,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_92_pointsto_objcont_info_79;
// -- Table: pointsto_objcont.@info.8
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_93_pointsto_objcont_info_8 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<90,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_93_pointsto_objcont_info_8;
// -- Table: pointsto_objcont.@info.80
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_94_pointsto_objcont_info_80 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<91,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_94_pointsto_objcont_info_80;
// -- Table: pointsto_objcont.@info.81
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_95_pointsto_objcont_info_81 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<92,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_95_pointsto_objcont_info_81;
// -- Table: pointsto_objcont.@info.82
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_96_pointsto_objcont_info_82 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<93,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_96_pointsto_objcont_info_82;
// -- Table: pointsto_objcont.@info.83
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_97_pointsto_objcont_info_83 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<94,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_97_pointsto_objcont_info_83;
// -- Table: pointsto_objcont.@info.84
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_98_pointsto_objcont_info_84 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<95,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_98_pointsto_objcont_info_84;
// -- Table: pointsto_objcont.@info.85
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_99_pointsto_objcont_info_85 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<96,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_99_pointsto_objcont_info_85;
// -- Table: pointsto_objcont.@info.86
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_100_pointsto_objcont_info_86 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<97,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_100_pointsto_objcont_info_86;
// -- Table: pointsto_objcont.@info.87
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_101_pointsto_objcont_info_87 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<98,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_101_pointsto_objcont_info_87;
// -- Table: pointsto_objcont.@info.88
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_102_pointsto_objcont_info_88 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<99,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_102_pointsto_objcont_info_88;
// -- Table: pointsto_objcont.@info.89
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_103_pointsto_objcont_info_89 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<100,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_103_pointsto_objcont_info_89;
// -- Table: pointsto_objcont.@info.9
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_104_pointsto_objcont_info_9 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<101,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_104_pointsto_objcont_info_9;
// -- Table: pointsto_objcont.@info.90
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_105_pointsto_objcont_info_90 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<102,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_105_pointsto_objcont_info_90;
// -- Table: pointsto_objcont.@info.91
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_106_pointsto_objcont_info_91 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<103,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_106_pointsto_objcont_info_91;
// -- Table: pointsto_objcont.@info.92
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_107_pointsto_objcont_info_92 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<104,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_107_pointsto_objcont_info_92;
// -- Table: pointsto_objcont.@info.93
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_108_pointsto_objcont_info_93 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<105,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_108_pointsto_objcont_info_93;
// -- Table: pointsto_objcont.@info.94
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_109_pointsto_objcont_info_94 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<106,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_109_pointsto_objcont_info_94;
// -- Table: pointsto_objcont.@info.95
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_110_pointsto_objcont_info_95 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<107,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_110_pointsto_objcont_info_95;
// -- Table: pointsto_objcont.@info.96
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_111_pointsto_objcont_info_96 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<108,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_111_pointsto_objcont_info_96;
// -- Table: pointsto_objcont.@info.97
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_112_pointsto_objcont_info_97 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<109,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_112_pointsto_objcont_info_97;
// -- Table: pointsto_objcont.@info.98
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_113_pointsto_objcont_info_98 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<110,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_113_pointsto_objcont_info_98;
// -- Table: pointsto_objcont.@info.99
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_114_pointsto_objcont_info_99 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<111,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_114_pointsto_objcont_info_99;
public:
Sf_souffle_small() : 
wrapper_rel_1_Rule(*rel_1_Rule,symTable,"Rule",std::array<const char *,3>{{"i:number","i:number","i:number"}},std::array<const char *,3>{{"v0","@rule_number","@level_number"}}),

wrapper_rel_2_actual(*rel_2_actual,symTable,"actual",std::array<const char *,5>{{"s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,5>{{"v0","v1","v2","@rule_number","@level_number"}}),

wrapper_rel_3_assign(*rel_3_assign,symTable,"assign",std::array<const char *,8>{{"s:V","s:V","s:V","s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,8>{{"v0","v1","v2","v3","v4","v5","@rule_number","@level_number"}}),

wrapper_rel_4_enclosing_type(*rel_4_enclosing_type,symTable,"enclosing_type",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_5_heappointsto(*rel_5_heappointsto,symTable,"heappointsto",std::array<const char *,5>{{"s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,5>{{"v0","v1","v2","@rule_number","@level_number"}}),

wrapper_rel_6_invocation(*rel_6_invocation,symTable,"invocation",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_7_load(*rel_7_load,symTable,"load",std::array<const char *,5>{{"s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,5>{{"v0","v1","v2","@rule_number","@level_number"}}),

wrapper_rel_8_points_initial(*rel_8_points_initial,symTable,"points_initial",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_9_pointsto(*rel_9_pointsto,symTable,"pointsto",std::array<const char *,6>{{"s:V","s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,6>{{"v0","v1","v2","v3","@rule_number","@level_number"}}),

wrapper_rel_10_receiver_formal(*rel_10_receiver_formal,symTable,"receiver_formal",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_11_store(*rel_11_store,symTable,"store",std::array<const char *,5>{{"s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,5>{{"v0","v1","v2","@rule_number","@level_number"}}),

wrapper_rel_12_pointsto_objcont(*rel_12_pointsto_objcont,symTable,"pointsto_objcont",std::array<const char *,5>{{"s:V","s:V","s:V","i:number","i:number"}},std::array<const char *,5>{{"v0","v1","v2","@rule_number","@level_number"}}),

wrapper_rel_15_pointsto_objcont_info_1(*rel_15_pointsto_objcont_info_1,symTable,"pointsto_objcont.@info.1",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_16_pointsto_objcont_info_10(*rel_16_pointsto_objcont_info_10,symTable,"pointsto_objcont.@info.10",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_17_pointsto_objcont_info_100(*rel_17_pointsto_objcont_info_100,symTable,"pointsto_objcont.@info.100",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_18_pointsto_objcont_info_11(*rel_18_pointsto_objcont_info_11,symTable,"pointsto_objcont.@info.11",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_19_pointsto_objcont_info_12(*rel_19_pointsto_objcont_info_12,symTable,"pointsto_objcont.@info.12",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_20_pointsto_objcont_info_13(*rel_20_pointsto_objcont_info_13,symTable,"pointsto_objcont.@info.13",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_21_pointsto_objcont_info_14(*rel_21_pointsto_objcont_info_14,symTable,"pointsto_objcont.@info.14",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_22_pointsto_objcont_info_15(*rel_22_pointsto_objcont_info_15,symTable,"pointsto_objcont.@info.15",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_23_pointsto_objcont_info_16(*rel_23_pointsto_objcont_info_16,symTable,"pointsto_objcont.@info.16",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_24_pointsto_objcont_info_17(*rel_24_pointsto_objcont_info_17,symTable,"pointsto_objcont.@info.17",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_25_pointsto_objcont_info_18(*rel_25_pointsto_objcont_info_18,symTable,"pointsto_objcont.@info.18",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_26_pointsto_objcont_info_19(*rel_26_pointsto_objcont_info_19,symTable,"pointsto_objcont.@info.19",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_27_pointsto_objcont_info_2(*rel_27_pointsto_objcont_info_2,symTable,"pointsto_objcont.@info.2",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_28_pointsto_objcont_info_20(*rel_28_pointsto_objcont_info_20,symTable,"pointsto_objcont.@info.20",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_29_pointsto_objcont_info_21(*rel_29_pointsto_objcont_info_21,symTable,"pointsto_objcont.@info.21",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_30_pointsto_objcont_info_22(*rel_30_pointsto_objcont_info_22,symTable,"pointsto_objcont.@info.22",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_31_pointsto_objcont_info_23(*rel_31_pointsto_objcont_info_23,symTable,"pointsto_objcont.@info.23",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_32_pointsto_objcont_info_24(*rel_32_pointsto_objcont_info_24,symTable,"pointsto_objcont.@info.24",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_33_pointsto_objcont_info_25(*rel_33_pointsto_objcont_info_25,symTable,"pointsto_objcont.@info.25",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_34_pointsto_objcont_info_26(*rel_34_pointsto_objcont_info_26,symTable,"pointsto_objcont.@info.26",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_35_pointsto_objcont_info_27(*rel_35_pointsto_objcont_info_27,symTable,"pointsto_objcont.@info.27",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_36_pointsto_objcont_info_28(*rel_36_pointsto_objcont_info_28,symTable,"pointsto_objcont.@info.28",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_37_pointsto_objcont_info_29(*rel_37_pointsto_objcont_info_29,symTable,"pointsto_objcont.@info.29",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_38_pointsto_objcont_info_3(*rel_38_pointsto_objcont_info_3,symTable,"pointsto_objcont.@info.3",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_39_pointsto_objcont_info_30(*rel_39_pointsto_objcont_info_30,symTable,"pointsto_objcont.@info.30",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_40_pointsto_objcont_info_31(*rel_40_pointsto_objcont_info_31,symTable,"pointsto_objcont.@info.31",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_41_pointsto_objcont_info_32(*rel_41_pointsto_objcont_info_32,symTable,"pointsto_objcont.@info.32",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_42_pointsto_objcont_info_33(*rel_42_pointsto_objcont_info_33,symTable,"pointsto_objcont.@info.33",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_43_pointsto_objcont_info_34(*rel_43_pointsto_objcont_info_34,symTable,"pointsto_objcont.@info.34",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_44_pointsto_objcont_info_35(*rel_44_pointsto_objcont_info_35,symTable,"pointsto_objcont.@info.35",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_45_pointsto_objcont_info_36(*rel_45_pointsto_objcont_info_36,symTable,"pointsto_objcont.@info.36",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_46_pointsto_objcont_info_37(*rel_46_pointsto_objcont_info_37,symTable,"pointsto_objcont.@info.37",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_47_pointsto_objcont_info_38(*rel_47_pointsto_objcont_info_38,symTable,"pointsto_objcont.@info.38",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_48_pointsto_objcont_info_39(*rel_48_pointsto_objcont_info_39,symTable,"pointsto_objcont.@info.39",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_49_pointsto_objcont_info_4(*rel_49_pointsto_objcont_info_4,symTable,"pointsto_objcont.@info.4",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_50_pointsto_objcont_info_40(*rel_50_pointsto_objcont_info_40,symTable,"pointsto_objcont.@info.40",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_51_pointsto_objcont_info_41(*rel_51_pointsto_objcont_info_41,symTable,"pointsto_objcont.@info.41",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_52_pointsto_objcont_info_42(*rel_52_pointsto_objcont_info_42,symTable,"pointsto_objcont.@info.42",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_53_pointsto_objcont_info_43(*rel_53_pointsto_objcont_info_43,symTable,"pointsto_objcont.@info.43",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_54_pointsto_objcont_info_44(*rel_54_pointsto_objcont_info_44,symTable,"pointsto_objcont.@info.44",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_55_pointsto_objcont_info_45(*rel_55_pointsto_objcont_info_45,symTable,"pointsto_objcont.@info.45",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_56_pointsto_objcont_info_46(*rel_56_pointsto_objcont_info_46,symTable,"pointsto_objcont.@info.46",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_57_pointsto_objcont_info_47(*rel_57_pointsto_objcont_info_47,symTable,"pointsto_objcont.@info.47",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_58_pointsto_objcont_info_48(*rel_58_pointsto_objcont_info_48,symTable,"pointsto_objcont.@info.48",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_59_pointsto_objcont_info_49(*rel_59_pointsto_objcont_info_49,symTable,"pointsto_objcont.@info.49",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_60_pointsto_objcont_info_5(*rel_60_pointsto_objcont_info_5,symTable,"pointsto_objcont.@info.5",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_61_pointsto_objcont_info_50(*rel_61_pointsto_objcont_info_50,symTable,"pointsto_objcont.@info.50",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_62_pointsto_objcont_info_51(*rel_62_pointsto_objcont_info_51,symTable,"pointsto_objcont.@info.51",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_63_pointsto_objcont_info_52(*rel_63_pointsto_objcont_info_52,symTable,"pointsto_objcont.@info.52",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_64_pointsto_objcont_info_53(*rel_64_pointsto_objcont_info_53,symTable,"pointsto_objcont.@info.53",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_65_pointsto_objcont_info_54(*rel_65_pointsto_objcont_info_54,symTable,"pointsto_objcont.@info.54",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_66_pointsto_objcont_info_55(*rel_66_pointsto_objcont_info_55,symTable,"pointsto_objcont.@info.55",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_67_pointsto_objcont_info_56(*rel_67_pointsto_objcont_info_56,symTable,"pointsto_objcont.@info.56",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_68_pointsto_objcont_info_57(*rel_68_pointsto_objcont_info_57,symTable,"pointsto_objcont.@info.57",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_69_pointsto_objcont_info_58(*rel_69_pointsto_objcont_info_58,symTable,"pointsto_objcont.@info.58",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_70_pointsto_objcont_info_59(*rel_70_pointsto_objcont_info_59,symTable,"pointsto_objcont.@info.59",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_71_pointsto_objcont_info_6(*rel_71_pointsto_objcont_info_6,symTable,"pointsto_objcont.@info.6",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_72_pointsto_objcont_info_60(*rel_72_pointsto_objcont_info_60,symTable,"pointsto_objcont.@info.60",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_73_pointsto_objcont_info_61(*rel_73_pointsto_objcont_info_61,symTable,"pointsto_objcont.@info.61",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_74_pointsto_objcont_info_62(*rel_74_pointsto_objcont_info_62,symTable,"pointsto_objcont.@info.62",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_75_pointsto_objcont_info_63(*rel_75_pointsto_objcont_info_63,symTable,"pointsto_objcont.@info.63",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_76_pointsto_objcont_info_64(*rel_76_pointsto_objcont_info_64,symTable,"pointsto_objcont.@info.64",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_77_pointsto_objcont_info_65(*rel_77_pointsto_objcont_info_65,symTable,"pointsto_objcont.@info.65",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_78_pointsto_objcont_info_66(*rel_78_pointsto_objcont_info_66,symTable,"pointsto_objcont.@info.66",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_79_pointsto_objcont_info_67(*rel_79_pointsto_objcont_info_67,symTable,"pointsto_objcont.@info.67",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_80_pointsto_objcont_info_68(*rel_80_pointsto_objcont_info_68,symTable,"pointsto_objcont.@info.68",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_81_pointsto_objcont_info_69(*rel_81_pointsto_objcont_info_69,symTable,"pointsto_objcont.@info.69",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_82_pointsto_objcont_info_7(*rel_82_pointsto_objcont_info_7,symTable,"pointsto_objcont.@info.7",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_83_pointsto_objcont_info_70(*rel_83_pointsto_objcont_info_70,symTable,"pointsto_objcont.@info.70",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_84_pointsto_objcont_info_71(*rel_84_pointsto_objcont_info_71,symTable,"pointsto_objcont.@info.71",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_85_pointsto_objcont_info_72(*rel_85_pointsto_objcont_info_72,symTable,"pointsto_objcont.@info.72",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_86_pointsto_objcont_info_73(*rel_86_pointsto_objcont_info_73,symTable,"pointsto_objcont.@info.73",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_87_pointsto_objcont_info_74(*rel_87_pointsto_objcont_info_74,symTable,"pointsto_objcont.@info.74",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_88_pointsto_objcont_info_75(*rel_88_pointsto_objcont_info_75,symTable,"pointsto_objcont.@info.75",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_89_pointsto_objcont_info_76(*rel_89_pointsto_objcont_info_76,symTable,"pointsto_objcont.@info.76",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_90_pointsto_objcont_info_77(*rel_90_pointsto_objcont_info_77,symTable,"pointsto_objcont.@info.77",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_91_pointsto_objcont_info_78(*rel_91_pointsto_objcont_info_78,symTable,"pointsto_objcont.@info.78",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_92_pointsto_objcont_info_79(*rel_92_pointsto_objcont_info_79,symTable,"pointsto_objcont.@info.79",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_93_pointsto_objcont_info_8(*rel_93_pointsto_objcont_info_8,symTable,"pointsto_objcont.@info.8",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_94_pointsto_objcont_info_80(*rel_94_pointsto_objcont_info_80,symTable,"pointsto_objcont.@info.80",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_95_pointsto_objcont_info_81(*rel_95_pointsto_objcont_info_81,symTable,"pointsto_objcont.@info.81",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_96_pointsto_objcont_info_82(*rel_96_pointsto_objcont_info_82,symTable,"pointsto_objcont.@info.82",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_97_pointsto_objcont_info_83(*rel_97_pointsto_objcont_info_83,symTable,"pointsto_objcont.@info.83",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_98_pointsto_objcont_info_84(*rel_98_pointsto_objcont_info_84,symTable,"pointsto_objcont.@info.84",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_99_pointsto_objcont_info_85(*rel_99_pointsto_objcont_info_85,symTable,"pointsto_objcont.@info.85",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_100_pointsto_objcont_info_86(*rel_100_pointsto_objcont_info_86,symTable,"pointsto_objcont.@info.86",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_101_pointsto_objcont_info_87(*rel_101_pointsto_objcont_info_87,symTable,"pointsto_objcont.@info.87",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_102_pointsto_objcont_info_88(*rel_102_pointsto_objcont_info_88,symTable,"pointsto_objcont.@info.88",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_103_pointsto_objcont_info_89(*rel_103_pointsto_objcont_info_89,symTable,"pointsto_objcont.@info.89",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_104_pointsto_objcont_info_9(*rel_104_pointsto_objcont_info_9,symTable,"pointsto_objcont.@info.9",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_105_pointsto_objcont_info_90(*rel_105_pointsto_objcont_info_90,symTable,"pointsto_objcont.@info.90",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_106_pointsto_objcont_info_91(*rel_106_pointsto_objcont_info_91,symTable,"pointsto_objcont.@info.91",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_107_pointsto_objcont_info_92(*rel_107_pointsto_objcont_info_92,symTable,"pointsto_objcont.@info.92",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_108_pointsto_objcont_info_93(*rel_108_pointsto_objcont_info_93,symTable,"pointsto_objcont.@info.93",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_109_pointsto_objcont_info_94(*rel_109_pointsto_objcont_info_94,symTable,"pointsto_objcont.@info.94",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_110_pointsto_objcont_info_95(*rel_110_pointsto_objcont_info_95,symTable,"pointsto_objcont.@info.95",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_111_pointsto_objcont_info_96(*rel_111_pointsto_objcont_info_96,symTable,"pointsto_objcont.@info.96",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_112_pointsto_objcont_info_97(*rel_112_pointsto_objcont_info_97,symTable,"pointsto_objcont.@info.97",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_113_pointsto_objcont_info_98(*rel_113_pointsto_objcont_info_98,symTable,"pointsto_objcont.@info.98",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_114_pointsto_objcont_info_99(*rel_114_pointsto_objcont_info_99,symTable,"pointsto_objcont.@info.99",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}){
addRelation("Rule",&wrapper_rel_1_Rule,true,false);
addRelation("actual",&wrapper_rel_2_actual,true,false);
addRelation("assign",&wrapper_rel_3_assign,true,false);
addRelation("enclosing_type",&wrapper_rel_4_enclosing_type,true,false);
addRelation("heappointsto",&wrapper_rel_5_heappointsto,false,true);
addRelation("invocation",&wrapper_rel_6_invocation,true,false);
addRelation("load",&wrapper_rel_7_load,true,false);
addRelation("points_initial",&wrapper_rel_8_points_initial,true,false);
addRelation("pointsto",&wrapper_rel_9_pointsto,false,true);
addRelation("receiver_formal",&wrapper_rel_10_receiver_formal,true,false);
addRelation("store",&wrapper_rel_11_store,true,false);
addRelation("pointsto_objcont",&wrapper_rel_12_pointsto_objcont,false,true);
addRelation("pointsto_objcont.@info.1",&wrapper_rel_15_pointsto_objcont_info_1,false,false);
addRelation("pointsto_objcont.@info.10",&wrapper_rel_16_pointsto_objcont_info_10,false,false);
addRelation("pointsto_objcont.@info.100",&wrapper_rel_17_pointsto_objcont_info_100,false,false);
addRelation("pointsto_objcont.@info.11",&wrapper_rel_18_pointsto_objcont_info_11,false,false);
addRelation("pointsto_objcont.@info.12",&wrapper_rel_19_pointsto_objcont_info_12,false,false);
addRelation("pointsto_objcont.@info.13",&wrapper_rel_20_pointsto_objcont_info_13,false,false);
addRelation("pointsto_objcont.@info.14",&wrapper_rel_21_pointsto_objcont_info_14,false,false);
addRelation("pointsto_objcont.@info.15",&wrapper_rel_22_pointsto_objcont_info_15,false,false);
addRelation("pointsto_objcont.@info.16",&wrapper_rel_23_pointsto_objcont_info_16,false,false);
addRelation("pointsto_objcont.@info.17",&wrapper_rel_24_pointsto_objcont_info_17,false,false);
addRelation("pointsto_objcont.@info.18",&wrapper_rel_25_pointsto_objcont_info_18,false,false);
addRelation("pointsto_objcont.@info.19",&wrapper_rel_26_pointsto_objcont_info_19,false,false);
addRelation("pointsto_objcont.@info.2",&wrapper_rel_27_pointsto_objcont_info_2,false,false);
addRelation("pointsto_objcont.@info.20",&wrapper_rel_28_pointsto_objcont_info_20,false,false);
addRelation("pointsto_objcont.@info.21",&wrapper_rel_29_pointsto_objcont_info_21,false,false);
addRelation("pointsto_objcont.@info.22",&wrapper_rel_30_pointsto_objcont_info_22,false,false);
addRelation("pointsto_objcont.@info.23",&wrapper_rel_31_pointsto_objcont_info_23,false,false);
addRelation("pointsto_objcont.@info.24",&wrapper_rel_32_pointsto_objcont_info_24,false,false);
addRelation("pointsto_objcont.@info.25",&wrapper_rel_33_pointsto_objcont_info_25,false,false);
addRelation("pointsto_objcont.@info.26",&wrapper_rel_34_pointsto_objcont_info_26,false,false);
addRelation("pointsto_objcont.@info.27",&wrapper_rel_35_pointsto_objcont_info_27,false,false);
addRelation("pointsto_objcont.@info.28",&wrapper_rel_36_pointsto_objcont_info_28,false,false);
addRelation("pointsto_objcont.@info.29",&wrapper_rel_37_pointsto_objcont_info_29,false,false);
addRelation("pointsto_objcont.@info.3",&wrapper_rel_38_pointsto_objcont_info_3,false,false);
addRelation("pointsto_objcont.@info.30",&wrapper_rel_39_pointsto_objcont_info_30,false,false);
addRelation("pointsto_objcont.@info.31",&wrapper_rel_40_pointsto_objcont_info_31,false,false);
addRelation("pointsto_objcont.@info.32",&wrapper_rel_41_pointsto_objcont_info_32,false,false);
addRelation("pointsto_objcont.@info.33",&wrapper_rel_42_pointsto_objcont_info_33,false,false);
addRelation("pointsto_objcont.@info.34",&wrapper_rel_43_pointsto_objcont_info_34,false,false);
addRelation("pointsto_objcont.@info.35",&wrapper_rel_44_pointsto_objcont_info_35,false,false);
addRelation("pointsto_objcont.@info.36",&wrapper_rel_45_pointsto_objcont_info_36,false,false);
addRelation("pointsto_objcont.@info.37",&wrapper_rel_46_pointsto_objcont_info_37,false,false);
addRelation("pointsto_objcont.@info.38",&wrapper_rel_47_pointsto_objcont_info_38,false,false);
addRelation("pointsto_objcont.@info.39",&wrapper_rel_48_pointsto_objcont_info_39,false,false);
addRelation("pointsto_objcont.@info.4",&wrapper_rel_49_pointsto_objcont_info_4,false,false);
addRelation("pointsto_objcont.@info.40",&wrapper_rel_50_pointsto_objcont_info_40,false,false);
addRelation("pointsto_objcont.@info.41",&wrapper_rel_51_pointsto_objcont_info_41,false,false);
addRelation("pointsto_objcont.@info.42",&wrapper_rel_52_pointsto_objcont_info_42,false,false);
addRelation("pointsto_objcont.@info.43",&wrapper_rel_53_pointsto_objcont_info_43,false,false);
addRelation("pointsto_objcont.@info.44",&wrapper_rel_54_pointsto_objcont_info_44,false,false);
addRelation("pointsto_objcont.@info.45",&wrapper_rel_55_pointsto_objcont_info_45,false,false);
addRelation("pointsto_objcont.@info.46",&wrapper_rel_56_pointsto_objcont_info_46,false,false);
addRelation("pointsto_objcont.@info.47",&wrapper_rel_57_pointsto_objcont_info_47,false,false);
addRelation("pointsto_objcont.@info.48",&wrapper_rel_58_pointsto_objcont_info_48,false,false);
addRelation("pointsto_objcont.@info.49",&wrapper_rel_59_pointsto_objcont_info_49,false,false);
addRelation("pointsto_objcont.@info.5",&wrapper_rel_60_pointsto_objcont_info_5,false,false);
addRelation("pointsto_objcont.@info.50",&wrapper_rel_61_pointsto_objcont_info_50,false,false);
addRelation("pointsto_objcont.@info.51",&wrapper_rel_62_pointsto_objcont_info_51,false,false);
addRelation("pointsto_objcont.@info.52",&wrapper_rel_63_pointsto_objcont_info_52,false,false);
addRelation("pointsto_objcont.@info.53",&wrapper_rel_64_pointsto_objcont_info_53,false,false);
addRelation("pointsto_objcont.@info.54",&wrapper_rel_65_pointsto_objcont_info_54,false,false);
addRelation("pointsto_objcont.@info.55",&wrapper_rel_66_pointsto_objcont_info_55,false,false);
addRelation("pointsto_objcont.@info.56",&wrapper_rel_67_pointsto_objcont_info_56,false,false);
addRelation("pointsto_objcont.@info.57",&wrapper_rel_68_pointsto_objcont_info_57,false,false);
addRelation("pointsto_objcont.@info.58",&wrapper_rel_69_pointsto_objcont_info_58,false,false);
addRelation("pointsto_objcont.@info.59",&wrapper_rel_70_pointsto_objcont_info_59,false,false);
addRelation("pointsto_objcont.@info.6",&wrapper_rel_71_pointsto_objcont_info_6,false,false);
addRelation("pointsto_objcont.@info.60",&wrapper_rel_72_pointsto_objcont_info_60,false,false);
addRelation("pointsto_objcont.@info.61",&wrapper_rel_73_pointsto_objcont_info_61,false,false);
addRelation("pointsto_objcont.@info.62",&wrapper_rel_74_pointsto_objcont_info_62,false,false);
addRelation("pointsto_objcont.@info.63",&wrapper_rel_75_pointsto_objcont_info_63,false,false);
addRelation("pointsto_objcont.@info.64",&wrapper_rel_76_pointsto_objcont_info_64,false,false);
addRelation("pointsto_objcont.@info.65",&wrapper_rel_77_pointsto_objcont_info_65,false,false);
addRelation("pointsto_objcont.@info.66",&wrapper_rel_78_pointsto_objcont_info_66,false,false);
addRelation("pointsto_objcont.@info.67",&wrapper_rel_79_pointsto_objcont_info_67,false,false);
addRelation("pointsto_objcont.@info.68",&wrapper_rel_80_pointsto_objcont_info_68,false,false);
addRelation("pointsto_objcont.@info.69",&wrapper_rel_81_pointsto_objcont_info_69,false,false);
addRelation("pointsto_objcont.@info.7",&wrapper_rel_82_pointsto_objcont_info_7,false,false);
addRelation("pointsto_objcont.@info.70",&wrapper_rel_83_pointsto_objcont_info_70,false,false);
addRelation("pointsto_objcont.@info.71",&wrapper_rel_84_pointsto_objcont_info_71,false,false);
addRelation("pointsto_objcont.@info.72",&wrapper_rel_85_pointsto_objcont_info_72,false,false);
addRelation("pointsto_objcont.@info.73",&wrapper_rel_86_pointsto_objcont_info_73,false,false);
addRelation("pointsto_objcont.@info.74",&wrapper_rel_87_pointsto_objcont_info_74,false,false);
addRelation("pointsto_objcont.@info.75",&wrapper_rel_88_pointsto_objcont_info_75,false,false);
addRelation("pointsto_objcont.@info.76",&wrapper_rel_89_pointsto_objcont_info_76,false,false);
addRelation("pointsto_objcont.@info.77",&wrapper_rel_90_pointsto_objcont_info_77,false,false);
addRelation("pointsto_objcont.@info.78",&wrapper_rel_91_pointsto_objcont_info_78,false,false);
addRelation("pointsto_objcont.@info.79",&wrapper_rel_92_pointsto_objcont_info_79,false,false);
addRelation("pointsto_objcont.@info.8",&wrapper_rel_93_pointsto_objcont_info_8,false,false);
addRelation("pointsto_objcont.@info.80",&wrapper_rel_94_pointsto_objcont_info_80,false,false);
addRelation("pointsto_objcont.@info.81",&wrapper_rel_95_pointsto_objcont_info_81,false,false);
addRelation("pointsto_objcont.@info.82",&wrapper_rel_96_pointsto_objcont_info_82,false,false);
addRelation("pointsto_objcont.@info.83",&wrapper_rel_97_pointsto_objcont_info_83,false,false);
addRelation("pointsto_objcont.@info.84",&wrapper_rel_98_pointsto_objcont_info_84,false,false);
addRelation("pointsto_objcont.@info.85",&wrapper_rel_99_pointsto_objcont_info_85,false,false);
addRelation("pointsto_objcont.@info.86",&wrapper_rel_100_pointsto_objcont_info_86,false,false);
addRelation("pointsto_objcont.@info.87",&wrapper_rel_101_pointsto_objcont_info_87,false,false);
addRelation("pointsto_objcont.@info.88",&wrapper_rel_102_pointsto_objcont_info_88,false,false);
addRelation("pointsto_objcont.@info.89",&wrapper_rel_103_pointsto_objcont_info_89,false,false);
addRelation("pointsto_objcont.@info.9",&wrapper_rel_104_pointsto_objcont_info_9,false,false);
addRelation("pointsto_objcont.@info.90",&wrapper_rel_105_pointsto_objcont_info_90,false,false);
addRelation("pointsto_objcont.@info.91",&wrapper_rel_106_pointsto_objcont_info_91,false,false);
addRelation("pointsto_objcont.@info.92",&wrapper_rel_107_pointsto_objcont_info_92,false,false);
addRelation("pointsto_objcont.@info.93",&wrapper_rel_108_pointsto_objcont_info_93,false,false);
addRelation("pointsto_objcont.@info.94",&wrapper_rel_109_pointsto_objcont_info_94,false,false);
addRelation("pointsto_objcont.@info.95",&wrapper_rel_110_pointsto_objcont_info_95,false,false);
addRelation("pointsto_objcont.@info.96",&wrapper_rel_111_pointsto_objcont_info_96,false,false);
addRelation("pointsto_objcont.@info.97",&wrapper_rel_112_pointsto_objcont_info_97,false,false);
addRelation("pointsto_objcont.@info.98",&wrapper_rel_113_pointsto_objcont_info_98,false,false);
addRelation("pointsto_objcont.@info.99",&wrapper_rel_114_pointsto_objcont_info_99,false,false);
}
~Sf_souffle_small() {
}
private:
void runFunction(std::string inputDirectory = ".", std::string outputDirectory = ".", size_t stratumIndex = (size_t) -1, bool performIO = false) {
SignalHandler::instance()->set();
std::atomic<size_t> iter(0);

// -- query evaluation --
/* BEGIN STRATUM 0 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./Rule.facts"},{"name","Rule"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({0,0,0}), symTable, ioDirectives, true)->readAll(*rel_1_Rule);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 0 */
/* BEGIN STRATUM 1 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./actual.facts"},{"name","actual"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_2_actual);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 1 */
/* BEGIN STRATUM 2 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./assign.facts"},{"name","assign"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_3_assign);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 2 */
/* BEGIN STRATUM 3 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./enclosing_type.facts"},{"name","enclosing_type"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_4_enclosing_type);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 3 */
/* BEGIN STRATUM 4 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1\tv2"},{"filename","./heappointsto.csv"},{"name","heappointsto"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_5_heappointsto);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}();
/* END STRATUM 4 */
/* BEGIN STRATUM 5 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./invocation.facts"},{"name","invocation"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_6_invocation);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 5 */
/* BEGIN STRATUM 6 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./load.facts"},{"name","load"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_7_load);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 6 */
/* BEGIN STRATUM 7 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./points_initial.facts"},{"name","points_initial"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_8_points_initial);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 7 */
/* BEGIN STRATUM 8 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1\tv2\tv3"},{"filename","./pointsto.csv"},{"name","pointsto"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_9_pointsto);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}();
/* END STRATUM 8 */
/* BEGIN STRATUM 9 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./receiver_formal.facts"},{"name","receiver_formal"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_10_receiver_formal);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 9 */
/* BEGIN STRATUM 10 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./store.facts"},{"name","store"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_11_store);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 10 */
/* BEGIN STRATUM 11 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v2,v1,1,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(10,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   receiver_formal(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [40:1-40:91])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(10),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_10_receiver_formal->equalRange_1(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(1)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v2,v0,v1,2,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(6,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   store(v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [41:1-41:84])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_11_store->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_11_store_op_ctxt,rel_11_store->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(6),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],0,0,0}});
auto range = rel_11_store->equalRange_3(key,READ_OP_CONTEXT(rel_11_store_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(2)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,3,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(11,_,@level_num_0),
   actual(v0,v1,v2,_,@level_num_1),
   points_initial(v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [42:1-42:86])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_2_actual->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(11),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_2_actual) {
const Tuple<RamDomain,4> key({{env1[0],env1[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(3)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v1,v0,v2,5,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(0,_,@level_num_0),
   load(v0,v1,v2,_,@level_num_1),
   points_initial(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [44:1-44:83])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_7_load->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(0),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_7_load) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(5)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v2,v0,v1,7,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(8,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   receiver_formal(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [46:1-46:90])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(8),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_10_receiver_formal->equalRange_1(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(7)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v2,v1,8,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(9,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   points_initial(v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [47:1-47:89])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(9),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_8_points_initial->equalRange_2(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(8)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v2,v1,10,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   store(v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [49:1-49:84])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_11_store->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_11_store_op_ctxt,rel_11_store->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],0,0,0}});
auto range = rel_11_store->equalRange_3(key,READ_OP_CONTEXT(rel_11_store_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(10)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,11,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(3,_,@level_num_0),
   load(v0,v1,v2,_,@level_num_1),
   points_initial(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [50:1-50:83])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_7_load->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(3),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_7_load) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(11)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,13,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(69300,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v2,v0,v1,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [52:1-52:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(69300),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_30(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(13)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,14,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(56630,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v2,v2,v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [53:1-53:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(56630),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_46(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(14)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,15,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(34295,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v1,v0,v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [54:1-54:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(34295),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_25(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[1]) == (env2[5]))) && (((env2[1]) == (env2[2]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(15)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,16,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(19791,_,@level_num_0),
   enclosing_type(v2,v0,_,@level_num_1),
   actual(v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [55:1-55:89])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_2_actual->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(19791),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,5> key({{env1[1],0,env1[0],0,0}});
auto range = rel_2_actual->equalRange_5(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(16)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,17,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(48017,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [56:1-56:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(48017),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(17)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,18,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(13813,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   load(v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [57:1-57:87])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_7_load->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(13813),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,5> key({{env1[0],env1[1],0,0,0}});
auto range = rel_7_load->equalRange_3(key,READ_OP_CONTEXT(rel_7_load_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(18)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,19,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(28791,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v0,v2,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [58:1-58:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(28791),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],0,env1[0],0,env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_21(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[1]) == (env2[5]))) && (((env2[1]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(19)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,20,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(36691,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [59:1-59:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(36691),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(20)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,21,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(15217,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   invocation(v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [60:1-60:89])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_6_invocation->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_6_invocation_op_ctxt,rel_6_invocation->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(15217),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_invocation->equalRange_1(key,READ_OP_CONTEXT(rel_6_invocation_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(21)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,22,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(27895,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v1,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [61:1-61:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(27895),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_51(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(22)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,23,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(35837,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [62:1-62:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(35837),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(23)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,24,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(86626,_,@level_num_0),
   enclosing_type(v1,v2,_,@level_num_1),
   assign(v1,v0,v2,v2,v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [63:1-63:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(86626),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_29(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(24)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,25,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(22946,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v0,v1,v1,v0,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [64:1-64:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(22946),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],env1[0],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[4]),static_cast<RamDomain>(RamDomain(25)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,26,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(84399,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v2,v0,v1,v2,v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [65:1-65:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(84399),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],0,env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(26)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,27,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(18672,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   actual(v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [66:1-66:89])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_2_actual->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(18672),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,5> key({{env1[1],0,env1[0],0,0}});
auto range = rel_2_actual->equalRange_5(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(27)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,28,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(73858,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v2,v0,v1,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [67:1-67:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(73858),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],env1[0],env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_30(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(28)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,29,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(28989,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [68:1-68:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(28989),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(29)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,30,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(78609,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [69:1-69:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(78609),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(30)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,31,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(35569,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v2,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [70:1-70:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(35569),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_21(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[1]) == (env2[5]))) && (((env2[1]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(31)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,32,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(62907,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v1,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [71:1-71:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(62907),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_51(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(32)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,33,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(40656,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v2,v1,v0,v2,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [72:1-72:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40656),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],0,env1[0],env1[1],env1[1],0,0}});
auto range = rel_3_assign->equalRange_58(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[2]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(33)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,34,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(19390,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   actual(v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [73:1-73:89])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_2_actual->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(19390),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],0,0,0}});
auto range = rel_2_actual->equalRange_3(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(34)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,35,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(41025,_,@level_num_0),
   enclosing_type(v2,v0,_,@level_num_1),
   assign(v0,v2,v0,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [74:1-74:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(41025),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],env1[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[4]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(35)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,36,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(36249,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [75:1-75:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(36249),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(36)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,37,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(62351,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v2,v0,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [76:1-76:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(62351),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_22(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[0]) == (env2[5]))) && (((env2[0]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(37)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,38,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(2567,_,@level_num_0),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [77:1-77:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2567),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[3]))) && (((env1[1]) == (env1[4]))))) && (((env1[2]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(38)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,39,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(40179,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v1,v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [78:1-78:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40179),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_21(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[1]) == (env2[5]))) && (((env2[1]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(39)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,40,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(59120,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [79:1-79:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(59120),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(40)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,41,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(78420,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v1,v0,v2,v2,v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [80:1-80:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(78420),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],0,0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_51(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(41)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,42,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(64858,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [81:1-81:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(64858),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(42)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,43,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(28441,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [82:1-82:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(28441),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_53(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(43)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,44,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(47932,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [83:1-83:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(47932),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(44)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,45,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(40777,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v2,v2,v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [84:1-84:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40777),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_46(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(45)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,46,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(38959,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [85:1-85:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(38959),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_53(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(46)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,47,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(52193,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v2,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [86:1-86:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(52193),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_54(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(47)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,48,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(5063,_,@level_num_0),
   assign(v1,v0,v2,v1,v0,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [87:1-87:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(5063),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[1]) == (env1[4]))) && (((env1[0]) == (env1[3]))))) && (((env1[2]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(48)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,49,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(63698,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [88:1-88:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(63698),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_53(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(49)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,50,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(53306,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v2,v1,v0,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [89:1-89:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(53306),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],0,env1[0],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(50)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,51,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(64812,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v0,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [90:1-90:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(64812),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],env1[0],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[4]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(51)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,52,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(79085,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v2,v1,v0,v2,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [91:1-91:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(79085),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,0,0,0}});
auto range = rel_3_assign->equalRange_13(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[1]) == (env2[5]))) && (((env2[1]) == (env2[4]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(52)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,53,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(35495,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v0,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [92:1-92:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(35495),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[0],env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[3]),static_cast<RamDomain>(RamDomain(53)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,54,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(43610,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v1,v0,v2,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [93:1-93:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(43610),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(54)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,55,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(33581,_,@level_num_0),
   enclosing_type(v2,v1,_,@level_num_1),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [94:1-94:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(33581),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],env1[0],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_46(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(55)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,56,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(88964,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v2,v0,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [95:1-95:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(88964),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],env1[0],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_54(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(56)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,57,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(41537,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v2,v1,v0,v2,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [96:1-96:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(41537),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,0,0,0}});
auto range = rel_3_assign->equalRange_13(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[1]) == (env2[5]))) && (((env2[1]) == (env2[4]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(57)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,58,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(6139,_,@level_num_0),
   assign(v0,v2,v1,v1,v0,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [97:1-97:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(6139),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[4]))) && (((env1[2]) == (env1[3]))))) && (((env1[1]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(58)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,59,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(66026,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v0,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [98:1-98:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(66026),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[0],0,env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(59)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,60,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(78281,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v0,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [99:1-99:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(78281),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[0],0,env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(60)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,61,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(34234,_,@level_num_0),
   enclosing_type(v1,v2,_,@level_num_1),
   assign(v0,v2,v0,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [100:1-100:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(34234),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_26(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[0]) == (env2[5]))) && (((env2[0]) == (env2[2]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(61)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,62,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(48347,_,@level_num_0),
   enclosing_type(v1,v2,_,@level_num_1),
   assign(v0,v2,v1,v2,v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [101:1-101:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(48347),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],env1[0],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_46(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(62)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,63,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(36826,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [102:1-102:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(36826),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(63)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,64,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(19964,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v1,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [103:1-103:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(19964),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_51(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(64)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,65,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(70583,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v2,v2,v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [104:1-104:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(70583),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_30(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(65)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,66,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(9423,_,@level_num_0),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [105:1-105:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(9423),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[3]))) && (((env1[1]) == (env1[4]))))) && (((env1[2]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(66)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,67,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(59394,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v2,v1,v0,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [106:1-106:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(59394),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],0,env1[0],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_58(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[2]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(67)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,68,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(8227,_,@level_num_0),
   assign(v0,v0,v1,v1,v0,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [107:1-107:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(8227),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[1]))) && (((env1[0]) == (env1[4]))))) && (((env1[2]) == (env1[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(env1[5]),static_cast<RamDomain>(RamDomain(68)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,69,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(22304,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v1,v0,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [108:1-108:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(22304),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,0,env1[0],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_44(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[0]) == (env2[4]))) && (((env2[0]) == (env2[1]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(69)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,70,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(21947,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [109:1-109:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(21947),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_53(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(70)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,71,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(82029,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [110:1-110:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(82029),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(71)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,72,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(79077,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v1,v0,v2,v2,v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [111:1-111:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(79077),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_51(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(72)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,73,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(4839,_,@level_num_0),
   assign(v0,v0,v1,v2,v2,v0,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [112:1-112:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(4839),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[1]))) && (((env1[0]) == (env1[5]))))) && (((env1[3]) == (env1[4]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(env1[3]),static_cast<RamDomain>(RamDomain(73)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,74,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(20846,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v1,v2,v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [113:1-113:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(20846),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(74)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,75,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(10458,_,@level_num_0),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [114:1-114:77])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(10458),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[3]))) && (((env1[1]) == (env1[4]))))) && (((env1[2]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(75)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,76,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(25015,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [115:1-115:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(25015),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(76)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,77,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(65996,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [116:1-116:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(65996),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_53(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(77)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,78,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(34638,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v2,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [117:1-117:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(34638),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(78)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,79,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(27604,_,@level_num_0),
   enclosing_type(v2,v0,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [118:1-118:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(27604),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],0,env1[0],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(79)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,80,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(67769,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v1,v0,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [119:1-119:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(67769),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,0,env1[0],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_57(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[2]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(80)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,81,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(63016,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [120:1-120:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(63016),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(81)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,82,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(42257,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v0,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [121:1-121:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(42257),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[0],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_54(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(82)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,83,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(24992,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v1,v0,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [122:1-122:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(24992),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(83)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,84,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(32795,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v2,v2,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [123:1-123:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(32795),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],env1[1],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_62(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(84)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,85,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(3548,_,@level_num_0),
   assign(v0,v0,v1,v2,v1,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [124:1-124:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(3548),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[1]))) && (((env1[2]) == (env1[4]))))) && (((env1[3]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(env1[3]),static_cast<RamDomain>(RamDomain(85)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,86,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(41694,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [125:1-125:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(41694),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(86)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,87,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(64161,_,@level_num_0),
   enclosing_type(v2,v0,_,@level_num_1),
   assign(v0,v2,v0,v1,v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [126:1-126:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(64161),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],env1[1],0,env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[3]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(87)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,88,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(14576,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   load(v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [127:1-127:87])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_7_load->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(14576),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,5> key({{env1[0],env1[1],0,0,0}});
auto range = rel_7_load->equalRange_3(key,READ_OP_CONTEXT(rel_7_load_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(88)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,89,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(43687,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v0,v2,v2,v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [128:1-128:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(43687),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_30(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(89)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,90,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(7005,_,@level_num_0),
   assign(v0,v1,v2,v1,v0,v2,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [129:1-129:76])_");
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(7005),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_assign) {
if( ((((((env1[0]) == (env1[4]))) && (((env1[1]) == (env1[3]))))) && (((env1[2]) == (env1[5]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(90)),static_cast<RamDomain>((std::max({env0[2], env1[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,91,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(22493,_,@level_num_0),
   enclosing_type(v1,v2,_,@level_num_1),
   assign(v0,v1,v1,v0,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [130:1-130:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(22493),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[0],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_22(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[0]) == (env2[5]))) && (((env2[0]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(91)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,92,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(40917,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v2,v0,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [131:1-131:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40917),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],env1[0],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_54(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[0]) == (env2[3]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(92)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,93,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(67708,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [132:1-132:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(67708),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(93)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,94,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(90086,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [133:1-133:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(90086),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(94)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,95,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(47927,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v1,v2,v0,v1,v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [134:1-134:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(47927),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[1],env1[0],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_22(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[0]) == (env2[5]))) && (((env2[0]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(95)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,96,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(86220,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v2,v1,v0,v2,v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [135:1-135:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(86220),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{0,env1[0],env1[1],0,0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_38(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[0]) == (env2[4]))) && (((env2[0]) == (env2[3]))))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(96)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,97,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(87963,_,@level_num_0),
   enclosing_type(v0,v1,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [136:1-136:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(87963),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[5]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(97)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,98,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(20685,_,@level_num_0),
   enclosing_type(v0,v2,_,@level_num_1),
   assign(v0,v1,v2,v0,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [137:1-137:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(20685),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[1]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(98)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,99,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(39726,_,@level_num_0),
   enclosing_type(v1,v0,_,@level_num_1),
   assign(v0,v1,v2,v1,v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [138:1-138:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(39726),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],0,env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_43(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[2]) == (env2[4]))) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(RamDomain(99)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,100,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(73695,_,@level_num_0),
   enclosing_type(v2,v1,_,@level_num_1),
   assign(v2,v0,v1,v2,v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [139:1-139:101])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(73695),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_enclosing_type) {
const Tuple<RamDomain,8> key({{env1[0],0,env1[1],env1[0],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_61(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(100)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[7], })) + (RamDomain(1)))}});
rel_12_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
}
}
}
}
}
rel_13_delta_pointsto_objcont->insertAll(*rel_12_pointsto_objcont);
iter = 0;
for(;;) {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v1,v2,4,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(2,_,@level_num_0),
   pointsto_objcont(v0,v1,v2,_,@level_num_1),
   receiver_formal(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [43:1-43:96])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_13_delta_pointsto_objcont->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
CREATE_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt,rel_14_new_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_13_delta_pointsto_objcont_op_ctxt,rel_13_delta_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_13_delta_pointsto_objcont) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_10_receiver_formal->equalRange_3(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{env1[0],env1[1],env1[2],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[4] <= (std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(4)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1)))}});
rel_14_new_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v1,v0,v2,6,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(4,_,@level_num_0),
   pointsto_objcont(v0,v1,v2,_,@level_num_1),
   receiver_formal(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [45:1-45:96])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_13_delta_pointsto_objcont->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
CREATE_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt,rel_14_new_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_13_delta_pointsto_objcont_op_ctxt,rel_13_delta_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(4),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_13_delta_pointsto_objcont) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_10_receiver_formal->equalRange_3(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{env1[1],env1[0],env1[2],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[4] <= (std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[2]),static_cast<RamDomain>(RamDomain(6)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[4], }), env2[3], })) + (RamDomain(1)))}});
rel_14_new_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v2,v0,v1,9,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(5,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   pointsto_objcont(v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [48:1-48:95])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_13_delta_pointsto_objcont->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt,rel_14_new_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_13_delta_pointsto_objcont_op_ctxt,rel_13_delta_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(5),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],0,0,0}});
auto range = rel_13_delta_pointsto_objcont->equalRange_3(key,READ_OP_CONTEXT(rel_13_delta_pointsto_objcont_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{env2[2],env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[4] <= (std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(9)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_14_new_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(pointsto_objcont(v0,v2,v1,12,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(7,_,@level_num_0),
   points_initial(v0,v1,_,@level_num_1),
   pointsto_objcont(v1,v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/1-object-1-type_100/rules.small.dl [51:1-51:95])_");
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_13_delta_pointsto_objcont->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt,rel_14_new_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
CREATE_OP_CONTEXT(rel_13_delta_pointsto_objcont_op_ctxt,rel_13_delta_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(7),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_8_points_initial) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],0,0,0}});
auto range = rel_13_delta_pointsto_objcont->equalRange_3(key,READ_OP_CONTEXT(rel_13_delta_pointsto_objcont_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{env1[0],env2[2],env1[1],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[4] <= (std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,5> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[2]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(12)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[4], })) + (RamDomain(1)))}});
rel_14_new_pointsto_objcont->insert(tuple,READ_OP_CONTEXT(rel_14_new_pointsto_objcont_op_ctxt));
}
}
}
}
}
}
if(rel_14_new_pointsto_objcont->empty()) break;
rel_12_pointsto_objcont->insertAll(*rel_14_new_pointsto_objcont);
std::swap(rel_13_delta_pointsto_objcont, rel_14_new_pointsto_objcont);
rel_14_new_pointsto_objcont->purge();
iter++;
}
iter = 0;
if (!isHintsProfilingEnabled()) rel_13_delta_pointsto_objcont->purge();
if (!isHintsProfilingEnabled()) rel_14_new_pointsto_objcont->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1\tv2"},{"filename","./pointsto_objcont.csv"},{"name","pointsto_objcont"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_12_pointsto_objcont);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}();
/* END STRATUM 11 */
/* BEGIN STRATUM 12 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.1(1,"v0,v2,v1","Rule","points_initial,v0,v1","receiver_formal,v1,v2","pointsto_objcont(v0,v2,v1) :- 
   Rule(10),
   points_initial(v0,v1),
   receiver_formal(v1,v2).").
in file  [0:0-0:0])_");
rel_15_pointsto_objcont_info_1->insert(RamDomain(1),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(3),RamDomain(4));
}();
/* END STRATUM 12 */
/* BEGIN STRATUM 13 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.10(10,"v0,v2,v1","Rule","points_initial,v0,v1","store,v1,v0,v2","pointsto_objcont(v0,v2,v1) :- 
   Rule(1),
   points_initial(v0,v1),
   store(v1,v0,v2).").
in file  [0:0-0:0])_");
rel_16_pointsto_objcont_info_10->insert(RamDomain(10),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(6),RamDomain(25));
}();
/* END STRATUM 13 */
/* BEGIN STRATUM 14 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.100(100,"v0,v1,v2","Rule","enclosing_type,v2,v1","assign,v2,v0,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(73695),
   enclosing_type(v2,v1),
   assign(v2,v0,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_17_pointsto_objcont_info_100->insert(RamDomain(100),RamDomain(8),RamDomain(1),RamDomain(97),RamDomain(69),RamDomain(157));
}();
/* END STRATUM 14 */
/* BEGIN STRATUM 15 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.11(11,"v0,v1,v2","Rule","load,v0,v1,v2","points_initial,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(3),
   load(v0,v1,v2),
   points_initial(v2,v0).").
in file  [0:0-0:0])_");
rel_18_pointsto_objcont_info_11->insert(RamDomain(11),RamDomain(8),RamDomain(1),RamDomain(16),RamDomain(17),RamDomain(26));
}();
/* END STRATUM 15 */
/* BEGIN STRATUM 16 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.12(12,"v0,v2,v1","Rule","points_initial,v0,v1","pointsto_objcont,v1,v0,v2","pointsto_objcont(v0,v2,v1) :- 
   Rule(7),
   points_initial(v0,v1),
   pointsto_objcont(v1,v0,v2).").
in file  [0:0-0:0])_");
rel_19_pointsto_objcont_info_12->insert(RamDomain(12),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(23),RamDomain(27));
}();
/* END STRATUM 16 */
/* BEGIN STRATUM 17 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.13(13,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v2,v0,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(69300),
   enclosing_type(v0,v1),
   assign(v2,v0,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_20_pointsto_objcont_info_13->insert(RamDomain(13),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(29),RamDomain(30));
}();
/* END STRATUM 17 */
/* BEGIN STRATUM 18 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.14(14,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v2,v2,v1,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(56630),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v1,v0).").
in file  [0:0-0:0])_");
rel_21_pointsto_objcont_info_14->insert(RamDomain(14),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(32),RamDomain(33));
}();
/* END STRATUM 18 */
/* BEGIN STRATUM 19 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.15(15,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v1,v0,v2,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(34295),
   enclosing_type(v0,v2),
   assign(v0,v1,v1,v0,v2,v1).").
in file  [0:0-0:0])_");
rel_22_pointsto_objcont_info_15->insert(RamDomain(15),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(34),RamDomain(35));
}();
/* END STRATUM 19 */
/* BEGIN STRATUM 20 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.16(16,"v0,v1,v2","Rule","enclosing_type,v2,v0","actual,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(19791),
   enclosing_type(v2,v0),
   actual(v0,v1,v2).").
in file  [0:0-0:0])_");
rel_23_pointsto_objcont_info_16->insert(RamDomain(16),RamDomain(8),RamDomain(1),RamDomain(36),RamDomain(9),RamDomain(37));
}();
/* END STRATUM 20 */
/* BEGIN STRATUM 21 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.17(17,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(48017),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_24_pointsto_objcont_info_17->insert(RamDomain(17),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(39));
}();
/* END STRATUM 21 */
/* BEGIN STRATUM 22 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.18(18,"v0,v1,v2","Rule","enclosing_type,v0,v1","load,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(13813),
   enclosing_type(v0,v1),
   load(v0,v1,v2).").
in file  [0:0-0:0])_");
rel_25_pointsto_objcont_info_18->insert(RamDomain(18),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(16),RamDomain(40));
}();
/* END STRATUM 22 */
/* BEGIN STRATUM 23 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.19(19,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v0,v2,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(28791),
   enclosing_type(v1,v0),
   assign(v0,v2,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_26_pointsto_objcont_info_19->insert(RamDomain(19),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(42),RamDomain(43));
}();
/* END STRATUM 23 */
/* BEGIN STRATUM 24 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.2(2,"v2,v0,v1","Rule","points_initial,v0,v1","store,v1,v0,v2","pointsto_objcont(v2,v0,v1) :- 
   Rule(6),
   points_initial(v0,v1),
   store(v1,v0,v2).").
in file  [0:0-0:0])_");
rel_27_pointsto_objcont_info_2->insert(RamDomain(2),RamDomain(5),RamDomain(1),RamDomain(2),RamDomain(6),RamDomain(7));
}();
/* END STRATUM 24 */
/* BEGIN STRATUM 25 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.20(20,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(36691),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_28_pointsto_objcont_info_20->insert(RamDomain(20),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(38),RamDomain(44));
}();
/* END STRATUM 25 */
/* BEGIN STRATUM 26 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.21(21,"v0,v1,v2","Rule","enclosing_type,v0,v1","invocation,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(15217),
   enclosing_type(v0,v1),
   invocation(v0,v2).").
in file  [0:0-0:0])_");
rel_29_pointsto_objcont_info_21->insert(RamDomain(21),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(45),RamDomain(46));
}();
/* END STRATUM 26 */
/* BEGIN STRATUM 27 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.22(22,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(27895),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_30_pointsto_objcont_info_22->insert(RamDomain(22),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(47),RamDomain(48));
}();
/* END STRATUM 27 */
/* BEGIN STRATUM 28 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.23(23,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(35837),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_31_pointsto_objcont_info_23->insert(RamDomain(23),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(49));
}();
/* END STRATUM 28 */
/* BEGIN STRATUM 29 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.24(24,"v0,v1,v2","Rule","enclosing_type,v1,v2","assign,v1,v0,v2,v2,v1,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(86626),
   enclosing_type(v1,v2),
   assign(v1,v0,v2,v2,v1,v0).").
in file  [0:0-0:0])_");
rel_32_pointsto_objcont_info_24->insert(RamDomain(24),RamDomain(8),RamDomain(1),RamDomain(50),RamDomain(32),RamDomain(51));
}();
/* END STRATUM 29 */
/* BEGIN STRATUM 30 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.25(25,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v0,v1,v1,v0,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(22946),
   enclosing_type(v1,v0),
   assign(v0,v1,v1,v0,v2,v0).").
in file  [0:0-0:0])_");
rel_33_pointsto_objcont_info_25->insert(RamDomain(25),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(52),RamDomain(53));
}();
/* END STRATUM 30 */
/* BEGIN STRATUM 31 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.26(26,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v2,v0,v1,v2,v1,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(84399),
   enclosing_type(v0,v2),
   assign(v2,v0,v1,v2,v1,v0).").
in file  [0:0-0:0])_");
rel_34_pointsto_objcont_info_26->insert(RamDomain(26),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(54),RamDomain(55));
}();
/* END STRATUM 31 */
/* BEGIN STRATUM 32 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.27(27,"v0,v1,v2","Rule","enclosing_type,v0,v1","actual,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(18672),
   enclosing_type(v0,v1),
   actual(v1,v2,v0).").
in file  [0:0-0:0])_");
rel_35_pointsto_objcont_info_27->insert(RamDomain(27),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(56),RamDomain(57));
}();
/* END STRATUM 32 */
/* BEGIN STRATUM 33 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.28(28,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v2,v0,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(73858),
   enclosing_type(v1,v0),
   assign(v2,v0,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_36_pointsto_objcont_info_28->insert(RamDomain(28),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(29),RamDomain(58));
}();
/* END STRATUM 33 */
/* BEGIN STRATUM 34 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.29(29,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(28989),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_37_pointsto_objcont_info_29->insert(RamDomain(29),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(59));
}();
/* END STRATUM 34 */
/* BEGIN STRATUM 35 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.3(3,"v0,v1,v2","Rule","actual,v0,v1,v2","points_initial,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(11),
   actual(v0,v1,v2),
   points_initial(v0,v2).").
in file  [0:0-0:0])_");
rel_38_pointsto_objcont_info_3->insert(RamDomain(3),RamDomain(8),RamDomain(1),RamDomain(9),RamDomain(10),RamDomain(11));
}();
/* END STRATUM 35 */
/* BEGIN STRATUM 36 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.30(30,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(78609),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_39_pointsto_objcont_info_30->insert(RamDomain(30),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(60));
}();
/* END STRATUM 36 */
/* BEGIN STRATUM 37 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.31(31,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v2,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(35569),
   enclosing_type(v0,v1),
   assign(v0,v2,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_40_pointsto_objcont_info_31->insert(RamDomain(31),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(42),RamDomain(61));
}();
/* END STRATUM 37 */
/* BEGIN STRATUM 38 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.32(32,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(62907),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_41_pointsto_objcont_info_32->insert(RamDomain(32),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(47),RamDomain(62));
}();
/* END STRATUM 38 */
/* BEGIN STRATUM 39 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.33(33,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v2,v1,v0,v2,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(40656),
   enclosing_type(v0,v2),
   assign(v1,v2,v1,v0,v2,v2).").
in file  [0:0-0:0])_");
rel_42_pointsto_objcont_info_33->insert(RamDomain(33),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(63),RamDomain(64));
}();
/* END STRATUM 39 */
/* BEGIN STRATUM 40 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.34(34,"v0,v1,v2","Rule","enclosing_type,v1,v0","actual,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(19390),
   enclosing_type(v1,v0),
   actual(v0,v1,v2).").
in file  [0:0-0:0])_");
rel_43_pointsto_objcont_info_34->insert(RamDomain(34),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(9),RamDomain(65));
}();
/* END STRATUM 40 */
/* BEGIN STRATUM 41 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.35(35,"v0,v1,v2","Rule","enclosing_type,v2,v0","assign,v0,v2,v0,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(41025),
   enclosing_type(v2,v0),
   assign(v0,v2,v0,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_44_pointsto_objcont_info_35->insert(RamDomain(35),RamDomain(8),RamDomain(1),RamDomain(36),RamDomain(66),RamDomain(67));
}();
/* END STRATUM 41 */
/* BEGIN STRATUM 42 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.36(36,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(36249),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_45_pointsto_objcont_info_36->insert(RamDomain(36),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(38),RamDomain(68));
}();
/* END STRATUM 42 */
/* BEGIN STRATUM 43 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.37(37,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v2,v0,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(62351),
   enclosing_type(v0,v1),
   assign(v2,v0,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_46_pointsto_objcont_info_37->insert(RamDomain(37),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(69),RamDomain(70));
}();
/* END STRATUM 43 */
/* BEGIN STRATUM 44 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.38(38,"v0,v1,v2","Rule","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(2567),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_47_pointsto_objcont_info_38->insert(RamDomain(38),RamDomain(8),RamDomain(1),RamDomain(38),RamDomain(71));
}();
/* END STRATUM 44 */
/* BEGIN STRATUM 45 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.39(39,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v1,v2,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(40179),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v2,v1).").
in file  [0:0-0:0])_");
rel_48_pointsto_objcont_info_39->insert(RamDomain(39),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(72),RamDomain(73));
}();
/* END STRATUM 45 */
/* BEGIN STRATUM 46 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.4(4,"v0,v1,v2","Rule","pointsto_objcont,v0,v1,v2","receiver_formal,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(2),
   pointsto_objcont(v0,v1,v2),
   receiver_formal(v2,v0).").
in file  [0:0-0:0])_");
rel_49_pointsto_objcont_info_4->insert(RamDomain(4),RamDomain(8),RamDomain(1),RamDomain(12),RamDomain(13),RamDomain(14));
}();
/* END STRATUM 46 */
/* BEGIN STRATUM 47 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.40(40,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(59120),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_50_pointsto_objcont_info_40->insert(RamDomain(40),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(74));
}();
/* END STRATUM 47 */
/* BEGIN STRATUM 48 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.41(41,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v1,v0,v2,v2,v0,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(78420),
   enclosing_type(v0,v1),
   assign(v1,v0,v2,v2,v0,v1).").
in file  [0:0-0:0])_");
rel_51_pointsto_objcont_info_41->insert(RamDomain(41),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(75),RamDomain(76));
}();
/* END STRATUM 48 */
/* BEGIN STRATUM 49 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.42(42,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(64858),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_52_pointsto_objcont_info_42->insert(RamDomain(42),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(77));
}();
/* END STRATUM 49 */
/* BEGIN STRATUM 50 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.43(43,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(28441),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_53_pointsto_objcont_info_43->insert(RamDomain(43),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(78),RamDomain(79));
}();
/* END STRATUM 50 */
/* BEGIN STRATUM 51 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.44(44,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(47932),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_54_pointsto_objcont_info_44->insert(RamDomain(44),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(80));
}();
/* END STRATUM 51 */
/* BEGIN STRATUM 52 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.45(45,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v2,v2,v1,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(40777),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v1,v0).").
in file  [0:0-0:0])_");
rel_55_pointsto_objcont_info_45->insert(RamDomain(45),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(32),RamDomain(81));
}();
/* END STRATUM 52 */
/* BEGIN STRATUM 53 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.46(46,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(38959),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_56_pointsto_objcont_info_46->insert(RamDomain(46),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(78),RamDomain(82));
}();
/* END STRATUM 53 */
/* BEGIN STRATUM 54 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.47(47,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v2,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(52193),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_57_pointsto_objcont_info_47->insert(RamDomain(47),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(83),RamDomain(84));
}();
/* END STRATUM 54 */
/* BEGIN STRATUM 55 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.48(48,"v0,v1,v2","Rule","assign,v1,v0,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(5063),
   assign(v1,v0,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_58_pointsto_objcont_info_48->insert(RamDomain(48),RamDomain(8),RamDomain(1),RamDomain(85),RamDomain(86));
}();
/* END STRATUM 55 */
/* BEGIN STRATUM 56 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.49(49,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(63698),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_59_pointsto_objcont_info_49->insert(RamDomain(49),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(87),RamDomain(88));
}();
/* END STRATUM 56 */
/* BEGIN STRATUM 57 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.5(5,"v1,v0,v2","Rule","load,v0,v1,v2","points_initial,v2,v0","pointsto_objcont(v1,v0,v2) :- 
   Rule(0),
   load(v0,v1,v2),
   points_initial(v2,v0).").
in file  [0:0-0:0])_");
rel_60_pointsto_objcont_info_5->insert(RamDomain(5),RamDomain(15),RamDomain(1),RamDomain(16),RamDomain(17),RamDomain(18));
}();
/* END STRATUM 57 */
/* BEGIN STRATUM 58 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.50(50,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v2,v1,v0,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(53306),
   enclosing_type(v0,v2),
   assign(v2,v1,v0,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_61_pointsto_objcont_info_50->insert(RamDomain(50),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(89),RamDomain(90));
}();
/* END STRATUM 58 */
/* BEGIN STRATUM 59 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.51(51,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v0,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(64812),
   enclosing_type(v0,v2),
   assign(v0,v2,v0,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_62_pointsto_objcont_info_51->insert(RamDomain(51),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(66),RamDomain(91));
}();
/* END STRATUM 59 */
/* BEGIN STRATUM 60 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.52(52,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v2,v1,v0,v2,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(79085),
   enclosing_type(v0,v1),
   assign(v0,v2,v1,v0,v2,v2).").
in file  [0:0-0:0])_");
rel_63_pointsto_objcont_info_52->insert(RamDomain(52),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(92),RamDomain(93));
}();
/* END STRATUM 60 */
/* BEGIN STRATUM 61 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.53(53,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v0,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(35495),
   enclosing_type(v0,v1),
   assign(v0,v0,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_64_pointsto_objcont_info_53->insert(RamDomain(53),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(94),RamDomain(95));
}();
/* END STRATUM 61 */
/* BEGIN STRATUM 62 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.54(54,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v1,v0,v2,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(43610),
   enclosing_type(v1,v0),
   assign(v1,v0,v2,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_65_pointsto_objcont_info_54->insert(RamDomain(54),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(83),RamDomain(96));
}();
/* END STRATUM 62 */
/* BEGIN STRATUM 63 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.55(55,"v0,v1,v2","Rule","enclosing_type,v2,v1","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(33581),
   enclosing_type(v2,v1),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_66_pointsto_objcont_info_55->insert(RamDomain(55),RamDomain(8),RamDomain(1),RamDomain(97),RamDomain(78),RamDomain(98));
}();
/* END STRATUM 63 */
/* BEGIN STRATUM 64 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.56(56,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v2,v0,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(88964),
   enclosing_type(v0,v2),
   assign(v1,v2,v0,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_67_pointsto_objcont_info_56->insert(RamDomain(56),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(99),RamDomain(100));
}();
/* END STRATUM 64 */
/* BEGIN STRATUM 65 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.57(57,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v2,v1,v0,v2,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(41537),
   enclosing_type(v0,v1),
   assign(v0,v2,v1,v0,v2,v2).").
in file  [0:0-0:0])_");
rel_68_pointsto_objcont_info_57->insert(RamDomain(57),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(92),RamDomain(101));
}();
/* END STRATUM 65 */
/* BEGIN STRATUM 66 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.58(58,"v0,v1,v2","Rule","assign,v0,v2,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(6139),
   assign(v0,v2,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_69_pointsto_objcont_info_58->insert(RamDomain(58),RamDomain(8),RamDomain(1),RamDomain(47),RamDomain(102));
}();
/* END STRATUM 66 */
/* BEGIN STRATUM 67 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.59(59,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v0,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(66026),
   enclosing_type(v0,v2),
   assign(v0,v0,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_70_pointsto_objcont_info_59->insert(RamDomain(59),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(94),RamDomain(103));
}();
/* END STRATUM 67 */
/* BEGIN STRATUM 68 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.6(6,"v1,v0,v2","Rule","pointsto_objcont,v0,v1,v2","receiver_formal,v2,v0","pointsto_objcont(v1,v0,v2) :- 
   Rule(4),
   pointsto_objcont(v0,v1,v2),
   receiver_formal(v2,v0).").
in file  [0:0-0:0])_");
rel_71_pointsto_objcont_info_6->insert(RamDomain(6),RamDomain(15),RamDomain(1),RamDomain(12),RamDomain(13),RamDomain(19));
}();
/* END STRATUM 68 */
/* BEGIN STRATUM 69 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.60(60,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v0,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(78281),
   enclosing_type(v0,v2),
   assign(v0,v0,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_72_pointsto_objcont_info_60->insert(RamDomain(60),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(94),RamDomain(104));
}();
/* END STRATUM 69 */
/* BEGIN STRATUM 70 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.61(61,"v0,v1,v2","Rule","enclosing_type,v1,v2","assign,v0,v2,v0,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(34234),
   enclosing_type(v1,v2),
   assign(v0,v2,v0,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_73_pointsto_objcont_info_61->insert(RamDomain(61),RamDomain(8),RamDomain(1),RamDomain(50),RamDomain(105),RamDomain(106));
}();
/* END STRATUM 70 */
/* BEGIN STRATUM 71 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.62(62,"v0,v1,v2","Rule","enclosing_type,v1,v2","assign,v0,v2,v1,v2,v0,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(48347),
   enclosing_type(v1,v2),
   assign(v0,v2,v1,v2,v0,v1).").
in file  [0:0-0:0])_");
rel_74_pointsto_objcont_info_62->insert(RamDomain(62),RamDomain(8),RamDomain(1),RamDomain(50),RamDomain(107),RamDomain(108));
}();
/* END STRATUM 71 */
/* BEGIN STRATUM 72 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.63(63,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(36826),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_75_pointsto_objcont_info_63->insert(RamDomain(63),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(42),RamDomain(109));
}();
/* END STRATUM 72 */
/* BEGIN STRATUM 73 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.64(64,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(19964),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_76_pointsto_objcont_info_64->insert(RamDomain(64),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(47),RamDomain(110));
}();
/* END STRATUM 73 */
/* BEGIN STRATUM 74 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.65(65,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v2,v2,v0,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(70583),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v0,v1).").
in file  [0:0-0:0])_");
rel_77_pointsto_objcont_info_65->insert(RamDomain(65),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(75),RamDomain(111));
}();
/* END STRATUM 74 */
/* BEGIN STRATUM 75 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.66(66,"v0,v1,v2","Rule","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(9423),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_78_pointsto_objcont_info_66->insert(RamDomain(66),RamDomain(8),RamDomain(1),RamDomain(38),RamDomain(112));
}();
/* END STRATUM 75 */
/* BEGIN STRATUM 76 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.67(67,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v2,v1,v0,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(59394),
   enclosing_type(v0,v2),
   assign(v1,v2,v1,v0,v2,v0).").
in file  [0:0-0:0])_");
rel_79_pointsto_objcont_info_67->insert(RamDomain(67),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(113),RamDomain(114));
}();
/* END STRATUM 76 */
/* BEGIN STRATUM 77 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.68(68,"v0,v1,v2","Rule","assign,v0,v0,v1,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(8227),
   assign(v0,v0,v1,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_80_pointsto_objcont_info_68->insert(RamDomain(68),RamDomain(8),RamDomain(1),RamDomain(115),RamDomain(116));
}();
/* END STRATUM 77 */
/* BEGIN STRATUM 78 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.69(69,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v1,v0,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(22304),
   enclosing_type(v0,v2),
   assign(v1,v1,v0,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_81_pointsto_objcont_info_69->insert(RamDomain(69),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(117),RamDomain(118));
}();
/* END STRATUM 78 */
/* BEGIN STRATUM 79 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.7(7,"v2,v0,v1","Rule","points_initial,v0,v1","receiver_formal,v1,v2","pointsto_objcont(v2,v0,v1) :- 
   Rule(8),
   points_initial(v0,v1),
   receiver_formal(v1,v2).").
in file  [0:0-0:0])_");
rel_82_pointsto_objcont_info_7->insert(RamDomain(7),RamDomain(5),RamDomain(1),RamDomain(2),RamDomain(3),RamDomain(20));
}();
/* END STRATUM 79 */
/* BEGIN STRATUM 80 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.70(70,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(21947),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_83_pointsto_objcont_info_70->insert(RamDomain(70),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(78),RamDomain(119));
}();
/* END STRATUM 80 */
/* BEGIN STRATUM 81 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.71(71,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(82029),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_84_pointsto_objcont_info_71->insert(RamDomain(71),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(78),RamDomain(120));
}();
/* END STRATUM 81 */
/* BEGIN STRATUM 82 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.72(72,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v1,v0,v2,v2,v1,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(79077),
   enclosing_type(v1,v0),
   assign(v1,v0,v2,v2,v1,v0).").
in file  [0:0-0:0])_");
rel_85_pointsto_objcont_info_72->insert(RamDomain(72),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(32),RamDomain(121));
}();
/* END STRATUM 82 */
/* BEGIN STRATUM 83 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.73(73,"v0,v1,v2","Rule","assign,v0,v0,v1,v2,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(4839),
   assign(v0,v0,v1,v2,v2,v0).").
in file  [0:0-0:0])_");
rel_86_pointsto_objcont_info_73->insert(RamDomain(73),RamDomain(8),RamDomain(1),RamDomain(122),RamDomain(123));
}();
/* END STRATUM 83 */
/* BEGIN STRATUM 84 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.74(74,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v1,v2,v1,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(20846),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v2,v1,v0).").
in file  [0:0-0:0])_");
rel_87_pointsto_objcont_info_74->insert(RamDomain(74),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(124),RamDomain(125));
}();
/* END STRATUM 84 */
/* BEGIN STRATUM 85 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.75(75,"v0,v1,v2","Rule","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(10458),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_88_pointsto_objcont_info_75->insert(RamDomain(75),RamDomain(8),RamDomain(1),RamDomain(38),RamDomain(126));
}();
/* END STRATUM 85 */
/* BEGIN STRATUM 86 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.76(76,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(25015),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_89_pointsto_objcont_info_76->insert(RamDomain(76),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(127));
}();
/* END STRATUM 86 */
/* BEGIN STRATUM 87 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.77(77,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(65996),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_90_pointsto_objcont_info_77->insert(RamDomain(77),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(78),RamDomain(128));
}();
/* END STRATUM 87 */
/* BEGIN STRATUM 88 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.78(78,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v2,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(34638),
   enclosing_type(v0,v2),
   assign(v0,v2,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_91_pointsto_objcont_info_78->insert(RamDomain(78),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(42),RamDomain(129));
}();
/* END STRATUM 88 */
/* BEGIN STRATUM 89 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.79(79,"v0,v1,v2","Rule","enclosing_type,v2,v0","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(27604),
   enclosing_type(v2,v0),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_92_pointsto_objcont_info_79->insert(RamDomain(79),RamDomain(8),RamDomain(1),RamDomain(36),RamDomain(38),RamDomain(130));
}();
/* END STRATUM 89 */
/* BEGIN STRATUM 90 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.8(8,"v0,v2,v1","Rule","points_initial,v0,v1","points_initial,v2,v1","pointsto_objcont(v0,v2,v1) :- 
   Rule(9),
   points_initial(v0,v1),
   points_initial(v2,v1).").
in file  [0:0-0:0])_");
rel_93_pointsto_objcont_info_8->insert(RamDomain(8),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(21),RamDomain(22));
}();
/* END STRATUM 90 */
/* BEGIN STRATUM 91 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.80(80,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v1,v0,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(67769),
   enclosing_type(v0,v2),
   assign(v0,v1,v1,v0,v2,v0).").
in file  [0:0-0:0])_");
rel_94_pointsto_objcont_info_80->insert(RamDomain(80),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(52),RamDomain(131));
}();
/* END STRATUM 91 */
/* BEGIN STRATUM 92 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.81(81,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(63016),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_95_pointsto_objcont_info_81->insert(RamDomain(81),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(132));
}();
/* END STRATUM 92 */
/* BEGIN STRATUM 93 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.82(82,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v0,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(42257),
   enclosing_type(v0,v2),
   assign(v1,v0,v0,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_96_pointsto_objcont_info_82->insert(RamDomain(82),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(133),RamDomain(134));
}();
/* END STRATUM 93 */
/* BEGIN STRATUM 94 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.83(83,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v1,v0,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(24992),
   enclosing_type(v1,v0),
   assign(v1,v0,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_97_pointsto_objcont_info_83->insert(RamDomain(83),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(135),RamDomain(136));
}();
/* END STRATUM 94 */
/* BEGIN STRATUM 95 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.84(84,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v2,v2,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(32795),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v2,v0).").
in file  [0:0-0:0])_");
rel_98_pointsto_objcont_info_84->insert(RamDomain(84),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(137),RamDomain(138));
}();
/* END STRATUM 95 */
/* BEGIN STRATUM 96 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.85(85,"v0,v1,v2","Rule","assign,v0,v0,v1,v2,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(3548),
   assign(v0,v0,v1,v2,v1,v2).").
in file  [0:0-0:0])_");
rel_99_pointsto_objcont_info_85->insert(RamDomain(85),RamDomain(8),RamDomain(1),RamDomain(94),RamDomain(139));
}();
/* END STRATUM 96 */
/* BEGIN STRATUM 97 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.86(86,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(41694),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_100_pointsto_objcont_info_86->insert(RamDomain(86),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(38),RamDomain(140));
}();
/* END STRATUM 97 */
/* BEGIN STRATUM 98 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.87(87,"v0,v1,v2","Rule","enclosing_type,v2,v0","assign,v0,v2,v0,v1,v2,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(64161),
   enclosing_type(v2,v0),
   assign(v0,v2,v0,v1,v2,v1).").
in file  [0:0-0:0])_");
rel_101_pointsto_objcont_info_87->insert(RamDomain(87),RamDomain(8),RamDomain(1),RamDomain(36),RamDomain(141),RamDomain(142));
}();
/* END STRATUM 98 */
/* BEGIN STRATUM 99 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.88(88,"v0,v1,v2","Rule","enclosing_type,v0,v1","load,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(14576),
   enclosing_type(v0,v1),
   load(v0,v1,v2).").
in file  [0:0-0:0])_");
rel_102_pointsto_objcont_info_88->insert(RamDomain(88),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(16),RamDomain(143));
}();
/* END STRATUM 99 */
/* BEGIN STRATUM 100 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.89(89,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v0,v2,v2,v0,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(43687),
   enclosing_type(v0,v2),
   assign(v1,v0,v2,v2,v0,v1).").
in file  [0:0-0:0])_");
rel_103_pointsto_objcont_info_89->insert(RamDomain(89),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(75),RamDomain(144));
}();
/* END STRATUM 100 */
/* BEGIN STRATUM 101 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.9(9,"v2,v0,v1","Rule","points_initial,v0,v1","pointsto_objcont,v1,v0,v2","pointsto_objcont(v2,v0,v1) :- 
   Rule(5),
   points_initial(v0,v1),
   pointsto_objcont(v1,v0,v2).").
in file  [0:0-0:0])_");
rel_104_pointsto_objcont_info_9->insert(RamDomain(9),RamDomain(5),RamDomain(1),RamDomain(2),RamDomain(23),RamDomain(24));
}();
/* END STRATUM 101 */
/* BEGIN STRATUM 102 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.90(90,"v0,v1,v2","Rule","assign,v0,v1,v2,v1,v0,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(7005),
   assign(v0,v1,v2,v1,v0,v2).").
in file  [0:0-0:0])_");
rel_105_pointsto_objcont_info_90->insert(RamDomain(90),RamDomain(8),RamDomain(1),RamDomain(78),RamDomain(145));
}();
/* END STRATUM 102 */
/* BEGIN STRATUM 103 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.91(91,"v0,v1,v2","Rule","enclosing_type,v1,v2","assign,v0,v1,v1,v0,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(22493),
   enclosing_type(v1,v2),
   assign(v0,v1,v1,v0,v2,v0).").
in file  [0:0-0:0])_");
rel_106_pointsto_objcont_info_91->insert(RamDomain(91),RamDomain(8),RamDomain(1),RamDomain(50),RamDomain(52),RamDomain(146));
}();
/* END STRATUM 103 */
/* BEGIN STRATUM 104 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.92(92,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v2,v0,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(40917),
   enclosing_type(v0,v2),
   assign(v1,v2,v0,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_107_pointsto_objcont_info_92->insert(RamDomain(92),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(99),RamDomain(147));
}();
/* END STRATUM 104 */
/* BEGIN STRATUM 105 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.93(93,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(67708),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_108_pointsto_objcont_info_93->insert(RamDomain(93),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(148));
}();
/* END STRATUM 105 */
/* BEGIN STRATUM 106 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.94(94,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(90086),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_109_pointsto_objcont_info_94->insert(RamDomain(94),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(149));
}();
/* END STRATUM 106 */
/* BEGIN STRATUM 107 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.95(95,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v1,v2,v0,v1,v2,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(47927),
   enclosing_type(v0,v2),
   assign(v1,v2,v0,v1,v2,v1).").
in file  [0:0-0:0])_");
rel_110_pointsto_objcont_info_95->insert(RamDomain(95),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(150),RamDomain(151));
}();
/* END STRATUM 107 */
/* BEGIN STRATUM 108 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.96(96,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v2,v1,v0,v2,v2,v1","pointsto_objcont(v0,v1,v2) :- 
   Rule(86220),
   enclosing_type(v1,v0),
   assign(v2,v1,v0,v2,v2,v1).").
in file  [0:0-0:0])_");
rel_111_pointsto_objcont_info_96->insert(RamDomain(96),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(152),RamDomain(153));
}();
/* END STRATUM 108 */
/* BEGIN STRATUM 109 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.97(97,"v0,v1,v2","Rule","enclosing_type,v0,v1","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(87963),
   enclosing_type(v0,v1),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_112_pointsto_objcont_info_97->insert(RamDomain(97),RamDomain(8),RamDomain(1),RamDomain(28),RamDomain(38),RamDomain(154));
}();
/* END STRATUM 109 */
/* BEGIN STRATUM 110 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.98(98,"v0,v1,v2","Rule","enclosing_type,v0,v2","assign,v0,v1,v2,v0,v1,v2","pointsto_objcont(v0,v1,v2) :- 
   Rule(20685),
   enclosing_type(v0,v2),
   assign(v0,v1,v2,v0,v1,v2).").
in file  [0:0-0:0])_");
rel_113_pointsto_objcont_info_98->insert(RamDomain(98),RamDomain(8),RamDomain(1),RamDomain(31),RamDomain(38),RamDomain(155));
}();
/* END STRATUM 110 */
/* BEGIN STRATUM 111 */
[&]() {
SignalHandler::instance()->setMsg(R"_(pointsto_objcont.@info.99(99,"v0,v1,v2","Rule","enclosing_type,v1,v0","assign,v0,v1,v2,v1,v2,v0","pointsto_objcont(v0,v1,v2) :- 
   Rule(39726),
   enclosing_type(v1,v0),
   assign(v0,v1,v2,v1,v2,v0).").
in file  [0:0-0:0])_");
rel_114_pointsto_objcont_info_99->insert(RamDomain(99),RamDomain(8),RamDomain(1),RamDomain(41),RamDomain(87),RamDomain(156));
}();
/* END STRATUM 111 */

// -- relation hint statistics --
if(isHintsProfilingEnabled()) {
std::cout << " -- Operation Hint Statistics --\n";
std::cout << "Relation rel_1_Rule:\n";
rel_1_Rule->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_2_actual:\n";
rel_2_actual->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_3_assign:\n";
rel_3_assign->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_4_enclosing_type:\n";
rel_4_enclosing_type->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_5_heappointsto:\n";
rel_5_heappointsto->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_6_invocation:\n";
rel_6_invocation->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_7_load:\n";
rel_7_load->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_8_points_initial:\n";
rel_8_points_initial->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_9_pointsto:\n";
rel_9_pointsto->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_10_receiver_formal:\n";
rel_10_receiver_formal->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_11_store:\n";
rel_11_store->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_12_pointsto_objcont:\n";
rel_12_pointsto_objcont->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_13_delta_pointsto_objcont:\n";
rel_13_delta_pointsto_objcont->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_14_new_pointsto_objcont:\n";
rel_14_new_pointsto_objcont->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_15_pointsto_objcont_info_1:\n";
rel_15_pointsto_objcont_info_1->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_16_pointsto_objcont_info_10:\n";
rel_16_pointsto_objcont_info_10->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_17_pointsto_objcont_info_100:\n";
rel_17_pointsto_objcont_info_100->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_18_pointsto_objcont_info_11:\n";
rel_18_pointsto_objcont_info_11->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_19_pointsto_objcont_info_12:\n";
rel_19_pointsto_objcont_info_12->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_20_pointsto_objcont_info_13:\n";
rel_20_pointsto_objcont_info_13->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_21_pointsto_objcont_info_14:\n";
rel_21_pointsto_objcont_info_14->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_22_pointsto_objcont_info_15:\n";
rel_22_pointsto_objcont_info_15->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_23_pointsto_objcont_info_16:\n";
rel_23_pointsto_objcont_info_16->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_24_pointsto_objcont_info_17:\n";
rel_24_pointsto_objcont_info_17->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_25_pointsto_objcont_info_18:\n";
rel_25_pointsto_objcont_info_18->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_26_pointsto_objcont_info_19:\n";
rel_26_pointsto_objcont_info_19->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_27_pointsto_objcont_info_2:\n";
rel_27_pointsto_objcont_info_2->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_28_pointsto_objcont_info_20:\n";
rel_28_pointsto_objcont_info_20->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_29_pointsto_objcont_info_21:\n";
rel_29_pointsto_objcont_info_21->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_30_pointsto_objcont_info_22:\n";
rel_30_pointsto_objcont_info_22->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_31_pointsto_objcont_info_23:\n";
rel_31_pointsto_objcont_info_23->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_32_pointsto_objcont_info_24:\n";
rel_32_pointsto_objcont_info_24->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_33_pointsto_objcont_info_25:\n";
rel_33_pointsto_objcont_info_25->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_34_pointsto_objcont_info_26:\n";
rel_34_pointsto_objcont_info_26->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_35_pointsto_objcont_info_27:\n";
rel_35_pointsto_objcont_info_27->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_36_pointsto_objcont_info_28:\n";
rel_36_pointsto_objcont_info_28->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_37_pointsto_objcont_info_29:\n";
rel_37_pointsto_objcont_info_29->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_38_pointsto_objcont_info_3:\n";
rel_38_pointsto_objcont_info_3->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_39_pointsto_objcont_info_30:\n";
rel_39_pointsto_objcont_info_30->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_40_pointsto_objcont_info_31:\n";
rel_40_pointsto_objcont_info_31->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_41_pointsto_objcont_info_32:\n";
rel_41_pointsto_objcont_info_32->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_42_pointsto_objcont_info_33:\n";
rel_42_pointsto_objcont_info_33->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_43_pointsto_objcont_info_34:\n";
rel_43_pointsto_objcont_info_34->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_44_pointsto_objcont_info_35:\n";
rel_44_pointsto_objcont_info_35->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_45_pointsto_objcont_info_36:\n";
rel_45_pointsto_objcont_info_36->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_46_pointsto_objcont_info_37:\n";
rel_46_pointsto_objcont_info_37->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_47_pointsto_objcont_info_38:\n";
rel_47_pointsto_objcont_info_38->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_48_pointsto_objcont_info_39:\n";
rel_48_pointsto_objcont_info_39->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_49_pointsto_objcont_info_4:\n";
rel_49_pointsto_objcont_info_4->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_50_pointsto_objcont_info_40:\n";
rel_50_pointsto_objcont_info_40->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_51_pointsto_objcont_info_41:\n";
rel_51_pointsto_objcont_info_41->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_52_pointsto_objcont_info_42:\n";
rel_52_pointsto_objcont_info_42->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_53_pointsto_objcont_info_43:\n";
rel_53_pointsto_objcont_info_43->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_54_pointsto_objcont_info_44:\n";
rel_54_pointsto_objcont_info_44->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_55_pointsto_objcont_info_45:\n";
rel_55_pointsto_objcont_info_45->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_56_pointsto_objcont_info_46:\n";
rel_56_pointsto_objcont_info_46->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_57_pointsto_objcont_info_47:\n";
rel_57_pointsto_objcont_info_47->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_58_pointsto_objcont_info_48:\n";
rel_58_pointsto_objcont_info_48->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_59_pointsto_objcont_info_49:\n";
rel_59_pointsto_objcont_info_49->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_60_pointsto_objcont_info_5:\n";
rel_60_pointsto_objcont_info_5->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_61_pointsto_objcont_info_50:\n";
rel_61_pointsto_objcont_info_50->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_62_pointsto_objcont_info_51:\n";
rel_62_pointsto_objcont_info_51->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_63_pointsto_objcont_info_52:\n";
rel_63_pointsto_objcont_info_52->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_64_pointsto_objcont_info_53:\n";
rel_64_pointsto_objcont_info_53->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_65_pointsto_objcont_info_54:\n";
rel_65_pointsto_objcont_info_54->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_66_pointsto_objcont_info_55:\n";
rel_66_pointsto_objcont_info_55->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_67_pointsto_objcont_info_56:\n";
rel_67_pointsto_objcont_info_56->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_68_pointsto_objcont_info_57:\n";
rel_68_pointsto_objcont_info_57->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_69_pointsto_objcont_info_58:\n";
rel_69_pointsto_objcont_info_58->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_70_pointsto_objcont_info_59:\n";
rel_70_pointsto_objcont_info_59->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_71_pointsto_objcont_info_6:\n";
rel_71_pointsto_objcont_info_6->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_72_pointsto_objcont_info_60:\n";
rel_72_pointsto_objcont_info_60->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_73_pointsto_objcont_info_61:\n";
rel_73_pointsto_objcont_info_61->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_74_pointsto_objcont_info_62:\n";
rel_74_pointsto_objcont_info_62->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_75_pointsto_objcont_info_63:\n";
rel_75_pointsto_objcont_info_63->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_76_pointsto_objcont_info_64:\n";
rel_76_pointsto_objcont_info_64->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_77_pointsto_objcont_info_65:\n";
rel_77_pointsto_objcont_info_65->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_78_pointsto_objcont_info_66:\n";
rel_78_pointsto_objcont_info_66->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_79_pointsto_objcont_info_67:\n";
rel_79_pointsto_objcont_info_67->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_80_pointsto_objcont_info_68:\n";
rel_80_pointsto_objcont_info_68->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_81_pointsto_objcont_info_69:\n";
rel_81_pointsto_objcont_info_69->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_82_pointsto_objcont_info_7:\n";
rel_82_pointsto_objcont_info_7->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_83_pointsto_objcont_info_70:\n";
rel_83_pointsto_objcont_info_70->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_84_pointsto_objcont_info_71:\n";
rel_84_pointsto_objcont_info_71->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_85_pointsto_objcont_info_72:\n";
rel_85_pointsto_objcont_info_72->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_86_pointsto_objcont_info_73:\n";
rel_86_pointsto_objcont_info_73->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_87_pointsto_objcont_info_74:\n";
rel_87_pointsto_objcont_info_74->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_88_pointsto_objcont_info_75:\n";
rel_88_pointsto_objcont_info_75->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_89_pointsto_objcont_info_76:\n";
rel_89_pointsto_objcont_info_76->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_90_pointsto_objcont_info_77:\n";
rel_90_pointsto_objcont_info_77->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_91_pointsto_objcont_info_78:\n";
rel_91_pointsto_objcont_info_78->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_92_pointsto_objcont_info_79:\n";
rel_92_pointsto_objcont_info_79->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_93_pointsto_objcont_info_8:\n";
rel_93_pointsto_objcont_info_8->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_94_pointsto_objcont_info_80:\n";
rel_94_pointsto_objcont_info_80->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_95_pointsto_objcont_info_81:\n";
rel_95_pointsto_objcont_info_81->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_96_pointsto_objcont_info_82:\n";
rel_96_pointsto_objcont_info_82->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_97_pointsto_objcont_info_83:\n";
rel_97_pointsto_objcont_info_83->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_98_pointsto_objcont_info_84:\n";
rel_98_pointsto_objcont_info_84->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_99_pointsto_objcont_info_85:\n";
rel_99_pointsto_objcont_info_85->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_100_pointsto_objcont_info_86:\n";
rel_100_pointsto_objcont_info_86->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_101_pointsto_objcont_info_87:\n";
rel_101_pointsto_objcont_info_87->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_102_pointsto_objcont_info_88:\n";
rel_102_pointsto_objcont_info_88->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_103_pointsto_objcont_info_89:\n";
rel_103_pointsto_objcont_info_89->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_104_pointsto_objcont_info_9:\n";
rel_104_pointsto_objcont_info_9->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_105_pointsto_objcont_info_90:\n";
rel_105_pointsto_objcont_info_90->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_106_pointsto_objcont_info_91:\n";
rel_106_pointsto_objcont_info_91->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_107_pointsto_objcont_info_92:\n";
rel_107_pointsto_objcont_info_92->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_108_pointsto_objcont_info_93:\n";
rel_108_pointsto_objcont_info_93->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_109_pointsto_objcont_info_94:\n";
rel_109_pointsto_objcont_info_94->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_110_pointsto_objcont_info_95:\n";
rel_110_pointsto_objcont_info_95->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_111_pointsto_objcont_info_96:\n";
rel_111_pointsto_objcont_info_96->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_112_pointsto_objcont_info_97:\n";
rel_112_pointsto_objcont_info_97->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_113_pointsto_objcont_info_98:\n";
rel_113_pointsto_objcont_info_98->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_114_pointsto_objcont_info_99:\n";
rel_114_pointsto_objcont_info_99->printHintStatistics(std::cout,"  ");
std::cout << "\n";
}
SignalHandler::instance()->reset();
}
public:
void run(size_t stratumIndex = (size_t) -1) override { runFunction(".", ".", stratumIndex, false); }
public:
void runAll(std::string inputDirectory = ".", std::string outputDirectory = ".", size_t stratumIndex = (size_t) -1) override { runFunction(inputDirectory, outputDirectory, stratumIndex, true);
}
public:
void printAll(std::string outputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1\tv2"},{"filename","./heappointsto.csv"},{"name","heappointsto"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_5_heappointsto);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1\tv2\tv3"},{"filename","./pointsto.csv"},{"name","pointsto"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_9_pointsto);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1\tv2"},{"filename","./pointsto_objcont.csv"},{"name","pointsto_objcont"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_12_pointsto_objcont);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void loadAll(std::string inputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./Rule.facts"},{"name","Rule"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({0,0,0}), symTable, ioDirectives, true)->readAll(*rel_1_Rule);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./actual.facts"},{"name","actual"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_2_actual);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./assign.facts"},{"name","assign"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_3_assign);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./enclosing_type.facts"},{"name","enclosing_type"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_4_enclosing_type);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./invocation.facts"},{"name","invocation"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_6_invocation);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./load.facts"},{"name","load"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_7_load);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./points_initial.facts"},{"name","points_initial"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_8_points_initial);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./receiver_formal.facts"},{"name","receiver_formal"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_10_receiver_formal);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./store.facts"},{"name","store"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_11_store);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
public:
void dumpInputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_1_Rule");
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0}), symTable, ioDirectives, true)->writeAll(*rel_1_Rule);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_2_actual");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_2_actual);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_3_assign");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_3_assign);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_4_enclosing_type");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_4_enclosing_type);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_6_invocation");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_6_invocation);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_7_load");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_7_load);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_8_points_initial");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_8_points_initial);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_10_receiver_formal");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_10_receiver_formal);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_11_store");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_11_store);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void dumpOutputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_5_heappointsto");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_5_heappointsto);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_9_pointsto");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_9_pointsto);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_12_pointsto_objcont");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_12_pointsto_objcont);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
SymbolTable& getSymbolTable() override {
return symTable;
}
void executeSubroutine(std::string name, const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) override {
if (name == "pointsto_objcont_100_negation_subproof") {
subproof_0(args, ret, err);
}
if (name == "pointsto_objcont_100_subproof") {
subproof_1(args, ret, err);
}
if (name == "pointsto_objcont_10_negation_subproof") {
subproof_2(args, ret, err);
}
if (name == "pointsto_objcont_10_subproof") {
subproof_3(args, ret, err);
}
if (name == "pointsto_objcont_11_negation_subproof") {
subproof_4(args, ret, err);
}
if (name == "pointsto_objcont_11_subproof") {
subproof_5(args, ret, err);
}
if (name == "pointsto_objcont_12_negation_subproof") {
subproof_6(args, ret, err);
}
if (name == "pointsto_objcont_12_subproof") {
subproof_7(args, ret, err);
}
if (name == "pointsto_objcont_13_negation_subproof") {
subproof_8(args, ret, err);
}
if (name == "pointsto_objcont_13_subproof") {
subproof_9(args, ret, err);
}
if (name == "pointsto_objcont_14_negation_subproof") {
subproof_10(args, ret, err);
}
if (name == "pointsto_objcont_14_subproof") {
subproof_11(args, ret, err);
}
if (name == "pointsto_objcont_15_negation_subproof") {
subproof_12(args, ret, err);
}
if (name == "pointsto_objcont_15_subproof") {
subproof_13(args, ret, err);
}
if (name == "pointsto_objcont_16_negation_subproof") {
subproof_14(args, ret, err);
}
if (name == "pointsto_objcont_16_subproof") {
subproof_15(args, ret, err);
}
if (name == "pointsto_objcont_17_negation_subproof") {
subproof_16(args, ret, err);
}
if (name == "pointsto_objcont_17_subproof") {
subproof_17(args, ret, err);
}
if (name == "pointsto_objcont_18_negation_subproof") {
subproof_18(args, ret, err);
}
if (name == "pointsto_objcont_18_subproof") {
subproof_19(args, ret, err);
}
if (name == "pointsto_objcont_19_negation_subproof") {
subproof_20(args, ret, err);
}
if (name == "pointsto_objcont_19_subproof") {
subproof_21(args, ret, err);
}
if (name == "pointsto_objcont_1_negation_subproof") {
subproof_22(args, ret, err);
}
if (name == "pointsto_objcont_1_subproof") {
subproof_23(args, ret, err);
}
if (name == "pointsto_objcont_20_negation_subproof") {
subproof_24(args, ret, err);
}
if (name == "pointsto_objcont_20_subproof") {
subproof_25(args, ret, err);
}
if (name == "pointsto_objcont_21_negation_subproof") {
subproof_26(args, ret, err);
}
if (name == "pointsto_objcont_21_subproof") {
subproof_27(args, ret, err);
}
if (name == "pointsto_objcont_22_negation_subproof") {
subproof_28(args, ret, err);
}
if (name == "pointsto_objcont_22_subproof") {
subproof_29(args, ret, err);
}
if (name == "pointsto_objcont_23_negation_subproof") {
subproof_30(args, ret, err);
}
if (name == "pointsto_objcont_23_subproof") {
subproof_31(args, ret, err);
}
if (name == "pointsto_objcont_24_negation_subproof") {
subproof_32(args, ret, err);
}
if (name == "pointsto_objcont_24_subproof") {
subproof_33(args, ret, err);
}
if (name == "pointsto_objcont_25_negation_subproof") {
subproof_34(args, ret, err);
}
if (name == "pointsto_objcont_25_subproof") {
subproof_35(args, ret, err);
}
if (name == "pointsto_objcont_26_negation_subproof") {
subproof_36(args, ret, err);
}
if (name == "pointsto_objcont_26_subproof") {
subproof_37(args, ret, err);
}
if (name == "pointsto_objcont_27_negation_subproof") {
subproof_38(args, ret, err);
}
if (name == "pointsto_objcont_27_subproof") {
subproof_39(args, ret, err);
}
if (name == "pointsto_objcont_28_negation_subproof") {
subproof_40(args, ret, err);
}
if (name == "pointsto_objcont_28_subproof") {
subproof_41(args, ret, err);
}
if (name == "pointsto_objcont_29_negation_subproof") {
subproof_42(args, ret, err);
}
if (name == "pointsto_objcont_29_subproof") {
subproof_43(args, ret, err);
}
if (name == "pointsto_objcont_2_negation_subproof") {
subproof_44(args, ret, err);
}
if (name == "pointsto_objcont_2_subproof") {
subproof_45(args, ret, err);
}
if (name == "pointsto_objcont_30_negation_subproof") {
subproof_46(args, ret, err);
}
if (name == "pointsto_objcont_30_subproof") {
subproof_47(args, ret, err);
}
if (name == "pointsto_objcont_31_negation_subproof") {
subproof_48(args, ret, err);
}
if (name == "pointsto_objcont_31_subproof") {
subproof_49(args, ret, err);
}
if (name == "pointsto_objcont_32_negation_subproof") {
subproof_50(args, ret, err);
}
if (name == "pointsto_objcont_32_subproof") {
subproof_51(args, ret, err);
}
if (name == "pointsto_objcont_33_negation_subproof") {
subproof_52(args, ret, err);
}
if (name == "pointsto_objcont_33_subproof") {
subproof_53(args, ret, err);
}
if (name == "pointsto_objcont_34_negation_subproof") {
subproof_54(args, ret, err);
}
if (name == "pointsto_objcont_34_subproof") {
subproof_55(args, ret, err);
}
if (name == "pointsto_objcont_35_negation_subproof") {
subproof_56(args, ret, err);
}
if (name == "pointsto_objcont_35_subproof") {
subproof_57(args, ret, err);
}
if (name == "pointsto_objcont_36_negation_subproof") {
subproof_58(args, ret, err);
}
if (name == "pointsto_objcont_36_subproof") {
subproof_59(args, ret, err);
}
if (name == "pointsto_objcont_37_negation_subproof") {
subproof_60(args, ret, err);
}
if (name == "pointsto_objcont_37_subproof") {
subproof_61(args, ret, err);
}
if (name == "pointsto_objcont_38_negation_subproof") {
subproof_62(args, ret, err);
}
if (name == "pointsto_objcont_38_subproof") {
subproof_63(args, ret, err);
}
if (name == "pointsto_objcont_39_negation_subproof") {
subproof_64(args, ret, err);
}
if (name == "pointsto_objcont_39_subproof") {
subproof_65(args, ret, err);
}
if (name == "pointsto_objcont_3_negation_subproof") {
subproof_66(args, ret, err);
}
if (name == "pointsto_objcont_3_subproof") {
subproof_67(args, ret, err);
}
if (name == "pointsto_objcont_40_negation_subproof") {
subproof_68(args, ret, err);
}
if (name == "pointsto_objcont_40_subproof") {
subproof_69(args, ret, err);
}
if (name == "pointsto_objcont_41_negation_subproof") {
subproof_70(args, ret, err);
}
if (name == "pointsto_objcont_41_subproof") {
subproof_71(args, ret, err);
}
if (name == "pointsto_objcont_42_negation_subproof") {
subproof_72(args, ret, err);
}
if (name == "pointsto_objcont_42_subproof") {
subproof_73(args, ret, err);
}
if (name == "pointsto_objcont_43_negation_subproof") {
subproof_74(args, ret, err);
}
if (name == "pointsto_objcont_43_subproof") {
subproof_75(args, ret, err);
}
if (name == "pointsto_objcont_44_negation_subproof") {
subproof_76(args, ret, err);
}
if (name == "pointsto_objcont_44_subproof") {
subproof_77(args, ret, err);
}
if (name == "pointsto_objcont_45_negation_subproof") {
subproof_78(args, ret, err);
}
if (name == "pointsto_objcont_45_subproof") {
subproof_79(args, ret, err);
}
if (name == "pointsto_objcont_46_negation_subproof") {
subproof_80(args, ret, err);
}
if (name == "pointsto_objcont_46_subproof") {
subproof_81(args, ret, err);
}
if (name == "pointsto_objcont_47_negation_subproof") {
subproof_82(args, ret, err);
}
if (name == "pointsto_objcont_47_subproof") {
subproof_83(args, ret, err);
}
if (name == "pointsto_objcont_48_negation_subproof") {
subproof_84(args, ret, err);
}
if (name == "pointsto_objcont_48_subproof") {
subproof_85(args, ret, err);
}
if (name == "pointsto_objcont_49_negation_subproof") {
subproof_86(args, ret, err);
}
if (name == "pointsto_objcont_49_subproof") {
subproof_87(args, ret, err);
}
if (name == "pointsto_objcont_4_negation_subproof") {
subproof_88(args, ret, err);
}
if (name == "pointsto_objcont_4_subproof") {
subproof_89(args, ret, err);
}
if (name == "pointsto_objcont_50_negation_subproof") {
subproof_90(args, ret, err);
}
if (name == "pointsto_objcont_50_subproof") {
subproof_91(args, ret, err);
}
if (name == "pointsto_objcont_51_negation_subproof") {
subproof_92(args, ret, err);
}
if (name == "pointsto_objcont_51_subproof") {
subproof_93(args, ret, err);
}
if (name == "pointsto_objcont_52_negation_subproof") {
subproof_94(args, ret, err);
}
if (name == "pointsto_objcont_52_subproof") {
subproof_95(args, ret, err);
}
if (name == "pointsto_objcont_53_negation_subproof") {
subproof_96(args, ret, err);
}
if (name == "pointsto_objcont_53_subproof") {
subproof_97(args, ret, err);
}
if (name == "pointsto_objcont_54_negation_subproof") {
subproof_98(args, ret, err);
}
if (name == "pointsto_objcont_54_subproof") {
subproof_99(args, ret, err);
}
if (name == "pointsto_objcont_55_negation_subproof") {
subproof_100(args, ret, err);
}
if (name == "pointsto_objcont_55_subproof") {
subproof_101(args, ret, err);
}
if (name == "pointsto_objcont_56_negation_subproof") {
subproof_102(args, ret, err);
}
if (name == "pointsto_objcont_56_subproof") {
subproof_103(args, ret, err);
}
if (name == "pointsto_objcont_57_negation_subproof") {
subproof_104(args, ret, err);
}
if (name == "pointsto_objcont_57_subproof") {
subproof_105(args, ret, err);
}
if (name == "pointsto_objcont_58_negation_subproof") {
subproof_106(args, ret, err);
}
if (name == "pointsto_objcont_58_subproof") {
subproof_107(args, ret, err);
}
if (name == "pointsto_objcont_59_negation_subproof") {
subproof_108(args, ret, err);
}
if (name == "pointsto_objcont_59_subproof") {
subproof_109(args, ret, err);
}
if (name == "pointsto_objcont_5_negation_subproof") {
subproof_110(args, ret, err);
}
if (name == "pointsto_objcont_5_subproof") {
subproof_111(args, ret, err);
}
if (name == "pointsto_objcont_60_negation_subproof") {
subproof_112(args, ret, err);
}
if (name == "pointsto_objcont_60_subproof") {
subproof_113(args, ret, err);
}
if (name == "pointsto_objcont_61_negation_subproof") {
subproof_114(args, ret, err);
}
if (name == "pointsto_objcont_61_subproof") {
subproof_115(args, ret, err);
}
if (name == "pointsto_objcont_62_negation_subproof") {
subproof_116(args, ret, err);
}
if (name == "pointsto_objcont_62_subproof") {
subproof_117(args, ret, err);
}
if (name == "pointsto_objcont_63_negation_subproof") {
subproof_118(args, ret, err);
}
if (name == "pointsto_objcont_63_subproof") {
subproof_119(args, ret, err);
}
if (name == "pointsto_objcont_64_negation_subproof") {
subproof_120(args, ret, err);
}
if (name == "pointsto_objcont_64_subproof") {
subproof_121(args, ret, err);
}
if (name == "pointsto_objcont_65_negation_subproof") {
subproof_122(args, ret, err);
}
if (name == "pointsto_objcont_65_subproof") {
subproof_123(args, ret, err);
}
if (name == "pointsto_objcont_66_negation_subproof") {
subproof_124(args, ret, err);
}
if (name == "pointsto_objcont_66_subproof") {
subproof_125(args, ret, err);
}
if (name == "pointsto_objcont_67_negation_subproof") {
subproof_126(args, ret, err);
}
if (name == "pointsto_objcont_67_subproof") {
subproof_127(args, ret, err);
}
if (name == "pointsto_objcont_68_negation_subproof") {
subproof_128(args, ret, err);
}
if (name == "pointsto_objcont_68_subproof") {
subproof_129(args, ret, err);
}
if (name == "pointsto_objcont_69_negation_subproof") {
subproof_130(args, ret, err);
}
if (name == "pointsto_objcont_69_subproof") {
subproof_131(args, ret, err);
}
if (name == "pointsto_objcont_6_negation_subproof") {
subproof_132(args, ret, err);
}
if (name == "pointsto_objcont_6_subproof") {
subproof_133(args, ret, err);
}
if (name == "pointsto_objcont_70_negation_subproof") {
subproof_134(args, ret, err);
}
if (name == "pointsto_objcont_70_subproof") {
subproof_135(args, ret, err);
}
if (name == "pointsto_objcont_71_negation_subproof") {
subproof_136(args, ret, err);
}
if (name == "pointsto_objcont_71_subproof") {
subproof_137(args, ret, err);
}
if (name == "pointsto_objcont_72_negation_subproof") {
subproof_138(args, ret, err);
}
if (name == "pointsto_objcont_72_subproof") {
subproof_139(args, ret, err);
}
if (name == "pointsto_objcont_73_negation_subproof") {
subproof_140(args, ret, err);
}
if (name == "pointsto_objcont_73_subproof") {
subproof_141(args, ret, err);
}
if (name == "pointsto_objcont_74_negation_subproof") {
subproof_142(args, ret, err);
}
if (name == "pointsto_objcont_74_subproof") {
subproof_143(args, ret, err);
}
if (name == "pointsto_objcont_75_negation_subproof") {
subproof_144(args, ret, err);
}
if (name == "pointsto_objcont_75_subproof") {
subproof_145(args, ret, err);
}
if (name == "pointsto_objcont_76_negation_subproof") {
subproof_146(args, ret, err);
}
if (name == "pointsto_objcont_76_subproof") {
subproof_147(args, ret, err);
}
if (name == "pointsto_objcont_77_negation_subproof") {
subproof_148(args, ret, err);
}
if (name == "pointsto_objcont_77_subproof") {
subproof_149(args, ret, err);
}
if (name == "pointsto_objcont_78_negation_subproof") {
subproof_150(args, ret, err);
}
if (name == "pointsto_objcont_78_subproof") {
subproof_151(args, ret, err);
}
if (name == "pointsto_objcont_79_negation_subproof") {
subproof_152(args, ret, err);
}
if (name == "pointsto_objcont_79_subproof") {
subproof_153(args, ret, err);
}
if (name == "pointsto_objcont_7_negation_subproof") {
subproof_154(args, ret, err);
}
if (name == "pointsto_objcont_7_subproof") {
subproof_155(args, ret, err);
}
if (name == "pointsto_objcont_80_negation_subproof") {
subproof_156(args, ret, err);
}
if (name == "pointsto_objcont_80_subproof") {
subproof_157(args, ret, err);
}
if (name == "pointsto_objcont_81_negation_subproof") {
subproof_158(args, ret, err);
}
if (name == "pointsto_objcont_81_subproof") {
subproof_159(args, ret, err);
}
if (name == "pointsto_objcont_82_negation_subproof") {
subproof_160(args, ret, err);
}
if (name == "pointsto_objcont_82_subproof") {
subproof_161(args, ret, err);
}
if (name == "pointsto_objcont_83_negation_subproof") {
subproof_162(args, ret, err);
}
if (name == "pointsto_objcont_83_subproof") {
subproof_163(args, ret, err);
}
if (name == "pointsto_objcont_84_negation_subproof") {
subproof_164(args, ret, err);
}
if (name == "pointsto_objcont_84_subproof") {
subproof_165(args, ret, err);
}
if (name == "pointsto_objcont_85_negation_subproof") {
subproof_166(args, ret, err);
}
if (name == "pointsto_objcont_85_subproof") {
subproof_167(args, ret, err);
}
if (name == "pointsto_objcont_86_negation_subproof") {
subproof_168(args, ret, err);
}
if (name == "pointsto_objcont_86_subproof") {
subproof_169(args, ret, err);
}
if (name == "pointsto_objcont_87_negation_subproof") {
subproof_170(args, ret, err);
}
if (name == "pointsto_objcont_87_subproof") {
subproof_171(args, ret, err);
}
if (name == "pointsto_objcont_88_negation_subproof") {
subproof_172(args, ret, err);
}
if (name == "pointsto_objcont_88_subproof") {
subproof_173(args, ret, err);
}
if (name == "pointsto_objcont_89_negation_subproof") {
subproof_174(args, ret, err);
}
if (name == "pointsto_objcont_89_subproof") {
subproof_175(args, ret, err);
}
if (name == "pointsto_objcont_8_negation_subproof") {
subproof_176(args, ret, err);
}
if (name == "pointsto_objcont_8_subproof") {
subproof_177(args, ret, err);
}
if (name == "pointsto_objcont_90_negation_subproof") {
subproof_178(args, ret, err);
}
if (name == "pointsto_objcont_90_subproof") {
subproof_179(args, ret, err);
}
if (name == "pointsto_objcont_91_negation_subproof") {
subproof_180(args, ret, err);
}
if (name == "pointsto_objcont_91_subproof") {
subproof_181(args, ret, err);
}
if (name == "pointsto_objcont_92_negation_subproof") {
subproof_182(args, ret, err);
}
if (name == "pointsto_objcont_92_subproof") {
subproof_183(args, ret, err);
}
if (name == "pointsto_objcont_93_negation_subproof") {
subproof_184(args, ret, err);
}
if (name == "pointsto_objcont_93_subproof") {
subproof_185(args, ret, err);
}
if (name == "pointsto_objcont_94_negation_subproof") {
subproof_186(args, ret, err);
}
if (name == "pointsto_objcont_94_subproof") {
subproof_187(args, ret, err);
}
if (name == "pointsto_objcont_95_negation_subproof") {
subproof_188(args, ret, err);
}
if (name == "pointsto_objcont_95_subproof") {
subproof_189(args, ret, err);
}
if (name == "pointsto_objcont_96_negation_subproof") {
subproof_190(args, ret, err);
}
if (name == "pointsto_objcont_96_subproof") {
subproof_191(args, ret, err);
}
if (name == "pointsto_objcont_97_negation_subproof") {
subproof_192(args, ret, err);
}
if (name == "pointsto_objcont_97_subproof") {
subproof_193(args, ret, err);
}
if (name == "pointsto_objcont_98_negation_subproof") {
subproof_194(args, ret, err);
}
if (name == "pointsto_objcont_98_subproof") {
subproof_195(args, ret, err);
}
if (name == "pointsto_objcont_99_negation_subproof") {
subproof_196(args, ret, err);
}
if (name == "pointsto_objcont_99_subproof") {
subproof_197(args, ret, err);
}
if (name == "pointsto_objcont_9_negation_subproof") {
subproof_198(args, ret, err);
}
if (name == "pointsto_objcont_9_subproof") {
subproof_199(args, ret, err);
}
}
void subproof_0(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(73695),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(73695));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_1(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(73695),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[2],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[0],env1[1],env1[0],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_63(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[7]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(73695));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_2(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_11_store_op_ctxt,rel_11_store->createContext());
if(!rel_11_store->equalRange_7(Tuple<RamDomain,5>({{(args)[2],(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_11_store_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_3(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_11_store->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_11_store_op_ctxt,rel_11_store->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],(args)[1],0,0}});
auto range = rel_11_store->equalRange_7(key,READ_OP_CONTEXT(rel_11_store_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_4(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(3),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(3));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
if(!rel_7_load->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_7_load_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_5(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_7_load->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
const Tuple<RamDomain,3> key({{RamDomain(3),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{(args)[0],(args)[1],(args)[2],0,0}});
auto range = rel_7_load->equalRange_7(key,READ_OP_CONTEXT(rel_7_load_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[4]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_6(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(7),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(7));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
if(!rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{(args)[2],(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_7(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_12_pointsto_objcont->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(7),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],(args)[1],0,0}});
auto range = rel_12_pointsto_objcont->equalRange_7(key,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(7));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_8(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(69300),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(69300));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_9(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(69300),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[2],env1[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(69300));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_10(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(56630),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(56630));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_11(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(56630),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(56630));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_12(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(34295),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(34295));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_13(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(34295),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) && (((env2[1]) == (env2[2]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(34295));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_14(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(19791),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(19791));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
if(!rel_2_actual->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_2_actual_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_15(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_2_actual->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
const Tuple<RamDomain,3> key({{RamDomain(19791),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[2],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],(args)[1],env1[0],0,0}});
auto range = rel_2_actual->equalRange_7(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(19791));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_16(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(48017),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(48017));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_17(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(48017),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(48017));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_18(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(13813),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(13813));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
if(!rel_7_load->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_7_load_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_19(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_7_load->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
const Tuple<RamDomain,3> key({{RamDomain(13813),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[0],env1[1],(args)[2],0,0}});
auto range = rel_7_load->equalRange_7(key,READ_OP_CONTEXT(rel_7_load_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(13813));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_20(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(28791),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(28791));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_21(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(28791),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],(args)[2],env1[0],0,env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(28791));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_22(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(10),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(10));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
if(!rel_10_receiver_formal->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_23(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
const Tuple<RamDomain,3> key({{RamDomain(10),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_10_receiver_formal->equalRange_3(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(10));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_24(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(36691),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(36691));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_25(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(36691),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(36691));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_26(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(15217),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(15217));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_6_invocation_op_ctxt,rel_6_invocation->createContext());
if(!rel_6_invocation->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_invocation_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_27(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_6_invocation->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_6_invocation_op_ctxt,rel_6_invocation->createContext());
const Tuple<RamDomain,3> key({{RamDomain(15217),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[2],0,0}});
auto range = rel_6_invocation->equalRange_3(key,READ_OP_CONTEXT(rel_6_invocation_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(15217));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_28(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(27895),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(27895));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_29(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(27895),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(27895));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_30(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(35837),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(35837));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_31(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(35837),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(35837));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_32(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(86626),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(86626));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_33(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(86626),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(86626));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_34(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(22946),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(22946));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_35(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(22946),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],env1[0],env1[1],(args)[2],env1[1],0,0}});
auto range = rel_3_assign->equalRange_63(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[7]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(22946));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_36(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(84399),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(84399));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_37(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(84399),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],(args)[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(84399));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_38(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(18672),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(18672));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
if(!rel_2_actual->equalRange_7(Tuple<RamDomain,5>({{(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_2_actual_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_39(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_2_actual->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
const Tuple<RamDomain,3> key({{RamDomain(18672),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],(args)[2],env1[0],0,0}});
auto range = rel_2_actual->equalRange_7(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(18672));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_40(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(73858),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(73858));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_41(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(73858),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[2],env1[1],env1[0],env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(73858));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_42(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(28989),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(28989));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_43(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(28989),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(28989));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_44(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(6),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(6));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_11_store_op_ctxt,rel_11_store->createContext());
if(!rel_11_store->equalRange_7(Tuple<RamDomain,5>({{(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_11_store_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_45(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_11_store->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_11_store_op_ctxt,rel_11_store->createContext());
const Tuple<RamDomain,3> key({{RamDomain(6),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],(args)[0],0,0}});
auto range = rel_11_store->equalRange_7(key,READ_OP_CONTEXT(rel_11_store_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(6));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_46(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(78609),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(78609));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_47(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(78609),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(78609));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_48(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(35569),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(35569));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_49(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(35569),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[2],env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(35569));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_50(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(62907),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(62907));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_51(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(62907),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(62907));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_52(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(40656),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(40656));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_53(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40656),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[1],0,env1[0],env1[1],env1[1],0,0}});
auto range = rel_3_assign->equalRange_59(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[2]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(40656));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_54(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(19390),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(19390));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
if(!rel_2_actual->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_2_actual_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_55(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_2_actual->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
const Tuple<RamDomain,3> key({{RamDomain(19390),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],(args)[2],0,0}});
auto range = rel_2_actual->equalRange_7(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(19390));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_56(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(41025),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(41025));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[0],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_57(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(41025),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[2],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],env1[1],env1[1],(args)[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_63(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[7]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(41025));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_58(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(36249),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(36249));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_59(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(36249),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(36249));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_60(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(62351),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(62351));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_61(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(62351),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[2],env1[0],env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(62351));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_62(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2567),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2567));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_63(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2567),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],(args)[1],(args)[2],0,0,0,0,0}});
auto range = rel_3_assign->equalRange_7(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[2]) == (env1[5]))))) && (((env1[1]) == (env1[4]))))) && (((env1[0]) == (env1[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2567));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_64(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(40179),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(40179));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_65(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40179),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(40179));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_66(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(11),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(11));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
if(!rel_2_actual->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_2_actual_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_67(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_2_actual->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_actual_op_ctxt,rel_2_actual->createContext());
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
const Tuple<RamDomain,3> key({{RamDomain(11),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{(args)[0],(args)[1],(args)[2],0,0}});
auto range = rel_2_actual->equalRange_7(key,READ_OP_CONTEXT(rel_2_actual_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[4]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(11));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_68(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(59120),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(59120));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_69(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(59120),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(59120));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_70(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(78420),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(78420));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_71(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(78420),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],(args)[2],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(78420));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_72(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(64858),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(64858));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_73(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(64858),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(64858));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_74(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(28441),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(28441));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_75(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(28441),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(28441));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_76(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(47932),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(47932));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_77(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(47932),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(47932));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_78(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(40777),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(40777));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_79(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40777),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(40777));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_80(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(38959),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(38959));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_81(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(38959),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(38959));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_82(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(52193),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(52193));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_83(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(52193),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[1],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(52193));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_84(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(5063),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(5063));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_85(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(5063),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],(args)[0],(args)[2],0,0,0,0,0}});
auto range = rel_3_assign->equalRange_7(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[2]) == (env1[5]))))) && (((env1[0]) == (env1[3]))))) && (((env1[1]) == (env1[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(5063));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_86(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(63698),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(63698));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_87(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(63698),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(63698));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_88(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
if(!rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
if(!rel_10_receiver_formal->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_89(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_12_pointsto_objcont->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{(args)[0],(args)[1],(args)[2],0,0}});
auto range = rel_12_pointsto_objcont->equalRange_7(key,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[4]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_10_receiver_formal->equalRange_3(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_90(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(53306),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(53306));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[1],(args)[0],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_91(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(53306),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],(args)[1],env1[0],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(53306));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_92(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(64812),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(64812));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[0],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_93(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(64812),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],env1[0],env1[0],(args)[1],env1[1],0,0}});
auto range = rel_3_assign->equalRange_63(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[7]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(64812));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_94(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(79085),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(79085));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[0],(args)[2],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_95(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(79085),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[2],env1[1],env1[0],0,0,0,0}});
auto range = rel_3_assign->equalRange_15(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(79085));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_96(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(35495),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(35495));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_97(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(35495),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[0],env1[1],(args)[2],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[3]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(35495));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_98(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(43610),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(43610));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_99(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(43610),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(43610));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_100(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(33581),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(33581));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_101(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(33581),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[2],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],env1[1],env1[0],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(33581));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_102(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(88964),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(88964));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_103(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(88964),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[1],env1[0],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(88964));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_104(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(41537),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(41537));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[0],(args)[2],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_105(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(41537),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[2],env1[1],env1[0],0,0,0,0}});
auto range = rel_3_assign->equalRange_15(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[5]))))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(41537));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_106(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(6139),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(6139));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_107(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(6139),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],(args)[2],(args)[1],0,0,0,0,0}});
auto range = rel_3_assign->equalRange_7(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[1]) == (env1[5]))))) && (((env1[2]) == (env1[3]))))) && (((env1[0]) == (env1[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(6139));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_108(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(66026),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(66026));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_109(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(66026),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[0],(args)[1],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(66026));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_110(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(0),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(0));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
if(!rel_7_load->equalRange_7(Tuple<RamDomain,5>({{(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_7_load_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_111(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_7_load->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
const Tuple<RamDomain,3> key({{RamDomain(0),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{(args)[1],(args)[0],(args)[2],0,0}});
auto range = rel_7_load->equalRange_7(key,READ_OP_CONTEXT(rel_7_load_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[4]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_112(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(78281),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(78281));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_113(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(78281),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[0],(args)[1],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(78281));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_114(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(34234),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(34234));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[0],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_115(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(34234),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],env1[1],0,env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_27(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) && (((env2[0]) == (env2[2]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(34234));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_116(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(48347),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(48347));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[2],(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_117(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(48347),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],env1[1],env1[0],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(48347));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_118(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(36826),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(36826));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_119(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(36826),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[1],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(36826));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_120(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(19964),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(19964));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_121(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(19964),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(19964));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_122(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(70583),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(70583));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_123(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(70583),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(70583));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_124(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(9423),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(9423));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_125(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(9423),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],(args)[1],(args)[2],0,0,0,0,0}});
auto range = rel_3_assign->equalRange_7(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[2]) == (env1[5]))))) && (((env1[1]) == (env1[4]))))) && (((env1[0]) == (env1[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(9423));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_126(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(59394),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(59394));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_127(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(59394),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[1],0,env1[0],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_59(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[2]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(59394));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_128(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(8227),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(8227));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_129(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(8227),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],0,(args)[1],0,0,(args)[2],0,0}});
auto range = rel_3_assign->equalRange_37(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[2]) == (env1[3]))))) && (((env1[0]) == (env1[4]))))) && (((env1[0]) == (env1[1]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(8227));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[5]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[5]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_130(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(22304),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(22304));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[1],(args)[0],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_131(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(22304),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],0,env1[0],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_45(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[4]))))) && (((env2[0]) == (env2[1]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(22304));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_132(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(4),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(4));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
if(!rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
if(!rel_10_receiver_formal->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_133(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_12_pointsto_objcont->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(4),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{(args)[1],(args)[0],(args)[2],0,0}});
auto range = rel_12_pointsto_objcont->equalRange_7(key,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[4]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[2],env1[0],0,0}});
auto range = rel_10_receiver_formal->equalRange_3(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(4));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_134(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(21947),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(21947));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_135(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(21947),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(21947));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_136(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(82029),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(82029));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_137(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(82029),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(82029));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_138(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(79077),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(79077));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_139(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(79077),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(79077));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_140(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(4839),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(4839));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[0],(args)[1],(args)[2],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_141(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(4839),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],0,(args)[1],(args)[2],0,0,0,0}});
auto range = rel_3_assign->equalRange_13(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[3]) == (env1[4]))))) && (((env1[0]) == (env1[5]))))) && (((env1[0]) == (env1[1]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(4839));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_142(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(20846),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(20846));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_143(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(20846),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[1],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(20846));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_144(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(10458),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(10458));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_145(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(10458),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],(args)[1],(args)[2],0,0,0,0,0}});
auto range = rel_3_assign->equalRange_7(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[2]) == (env1[5]))))) && (((env1[1]) == (env1[4]))))) && (((env1[0]) == (env1[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(10458));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_146(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(25015),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(25015));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_147(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(25015),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(25015));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_148(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(65996),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(65996));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_149(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(65996),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],0,env1[0],env1[1],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(65996));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_150(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(34638),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(34638));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_151(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(34638),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[1],env1[1],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(34638));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_152(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(27604),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(27604));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_153(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(27604),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[2],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],(args)[1],env1[0],env1[1],0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(27604));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_154(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(8),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(8));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
if(!rel_10_receiver_formal->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_155(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_10_receiver_formal->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_10_receiver_formal_op_ctxt,rel_10_receiver_formal->createContext());
const Tuple<RamDomain,3> key({{RamDomain(8),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_10_receiver_formal->equalRange_3(key,READ_OP_CONTEXT(rel_10_receiver_formal_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(8));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_156(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(67769),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(67769));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_157(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(67769),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],0,env1[0],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_59(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[2]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(67769));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_158(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(63016),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(63016));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_159(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(63016),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(63016));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_160(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(42257),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(42257));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[0],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_161(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(42257),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[0],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(42257));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_162(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(24992),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(24992));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_163(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(24992),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(24992));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_164(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(32795),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(32795));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_165(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(32795),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[1],env1[1],env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_63(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[7]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(32795));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_166(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(3548),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(3548));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_167(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(3548),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],0,(args)[1],(args)[2],0,0,0,0}});
auto range = rel_3_assign->equalRange_13(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[3]) == (env1[5]))))) && (((env1[2]) == (env1[4]))))) && (((env1[0]) == (env1[1]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3548));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_168(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(41694),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(41694));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_169(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(41694),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(41694));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_170(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(64161),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(64161));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[2],(args)[0],(args)[1],(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_171(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(64161),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[2],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],env1[1],(args)[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[3]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(64161));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_172(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(14576),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(14576));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
if(!rel_7_load->equalRange_7(Tuple<RamDomain,5>({{(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_7_load_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_173(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_7_load->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_7_load_op_ctxt,rel_7_load->createContext());
const Tuple<RamDomain,3> key({{RamDomain(14576),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[0],env1[1],(args)[2],0,0}});
auto range = rel_7_load->equalRange_7(key,READ_OP_CONTEXT(rel_7_load_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(14576));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_174(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(43687),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(43687));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[0],(args)[2],(args)[2],(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_175(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(43687),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[0],env1[1],env1[1],env1[0],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(43687));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_176(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(9),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(9));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_177(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_8_points_initial->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
const Tuple<RamDomain,3> key({{RamDomain(9),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(9));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_178(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(7005),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(7005));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_179(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_1_Rule->empty())) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(7005),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],(args)[1],(args)[2],0,0,0,0,0}});
auto range = rel_3_assign->equalRange_7(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env1 : range) {
if( ((((((((env1[7]) < ((args)[3]))) && (((env1[2]) == (env1[5]))))) && (((env1[1]) == (env1[3]))))) && (((env1[0]) == (env1[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(7005));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[6]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
return;
}
void subproof_180(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(22493),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(22493));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[1],(args)[0],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_181(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(22493),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[0],env1[0],env1[0],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(22493));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_182(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(40917),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(40917));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_183(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(40917),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[1],env1[0],0,env1[1],env1[0],0,0}});
auto range = rel_3_assign->equalRange_55(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(40917));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_184(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(67708),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(67708));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_185(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(67708),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(67708));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_186(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(90086),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(90086));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_187(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(90086),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(90086));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_188(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(47927),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(47927));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_189(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(47927),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[1],env1[1],env1[0],0,env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_23(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[5]))))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(47927));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_190(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(86220),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(86220));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[2],(args)[1],(args)[0],(args)[2],(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
return;
}
void subproof_191(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(86220),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{(args)[2],env1[0],env1[1],0,0,env1[0],0,0}});
auto range = rel_3_assign->equalRange_39(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((((env2[7]) < ((args)[3]))) && (((env2[0]) == (env2[4]))))) && (((env2[0]) == (env2[3]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(86220));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_192(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(87963),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(87963));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_193(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(87963),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],env1[1],(args)[2],env1[0],env1[1],0,0,0}});
auto range = rel_3_assign->equalRange_31(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[5]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(87963));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_194(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(20685),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(20685));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[0],(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
return;
}
void subproof_195(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(20685),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[2],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[0],(args)[1],env1[1],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[1]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(20685));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_196(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(39726),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(39726));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
if(!rel_4_enclosing_type->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
if(!rel_3_assign->equalRange_63(Tuple<RamDomain,8>({{(args)[0],(args)[1],(args)[2],(args)[1],(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_assign_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_197(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_4_enclosing_type->empty())))) && (!(rel_3_assign->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_4_enclosing_type_op_ctxt,rel_4_enclosing_type->createContext());
CREATE_OP_CONTEXT(rel_3_assign_op_ctxt,rel_3_assign->createContext());
const Tuple<RamDomain,3> key({{RamDomain(39726),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_4_enclosing_type->equalRange_3(key,READ_OP_CONTEXT(rel_4_enclosing_type_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,8> key({{env1[1],env1[0],(args)[2],env1[0],0,env1[1],0,0}});
auto range = rel_3_assign->equalRange_47(key,READ_OP_CONTEXT(rel_3_assign_op_ctxt));
for(const auto& env2 : range) {
if( ((((env2[7]) < ((args)[3]))) && (((env2[2]) == (env2[4]))))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(39726));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[6]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[7]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
void subproof_198(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
if(!rel_1_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(5),0,0}}),READ_OP_CONTEXT(rel_1_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(5));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
if(!rel_8_points_initial->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_8_points_initial_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
if(!rel_12_pointsto_objcont->equalRange_7(Tuple<RamDomain,5>({{(args)[2],(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_199(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_1_Rule->empty())) && (!(rel_8_points_initial->empty())))) && (!(rel_12_pointsto_objcont->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Rule_op_ctxt,rel_1_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_points_initial_op_ctxt,rel_8_points_initial->createContext());
CREATE_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt,rel_12_pointsto_objcont->createContext());
const Tuple<RamDomain,3> key({{RamDomain(5),0,0}});
auto range = rel_1_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_1_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[3]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[2],0,0}});
auto range = rel_8_points_initial->equalRange_3(key,READ_OP_CONTEXT(rel_8_points_initial_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[3]))) {
const Tuple<RamDomain,5> key({{env1[1],env1[0],(args)[0],0,0}});
auto range = rel_12_pointsto_objcont->equalRange_7(key,READ_OP_CONTEXT(rel_12_pointsto_objcont_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[4]) < ((args)[3]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(5));
err.push_back(false);
ret.push_back(env0[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
ret.push_back(env2[4]);
err.push_back(false);
ret.push_back((args)[3]);
err.push_back(false);
}
}
}
}
}
}
}
}
return;
}
};
SouffleProgram *newInstance_souffle_small(){return new Sf_souffle_small;}
SymbolTable *getST_souffle_small(SouffleProgram *p){return &reinterpret_cast<Sf_souffle_small*>(p)->symTable;}

#ifdef __EMBEDDED_SOUFFLE__
class factory_Sf_souffle_small: public souffle::ProgramFactory {
SouffleProgram *newInstance() {
return new Sf_souffle_small();
};
public:
factory_Sf_souffle_small() : ProgramFactory("souffle_small"){}
};
static factory_Sf_souffle_small __factory_Sf_souffle_small_instance;
}
#else
}
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(rules.small.dl)",
R"(.)",
R"(.)",
false,
R"()",
1,
-1);
if (!opt.parse(argc,argv)) return 1;
#if defined(_OPENMP) 
omp_set_nested(true);

#endif
souffle::Sf_souffle_small obj;
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir(), opt.getStratumIndex());
explain(obj, false);
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}

#endif
