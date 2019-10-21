//
//  config.hpp
//  ALPS
//
//  Created by Xujie Si on 11/9/17.
//  Copyright © 2017 Xujie Si. All rights reserved.
//

#ifndef config_hpp
#define config_hpp

class Configuration {
public:
  static Configuration* config;
  int MaxRules = 1<<30;
  int K = 1;
  int bindings = 0;
  int augmentations = 0;
  int distinctRel = -1;
  
  bool enable1D = false;
  bool enableG = false;
  bool enableS = false;
  bool enableX = false;
  bool enableStaged = false;
  
  bool enableRandom = false;  
  bool enableChain1 = false;
  bool enableChain2 = false;
  bool enableChain3 = false;
  bool enableHeadBinding = false;

  bool enableFilter1 = false;
  bool enableFilter2 = false;

  bool enableGraphDistance = false;
    
  static const Configuration& getConfig() {
    if(config == nullptr) {
      config = new Configuration();
    }
    return *config;
  }
  
  static Configuration& getMutableConfig() {
    if(config == nullptr) {
      config = new Configuration();
    }
    return *config;
  }
  
  
private:
  Configuration() {}
};


#endif /* config_hpp */
