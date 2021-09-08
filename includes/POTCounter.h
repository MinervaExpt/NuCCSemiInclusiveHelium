#include "PlotUtils/ChainWrapper.h"

#include <string>
double GetPOT(PlotUtils::ChainWrapper* _chain,std::string name="Data"){
  TChain *chain = _chain->GetChain();
  double tot_pot_data = 0.0;
  double pot_data = 0.0;
  TBranch *b_pot_data;
  chain->SetBranchAddress("POT_Used",&pot_data,&b_pot_data);
  Int_t tot_entries = chain->GetEntries();
  double global_pot_data = 0.0;
  double global_pot=0.0;
  TBranch *b_global_pot;
  chain->SetBranchAddress("POT_Total",&global_pot,&b_global_pot);
  for(int i =0;i<tot_entries;i++){
    chain->GetEntry(i);
    tot_pot_data+= pot_data;
    global_pot_data+= global_pot;
  }
  std::cout<<name << "Total POT: "<<global_pot_data<<std::endl;
  std::cout<<name << "Used POT returned: "<<tot_pot_data<<std::endl;
  return tot_pot_data;
}

