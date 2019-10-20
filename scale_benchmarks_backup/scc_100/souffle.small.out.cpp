
#include "souffle/CompiledSouffle.h"
#include <mutex>
#include "souffle/Explain.h"

extern "C" {
}

namespace souffle {
using namespace ram;
struct t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15 {
using t_tuple = Tuple<RamDomain, 4>;
struct updater_t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15 {
void update(t_tuple& old_t, const t_tuple& new_t) {
old_t[2] = new_t[2];
old_t[3] = new_t[3];
}
};
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,3,2>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<0,1>, updater_t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>;
t_ind_0 ind_0;
using t_ind_1 = btree_set<t_tuple, index_utils::comparator<1,0,2,3>, std::allocator<t_tuple>, 256, typename souffle::detail::default_strategy<t_tuple>::type, index_utils::comparator<1,0>, updater_t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>;
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
void insertAll(t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15& other) {
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
range<t_ind_1::iterator> equalRange_2(const t_tuple& t, context& h) const {
t_tuple low(t); t_tuple high(t);
low[0] = MIN_RAM_DOMAIN;
high[0] = MAX_RAM_DOMAIN;
low[2] = MIN_RAM_DOMAIN;
high[2] = MAX_RAM_DOMAIN;
low[3] = MIN_RAM_DOMAIN;
high[3] = MAX_RAM_DOMAIN;
return make_range(ind_1.lower_bound(low, h.hints_1), ind_1.upper_bound(high, h.hints_1));
}
range<t_ind_1::iterator> equalRange_2(const t_tuple& t) const {
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
range<t_ind_1::iterator> equalRange_15(const t_tuple& t, context& h) const {
auto pos = ind_1.find(t, h.hints_1);
auto fin = ind_1.end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<t_ind_1::iterator> equalRange_15(const t_tuple& t) const {
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
o << prefix << "arity 4 direct b-tree index [0,1,3,2]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
const auto& stats_1 = ind_1.getHintStatistics();
o << prefix << "arity 4 direct b-tree index [1,0,2,3]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_1.inserts.getHits() << "/" << stats_1.inserts.getMisses() << "/" << stats_1.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_1.contains.getHits() << "/" << stats_1.contains.getMisses() << "/" << stats_1.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_1.lower_bound.getHits() << "/" << stats_1.lower_bound.getMisses() << "/" << stats_1.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_1.upper_bound.getHits() << "/" << stats_1.upper_bound.getMisses() << "/" << stats_1.upper_bound.getAccesses() << "\n";
}
};
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
struct t_btree_7__0_1_2_3_4_5_6__127 {
using t_tuple = Tuple<RamDomain, 7>;
Table<t_tuple> dataTable;
Lock insert_lock;
using t_ind_0 = btree_set<const t_tuple*, index_utils::deref_compare<typename index_utils::comparator<0,1,2,3,4,5,6>>>;
t_ind_0 ind_0;
using iterator_0 = IterDerefWrapper<typename t_ind_0::iterator>;
using iterator = iterator_0;
struct context {
t_ind_0::operation_hints hints_0;
};
context createContext() { return context(); }
bool insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool insert(const t_tuple& t, context& h) {
const t_tuple* masterCopy = nullptr;
{
auto lease = insert_lock.acquire();
if (contains(t, h)) return false;
masterCopy = &dataTable.insert(t);
ind_0.insert(masterCopy, h.hints_0);
}
return true;
}
bool insert(const RamDomain* ramDomain) {
RamDomain data[7];
std::copy(ramDomain, ramDomain + 7, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4,RamDomain a5,RamDomain a6) {
RamDomain data[7] = {a0,a1,a2,a3,a4,a5,a6};
return insert(data);
}
template <typename T>
void insertAll(T& other) {
for (auto const& cur : other) {
insert(cur);
}
}
bool contains(const t_tuple& t, context& h) const {
return ind_0.contains(&t, h.hints_0);
}
bool contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t size() const {
return ind_0.size();
}
iterator find(const t_tuple& t, context& h) const {
return ind_0.find(&t, h.hints_0);
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
range<iterator_0> equalRange_127(const t_tuple& t, context& h) const {
auto pos = find(t, h);
auto fin = end();
if (pos != fin) {fin = pos; ++fin;}
return make_range(pos, fin);
}
range<iterator_0> equalRange_127(const t_tuple& t) const {
context h; return equalRange_127(t, h);
}
bool empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> partition() const {
std::vector<range<iterator>> res;
for (const auto& cur : ind_0.getChunks(400)) {
    res.push_back(make_range(derefIter(cur.begin()), derefIter(cur.end())));
}
return res;
}
void purge() {
ind_0.clear();
dataTable.clear();
}
iterator begin() const {
return ind_0.begin();
}
iterator end() const {
return ind_0.end();
}
void printHintStatistics(std::ostream& o, const std::string prefix) const {
const auto& stats_0 = ind_0.getHintStatistics();
o << prefix << "arity 7 indirect b-tree index [0,1,2,3,4,5,6]: (hits/misses/total)\n";
o << prefix << "Insert: " << stats_0.inserts.getHits() << "/" << stats_0.inserts.getMisses() << "/" << stats_0.inserts.getAccesses() << "\n";
o << prefix << "Contains: " << stats_0.contains.getHits() << "/" << stats_0.contains.getMisses() << "/" << stats_0.contains.getAccesses() << "\n";
o << prefix << "Lower-bound: " << stats_0.lower_bound.getHits() << "/" << stats_0.lower_bound.getMisses() << "/" << stats_0.lower_bound.getAccesses() << "\n";
o << prefix << "Upper-bound: " << stats_0.upper_bound.getHits() << "/" << stats_0.upper_bound.getMisses() << "/" << stats_0.upper_bound.getAccesses() << "\n";
}
};
struct t_btree_6__0_1_2_3_4_5__63 {
using t_tuple = Tuple<RamDomain, 6>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4,5>>;
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
struct t_btree_5__0_1_2_3_4__31 {
using t_tuple = Tuple<RamDomain, 5>;
using t_ind_0 = btree_set<t_tuple, index_utils::comparator<0,1,2,3,4>>;
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
	R"_(v0,v1)_",
	R"_(Rule)_",
	R"_(Edge,v2,v0)_",
	R"_(SCC,v2,v0)_",
	R"_(Edge,v2,v1)_",
	R"_(SCC(v0,v1) :- 
   Rule(1125),
   Edge(v2,v0),
   SCC(v2,v0),
   Edge(v2,v1).)_",
	R"_(invent_Path,v0,v1)_",
	R"_(SCC,v0,v1)_",
	R"_(SCC(v0,v1) :- 
   Rule(1797),
   invent_Path(v0,v1),
   SCC(v0,v1).)_",
	R"_(invent_Path,v1,v0)_",
	R"_(SCC,v1,v0)_",
	R"_(SCC(v0,v1) :- 
   Rule(1948),
   invent_Path(v1,v0),
   SCC(v1,v0).)_",
	R"_(invent_Path,v2,v0)_",
	R"_(invent_Path,v1,v2)_",
	R"_(SCC(v0,v1) :- 
   Rule(1714),
   invent_Path(v0,v1),
   invent_Path(v2,v0),
   invent_Path(v1,v2).)_",
	R"_(invent_Path,v2,v1)_",
	R"_(SCC,v0,v2)_",
	R"_(SCC(v0,v1) :- 
   Rule(1992),
   invent_Path(v2,v1),
   SCC(v1,v0),
   SCC(v0,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1741),
   invent_Path(v2,v0),
   invent_Path(v1,v2).)_",
	R"_(SCC,v2,v1)_",
	R"_(SCC(v0,v1) :- 
   Rule(1933),
   invent_Path(v2,v1),
   SCC(v2,v1),
   invent_Path(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1791),
   invent_Path(v1,v0),
   invent_Path(v0,v1),
   SCC(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(692),
   invent_Path(v0,v1),
   invent_Path(v1,v0).)_",
	R"_(Edge,v1,v2)_",
	R"_(SCC,v1,v2)_",
	R"_(SCC(v0,v1) :- 
   Rule(1596),
   Edge(v1,v2),
   SCC(v1,v2),
   SCC(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1163),
   Edge(v1,v2),
   Edge(v2,v1),
   SCC(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2177),
   SCC(v0,v2),
   SCC(v2,v0),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2001),
   invent_Path(v0,v1),
   SCC(v0,v2),
   SCC(v1,v2).)_",
	R"_(Edge,v0,v1)_",
	R"_(Edge,v0,v2)_",
	R"_(SCC(v0,v1) :- 
   Rule(773),
   Edge(v0,v1),
   Edge(v1,v2),
   Edge(v0,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(874),
   Edge(v2,v1),
   Edge(v0,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(859),
   Edge(v1,v2),
   Edge(v2,v1),
   Edge(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(878),
   Edge(v0,v1),
   invent_Path(v1,v0).)_",
	R"_(Edge,v1,v0)_",
	R"_(SCC(v0,v1) :- 
   Rule(1600),
   Edge(v1,v0),
   SCC(v2,v1),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1425),
   Edge(v0,v2),
   invent_Path(v2,v0),
   SCC(v1,v2).)_",
	R"_(invent_Path,v1)_",
	R"_(SCC(v0,v1) :- 
   Rule(1905),
   invent_Path(v1,_),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1689),
   invent_Path(v2,v0),
   invent_Path(v1,v2),
   invent_Path(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1866),
   invent_Path(v0,v1),
   invent_Path(v2,v0),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1335),
   Edge(v1,v0),
   invent_Path(v0,v1),
   SCC(v0,v1).)_",
	R"_(invent_Path,v0,v2)_",
	R"_(SCC(v0,v1) :- 
   Rule(1436),
   Edge(v0,v2),
   invent_Path(v0,v2),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1065),
   Edge(v2,v1),
   Edge(v0,v2),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1166),
   Edge(v2,v0),
   Edge(v2,v1),
   SCC(v2,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1360),
   Edge(v0,v2),
   invent_Path(v2,v0),
   SCC(v0,v1).)_",
	R"_(SCC,v0)_",
	R"_(SCC(v0,v1) :- 
   Rule(1972),
   invent_Path(v1,v0),
   SCC(_,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1930),
   invent_Path(v2,v0),
   invent_Path(v2,v1),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1893),
   invent_Path(v2,v0),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1058),
   Edge(v0,v1),
   Edge(v0,v2),
   SCC(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1717),
   invent_Path(v1,v0),
   invent_Path(v2,v1),
   invent_Path(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1159),
   Edge(v0,v2),
   Edge(v2,v1),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1599),
   Edge(v1,v2),
   SCC(v2,v1),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2139),
   SCC(v2,v0),
   SCC(v2,v1),
   SCC(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(885),
   Edge(v0,v1),
   invent_Path(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1848),
   invent_Path(v2,v1),
   invent_Path(v0,v1),
   SCC(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1162),
   Edge(v2,v1),
   Edge(v1,v2),
   SCC(v0,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1658),
   invent_Path(v2,v0),
   invent_Path(v0,v2),
   invent_Path(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1813),
   invent_Path(v2,v0),
   invent_Path(v0,v2),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1071),
   Edge(v1,v2),
   Edge(v2,v0),
   SCC(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1842),
   invent_Path(v2,v0),
   invent_Path(v2,v1),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1204),
   Edge(v2,v0),
   invent_Path(v0,v2),
   invent_Path(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1096),
   Edge(v1,v2),
   Edge(v0,v1),
   SCC(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2184),
   SCC(v0,v2),
   SCC(v2,v0),
   SCC(v2,v1).)_",
	R"_(Edge,v0)_",
	R"_(SCC(v0,v1) :- 
   Rule(740),
   Edge(v0,v1),
   Edge(_,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1571),
   Edge(v0,v2),
   SCC(v0,v2),
   SCC(v2,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1587),
   Edge(v2,v0),
   SCC(v2,v0),
   SCC(v2,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1712),
   invent_Path(v1,v2),
   invent_Path(v0,v2),
   invent_Path(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(699),
   invent_Path(v2,v0),
   invent_Path(v2,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(823),
   Edge(v1,v2),
   Edge(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1338),
   Edge(v0,v1),
   invent_Path(v1,v0),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(994),
   Edge(v1,v2),
   invent_Path(v2,v1),
   Edge(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(684),
   Edge(v1,v2),
   SCC(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2015),
   invent_Path(v0,v2),
   SCC(v0,v1),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(854),
   Edge(v0,v2),
   Edge(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1336),
   Edge(v1,v0),
   invent_Path(v0,v1),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1143),
   Edge(v1,v2),
   Edge(v2,v1),
   SCC(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(985),
   Edge(v1,v2),
   Edge(v2,v1),
   invent_Path(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(733),
   Edge(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1075),
   Edge(v2,v0),
   Edge(v2,v1),
   SCC(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1783),
   invent_Path(v2,v1),
   invent_Path(v1,v2),
   invent_Path(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1540),
   Edge(v2,v0),
   SCC(v0,v1),
   SCC(v1,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1951),
   invent_Path(v0,v2),
   SCC(v2,v0),
   SCC(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(914),
   Edge(v1,v2),
   Edge(v0,v2),
   invent_Path(v1,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1771),
   invent_Path(v1,v2),
   invent_Path(v2,v1),
   invent_Path(v2,v0).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1734),
   invent_Path(v1,v2),
   invent_Path(v2,v0),
   invent_Path(v0,v2).)_",
	R"_(SCC(v0,v1) :- 
   Rule(1695),
   invent_Path(v2,v1),
   invent_Path(v2,v0),
   invent_Path(v0,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2019),
   invent_Path(v0,v1),
   SCC(v0,v2),
   SCC(v2,v1).)_",
	R"_(SCC(v0,v1) :- 
   Rule(2243),
   SCC(v0,v2),
   SCC(v1,v2),
   SCC(v2,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(238),
   Edge(v0,v1),
   Edge(v2,v1),
   invent_Path(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(0),
   Edge(v0,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(456),
   Edge(v2,v1),
   invent_Path(v1,v2),
   invent_Path(v1,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(77),
   Edge(v2,v1),
   Edge(v0,v1),
   Edge(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(99),
   Edge(v0,v1),
   Edge(v0,v2),
   Edge(v1,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(202),
   Edge(v2,v0),
   invent_Path(v0,v2),
   Edge(v1,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(174),
   Edge(v1,v2),
   Edge(v2,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(525),
   invent_Path(v1,v0),
   invent_Path(v2,v0),
   invent_Path(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(123),
   Edge(v0,v2),
   Edge(v2,v0),
   Edge(v1,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(188),
   Edge(v2,v1),
   Edge(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(607),
   invent_Path(v1,_),
   invent_Path(v0,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(142),
   Edge(v0,v2),
   Edge(v1,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(69),
   Edge(v1,v0),
   Edge(v2,v0),
   Edge(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(483),
   Edge(v1,v2),
   invent_Path(v2,v1),
   invent_Path(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(592),
   invent_Path(v1,v2),
   invent_Path(v2,v0),
   invent_Path(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(48),
   Edge(v0,_),
   Edge(v0,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(214),
   Edge(v2,v0),
   Edge(v0,v2),
   invent_Path(v0,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(73),
   Edge(v1,v2),
   Edge(v1,v0),
   Edge(v2,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(23),
   Edge(v0,v2),
   invent_Path(v2,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(187),
   Edge(v2,v1),
   Edge(v2,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(106),
   Edge(v1,v2),
   Edge(v0,v1),
   Edge(v2,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(178),
   Edge(v2,v0),
   Edge(v1,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(184),
   Edge(v2,v1),
   Edge(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(603),
   invent_Path(v1,v2),
   invent_Path(v2,v1),
   invent_Path(v0,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(207),
   Edge(v1,v0),
   Edge(v0,v2),
   invent_Path(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(297),
   Edge(v2,v1),
   Edge(v1,v2),
   invent_Path(v0,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(176),
   Edge(v2,v0),
   Edge(v2,v1).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(53),
   Edge(v0,v1),
   Edge(v2,v0),
   Edge(v0,v2).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(512),
   invent_Path(v1,v0),
   invent_Path(v0,v2),
   invent_Path(v2,v0).)_",
	R"_(invent_Path(v0,v1) :- 
   Rule(210),
   Edge(v0,_),
   invent_Path(v1,v0).)_",
};// -- Table: Edge
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_1_Edge = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
souffle::RelationWrapper<0,t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15,Tuple<RamDomain,4>,4> wrapper_rel_1_Edge;
// -- Table: Rule
std::unique_ptr<t_btree_3__0_1_2__1__7> rel_2_Rule = std::make_unique<t_btree_3__0_1_2__1__7>();
souffle::RelationWrapper<1,t_btree_3__0_1_2__1__7,Tuple<RamDomain,3>,3> wrapper_rel_2_Rule;
// -- Table: invent_Path
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_3_invent_Path = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
souffle::RelationWrapper<2,t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15,Tuple<RamDomain,4>,4> wrapper_rel_3_invent_Path;
// -- Table: @delta_invent_Path
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_4_delta_invent_Path = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
// -- Table: @new_invent_Path
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_5_new_invent_Path = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
// -- Table: SCC
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_6_SCC = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
souffle::RelationWrapper<3,t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15,Tuple<RamDomain,4>,4> wrapper_rel_6_SCC;
// -- Table: @delta_SCC
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_7_delta_SCC = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
// -- Table: @new_SCC
std::unique_ptr<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15> rel_8_new_SCC = std::make_unique<t_btree_4__0_1_3_2__1_0_2_3__1__2__3__15>();
// -- Table: SCC.@info.1
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_9_SCC_info_1 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<4,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_9_SCC_info_1;
// -- Table: SCC.@info.10
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_10_SCC_info_10 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<5,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_10_SCC_info_10;
// -- Table: SCC.@info.11
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_11_SCC_info_11 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<6,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_11_SCC_info_11;
// -- Table: SCC.@info.12
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_12_SCC_info_12 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<7,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_12_SCC_info_12;
// -- Table: SCC.@info.13
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_13_SCC_info_13 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<8,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_13_SCC_info_13;
// -- Table: SCC.@info.14
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_14_SCC_info_14 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<9,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_14_SCC_info_14;
// -- Table: SCC.@info.15
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_15_SCC_info_15 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<10,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_15_SCC_info_15;
// -- Table: SCC.@info.16
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_16_SCC_info_16 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<11,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_16_SCC_info_16;
// -- Table: SCC.@info.17
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_17_SCC_info_17 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<12,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_17_SCC_info_17;
// -- Table: SCC.@info.18
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_18_SCC_info_18 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<13,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_18_SCC_info_18;
// -- Table: SCC.@info.19
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_19_SCC_info_19 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<14,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_19_SCC_info_19;
// -- Table: SCC.@info.2
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_20_SCC_info_2 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<15,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_20_SCC_info_2;
// -- Table: SCC.@info.20
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_21_SCC_info_20 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<16,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_21_SCC_info_20;
// -- Table: SCC.@info.21
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_22_SCC_info_21 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<17,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_22_SCC_info_21;
// -- Table: SCC.@info.22
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_23_SCC_info_22 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<18,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_23_SCC_info_22;
// -- Table: SCC.@info.23
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_24_SCC_info_23 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<19,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_24_SCC_info_23;
// -- Table: SCC.@info.24
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_25_SCC_info_24 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<20,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_25_SCC_info_24;
// -- Table: SCC.@info.25
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_26_SCC_info_25 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<21,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_26_SCC_info_25;
// -- Table: SCC.@info.26
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_27_SCC_info_26 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<22,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_27_SCC_info_26;
// -- Table: SCC.@info.27
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_28_SCC_info_27 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<23,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_28_SCC_info_27;
// -- Table: SCC.@info.28
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_29_SCC_info_28 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<24,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_29_SCC_info_28;
// -- Table: SCC.@info.29
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_30_SCC_info_29 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<25,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_30_SCC_info_29;
// -- Table: SCC.@info.3
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_31_SCC_info_3 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<26,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_31_SCC_info_3;
// -- Table: SCC.@info.30
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_32_SCC_info_30 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<27,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_32_SCC_info_30;
// -- Table: SCC.@info.31
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_33_SCC_info_31 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<28,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_33_SCC_info_31;
// -- Table: SCC.@info.32
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_34_SCC_info_32 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<29,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_34_SCC_info_32;
// -- Table: SCC.@info.33
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_35_SCC_info_33 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<30,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_35_SCC_info_33;
// -- Table: SCC.@info.34
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_36_SCC_info_34 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<31,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_36_SCC_info_34;
// -- Table: SCC.@info.35
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_37_SCC_info_35 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<32,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_37_SCC_info_35;
// -- Table: SCC.@info.36
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_38_SCC_info_36 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<33,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_38_SCC_info_36;
// -- Table: SCC.@info.37
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_39_SCC_info_37 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<34,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_39_SCC_info_37;
// -- Table: SCC.@info.38
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_40_SCC_info_38 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<35,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_40_SCC_info_38;
// -- Table: SCC.@info.39
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_41_SCC_info_39 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<36,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_41_SCC_info_39;
// -- Table: SCC.@info.4
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_42_SCC_info_4 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<37,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_42_SCC_info_4;
// -- Table: SCC.@info.40
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_43_SCC_info_40 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<38,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_43_SCC_info_40;
// -- Table: SCC.@info.41
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_44_SCC_info_41 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<39,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_44_SCC_info_41;
// -- Table: SCC.@info.42
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_45_SCC_info_42 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<40,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_45_SCC_info_42;
// -- Table: SCC.@info.43
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_46_SCC_info_43 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<41,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_46_SCC_info_43;
// -- Table: SCC.@info.44
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_47_SCC_info_44 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<42,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_47_SCC_info_44;
// -- Table: SCC.@info.45
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_48_SCC_info_45 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<43,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_48_SCC_info_45;
// -- Table: SCC.@info.46
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_49_SCC_info_46 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<44,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_49_SCC_info_46;
// -- Table: SCC.@info.47
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_50_SCC_info_47 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<45,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_50_SCC_info_47;
// -- Table: SCC.@info.48
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_51_SCC_info_48 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<46,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_51_SCC_info_48;
// -- Table: SCC.@info.49
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_52_SCC_info_49 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<47,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_52_SCC_info_49;
// -- Table: SCC.@info.5
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_53_SCC_info_5 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<48,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_53_SCC_info_5;
// -- Table: SCC.@info.50
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_54_SCC_info_50 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<49,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_54_SCC_info_50;
// -- Table: SCC.@info.51
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_55_SCC_info_51 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<50,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_55_SCC_info_51;
// -- Table: SCC.@info.52
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_56_SCC_info_52 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<51,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_56_SCC_info_52;
// -- Table: SCC.@info.53
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_57_SCC_info_53 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<52,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_57_SCC_info_53;
// -- Table: SCC.@info.54
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_58_SCC_info_54 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<53,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_58_SCC_info_54;
// -- Table: SCC.@info.55
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_59_SCC_info_55 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<54,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_59_SCC_info_55;
// -- Table: SCC.@info.56
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_60_SCC_info_56 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<55,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_60_SCC_info_56;
// -- Table: SCC.@info.57
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_61_SCC_info_57 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<56,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_61_SCC_info_57;
// -- Table: SCC.@info.58
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_62_SCC_info_58 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<57,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_62_SCC_info_58;
// -- Table: SCC.@info.59
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_63_SCC_info_59 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<58,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_63_SCC_info_59;
// -- Table: SCC.@info.6
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_64_SCC_info_6 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<59,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_64_SCC_info_6;
// -- Table: SCC.@info.60
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_65_SCC_info_60 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<60,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_65_SCC_info_60;
// -- Table: SCC.@info.61
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_66_SCC_info_61 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<61,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_66_SCC_info_61;
// -- Table: SCC.@info.62
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_67_SCC_info_62 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<62,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_67_SCC_info_62;
// -- Table: SCC.@info.63
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_68_SCC_info_63 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<63,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_68_SCC_info_63;
// -- Table: SCC.@info.64
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_69_SCC_info_64 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<64,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_69_SCC_info_64;
// -- Table: SCC.@info.65
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_70_SCC_info_65 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<65,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_70_SCC_info_65;
// -- Table: SCC.@info.66
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_71_SCC_info_66 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<66,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_71_SCC_info_66;
// -- Table: SCC.@info.67
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_72_SCC_info_67 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<67,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_72_SCC_info_67;
// -- Table: SCC.@info.68
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_73_SCC_info_68 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<68,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_73_SCC_info_68;
// -- Table: SCC.@info.69
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_74_SCC_info_69 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<69,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_74_SCC_info_69;
// -- Table: SCC.@info.7
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_75_SCC_info_7 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<70,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_75_SCC_info_7;
// -- Table: SCC.@info.70
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_76_SCC_info_70 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<71,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_76_SCC_info_70;
// -- Table: SCC.@info.8
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_77_SCC_info_8 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<72,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_77_SCC_info_8;
// -- Table: SCC.@info.9
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_78_SCC_info_9 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<73,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_78_SCC_info_9;
// -- Table: invent_Path.@info.1
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_79_invent_Path_info_1 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<74,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_79_invent_Path_info_1;
// -- Table: invent_Path.@info.10
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_80_invent_Path_info_10 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<75,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_80_invent_Path_info_10;
// -- Table: invent_Path.@info.11
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_81_invent_Path_info_11 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<76,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_81_invent_Path_info_11;
// -- Table: invent_Path.@info.12
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_82_invent_Path_info_12 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<77,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_82_invent_Path_info_12;
// -- Table: invent_Path.@info.13
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_83_invent_Path_info_13 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<78,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_83_invent_Path_info_13;
// -- Table: invent_Path.@info.14
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_84_invent_Path_info_14 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<79,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_84_invent_Path_info_14;
// -- Table: invent_Path.@info.15
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_85_invent_Path_info_15 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<80,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_85_invent_Path_info_15;
// -- Table: invent_Path.@info.16
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_86_invent_Path_info_16 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<81,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_86_invent_Path_info_16;
// -- Table: invent_Path.@info.17
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_87_invent_Path_info_17 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<82,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_87_invent_Path_info_17;
// -- Table: invent_Path.@info.18
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_88_invent_Path_info_18 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<83,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_88_invent_Path_info_18;
// -- Table: invent_Path.@info.19
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_89_invent_Path_info_19 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<84,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_89_invent_Path_info_19;
// -- Table: invent_Path.@info.2
std::unique_ptr<t_btree_5__0_1_2_3_4__31> rel_90_invent_Path_info_2 = std::make_unique<t_btree_5__0_1_2_3_4__31>();
souffle::RelationWrapper<85,t_btree_5__0_1_2_3_4__31,Tuple<RamDomain,5>,5> wrapper_rel_90_invent_Path_info_2;
// -- Table: invent_Path.@info.20
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_91_invent_Path_info_20 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<86,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_91_invent_Path_info_20;
// -- Table: invent_Path.@info.21
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_92_invent_Path_info_21 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<87,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_92_invent_Path_info_21;
// -- Table: invent_Path.@info.22
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_93_invent_Path_info_22 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<88,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_93_invent_Path_info_22;
// -- Table: invent_Path.@info.23
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_94_invent_Path_info_23 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<89,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_94_invent_Path_info_23;
// -- Table: invent_Path.@info.24
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_95_invent_Path_info_24 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<90,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_95_invent_Path_info_24;
// -- Table: invent_Path.@info.25
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_96_invent_Path_info_25 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<91,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_96_invent_Path_info_25;
// -- Table: invent_Path.@info.26
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_97_invent_Path_info_26 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<92,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_97_invent_Path_info_26;
// -- Table: invent_Path.@info.27
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_98_invent_Path_info_27 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<93,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_98_invent_Path_info_27;
// -- Table: invent_Path.@info.28
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_99_invent_Path_info_28 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<94,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_99_invent_Path_info_28;
// -- Table: invent_Path.@info.29
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_100_invent_Path_info_29 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<95,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_100_invent_Path_info_29;
// -- Table: invent_Path.@info.3
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_101_invent_Path_info_3 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<96,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_101_invent_Path_info_3;
// -- Table: invent_Path.@info.30
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_102_invent_Path_info_30 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<97,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_102_invent_Path_info_30;
// -- Table: invent_Path.@info.4
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_103_invent_Path_info_4 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<98,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_103_invent_Path_info_4;
// -- Table: invent_Path.@info.5
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_104_invent_Path_info_5 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<99,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_104_invent_Path_info_5;
// -- Table: invent_Path.@info.6
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_105_invent_Path_info_6 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<100,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_105_invent_Path_info_6;
// -- Table: invent_Path.@info.7
std::unique_ptr<t_btree_6__0_1_2_3_4_5__63> rel_106_invent_Path_info_7 = std::make_unique<t_btree_6__0_1_2_3_4_5__63>();
souffle::RelationWrapper<101,t_btree_6__0_1_2_3_4_5__63,Tuple<RamDomain,6>,6> wrapper_rel_106_invent_Path_info_7;
// -- Table: invent_Path.@info.8
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_107_invent_Path_info_8 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<102,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_107_invent_Path_info_8;
// -- Table: invent_Path.@info.9
std::unique_ptr<t_btree_7__0_1_2_3_4_5_6__127> rel_108_invent_Path_info_9 = std::make_unique<t_btree_7__0_1_2_3_4_5_6__127>();
souffle::RelationWrapper<103,t_btree_7__0_1_2_3_4_5_6__127,Tuple<RamDomain,7>,7> wrapper_rel_108_invent_Path_info_9;
public:
Sf_souffle_small() : 
wrapper_rel_1_Edge(*rel_1_Edge,symTable,"Edge",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_2_Rule(*rel_2_Rule,symTable,"Rule",std::array<const char *,3>{{"i:number","i:number","i:number"}},std::array<const char *,3>{{"n","@rule_number","@level_number"}}),

wrapper_rel_3_invent_Path(*rel_3_invent_Path,symTable,"invent_Path",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_6_SCC(*rel_6_SCC,symTable,"SCC",std::array<const char *,4>{{"s:V","s:V","i:number","i:number"}},std::array<const char *,4>{{"v0","v1","@rule_number","@level_number"}}),

wrapper_rel_9_SCC_info_1(*rel_9_SCC_info_1,symTable,"SCC.@info.1",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_10_SCC_info_10(*rel_10_SCC_info_10,symTable,"SCC.@info.10",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_11_SCC_info_11(*rel_11_SCC_info_11,symTable,"SCC.@info.11",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_12_SCC_info_12(*rel_12_SCC_info_12,symTable,"SCC.@info.12",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_13_SCC_info_13(*rel_13_SCC_info_13,symTable,"SCC.@info.13",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_14_SCC_info_14(*rel_14_SCC_info_14,symTable,"SCC.@info.14",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_15_SCC_info_15(*rel_15_SCC_info_15,symTable,"SCC.@info.15",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_16_SCC_info_16(*rel_16_SCC_info_16,symTable,"SCC.@info.16",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_17_SCC_info_17(*rel_17_SCC_info_17,symTable,"SCC.@info.17",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_18_SCC_info_18(*rel_18_SCC_info_18,symTable,"SCC.@info.18",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_19_SCC_info_19(*rel_19_SCC_info_19,symTable,"SCC.@info.19",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_20_SCC_info_2(*rel_20_SCC_info_2,symTable,"SCC.@info.2",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_21_SCC_info_20(*rel_21_SCC_info_20,symTable,"SCC.@info.20",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_22_SCC_info_21(*rel_22_SCC_info_21,symTable,"SCC.@info.21",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_23_SCC_info_22(*rel_23_SCC_info_22,symTable,"SCC.@info.22",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_24_SCC_info_23(*rel_24_SCC_info_23,symTable,"SCC.@info.23",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_25_SCC_info_24(*rel_25_SCC_info_24,symTable,"SCC.@info.24",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_26_SCC_info_25(*rel_26_SCC_info_25,symTable,"SCC.@info.25",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_27_SCC_info_26(*rel_27_SCC_info_26,symTable,"SCC.@info.26",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_28_SCC_info_27(*rel_28_SCC_info_27,symTable,"SCC.@info.27",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_29_SCC_info_28(*rel_29_SCC_info_28,symTable,"SCC.@info.28",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_30_SCC_info_29(*rel_30_SCC_info_29,symTable,"SCC.@info.29",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_31_SCC_info_3(*rel_31_SCC_info_3,symTable,"SCC.@info.3",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_32_SCC_info_30(*rel_32_SCC_info_30,symTable,"SCC.@info.30",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_33_SCC_info_31(*rel_33_SCC_info_31,symTable,"SCC.@info.31",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_34_SCC_info_32(*rel_34_SCC_info_32,symTable,"SCC.@info.32",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_35_SCC_info_33(*rel_35_SCC_info_33,symTable,"SCC.@info.33",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_36_SCC_info_34(*rel_36_SCC_info_34,symTable,"SCC.@info.34",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_37_SCC_info_35(*rel_37_SCC_info_35,symTable,"SCC.@info.35",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_38_SCC_info_36(*rel_38_SCC_info_36,symTable,"SCC.@info.36",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_39_SCC_info_37(*rel_39_SCC_info_37,symTable,"SCC.@info.37",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_40_SCC_info_38(*rel_40_SCC_info_38,symTable,"SCC.@info.38",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_41_SCC_info_39(*rel_41_SCC_info_39,symTable,"SCC.@info.39",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_42_SCC_info_4(*rel_42_SCC_info_4,symTable,"SCC.@info.4",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_43_SCC_info_40(*rel_43_SCC_info_40,symTable,"SCC.@info.40",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_44_SCC_info_41(*rel_44_SCC_info_41,symTable,"SCC.@info.41",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_45_SCC_info_42(*rel_45_SCC_info_42,symTable,"SCC.@info.42",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_46_SCC_info_43(*rel_46_SCC_info_43,symTable,"SCC.@info.43",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_47_SCC_info_44(*rel_47_SCC_info_44,symTable,"SCC.@info.44",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_48_SCC_info_45(*rel_48_SCC_info_45,symTable,"SCC.@info.45",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_49_SCC_info_46(*rel_49_SCC_info_46,symTable,"SCC.@info.46",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_50_SCC_info_47(*rel_50_SCC_info_47,symTable,"SCC.@info.47",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_51_SCC_info_48(*rel_51_SCC_info_48,symTable,"SCC.@info.48",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_52_SCC_info_49(*rel_52_SCC_info_49,symTable,"SCC.@info.49",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_53_SCC_info_5(*rel_53_SCC_info_5,symTable,"SCC.@info.5",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_54_SCC_info_50(*rel_54_SCC_info_50,symTable,"SCC.@info.50",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_55_SCC_info_51(*rel_55_SCC_info_51,symTable,"SCC.@info.51",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_56_SCC_info_52(*rel_56_SCC_info_52,symTable,"SCC.@info.52",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_57_SCC_info_53(*rel_57_SCC_info_53,symTable,"SCC.@info.53",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_58_SCC_info_54(*rel_58_SCC_info_54,symTable,"SCC.@info.54",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_59_SCC_info_55(*rel_59_SCC_info_55,symTable,"SCC.@info.55",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_60_SCC_info_56(*rel_60_SCC_info_56,symTable,"SCC.@info.56",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_61_SCC_info_57(*rel_61_SCC_info_57,symTable,"SCC.@info.57",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_62_SCC_info_58(*rel_62_SCC_info_58,symTable,"SCC.@info.58",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_63_SCC_info_59(*rel_63_SCC_info_59,symTable,"SCC.@info.59",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_64_SCC_info_6(*rel_64_SCC_info_6,symTable,"SCC.@info.6",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_65_SCC_info_60(*rel_65_SCC_info_60,symTable,"SCC.@info.60",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_66_SCC_info_61(*rel_66_SCC_info_61,symTable,"SCC.@info.61",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_67_SCC_info_62(*rel_67_SCC_info_62,symTable,"SCC.@info.62",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_68_SCC_info_63(*rel_68_SCC_info_63,symTable,"SCC.@info.63",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_69_SCC_info_64(*rel_69_SCC_info_64,symTable,"SCC.@info.64",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_70_SCC_info_65(*rel_70_SCC_info_65,symTable,"SCC.@info.65",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_71_SCC_info_66(*rel_71_SCC_info_66,symTable,"SCC.@info.66",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_72_SCC_info_67(*rel_72_SCC_info_67,symTable,"SCC.@info.67",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_73_SCC_info_68(*rel_73_SCC_info_68,symTable,"SCC.@info.68",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_74_SCC_info_69(*rel_74_SCC_info_69,symTable,"SCC.@info.69",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_75_SCC_info_7(*rel_75_SCC_info_7,symTable,"SCC.@info.7",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_76_SCC_info_70(*rel_76_SCC_info_70,symTable,"SCC.@info.70",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_77_SCC_info_8(*rel_77_SCC_info_8,symTable,"SCC.@info.8",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_78_SCC_info_9(*rel_78_SCC_info_9,symTable,"SCC.@info.9",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_79_invent_Path_info_1(*rel_79_invent_Path_info_1,symTable,"invent_Path.@info.1",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_80_invent_Path_info_10(*rel_80_invent_Path_info_10,symTable,"invent_Path.@info.10",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_81_invent_Path_info_11(*rel_81_invent_Path_info_11,symTable,"invent_Path.@info.11",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_82_invent_Path_info_12(*rel_82_invent_Path_info_12,symTable,"invent_Path.@info.12",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_83_invent_Path_info_13(*rel_83_invent_Path_info_13,symTable,"invent_Path.@info.13",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_84_invent_Path_info_14(*rel_84_invent_Path_info_14,symTable,"invent_Path.@info.14",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_85_invent_Path_info_15(*rel_85_invent_Path_info_15,symTable,"invent_Path.@info.15",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_86_invent_Path_info_16(*rel_86_invent_Path_info_16,symTable,"invent_Path.@info.16",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_87_invent_Path_info_17(*rel_87_invent_Path_info_17,symTable,"invent_Path.@info.17",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_88_invent_Path_info_18(*rel_88_invent_Path_info_18,symTable,"invent_Path.@info.18",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_89_invent_Path_info_19(*rel_89_invent_Path_info_19,symTable,"invent_Path.@info.19",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_90_invent_Path_info_2(*rel_90_invent_Path_info_2,symTable,"invent_Path.@info.2",std::array<const char *,5>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,5>{{"clause_num","head_vars","rel_0","rel_1","clause_repr"}}),

wrapper_rel_91_invent_Path_info_20(*rel_91_invent_Path_info_20,symTable,"invent_Path.@info.20",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_92_invent_Path_info_21(*rel_92_invent_Path_info_21,symTable,"invent_Path.@info.21",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_93_invent_Path_info_22(*rel_93_invent_Path_info_22,symTable,"invent_Path.@info.22",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_94_invent_Path_info_23(*rel_94_invent_Path_info_23,symTable,"invent_Path.@info.23",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_95_invent_Path_info_24(*rel_95_invent_Path_info_24,symTable,"invent_Path.@info.24",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_96_invent_Path_info_25(*rel_96_invent_Path_info_25,symTable,"invent_Path.@info.25",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_97_invent_Path_info_26(*rel_97_invent_Path_info_26,symTable,"invent_Path.@info.26",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_98_invent_Path_info_27(*rel_98_invent_Path_info_27,symTable,"invent_Path.@info.27",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_99_invent_Path_info_28(*rel_99_invent_Path_info_28,symTable,"invent_Path.@info.28",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_100_invent_Path_info_29(*rel_100_invent_Path_info_29,symTable,"invent_Path.@info.29",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_101_invent_Path_info_3(*rel_101_invent_Path_info_3,symTable,"invent_Path.@info.3",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_102_invent_Path_info_30(*rel_102_invent_Path_info_30,symTable,"invent_Path.@info.30",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_103_invent_Path_info_4(*rel_103_invent_Path_info_4,symTable,"invent_Path.@info.4",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_104_invent_Path_info_5(*rel_104_invent_Path_info_5,symTable,"invent_Path.@info.5",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_105_invent_Path_info_6(*rel_105_invent_Path_info_6,symTable,"invent_Path.@info.6",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_106_invent_Path_info_7(*rel_106_invent_Path_info_7,symTable,"invent_Path.@info.7",std::array<const char *,6>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,6>{{"clause_num","head_vars","rel_0","rel_1","rel_2","clause_repr"}}),

wrapper_rel_107_invent_Path_info_8(*rel_107_invent_Path_info_8,symTable,"invent_Path.@info.8",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}),

wrapper_rel_108_invent_Path_info_9(*rel_108_invent_Path_info_9,symTable,"invent_Path.@info.9",std::array<const char *,7>{{"i:number","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol","s:symbol"}},std::array<const char *,7>{{"clause_num","head_vars","rel_0","rel_1","rel_2","rel_3","clause_repr"}}){
addRelation("Edge",&wrapper_rel_1_Edge,true,false);
addRelation("Rule",&wrapper_rel_2_Rule,true,false);
addRelation("invent_Path",&wrapper_rel_3_invent_Path,false,true);
addRelation("SCC",&wrapper_rel_6_SCC,false,true);
addRelation("SCC.@info.1",&wrapper_rel_9_SCC_info_1,false,false);
addRelation("SCC.@info.10",&wrapper_rel_10_SCC_info_10,false,false);
addRelation("SCC.@info.11",&wrapper_rel_11_SCC_info_11,false,false);
addRelation("SCC.@info.12",&wrapper_rel_12_SCC_info_12,false,false);
addRelation("SCC.@info.13",&wrapper_rel_13_SCC_info_13,false,false);
addRelation("SCC.@info.14",&wrapper_rel_14_SCC_info_14,false,false);
addRelation("SCC.@info.15",&wrapper_rel_15_SCC_info_15,false,false);
addRelation("SCC.@info.16",&wrapper_rel_16_SCC_info_16,false,false);
addRelation("SCC.@info.17",&wrapper_rel_17_SCC_info_17,false,false);
addRelation("SCC.@info.18",&wrapper_rel_18_SCC_info_18,false,false);
addRelation("SCC.@info.19",&wrapper_rel_19_SCC_info_19,false,false);
addRelation("SCC.@info.2",&wrapper_rel_20_SCC_info_2,false,false);
addRelation("SCC.@info.20",&wrapper_rel_21_SCC_info_20,false,false);
addRelation("SCC.@info.21",&wrapper_rel_22_SCC_info_21,false,false);
addRelation("SCC.@info.22",&wrapper_rel_23_SCC_info_22,false,false);
addRelation("SCC.@info.23",&wrapper_rel_24_SCC_info_23,false,false);
addRelation("SCC.@info.24",&wrapper_rel_25_SCC_info_24,false,false);
addRelation("SCC.@info.25",&wrapper_rel_26_SCC_info_25,false,false);
addRelation("SCC.@info.26",&wrapper_rel_27_SCC_info_26,false,false);
addRelation("SCC.@info.27",&wrapper_rel_28_SCC_info_27,false,false);
addRelation("SCC.@info.28",&wrapper_rel_29_SCC_info_28,false,false);
addRelation("SCC.@info.29",&wrapper_rel_30_SCC_info_29,false,false);
addRelation("SCC.@info.3",&wrapper_rel_31_SCC_info_3,false,false);
addRelation("SCC.@info.30",&wrapper_rel_32_SCC_info_30,false,false);
addRelation("SCC.@info.31",&wrapper_rel_33_SCC_info_31,false,false);
addRelation("SCC.@info.32",&wrapper_rel_34_SCC_info_32,false,false);
addRelation("SCC.@info.33",&wrapper_rel_35_SCC_info_33,false,false);
addRelation("SCC.@info.34",&wrapper_rel_36_SCC_info_34,false,false);
addRelation("SCC.@info.35",&wrapper_rel_37_SCC_info_35,false,false);
addRelation("SCC.@info.36",&wrapper_rel_38_SCC_info_36,false,false);
addRelation("SCC.@info.37",&wrapper_rel_39_SCC_info_37,false,false);
addRelation("SCC.@info.38",&wrapper_rel_40_SCC_info_38,false,false);
addRelation("SCC.@info.39",&wrapper_rel_41_SCC_info_39,false,false);
addRelation("SCC.@info.4",&wrapper_rel_42_SCC_info_4,false,false);
addRelation("SCC.@info.40",&wrapper_rel_43_SCC_info_40,false,false);
addRelation("SCC.@info.41",&wrapper_rel_44_SCC_info_41,false,false);
addRelation("SCC.@info.42",&wrapper_rel_45_SCC_info_42,false,false);
addRelation("SCC.@info.43",&wrapper_rel_46_SCC_info_43,false,false);
addRelation("SCC.@info.44",&wrapper_rel_47_SCC_info_44,false,false);
addRelation("SCC.@info.45",&wrapper_rel_48_SCC_info_45,false,false);
addRelation("SCC.@info.46",&wrapper_rel_49_SCC_info_46,false,false);
addRelation("SCC.@info.47",&wrapper_rel_50_SCC_info_47,false,false);
addRelation("SCC.@info.48",&wrapper_rel_51_SCC_info_48,false,false);
addRelation("SCC.@info.49",&wrapper_rel_52_SCC_info_49,false,false);
addRelation("SCC.@info.5",&wrapper_rel_53_SCC_info_5,false,false);
addRelation("SCC.@info.50",&wrapper_rel_54_SCC_info_50,false,false);
addRelation("SCC.@info.51",&wrapper_rel_55_SCC_info_51,false,false);
addRelation("SCC.@info.52",&wrapper_rel_56_SCC_info_52,false,false);
addRelation("SCC.@info.53",&wrapper_rel_57_SCC_info_53,false,false);
addRelation("SCC.@info.54",&wrapper_rel_58_SCC_info_54,false,false);
addRelation("SCC.@info.55",&wrapper_rel_59_SCC_info_55,false,false);
addRelation("SCC.@info.56",&wrapper_rel_60_SCC_info_56,false,false);
addRelation("SCC.@info.57",&wrapper_rel_61_SCC_info_57,false,false);
addRelation("SCC.@info.58",&wrapper_rel_62_SCC_info_58,false,false);
addRelation("SCC.@info.59",&wrapper_rel_63_SCC_info_59,false,false);
addRelation("SCC.@info.6",&wrapper_rel_64_SCC_info_6,false,false);
addRelation("SCC.@info.60",&wrapper_rel_65_SCC_info_60,false,false);
addRelation("SCC.@info.61",&wrapper_rel_66_SCC_info_61,false,false);
addRelation("SCC.@info.62",&wrapper_rel_67_SCC_info_62,false,false);
addRelation("SCC.@info.63",&wrapper_rel_68_SCC_info_63,false,false);
addRelation("SCC.@info.64",&wrapper_rel_69_SCC_info_64,false,false);
addRelation("SCC.@info.65",&wrapper_rel_70_SCC_info_65,false,false);
addRelation("SCC.@info.66",&wrapper_rel_71_SCC_info_66,false,false);
addRelation("SCC.@info.67",&wrapper_rel_72_SCC_info_67,false,false);
addRelation("SCC.@info.68",&wrapper_rel_73_SCC_info_68,false,false);
addRelation("SCC.@info.69",&wrapper_rel_74_SCC_info_69,false,false);
addRelation("SCC.@info.7",&wrapper_rel_75_SCC_info_7,false,false);
addRelation("SCC.@info.70",&wrapper_rel_76_SCC_info_70,false,false);
addRelation("SCC.@info.8",&wrapper_rel_77_SCC_info_8,false,false);
addRelation("SCC.@info.9",&wrapper_rel_78_SCC_info_9,false,false);
addRelation("invent_Path.@info.1",&wrapper_rel_79_invent_Path_info_1,false,false);
addRelation("invent_Path.@info.10",&wrapper_rel_80_invent_Path_info_10,false,false);
addRelation("invent_Path.@info.11",&wrapper_rel_81_invent_Path_info_11,false,false);
addRelation("invent_Path.@info.12",&wrapper_rel_82_invent_Path_info_12,false,false);
addRelation("invent_Path.@info.13",&wrapper_rel_83_invent_Path_info_13,false,false);
addRelation("invent_Path.@info.14",&wrapper_rel_84_invent_Path_info_14,false,false);
addRelation("invent_Path.@info.15",&wrapper_rel_85_invent_Path_info_15,false,false);
addRelation("invent_Path.@info.16",&wrapper_rel_86_invent_Path_info_16,false,false);
addRelation("invent_Path.@info.17",&wrapper_rel_87_invent_Path_info_17,false,false);
addRelation("invent_Path.@info.18",&wrapper_rel_88_invent_Path_info_18,false,false);
addRelation("invent_Path.@info.19",&wrapper_rel_89_invent_Path_info_19,false,false);
addRelation("invent_Path.@info.2",&wrapper_rel_90_invent_Path_info_2,false,false);
addRelation("invent_Path.@info.20",&wrapper_rel_91_invent_Path_info_20,false,false);
addRelation("invent_Path.@info.21",&wrapper_rel_92_invent_Path_info_21,false,false);
addRelation("invent_Path.@info.22",&wrapper_rel_93_invent_Path_info_22,false,false);
addRelation("invent_Path.@info.23",&wrapper_rel_94_invent_Path_info_23,false,false);
addRelation("invent_Path.@info.24",&wrapper_rel_95_invent_Path_info_24,false,false);
addRelation("invent_Path.@info.25",&wrapper_rel_96_invent_Path_info_25,false,false);
addRelation("invent_Path.@info.26",&wrapper_rel_97_invent_Path_info_26,false,false);
addRelation("invent_Path.@info.27",&wrapper_rel_98_invent_Path_info_27,false,false);
addRelation("invent_Path.@info.28",&wrapper_rel_99_invent_Path_info_28,false,false);
addRelation("invent_Path.@info.29",&wrapper_rel_100_invent_Path_info_29,false,false);
addRelation("invent_Path.@info.3",&wrapper_rel_101_invent_Path_info_3,false,false);
addRelation("invent_Path.@info.30",&wrapper_rel_102_invent_Path_info_30,false,false);
addRelation("invent_Path.@info.4",&wrapper_rel_103_invent_Path_info_4,false,false);
addRelation("invent_Path.@info.5",&wrapper_rel_104_invent_Path_info_5,false,false);
addRelation("invent_Path.@info.6",&wrapper_rel_105_invent_Path_info_6,false,false);
addRelation("invent_Path.@info.7",&wrapper_rel_106_invent_Path_info_7,false,false);
addRelation("invent_Path.@info.8",&wrapper_rel_107_invent_Path_info_8,false,false);
addRelation("invent_Path.@info.9",&wrapper_rel_108_invent_Path_info_9,false,false);
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
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./Edge.facts"},{"name","Edge"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_1_Edge);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 0 */
/* BEGIN STRATUM 1 */
[&]() {
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./Rule.facts"},{"name","Rule"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({0,0,0}), symTable, ioDirectives, true)->readAll(*rel_2_Rule);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
}();
/* END STRATUM 1 */
/* BEGIN STRATUM 2 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,2,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(0,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [24:1-24:46])_");
if(((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(0),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(2)),static_cast<RamDomain>((std::max({env0[2], env1[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,4,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(77,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v0,v1,_,@level_num_2),
   Edge(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [44:1-44:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(77),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(4)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,5,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(99,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2),
   Edge(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [47:1-47:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(99),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(5)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,7,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(174,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [52:1-52:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(174),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(7)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,9,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(123,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2),
   Edge(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [54:1-54:76])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(123),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(9)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,10,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(188,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [56:1-56:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(188),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(10)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,12,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(142,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   Edge(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [61:1-61:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(142),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(12)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,13,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(69,_,@level_num_0),
   Edge(v1,v0,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2),
   Edge(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [64:1-64:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(69),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(13)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,16,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(48,_,@level_num_0),
   Edge(v0,_,_,@level_num_1),
   Edge(v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [75:1-75:75])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(48),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(16)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,18,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(73,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v1,v0,_,@level_num_2),
   Edge(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [77:1-77:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(73),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(18)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,20,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(187,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [88:1-88:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(187),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(20)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,21,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(106,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v0,v1,_,@level_num_2),
   Edge(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [91:1-91:76])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(106),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(21)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,22,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(178,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   Edge(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [92:1-92:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(178),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(22)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,23,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(184,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [96:1-96:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(184),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(23)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,27,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(176,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [107:1-107:76])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(176),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(27)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,28,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(53,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2),
   Edge(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [111:1-111:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(53),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(28)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_3_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
}
}
}
}
}
}
rel_4_delta_invent_Path->insertAll(*rel_3_invent_Path);
iter = 0;
for(;;) {
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,1,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(238,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [18:1-18:83])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(238),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(1)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,3,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(456,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   invent_Path(v1,v2,_,@level_num_2),
   invent_Path(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [40:1-40:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(456),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(3)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,3,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(456,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   invent_Path(v1,v2,_,@level_num_2),
   invent_Path(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [40:1-40:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(456),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_4_delta_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(3)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,6,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(202,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   Edge(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [51:1-51:83])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(202),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(6)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,8,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(525,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [53:1-53:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(525),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_delta_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[0],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(8)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,8,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(525,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [53:1-53:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(525),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[0],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(8)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,8,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(525,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [53:1-53:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(525),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(8)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,11,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(607,_,@level_num_0),
   invent_Path(v1,_,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [59:1-59:97])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(607),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_delta_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(11)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,11,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(607,_,@level_num_0),
   invent_Path(v1,_,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [59:1-59:97])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(607),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(11)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,14,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(483,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [70:1-70:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(483),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(14)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,14,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(483,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [70:1-70:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(483),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(14)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,15,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(592,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [73:1-73:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(592),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_delta_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(15)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,15,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(592,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [73:1-73:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(592),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_4_delta_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(15)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,15,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(592,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [73:1-73:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(592),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(15)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,17,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(214,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [76:1-76:83])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(214),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_4_delta_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(17)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,19,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(23,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [80:1-80:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(23),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_4_delta_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(19)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,24,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(603,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [99:1-99:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(603),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_delta_invent_Path) {
if( !(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(24)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,24,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(603,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [99:1-99:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(603),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(24)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,24,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(603,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [99:1-99:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(603),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(24)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,25,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(207,_,@level_num_0),
   Edge(v1,v0,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [101:1-101:83])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(207),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(25)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,26,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(297,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v1,v2,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [104:1-104:83])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(297),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(26)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,29,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(512,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [113:1-113:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(512),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_4_delta_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) && (!(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(29)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,29,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(512,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [113:1-113:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(512),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_4_delta_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_4_delta_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(29)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,29,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(512,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [113:1-113:97])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(512),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(29)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(invent_Path(v0,v1,30,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(210,_,@level_num_0),
   Edge(v0,_,_,@level_num_1),
   invent_Path(v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [114:1-114:83])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_4_delta_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt,rel_4_delta_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt,rel_5_new_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(210),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_4_delta_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_4_delta_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(30)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_5_new_invent_Path->insert(tuple,READ_OP_CONTEXT(rel_5_new_invent_Path_op_ctxt));
}
}
}
}
}
}
if(rel_5_new_invent_Path->empty()) break;
rel_3_invent_Path->insertAll(*rel_5_new_invent_Path);
std::swap(rel_4_delta_invent_Path, rel_5_new_invent_Path);
rel_5_new_invent_Path->purge();
iter++;
}
iter = 0;
if (!isHintsProfilingEnabled()) rel_4_delta_invent_Path->purge();
if (!isHintsProfilingEnabled()) rel_5_new_invent_Path->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1"},{"filename","./invent_Path.csv"},{"name","invent_Path"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_3_invent_Path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}();
/* END STRATUM 2 */
/* BEGIN STRATUM 3 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,4,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1714,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [21:1-21:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1714),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(4)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,6,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1741,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [23:1-23:90])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1741),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(6)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,9,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(692,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   invent_Path(v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [27:1-27:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(692),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(9)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,14,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(773,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   Edge(v1,v2,_,@level_num_2),
   Edge(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [32:1-32:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(773),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(14)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,15,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(874,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [33:1-33:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(874),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(15)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,16,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(859,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   Edge(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [34:1-34:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(859),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(16)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,17,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(878,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   invent_Path(v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [35:1-35:75])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(878),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(17)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,21,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1689,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v1,v2,_,@level_num_2),
   invent_Path(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [39:1-39:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1689),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(21)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,32,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1717,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [58:1-58:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1717),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(32)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,36,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(885,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [65:1-65:75])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(885),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(36)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,39,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1658,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [68:1-68:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1658),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(39)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,43,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1204,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [74:1-74:83])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1204),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(43)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,46,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(740,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   Edge(_,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [81:1-81:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(740),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(46)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,49,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1712,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [84:1-84:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1712),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[0],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(49)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,50,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(699,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [85:1-85:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(699),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(50)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,51,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(823,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [86:1-86:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(823),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(51)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,53,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(994,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   Edge(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [89:1-89:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(994),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(53)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,56,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(854,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   Edge(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [94:1-94:68])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(854),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(56)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,59,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(985,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [98:1-98:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(985),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(59)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,60,(max(@level_num_0,@level_num_1)+1)) :- 
   Rule(733,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [100:1-100:68])_");
if(((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(733),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(60)),static_cast<RamDomain>((std::max({env0[2], env1[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,62,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1783,_,@level_num_0),
   invent_Path(v2,v1,_,@level_num_1),
   invent_Path(v1,v2,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [103:1-103:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1783),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(62)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,65,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(914,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2),
   invent_Path(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [108:1-108:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(914),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(65)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,66,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1771,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [109:1-109:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1771),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(66)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,67,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1734,_,@level_num_0),
   invent_Path(v1,v2,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [110:1-110:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1734),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(67)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,68,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1695,_,@level_num_0),
   invent_Path(v2,v1,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   invent_Path(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [112:1-112:90])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1695),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(68)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_6_SCC->insert(tuple,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
}
}
}
}
}
}
rel_7_delta_SCC->insertAll(*rel_6_SCC);
iter = 0;
for(;;) {
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,1,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1125,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   Edge(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [17:1-17:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1125),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(1)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,2,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1797,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   SCC(v0,v1,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [19:1-19:82])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1797),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(2)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,3,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1948,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   SCC(v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [20:1-20:74])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1948),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(3)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,5,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1992,_,@level_num_0),
   invent_Path(v2,v1,_,@level_num_1),
   SCC(v1,v0,_,@level_num_2),
   SCC(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [22:1-22:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1992),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(5)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,5,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1992,_,@level_num_0),
   invent_Path(v2,v1,_,@level_num_1),
   SCC(v1,v0,_,@level_num_2),
   SCC(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [22:1-22:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1992),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(5)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,7,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1933,_,@level_num_0),
   invent_Path(v2,v1,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   invent_Path(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [25:1-25:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1933),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(7)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,8,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1791,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [26:1-26:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1791),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(8)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,10,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1596,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   SCC(v1,v2,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [28:1-28:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1596),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(10)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,10,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1596,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   SCC(v1,v2,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [28:1-28:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1596),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(10)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,11,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1163,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   SCC(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [29:1-29:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1163),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(11)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,12,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2177,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [30:1-30:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2177),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_7_delta_SCC) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(12)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,12,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2177,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [30:1-30:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2177),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(12)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,12,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2177,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [30:1-30:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2177),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(12)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,13,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2001,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   SCC(v0,v2,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [31:1-31:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2001),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(13)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,13,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2001,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   SCC(v0,v2,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [31:1-31:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2001),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(13)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,18,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1600,_,@level_num_0),
   Edge(v1,v0,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [36:1-36:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1600),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(18)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,18,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1600,_,@level_num_0),
   Edge(v1,v0,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [36:1-36:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1600),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(18)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,19,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1425,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [37:1-37:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1425),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(19)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,20,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1905,_,@level_num_0),
   invent_Path(v1,_,_,@level_num_1),
   SCC(v1,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [38:1-38:82])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1905),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(20)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,22,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1866,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [41:1-41:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1866),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(22)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,23,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1335,_,@level_num_0),
   Edge(v1,v0,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [42:1-42:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1335),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(23)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,24,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1436,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [43:1-43:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1436),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(24)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,25,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1065,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [45:1-45:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1065),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(25)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,26,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1166,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [46:1-46:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1166),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(26)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,27,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1360,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   invent_Path(v2,v0,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [48:1-48:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1360),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(27)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,28,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1972,_,@level_num_0),
   invent_Path(v1,v0,_,@level_num_1),
   SCC(_,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [49:1-49:74])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1972),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(28)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,29,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1930,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [50:1-50:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1930),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(29)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,30,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(1893,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   SCC(v1,v2,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [55:1-55:82])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1893),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(30)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,31,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1058,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   Edge(v0,v2,_,@level_num_2),
   SCC(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [57:1-57:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1058),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(31)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,33,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1159,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [60:1-60:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1159),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(33)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,34,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1599,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [62:1-62:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1599),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(34)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,34,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1599,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [62:1-62:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1599),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(34)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,35,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2139,_,@level_num_0),
   SCC(v2,v0,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [63:1-63:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2139),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_7_delta_SCC) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(35)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,35,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2139,_,@level_num_0),
   SCC(v2,v0,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [63:1-63:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2139),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(35)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,35,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2139,_,@level_num_0),
   SCC(v2,v0,_,@level_num_1),
   SCC(v2,v1,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [63:1-63:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2139),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(35)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,37,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1848,_,@level_num_0),
   invent_Path(v2,v1,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2),
   SCC(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [66:1-66:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1848),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(37)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,38,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1162,_,@level_num_0),
   Edge(v2,v1,_,@level_num_1),
   Edge(v1,v2,_,@level_num_2),
   SCC(v0,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [67:1-67:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1162),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(38)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,40,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1813,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v0,v2,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [69:1-69:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1813),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[0]),static_cast<RamDomain>(RamDomain(40)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,41,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1071,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v0,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [71:1-71:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1071),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(41)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,42,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1842,_,@level_num_0),
   invent_Path(v2,v0,_,@level_num_1),
   invent_Path(v2,v1,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [72:1-72:82])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1842),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(42)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,44,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1096,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v0,v1,_,@level_num_2),
   SCC(v2,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [78:1-78:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1096),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(44)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,45,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2184,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [79:1-79:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2184),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_7_delta_SCC) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(45)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,45,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2184,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [79:1-79:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2184),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(45)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,45,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2184,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [79:1-79:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2184),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(45)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,47,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1571,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   SCC(v0,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [82:1-82:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1571),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(47)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,47,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1571,_,@level_num_0),
   Edge(v0,v2,_,@level_num_1),
   SCC(v0,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [82:1-82:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1571),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(47)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,48,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1587,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [83:1-83:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1587),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(48)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,48,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1587,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [83:1-83:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1587),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(48)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,52,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1338,_,@level_num_0),
   Edge(v0,v1,_,@level_num_1),
   invent_Path(v1,v0,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [87:1-87:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1338),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(52)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,54,(max(max(@level_num_0,@level_num_1),@level_num_2)+1)) :- 
   Rule(684,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [90:1-90:53])_");
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(684),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(54)),static_cast<RamDomain>((std::max({std::max({env0[2], env1[3], }), env2[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,55,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2015,_,@level_num_0),
   invent_Path(v0,v2,_,@level_num_1),
   SCC(v0,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [93:1-93:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2015),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(55)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,55,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2015,_,@level_num_0),
   invent_Path(v0,v2,_,@level_num_1),
   SCC(v0,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [93:1-93:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2015),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(55)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,57,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1336,_,@level_num_0),
   Edge(v1,v0,_,@level_num_1),
   invent_Path(v0,v1,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [95:1-95:75])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1336),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(57)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,58,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1143,_,@level_num_0),
   Edge(v1,v2,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   SCC(v1,v0,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [97:1-97:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1143),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env3[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(RamDomain(58)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,61,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1075,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   Edge(v2,v1,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [102:1-102:68])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1075),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(61)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,63,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1540,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   SCC(v0,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [105:1-105:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1540),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(63)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,63,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1540,_,@level_num_0),
   Edge(v2,v0,_,@level_num_1),
   SCC(v0,v1,_,@level_num_2),
   SCC(v1,v2,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [105:1-105:67])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1540),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_1_Edge) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(env2[1]),static_cast<RamDomain>(RamDomain(63)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,64,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1951,_,@level_num_0),
   invent_Path(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [106:1-106:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1951),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((!([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(64)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,64,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(1951,_,@level_num_0),
   invent_Path(v0,v2,_,@level_num_1),
   SCC(v2,v0,_,@level_num_2),
   SCC(v0,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [106:1-106:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1951),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env3[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env3[1]),static_cast<RamDomain>(RamDomain(64)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,69,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2019,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   SCC(v0,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [115:1-115:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2019),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_7_delta_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[1],env1[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(69)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,69,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2019,_,@level_num_0),
   invent_Path(v0,v1,_,@level_num_1),
   SCC(v0,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [115:1-115:74])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2019),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_3_invent_Path) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env1[1]),static_cast<RamDomain>(RamDomain(69)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,70,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2243,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v1,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [116:1-116:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2243),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_7_delta_SCC) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) && (!(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env2[0],env1[1],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(70)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,70,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2243,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v1,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [116:1-116:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2243),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_7_delta_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env2 : range) {
if( !(!rel_7_delta_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[1],env2[0],0,0}}),READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt)).empty())) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(70)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
}
SignalHandler::instance()->setMsg(R"_(SCC(v0,v1,70,(max(max(max(@level_num_0,@level_num_1),@level_num_2),@level_num_3)+1)) :- 
   Rule(2243,_,@level_num_0),
   SCC(v0,v2,_,@level_num_1),
   SCC(v1,v2,_,@level_num_2),
   SCC(v2,v1,_,@level_num_3).
in file /Users/jonathan/Desktop/Research/POPL20/artifact/scale_benchmarks/scc_100/rules.small.dl [116:1-116:66])_");
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_7_delta_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_8_new_SCC_op_ctxt,rel_8_new_SCC->createContext());
CREATE_OP_CONTEXT(rel_7_delta_SCC_op_ctxt,rel_7_delta_SCC->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2243),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
for(const auto& env1 : *rel_6_SCC) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_7_delta_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_7_delta_SCC_op_ctxt));
for(const auto& env3 : range) {
if( !([&]() -> bool {
auto existenceCheck = rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{env1[0],env2[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
if (existenceCheck.empty()) return false; else return (*existenceCheck.begin())[3] <= (std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1));}()
)) {
Tuple<RamDomain,4> tuple({{static_cast<RamDomain>(env1[0]),static_cast<RamDomain>(env2[0]),static_cast<RamDomain>(RamDomain(70)),static_cast<RamDomain>((std::max({std::max({std::max({env0[2], env1[3], }), env2[3], }), env3[3], })) + (RamDomain(1)))}});
rel_8_new_SCC->insert(tuple,READ_OP_CONTEXT(rel_8_new_SCC_op_ctxt));
}
}
}
}
}
}
}
if(rel_8_new_SCC->empty()) break;
rel_6_SCC->insertAll(*rel_8_new_SCC);
std::swap(rel_7_delta_SCC, rel_8_new_SCC);
rel_8_new_SCC->purge();
iter++;
}
iter = 0;
if (!isHintsProfilingEnabled()) rel_7_delta_SCC->purge();
if (!isHintsProfilingEnabled()) rel_8_new_SCC->purge();
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1"},{"filename","./SCC.csv"},{"name","SCC"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_6_SCC);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}();
/* END STRATUM 3 */
/* BEGIN STRATUM 4 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.1(1,"v0,v1","Rule","Edge,v2,v0","SCC,v2,v0","Edge,v2,v1","SCC(v0,v1) :- 
   Rule(1125),
   Edge(v2,v0),
   SCC(v2,v0),
   Edge(v2,v1).").
in file  [0:0-0:0])_");
rel_9_SCC_info_1->insert(RamDomain(1),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(3),RamDomain(4),RamDomain(5));
}();
/* END STRATUM 4 */
/* BEGIN STRATUM 5 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.10(10,"v0,v1","Rule","Edge,v1,v2","SCC,v1,v2","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1596),
   Edge(v1,v2),
   SCC(v1,v2),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_10_SCC_info_10->insert(RamDomain(10),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(24),RamDomain(7),RamDomain(25));
}();
/* END STRATUM 5 */
/* BEGIN STRATUM 6 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.11(11,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v1","SCC,v2,v0","SCC(v0,v1) :- 
   Rule(1163),
   Edge(v1,v2),
   Edge(v2,v1),
   SCC(v2,v0).").
in file  [0:0-0:0])_");
rel_11_SCC_info_11->insert(RamDomain(11),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(4),RamDomain(3),RamDomain(26));
}();
/* END STRATUM 6 */
/* BEGIN STRATUM 7 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.12(12,"v0,v1","Rule","SCC,v0,v2","SCC,v2,v0","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(2177),
   SCC(v0,v2),
   SCC(v2,v0),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_12_SCC_info_12->insert(RamDomain(12),RamDomain(0),RamDomain(1),RamDomain(16),RamDomain(3),RamDomain(24),RamDomain(27));
}();
/* END STRATUM 7 */
/* BEGIN STRATUM 8 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.13(13,"v0,v1","Rule","invent_Path,v0,v1","SCC,v0,v2","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(2001),
   invent_Path(v0,v1),
   SCC(v0,v2),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_13_SCC_info_13->insert(RamDomain(13),RamDomain(0),RamDomain(1),RamDomain(6),RamDomain(16),RamDomain(24),RamDomain(28));
}();
/* END STRATUM 8 */
/* BEGIN STRATUM 9 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.14(14,"v0,v1","Rule","Edge,v0,v1","Edge,v1,v2","Edge,v0,v2","SCC(v0,v1) :- 
   Rule(773),
   Edge(v0,v1),
   Edge(v1,v2),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_14_SCC_info_14->insert(RamDomain(14),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(23),RamDomain(30),RamDomain(31));
}();
/* END STRATUM 9 */
/* BEGIN STRATUM 10 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.15(15,"v0,v1","Rule","Edge,v2,v1","Edge,v0,v2","SCC(v0,v1) :- 
   Rule(874),
   Edge(v2,v1),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_15_SCC_info_15->insert(RamDomain(15),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(30),RamDomain(32));
}();
/* END STRATUM 10 */
/* BEGIN STRATUM 11 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.16(16,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v1","Edge,v2,v0","SCC(v0,v1) :- 
   Rule(859),
   Edge(v1,v2),
   Edge(v2,v1),
   Edge(v2,v0).").
in file  [0:0-0:0])_");
rel_16_SCC_info_16->insert(RamDomain(16),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(4),RamDomain(2),RamDomain(33));
}();
/* END STRATUM 11 */
/* BEGIN STRATUM 12 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.17(17,"v0,v1","Rule","Edge,v0,v1","invent_Path,v1,v0","SCC(v0,v1) :- 
   Rule(878),
   Edge(v0,v1),
   invent_Path(v1,v0).").
in file  [0:0-0:0])_");
rel_17_SCC_info_17->insert(RamDomain(17),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(9),RamDomain(34));
}();
/* END STRATUM 12 */
/* BEGIN STRATUM 13 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.18(18,"v0,v1","Rule","Edge,v1,v0","SCC,v2,v1","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1600),
   Edge(v1,v0),
   SCC(v2,v1),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_18_SCC_info_18->insert(RamDomain(18),RamDomain(0),RamDomain(1),RamDomain(35),RamDomain(19),RamDomain(24),RamDomain(36));
}();
/* END STRATUM 13 */
/* BEGIN STRATUM 14 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.19(19,"v0,v1","Rule","Edge,v0,v2","invent_Path,v2,v0","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1425),
   Edge(v0,v2),
   invent_Path(v2,v0),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_19_SCC_info_19->insert(RamDomain(19),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(12),RamDomain(24),RamDomain(37));
}();
/* END STRATUM 14 */
/* BEGIN STRATUM 15 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.2(2,"v0,v1","Rule","invent_Path,v0,v1","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1797),
   invent_Path(v0,v1),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_20_SCC_info_2->insert(RamDomain(2),RamDomain(0),RamDomain(1),RamDomain(6),RamDomain(7),RamDomain(8));
}();
/* END STRATUM 15 */
/* BEGIN STRATUM 16 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.20(20,"v0,v1","Rule","invent_Path,v1","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1905),
   invent_Path(v1,_),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_21_SCC_info_20->insert(RamDomain(20),RamDomain(0),RamDomain(1),RamDomain(38),RamDomain(10),RamDomain(39));
}();
/* END STRATUM 16 */
/* BEGIN STRATUM 17 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.21(21,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v1,v2","invent_Path,v1,v0","SCC(v0,v1) :- 
   Rule(1689),
   invent_Path(v2,v0),
   invent_Path(v1,v2),
   invent_Path(v1,v0).").
in file  [0:0-0:0])_");
rel_22_SCC_info_21->insert(RamDomain(21),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(13),RamDomain(9),RamDomain(40));
}();
/* END STRATUM 17 */
/* BEGIN STRATUM 18 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.22(22,"v0,v1","Rule","invent_Path,v0,v1","invent_Path,v2,v0","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1866),
   invent_Path(v0,v1),
   invent_Path(v2,v0),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_23_SCC_info_22->insert(RamDomain(22),RamDomain(0),RamDomain(1),RamDomain(6),RamDomain(12),RamDomain(24),RamDomain(41));
}();
/* END STRATUM 18 */
/* BEGIN STRATUM 19 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.23(23,"v0,v1","Rule","Edge,v1,v0","invent_Path,v0,v1","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1335),
   Edge(v1,v0),
   invent_Path(v0,v1),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_24_SCC_info_23->insert(RamDomain(23),RamDomain(0),RamDomain(1),RamDomain(35),RamDomain(6),RamDomain(7),RamDomain(42));
}();
/* END STRATUM 19 */
/* BEGIN STRATUM 20 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.24(24,"v0,v1","Rule","Edge,v0,v2","invent_Path,v0,v2","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1436),
   Edge(v0,v2),
   invent_Path(v0,v2),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_25_SCC_info_24->insert(RamDomain(24),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(43),RamDomain(24),RamDomain(44));
}();
/* END STRATUM 20 */
/* BEGIN STRATUM 21 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.25(25,"v0,v1","Rule","Edge,v2,v1","Edge,v0,v2","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1065),
   Edge(v2,v1),
   Edge(v0,v2),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_26_SCC_info_25->insert(RamDomain(25),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(30),RamDomain(10),RamDomain(45));
}();
/* END STRATUM 21 */
/* BEGIN STRATUM 22 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.26(26,"v0,v1","Rule","Edge,v2,v0","Edge,v2,v1","SCC,v2,v1","SCC(v0,v1) :- 
   Rule(1166),
   Edge(v2,v0),
   Edge(v2,v1),
   SCC(v2,v1).").
in file  [0:0-0:0])_");
rel_27_SCC_info_26->insert(RamDomain(26),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(4),RamDomain(19),RamDomain(46));
}();
/* END STRATUM 22 */
/* BEGIN STRATUM 23 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.27(27,"v0,v1","Rule","Edge,v0,v2","invent_Path,v2,v0","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1360),
   Edge(v0,v2),
   invent_Path(v2,v0),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_28_SCC_info_27->insert(RamDomain(27),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(12),RamDomain(7),RamDomain(47));
}();
/* END STRATUM 23 */
/* BEGIN STRATUM 24 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.28(28,"v0,v1","Rule","invent_Path,v1,v0","SCC,v0","SCC(v0,v1) :- 
   Rule(1972),
   invent_Path(v1,v0),
   SCC(_,v0).").
in file  [0:0-0:0])_");
rel_29_SCC_info_28->insert(RamDomain(28),RamDomain(0),RamDomain(1),RamDomain(9),RamDomain(48),RamDomain(49));
}();
/* END STRATUM 24 */
/* BEGIN STRATUM 25 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.29(29,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v2,v1","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1930),
   invent_Path(v2,v0),
   invent_Path(v2,v1),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_30_SCC_info_29->insert(RamDomain(29),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(15),RamDomain(24),RamDomain(50));
}();
/* END STRATUM 25 */
/* BEGIN STRATUM 26 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.3(3,"v0,v1","Rule","invent_Path,v1,v0","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1948),
   invent_Path(v1,v0),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_31_SCC_info_3->insert(RamDomain(3),RamDomain(0),RamDomain(1),RamDomain(9),RamDomain(10),RamDomain(11));
}();
/* END STRATUM 26 */
/* BEGIN STRATUM 27 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.30(30,"v0,v1","Rule","invent_Path,v2,v0","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1893),
   invent_Path(v2,v0),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_32_SCC_info_30->insert(RamDomain(30),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(24),RamDomain(51));
}();
/* END STRATUM 27 */
/* BEGIN STRATUM 28 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.31(31,"v0,v1","Rule","Edge,v0,v1","Edge,v0,v2","SCC,v2,v0","SCC(v0,v1) :- 
   Rule(1058),
   Edge(v0,v1),
   Edge(v0,v2),
   SCC(v2,v0).").
in file  [0:0-0:0])_");
rel_33_SCC_info_31->insert(RamDomain(31),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(30),RamDomain(3),RamDomain(52));
}();
/* END STRATUM 28 */
/* BEGIN STRATUM 29 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.32(32,"v0,v1","Rule","invent_Path,v1,v0","invent_Path,v2,v1","invent_Path,v2,v0","SCC(v0,v1) :- 
   Rule(1717),
   invent_Path(v1,v0),
   invent_Path(v2,v1),
   invent_Path(v2,v0).").
in file  [0:0-0:0])_");
rel_34_SCC_info_32->insert(RamDomain(32),RamDomain(0),RamDomain(1),RamDomain(9),RamDomain(15),RamDomain(12),RamDomain(53));
}();
/* END STRATUM 29 */
/* BEGIN STRATUM 30 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.33(33,"v0,v1","Rule","Edge,v0,v2","Edge,v2,v1","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1159),
   Edge(v0,v2),
   Edge(v2,v1),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_35_SCC_info_33->insert(RamDomain(33),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(4),RamDomain(24),RamDomain(54));
}();
/* END STRATUM 30 */
/* BEGIN STRATUM 31 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.34(34,"v0,v1","Rule","Edge,v1,v2","SCC,v2,v1","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1599),
   Edge(v1,v2),
   SCC(v2,v1),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_36_SCC_info_34->insert(RamDomain(34),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(19),RamDomain(10),RamDomain(55));
}();
/* END STRATUM 31 */
/* BEGIN STRATUM 32 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.35(35,"v0,v1","Rule","SCC,v2,v0","SCC,v2,v1","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(2139),
   SCC(v2,v0),
   SCC(v2,v1),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_37_SCC_info_35->insert(RamDomain(35),RamDomain(0),RamDomain(1),RamDomain(3),RamDomain(19),RamDomain(7),RamDomain(56));
}();
/* END STRATUM 32 */
/* BEGIN STRATUM 33 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.36(36,"v0,v1","Rule","Edge,v0,v1","invent_Path,v0,v1","SCC(v0,v1) :- 
   Rule(885),
   Edge(v0,v1),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_38_SCC_info_36->insert(RamDomain(36),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(6),RamDomain(57));
}();
/* END STRATUM 33 */
/* BEGIN STRATUM 34 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.37(37,"v0,v1","Rule","invent_Path,v2,v1","invent_Path,v0,v1","SCC,v2,v0","SCC(v0,v1) :- 
   Rule(1848),
   invent_Path(v2,v1),
   invent_Path(v0,v1),
   SCC(v2,v0).").
in file  [0:0-0:0])_");
rel_39_SCC_info_37->insert(RamDomain(37),RamDomain(0),RamDomain(1),RamDomain(15),RamDomain(6),RamDomain(3),RamDomain(58));
}();
/* END STRATUM 34 */
/* BEGIN STRATUM 35 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.38(38,"v0,v1","Rule","Edge,v2,v1","Edge,v1,v2","SCC,v0,v2","SCC(v0,v1) :- 
   Rule(1162),
   Edge(v2,v1),
   Edge(v1,v2),
   SCC(v0,v2).").
in file  [0:0-0:0])_");
rel_40_SCC_info_38->insert(RamDomain(38),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(23),RamDomain(16),RamDomain(59));
}();
/* END STRATUM 35 */
/* BEGIN STRATUM 36 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.39(39,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v0,v2","invent_Path,v0,v1","SCC(v0,v1) :- 
   Rule(1658),
   invent_Path(v2,v0),
   invent_Path(v0,v2),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_41_SCC_info_39->insert(RamDomain(39),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(43),RamDomain(6),RamDomain(60));
}();
/* END STRATUM 36 */
/* BEGIN STRATUM 37 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.4(4,"v0,v1","Rule","invent_Path,v0,v1","invent_Path,v2,v0","invent_Path,v1,v2","SCC(v0,v1) :- 
   Rule(1714),
   invent_Path(v0,v1),
   invent_Path(v2,v0),
   invent_Path(v1,v2).").
in file  [0:0-0:0])_");
rel_42_SCC_info_4->insert(RamDomain(4),RamDomain(0),RamDomain(1),RamDomain(6),RamDomain(12),RamDomain(13),RamDomain(14));
}();
/* END STRATUM 37 */
/* BEGIN STRATUM 38 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.40(40,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v0,v2","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1813),
   invent_Path(v2,v0),
   invent_Path(v0,v2),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_43_SCC_info_40->insert(RamDomain(40),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(43),RamDomain(10),RamDomain(61));
}();
/* END STRATUM 38 */
/* BEGIN STRATUM 39 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.41(41,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v0","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1071),
   Edge(v1,v2),
   Edge(v2,v0),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_44_SCC_info_41->insert(RamDomain(41),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(2),RamDomain(7),RamDomain(62));
}();
/* END STRATUM 39 */
/* BEGIN STRATUM 40 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.42(42,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v2,v1","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1842),
   invent_Path(v2,v0),
   invent_Path(v2,v1),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_45_SCC_info_42->insert(RamDomain(42),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(15),RamDomain(10),RamDomain(63));
}();
/* END STRATUM 40 */
/* BEGIN STRATUM 41 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.43(43,"v0,v1","Rule","Edge,v2,v0","invent_Path,v0,v2","invent_Path,v0,v1","SCC(v0,v1) :- 
   Rule(1204),
   Edge(v2,v0),
   invent_Path(v0,v2),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_46_SCC_info_43->insert(RamDomain(43),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(43),RamDomain(6),RamDomain(64));
}();
/* END STRATUM 41 */
/* BEGIN STRATUM 42 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.44(44,"v0,v1","Rule","Edge,v1,v2","Edge,v0,v1","SCC,v2,v0","SCC(v0,v1) :- 
   Rule(1096),
   Edge(v1,v2),
   Edge(v0,v1),
   SCC(v2,v0).").
in file  [0:0-0:0])_");
rel_47_SCC_info_44->insert(RamDomain(44),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(29),RamDomain(3),RamDomain(65));
}();
/* END STRATUM 42 */
/* BEGIN STRATUM 43 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.45(45,"v0,v1","Rule","SCC,v0,v2","SCC,v2,v0","SCC,v2,v1","SCC(v0,v1) :- 
   Rule(2184),
   SCC(v0,v2),
   SCC(v2,v0),
   SCC(v2,v1).").
in file  [0:0-0:0])_");
rel_48_SCC_info_45->insert(RamDomain(45),RamDomain(0),RamDomain(1),RamDomain(16),RamDomain(3),RamDomain(19),RamDomain(66));
}();
/* END STRATUM 43 */
/* BEGIN STRATUM 44 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.46(46,"v0,v1","Rule","Edge,v0,v1","Edge,v0","SCC(v0,v1) :- 
   Rule(740),
   Edge(v0,v1),
   Edge(_,v0).").
in file  [0:0-0:0])_");
rel_49_SCC_info_46->insert(RamDomain(46),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(67),RamDomain(68));
}();
/* END STRATUM 44 */
/* BEGIN STRATUM 45 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.47(47,"v0,v1","Rule","Edge,v0,v2","SCC,v0,v2","SCC,v2,v1","SCC(v0,v1) :- 
   Rule(1571),
   Edge(v0,v2),
   SCC(v0,v2),
   SCC(v2,v1).").
in file  [0:0-0:0])_");
rel_50_SCC_info_47->insert(RamDomain(47),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(16),RamDomain(19),RamDomain(69));
}();
/* END STRATUM 45 */
/* BEGIN STRATUM 46 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.48(48,"v0,v1","Rule","Edge,v2,v0","SCC,v2,v0","SCC,v2,v1","SCC(v0,v1) :- 
   Rule(1587),
   Edge(v2,v0),
   SCC(v2,v0),
   SCC(v2,v1).").
in file  [0:0-0:0])_");
rel_51_SCC_info_48->insert(RamDomain(48),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(3),RamDomain(19),RamDomain(70));
}();
/* END STRATUM 46 */
/* BEGIN STRATUM 47 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.49(49,"v0,v1","Rule","invent_Path,v1,v2","invent_Path,v0,v2","invent_Path,v0,v1","SCC(v0,v1) :- 
   Rule(1712),
   invent_Path(v1,v2),
   invent_Path(v0,v2),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_52_SCC_info_49->insert(RamDomain(49),RamDomain(0),RamDomain(1),RamDomain(13),RamDomain(43),RamDomain(6),RamDomain(71));
}();
/* END STRATUM 47 */
/* BEGIN STRATUM 48 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.5(5,"v0,v1","Rule","invent_Path,v2,v1","SCC,v1,v0","SCC,v0,v2","SCC(v0,v1) :- 
   Rule(1992),
   invent_Path(v2,v1),
   SCC(v1,v0),
   SCC(v0,v2).").
in file  [0:0-0:0])_");
rel_53_SCC_info_5->insert(RamDomain(5),RamDomain(0),RamDomain(1),RamDomain(15),RamDomain(10),RamDomain(16),RamDomain(17));
}();
/* END STRATUM 48 */
/* BEGIN STRATUM 49 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.50(50,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v2,v1","SCC(v0,v1) :- 
   Rule(699),
   invent_Path(v2,v0),
   invent_Path(v2,v1).").
in file  [0:0-0:0])_");
rel_54_SCC_info_50->insert(RamDomain(50),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(15),RamDomain(72));
}();
/* END STRATUM 49 */
/* BEGIN STRATUM 50 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.51(51,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v0","SCC(v0,v1) :- 
   Rule(823),
   Edge(v1,v2),
   Edge(v2,v0).").
in file  [0:0-0:0])_");
rel_55_SCC_info_51->insert(RamDomain(51),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(2),RamDomain(73));
}();
/* END STRATUM 50 */
/* BEGIN STRATUM 51 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.52(52,"v0,v1","Rule","Edge,v0,v1","invent_Path,v1,v0","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1338),
   Edge(v0,v1),
   invent_Path(v1,v0),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_56_SCC_info_52->insert(RamDomain(52),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(9),RamDomain(10),RamDomain(74));
}();
/* END STRATUM 51 */
/* BEGIN STRATUM 52 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.53(53,"v0,v1","Rule","Edge,v1,v2","invent_Path,v2,v1","Edge,v1,v0","SCC(v0,v1) :- 
   Rule(994),
   Edge(v1,v2),
   invent_Path(v2,v1),
   Edge(v1,v0).").
in file  [0:0-0:0])_");
rel_57_SCC_info_53->insert(RamDomain(53),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(15),RamDomain(35),RamDomain(75));
}();
/* END STRATUM 52 */
/* BEGIN STRATUM 53 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.54(54,"v0,v1","Rule","Edge,v1,v2","SCC,v2,v0","SCC(v0,v1) :- 
   Rule(684),
   Edge(v1,v2),
   SCC(v2,v0).").
in file  [0:0-0:0])_");
rel_58_SCC_info_54->insert(RamDomain(54),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(3),RamDomain(76));
}();
/* END STRATUM 53 */
/* BEGIN STRATUM 54 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.55(55,"v0,v1","Rule","invent_Path,v0,v2","SCC,v0,v1","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(2015),
   invent_Path(v0,v2),
   SCC(v0,v1),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_59_SCC_info_55->insert(RamDomain(55),RamDomain(0),RamDomain(1),RamDomain(43),RamDomain(7),RamDomain(24),RamDomain(77));
}();
/* END STRATUM 54 */
/* BEGIN STRATUM 55 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.56(56,"v0,v1","Rule","Edge,v0,v2","Edge,v1,v2","SCC(v0,v1) :- 
   Rule(854),
   Edge(v0,v2),
   Edge(v1,v2).").
in file  [0:0-0:0])_");
rel_60_SCC_info_56->insert(RamDomain(56),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(23),RamDomain(78));
}();
/* END STRATUM 55 */
/* BEGIN STRATUM 56 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.57(57,"v0,v1","Rule","Edge,v1,v0","invent_Path,v0,v1","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1336),
   Edge(v1,v0),
   invent_Path(v0,v1),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_61_SCC_info_57->insert(RamDomain(57),RamDomain(0),RamDomain(1),RamDomain(35),RamDomain(6),RamDomain(10),RamDomain(79));
}();
/* END STRATUM 56 */
/* BEGIN STRATUM 57 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.58(58,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v1","SCC,v1,v0","SCC(v0,v1) :- 
   Rule(1143),
   Edge(v1,v2),
   Edge(v2,v1),
   SCC(v1,v0).").
in file  [0:0-0:0])_");
rel_62_SCC_info_58->insert(RamDomain(58),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(4),RamDomain(10),RamDomain(80));
}();
/* END STRATUM 57 */
/* BEGIN STRATUM 58 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.59(59,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v1","invent_Path,v0,v1","SCC(v0,v1) :- 
   Rule(985),
   Edge(v1,v2),
   Edge(v2,v1),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_63_SCC_info_59->insert(RamDomain(59),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(4),RamDomain(6),RamDomain(81));
}();
/* END STRATUM 58 */
/* BEGIN STRATUM 59 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.6(6,"v0,v1","Rule","invent_Path,v2,v0","invent_Path,v1,v2","SCC(v0,v1) :- 
   Rule(1741),
   invent_Path(v2,v0),
   invent_Path(v1,v2).").
in file  [0:0-0:0])_");
rel_64_SCC_info_6->insert(RamDomain(6),RamDomain(0),RamDomain(1),RamDomain(12),RamDomain(13),RamDomain(18));
}();
/* END STRATUM 59 */
/* BEGIN STRATUM 60 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.60(60,"v0,v1","Rule","Edge,v0,v1","SCC(v0,v1) :- 
   Rule(733),
   Edge(v0,v1).").
in file  [0:0-0:0])_");
rel_65_SCC_info_60->insert(RamDomain(60),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(82));
}();
/* END STRATUM 60 */
/* BEGIN STRATUM 61 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.61(61,"v0,v1","Rule","Edge,v2,v0","Edge,v2,v1","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1075),
   Edge(v2,v0),
   Edge(v2,v1),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_66_SCC_info_61->insert(RamDomain(61),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(4),RamDomain(7),RamDomain(83));
}();
/* END STRATUM 61 */
/* BEGIN STRATUM 62 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.62(62,"v0,v1","Rule","invent_Path,v2,v1","invent_Path,v1,v2","invent_Path,v2,v0","SCC(v0,v1) :- 
   Rule(1783),
   invent_Path(v2,v1),
   invent_Path(v1,v2),
   invent_Path(v2,v0).").
in file  [0:0-0:0])_");
rel_67_SCC_info_62->insert(RamDomain(62),RamDomain(0),RamDomain(1),RamDomain(15),RamDomain(13),RamDomain(12),RamDomain(84));
}();
/* END STRATUM 62 */
/* BEGIN STRATUM 63 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.63(63,"v0,v1","Rule","Edge,v2,v0","SCC,v0,v1","SCC,v1,v2","SCC(v0,v1) :- 
   Rule(1540),
   Edge(v2,v0),
   SCC(v0,v1),
   SCC(v1,v2).").
in file  [0:0-0:0])_");
rel_68_SCC_info_63->insert(RamDomain(63),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(7),RamDomain(24),RamDomain(85));
}();
/* END STRATUM 63 */
/* BEGIN STRATUM 64 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.64(64,"v0,v1","Rule","invent_Path,v0,v2","SCC,v2,v0","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1951),
   invent_Path(v0,v2),
   SCC(v2,v0),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_69_SCC_info_64->insert(RamDomain(64),RamDomain(0),RamDomain(1),RamDomain(43),RamDomain(3),RamDomain(7),RamDomain(86));
}();
/* END STRATUM 64 */
/* BEGIN STRATUM 65 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.65(65,"v0,v1","Rule","Edge,v1,v2","Edge,v0,v2","invent_Path,v1,v0","SCC(v0,v1) :- 
   Rule(914),
   Edge(v1,v2),
   Edge(v0,v2),
   invent_Path(v1,v0).").
in file  [0:0-0:0])_");
rel_70_SCC_info_65->insert(RamDomain(65),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(30),RamDomain(9),RamDomain(87));
}();
/* END STRATUM 65 */
/* BEGIN STRATUM 66 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.66(66,"v0,v1","Rule","invent_Path,v1,v2","invent_Path,v2,v1","invent_Path,v2,v0","SCC(v0,v1) :- 
   Rule(1771),
   invent_Path(v1,v2),
   invent_Path(v2,v1),
   invent_Path(v2,v0).").
in file  [0:0-0:0])_");
rel_71_SCC_info_66->insert(RamDomain(66),RamDomain(0),RamDomain(1),RamDomain(13),RamDomain(15),RamDomain(12),RamDomain(88));
}();
/* END STRATUM 66 */
/* BEGIN STRATUM 67 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.67(67,"v0,v1","Rule","invent_Path,v1,v2","invent_Path,v2,v0","invent_Path,v0,v2","SCC(v0,v1) :- 
   Rule(1734),
   invent_Path(v1,v2),
   invent_Path(v2,v0),
   invent_Path(v0,v2).").
in file  [0:0-0:0])_");
rel_72_SCC_info_67->insert(RamDomain(67),RamDomain(0),RamDomain(1),RamDomain(13),RamDomain(12),RamDomain(43),RamDomain(89));
}();
/* END STRATUM 67 */
/* BEGIN STRATUM 68 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.68(68,"v0,v1","Rule","invent_Path,v2,v1","invent_Path,v2,v0","invent_Path,v0,v1","SCC(v0,v1) :- 
   Rule(1695),
   invent_Path(v2,v1),
   invent_Path(v2,v0),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_73_SCC_info_68->insert(RamDomain(68),RamDomain(0),RamDomain(1),RamDomain(15),RamDomain(12),RamDomain(6),RamDomain(90));
}();
/* END STRATUM 68 */
/* BEGIN STRATUM 69 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.69(69,"v0,v1","Rule","invent_Path,v0,v1","SCC,v0,v2","SCC,v2,v1","SCC(v0,v1) :- 
   Rule(2019),
   invent_Path(v0,v1),
   SCC(v0,v2),
   SCC(v2,v1).").
in file  [0:0-0:0])_");
rel_74_SCC_info_69->insert(RamDomain(69),RamDomain(0),RamDomain(1),RamDomain(6),RamDomain(16),RamDomain(19),RamDomain(91));
}();
/* END STRATUM 69 */
/* BEGIN STRATUM 70 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.7(7,"v0,v1","Rule","invent_Path,v2,v1","SCC,v2,v1","invent_Path,v2,v0","SCC(v0,v1) :- 
   Rule(1933),
   invent_Path(v2,v1),
   SCC(v2,v1),
   invent_Path(v2,v0).").
in file  [0:0-0:0])_");
rel_75_SCC_info_7->insert(RamDomain(7),RamDomain(0),RamDomain(1),RamDomain(15),RamDomain(19),RamDomain(12),RamDomain(20));
}();
/* END STRATUM 70 */
/* BEGIN STRATUM 71 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.70(70,"v0,v1","Rule","SCC,v0,v2","SCC,v1,v2","SCC,v2,v1","SCC(v0,v1) :- 
   Rule(2243),
   SCC(v0,v2),
   SCC(v1,v2),
   SCC(v2,v1).").
in file  [0:0-0:0])_");
rel_76_SCC_info_70->insert(RamDomain(70),RamDomain(0),RamDomain(1),RamDomain(16),RamDomain(24),RamDomain(19),RamDomain(92));
}();
/* END STRATUM 71 */
/* BEGIN STRATUM 72 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.8(8,"v0,v1","Rule","invent_Path,v1,v0","invent_Path,v0,v1","SCC,v0,v1","SCC(v0,v1) :- 
   Rule(1791),
   invent_Path(v1,v0),
   invent_Path(v0,v1),
   SCC(v0,v1).").
in file  [0:0-0:0])_");
rel_77_SCC_info_8->insert(RamDomain(8),RamDomain(0),RamDomain(1),RamDomain(9),RamDomain(6),RamDomain(7),RamDomain(21));
}();
/* END STRATUM 72 */
/* BEGIN STRATUM 73 */
[&]() {
SignalHandler::instance()->setMsg(R"_(SCC.@info.9(9,"v0,v1","Rule","invent_Path,v0,v1","invent_Path,v1,v0","SCC(v0,v1) :- 
   Rule(692),
   invent_Path(v0,v1),
   invent_Path(v1,v0).").
in file  [0:0-0:0])_");
rel_78_SCC_info_9->insert(RamDomain(9),RamDomain(0),RamDomain(1),RamDomain(6),RamDomain(9),RamDomain(22));
}();
/* END STRATUM 73 */
/* BEGIN STRATUM 74 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.1(1,"v0,v1","Rule","Edge,v0,v1","Edge,v2,v1","invent_Path,v0,v2","invent_Path(v0,v1) :- 
   Rule(238),
   Edge(v0,v1),
   Edge(v2,v1),
   invent_Path(v0,v2).").
in file  [0:0-0:0])_");
rel_79_invent_Path_info_1->insert(RamDomain(1),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(4),RamDomain(43),RamDomain(93));
}();
/* END STRATUM 74 */
/* BEGIN STRATUM 75 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.10(10,"v0,v1","Rule","Edge,v2,v1","Edge,v0,v2","invent_Path(v0,v1) :- 
   Rule(188),
   Edge(v2,v1),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_80_invent_Path_info_10->insert(RamDomain(10),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(30),RamDomain(102));
}();
/* END STRATUM 75 */
/* BEGIN STRATUM 76 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.11(11,"v0,v1","Rule","invent_Path,v1","invent_Path,v0,v1","invent_Path(v0,v1) :- 
   Rule(607),
   invent_Path(v1,_),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_81_invent_Path_info_11->insert(RamDomain(11),RamDomain(0),RamDomain(1),RamDomain(38),RamDomain(6),RamDomain(103));
}();
/* END STRATUM 76 */
/* BEGIN STRATUM 77 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.12(12,"v0,v1","Rule","Edge,v0,v2","Edge,v1,v2","invent_Path(v0,v1) :- 
   Rule(142),
   Edge(v0,v2),
   Edge(v1,v2).").
in file  [0:0-0:0])_");
rel_82_invent_Path_info_12->insert(RamDomain(12),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(23),RamDomain(104));
}();
/* END STRATUM 77 */
/* BEGIN STRATUM 78 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.13(13,"v0,v1","Rule","Edge,v1,v0","Edge,v2,v0","Edge,v0,v2","invent_Path(v0,v1) :- 
   Rule(69),
   Edge(v1,v0),
   Edge(v2,v0),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_83_invent_Path_info_13->insert(RamDomain(13),RamDomain(0),RamDomain(1),RamDomain(35),RamDomain(2),RamDomain(30),RamDomain(105));
}();
/* END STRATUM 78 */
/* BEGIN STRATUM 79 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.14(14,"v0,v1","Rule","Edge,v1,v2","invent_Path,v2,v1","invent_Path,v0,v2","invent_Path(v0,v1) :- 
   Rule(483),
   Edge(v1,v2),
   invent_Path(v2,v1),
   invent_Path(v0,v2).").
in file  [0:0-0:0])_");
rel_84_invent_Path_info_14->insert(RamDomain(14),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(15),RamDomain(43),RamDomain(106));
}();
/* END STRATUM 79 */
/* BEGIN STRATUM 80 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.15(15,"v0,v1","Rule","invent_Path,v1,v2","invent_Path,v2,v0","invent_Path,v0,v2","invent_Path(v0,v1) :- 
   Rule(592),
   invent_Path(v1,v2),
   invent_Path(v2,v0),
   invent_Path(v0,v2).").
in file  [0:0-0:0])_");
rel_85_invent_Path_info_15->insert(RamDomain(15),RamDomain(0),RamDomain(1),RamDomain(13),RamDomain(12),RamDomain(43),RamDomain(107));
}();
/* END STRATUM 80 */
/* BEGIN STRATUM 81 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.16(16,"v0,v1","Rule","Edge,v0","Edge,v0,v1","invent_Path(v0,v1) :- 
   Rule(48),
   Edge(v0,_),
   Edge(v0,v1).").
in file  [0:0-0:0])_");
rel_86_invent_Path_info_16->insert(RamDomain(16),RamDomain(0),RamDomain(1),RamDomain(67),RamDomain(29),RamDomain(108));
}();
/* END STRATUM 81 */
/* BEGIN STRATUM 82 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.17(17,"v0,v1","Rule","Edge,v2,v0","Edge,v0,v2","invent_Path,v0,v1","invent_Path(v0,v1) :- 
   Rule(214),
   Edge(v2,v0),
   Edge(v0,v2),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_87_invent_Path_info_17->insert(RamDomain(17),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(30),RamDomain(6),RamDomain(109));
}();
/* END STRATUM 82 */
/* BEGIN STRATUM 83 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.18(18,"v0,v1","Rule","Edge,v1,v2","Edge,v1,v0","Edge,v2,v0","invent_Path(v0,v1) :- 
   Rule(73),
   Edge(v1,v2),
   Edge(v1,v0),
   Edge(v2,v0).").
in file  [0:0-0:0])_");
rel_88_invent_Path_info_18->insert(RamDomain(18),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(35),RamDomain(2),RamDomain(110));
}();
/* END STRATUM 83 */
/* BEGIN STRATUM 84 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.19(19,"v0,v1","Rule","Edge,v0,v2","invent_Path,v2,v1","invent_Path(v0,v1) :- 
   Rule(23),
   Edge(v0,v2),
   invent_Path(v2,v1).").
in file  [0:0-0:0])_");
rel_89_invent_Path_info_19->insert(RamDomain(19),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(15),RamDomain(111));
}();
/* END STRATUM 84 */
/* BEGIN STRATUM 85 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.2(2,"v0,v1","Rule","Edge,v0,v1","invent_Path(v0,v1) :- 
   Rule(0),
   Edge(v0,v1).").
in file  [0:0-0:0])_");
rel_90_invent_Path_info_2->insert(RamDomain(2),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(94));
}();
/* END STRATUM 85 */
/* BEGIN STRATUM 86 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.20(20,"v0,v1","Rule","Edge,v2,v1","Edge,v2,v0","invent_Path(v0,v1) :- 
   Rule(187),
   Edge(v2,v1),
   Edge(v2,v0).").
in file  [0:0-0:0])_");
rel_91_invent_Path_info_20->insert(RamDomain(20),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(2),RamDomain(112));
}();
/* END STRATUM 86 */
/* BEGIN STRATUM 87 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.21(21,"v0,v1","Rule","Edge,v1,v2","Edge,v0,v1","Edge,v2,v0","invent_Path(v0,v1) :- 
   Rule(106),
   Edge(v1,v2),
   Edge(v0,v1),
   Edge(v2,v0).").
in file  [0:0-0:0])_");
rel_92_invent_Path_info_21->insert(RamDomain(21),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(29),RamDomain(2),RamDomain(113));
}();
/* END STRATUM 87 */
/* BEGIN STRATUM 88 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.22(22,"v0,v1","Rule","Edge,v2,v0","Edge,v1,v2","invent_Path(v0,v1) :- 
   Rule(178),
   Edge(v2,v0),
   Edge(v1,v2).").
in file  [0:0-0:0])_");
rel_93_invent_Path_info_22->insert(RamDomain(22),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(23),RamDomain(114));
}();
/* END STRATUM 88 */
/* BEGIN STRATUM 89 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.23(23,"v0,v1","Rule","Edge,v2,v1","Edge,v0,v2","invent_Path(v0,v1) :- 
   Rule(184),
   Edge(v2,v1),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_94_invent_Path_info_23->insert(RamDomain(23),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(30),RamDomain(115));
}();
/* END STRATUM 89 */
/* BEGIN STRATUM 90 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.24(24,"v0,v1","Rule","invent_Path,v1,v2","invent_Path,v2,v1","invent_Path,v0,v1","invent_Path(v0,v1) :- 
   Rule(603),
   invent_Path(v1,v2),
   invent_Path(v2,v1),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_95_invent_Path_info_24->insert(RamDomain(24),RamDomain(0),RamDomain(1),RamDomain(13),RamDomain(15),RamDomain(6),RamDomain(116));
}();
/* END STRATUM 90 */
/* BEGIN STRATUM 91 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.25(25,"v0,v1","Rule","Edge,v1,v0","Edge,v0,v2","invent_Path,v0,v2","invent_Path(v0,v1) :- 
   Rule(207),
   Edge(v1,v0),
   Edge(v0,v2),
   invent_Path(v0,v2).").
in file  [0:0-0:0])_");
rel_96_invent_Path_info_25->insert(RamDomain(25),RamDomain(0),RamDomain(1),RamDomain(35),RamDomain(30),RamDomain(43),RamDomain(117));
}();
/* END STRATUM 91 */
/* BEGIN STRATUM 92 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.26(26,"v0,v1","Rule","Edge,v2,v1","Edge,v1,v2","invent_Path,v0,v1","invent_Path(v0,v1) :- 
   Rule(297),
   Edge(v2,v1),
   Edge(v1,v2),
   invent_Path(v0,v1).").
in file  [0:0-0:0])_");
rel_97_invent_Path_info_26->insert(RamDomain(26),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(23),RamDomain(6),RamDomain(118));
}();
/* END STRATUM 92 */
/* BEGIN STRATUM 93 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.27(27,"v0,v1","Rule","Edge,v2,v0","Edge,v2,v1","invent_Path(v0,v1) :- 
   Rule(176),
   Edge(v2,v0),
   Edge(v2,v1).").
in file  [0:0-0:0])_");
rel_98_invent_Path_info_27->insert(RamDomain(27),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(4),RamDomain(119));
}();
/* END STRATUM 93 */
/* BEGIN STRATUM 94 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.28(28,"v0,v1","Rule","Edge,v0,v1","Edge,v2,v0","Edge,v0,v2","invent_Path(v0,v1) :- 
   Rule(53),
   Edge(v0,v1),
   Edge(v2,v0),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_99_invent_Path_info_28->insert(RamDomain(28),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(2),RamDomain(30),RamDomain(120));
}();
/* END STRATUM 94 */
/* BEGIN STRATUM 95 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.29(29,"v0,v1","Rule","invent_Path,v1,v0","invent_Path,v0,v2","invent_Path,v2,v0","invent_Path(v0,v1) :- 
   Rule(512),
   invent_Path(v1,v0),
   invent_Path(v0,v2),
   invent_Path(v2,v0).").
in file  [0:0-0:0])_");
rel_100_invent_Path_info_29->insert(RamDomain(29),RamDomain(0),RamDomain(1),RamDomain(9),RamDomain(43),RamDomain(12),RamDomain(121));
}();
/* END STRATUM 95 */
/* BEGIN STRATUM 96 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.3(3,"v0,v1","Rule","Edge,v2,v1","invent_Path,v1,v2","invent_Path,v1,v0","invent_Path(v0,v1) :- 
   Rule(456),
   Edge(v2,v1),
   invent_Path(v1,v2),
   invent_Path(v1,v0).").
in file  [0:0-0:0])_");
rel_101_invent_Path_info_3->insert(RamDomain(3),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(13),RamDomain(9),RamDomain(95));
}();
/* END STRATUM 96 */
/* BEGIN STRATUM 97 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.30(30,"v0,v1","Rule","Edge,v0","invent_Path,v1,v0","invent_Path(v0,v1) :- 
   Rule(210),
   Edge(v0,_),
   invent_Path(v1,v0).").
in file  [0:0-0:0])_");
rel_102_invent_Path_info_30->insert(RamDomain(30),RamDomain(0),RamDomain(1),RamDomain(67),RamDomain(9),RamDomain(122));
}();
/* END STRATUM 97 */
/* BEGIN STRATUM 98 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.4(4,"v0,v1","Rule","Edge,v2,v1","Edge,v0,v1","Edge,v0,v2","invent_Path(v0,v1) :- 
   Rule(77),
   Edge(v2,v1),
   Edge(v0,v1),
   Edge(v0,v2).").
in file  [0:0-0:0])_");
rel_103_invent_Path_info_4->insert(RamDomain(4),RamDomain(0),RamDomain(1),RamDomain(4),RamDomain(29),RamDomain(30),RamDomain(96));
}();
/* END STRATUM 98 */
/* BEGIN STRATUM 99 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.5(5,"v0,v1","Rule","Edge,v0,v1","Edge,v0,v2","Edge,v1,v2","invent_Path(v0,v1) :- 
   Rule(99),
   Edge(v0,v1),
   Edge(v0,v2),
   Edge(v1,v2).").
in file  [0:0-0:0])_");
rel_104_invent_Path_info_5->insert(RamDomain(5),RamDomain(0),RamDomain(1),RamDomain(29),RamDomain(30),RamDomain(23),RamDomain(97));
}();
/* END STRATUM 99 */
/* BEGIN STRATUM 100 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.6(6,"v0,v1","Rule","Edge,v2,v0","invent_Path,v0,v2","Edge,v1,v0","invent_Path(v0,v1) :- 
   Rule(202),
   Edge(v2,v0),
   invent_Path(v0,v2),
   Edge(v1,v0).").
in file  [0:0-0:0])_");
rel_105_invent_Path_info_6->insert(RamDomain(6),RamDomain(0),RamDomain(1),RamDomain(2),RamDomain(43),RamDomain(35),RamDomain(98));
}();
/* END STRATUM 100 */
/* BEGIN STRATUM 101 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.7(7,"v0,v1","Rule","Edge,v1,v2","Edge,v2,v0","invent_Path(v0,v1) :- 
   Rule(174),
   Edge(v1,v2),
   Edge(v2,v0).").
in file  [0:0-0:0])_");
rel_106_invent_Path_info_7->insert(RamDomain(7),RamDomain(0),RamDomain(1),RamDomain(23),RamDomain(2),RamDomain(99));
}();
/* END STRATUM 101 */
/* BEGIN STRATUM 102 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.8(8,"v0,v1","Rule","invent_Path,v1,v0","invent_Path,v2,v0","invent_Path,v0,v2","invent_Path(v0,v1) :- 
   Rule(525),
   invent_Path(v1,v0),
   invent_Path(v2,v0),
   invent_Path(v0,v2).").
in file  [0:0-0:0])_");
rel_107_invent_Path_info_8->insert(RamDomain(8),RamDomain(0),RamDomain(1),RamDomain(9),RamDomain(12),RamDomain(43),RamDomain(100));
}();
/* END STRATUM 102 */
/* BEGIN STRATUM 103 */
[&]() {
SignalHandler::instance()->setMsg(R"_(invent_Path.@info.9(9,"v0,v1","Rule","Edge,v0,v2","Edge,v2,v0","Edge,v1,v2","invent_Path(v0,v1) :- 
   Rule(123),
   Edge(v0,v2),
   Edge(v2,v0),
   Edge(v1,v2).").
in file  [0:0-0:0])_");
rel_108_invent_Path_info_9->insert(RamDomain(9),RamDomain(0),RamDomain(1),RamDomain(30),RamDomain(2),RamDomain(23),RamDomain(101));
}();
/* END STRATUM 103 */

// -- relation hint statistics --
if(isHintsProfilingEnabled()) {
std::cout << " -- Operation Hint Statistics --\n";
std::cout << "Relation rel_1_Edge:\n";
rel_1_Edge->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_2_Rule:\n";
rel_2_Rule->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_3_invent_Path:\n";
rel_3_invent_Path->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_4_delta_invent_Path:\n";
rel_4_delta_invent_Path->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_5_new_invent_Path:\n";
rel_5_new_invent_Path->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_6_SCC:\n";
rel_6_SCC->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_7_delta_SCC:\n";
rel_7_delta_SCC->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_8_new_SCC:\n";
rel_8_new_SCC->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_9_SCC_info_1:\n";
rel_9_SCC_info_1->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_10_SCC_info_10:\n";
rel_10_SCC_info_10->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_11_SCC_info_11:\n";
rel_11_SCC_info_11->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_12_SCC_info_12:\n";
rel_12_SCC_info_12->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_13_SCC_info_13:\n";
rel_13_SCC_info_13->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_14_SCC_info_14:\n";
rel_14_SCC_info_14->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_15_SCC_info_15:\n";
rel_15_SCC_info_15->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_16_SCC_info_16:\n";
rel_16_SCC_info_16->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_17_SCC_info_17:\n";
rel_17_SCC_info_17->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_18_SCC_info_18:\n";
rel_18_SCC_info_18->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_19_SCC_info_19:\n";
rel_19_SCC_info_19->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_20_SCC_info_2:\n";
rel_20_SCC_info_2->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_21_SCC_info_20:\n";
rel_21_SCC_info_20->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_22_SCC_info_21:\n";
rel_22_SCC_info_21->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_23_SCC_info_22:\n";
rel_23_SCC_info_22->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_24_SCC_info_23:\n";
rel_24_SCC_info_23->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_25_SCC_info_24:\n";
rel_25_SCC_info_24->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_26_SCC_info_25:\n";
rel_26_SCC_info_25->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_27_SCC_info_26:\n";
rel_27_SCC_info_26->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_28_SCC_info_27:\n";
rel_28_SCC_info_27->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_29_SCC_info_28:\n";
rel_29_SCC_info_28->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_30_SCC_info_29:\n";
rel_30_SCC_info_29->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_31_SCC_info_3:\n";
rel_31_SCC_info_3->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_32_SCC_info_30:\n";
rel_32_SCC_info_30->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_33_SCC_info_31:\n";
rel_33_SCC_info_31->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_34_SCC_info_32:\n";
rel_34_SCC_info_32->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_35_SCC_info_33:\n";
rel_35_SCC_info_33->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_36_SCC_info_34:\n";
rel_36_SCC_info_34->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_37_SCC_info_35:\n";
rel_37_SCC_info_35->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_38_SCC_info_36:\n";
rel_38_SCC_info_36->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_39_SCC_info_37:\n";
rel_39_SCC_info_37->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_40_SCC_info_38:\n";
rel_40_SCC_info_38->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_41_SCC_info_39:\n";
rel_41_SCC_info_39->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_42_SCC_info_4:\n";
rel_42_SCC_info_4->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_43_SCC_info_40:\n";
rel_43_SCC_info_40->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_44_SCC_info_41:\n";
rel_44_SCC_info_41->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_45_SCC_info_42:\n";
rel_45_SCC_info_42->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_46_SCC_info_43:\n";
rel_46_SCC_info_43->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_47_SCC_info_44:\n";
rel_47_SCC_info_44->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_48_SCC_info_45:\n";
rel_48_SCC_info_45->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_49_SCC_info_46:\n";
rel_49_SCC_info_46->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_50_SCC_info_47:\n";
rel_50_SCC_info_47->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_51_SCC_info_48:\n";
rel_51_SCC_info_48->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_52_SCC_info_49:\n";
rel_52_SCC_info_49->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_53_SCC_info_5:\n";
rel_53_SCC_info_5->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_54_SCC_info_50:\n";
rel_54_SCC_info_50->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_55_SCC_info_51:\n";
rel_55_SCC_info_51->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_56_SCC_info_52:\n";
rel_56_SCC_info_52->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_57_SCC_info_53:\n";
rel_57_SCC_info_53->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_58_SCC_info_54:\n";
rel_58_SCC_info_54->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_59_SCC_info_55:\n";
rel_59_SCC_info_55->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_60_SCC_info_56:\n";
rel_60_SCC_info_56->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_61_SCC_info_57:\n";
rel_61_SCC_info_57->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_62_SCC_info_58:\n";
rel_62_SCC_info_58->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_63_SCC_info_59:\n";
rel_63_SCC_info_59->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_64_SCC_info_6:\n";
rel_64_SCC_info_6->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_65_SCC_info_60:\n";
rel_65_SCC_info_60->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_66_SCC_info_61:\n";
rel_66_SCC_info_61->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_67_SCC_info_62:\n";
rel_67_SCC_info_62->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_68_SCC_info_63:\n";
rel_68_SCC_info_63->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_69_SCC_info_64:\n";
rel_69_SCC_info_64->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_70_SCC_info_65:\n";
rel_70_SCC_info_65->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_71_SCC_info_66:\n";
rel_71_SCC_info_66->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_72_SCC_info_67:\n";
rel_72_SCC_info_67->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_73_SCC_info_68:\n";
rel_73_SCC_info_68->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_74_SCC_info_69:\n";
rel_74_SCC_info_69->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_75_SCC_info_7:\n";
rel_75_SCC_info_7->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_76_SCC_info_70:\n";
rel_76_SCC_info_70->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_77_SCC_info_8:\n";
rel_77_SCC_info_8->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_78_SCC_info_9:\n";
rel_78_SCC_info_9->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_79_invent_Path_info_1:\n";
rel_79_invent_Path_info_1->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_80_invent_Path_info_10:\n";
rel_80_invent_Path_info_10->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_81_invent_Path_info_11:\n";
rel_81_invent_Path_info_11->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_82_invent_Path_info_12:\n";
rel_82_invent_Path_info_12->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_83_invent_Path_info_13:\n";
rel_83_invent_Path_info_13->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_84_invent_Path_info_14:\n";
rel_84_invent_Path_info_14->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_85_invent_Path_info_15:\n";
rel_85_invent_Path_info_15->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_86_invent_Path_info_16:\n";
rel_86_invent_Path_info_16->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_87_invent_Path_info_17:\n";
rel_87_invent_Path_info_17->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_88_invent_Path_info_18:\n";
rel_88_invent_Path_info_18->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_89_invent_Path_info_19:\n";
rel_89_invent_Path_info_19->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_90_invent_Path_info_2:\n";
rel_90_invent_Path_info_2->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_91_invent_Path_info_20:\n";
rel_91_invent_Path_info_20->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_92_invent_Path_info_21:\n";
rel_92_invent_Path_info_21->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_93_invent_Path_info_22:\n";
rel_93_invent_Path_info_22->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_94_invent_Path_info_23:\n";
rel_94_invent_Path_info_23->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_95_invent_Path_info_24:\n";
rel_95_invent_Path_info_24->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_96_invent_Path_info_25:\n";
rel_96_invent_Path_info_25->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_97_invent_Path_info_26:\n";
rel_97_invent_Path_info_26->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_98_invent_Path_info_27:\n";
rel_98_invent_Path_info_27->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_99_invent_Path_info_28:\n";
rel_99_invent_Path_info_28->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_100_invent_Path_info_29:\n";
rel_100_invent_Path_info_29->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_101_invent_Path_info_3:\n";
rel_101_invent_Path_info_3->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_102_invent_Path_info_30:\n";
rel_102_invent_Path_info_30->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_103_invent_Path_info_4:\n";
rel_103_invent_Path_info_4->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_104_invent_Path_info_5:\n";
rel_104_invent_Path_info_5->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_105_invent_Path_info_6:\n";
rel_105_invent_Path_info_6->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_106_invent_Path_info_7:\n";
rel_106_invent_Path_info_7->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_107_invent_Path_info_8:\n";
rel_107_invent_Path_info_8->printHintStatistics(std::cout,"  ");
std::cout << "\n";
std::cout << "Relation rel_108_invent_Path_info_9:\n";
rel_108_invent_Path_info_9->printHintStatistics(std::cout,"  ");
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
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1"},{"filename","./invent_Path.csv"},{"name","invent_Path"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_3_invent_Path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","v0\tv1"},{"filename","./SCC.csv"},{"name","SCC"}});
if (!outputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = outputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_6_SCC);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void loadAll(std::string inputDirectory = ".") override {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./Edge.facts"},{"name","Edge"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->readAll(*rel_1_Edge);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"filename","./Rule.facts"},{"name","Rule"}});
if (!inputDirectory.empty() && directiveMap["IO"] == "file" && directiveMap["filename"].front() != '/') {directiveMap["filename"] = inputDirectory + "/" + directiveMap["filename"];}
IODirectives ioDirectives(directiveMap);
IOSystem::getInstance().getReader(std::vector<bool>({0,0,0}), symTable, ioDirectives, true)->readAll(*rel_2_Rule);
} catch (std::exception& e) {std::cerr << "Error loading data: " << e.what() << '\n';}
}
public:
void dumpInputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_1_Edge");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_1_Edge);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_2_Rule");
IOSystem::getInstance().getWriter(std::vector<bool>({0,0,0}), symTable, ioDirectives, true)->writeAll(*rel_2_Rule);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
void dumpOutputs(std::ostream& out = std::cout) override {
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_3_invent_Path");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_3_invent_Path);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
try {IODirectives ioDirectives;
ioDirectives.setIOType("stdout");
ioDirectives.setRelationName("rel_6_SCC");
IOSystem::getInstance().getWriter(std::vector<bool>({1,1,0,0}), symTable, ioDirectives, true)->writeAll(*rel_6_SCC);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
public:
SymbolTable& getSymbolTable() override {
return symTable;
}
void executeSubroutine(std::string name, const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) override {
if (name == "SCC_10_negation_subproof") {
subproof_0(args, ret, err);
}
if (name == "SCC_10_subproof") {
subproof_1(args, ret, err);
}
if (name == "SCC_11_negation_subproof") {
subproof_2(args, ret, err);
}
if (name == "SCC_11_subproof") {
subproof_3(args, ret, err);
}
if (name == "SCC_12_negation_subproof") {
subproof_4(args, ret, err);
}
if (name == "SCC_12_subproof") {
subproof_5(args, ret, err);
}
if (name == "SCC_13_negation_subproof") {
subproof_6(args, ret, err);
}
if (name == "SCC_13_subproof") {
subproof_7(args, ret, err);
}
if (name == "SCC_14_negation_subproof") {
subproof_8(args, ret, err);
}
if (name == "SCC_14_subproof") {
subproof_9(args, ret, err);
}
if (name == "SCC_15_negation_subproof") {
subproof_10(args, ret, err);
}
if (name == "SCC_15_subproof") {
subproof_11(args, ret, err);
}
if (name == "SCC_16_negation_subproof") {
subproof_12(args, ret, err);
}
if (name == "SCC_16_subproof") {
subproof_13(args, ret, err);
}
if (name == "SCC_17_negation_subproof") {
subproof_14(args, ret, err);
}
if (name == "SCC_17_subproof") {
subproof_15(args, ret, err);
}
if (name == "SCC_18_negation_subproof") {
subproof_16(args, ret, err);
}
if (name == "SCC_18_subproof") {
subproof_17(args, ret, err);
}
if (name == "SCC_19_negation_subproof") {
subproof_18(args, ret, err);
}
if (name == "SCC_19_subproof") {
subproof_19(args, ret, err);
}
if (name == "SCC_1_negation_subproof") {
subproof_20(args, ret, err);
}
if (name == "SCC_1_subproof") {
subproof_21(args, ret, err);
}
if (name == "SCC_20_negation_subproof") {
subproof_22(args, ret, err);
}
if (name == "SCC_20_subproof") {
subproof_23(args, ret, err);
}
if (name == "SCC_21_negation_subproof") {
subproof_24(args, ret, err);
}
if (name == "SCC_21_subproof") {
subproof_25(args, ret, err);
}
if (name == "SCC_22_negation_subproof") {
subproof_26(args, ret, err);
}
if (name == "SCC_22_subproof") {
subproof_27(args, ret, err);
}
if (name == "SCC_23_negation_subproof") {
subproof_28(args, ret, err);
}
if (name == "SCC_23_subproof") {
subproof_29(args, ret, err);
}
if (name == "SCC_24_negation_subproof") {
subproof_30(args, ret, err);
}
if (name == "SCC_24_subproof") {
subproof_31(args, ret, err);
}
if (name == "SCC_25_negation_subproof") {
subproof_32(args, ret, err);
}
if (name == "SCC_25_subproof") {
subproof_33(args, ret, err);
}
if (name == "SCC_26_negation_subproof") {
subproof_34(args, ret, err);
}
if (name == "SCC_26_subproof") {
subproof_35(args, ret, err);
}
if (name == "SCC_27_negation_subproof") {
subproof_36(args, ret, err);
}
if (name == "SCC_27_subproof") {
subproof_37(args, ret, err);
}
if (name == "SCC_28_negation_subproof") {
subproof_38(args, ret, err);
}
if (name == "SCC_28_subproof") {
subproof_39(args, ret, err);
}
if (name == "SCC_29_negation_subproof") {
subproof_40(args, ret, err);
}
if (name == "SCC_29_subproof") {
subproof_41(args, ret, err);
}
if (name == "SCC_2_negation_subproof") {
subproof_42(args, ret, err);
}
if (name == "SCC_2_subproof") {
subproof_43(args, ret, err);
}
if (name == "SCC_30_negation_subproof") {
subproof_44(args, ret, err);
}
if (name == "SCC_30_subproof") {
subproof_45(args, ret, err);
}
if (name == "SCC_31_negation_subproof") {
subproof_46(args, ret, err);
}
if (name == "SCC_31_subproof") {
subproof_47(args, ret, err);
}
if (name == "SCC_32_negation_subproof") {
subproof_48(args, ret, err);
}
if (name == "SCC_32_subproof") {
subproof_49(args, ret, err);
}
if (name == "SCC_33_negation_subproof") {
subproof_50(args, ret, err);
}
if (name == "SCC_33_subproof") {
subproof_51(args, ret, err);
}
if (name == "SCC_34_negation_subproof") {
subproof_52(args, ret, err);
}
if (name == "SCC_34_subproof") {
subproof_53(args, ret, err);
}
if (name == "SCC_35_negation_subproof") {
subproof_54(args, ret, err);
}
if (name == "SCC_35_subproof") {
subproof_55(args, ret, err);
}
if (name == "SCC_36_negation_subproof") {
subproof_56(args, ret, err);
}
if (name == "SCC_36_subproof") {
subproof_57(args, ret, err);
}
if (name == "SCC_37_negation_subproof") {
subproof_58(args, ret, err);
}
if (name == "SCC_37_subproof") {
subproof_59(args, ret, err);
}
if (name == "SCC_38_negation_subproof") {
subproof_60(args, ret, err);
}
if (name == "SCC_38_subproof") {
subproof_61(args, ret, err);
}
if (name == "SCC_39_negation_subproof") {
subproof_62(args, ret, err);
}
if (name == "SCC_39_subproof") {
subproof_63(args, ret, err);
}
if (name == "SCC_3_negation_subproof") {
subproof_64(args, ret, err);
}
if (name == "SCC_3_subproof") {
subproof_65(args, ret, err);
}
if (name == "SCC_40_negation_subproof") {
subproof_66(args, ret, err);
}
if (name == "SCC_40_subproof") {
subproof_67(args, ret, err);
}
if (name == "SCC_41_negation_subproof") {
subproof_68(args, ret, err);
}
if (name == "SCC_41_subproof") {
subproof_69(args, ret, err);
}
if (name == "SCC_42_negation_subproof") {
subproof_70(args, ret, err);
}
if (name == "SCC_42_subproof") {
subproof_71(args, ret, err);
}
if (name == "SCC_43_negation_subproof") {
subproof_72(args, ret, err);
}
if (name == "SCC_43_subproof") {
subproof_73(args, ret, err);
}
if (name == "SCC_44_negation_subproof") {
subproof_74(args, ret, err);
}
if (name == "SCC_44_subproof") {
subproof_75(args, ret, err);
}
if (name == "SCC_45_negation_subproof") {
subproof_76(args, ret, err);
}
if (name == "SCC_45_subproof") {
subproof_77(args, ret, err);
}
if (name == "SCC_46_negation_subproof") {
subproof_78(args, ret, err);
}
if (name == "SCC_46_subproof") {
subproof_79(args, ret, err);
}
if (name == "SCC_47_negation_subproof") {
subproof_80(args, ret, err);
}
if (name == "SCC_47_subproof") {
subproof_81(args, ret, err);
}
if (name == "SCC_48_negation_subproof") {
subproof_82(args, ret, err);
}
if (name == "SCC_48_subproof") {
subproof_83(args, ret, err);
}
if (name == "SCC_49_negation_subproof") {
subproof_84(args, ret, err);
}
if (name == "SCC_49_subproof") {
subproof_85(args, ret, err);
}
if (name == "SCC_4_negation_subproof") {
subproof_86(args, ret, err);
}
if (name == "SCC_4_subproof") {
subproof_87(args, ret, err);
}
if (name == "SCC_50_negation_subproof") {
subproof_88(args, ret, err);
}
if (name == "SCC_50_subproof") {
subproof_89(args, ret, err);
}
if (name == "SCC_51_negation_subproof") {
subproof_90(args, ret, err);
}
if (name == "SCC_51_subproof") {
subproof_91(args, ret, err);
}
if (name == "SCC_52_negation_subproof") {
subproof_92(args, ret, err);
}
if (name == "SCC_52_subproof") {
subproof_93(args, ret, err);
}
if (name == "SCC_53_negation_subproof") {
subproof_94(args, ret, err);
}
if (name == "SCC_53_subproof") {
subproof_95(args, ret, err);
}
if (name == "SCC_54_negation_subproof") {
subproof_96(args, ret, err);
}
if (name == "SCC_54_subproof") {
subproof_97(args, ret, err);
}
if (name == "SCC_55_negation_subproof") {
subproof_98(args, ret, err);
}
if (name == "SCC_55_subproof") {
subproof_99(args, ret, err);
}
if (name == "SCC_56_negation_subproof") {
subproof_100(args, ret, err);
}
if (name == "SCC_56_subproof") {
subproof_101(args, ret, err);
}
if (name == "SCC_57_negation_subproof") {
subproof_102(args, ret, err);
}
if (name == "SCC_57_subproof") {
subproof_103(args, ret, err);
}
if (name == "SCC_58_negation_subproof") {
subproof_104(args, ret, err);
}
if (name == "SCC_58_subproof") {
subproof_105(args, ret, err);
}
if (name == "SCC_59_negation_subproof") {
subproof_106(args, ret, err);
}
if (name == "SCC_59_subproof") {
subproof_107(args, ret, err);
}
if (name == "SCC_5_negation_subproof") {
subproof_108(args, ret, err);
}
if (name == "SCC_5_subproof") {
subproof_109(args, ret, err);
}
if (name == "SCC_60_negation_subproof") {
subproof_110(args, ret, err);
}
if (name == "SCC_60_subproof") {
subproof_111(args, ret, err);
}
if (name == "SCC_61_negation_subproof") {
subproof_112(args, ret, err);
}
if (name == "SCC_61_subproof") {
subproof_113(args, ret, err);
}
if (name == "SCC_62_negation_subproof") {
subproof_114(args, ret, err);
}
if (name == "SCC_62_subproof") {
subproof_115(args, ret, err);
}
if (name == "SCC_63_negation_subproof") {
subproof_116(args, ret, err);
}
if (name == "SCC_63_subproof") {
subproof_117(args, ret, err);
}
if (name == "SCC_64_negation_subproof") {
subproof_118(args, ret, err);
}
if (name == "SCC_64_subproof") {
subproof_119(args, ret, err);
}
if (name == "SCC_65_negation_subproof") {
subproof_120(args, ret, err);
}
if (name == "SCC_65_subproof") {
subproof_121(args, ret, err);
}
if (name == "SCC_66_negation_subproof") {
subproof_122(args, ret, err);
}
if (name == "SCC_66_subproof") {
subproof_123(args, ret, err);
}
if (name == "SCC_67_negation_subproof") {
subproof_124(args, ret, err);
}
if (name == "SCC_67_subproof") {
subproof_125(args, ret, err);
}
if (name == "SCC_68_negation_subproof") {
subproof_126(args, ret, err);
}
if (name == "SCC_68_subproof") {
subproof_127(args, ret, err);
}
if (name == "SCC_69_negation_subproof") {
subproof_128(args, ret, err);
}
if (name == "SCC_69_subproof") {
subproof_129(args, ret, err);
}
if (name == "SCC_6_negation_subproof") {
subproof_130(args, ret, err);
}
if (name == "SCC_6_subproof") {
subproof_131(args, ret, err);
}
if (name == "SCC_70_negation_subproof") {
subproof_132(args, ret, err);
}
if (name == "SCC_70_subproof") {
subproof_133(args, ret, err);
}
if (name == "SCC_7_negation_subproof") {
subproof_134(args, ret, err);
}
if (name == "SCC_7_subproof") {
subproof_135(args, ret, err);
}
if (name == "SCC_8_negation_subproof") {
subproof_136(args, ret, err);
}
if (name == "SCC_8_subproof") {
subproof_137(args, ret, err);
}
if (name == "SCC_9_negation_subproof") {
subproof_138(args, ret, err);
}
if (name == "SCC_9_subproof") {
subproof_139(args, ret, err);
}
if (name == "invent_Path_10_negation_subproof") {
subproof_140(args, ret, err);
}
if (name == "invent_Path_10_subproof") {
subproof_141(args, ret, err);
}
if (name == "invent_Path_11_negation_subproof") {
subproof_142(args, ret, err);
}
if (name == "invent_Path_11_subproof") {
subproof_143(args, ret, err);
}
if (name == "invent_Path_12_negation_subproof") {
subproof_144(args, ret, err);
}
if (name == "invent_Path_12_subproof") {
subproof_145(args, ret, err);
}
if (name == "invent_Path_13_negation_subproof") {
subproof_146(args, ret, err);
}
if (name == "invent_Path_13_subproof") {
subproof_147(args, ret, err);
}
if (name == "invent_Path_14_negation_subproof") {
subproof_148(args, ret, err);
}
if (name == "invent_Path_14_subproof") {
subproof_149(args, ret, err);
}
if (name == "invent_Path_15_negation_subproof") {
subproof_150(args, ret, err);
}
if (name == "invent_Path_15_subproof") {
subproof_151(args, ret, err);
}
if (name == "invent_Path_16_negation_subproof") {
subproof_152(args, ret, err);
}
if (name == "invent_Path_16_subproof") {
subproof_153(args, ret, err);
}
if (name == "invent_Path_17_negation_subproof") {
subproof_154(args, ret, err);
}
if (name == "invent_Path_17_subproof") {
subproof_155(args, ret, err);
}
if (name == "invent_Path_18_negation_subproof") {
subproof_156(args, ret, err);
}
if (name == "invent_Path_18_subproof") {
subproof_157(args, ret, err);
}
if (name == "invent_Path_19_negation_subproof") {
subproof_158(args, ret, err);
}
if (name == "invent_Path_19_subproof") {
subproof_159(args, ret, err);
}
if (name == "invent_Path_1_negation_subproof") {
subproof_160(args, ret, err);
}
if (name == "invent_Path_1_subproof") {
subproof_161(args, ret, err);
}
if (name == "invent_Path_20_negation_subproof") {
subproof_162(args, ret, err);
}
if (name == "invent_Path_20_subproof") {
subproof_163(args, ret, err);
}
if (name == "invent_Path_21_negation_subproof") {
subproof_164(args, ret, err);
}
if (name == "invent_Path_21_subproof") {
subproof_165(args, ret, err);
}
if (name == "invent_Path_22_negation_subproof") {
subproof_166(args, ret, err);
}
if (name == "invent_Path_22_subproof") {
subproof_167(args, ret, err);
}
if (name == "invent_Path_23_negation_subproof") {
subproof_168(args, ret, err);
}
if (name == "invent_Path_23_subproof") {
subproof_169(args, ret, err);
}
if (name == "invent_Path_24_negation_subproof") {
subproof_170(args, ret, err);
}
if (name == "invent_Path_24_subproof") {
subproof_171(args, ret, err);
}
if (name == "invent_Path_25_negation_subproof") {
subproof_172(args, ret, err);
}
if (name == "invent_Path_25_subproof") {
subproof_173(args, ret, err);
}
if (name == "invent_Path_26_negation_subproof") {
subproof_174(args, ret, err);
}
if (name == "invent_Path_26_subproof") {
subproof_175(args, ret, err);
}
if (name == "invent_Path_27_negation_subproof") {
subproof_176(args, ret, err);
}
if (name == "invent_Path_27_subproof") {
subproof_177(args, ret, err);
}
if (name == "invent_Path_28_negation_subproof") {
subproof_178(args, ret, err);
}
if (name == "invent_Path_28_subproof") {
subproof_179(args, ret, err);
}
if (name == "invent_Path_29_negation_subproof") {
subproof_180(args, ret, err);
}
if (name == "invent_Path_29_subproof") {
subproof_181(args, ret, err);
}
if (name == "invent_Path_2_negation_subproof") {
subproof_182(args, ret, err);
}
if (name == "invent_Path_2_subproof") {
subproof_183(args, ret, err);
}
if (name == "invent_Path_30_negation_subproof") {
subproof_184(args, ret, err);
}
if (name == "invent_Path_30_subproof") {
subproof_185(args, ret, err);
}
if (name == "invent_Path_3_negation_subproof") {
subproof_186(args, ret, err);
}
if (name == "invent_Path_3_subproof") {
subproof_187(args, ret, err);
}
if (name == "invent_Path_4_negation_subproof") {
subproof_188(args, ret, err);
}
if (name == "invent_Path_4_subproof") {
subproof_189(args, ret, err);
}
if (name == "invent_Path_5_negation_subproof") {
subproof_190(args, ret, err);
}
if (name == "invent_Path_5_subproof") {
subproof_191(args, ret, err);
}
if (name == "invent_Path_6_negation_subproof") {
subproof_192(args, ret, err);
}
if (name == "invent_Path_6_subproof") {
subproof_193(args, ret, err);
}
if (name == "invent_Path_7_negation_subproof") {
subproof_194(args, ret, err);
}
if (name == "invent_Path_7_subproof") {
subproof_195(args, ret, err);
}
if (name == "invent_Path_8_negation_subproof") {
subproof_196(args, ret, err);
}
if (name == "invent_Path_8_subproof") {
subproof_197(args, ret, err);
}
if (name == "invent_Path_9_negation_subproof") {
subproof_198(args, ret, err);
}
if (name == "invent_Path_9_subproof") {
subproof_199(args, ret, err);
}
}
void subproof_0(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1596),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1596));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_1(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1596),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1596));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1163),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1163));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_3(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1163),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1163));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2177),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2177));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_5(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2177),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2177));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2001),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2001));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_7(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2001),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2001));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(773),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(773));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_9(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(773),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(773));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(874),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(874));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_11(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(874),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(874));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(859),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(859));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_13(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(859),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(859));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(878),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(878));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
return;
}
void subproof_15(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(878),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(878));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1600),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1600));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_17(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1600),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1600));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1425),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1425));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_19(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1425),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1425));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1125),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1125));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_21(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1125),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1125));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1905),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1905));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_1(Tuple<RamDomain,4>({{(args)[1],0,0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
ret.push_back(0);
err.push_back(true);
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
}
return;
}
void subproof_23(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1905),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1905));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1689),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1689));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_25(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1689),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1689));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1866),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1866));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_27(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1866),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1866));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1335),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1335));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_29(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1335),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1335));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1436),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1436));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_31(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1436),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1436));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1065),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1065));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_33(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1065),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1065));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1166),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1166));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_35(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1166),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1166));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1360),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1360));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_37(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1360),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1360));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1972),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1972));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_2(Tuple<RamDomain,4>({{0,(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_39(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1972),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1972));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1930),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1930));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_41(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1930),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1930));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1797),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1797));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
}
return;
}
void subproof_43(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1797),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1797));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1893),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1893));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
void subproof_45(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1893),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1893));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1058),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1058));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_47(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1058),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1058));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1717),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1717));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_49(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1717),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1717));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1159),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1159));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_51(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1159),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1159));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1599),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1599));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_53(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1599),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1599));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2139),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2139));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_55(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2139),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_2(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2139));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(885),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(885));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
return;
}
void subproof_57(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(885),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(885));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1848),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1848));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_59(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1848),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1848));
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
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1162),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1162));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_61(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1162),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1162));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1658),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1658));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_63(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1658),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1658));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
void subproof_64(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1948),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1948));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
}
return;
}
void subproof_65(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1948),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1948));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1813),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1813));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_67(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1813),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1813));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1071),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1071));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_69(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1071),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1071));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1842),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1842));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_71(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1842),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1842));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1204),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1204));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_73(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1204),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1204));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1096),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1096));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_75(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1096),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1096));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2184),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2184));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_77(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2184),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2184));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(740),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(740));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_2(Tuple<RamDomain,4>({{0,(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(0);
err.push_back(true);
ret.push_back((args)[0]);
err.push_back(false);
}
return;
}
void subproof_79(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(740),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(740));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1571),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1571));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_81(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1571),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1571));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1587),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1587));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_83(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1587),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1587));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1712),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1712));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_85(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1712),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[0],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1712));
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
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
void subproof_86(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1714),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1714));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_87(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1714),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1714));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(699),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(699));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
void subproof_89(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(699),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(699));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(823),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(823));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_91(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(823),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(823));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1338),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1338));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_93(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1338),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1338));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(994),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(994));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_95(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(994),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(994));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(684),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(684));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
void subproof_97(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(684),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(684));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2015),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2015));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_99(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2015),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2015));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(854),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(854));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_101(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(854),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(854));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1336),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1336));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_103(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1336),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1336));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1143),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1143));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_105(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1143),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1143));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(985),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(985));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_107(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(985),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(985));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
void subproof_108(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1992),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1992));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_109(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1992),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1992));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(733),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(733));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
return;
}
void subproof_111(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(733),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(733));
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
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1075),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1075));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_113(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1075),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1075));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1783),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1783));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_115(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1783),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1783));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1540),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1540));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_117(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1540),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1540));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1951),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1951));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_119(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1951),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1951));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(914),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(914));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_121(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(914),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(914));
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
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1771),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1771));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_123(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1771),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1771));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1734),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1734));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_125(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1734),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1734));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
void subproof_126(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1695),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1695));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_127(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1695),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1695));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2019),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2019));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_129(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2019),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2019));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
void subproof_130(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1741),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1741));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
void subproof_131(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1741),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1741));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(2243),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(2243));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
if(((((((!(rel_2_Rule->empty())) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(2243),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_6_SCC->equalRange_1(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(2243));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1933),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1933));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_135(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1933),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env1[1],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1933));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(1791),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(1791));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
if(!rel_6_SCC->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_6_SCC_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_137(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_6_SCC->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
CREATE_OP_CONTEXT(rel_6_SCC_op_ctxt,rel_6_SCC->createContext());
const Tuple<RamDomain,3> key({{RamDomain(1791),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_6_SCC->equalRange_3(key,READ_OP_CONTEXT(rel_6_SCC_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(1791));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(692),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(692));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
return;
}
void subproof_139(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(692),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(692));
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(188),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(188));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_141(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(188),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(188));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
void subproof_142(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(607),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(607));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_1(Tuple<RamDomain,4>({{(args)[1],0,0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
ret.push_back(0);
err.push_back(true);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
return;
}
void subproof_143(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(607),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(607));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(142),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(142));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_145(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(142),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(142));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
void subproof_146(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(69),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(69));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_147(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(69),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(69));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(483),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(483));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_149(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(483),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(483));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(592),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(592));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_151(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(592),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(592));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(48),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(48));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_1(Tuple<RamDomain,4>({{(args)[0],0,0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
ret.push_back(0);
err.push_back(true);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
}
return;
}
void subproof_153(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(48),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(48));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(214),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(214));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_155(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(214),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(214));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(73),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(73));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_157(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(73),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(73));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(23),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(23));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
void subproof_159(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(23),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(23));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(238),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(238));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_161(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(238),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(238));
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
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(187),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(187));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_163(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(187),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(187));
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
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(106),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(106));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_165(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(106),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(106));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(178),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(178));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_167(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(178),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(178));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
void subproof_168(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(184),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(184));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_169(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(184),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(184));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(603),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(603));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_171(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(603),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(603));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(207),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(207));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_173(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(207),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(207));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(297),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(297));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_175(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(297),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(297));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(176),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(176));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_177(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(176),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(176));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(53),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(53));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_179(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(53),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],env2[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(53));
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
ret.push_back(env2[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
void subproof_180(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(512),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(512));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_181(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(512),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],0,0,0}});
auto range = rel_3_invent_Path->equalRange_1(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[1],env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(512));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(0),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
return;
}
void subproof_183(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(0),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
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
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(210),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(210));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_1(Tuple<RamDomain,4>({{(args)[0],0,0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
ret.push_back(0);
err.push_back(true);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
}
return;
}
void subproof_185(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(210),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(210));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(456),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(456));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_187(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(456),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(456));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env3[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(77),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(77));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_189(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(77),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],env1[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env2[0],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(77));
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
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(99),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(99));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[1],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_191(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(99),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],(args)[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(99));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(202),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(202));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
return;
}
void subproof_193(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(202),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_2(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(202));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(174),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(174));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
void subproof_195(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(174),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],(args)[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(174));
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
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(525),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(525));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
if(!rel_3_invent_Path->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_197(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) && (!(rel_3_invent_Path->empty())))) {
{
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
CREATE_OP_CONTEXT(rel_3_invent_Path_op_ctxt,rel_3_invent_Path->createContext());
const Tuple<RamDomain,3> key({{RamDomain(525),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],(args)[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{0,env1[1],0,0}});
auto range = rel_3_invent_Path->equalRange_2(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env2[0],0,0}});
auto range = rel_3_invent_Path->equalRange_3(key,READ_OP_CONTEXT(rel_3_invent_Path_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(525));
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
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env2[0]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
if(!rel_2_Rule->equalRange_1(Tuple<RamDomain,3>({{RamDomain(123),0,0}}),READ_OP_CONTEXT(rel_2_Rule_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(0));
err.push_back(false);
}
}
{
std::lock_guard<std::mutex> guard(lock);
ret.push_back(0);
err.push_back(true);
ret.push_back(RamDomain(123));
err.push_back(false);
}
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[0],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[2],(args)[0],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
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
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
if(!rel_1_Edge->equalRange_3(Tuple<RamDomain,4>({{(args)[1],(args)[2],0,0}}),READ_OP_CONTEXT(rel_1_Edge_op_ctxt)).empty()) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(3));
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
void subproof_199(const std::vector<RamDomain>& args, std::vector<RamDomain>& ret, std::vector<bool>& err) {
std::mutex lock;
if(((((((!(rel_2_Rule->empty())) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) && (!(rel_1_Edge->empty())))) {
{
CREATE_OP_CONTEXT(rel_1_Edge_op_ctxt,rel_1_Edge->createContext());
CREATE_OP_CONTEXT(rel_2_Rule_op_ctxt,rel_2_Rule->createContext());
const Tuple<RamDomain,3> key({{RamDomain(123),0,0}});
auto range = rel_2_Rule->equalRange_1(key,READ_OP_CONTEXT(rel_2_Rule_op_ctxt));
for(const auto& env0 : range) {
if( ((env0[2]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[0],0,0,0}});
auto range = rel_1_Edge->equalRange_1(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env1 : range) {
if( ((env1[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{env1[1],env1[0],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env2 : range) {
if( ((env2[3]) < ((args)[2]))) {
const Tuple<RamDomain,4> key({{(args)[1],env1[1],0,0}});
auto range = rel_1_Edge->equalRange_3(key,READ_OP_CONTEXT(rel_1_Edge_op_ctxt));
for(const auto& env3 : range) {
if( ((env3[3]) < ((args)[2]))) {
std::lock_guard<std::mutex> guard(lock);
ret.push_back(RamDomain(123));
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
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back(env1[1]);
err.push_back(false);
ret.push_back(env3[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back(env1[0]);
err.push_back(false);
ret.push_back((args)[0]);
err.push_back(false);
ret.push_back(env3[0]);
err.push_back(false);
ret.push_back((args)[1]);
err.push_back(false);
ret.push_back(env0[2]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env1[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env2[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
ret.push_back(env3[3]);
err.push_back(false);
ret.push_back((args)[2]);
err.push_back(false);
}
}
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
