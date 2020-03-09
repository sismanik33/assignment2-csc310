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

  redBlackTree.searchNode(200);
  redBlackTree.searchNode(197);

  redBlackTree.printTree();

  rbTree secondRBTree;
  int insertArray[10] = {1,2,3,4,5,6,6,7,8,9};
  
  for (i = 0; i < 10; i++) {
    secondRBTree.insertNode(insertArray[i]);
  }
  secondRBTree.printTree();
  secondRBTree.deleteNode(11);
  secondRBTree.deleteNode(8);
  secondRBTree.printTree();
  cout<<"Attempting to delete tree:\n";
  redBlackTree.deleteTree();
  secondRBTree.deleteTree();
  cout<<"Printing empty tree:\n";
  secondRBTree.printTree();
  
  return 0;
}