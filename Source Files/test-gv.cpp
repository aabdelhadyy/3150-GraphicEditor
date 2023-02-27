#include "ECGraphicViewImp.h"
#include "ECMouseObserver.h"
#include "ECKeyObserver.h"
#include "ECController.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
// Test graphical view code


void parseInts(string line, vector<int> &buffer){
    //cout << "parsing ints" << endl;
    stringstream stream(line);
    for (int n; stream >> n;) {
        //cout << n << endl;
        buffer.push_back(n);
    }
}
ECShape* parseShapes(ifstream &inFile, ECGraphicViewImp &view) {
    string buffer;
    getline(inFile, buffer);
    vector<int> nums;
    parseInts(buffer, nums);
    //cout << nums[0] << endl;
    switch (nums[0]) {
    case 0:
    {
        int x = nums[2];
        int y = nums[3];
        int cx = nums[6];
        int cy = nums[7];
        ECShape* newRect = new ECRectangle(view, x, y, cx, cy, false);
        return newRect;
    }
    case 1:
    {
        ECShape* newElip = new ECEllipse(view, nums[1], nums[2], nums[3], nums[4], false);
        return newElip;
    }
    case 2:
    {
        int x = nums[2];
        int y = nums[3];
        int cx = nums[6];
        int cy = nums[7];
        ECShape* newRect = new ECRectangle(view, x, y, cx, cy, true);
        return newRect;
    }
    case 3:
    {
        ECShape* newElip = new ECEllipse(view, nums[1], nums[2], nums[3], nums[4], true);
        return newElip;
    }
    case 4:
    {
        //cout << "composite" << endl;
        int numComposite = nums[1];
        vector<ECShape*> listShapes;
        for (int i = 0; i < numComposite; i++) {
            //cout << i << endl;
            listShapes.push_back(parseShapes(inFile, view));
        }
        //cout << "out of for loop" << endl;
        ECShape* newComp = new ECComposite(view, listShapes);
        return newComp;
    }
    }
}



int real_main(int argc, char **argv)
{
  const int widthWin = 500, heightWin = 500;
  ECGraphicViewImp view(widthWin, heightWin);

  // create a simple observer
  ECGraphicDoc doc;
  ECController ctrl(doc, view);
  ECMouseObserver mobs(view, ctrl);
  ECKeyObserver kobs(view, ctrl);
  view.Attach(&mobs);
  view.Attach(&kobs);


  if (argc >= 2) {
      std::ifstream inFile(argv[1]);
      if (inFile.is_open()) {
          string buffer;
          getline(inFile, buffer);
          vector<int> intBuff;
          parseInts(buffer, intBuff);
          int numShapes = intBuff[0];
          if (numShapes == 0) {
              inFile.close();
          }
          else {
              for (int i = 0; i < numShapes; i++) {
                  //cout << i << endl;
                  //cout << "numshapes:" << numShapes << endl;
                  //cout << "adding shape" << endl;
                  doc.AddShape(parseShapes(inFile, view));
              }
          }
          //cout << "closing file" << endl;
          inFile.close();
      }
  }
  view.Show();
  return 0;
}

int main(int argc, char **argv)
{
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

