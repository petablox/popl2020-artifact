#include  "defns.h"
#include  "extern.h"
#include  "template.h"
#include  "datalog.h"
#include  "context.h"
#include  "query.h"

#include "args.hpp"
#include "config.hpp"

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <z3++.h>


void redirectIO(){
  if (getenv("XCODE_STDIN")) {
    freopen( getenv("XCODE_STDIN"), "r", stdin);

    //std::ifstream arq(getenv("STDIN"));
    //std::cin.rdbuf(arq.rdbuf());
    std::cout << "redirected input" << std::endl;
  }
  else{
    //std::cout << "failed to redirect IO" << std::endl;
  }
}

int main(int argc, const char** argv)
/*    ----  */
{
    std::chrono::steady_clock::time_point synthesis_begin = std::chrono::steady_clock::now();

    redirectIO(); // used to debug in Xcode
    int save_in = dup(fileno(stdin));
    int seed;

    args::ArgumentParser parser("ALPS, a datalog synthesizer.", "");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::ValueFlag<std::string> flag_bench(parser, "string", "benchmark name (debug purpose)", {"bench"});

    args::Flag flag_onedirectional(parser, "One-directional", "One-directional search", {'O', "1D"});

    args::Group bisearch(parser, "\n**Bi-directional search args**\n", args::Group::Validators::DontCare);
    //args::Flag general(parser, "general", "general to specific (TopDown)", {'G', "TopDown"});
    //args::Flag specific(parser, "specific", "specific to general (BottomUp)", {'S', "BottomUp"});
    args::Flag flag_bidirectional(bisearch, "Bidirectional", "bi-directional search", {'B', "Bidirectional"});
    args::ValueFlag<int> flag_random(bisearch, "Random", "randomly pick questions", {'R', "Random"});
    args::ValueFlag<int> flag_K(bisearch, "int", "maximum #rules for each output relation", {'K', "MaxNumberPerIDB"});
    args::ValueFlag<int> flag_M(bisearch, "int", "maximum #rules for output program", {'M', "MaxNumberOverall"});
    args::ValueFlag<std::string> flag_T(bisearch, "string", "template file path", {'T', "Template"});



    //args::Group stage_search(parser, "\n**Staged search args**\n", args::Group::Validators::DontCare);
    args::Group stage_search = bisearch;
    //args::Flag flag_stage(stage_search, "Staged", "staged search", {'s', "staged"});
    args::Flag flag_chain1(stage_search, "chain1", "enable projection (or chain-1) pattern", {'1', "chain1","projection"});
    args::Flag flag_chain2(stage_search, "chain2", "enable chain of length two pattern", {'2', "chain2"});
    args::Flag flag_chain3(stage_search, "chain3", "enable chain of length three pattern", {'3', "chain3"});
    args::Flag flag_filter1(stage_search, "filter1", "enable filter-1 pattern", {"f1"});
    args::Flag flag_filter2(stage_search, "filter2", "enable filter-2 pattern", {"f2"});
    args::Flag flag_hb(stage_search, "HeadBinding", "enable bindings among rule head", {"headBinding"});
    args::ValueFlag<int> flag_bindings(stage_search, "int", "maximum #bindings in rule body", {'b', "bindings"});
    args::ValueFlag<int> flag_Aug(stage_search, "int", "maximum #augmentations", {'a', "augmentation"});

    args::ValueFlag<int> flag_distictRel(stage_search, "int", "maximum #dictinct relations in body", {'d', "distinctRel"});
    args::Flag flag_graph(bisearch, "Graph", "Graph edit distance", {'G', "Graph"});

    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

	ALPS::ContextManager CM;
    ALPS::QueryEngine QE;
    ALPS::Matching M;
	ALPS::DPManager DP(M);
    Configuration& Config = Configuration::getMutableConfig();
	std::string templatePath;
    

	z3::set_param("fixedpoint.engine", "datalog");

    if (flag_graph) {
        Config.enableGraphDistance = true;
        std::cout << "Graph distance is enabled" << std::endl;
    }
    
    if(flag_onedirectional) {
        Config.enable1D = true;
        std::cout << "One-directinal search is enabled" << std::endl;
    }
    else if(flag_bidirectional) {
        Config.enableG = true;
        Config.enableS = true;
        std::cout << "Bidirectional search is enabled" << std::endl;
    }
//    else if(flag_stage) {
//        Config.enableStaged = true;
//        std::cout << "Staged search is enabled" << std::endl;
//    }
    else {
        std::cout << "Error: no search strategy is chosen.\n"
        << "E.g. One directional, bi-directional, or staged search should be chosen" << std::endl;

        std::cout <<"\n" << parser << std::endl;
        return 0;
    }
    
    if(flag_random) {
        Config.enableRandom = true;
        QE.random_mode = true;
        seed = args::get(flag_random);
        std::srand(seed);
        std::cout << "will randomly pick questions, seed= " << seed << std::endl;
    }

    if(flag_K) {
        Config.K = args::get(flag_K);
        std::cout << "Maximum #rules for each IDB will be " << Config.K << std::endl;
    }
    if(flag_M) {
        Config.MaxRules = args::get(flag_M);
        std::cout << "Maximum #rules for programs will be " << Config.MaxRules << std::endl;
    }
    
    if(flag_T) {
        templatePath = args::get(flag_T);
        std::cout << "Using Templates: " << templatePath << std::endl;
        M.tm.loadTemplates(templatePath);
        std::cout << "Number of templates: " << M.tm.templates.size() << std::endl;
    }
    
    if(flag_distictRel) {
        Config.distinctRel = args::get(flag_distictRel);
        std::cout << "Number of maximum #distinct relations in a rule: " << Config.distinctRel << std::endl;
    }
    
    if(flag_filter1) {
        Config.enableFilter1 = true;
        std::cout << "filter-1 is enabled" << std::endl;
    }
    
    if(flag_filter2) {
        Config.enableFilter2 = true;
        std::cout << "filter-2 is enabled" << std::endl;
    }
    
    if (flag_hb) {
        Config.enableHeadBinding = true;
        std::cout << "Head bindings are enabled" << std::endl;
    }
    
    if(flag_Aug) {
        Config.augmentations = args::get(flag_Aug);
        std::cout << "augmentation distance: " << Config.augmentations << std::endl;
    }
    
    if (flag_bindings) {
        Config.bindings = args::get(flag_bindings);
        std::cout << "number of bindings: " << Config.bindings << std::endl;
    }
    
    if (flag_chain1) {
        Config.enableChain1 = true;
        std::cout << "chain1 is enabled" << std::endl;
    }
    
    if (flag_chain2) {
        Config.enableChain2 = true;
        std::cout << "chain2 is enabled" << std::endl;
    }
    
    if (flag_chain3) {
        Config.enableChain3 = true;
        std::cout << "chain3 is enabled" << std::endl;
    }
    
  MaxRel = -1;
	/*  Read input  */

	ReadTypes();

	//CheckTypeCompatibility();

	ReadRelations();

	fclose(stdin);
	stdin = fdopen(save_in,"r");

	//dup2(save_in, fileno(stdin));
	//char buf[100];
	//int status = scanf("%s", buf);
	//printf("\n\nbuf=%s, status=%d\n\n", buf, status);
	//return 0;


	CM.buildSorts(Type, MaxType+1);
	CM.buildFuncDecls(RelnOrder, MaxRel+1);
	CM.loadEDBFacts(RelnOrder, MaxRel+1);

	M.relm.loadRelations(RelnOrder, MaxRel+1);


    std::chrono::steady_clock::time_point synthesis_inputdone = std::chrono::steady_clock::now();
    std::cout << "\n**Loading input is done: " << std::chrono::duration_cast<std::chrono::milliseconds>(synthesis_inputdone - synthesis_begin).count() << " ms.\n\n";
    
    DP.exploreCandidateRules();
    std::chrono::steady_clock::time_point synthesis_exploreRules = std::chrono::steady_clock::now();

    std::cout << "\n**exploreCandidateRules is done: " << std::chrono::duration_cast<std::chrono::milliseconds>(synthesis_exploreRules - synthesis_begin).count() << " ms.\n\n";

    DP.fillIDBValues();


	QE.cm_ptr = &CM;
	QE.dp_ptr = &DP;
    
    if(flag_bidirectional) {
        QE.work();
    }
    else {
        std::cout <<"No search strategy is given!!" << std::endl;
    }
    
    std::chrono::steady_clock::time_point synthesis_end = std::chrono::steady_clock::now();
    
    std::cout << "\n**ALPS_end_to_end takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(synthesis_end - synthesis_begin).count()
    << " ms.\n";

    
	return 0;
}
