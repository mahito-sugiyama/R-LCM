#include <Rcpp.h>
#include <fstream>

#define Int int32_t
using namespace std;
using namespace Rcpp;
// [[Rcpp::plugins("cpp11")]]


// [[Rcpp::export]]
List lcm(NumericMatrix X, CharacterVector& file_name, double freq = 0.1, Int len_min = 0, Int len_max = 0) {
  if (len_max == 0) len_max = X.cols();

  // write to a file
  string file_name_cc = as<string>(file_name);
  string data_file = file_name_cc + "_input.txt";
  ofstream ofs(data_file.c_str());
  for (Int i = 0; i < X.rows(); ++i) {
    for (Int j = 0; j < X.cols(); ++j) {
      if (X(i, j) == 1) ofs << j << " ";
    }
    ofs << endl;
  } 
  ofs.close();

  // run LCM
  Int min_supp = (Int)round(freq * X.rows());
  string itemset_file = file_name_cc + "_itemsets.txt";
  remove(itemset_file.c_str());  
  string command_LCM = "./lcm Cf -l " + to_string(len_min) + " -u " + to_string(len_max) + " " + data_file + " " + to_string(min_supp) + " " + itemset_file;
  system(command_LCM.c_str());

  // read itemsets
  Int buf;
  string str;
  vector<vector<Int>> itemsets;
  NumericVector supports;
  ifstream ifs(itemset_file.c_str());
  while (getline(ifs, str)) {
    stringstream sstr(str);
    vector<Int> tmp;
    while (sstr >> buf) {
      tmp.push_back(buf);
    }
    supports.push_back(tmp.back());
    tmp.pop_back();
    sort(tmp.begin(), tmp.end());
    itemsets.push_back(tmp);
  }

  List res = List::create(Named("itemsets") = wrap(itemsets), Named("supports") = supports);
  return res;
}