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

  for(i = 0; i < inputCount; i++){
    myInput >> numFromFile;
    redBlackTree.insertNode(numFromFile);
  }

  // redBlackTree.searchNode(200);
  // redBlackTree.searchNode(197);

  redBlackTree.printTree();

  redBlackTree.deleteTree();
  
  return 0;
}