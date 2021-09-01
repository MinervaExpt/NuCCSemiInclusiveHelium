
#include "Make_Arachne_links.h"
//////////////////////////////////////////////////////////////////////////////




std::vector <SliceID> readInVector(const char* Title_text);
std::vector <SliceID_secTrk> readInVector_secTrk(const char* Title_text);
void WriteArachneLinksFrom_SliceID_secTrk(std::vector <SliceID_secTrk> input_vector, const char *output_name, bool isdata, bool useRodriges  );
void WriteArachneLinksFrom_SliceID_secTrk_CVSformat(std::vector <SliceID_secTrk> input_vector,  const char *output_name, bool isdata, bool useRodriges  );
void WriteArachneLinksFrom_SliceID_secTrk_LATEXCVSformat(std::vector <SliceID_secTrk> input_vector,  const char *output_name, bool isdata, bool useRodriges  );
void Kin(bool &Make_Arachne, bool &my_debug, const char *userDir) {
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~       Starting to Make Links: Arachne Links         ~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

const std::vector< ME_helium_Playlists> kPlayListVector = GetPlayListVector();
const std::vector<CryoVertex> kCryoVertexVaribles_vector = GetCryoVertexVaribles();


 char text_title_pdf1[2024];
 char text_title_pdf2[2024];
 char text_title_pdf3[2024];
 char text_title_pdf4[2024];
time_t now = time(0);
tm *ltm = localtime(&now);
 char timeset[2024];
sprintf(timeset,"%i_%i_%i_%i",1 + ltm->tm_mon,ltm->tm_mday, ltm->tm_hour,ltm->tm_min);


std::string pdf = string(text_title_pdf4);


auto vector = readInVector("test_1");

auto vector_arachne = readInVector_secTrk("Arachne_Arachne_secTRKBOTH_ME1D");

auto vector_High_angle = readInVector_secTrk("Arachne_Arachne_secTRKBOTH_ME1D");

auto vector_LowKE = readInVector_secTrk("Arachne_Arachne_secTRKlowKE_ME1D");

auto vector_TRUTH = readInVector_secTrk("Arachne_Arachne_secTRKBOTH_ME1DTRUTH");






for(auto cat : vector_arachne){
std::cout<< " pdg = "<< cat.pdg <<"  run:  "<< cat.run<< "  subrun:"<<cat.subrun<< "  gate:"<<cat.gate<< "  slice:"<<cat.slice<< std::endl;


}


WriteArachneLinksFrom_SliceID_secTrk(vector_arachne, "SecondaryTrkLowE_withAngleabove60", false, false  );

WriteArachneLinksFrom_SliceID_secTrk_LATEXCVSformat(vector_arachne, "Latexformat_SecondaryTrkLowE_withAngleabove60", false, true);

WriteArachneLinksFrom_SliceID_secTrk_LATEXCVSformat(vector_arachne, "Latexformat_withAngleabove60", false, true);

WriteArachneLinksFrom_SliceID_secTrk_LATEXCVSformat(vector_TRUTH , "Latexformat_withAngleabove60_TRUTH", false, true);

WriteArachneLinksFrom_SliceID_secTrk_CVSformat(vector_TRUTH , "CVSFormat_TRUTH_angleabout60", false, true);




   std::cout << std::endl;
   std::cout << "Done WITH Stacks" << std::endl;


}


//End of MainFuntion





/////////////////////////////////////////////
//Main Function
/////////////////////////////////////////////

 int main() {

bool Make_Arachne;
std::cout << "Make Arachne  (0 = false, 1 = true) " << std::endl;
std::cin >> Make_Arachne;
std::cout << std::boolalpha << Make_Arachne << std::endl;

bool m_Debug;
std::cout << "Debug On  (0 = false, 1 = true) " << std::endl;
std::cin >> m_Debug;
std::cout << std::boolalpha << m_Debug << std::endl;


std::string input;
std::cout << "What is the name of the user? " << std::endl;
std::cin >> input;
std::cout << input << std::endl;

const char *inputFileLoc = input.c_str();

Kin(Make_Arachne, m_Debug, inputFileLoc);

return 0;

}



std::vector<ME_helium_Playlists> GetPlayListVector() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<ME_helium_Playlists> Playlist;

  //Playlist.push_back(kME1G);
  Playlist.push_back(kME1P);
  Playlist.push_back(kME1A);

  return Playlist;
//#endif
}

//////////////////////////////////////////////////////////////////////////
//GET Vertex Varibles
//////////////////////////////////////////////////////////////////////////
std::vector<CryoVertex> GetCryoVertexVaribles() {
//#ifndef __CINT__ // related: https://root.cern.ch/faq/how-can-i-fix-problem-leading-error-cant-call-vectorpushback
  std::vector<CryoVertex> CryoVertexVars;

  CryoVertexVars.push_back(kX);
  CryoVertexVars.push_back(kY);
  CryoVertexVars.push_back(kZ);
  CryoVertexVars.push_back(kR);


  return CryoVertexVars;
//#endif
}

std::vector <SliceID> readInVector(const char* Title_text){

  char Title[1024];
  sprintf(Title, "%s.cvs",Title_text );

  std::ifstream myfile(Title);

  //const char delimiter = ',';

  std::vector <SliceID> C;
  if ( myfile.is_open() ){

    int run,subrun,gate,slice;
    char delimiter;
    myfile.ignore(1000, '\n');

    while(myfile >> run >> delimiter >> subrun >> delimiter >> gate >> delimiter >> slice){
      C.push_back({run,subrun,gate,slice});
    }
  }
  else{
    std::cerr<<"ERROR: The file isnt open.\n";
  }
  return C;
}//end of function



std::vector <SliceID_secTrk> readInVector_secTrk(const char* Title_text){

  char Title[1024];
  sprintf(Title, "%s.cvs",Title_text );

  std::ifstream myfile(Title);

  //const char delimiter = ',';

  std::vector <SliceID_secTrk> C;
  if ( myfile.is_open() ){

    int run,subrun,gate,slice;
    char delimiter;
    myfile.ignore(1000, '\n');
    double angle;
    double Energy_GeV;
    int pdg;


    while(myfile >> run >> delimiter >> subrun >> delimiter >> gate >> delimiter >> slice >> delimiter >> angle >> delimiter >> Energy_GeV >> delimiter >> pdg){
      C.push_back({run,subrun,gate,slice,angle,Energy_GeV,pdg});
    }
  }
  else{
    std::cerr<<"ERROR: The file isnt open.\n";
  }
  return C;
}//end of function



void WriteArachneLinksFrom_SliceID_secTrk(std::vector <SliceID_secTrk> input_vector,  const char *output_name, bool isdata, bool useRodriges  ){

  std::ofstream myfile;
  char Title[1024];
  sprintf(Title, "%s.cvs", output_name );
  std::string comma =  ",";
  myfile.open (Title);
  myfile << "pdg , name, Energy, Angle, Links \n";


  for(auto cat : input_vector ){
    std::string particle_name = GetcommonNamefromPDG(cat.pdg);
    SliceID event_id;

    event_id.run = cat.run;
    event_id.subrun = cat.subrun;
    event_id.gate = cat.gate;
    event_id.slice = cat.slice;

    std::string Link_path = arachne(event_id, isdata, useRodriges);

    myfile <<cat.pdg<< comma << particle_name << comma << cat.Energy_GeV << comma << cat.angle<< comma << Link_path <<"\n";


  }//end of for loop


  myfile.close();



}//end of function

void WriteArachneLinksFrom_SliceID_secTrk_LATEXCVSformat(std::vector <SliceID_secTrk> input_vector,  const char *output_name, bool isdata, bool useRodriges  ){

  std::ofstream myfile;
  char Title[1024];
  sprintf(Title, "%s.txt", output_name );
  std::string comma =  ",";
  myfile.open (Title);
  myfile << "\\documentclass{minimal} \n";
  myfile << "\\begin{filecontents*}{name.csv} \n";
  myfile << "pdg, pdg name, Energy, Angle, Links \n";

  int i = 1;
  for(auto cat : input_vector ){
    std::string particle_name = GetcommonNamefromPDG(cat.pdg);
    SliceID event_id;

    event_id.run = cat.run;
    event_id.subrun = cat.subrun;
    event_id.gate = cat.gate;
    event_id.slice = cat.slice;

    std::string Link_path = arachne(event_id, isdata, useRodriges);

    myfile <<cat.pdg<< comma << particle_name << comma << cat.Energy_GeV << comma << cat.angle<< comma << "\\href{" <<Link_path << " }{Archne link  "<< i << " }"<<"\n";
    i++;

  }//end of for loop


myfile << "\\end{filecontents*}\n";

  myfile.close();



}//end of function


bool Compare_SliceID_secTrk(SliceID_secTrk A, SliceID_secTrk B){
if(A.run == B.run  &&  A.subrun == B.subrun && A.gate == B.gate && A.slice == B.slice )
{return true;}
else {return false;}
}

/*
vector <SliceID_secTrk>  returnUnionVector_SliceID_secTrk_vectors(vector <SliceID_secTrk> input_A,
  vector<SliceID_secTrk> input_B,vector <SliceID_secTrk> &Unque_A, vector<SliceID_secTrk> &Unque_B ){




vector <SliceID_secTrk> Vector;

for(auto cat : input_A ){
 for(auto dog : input_B){

if(Compare_SliceID_secTrk(cat,dog){
Vector.push_back(cat);
else(
Unque_A.push_back(cat);
Unque_B.push_back(dog);
)

}


 }
}
*/

void WriteArachneLinksFrom_SliceID_secTrk_CVSformat(std::vector <SliceID_secTrk> input_vector,  const char *output_name, bool isdata, bool useRodriges  ){

  std::ofstream myfile;
  char Title[1024];
  sprintf(Title, "%s.cvs", output_name );
  std::string comma =  ",";
  myfile.open (Title);
   myfile << "pdg, pdg name, Energy, Angle, Links \n";

  int i = 1;
  for(auto cat : input_vector ){
    std::string particle_name = GetcommonNamefromPDG(cat.pdg);
    SliceID event_id;

    event_id.run = cat.run;
    event_id.subrun = cat.subrun;
    event_id.gate = cat.gate;
    event_id.slice = cat.slice;

    std::string Link_path = arachne(event_id, isdata, useRodriges);

    myfile <<cat.pdg<< comma << particle_name << comma << cat.Energy_GeV << comma << cat.angle<< comma  <<Link_path << "\n";
    i++;

  }//end of for loop


  myfile.close();



}//end of function
