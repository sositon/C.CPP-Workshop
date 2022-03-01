//
// Created by rotem on 30/10/2021.
//

#ifndef _MESURETIMEHELPER_H_
#define _MESURETIMEHELPER_H_
#include <vector>
#include <sstream>
#include <fstream>
#include "Apartment.h"
#include "Stack.h"
#include "AVL.h"
#include "Find.h"

/**
 *
 * Given a path to the file apartments100/apartments1000/apartments1000 return its corresponding vector
 * @param file_name A path to the given apartments file, in your pc.
 * @return a vector of st::pair<double, double> where each pair represents the x and y coordinates of an apartment.
 */
std::vector<std::pair<double, double>> xy_from_file (std::string file_name)
{
  std::ifstream in (file_name.c_str ());
  std::vector <std::pair<double, double>> vector;
  if (!in)
    {
      std::cerr << "Cannot open the File : " << file_name << std::endl;
      //exception
    }
  std::string str;
  // Read the next line from File until it reaches the end.
  while (std::getline (in, str))
    {
      std::stringstream ss (str);
      double pair[2];
      int i = 0;
      while (ss.good ())
        {
          std::string substr;
          getline (ss, substr, ',');
          pair[i++] = atof (substr.c_str ());
        }
      vector.push_back ({pair[0], pair[1]});
    }
  //Close The File
  in.close ();
  return vector;
}
class MyHashFunction {
 public:

  // We use predfined hash functions of strings
  // and define our hash function as XOR of the
  // hash values.
  size_t operator() (const Apartment &a) const
  {
    return (std::hash<double> () (a.get_x ()))
           ^ (std::hash<double> () (a.get_y ()));
  }
};
#endif //_MESURETIMEHELPER_H_
