
#include "datalog.h"
#include "template.h"
#include "query.h"
#include "extern.h"
#include "defns.h"
#include "config.hpp"

#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <z3++.h>
#include <ctime>
#include <chrono>
#include <cstdlib>



namespace ALPS {

int DatalogProgram::programCt = 0;
    
typedef std::map<int,int> PII;

namespace {

    const Configuration& Config = Configuration::getConfig();

    
bool check_proof(const IClause& g, const IClause& s, const PII& relMap, const PII& varMap) {

	if(g.cl_hd.pRel != s.cl_hd.pRel) {
		std::cout << "head relation does not match: g=" << g.cl_hd.pRel
				<< ", s=" << g.cl_hd.pRel << std::endl;
		return false;
	}

	/*
	for(auto pr : relMap) {
		// incorrect
		if( g.cl_body[pr.first].pRel != s.cl_body[pr.second].pRel){
			std::cout <<pr.first << "-th predicate name does not match " << pr.second << "-th \n";
			return false;
		}
	}*/

	// as variable order directly check

	// varMap seems unnecessary, as IClause does not change var orders from TClause
	// but generalization really matter on variable names, e.g. v2 -> v1


	// first map variable names, then check if the body is a strict subset of the other


	bool matched = false;
	const size_t g_sz = g.cl_body.size();
	const size_t s_sz = s.cl_body.size();
	for(int i=0; i < g_sz; ++i) {
		const TRelation& g_t = g.cl_body[i];

		matched = false;
		for(int j=0; j < s_sz; ++j) {
			const TRelation& s_t = s.cl_body[j];
			if(g_t.pRel != s_t.pRel) {
				continue;
			}


			int arity = s_t.getArity();
			int k = 0;
			while(k < arity){
				int g_var = g.tc.vbody[i].vdom[k];
				int s_var = s.tc.vbody[j].vdom[k];

				auto it = varMap.find(g_var);
				if(it == varMap.end() || it->second != s_var){
					break;
				}
				++k;
			}

			if(k == arity){
				matched = true;
				break;
			}
		}

		if(!matched) {
			//std::cout<<"i=" <<i << ", cannot find a match for " << g_t.getRelNameWithTypes() << std::endl;
			break;
		}
	}


	return matched;
}

void chooseK_exact_helper(int nth, int k, const std::vector<int>& elements, std::vector<std::set<int>>& res, std::set<int>& cur) {
    
    if(k<0 || nth < k || nth > elements.size()){
        return;
    }
    
    if(k == 0) {
        res.push_back(cur);
        return;
    }
    
    const int e = elements[nth-1];
    
    // choose nth
    cur.insert(e);
    chooseK_exact_helper(nth-1, k-1, elements, res, cur);
    cur.erase(e);
    
    
    // don't choose nth
    chooseK_exact_helper(nth-1, k, elements, res, cur);
}
    
std::vector<std::set<int>> chooseK_helper(int n, int i, const std::vector<int>& v) {
	std::vector<std::set<int>> res;

	if(n > v.size()){
		return res;
	}

	if (i == 0 || n == 0) {
		res.push_back( std::set<int>() );
		return res;
	}

	auto encode = [&v](int x) {return v[x-1];};

	// choose n
	std::vector<std::set<int>> tmp1 = chooseK_helper(n-1, i-1, v);
	for(std::set<int>& x : tmp1) {
		x.insert( encode(n) );
		res.push_back( std::move(x) );
	}

	// don't choose n
	std::vector<std::set<int>> tmp2 = chooseK_helper(n-1, i, v);
	for(std::set<int>& x : tmp2) {
		res.push_back( std::move(x) );
	}

	return res;
}
 
    
    void gen_combinations(const int K, int leftSum, int leftBox, std::vector< std::vector<int> >& configs, std::vector<int>&cur)
    {
        if(leftSum < leftBox) {
            return;
        }

        if(leftBox == 0) {
            configs.push_back(cur);
            return;
        }
        
        for(int number = 1; number <= K; ++number) {
            cur.push_back(number);
            gen_combinations(K, leftSum - number, leftBox - 1, configs, cur);
            cur.pop_back();
        }
    }

    
    void deduplication_I(std::vector<IClause>& candidate) {
        // deduplicate instantiated rules
        const int sz = (int) candidate.size();
        std::map< std::pair<Relation,int>, std::set<int>> rel_sz_map;
        for(int i=0;i<sz;++i) {
            const IClause& ic = candidate[i];
            std::pair<Relation,int> key = std::make_pair(ic.cl_hd.getRel(), (int)ic.cl_body.size());
            rel_sz_map[ key ].insert(i);
        }
        
        std::set<int> erase;
        for(auto& pr : rel_sz_map) {
            //const std::pair<Relation,int>& key = pr.first;
            auto it1 = pr.second.begin();
            auto end = pr.second.end();
            while(it1 != end) {
                if(erase.find(*it1) != erase.end()) {
                    break;
                }
                
                auto it2 = it1;
                ++it2;
                while(it2 != end) {
                    const IClause& ic1 = candidate[*it1];
                    const IClause& ic2 = candidate[*it2];
                    
                    if(ic1.equivalentTo(ic2)) {
                        erase.insert(*it2);
                    }
                    ++it2;
                }
                ++it1;
            }
        }
        
        std::vector<IClause> icv;
        for(int i=0;i< sz; ++i) {
            if(erase.find(i) != erase.end()) {
                continue;
            }
            icv.push_back( std::move(candidate[i]) );
        }
        std::swap(icv, candidate);
    }
    
    void deduplication(std::vector<TClause>& candidate) {
        std::set<int> erase;
        
        const size_t sz = candidate.size();
        for(int i=0;i< sz; ++i) {
            if(erase.find(i) != erase.end()) {
                continue;
            }
            
            const TClause& ta = candidate[i];
            for(int j=i+1; j < sz; ++j) {
                const TClause& tb = candidate[j];
                
                std::map<int,int> relMap;
                std::map<int,int> varMap;
                if(ta.moreGeneralThan(tb, relMap, varMap)) {
                    std::map<int,int> relMap2;
                    std::map<int,int> varMap2;
                    if(tb.moreGeneralThan(ta, relMap2, varMap2)) {
                        if(ta.vbody.size() == tb.vbody.size()) {
                            // now very very likely ta === tb
                            erase.insert(j);
                        }
                    }
                }
            }
        }
        
        std::vector<TClause> cv;
        for(int i=0;i< sz; ++i) {
            if(erase.find(i) != erase.end()) {
                continue;
            }
            cv.push_back( std::move(candidate[i]) );
        }
        std::swap(cv, candidate);
    }
    
    std::vector<std::pair<int,int>> findPivots(const TRelation& r1, const TRelation& r2) {
        std::vector<std::pair<int,int>> res;
        // find the pivot
        for(int i=0; i<r1.getArity(); ++i) {
            for(int j=0;j<r2.getArity();++j) {
                if(r1.getType(i) != r2.getType(j)) {
                    continue;
                }
                res.push_back(std::make_pair(i,j));
            }
        }
        
        return res;
    }

    std::vector<TClause> enumerateProjections(const TRelation& target,
                                              const std::vector<TypeInfo> types,
                                              const std::vector<TPredicate> & vbody) {
        std::vector<TClause> res;
        const int target_arity = target.getArity();
        const int m = (int) types.size();
        std::vector<int> indexes(m);
        
        int ct = 1;
        for(int i=0;i<m;++i) {
            indexes[i] = i;
            ct *= i + 1;
        }
        
        while(ct > 0) {
            for(int i=0; i < m; ++i) {
                if(types[ indexes[i] ] != target.getType(i)) {
                    break;
                }
                if( i >= target_arity - 1) {
                    // create head predicate variable
                    TPredicate head;
                    head.pid = 0;
                    head.arity = target_arity;
                    head.vdom.clear();
                    for(int j=0; j< head.arity; ++j) {
                        head.vdom.push_back( indexes[j] );
                    }
                    
                    TClause tc;
                    tc.hd = std::move(head);
                    tc.vbody = vbody;
                    
                    res.push_back(std::move(tc));
                    
                    break;
                }
            }
            
            std::vector<int> copy = indexes;
            bool update = false;
            while(!update && ct > 0) {
                --ct;
                std::next_permutation(indexes.begin(), indexes.end());
                
                for(int i=0;i < target_arity; ++i) {
                    if(copy[i] != indexes[i]) {
                        update = true;
                        break;
                    }
                }
            } // end of inner while loop
            
        } // end of permutation while loop
        
        return res;
    }
    
    
    TClause createChainK(int K) {
        TClause chainK;
        chainK.hd.pid = 0;
        chainK.hd.arity = 2;
        chainK.hd.vdom = {0, K};
        
        for(int i=0;i<K;++i) {
            TPredicate b;
            b.pid = i+1;
            b.arity = 2;
            b.vdom = {i, i+1};
            chainK.vbody.push_back(std::move(b));
        }
        
        return chainK;
    }
    
    
    std::vector<TClause> all_permutations(const TClause& T) {
        const int K = (int) T.vbody.size();
        
        std::vector<int> index(K);
        int ct = 1;
        for(int i=0;i<K;++i){
            index[i] = i;
            ct *= (i + 1);
        }
        
        std::vector<TClause> res;
        while(--ct >=0) {
            TClause tmp;
            tmp.hd = T.hd;
            for (int i = 0; i < T.vbody.size(); i++) {
                tmp.vbody.push_back(T.vbody[index[i]]);
            }
            /*for(const auto & p : chainK.vbody) {
             tmp.vbody.push_back(p);
             }*/
            res.push_back(std::move(tmp));
            std::next_permutation(index.begin(), index.end());
        }
        return res;
    }
    
    std::vector<TClause> createChainK_with_permutation(int K) {
        TClause T = createChainK(K);
        return all_permutations(T);
    }

    
    bool isUsefulChain(const TClause& tc) {
        // TODO: incorporate a few heuristics
        // 1) if head arity > 1, then its variables should refere different relations
        // 2) usually, the head variable does not refer the binding variable used in body [not sure for dev_set_062]
        

        //return true;
        
        if(tc.hd.arity > 1) {
            std::set<int> head_variables;
            for(int x : tc.hd.vdom) {
                head_variables.insert(x);
            }
            int index = 0;
            for(auto & v : tc.vbody) {
                ++index;
                bool ok = false;
                for(int x : v.vdom) {
                    if(head_variables.find(x) != head_variables.end()) {
                        ok = true;
                        break;
                    }
                }
                if(!ok) {
                    // for chain-3, assume the middle one is the pivot
                    if(tc.vbody.size() == 3 && index == 2){
                        continue;
                    }
                    return false;
                }
            }
        }

        return true;
    }

    
    int editDistance(const std::vector<int>& vA, const std::vector<int>& vB) {
        if(vA.size() > 10 || vB.size() > 10) {
            std::cerr << "Error: too many varaibles are invovled" << std::endl;
        }
        
        int dp[11][11];
        for(int i=0;i<11;++i) {
            dp[0][i] = i;
            dp[i][0] = i;
        }
        
        for(int i=1; i<= vA.size(); ++i) {
            for(int j=1; j<=vB.size(); ++j) {
                if(vA[i-1] == vB[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = 1 + std::min(dp[i-1][j], dp[i][j-1]);
                    
                    // introduce replace operation
                    if(dp[i][j] > dp[i-1][j-1] + 1) {
                        dp[i][j] = dp[i-1][j-1] + 1;
                    }
                }
            }
        }
        
        /*
        std::cout << "vA: ";
        for(auto x : vA) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "vB: ";
        for(auto x : vB) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "distance: " <<dp[ vA.size() ][ vB.size() ] << std::endl;
        */
        
        return dp[ vA.size() ][ vB.size() ];
    }

    int editDistance(const TClause& tA, const TClause& tB, std::map<int,int>& var_map) {
        int res = 0;
        std::vector<int> tmp_v;
        std::transform(tA.hd.vdom.begin(), tA.hd.vdom.end(), std::back_inserter(tmp_v), [&var_map](int x){return var_map[x];} );
        res += editDistance(tmp_v, tB.hd.vdom);
        
        const int sz = (int) tA.vbody.size();
        for(int j=0;j<sz; ++j) {
            const TPredicate& b = tA.vbody[j];
            tmp_v.clear();
            std::transform(b.vdom.begin(), b.vdom.end(), std::back_inserter(tmp_v), [&var_map](int x){return var_map[x];} );
            res += editDistance(tmp_v, tB.vbody[j].vdom);
        }

        return res;
    }
    
    int countCommonElements(const std::vector<int>& vA,const std::vector<int>& vB) {
        std::set<int> stA(vA.begin(),vA.end());
        std::set<int> stB(vB.begin(),vB.end());
        int ct = 0;
        for(auto x : stA) {
            if(stB.find(x) != stB.end()) {
                ++ct;
            }
        }

        return ct;
    }
    
    int graphMatchingDistance(const TClause& tA, const TClause& tB, std::map<int,int>& var_map) {
        // ignore ordering, maxium cost bipartitie matching or minimum cost perfect matching
        // max{sum(arity)}  - max cost matching
        int res = 0;
        
        std::vector<int> tmp_v;
        std::transform(tA.hd.vdom.begin(), tA.hd.vdom.end(), std::back_inserter(tmp_v), [&var_map](int x){return var_map[x];} );
        res += countCommonElements(tmp_v, tB.hd.vdom);
        
        //std::cout << "matching-1: " << res << std::endl;
        
        const int sz = (int) tA.vbody.size();
        for(int j=0;j<sz; ++j) {
            const TPredicate& b = tA.vbody[j];
            tmp_v.clear();
            std::transform(b.vdom.begin(), b.vdom.end(), std::back_inserter(tmp_v), [&var_map](int x){return var_map[x];} );
            res += countCommonElements(tmp_v, tB.vbody[j].vdom);
            //std::cout << "matching-2-" << j <<": " << res << std::endl;
        }
        
        int sum_arity_a = tA.hd.arity;
        for(const auto& T : tA.vbody) {
            sum_arity_a += T.arity;
        }
        
        int sum_arity_b = tB.hd.arity;
        for(const auto& T : tB.vbody) {
            sum_arity_b+= T.arity;
        }
        
        //std::cout << "matchings: " << res << std::endl;
        
        //res = std::max(sum_arity_a, sum_arity_b) - res;
        
        res = sum_arity_a + sum_arity_b - 2 * res;
        
        /*
        if(sz == 3) {
            //std::cout << "tA: " << tA.toStr() << std::endl;
            //std::cout << "tB: " << tB.toStr() << std::endl;
            //std::cout << "var_map: " << std::endl;
            //for(auto& pr : var_map) {
            //    std::cout << pr.first << " --> " << pr.second << std::endl;
            //}
            if(res == 3) {
                std::cout << "sum_arity_a = " << sum_arity_a << ", sum_arity_b = " << sum_arity_b << std::endl;
                int x = 0;
            }
        }*/

        return res;
    }

    
    bool editDistanceWithinK_helper3 (int K, const std::vector<int>& from, int i,
                                      const std::vector<int>& to, int j,  int var_map[11]) {
        
        /*
        std::cout << "K=" << K << ", i=" <<i << ", j=" << j << std::endl;
        std::cout << "from: ";
        for(auto x : from) std::cout <<x <<" ";
        std::cout << std::endl;
        
        std::cout << "to: ";
        for(auto x : to) std::cout <<x <<" ";
        std::cout << std::endl;
        
        std::cout << "var_map: \n";
        for(int i=0;i<11;++i) {
            std::cout << i << " -> " << var_map[i] << std::endl;
        }
        */

        int dbg = 0;

        

        if(K < 0) {
            dbg = 0;
            return false;
        }
        
        if(i >= from.size()) {
            dbg = 0;
            return K  >= ((int)to.size() - j);
        }

        if(j >= to.size()) {
             dbg = 0;
            return K  >= ((int)from.size() - i);
        }

        if(from[i] < 0 || to[j] < 0) {
            if(from[i] >= 0) {
                return editDistanceWithinK_helper3(K-1, from, i+1, to, j, var_map);
            }
            if(to[j] >= 0) {
                return editDistanceWithinK_helper3(K-1, from, i, to, j+1, var_map);
            }

            if(from[i] != to[j]) {
                std::cout << "Warn: this should not happen in editDistanceWithinK_helper3" << std::endl;
                
                 std::cout << "K=" << K << ", i=" <<i << ", j=" << j << std::endl;
                 std::cout << "from: ";
                 for(auto x : from) std::cout <<x <<" ";
                 std::cout << std::endl;
                 
                 std::cout << "to: ";
                 for(auto x : to) std::cout <<x <<" ";
                 std::cout << std::endl;
                 
                 std::cout << "var_map: \n";
                 for(int i=0;i<11;++i) {
                 std::cout << i << " -> " << var_map[i] << std::endl;
                 }
                 
                return false;
            }
            else{
                return editDistanceWithinK_helper3(K, from, i+1, to, j+1, var_map);
            }
        }
        
        int x = var_map[ from[i] ];
        if(x != -1) {
            // already be mapped to some variable

            if(x == to[j]) {
                return editDistanceWithinK_helper3(K, from, i+1, to, j+1, var_map);
            }
            else{
                if(editDistanceWithinK_helper3(K-1, from, i+1, to, j+1, var_map)) {
                    return true;
                }
                if(editDistanceWithinK_helper3(K-1, from, i, to, j+1, var_map)) {
                    return true;
                }
                if(editDistanceWithinK_helper3(K-1, from, i+1, to, j, var_map)) {
                    return true;
                }
            }
        }
        else {
            // not mapped yet
            {
                bool used = false;
                for(int i=0;i<11;++i) {
                    if(var_map[i] == to[j]) {
                        used = true;
                        break;
                    }
                }
                if(!used){
                    // make a change on map
                    var_map[ from[i] ] = to[j];
                    if(editDistanceWithinK_helper3(K, from, i+1, to, j+1, var_map)) {
                        return true;
                    }
                    // restore
                    var_map[ from[i] ] = -1;
                }
            }
            
            {
                // do not make change on map
                if(editDistanceWithinK_helper3(K-1, from, i+1, to, j+1, var_map)) {
                    return true;
                }
                if(editDistanceWithinK_helper3(K-1, from, i, to, j+1, var_map)) {
                    return true;
                }
                if(editDistanceWithinK_helper3(K-1, from, i+1, to, j, var_map)) {
                    return true;
                }
            }
        }
        
        return false;
    }

    bool editDistanceWithinK_helper(const std::vector<TPredicate>& vA, const std::vector<TPredicate>& vB, int K) {
        
        std::vector<int> v1;
        for(int i=0; i<vA.size(); ++i) {
            for(auto x : vA[i].vdom) {
                v1.push_back(x);
            }
            v1.push_back(-1-i);
        }

        std::vector<int> v2;
        for(int i=0; i<vB.size(); ++i) {
            for(auto x : vB[i].vdom) {
                v2.push_back(x);
            }
            v2.push_back(-1-i);
        }
        
        int var_map[11];
        for(int i=0;i<11;++i) var_map[i] = -1;
        
        bool res = editDistanceWithinK_helper3(K, v1, 0, v2, 0, var_map);
        return res;
    }
    
    bool editDistanceWithinK (const TClause& tA, const TClause& tB, int K) {
        if(tA.vbody.size() != tB.vbody.size()) {
            std::cout <<"Warn(augmentationDistanceWithinK): body have different sizes, incomparable" << std::endl;
            return false;
        }

        std::set<int> varsA;
        for(auto x: tA.hd.vdom) varsA.insert(x);
        for(auto & t : tA.vbody) {
            for(auto x: t.vdom) {
                varsA.insert(x);
            }
        }
        if(varsA.size() > 10) {
            std::cout << "Error: the number of variables are too much!!" << std::endl;
            return false;
        }

        
        std::vector<TPredicate> va;
        va.push_back(tA.hd);
        for(const auto &t : tA.vbody) {
            va.push_back(t);
        }
        
        std::vector<TPredicate> vb;
        vb.push_back(tB.hd);
        for(const auto &t : tB.vbody) {
            vb.push_back(t);
        }
        
        return editDistanceWithinK_helper(va,vb,K);
    }

    int augmentationDistance_maybe_fast(const TClause& tA, const TClause& tB) {
        int l = 0;
        int r = 15;
        while(l < r) {
            int mid = (l+r)/2;
            bool test = editDistanceWithinK(tA, tB, mid);
            if(test) {
                r = mid;
            }
            else {
                l = mid + 1;
            }
        }
        return l;
    }
    
    int augmentationDistance(const TClause& tA, const TClause& tB) {
        int sum = 1 << 30;

        if(tA.vbody.size() != tB.vbody.size()) {
            std::cout <<"Warn(augmentationDistance): body have different sizes, incomparable" << std::endl;
            return sum;
        }
        
        // enumerate all mappings then compute edit distance
        
        std::set<int> varsA;
        for(auto & x : tA.hd.vdom) varsA.insert(x);
        for(auto & b : tA.vbody) for(int x : b.vdom) varsA.insert(x);

        std::set<int> varsB;
        for(auto & x : tB.hd.vdom) varsB.insert(x);
        for(auto & b : tB.vbody) for(int x : b.vdom) varsB.insert(x);
        
        //if(varsA.size() > 6 || varsB.size() > 6) {
        //    return 1<<30;
        //}
        
        if(varsA.size() > varsB.size()) {
            return augmentationDistance(tB, tA);
        }

        
        // varsA.size <= varsB.size
        std::vector<int> vB(varsB.begin(),varsB.end());
        std::vector<int> indexes;
        int ct = 1;
        for(int i=0;i<vB.size();++i) {
            indexes.push_back(i);
            ct *= i + 1;
        }
        
        while(--ct >= 0) {
            std::map<int,int> var_map;
            int i = 0;
            for(auto x: varsA) {
                var_map[x] = vB[ indexes[i++] ];
            }

            int tmp_sum;
            if (Config.enableGraphDistance) {
                tmp_sum = graphMatchingDistance(tA, tB, var_map);  // use graph matching metric
            } else {
                tmp_sum = editDistance(tA, tB, var_map);
            }
            
            sum = std::min(sum, tmp_sum);

            std::next_permutation(indexes.begin(), indexes.end());
        }
        
        return sum;
    }
    
    
    void showDistanceStats(const std::vector<TClause> & Ts){
        
        std::cout << "=== distance stats ===" << std::endl;
        std::cout << "Number of Templates: " << Ts.size() << std::endl;
        
        for(int K = 1; K <= 3; ++K) {
            //TClause chainK = createChainK(K);
            auto chainKs = createChainK_with_permutation(K);
            
            int ct = 0;
            std::map<int,int> stats;
            for(auto & t :  Ts) {
                if(t.vbody.size() == K) {
                    ++ ct;
                    //int dist = augmentationDistance(chainK, t);
                    int dist = 100;
                    for(auto& ch : chainKs){
                        int tmp = augmentationDistance_maybe_fast(ch,t);
                        dist = std::min(tmp, dist);
                    }
                    ++stats[dist];
                }
            }
            
            std::cout << "Number of chain-" << K << " like templates: " << ct << std::endl;
            for(auto& pr : stats) {
                std::cout << "dis: " << pr.first << ", count: " << pr.second << std::endl;
            }
        }
    }


} // end of anonymous namespace

std::set<int> IDBTR::extractRules(const std::set<int>& tmpls) const {
	std::set<int> res;
	for (const int x : tmpls) {
		auto it = tmpl2rules.find(x);
		if(it == tmpl2rules.end()) {
			continue;
		}

		for (const int e : it->second) {
			res.insert(e);
		}
	}

	std::cout << "extractRules, tmpls.size = " << tmpls.size() << ", res.size=" << res.size() << std::endl;

	return res;
}

// assume tm, rules  are already given
// initialize tmpl2rules, mostG, mostS
void IDBTR::init(){
	const size_t num_rules = rules.size();
	const size_t num_tmpls = tm.templates.size();

	// initialize tmpl2rules
	tmpl2rules.clear();

	for(int i=0; i < num_rules; ++i) {
		const IClause& cl = rules[i];
		int j = (int)( std::find(tm.templates.begin(), tm.templates.end(), cl.tc) - tm.templates.begin() );
		if(j < num_tmpls) {
			tmpl2rules[j].insert(i);
		}
		else {
			std::cerr << "ERROR: IDBTR::int() cannot find template " << cl.tc.toStr() << " in tm\n";
		}
	}

	// initialize mostG/S
	//mostG.clear();
	//mostG.insert( extractRules(tm.getMostGeneral()) );
	//mostS.clear();
	//mostS.insert( extractRules(tm.getMostSpecific()) );

}

std::set<int> IDBTR::generalize(int rule_index) const{
	std::set<int> res;
	const IClause& cl = rules[rule_index];
	const TClause& tc = cl.tc;
	const int ti = tm.indexOf(tc);

	if(ti < 0) {
		std::cerr << "ERRPR: IDBTR::generalize cannot find template " << tc.toStr() << std::endl;
		return res;
	}

	auto it_tmpls = tm.specific_po.find(ti);
	if (it_tmpls == tm.specific_po.end() || it_tmpls->second.empty()) {
		return res;
	}

	const std::set<int>& tmpls = it_tmpls->second;
	for(int t : tmpls) {
		auto it_proof = tm.general_proof.find(t);
		if(it_proof == tm.general_proof.end()) {
			std::cerr << "ERROR: IDBTR::generalize specific_po exists, but no proof" << std::endl;
			return res;
		}

		const std::map<int, std::pair<PII, PII>> & proof = it_proof->second;
		auto it = proof.find(ti);
		if (it == proof.end()) {
			std::cerr << "ERROR: IDBTR::generalize cannot find a proof between "
					<< tm.templates[t].toStr()  << "  and  " << tc.toStr()
					<< std::endl;
		}
		const std::pair<PII, PII> & pf = it->second;
		const std::map<int, int>& relMap = pf.first;
		const std::map<int, int>& varMap = pf.second;

		auto it2 = tmpl2rules.find(t);
		if (it2 == tmpl2rules.end()) {
			continue;
		}
		for (int r : it2->second) {
			// Later if the refinement becomes unsound
			// try to replace check_proof with explicit theta-subsumption check
			if (check_proof(rules[r], cl, relMap, varMap)) {
				res.insert(r);
			}
		}
	}

	return res;
}

std::set<int> IDBTR::specialize(int rule_index) const{
	std::set<int> res;

	const IClause& cl = rules[rule_index];
	const TClause& tc = cl.tc;
	const int ti = tm.indexOf(tc);

	if(ti < 0) {
		std::cerr << "ERRPR: IDBTR::specialize cannot find template " << tc.toStr() << std::endl;
		return res;
	}

	auto it_tmpls = tm.general_po.find(ti);
	if(it_tmpls == tm.general_po.end() || it_tmpls->second.empty()){
		return res;
	}


	//if(tc.vbody.size() > 1) {
	//	return res;
	//}
	//std::cout << "specialize:\n" << tc.toStr() << std::endl;



	const std::set<int>& tmpls = it_tmpls->second;

	// Note that there could be multiple proofs between two templates
	// Instead of directly using one proof to check general relation between
	// two IClauses, we would better redo theta-sumption bewteen them.
	auto it_proof = tm.general_proof.find(ti);
	if(it_proof == tm.general_proof.end()) {
		std::cerr << "ERROR: IDBTR::specialize templates are not empty, but no proof" << std::endl;
		return res;
	}

	const std::map<int, std::pair<PII,PII>> & proof = it_proof->second;

	for(int t : tmpls) {
		auto it = proof.find(t);
		if(it == proof.end()) {
			std::cerr << "ERROR: IDBTR::specialize cannot find a proof between "
					<< tc.toStr() << "  and  " << tm.templates[t].toStr()
					<< std::endl;
		}
		const std::pair<PII,PII> & pf = it->second;
		const std::map<int,int>& relMap = pf.first;
		const std::map<int,int>& varMap = pf.second;


		auto it2 = tmpl2rules.find(t);
		if(it2 == tmpl2rules.end()){
			continue;
		}

		for(int r : it2->second) {
			// Later if the refinement becomes unsound
			// try to replace check_proof with explicit theta-subsumption check

			//std::cout << "test...\n";
			//std::cout << "    " << cl.toStr() << std::endl;
			//std::cout << "    " << rules[r].toStr() << std::endl;


			if(check_proof(cl, rules[r], relMap, varMap)) {

				//std::cout << "IDBTR::specialize, Partial order between two IClauses\n";
				//std::cout << cl.toStr() << std::endl;
				//std::cout << rules[r].toStr() << std::endl;
				res.insert(r);
			}
		}
	}

	return res;
}

std::vector< std::set<int> > IDBTR::chooseK_exact(const int k, ChooseOption option) const {
    
    std::set<int> st;
    
    if(GENERAL == option) {
        st = extractRules( tm.getMostGeneral() );
    }
    else if(SPECIFIC == option){
        st = extractRules( tm.getMostSpecific() );
    }
    else if(ALL == option){
        size_t sz = tm.templates.size();
        std::set<int> tmpls;
        for(int i=0;i < sz; ++i) {
            tmpls.insert(i);
        }
        
        st = extractRules(tmpls);
    }
    else{
        std::cout <<"Error(IDBTR::chooseK_exact) unknown option "<< option << std::endl;
    }

    std::vector< std::set<int> > res;
    if(k <= st.size()) {
        std::vector<int> elements(st.begin(), st.end());
        std::set<int> cur;
        chooseK_exact_helper( (int)elements.size(), k, elements, res, cur);
        std::cout << "\n#elements: " << elements.size() << " K = " << k << ", res.size: " << res.size() << "\n";
        
        
//        std::cout << "elements: { ";
//        for(int x : elements) {
//            std::cout << x << ", ";
//        }
//        std::cout << "} \n";
//
//        std::cout << "res.size = " << res.size() << "\n";
//        for(auto st : res) {
//            std::cout << "{ ";
//            for(int x : st) {
//                std::cout << x << ", ";
//            }
//            std::cout << "} \n";
//        }
        
        
    }
    
    
    return res;
}

std::vector<std::set<int>> IDBTR::chooseK(int k, ChooseOption option) const {
	if(k > 5) {
		std::vector<std::set<int>> res;
		std::cerr << "K might be too large: " << k << std::endl;
		//return res;
	}

	std::set<int> st;

	if(GENERAL == option) {
		st = extractRules( tm.getMostGeneral() );
	}
	else if(SPECIFIC == option){
		st = extractRules( tm.getMostSpecific() );
	}
	else if(ALL == option){
		size_t sz = tm.templates.size();
		std::set<int> tmpls;
		for(int i=0;i < sz; ++i) {
			tmpls.insert(i);
		}

		st = extractRules(tmpls);
	}
	else{
		std::cout <<"Error(IDBTR::chooseK) unknown option "<< option << std::endl;
	}

	std::cout << "chooseK (K=" << k <<") in " << rel.getRelNameWithTypes()
    << ", st.size = " << st.size() <<std::endl;

	std::vector<int> v(st.begin(), st.end());

	return chooseK_helper( (int) v.size(), k, v);
}


void DPManager::fillIDBValues() {
	int query_space = 0;
	int true_labels = 0;

	for(const IDBTR& x : idbRules){
		const TRelation& tr = x.rel;

		std::set<std::vector<int>> st;

		Relation rel = tr.pRel;
		Tuple* tp = rel->Pos;
		int ct = 0;
		while (*tp) {
			++ct;

			std::vector<int> v;
			for (int j = 1; j <= rel->Arity; ++j) {
				v.push_back( (int) (*tp)[j]);
			}

			st.insert(std::move(v));

			++tp;
		}


		IDBValue iv(tr);
		iv.pos = std::move(st);

		idbValues.push_back(std::move(iv));

		int space = 1;
		for(int i=1; i <= rel->Arity; ++i) {
			TypeInfo ti = rel->TypeRef[i];
			space *= ti->NValues;
		}

		std::cout << "query_space for " << rel->Name << ": " << space << std::endl;
		std::cout << "true_label for " << rel->Name << ": " << ct << std::endl;
		query_space += space;
		true_labels += ct;
	}

	std::cout << "overall_query_space: " << query_space << std::endl;
	std::cout << "overall_true_label: " << true_labels << std::endl;
}
    
    void DPManager::exploreProjection(const TRelation& target, std::vector<TClause>& candidates) {
        
        std::cout << "explore projection for target: " << target.getRelNameWithTypes() << std::endl;
        
        std::vector<TRelation> rels;
        for(const TRelation& r : M.relm.vEDBRel) rels.push_back(r);
        for(const TRelation& r : M.relm.vIDBRel) rels.push_back(r);

        
        const int target_arity = target.getArity();
        for(const TRelation& r : rels) {
            if(target_arity > r.getArity()) {
                continue;
            }
            
            // as the arity is fairly small, let's simply try all enumerations: O( arity! )
            std::vector<TypeInfo> types;
            TPredicate b;
            b.arity = r.getArity();
            b.pid = 1;
            
            for(int i=0;i<r.getArity();++i) {
                types.push_back(r.getType(i));
                b.vdom.push_back(i);
            }

            std::vector<TPredicate> vbody;
            vbody.push_back(std::move(b));
            
            
            for(auto& x : enumerateProjections(target, types, vbody)) {
                int dis = editDistance(x.hd.vdom, x.vbody[0].vdom);
                if(dis > 3) {
                    // usually projection is either a copy or slightly vary variable order
                    std::cout <<"dis=" << dis << ", skip projection: "<< x.toStr() << std::endl;
                    continue;
                }
                candidates.push_back(std::move(x));
            }
        }
    }

    void DPManager::addFilter2(std::vector<TClause>& candidates) {
        bool has_filter = false;
        for(const TRelation& r : M.relm.vEDBRel) {
            if(r.getArity() == 2) {
                has_filter = true;
                break;
            }
        }
        if(!has_filter) {
            std::cout << "no EDB can be used as a filter" << std::endl;
            return;
        }

        std::vector<TClause> res;
        for(const TClause& tc : candidates) {
            if(tc.vbody.size() > 1) {
                continue;
            }
            const TPredicate& p = tc.vbody[0];
            for(int i=0;i<p.arity;++i) {
                for(int j=0;j<p.arity;++j) {
                    if(i==j) {
                        continue;
                    }
                    TClause tmp;
                    tmp.hd = tc.hd;
                    tmp.vbody.push_back(p);
                    TPredicate b2;
                    b2.pid = 2;
                    b2.arity = 2;
                    b2.vdom = {i,j};
                    tmp.vbody.push_back(std::move(b2));
                    res.push_back( std::move(tmp) );
                }
            }
        }
        
        for(auto & t : res) {
            candidates.push_back( std::move(t));
        }
    }
    
    void DPManager::addFilter(std::vector<TClause>& candidates) {
        bool has_filter = false;
        for(const TRelation& r : M.relm.vEDBRel) {
            if(r.getArity() == 1) {
                has_filter = true;
                break;
            }
        }
        for(const TRelation& r : M.relm.vIDBRel) {
            if(r.getArity() == 1) {
                has_filter = true;
                break;
            }
        }
        if(!has_filter) {
            std::cout << "no EDB can be used as a filter" << std::endl;
            return;
        }
        
        const int sz = (int)candidates.size();
        for(int i=0; i<sz; ++i) {
            int ct = 0;
            std::set<int> existing_filter;
            for(const auto& x : candidates[i].vbody) {
                if( x.arity > 1) ++ct;
                if( x.arity == 1) {
                    existing_filter.insert( x.vdom[0] );
                }
            }
            
            
            if(ct >=1 && ct <= 2) {
                const TClause& templ_0 = candidates[i];

                std::cout << "try to extend with a filter for template: " << templ_0.toStr() << std::endl;
                // filter some dimention
                int j = 0;
                while(j < templ_0.vbody.size()) {
                    if(templ_0.vbody[j].arity > 1) {
                        break;
                    }
                    ++j;
                }
                const int arity = templ_0.vbody[j].arity;
                for(int k=0; k < arity; ++k) {
                    const TClause& templ = candidates[i];
                    if( existing_filter.find(templ.vbody[j].vdom[k]) != existing_filter.end() ) {
                        continue;
                    }
                    
                    TClause templ_filter = templ;
                    TPredicate filter;
                    filter.pid = (int) templ.vbody.size() + 1;
                    filter.arity = 1;
                    filter.vdom.push_back( templ.vbody[j].vdom[k]);
                    
                    templ_filter.vbody.push_back(std::move(filter));
                    
                    std::cout << "add filter template: " << templ_filter.toStr() << std::endl;
                    candidates.push_back( std::move(templ_filter) );
                    
                    // at this point, candidates get updated, the original reference to its element may become ineffect
                    // std::cout << "templ: " << templ.toStr() << std::endl;
                }
            }
        }
    }

    
    void DPManager::addNewBindingInHead(std::vector<TClause>& candidates) {
        // currently, only introduce new binding in the head
        
        const int sz = (int)candidates.size();
        for(int i=0; i<sz; ++i) {

            const int arity = candidates[i].hd.arity;
            std::cout << "add new binding for template: " << candidates[i].toStr() << std::endl;

            for(const int v : candidates[i].hd.vdom) {
                for(int j=0; j<arity; ++j) {
                    int x = candidates[i].hd.vdom[j];
                    if(x == v) {
                        continue;
                    }
                    // essential do the following things at the same time:
                    // 1) break its original binding with some variable in the body
                    // 2) bind it to another variable in head
                    TClause copy = candidates[i];
                    copy.hd.vdom[j] = v;
                    
                    std::cout << "new binding in head: " << copy.toStr() << std::endl;
                    candidates.push_back(std::move(copy));
                    
                }
            }
        }
    }
    
    
    void DPManager::addNewBindingInBody(std::vector<TClause>& candidates) {
        const int sz = (int)candidates.size();
        for(int i=0; i<sz; ++i) {
            std::set< std::pair<int,int> > vis;
            
            // compute binding stats
            std::map<int,int> var_cnt;
            for(auto x: candidates[i].hd.vdom) {
                ++var_cnt[x];
            }
            for(auto& v: candidates[i].vbody) {
                for(auto x: v.vdom) {
                    ++var_cnt[x];
                }
            }
            
            // add a binding in the body
            const int sz = (int) candidates[i].vbody.size();
            for(int j=0; j<sz; ++j) {
                // we need a copy here, because as long as candidates get updated,
                // any reference may be come ineffective thus avoid using reference
                TPredicate b_copy = candidates[i].vbody[j];
                for(int k=0; k<b_copy.vdom.size(); ++k) {
                    int x = b_copy.vdom[k];
                    if(var_cnt[x] > 1) {
                        // skip, the new binding should involve at least one fresh variable
                        continue;
                    }
                    
                    // search a variable in the body to bind
                    for(int cj=0; cj<sz; ++cj) {
                        if(cj == j) {
                            // avoid binding to variable in the same predicate
                            continue;
                        }
                        const int arity = (int) candidates[i].vbody[cj].arity;
                        for(int ck = 0;ck<arity;++ck) {
                            const int y = candidates[i].vbody[cj].vdom[ck];
                            if(var_cnt[y] > 2) {
                                // already too many bindings, skip
                                continue;
                            }
                            
                            TClause tc_copy = candidates[i];
                            tc_copy.vbody[j].vdom[k] = y;
                            candidates.push_back(std::move(tc_copy));
                        } // enumerate the dom to finish binding
                        
                    } // enumerate predicate in body
                    
                } // enumerate fresh dom to start binding
                
            } // enumerate predicate in body
            
        } // enumerate candidate templates
    }

    
    void DPManager::exploreChain2(const TRelation& target, std::vector<TClause>& candidates) {
        std::vector<TRelation> rels;
        
        for(const TRelation& r : M.relm.vEDBRel) rels.push_back(r);
        for(const TRelation& r : M.relm.vIDBRel) {
            // property of SQL
            if(target.getRel() == r.getRel()) {
                //continue;
            }

            rels.push_back(r);
        }
        
        // create a chain-2 used to compare distance
        const TClause chain2 = createChainK(2);

        const int sz = (int) rels.size();
        for(int ri=0;ri<sz;++ri) {
            const TRelation& r1 = rels[ri];
            
            for(int rj=ri;rj<sz;++rj) {
                const TRelation& r2 = rels[rj];
                
                // find the pivot
                for(auto& p : findPivots(r1,r2)) {
                    int i = p.first;
                    int j = p.second;
                    
                    //std::cout <<"try r1: "<< r1.getRelNameWithTypes() << ", r2: "<< r2.getRelNameWithTypes() << std::endl;
                    TPredicate  b1, b2;
                    
                    b1.pid = 1;
                    b1.arity = r1.getArity();
                    b1.vdom.clear();
                    for(int k=0;k<b1.arity;++k) b1.vdom.push_back(k);
                    
                    b2.pid = 2;
                    b2.arity = r2.getArity();
                    b2.vdom.clear();
                    for(int k=0;k<b2.arity;++k) {
                        if(k<j) {
                            b2.vdom.push_back(k + b1.arity);
                        }
                        if(k  == j) {
                            b2.vdom.push_back( b1.vdom[i] );
                        }
                        if(k > j) {
                            b2.vdom.push_back(k + b1.arity - 1);
                        }
                    }
                    
                    
                    // similar to projection, try all possible enumerations
                    const int m = b1.arity + b2.arity - 1;
                    
                    std::vector<TypeInfo> types;
                    for(int k=0;k<b1.arity;++k) {
                        types.push_back( r1.getType(k) );
                    }
                    for(int k=0;k<b2.arity;++k) {
                        if(types.size() == b2.vdom[k]) {
                            types.push_back( r2.getType(k) );
                        }
                    }
                    
                    if(m != types.size()) {
                        std::cerr << "Error: assertion does not hold, some types may be missing or redandunt" << std::endl;
                        std::cerr << "m = " << m << ", types.size = " << types.size() << std::endl;
                    }
                    
                    std::vector<TPredicate> vbody;
                    vbody.push_back(std::move(b1));
                    vbody.push_back(std::move(b2));
                    
                    for (auto & x : enumerateProjections(target, types, vbody) ){
                        if(isUsefulChain(x)) {
                            candidates.push_back(std::move(x));
                        }
                    }
                }

            } // enumerate r2
            
        } // enumerate r1
        
    }
    
    
    std::vector<TClause> chain3_helper(const TRelation& target, const TRelation& r1, const TRelation& r2, const TRelation& r3) {
        std::vector<TClause> res;
        
        for(auto& pr1 : findPivots(r1, r2)){
            for(auto & pr2 : findPivots(r2, r3)) {
                if(pr1.second == pr2.first) {
                    continue;
                }
                
                std::vector<TypeInfo> types;
                
                TPredicate b1;
                b1.pid = 1;
                b1.arity = r1.getArity();
                b1.vdom.clear();
                for(int i=0;i<b1.arity;++i) {
                    b1.vdom.push_back(i);
                    types.push_back( r1.getType(i) );
                }
                
                TPredicate b2;
                b2.pid = 2;
                b2.arity = r2.getArity();
                b2.vdom.clear();
                for(int i=0;i<b2.arity;++i) {
                    if(i < pr1.second) {
                        b2.vdom.push_back( b1.arity + i);
                        types.push_back( r2.getType(i) );
                    }
                    else if(i == pr1.second) {
                        b2.vdom.push_back( b1.vdom[pr1.first] );
                    }
                    else {
                        b2.vdom.push_back( b1.arity - 1 + i);
                        types.push_back( r2.getType(i) );
                    }
                }
                
                TPredicate b3;
                b3.pid = 3;
                b3.arity = r3.getArity();
                b3.vdom.clear();
                for(int i=0;i<b3.arity;++i) {
                    if(i < pr2.second) {
                        b3.vdom.push_back( b1.arity + b2.arity - 1 + i);
                        types.push_back( r3.getType(i) );
                    }
                    else if(i == pr2.second) {
                        b3.vdom.push_back( b2.vdom[pr2.first] );
                    }
                    else {
                        b3.vdom.push_back( b1.arity + b2.arity - 2 + i);
                        types.push_back( r3.getType(i) );
                    }
                }
                
                std::vector<TPredicate> vbody;
                vbody.push_back(std::move(b1));
                vbody.push_back(std::move(b2));
                vbody.push_back(std::move(b3));
                
                for(auto &x : enumerateProjections(target, types, vbody) ) {
                    res.push_back(std::move(x));
                }
            }
        }
        
        return res;
    }
    
    void DPManager::exploreChain3(const TRelation& target, std::vector<TClause>& candidates) {
        std::vector<TRelation> rels;
        
        for(const TRelation& r : M.relm.vEDBRel) rels.push_back(r);
        for(const TRelation& r : M.relm.vIDBRel) {
            // property of SQL
            if(target.getRel() == r.getRel()) {
                //continue;
            }

            rels.push_back(r);
        }
        
        const int sz = (int) rels.size();
        for(int ri=0; ri<sz; ++ri) {
            const TRelation& r1 = rels[ri];
            
            for(int rj=0; rj<sz; ++rj) {
                const TRelation& r2 = rels[rj];
                
                for(int rk=ri; rk<sz; ++rk) {
                    const TRelation& r3 = rels[rk];
                    
                    for(auto& x: chain3_helper(target, r1, r2, r3)) {
                        if(isUsefulChain(x)) {
                            candidates.push_back(std::move(x));
                        }
                    }
                } // enumerate chain tail
                
            } // enumerate the pivot
            
        } // enumerate chain head
    }
    
    static void compare_templates_to_chain(const std::vector<ALPS::TClause, std::allocator<ALPS::TClause> > &T) {
        std::vector<TClause> T1;
        std::vector<TClause> T2; // 1-object
        std::vector<TClause> T3; // 1-type
        std::vector<TClause> T4; // 1-object-type
        std::vector<TClause> T5; // 2-call-site
        
        std::vector<std::string> names;
        names.push_back("1-call-site");
        names.push_back("1-object");
        names.push_back("1-type");
        names.push_back("1-object-type");
        names.push_back("2-call-site");
        
        int K1 = 4;
        int K2 = 8;
        int K3 = 12;
        int K4 = 17;
        
        {
            int i = 0;
            for(auto t : T) {
                if (i < K1) {
                    T1.push_back(t);
                } else if (i < K2 ) {
                    T2.push_back(t);
                } else if (i < K3) {
                    T3.push_back(t);
                } else if (i < K4) {
                    T4.push_back(t);
                } else {
                    T5.push_back(t);
                }
                i++;
            }
        }
        
        std::vector<std::vector<TClause>> clauses;
        clauses.push_back(T1);
        clauses.push_back(T2);
        clauses.push_back(T3);
        clauses.push_back(T4);
        clauses.push_back(T5);
        
        int index = 0;
        for (auto t : clauses) {
            std::cout << "Examining " << names[index] << " templates" << std::endl;
            int dis = 0;
            for (auto c : t) {
                std::cout << "Examining " << c.toStr() << std::endl;
                int dis_from_chain = augmentationDistance(c, createChainK((int) c.vbody.size()));
                if (dis_from_chain > dis) {
                    dis = dis_from_chain;
                }
            }
            std::cout << "Distance from chain for " << names[index] << " is " << dis << std::endl;
            index++;
        }
        
    }

    static void compare_templates(const std::vector<ALPS::TClause, std::allocator<ALPS::TClause> > &T) {
        TClause chain3 = createChainK(3);
        TClause chain2 = createChainK(2);
        TClause chain1 = createChainK(1);
        
        std::vector<TClause> T1; // 1-call-site
        std::vector<TClause> T2; // 1-object
        std::vector<TClause> T3; // 1-type
        std::vector<TClause> T4; // 1-object-type
        std::vector<TClause> T5; // 2-call-site
        std::vector<TClause> T6; // Whaley
        
        std::vector<std::string> names;
        names.push_back("1-call-site");
        names.push_back("1-object");
        names.push_back("1-type");
        names.push_back("1-object-type");
        names.push_back("2-call-site");
        names.push_back("whaley");
        
        int K1 = 4;
        int K2 = 8;
        int K3 = 12;
        int K4 = 17;
        int K5 = 21;
        
        {
            int i = 0;
            for(auto t : T) {
                if (i < K1) {
                    T1.push_back(t);
                } else if (i < K2 ) {
                    T2.push_back(t);
                } else if (i < K3) {
                    T3.push_back(t);
                } else if (i < K4) {
                    T4.push_back(t);
                } else if (i < K5) {
                    T5.push_back(t);
                } else {
                    T6.push_back(t);
                }
                i++;
            }
        }
        
        std::vector<std::vector<TClause>> clauses;
        clauses.push_back(T1);
        clauses.push_back(T2);
        clauses.push_back(T3);
        clauses.push_back(T4);
        clauses.push_back(T5);
        clauses.push_back(T6);
        
        for (auto& c : clauses) {
            c.push_back(chain3);
            c.push_back(chain2);
            c.push_back(chain1);
        }
        
        int cs1_index = 0;
        for (auto& cs1 : clauses) {
            int cs2_index = 0;
            for (auto& cs2 : clauses) {
                std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                std::cout << "Examining " << names[cs1_index] << " and " << names[cs2_index] << std::endl;
                for(auto & t1 : cs1) {
                    std::cout << "find the closest template for " << t1.toStr() << std::endl;
                    int dis = 1 << 30;
                    int index = 0;
                    for(int j=0; j<cs2.size(); ++j) {
                        int tmp_dis = augmentationDistance(t1, cs2[j]);
                        if (tmp_dis < dis) {
                            dis = tmp_dis;
                            index = j;
                        }
                    }
                    
                    
                    std::cout << "closest template is " << cs2[index].toStr() << " with distance " << dis << std::endl;
                }
                cs2_index++;
                std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
            }
            cs1_index++;
        }
    }
    
void DPManager::exploreCandidateRules() {
	auto calc =[] (long long n, long long m) {
		long long res = 1;
		for(int i=0; i < m; ++i){
			res = res * (n - i) / (i + 1);
		}
		return res;
	};
    
    //compare_templates_to_chain(M.tm.templates);

    for(const TRelation& rel : M.relm.vIDBRel) {
        std::cout << "Relation: " << rel.getRelNameWithTypes( ) << std::endl;
        std::vector<TClause> given_templates = M.tm.findAllPossilbeMatchings(rel);

        std::cout << "Stats of given templates: \n";
        showDistanceStats(given_templates);
        std::cout << "\n\n";
    }
  
	for(const TRelation& rel : M.relm.vIDBRel) {

		std::cout << "Relation: " << rel.getRelNameWithTypes( ) << std::endl;
        
        std::vector<TClause> matched_given_templates = M.tm.findAllPossilbeMatchings(rel);
        
        std::vector<TClause> candidates;
		std::vector<TClause> useful_templates;
		std::vector<IClause> matchings;
        
        {
            // introduce first principle: projections
            if(Config.enableChain1){
                std::cout << "\nbefore explore projection: candidates size: " << candidates.size() << std::endl;
                exploreProjection(rel, candidates);
                std::cout << "after explore projection: candidates size: " << candidates.size() << std::endl;
            }

            
            if(Config.enableChain2) {
                std::cout << "\nbefore explore chain-2: candidates size: " << candidates.size() << std::endl;
                exploreChain2(rel, candidates);
                std::cout << "\nafter explore chain-2: candidates size: " << candidates.size() << std::endl;
            }

            // augment by adding filter
            if(Config.enableFilter1){
                std::cout << "\nbefore add filtering: candidates size: " << candidates.size() << std::endl;
                addFilter(candidates);
                //addFilter(candidates);
                std::cout << "after add filtering: candidates size: " << candidates.size() << std::endl;
            }
            
            if(Config.enableFilter2){
                std::cout << "\nbefore add filtering-2: candidates size: " << candidates.size() << std::endl;
                addFilter2(candidates);
                std::cout << "after add filtering-2: candidates size: " << candidates.size() << std::endl;
            }

            if(Config.enableChain3) {
                std::cout << "\nbefore explore chain-3: candidates size: " << candidates.size() << std::endl;
                exploreChain3(rel, candidates);
                std::cout << "\nafter explore chain-3: candidates size: " << candidates.size() << std::endl;
            }

            if(Config.bindings > 0) {
                int b = Config.bindings;
                while(--b>=0) {
                    std::cout << "\nbefore add new binding in Body: candidates size: " << candidates.size() << std::endl;
                    addNewBindingInBody(candidates);
                    std::cout << "after add new binding in Body: candidates size: " << candidates.size() << std::endl;
                }
            }

            // introduce new binding in head
            if(Config.enableHeadBinding) {
                std::cout << "\nbefore add new binding: candidates size: " << candidates.size() << std::endl;
                addNewBindingInHead(candidates);
                std::cout << "after add new binding: candidates size: " << candidates.size() << std::endl;
            }
            
            
            // include given templates
            for (auto& t : matched_given_templates) {
                candidates.push_back(t);
            }
            
            std::cout << "\nbefore filtering by augmentation: candidates size: " << candidates.size() << std::endl;
            
            std::vector<TClause> bases;
            for(int ci = 1; ci<=3;++ci) {
                for(auto& t : createChainK_with_permutation(ci)) {
                    bases.push_back( std::move(t) );
                }
            }
            
            for(auto& t : M.tm.templates) {
                for(auto & t2 : all_permutations(t)) {
                    bases.push_back( std::move(t2) );
                }
            }
            
            std::vector<TClause> filterByK;
            for(auto & t : candidates) {
                int sz = (int) t.vbody.size();

                bool isWithin = false;
                for (auto& b : bases) {
                    if(b.vbody.size() != sz) {
                        continue;
                    }
                    
                    if (Config.enableGraphDistance) {
                        if (editDistanceWithinK(b,t, Config.augmentations + 1)) {
                            if( augmentationDistance(b, t) <= Config.augmentations){
                                isWithin = true;
                                break;
                            }
                        }
                    } else {
                        if (editDistanceWithinK(b, t, Config.augmentations)) {
                            isWithin = true;
                            break;
                        }
                    }
                }
                
                if(!isWithin) {
                    
                    if(t.vbody.size() == 3) {
                        int ct_one = 0;
                        for(auto& x : t.vbody){
                            if(x.arity == 1) {
                                ++ct_one;
                            }
                        }
                        if(ct_one == 1) {
                            for(auto& b : createChainK_with_permutation(3)) {
                                std::cout << b.toStr() << std::endl;
                                int dis1 = augmentationDistance_maybe_fast(t, b);
                                int dis2 = augmentationDistance_maybe_fast(b, t);
                                std::cout <<"dis1: " << dis1 << ", dis2: " << dis2 << std::endl;
                            }
                            std::cout << "will remove: " << t.toStr() <<  std::endl;
                            ct_one = 0;
                        }
                    }
                    
                    continue;
                }
                
                /*int dis = augmentationDistance(chain[sz], t);
                for(auto& t2 : given_templates) {
                    if (t.vbody.size() != t2.vbody.size()) {
                        continue;
                    }
                    int tmp_dis = augmentationDistance(t2, t);
                    dis = std::min(dis, tmp_dis);
                }
                
                if(dis > 2) {
                    continue;
                }*/
                filterByK.push_back(std::move(t));
            }
            
            std::swap(filterByK, candidates);
            std::cout << "\nafter filtering: candidates size: " << candidates.size() << std::endl;
            
            //for(auto & t : candidates) {
            //    std::cout << t.toStr() << std::endl;
            //}
            
            for(auto & ta : matched_given_templates) {
                std::cout << "check matched given template: " << ta.toStr() << std::endl;
                
                bool find = false;
                for(auto& tb : candidates) {
                    if(ta.vbody.size() != tb.vbody.size()) {
                        continue;
                    }
                    if(editDistanceWithinK(ta, tb, 0)) {
                        std::cout << "a potential match: " << tb.toStr() << std::endl;
                        find = true;
                    }
                }
                
                if(!find) {
                    std::cout << "given template cannot find a match with generated ones" << std::endl;
                }
                
            }
            
            
            {
                // collect distance stats
                // std::cout << "Stats of generated templates: \n";
                // showDistanceStats(candidates);
            }
            
            // before run deduplication, eliminate templates which cannot be instantiated
            if(candidates.size() > 2000) {
                //M.findMatchingsWithTemplate(rel, tc);

            }

            std::cout << "before deduplication, candidates size: " << candidates.size() << std::endl;
            deduplication(candidates);
            std::cout << "after deduplication, candidates size: " << candidates.size() << std::endl;
            
            {
                // output some template examples
                std::cout << "100 examples of candidates: \n";
                for(int i=0;i<candidates.size();++i) {
                    if(i == 50 && candidates.size() > 100) {
                        i = (int)candidates.size() - 50;
                    }
                    std::cout << candidates[i].toStr() << std::endl;
                }
            }
            
            std::cout << std::endl;
        }
        
        

		long long sum = 0;

		for(const TClause& tc : candidates) {
			std::vector<IClause> Ms = M.findMatchingsWithTemplate(rel, tc);
			sum += Ms.size();

            int useful_match = 0;
			for(IClause& m : Ms) {
				if(m.is_useless()) {
					std::cout << "skip useless rule: " << m.toStr() << std::endl;
					continue;
				}
                ++useful_match;
				matchings.push_back( std::move(m) );
			}
            
            if(useful_match > 0) {
                std::cout << ">> Template: " << tc.toStr() << ",  matches: " << useful_match << std::endl;
                useful_templates.push_back(tc);
            }
		}

        std::cout << "before deduplicate rules, matching size: " <<  matchings.size() << std::endl;
        deduplication_I(matchings);
        std::cout << "after deduplicate rules, matching size: " <<  matchings.size() << std::endl;

        std::cout << "\nnumber of instantiated rules: " << matchings.size() << std::endl;
        std::cout << "all matchings : " << std::endl;
        int i=0;
        for(auto& m : matchings) {
            std::cout << i << ", " << m.toStr(false) << std::endl;
            ++i;
        }
        

		TemplateManager tempM;
		tempM.templates = std::move(useful_templates);
		tempM.buildPartialOrder();

		std::cout << "overall templates: " << tempM.templates.size() << std::endl;
		std::cout << "most general: " << tempM.getMostGeneral().size() << std::endl;
		std::cout << "most specific: " << tempM.getMostSpecific().size() << std::endl;
		std::cout << "independent: " << tempM.getIndependent().size() << std::endl;

		//tempM.logPO2dot( "//Users/xujie/git/ALPS/" + rel.getRelName() + ".dot" );

		IDBTR idb(rel);
		idb.tm = std::move(tempM);
		idb.rules = std::move(matchings);
		idb.init();

		idbRules.push_back( std::move(idb) );
      
        std::string name = idb.rel.getRelName();
        if(name.find("invent_") == 0) {
          invent_idbs.insert( (int)idbRules.size() - 1);
        }
      
	}

}

std::vector<DatalogProgram> DPManager::refineProg(const DatalogProgram& prog, bool specialize) {
	std::vector<DatalogProgram> res;

	for(auto pr : prog.state) {
		int idb_index = pr.first;
		const IDBTR & idb = idbRules[idb_index];

		const std::set<int>& rule_st = pr.second;

		// specialize one rule
		for(int rl : rule_st) {
			// try all candidates for one rule
			std::set<int> candidates = specialize ? idb.specialize(rl) : idb.generalize(rl);
			for(int can : candidates) {
				std::set<int> cp_st = rule_st;
				// NOTE: erase one then insert one,
				// #rules for an IDB does not change
				cp_st.erase(rl);
				cp_st.insert(can);

				std::map<int, std::set<int>> cp_state = prog.state;
				cp_state[idb_index] = std::move(cp_st);

				DatalogProgram dp(this);
				dp.state = std::move(cp_state);

				if(! hash_and_record(dp) ){
					// already existed, skip
					continue;
				}

				// NOTE: this insertion happens in three layer nested loops, could explode!!
				//res.insert( std::move(dp) );
				res.push_back( std::move(dp) );
			}
		}
	}

	return res;
}


std::vector<DatalogProgram> DPManager::refineProgWithTarget(const DatalogProgram& prog, bool specialize, int idb_index) {
	std::vector<DatalogProgram> res;
	std::set<int> refine_st = backwardAnalysis(prog, idb_index);

	const int DEPTH = -1;

	if(DEPTH > 0 && refine_st.size() >= DEPTH) {return res;}
	/*
	std::cout <<"\n\n"<< str(prog);
	std::cout << "after backward analysis from " << idb_index << std::endl;
	std::copy(refine_st.begin(), refine_st.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;
	*/

	for(auto pr : prog.state) {
		int idb_index = pr.first;
		if(refine_st.find(idb_index) == refine_st.end()) {
			continue;
		}

		const IDBTR & idb = idbRules[idb_index];

		const std::set<int>& rule_st = pr.second;

		// specialize one rule
		for(int rl : rule_st) {
			// try all candidates for one rule
			std::set<int> candidates = specialize ? idb.specialize(rl) : idb.generalize(rl);
			for(int can : candidates) {
				std::set<int> cp_st = rule_st;
				// NOTE: erase one then insert one,
				// #rules for an IDB does not change
				cp_st.erase(rl);
				cp_st.insert(can);

				std::map<int, std::set<int>> cp_state = prog.state;
				cp_state[idb_index] = std::move(cp_st);

				DatalogProgram dp(this);
				dp.state = std::move(cp_state);

				if (DEPTH > 0) {
					bool pass = true;
					for (auto pr : dp.state) {
						int index = pr.first;
						std::set<int> s = backwardAnalysis(prog, index);
						if (s.size() >= DEPTH) {
							pass = false;
							break;
						}
					}
					if (!pass) {
						continue;
					}
				}


				if(! pass_filters(dp) ){
					// fail to pass filters, skip
					continue;
				}

				// NOTE: this insertion happens in three layer nested loops, could explode!!
				//res.insert( std::move(dp) );
				res.push_back( std::move(dp) );
			}
            
            
            //if(dbg_track.count(prog.prog_id)){
            //    int x = 0 ;
            //}
            
            if(specialize) {
                // ideal specialization should EITHER erase the current rule
                // OR replace it with the whole set of specialized rules,
                // which correspond to the most "general" specialization
                std::set<int> cp_st = rule_st;
                cp_st.erase(rl);

                //for(int can : candidates) {
                //    cp_st.insert(can);
                //}

                // try any two rules (a simple hack for pts_type)
                // TODO(make it general)
                std::set< std::pair<int,int> > new_candidates;
                for(int c1 : candidates) {
                    for(int c2 : candidates) {
                        if(c1 < c2) {
                            new_candidates.insert(std::make_pair(c1, c2));
                        }
                    }
                }
                
                for(auto & pr : new_candidates) {
                    std::set<int> cp_st = rule_st;
                    
                    cp_st.erase(rl);
                    cp_st.insert(pr.first);
                    cp_st.insert(pr.second);

                    std::map<int, std::set<int>> cp_state = prog.state;
                    cp_state[idb_index] = std::move(cp_st);
                    
                    
                    DatalogProgram dp(this);
                    dp.state = std::move(cp_state);
                    
                    if(pass_filters(dp) ){
                        res.push_back( std::move(dp) );
                    }
                }
            }
		}

	}

	return res;
}

std::set<int> DPManager::backwardAnalysis(const DatalogProgram& prog, int idb_index) const {
	std::set<int> st;

	size_t prev_size = 0;
	st.insert(idb_index);
	while(prev_size < st.size()){
		prev_size = st.size();
		std::set<int> tmp_st;

		for(int x : st) {
			auto it = prog.state.find(x);
			if(it == prog.state.end() || it->second.empty()){
				continue;
			}

			const std::vector<IClause>& rules = idbRules[x].rules;
			for(int r_index : it->second) {
				const IClause& cl = rules[r_index];
				for(const TRelation& trel : cl.cl_body){
					int k = findIDBIndex(trel.pRel);
					if(k>=0){
						tmp_st.insert(k);
					}
				}
			}
		}

		for(int x : tmp_st){
			st.insert(x);
		}
	}

	return st;
}

void DPManager::init_SingleRulePrograms(){
    const size_t sz = idbRules.size();
    for(int i=0; i<sz; ++i) {
        const IDBTR& idb = idbRules[i];
        std::vector<std::set<int>>  vst = idb.chooseK(1, ALL);
        
        for(auto& st : vst) {
            if(st.empty()) {
                continue;
            }
            
            DatalogProgram dp (this);
            std::map<int, std::set<int>> state;
            state[i] = st;
            dp.state = std::move(state);
            SingleRulePrograms.push_back(std::move(dp));
        }
    }

}

DatalogProgram DPManager::add_rule(DatalogProgram& prog, std::pair<int,int> r) {
    DatalogProgram new_prog (this);
    std::map<int, std::set<int>> state = prog.state;
    state[r.first].insert(r.second);
    new_prog.state = std::move(state);
    
    return new_prog;
}

    
    void DPManager::init_helper_efficient(ChooseOption option) {
        std::vector< std::vector<int> > configs;
        std::vector< int > cur;
        
        const int number_of_idbs = (int) idbRules.size();
        gen_combinations(Config.K, Config.MaxRules, number_of_idbs, configs, cur);
        
        std::cout << "over estimated configs : " << configs.size() << "\n";
        
        std::chrono::steady_clock::time_point init_helper_efficient_begin = std::chrono::steady_clock::now();
        long long longest_run = 0;
        int max_threads = 0;
        
        for(auto& conf : configs) {

            std::vector< std::vector< std::set<int> > > VVS;
            for(int i=0; i < number_of_idbs; ++i) {
                const IDBTR& idb = idbRules[i];
                const int num_rules = conf[i];

                // TODO: consider to handle invented predicates special requirement
                
                std::vector<std::set<int>>  vst = idb.chooseK_exact(num_rules, option);
                VVS.push_back(std::move(vst));
            }
            
            long long ct = 1;
            std::cout << "Config: {";
            for(int i=0; i < number_of_idbs; ++i) {
                const IDBTR& idb = idbRules[i];
                std::cout << conf[i] << " " << idb.rel.getRelNameWithTypes() << ", ";

                ct *= VVS[i].size();
            }
            std::cout << "},  number of programs: " << ct << "\n";
            
            max_threads += ct;
            for(int p=0; p < ct; ++p) {
                DatalogProgram dp (this);
                std::map<int, std::set<int>> state;
                
                std::chrono::steady_clock::time_point _b = std::chrono::steady_clock::now();

                
                int k = p;
                for(int i = 0; i < number_of_idbs; ++i) {
                    int j = k % VVS[i].size();
                    state [i] = VVS[i][j];
                    
                    k = k / VVS[i].size();
                }
                
                dp.state = std::move(state);
                
                if(! pass_filters(dp)) {
                    //std::cout << "cannot pass filter:\n";
                    //std::cout << str(dp) << "\n";
                    continue;
                }
                
                if(GENERAL == option) {
                    //Gs.insert(std::move(dp));
                    Gs.push_back( std::move(dp) );
                }
                else if(SPECIFIC == option){
                    //Ss.insert(std::move(dp));
                    Ss.push_back( std::move(dp) );
                }
                else if(ALL == option) {
                    // use Gs for baseline data
                    Gs.push_back( std::move(dp) );
                }
                else {
                    std::cout << "Error (init_helper_efficient): unknown option: " << option << std::endl;
                }
                
                std::chrono::steady_clock::time_point _e = std::chrono::steady_clock::now();
                long long t = std::chrono::duration_cast<std::chrono::milliseconds>(_e - _b).count();
                if(longest_run < t) {
                    longest_run = t;
                }

            }
        }
        
        std::chrono::steady_clock::time_point init_helper_efficient_end = std::chrono::steady_clock::now();
        std::cout << "(Time_Measure) init_helper_efficient takes "
        << std::chrono::duration_cast<std::chrono::milliseconds>(init_helper_efficient_end - init_helper_efficient_begin).count()
        << " ms, longest_run: "<< longest_run <<" max_threads: " << max_threads <<"\n";

    }
    
void DPManager::init_helper(ChooseOption option) {
	std::vector< std::vector< std::set<int> > > VVS;

	long long space = 1;
	const size_t sz = idbRules.size();
	for(int i=0; i<sz; ++i) {
		const IDBTR& idb = idbRules[i];
        std::vector<std::set<int>>  vst;
        
        if(invent_idbs.find(i) != invent_idbs.end()) {
            vst = idb.chooseK(1, option); // 2 for scc, 1 for buildwall
        }
        else{
            vst = idb.chooseK(Config.K, option);
        }

		auto it = vst.begin();
		while(it != vst.end()){
			if(it->empty()) {
				it = vst.erase(it);
			}
			else{
				++it;
			}
		}
        
        //idb.rel.getRelName();

		space *= vst.size();
		VVS.push_back( std::move(vst) );
	}

	std::cout << "space: " << space << std::endl;

	for(int p = 0; p < space; ++p) {
		DatalogProgram dp (this);
		std::map<int, std::set<int>> state;

		int k = p;
		for(int i = 0; i < sz; ++i) {
			int j = k % VVS[i].size();
			state [i] = VVS[i][j];

			k = k / VVS[i].size();
		}

		dp.state = std::move(state);

		if(! pass_filters(dp)) {
            //std::cout << "cannot pass filter:\n";
            //std::cout << str(dp) << "\n";
			continue;
		}

		if(GENERAL == option) {
			//Gs.insert(std::move(dp));
			Gs.push_back( std::move(dp) );
		}
		else if(SPECIFIC == option){
			//Ss.insert(std::move(dp));
			Ss.push_back( std::move(dp) );
		}
		else if(ALL == option) {
			// use Gs for baseline data
			Gs.push_back( std::move(dp) );
		}
		else {
			std::cout << "Error (init_helper): unknown option: " << option << std::endl;
		}
	}

}

void DPManager::initGSX() {
	if(Config.enableG){
		//init_helper(GENERAL);
        init_helper_efficient(GENERAL);
		std::cout << "Gs.size = " << Gs.size() << std::endl;
        //for(auto& x : Gs) {
        //    std::cout << str(x) << "\n\n";
        //}
	}

	if(Config.enableS) {
        //init_helper(SPECIFIC);
        init_helper_efficient(SPECIFIC);
		std::cout << "Ss.size = " << Ss.size() << std::endl;
	}

	if(Config.enableX) {
        //init_helper(ALL);
        init_helper_efficient(ALL);
		std::cout << "Gs.size = " << Gs.size() << std::endl;
	}
	//execute( *Gs.begin() );
}

std::vector<ConcreteRule> DPManager::getConcreteRules(const DatalogProgram& dp) {
	std::vector<ConcreteRule> res;

	for(auto pr : dp.state) {
		int idb_index = pr.first;
		const IDBTR & idb = idbRules[idb_index];

		for(auto r : pr.second) {
			res.push_back( idb.rules[r].zip() );
		}
	}

	return res;
}



std::string DPManager::str(const DatalogProgram& dp, bool withTemplate) {
	std::stringstream ss;
	for(auto pr : dp.state) {
		int idb_index = pr.first;
		const IDBTR & idb = idbRules[idb_index];

		for(auto r : pr.second) {
			ss << idb.rules[r].toStr(withTemplate) << std::endl;
		}
	}

	return ss.str();
}

int DPManager::findIDBIndex(Relation r) const {
	const size_t n = idbRules.size();
	for(int i=0; i < n; ++i) {
		const IDBTR& idb = idbRules[i];
		if(r == idb.rel.pRel) {
			return i;
		}
	}

	return -1;
}

bool DPManager::may_derive_something(const DatalogProgram& x) const {
	std::map<int, std::vector< std::set<int> > > status;
	std::set<int> tasks;
	for(auto pr : x.state) {
		const int idb_index = pr.first;
		tasks.insert(idb_index);
		status[idb_index ] = get_dependents(x, idb_index);
	}

	std::set<int> resolved;
	size_t sz = tasks.size() + 1;
	while(sz > tasks.size()) {
		sz = tasks.size();

		for(auto pr : status) {
			const int idb_index = pr.first;
			if(resolved.find(idb_index) != resolved.end()) {
				continue;
			}
			for(auto st : pr.second){
				bool suc = true;
				for(int x : st) {
					if(resolved.find(x) == resolved.end()) {
						suc = false;
					}
				}
				if(suc) {
					resolved.insert(idb_index);
					tasks.erase(idb_index);
					break;
				}
			}
		}
	}

	return tasks.size() == 0;
}

std::vector< std::set<int> > DPManager::get_dependents(const DatalogProgram& prog, int idb_index) const {
	std::vector< std::set<int> > res;

	auto it = prog.state.find(idb_index);
	if(it == prog.state.end() || it->second.empty()) {
		return res;
	}
	const IDBTR& idb_tr = idbRules[idb_index];
	for(int r : it->second) {
		std::set<int> st;

		const IClause& cl = idb_tr.rules[r];
		for(const TRelation& rel : cl.cl_body) {
			if(rel.isIDB()) {
				st.insert( findIDBIndex(rel.pRel) );
			}
		}

		res.push_back(st);
	}

	return res;
}

bool DPManager::hash_and_record(const DatalogProgram& x){
	//std::string s = str(x, false);
    
    std::ostringstream ss;
    for(auto & pr : x.state) {
        if(pr.second.empty()) {
            continue;
        }
        ss << pr.first << "{";
        for(auto x : pr.second) {
            ss << x << ",";
        }
        ss << "}";
    }
    std::string s = ss.str();
    
    
	long long h = str_hash( s );
	auto it = visited.find(h);
	if(it == visited.end()) {
		//visited.insert( std::make_pair(h, s) );
		visited[h].insert(s);
	}
	else{
		// find the key, now check if there is a collision
		auto it2 = it->second.find(s);
		if(it2 == it->second.end()) {
			it->second.insert(s);
		}
		else{
			// already existsed
        return false;
		}
	}

	return true;
}

bool DPManager::total_rules_too_large(const DatalogProgram& dp) const {
	int ct = 0;
	for(const auto& x : dp.state) {
		ct += x.second.size();
	}
	return ct > Config.MaxRules || ct > Config.K * idbRules.size();
}


bool DPManager::pass_filters(const DatalogProgram& dp) {
    
	//if(Config.enableX) {
	//	return true;
	//}

    if(total_rules_too_large(dp)) {
        // too many rules, ignore
        return false;
    }

    if(! hash_and_record(dp) ){
        // already existed, skip
        return false;
    }
    
	if(! may_derive_something(dp)) {
		// if we cannot derive anything for some idb, skip
		//std::cout << "ignore: fail to derive certain idb\n" << str(dp) << std::endl;
		
        // here, the following heuristic does not work on one sql benchmark
        return false;
	}

	return true;
}

bool IDBValue::ask_and_update(std::vector<int>& v) {
	auto it = pos.find(v);

	if(it == pos.end()) {
		asked_neg.insert(v);
		return false;
	}
	else{
		asked_pos.insert(v);
		return true;
	}
}

bool DPManager::ask(const std::vector<int>& Q) {
	const int idb_index = Q[0];
	std::vector<int> tp(Q.begin()+1, Q.end());

	return idbValues[idb_index].ask_and_update(tp);
}

void DPManager::test_specialize() {

	for(const IDBTR& idb : idbRules ) {
		if(idb.rel.getRelName() == "reptile"){
			const size_t sz = idb.rules.size();
			for(int i=0; i < sz; ++i) {
				idb.specialize(i);
			}
		}
	}

}

DatalogProgram DPManager::expand() {
	DatalogProgram dp(this);

	std::queue< int > Queue;
	std::set< int > vis;
	Queue.push( (int)idbRules.size() - 1 );

	while(Queue.size()) {
		int idb_index = Queue.front();
		Queue.pop();

		if(vis.find(idb_index) != vis.end()){
			continue;
		}
		vis.insert(idb_index);
		const size_t sz = idbRules[idb_index].rules.size();
		for(int i=0; i < sz; ++i){
			dp.state[ idb_index ].insert( i );
		}

		const IDBTR& idb = idbRules[ idb_index ];
		for(const IClause& rule : idb.rules) {
			for(const TRelation& rel : rule.cl_body) {
				if(rel.isIDB()){
					Queue.push( findIDBIndex( rel.pRel ) );
				}
			}
		}
	}


	return dp;
}

void DPManager::examine_each_IDBTR(QueryEngine* pEngine){
    std::chrono::steady_clock::time_point examine_idb_begin = std::chrono::steady_clock::now();
    int max_threads = 0;
    long long longest_run = 0;

    /*
    for(int idb_index = 0; idb_index < idbRules.size(); ++idb_index){
        int i = 0;
        const size_t sz = idbRules[idb_index].rules.size();
        while(i < sz) {
            const IDBTR& idb = idbRules[idb_index];
            const IClause& cl = idb.rules[i];
            std::cout << "i = " << i << std::endl;
            std::cout << "idb_index=" << idb_index << ", idb: " << idb.rel.getRelNameWithTypes() << std::endl;
            std::cout << "clause : " << cl.toStr() << std::endl;
            ++i;
        }
    }*/

	std::set<int> affected_idbs;

	bool update = true;
	while(update){
		update = false;

		// find if some idb rule is useless "semantically"
		const size_t n = idbRules.size();
		for(int idb_index = 0; idb_index < n; ++idb_index){
			int i = 0;
			const size_t sz = idbRules[idb_index].rules.size();
			while(i < sz) {
                
                ++max_threads;
                std::chrono::steady_clock::time_point _b = std::chrono::steady_clock::now();

                
				const IDBTR& idb = idbRules[idb_index];
				const IClause& cl = idb.rules[i];

				//std::cout << "i = " << i << std::endl;
				//std::cout << "idb_index=" << idb_index << ", idb: " << idb.rel.getRelNameWithTypes() << std::endl;
				//std::cout << "clause : " << cl.toStr() << std::endl;


				// add a fakeIDB
				//std::cout <<"create fake IDB ..." << std::endl;
				Relation rel = CreateFakeIDBRel( cl.cl_hd.getArity() );
				TRelation fakeRel( rel );
				//std::cout <<"fakeIDB: " << fakeRel.getRelNameWithTypes() << std::endl;

				IDBTR fakeIDB( fakeRel );
				std::vector<TRelation> body = cl.cl_body;
				IClause fake_cl( cl.tc ,fakeRel, body);
				fakeIDB.rules.push_back( std::move(fake_cl) );

				// this will cause  IDBTR& becomes ineffective, thus crash later
				idbRules.push_back( std::move(fakeIDB) );


				// expand to a program
				DatalogProgram dp = expand();

				//std::cout << "expanded program:"<< std::endl;
				//std::cout << str(dp);

				// setup context
				pEngine->cm_ptr->updateFuncDecls(rel);


				//std::pair<Relation, std::vector<int> > Q;
				//Q.first = rel;
				//Q.second =  cl.tc.hd.vdom;

				z3::expr query = pEngine->construct_query(rel);
				// run engine
				if(pEngine->test(dp, query) == false) {
					//std::cout << "\n\n>>>>test result is false, will erase rule...\n\n" << std::endl;
					idbRules.pop_back();
					break;
				}
				else {
					//std::cout << "\n\n" << cl.toStr() << " seems OK.\n";
					//std::cout << str(dp) ;
				}


				idbRules.pop_back();
				++i;
                
                std::chrono::steady_clock::time_point _e = std::chrono::steady_clock::now();
                long long t = std::chrono::duration_cast<std::chrono::milliseconds>(_e - _b).count();
                if(longest_run < t) {
                    longest_run = t;
                }

			}

			if(i < sz) {
				IDBTR& idb = idbRules[idb_index];
				affected_idbs.insert(idb_index);

				//for(IClause & x : idb.rules){
				//	std::cout << x.toStr() << std::endl;
				//}

				std::cout << "erase useless rule: " << idb.rules[i].toStr() << std::endl;



				idb.rules.erase( idb.rules.begin() + i);
				//idb.rules.erase( &(idb.rules[i]));

				/*
				std::vector<IClause> tv;
				for(int j=0;j<idb.rules.size(); ++j) {
					if(i == j) continue;
					tv.push_back( std::move( idb.rules[j] ) );
				}

				idb.rules = std::move(tv);*/

				//for(IClause & x : idb.rules){
				//	std::cout << x.toStr() << std::endl;
				//}

				update = true;
				break;
			}
		}
	}

	// init affected IDBTR
	for(int idb_index : affected_idbs) {
		idbRules[ idb_index ].init();
	}
    
    std::chrono::steady_clock::time_point examine_idb_end = std::chrono::steady_clock::now();
    
    std::cout << "(Time_Measure) examine_each_IDBTR takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(examine_idb_end - examine_idb_begin).count()
    << " ms, longest_run: " << longest_run<<" max_threads: " << max_threads << "\n";

}

std::string DPManager::nice_display(const std::vector<int>& Q) const {
	std::stringstream ss;

	const int  idb_index = Q[0];
	const IDBTR& idb = idbRules[idb_index];
	const int arity = idb.rel.getArity();
	if(arity == (Q.size() - 1)){
		ss << idb.rel.getRelName() << "(";
		for(int i=0;i< arity; ++i) {
			if (i) {
				ss << ",";
			}
			ss << ConstName[Q[i + 1]];
		}
		ss << ")";
	}
	else{
		ss << "arity doest not match: " << idb.rel.getRelNameWithTypes()
				<< ", actual arity=" << Q.size() - 1;
	}

	return ss.str();
}


} // end of namespace ALPS
