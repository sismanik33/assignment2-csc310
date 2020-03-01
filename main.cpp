#include "rbTree.h"
#include "myException.h"

#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

  fstream myInput;
  int inputCount, i, numFromFile = 0;

  myInput.open("input.txt", ios::in);
  myInput >> inputCount;
  
  rbTree redBlackTree;
  int insertArray[5] = {5,4,3,2,1};

  for(i = 0; i < inputCount; i++){
    myInput >> numFromFile;
    redBlackTree.insertNode(numFromFile);
  }

  //  for(i = 0; i < 5; i++){
  //   redBlackTree.insertNode(insertArray[i]);
  // }
  // myInput.close();

  redBlackTree.printTree();
  
  return 0;
}