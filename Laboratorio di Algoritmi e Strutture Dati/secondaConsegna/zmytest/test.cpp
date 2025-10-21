#include "../zlasdtest/test.hpp"

#include <iostream>
#include <random>
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"
#include "../heap/vec/heapvec.hpp"
#include "../pq/heap/pqheap.hpp"

using namespace std;
using namespace lasd;

string generaStringaCasuale(auto genChar) {
  char c = (char)(genChar() + 65);
  return string(1, c);
}

void stampaRisultati(const string& nomeTest, bool success){
  cout << (success ? "{GOOD} " : "{WRONG} ") << nomeTest << endl;
}

bool testCostruttoriVector(){
  cout << "Testing Vector Constructors" << endl;
  cout << "Not testing SortableVector constructors since they just call Vector constructors"<<endl;
  bool allPassed = true;
  
  //Costruttori default con int, string e double
  cout<<"-Default Constructor-"<<endl;
  lasd::Vector<int> vec1;
  bool defaultVecConstructorInt = (vec1.Size() == 0 && vec1.Empty());
  stampaRisultati("Default Vector constructor int", defaultVecConstructorInt);
  cout<<"  -Expected size: 0, Actual size: "<<vec1.Size()<<endl;
  cout<<"  -Expected empty vector, Actual emptiness: "<<vec1.Empty()<<endl;
  allPassed &= defaultVecConstructorInt;

  lasd::Vector<string> vec2;
  bool defaultVecConstructorString = (vec2.Size() == 0 && vec2.Empty());
  stampaRisultati("Default Vector constructor string", defaultVecConstructorString);
  cout<<"  -Expected size: 0, Actual size: "<<vec2.Size()<<endl;
  cout<<"  -Expected empty vector, Actual emptiness: "<<vec2.Empty()<<endl;
  allPassed &= defaultVecConstructorString;

  lasd::Vector<double> vec3;
  bool defaultVecConstructorDouble = (vec3.Size() == 0 && vec3.Empty());
  stampaRisultati("Default Vector constructor double ", defaultVecConstructorDouble);
  cout<<"  -Expected size: 0, Actual size: "<<vec3.Size()<<endl;
  cout<<"  -Expected empty vector, Actual emptiness: "<<vec3.Empty()<<endl;
  allPassed &= defaultVecConstructorDouble;

  //Costruttori con dimensione con int, string e double
  cout<<"-Size constructor-"<<endl;
  lasd::Vector<int> vec4(5);
  bool sizeVecConstructorInt = (vec4.Size() == 5 && !vec4.Empty());
  stampaRisultati("Size Vector constructor int", sizeVecConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<vec4.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec4.Empty()<<endl;
  allPassed &= sizeVecConstructorInt;

  lasd::Vector<string> vec5(5);
  bool sizeVecConstructorString = (vec5.Size() == 5 && !vec5.Empty());
  stampaRisultati("Size Vector constructor string", sizeVecConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<vec5.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec5.Empty()<<endl;
  allPassed &= sizeVecConstructorInt;

  lasd::Vector<double> vec6(5);
  bool sizeVecConstructorDouble = (vec6.Size() == 5 && !vec6.Empty());
  stampaRisultati("Size Vector constructor double ", sizeVecConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<vec6.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec6.Empty()<<endl;
  allPassed &= sizeVecConstructorDouble;

  //Test delle inizializzazioni
  bool initializationCorrect = true;
  for (ulong index = 0; index < 5; index++) {
    if (vec4[index] != 0 || vec5[index] != "" || vec6[index] != 0) {
      initializationCorrect = false;
      break;
    }
  }
  stampaRisultati("Element initialization", initializationCorrect);
  cout << "  - All elements should be 0" << endl;
  allPassed &= (initializationCorrect);

  //Preparazione della lista per il test del costruttore da TraversableContainer
  lasd::List<int> list1;
  lasd::List<string> list2;
  lasd::List<double> list3;
  for (ulong index = 0; index < 5; index++){
    list1.InsertAtBack(index);
  }
  list2.InsertAtBack("A"); list2.InsertAtBack("B"); list2.InsertAtBack("C"); list2.InsertAtBack("D"); list2.InsertAtBack("E");

  for (double index = 0; index < 0.5; index = index + 0.1){
    list3.InsertAtBack(index);
  }

  //Test del costruttore di TraversableContainer
  cout<<"-TraversableContainer constructor-"<<endl;
  lasd::Vector<int> vec7(list1);
  bool TraversableContainerVecConstructorInt = (vec7.Size() == 5 && !vec7.Empty());
  stampaRisultati("TraversableContainer Vector constructor int", TraversableContainerVecConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<vec7.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec7.Empty()<<endl;
  allPassed &= TraversableContainerVecConstructorInt;

  lasd::Vector<string> vec8(list2);
  bool TraversableContainerConstructorString = (vec8.Size() == 5 && !vec8.Empty());
  stampaRisultati("TraversableContainer Vector constructor string", TraversableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<vec8.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec8.Empty()<<endl;
  allPassed &= TraversableContainerConstructorString;

  lasd::Vector<double> vec9(list3);
  bool TraversableContainerConstructorDouble = (vec9.Size() == 5 && !vec9.Empty());
  stampaRisultati("TraversableContainer Vector constructor double ", TraversableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<vec9.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec9.Empty()<<endl;
  allPassed &= TraversableContainerConstructorDouble;

  //Test delle inizializzazioni
  bool elementsCorrectInt = true;
  for (ulong index = 0; index < vec7.Size(); index++) {
    if (vec7[index] != static_cast<int>(index)) {
      elementsCorrectInt = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- int (content)", elementsCorrectInt);
  cout << "  -Expected elements: 0 1 2 3 4" << endl;
  cout << "  -Actual elements: ";
  vec7.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectInt);

  bool elementsCorrectString = true;
  if (vec8[0] != "A" || vec8[1] != "B" || vec8[2] != "C" || vec8[3] != "D" || vec8[4] != "E") elementsCorrectString = false;
  stampaRisultati("-TraversableContainer constructor- string (content)", elementsCorrectString);
  cout << "  -Expected elements: A B C D E " << endl;
  cout << "  -Actual elements: ";
  vec8.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectString);

  bool elementsCorrectDouble = true;
  double value = 0;
  for (ulong index = 0; index<vec9.Size(); index++){
    if (vec9[index] != value){
      elementsCorrectDouble = false;
    }
    value += 0.1;
  }
  stampaRisultati("-TraversableContainer constructor- double (content)", elementsCorrectDouble);
  cout << "  - Expected elements: 0 0.1 0.2 0.3 0.4 " << endl;
  cout << "  - Actual elements: ";
  vec9.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDouble);

  cout<<"-MappableContainer constructor-"<<endl;
  lasd::Vector<int> vec14(std::move(list1));
  bool MappableContainerVecConstructorInt = (vec14.Size() == 5 && !vec8.Empty());
  stampaRisultati("MappableContainer Vector constructor int", MappableContainerVecConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<vec14.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec14.Empty()<<endl;
  allPassed &= MappableContainerVecConstructorInt;

  lasd::Vector<string> vec15(std::move(list2));
  bool MappableContainerConstructorString = (vec15.Size() == 5 && !vec15.Empty());
  stampaRisultati("MappableContainer Vector constructor string", MappableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<vec15.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec15.Empty()<<endl;
  allPassed &= MappableContainerConstructorString;

  lasd::Vector<double> vec16(std::move(list3));
  bool MappableContainerConstructorDouble = (vec16.Size() == 5 && !vec16.Empty());
  stampaRisultati("MappableContainer Vector constructor double ", MappableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<vec16.Size()<<endl;
  cout<<"  -Expected non-empty vector, Actual emptiness: "<<vec16.Empty()<<endl;
  allPassed &= MappableContainerConstructorDouble;

  //Test delle inizializzazioni
  bool elementsCorrectIntMap = true;
  for (ulong index = 0; index < vec14.Size(); index++) {
    if (vec14[index] != static_cast<int>(index)) {
      elementsCorrectIntMap = false;
      break;
    }
  }
  stampaRisultati("-MappableContainer constructor- int (content)", elementsCorrectIntMap);
  cout << "  - Expected elements: 0 1 2 3 4" << endl;
  cout << "  - Actual elements: ";
  vec14.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectIntMap);

  bool elementsCorrectStringMap = true;
  if (vec15[0] != "A" || vec15[1] != "B" || vec15[2] != "C" || vec15[3] != "D" || vec15[4] != "E") elementsCorrectStringMap = false;
  stampaRisultati("-MappableContainer constructor- string (content)", elementsCorrectStringMap);
  cout << "  - Expected elements: A B C D E " << endl;
  cout << "  - Actual elements: ";
  vec15.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectStringMap);

  bool elementsCorrectDoubleMap = true;
  double value2 = 0;
  for (ulong index = 0; index<vec16.Size(); index++){
    if (vec16[index] != value2){
      elementsCorrectDoubleMap = false;
    }
    value2 += 0.1;
  }
  stampaRisultati("-MappableContainer constructor- double (content)", elementsCorrectDoubleMap);
  cout << "  - Expected elements: 0 0.1 0.2 0.3 0.4 " << endl;
  cout << "  - Actual elements: ";
  vec16.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDoubleMap);

  //Test dei costruttori di Copy e Move
  lasd::Vector<int> copyvec1(vec7);
  lasd::Vector<string> copyvec2(vec8);
  lasd::Vector<double> copyvec3(vec9);

  cout<<"-Copy constructor-"<<endl;
  bool copyConstructorTestInt = (copyvec1.Size() == vec7.Size() && copyvec1 == vec7);
  stampaRisultati("-Copy constructor- int", copyConstructorTestInt);
  cout << "  - Expected size: " << copyvec1.Size() << ", Actual size: " << vec7.Size() << endl;
  cout << "  - Identical elements: " << (copyvec1 == vec7 ? "true" : "false") << endl;
  allPassed &= copyConstructorTestInt;

  bool copyConstructorTestString = (copyvec2.Size() == vec8.Size() && copyvec2 == vec8);
  stampaRisultati("-Copy constructor- string", copyConstructorTestString);
  cout << "  - Expected size: " << copyvec2.Size() << ", Actual size: " << vec8.Size() << endl;
  cout << "  - Identical elements: " << (copyvec2 == vec8 ? "true" : "false") << endl;
  allPassed &= copyConstructorTestString;

  bool copyConstructorTestDouble = (copyvec3.Size() == vec9.Size() && copyvec3 == vec9);
  stampaRisultati("-Copy constructor- double", copyConstructorTestDouble);
  cout << "  - Expected size: " << copyvec3.Size() << ", Actual size: " << vec9.Size() << endl;
  cout << "  - Identical elements: " << (copyvec3 == vec9 ? "true" : "false") << endl;
  allPassed &= copyConstructorTestDouble;

  lasd::Vector<int> movevec1(std::move(vec7));
  lasd::Vector<string> movevec2(std::move(vec8));
  lasd::Vector<double> movevec3(std::move(vec9));

  cout<<"-Move constructor-"<<endl;
  bool moveConstructorTestInt = (movevec1.Size() == 5 && vec7.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestInt);
  cout << "  - Expected size of new vector: 5, Actual size: " << movevec1.Size() << endl;
  cout << "  - Expected size of original vector: 0, Actual size: " << vec7.Size() << endl;
  cout << "  - Elements of new vector: ";
  movevec1.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestInt;

  bool moveConstructorTestString = (movevec2.Size() == 5 && vec8.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestString);
  cout << "  - Expected size of new vector: 5, Actual size: " << movevec2.Size() << endl;
  cout << "  - Expected size of original vector: 0, Actual size: " << vec8.Size() << endl;
  cout << "  - Elements of new vector: ";
  movevec2.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestString;

  bool moveConstructorTestDouble = (movevec3.Size() == 5 && vec9.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestDouble);
  cout << "  - Expected size of new vector: 5, Actual size: " << movevec3.Size() << endl;
  cout << "  - Expected size of original vector: 0, Actual size: " << vec9.Size() << endl;
  cout << "  - Elements of new vector: ";
  movevec3.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestDouble;

  cout<<"End of the Vector constructors test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testFunzioniVector(){
  cout << "Testing Vector Functions without testing limit cases" << endl;
  cout << "Not testing every datatype in this test, tests will be limited to the int type"<<endl;
  cout << "Also not testing SortableVector functions since they just call Vector functions, sorting test will be later"<<endl;
  cout << "Implicitly tested functions while testing the constructors: "<<endl;
  cout << "- operator[] in reading"<<endl;
  cout << "- operator =="<<endl;
  bool allPassed = true; 

  //Vector di test
  lasd::Vector<int> testVector1(5);
  for (ulong index = 0; index < 5; index++){
    testVector1[index] = index;
  }

  cout<<"Testing operator[] in writing"<<endl;
  lasd::Vector<int> testVector2(testVector1);
  for (ulong index = 0; index<5; index++){
    testVector2[index] = testVector1[index]*2;
  }

  bool operatorWriteTest = true;
  for (ulong index = 0; index<5; index++){
    if (testVector2[index] != (testVector1[index]*2)){
      operatorWriteTest = false;
      break;
    }
  }
  stampaRisultati("operator[] write", operatorWriteTest);
  cout << "  - Expected elements after modification: 0 2 4 6 8" << endl;
  cout << "  - Actual elements: ";
  for (ulong index = 0; index < testVector2.Size(); index++) {
    cout << testVector2[index] << " ";
  }
  cout << endl;
  allPassed &= operatorWriteTest;

  cout << "Testing != Operator"<<endl;
  bool notEqualOperator = (testVector1 != testVector2);
  stampaRisultati("operator !=", notEqualOperator);
  cout << "  - Expected result: true, Actual result: "<<(testVector1 != testVector2)<<endl;
  allPassed &= notEqualOperator;

  cout<<"Testing Front & Back"<<endl;
  bool frontTest = (testVector2.Front() == 0);
  bool backTest = (testVector2.Back() == 8);
  stampaRisultati("Front ", frontTest);
  cout<<"Expected front: 0, Actual front: "<<testVector2.Front()<<endl;
  stampaRisultati("Back ", backTest);
  cout<<"Expected back: 8, Actual back: "<<testVector2.Back()<<endl;
  allPassed &= (frontTest & backTest);

  cout<<"Testing copy assignment"<<endl;
  lasd::Vector<int> testVector3;
  testVector3 = testVector2;
  bool copyAssignmentTest = (testVector2 == testVector3);
  stampaRisultati("Copy assignment test ", copyAssignmentTest);
  cout << "  - Expected size: " << testVector2.Size() << ", Actual size: " << testVector3.Size() << endl;
  cout << "  - Identical elements: " << (testVector3 == testVector2 ? "true" : "false") << endl;
  allPassed &= copyAssignmentTest;

  cout<<"Testing move assignment"<<endl;
  lasd::Vector<int> testVector4;
  cout << "  - Elements of the old vector: ";
  testVector2.PreOrderTraverse([](const int &x) {cout << x << " "; });
  cout << endl;
  testVector4 = std::move(testVector2);
  bool moveAssignmentTest = (testVector2.Size() == 0 && testVector4.Size() == 5);
  stampaRisultati("Move assignment test ", moveAssignmentTest);
  cout << "  - Expected size of original vector: 0, Actual size: " << testVector2.Size() << endl;
  cout << "  - Elements of new vector: ";
  testVector4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveAssignmentTest;

  cout << "Testing an upsizing of the vector"<<endl;
  lasd::Vector<int> testVector5;
  testVector5 = testVector4;
  testVector4.Resize(6);
  bool upSizingTest = (testVector4.Size() == 6);
  stampaRisultati("Upsizing of the vector ", upSizingTest);
  cout<<"  -Expected size: 7, Actual size: "<<testVector4.Size()<<endl;
  cout<<"  -The initial elements were preserved: "<<endl;
  bool initialElementsTestUpSize = true;
  for (ulong index = 0; index<5; index++){
    if (testVector4[index] != testVector5[index]){
      initialElementsTestUpSize = false;
      break;
    }
  }
  cout<<endl;
  stampaRisultati("Preservation of the initial elements after upsisizing ", initialElementsTestUpSize);
  cout<<"Elements after the upsizing ";
  testVector4.PreOrderTraverse([](const int& x){cout << x << " ";});
  cout<<endl;
  allPassed &= (upSizingTest & initialElementsTestUpSize);

  cout<< "Testing a downsizing of the vector"<<endl;
  testVector5 = testVector4;
  testVector4.Resize(4);
  bool downSizingTest = (testVector4.Size() == 4);
  stampaRisultati("Downsizing of the vector ", downSizingTest);
  cout<<"  -The initial elements were preserved: "<<endl;
  bool initialElementsTestDownSize = true;
  for (ulong index = 0; index<testVector4.Size(); index++){
    if (testVector4[index] != testVector5[index]){
      initialElementsTestDownSize = false;
      break;
    }
  }
  stampaRisultati("Preservation of the elements after downsizing ", initialElementsTestDownSize);
  cout<<"Elements after downsizing, expected 0 2 4 6"<<endl;
  testVector4.PreOrderTraverse([](const int& x){cout << x << " ";});
  cout<<endl;
  allPassed &= (downSizingTest & initialElementsTestDownSize);
  

  cout<<"Testing clear"<<endl;
  testVector4.Clear();
  bool clearTest = (testVector4.Size() == 0 && testVector4.Empty());
  stampaRisultati("Clearing of the vector ", clearTest);
  cout<<"  -Expected size of the vector: 0, Actual size: "<<testVector4.Size()<<endl;
  cout<<"  -The vector must be empty, Actual emptiness: "<<testVector4.Empty()<<endl;
  allPassed &= clearTest;

  cout<<"End of the vector functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testUlterioriFunzioniVector(auto genInt){
  cout <<"Testing other Vector functions, mostly inherited ones"<<endl;
  cout <<"Implicitly tested functions while testing Vector functions: "<<endl;
  cout <<" -PreOrderTraverse()"<<endl;
  cout <<" -Size()"<<endl;
  cout <<" -Empty()"<<endl;
  bool allPassed = true;

  //Vector di test
  lasd::Vector<int> testVec1(5);
  for (ulong index = 0; index<5; index++){
    testVec1[index] = index;
  }


  cout<<"Testing PostOrderTraverse, no boolean here"<<endl;
  cout<<"PreOrderTraverse of the vector, the post order must be the reverse of this: "<<endl;
  testVec1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Post order: "<<endl;
  testVec1.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout << endl;

  lasd::Vector<int> testVec2(testVec1);
  cout<<"Testing PreOrderMap"<<endl;
  testVec1.PreOrderMap([](int& x){x*=2;});
  testVec1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testPreOrderMap = true;
  for (ulong index = 0; index < testVec1.Size(); index++){
      if (testVec1[index]/2 != testVec2[index]){
        testPreOrderMap = false;
        break;
      }
  }
  stampaRisultati("Pre Order Map ", testPreOrderMap);
  cout<<"  -Original Elements: "<<endl;
  testVec2.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Expected elements: 0 2 4 6 8"<<endl;
  cout<<"  -Actual Elements: ";
  testVec1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testPreOrderMap;

  cout<<"Testing PostOrderMap"<<endl;
  testVec1 = testVec2;
  testVec1.PostOrderMap([](int& x){x*=2;});
  testVec1.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testPostOrderMap = true;
  for (ulong index = 0; index < testVec1.Size(); index++){
    if (testVec1[index]/2 != testVec2[index]){
      testPostOrderMap = false;
      break;
    }
  }
  stampaRisultati("Post Order Map ", testPostOrderMap);
  cout<<"  -Original Elements: ";
  testVec2.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Expected elements: 0 2 4 6 8"<<endl;
  cout<<"  -Actual Elements: ";
  testVec1.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testPostOrderMap;


  cout<<"Testing Exists"<<endl;
  cout<<"We know that 8 is in the vector, let's see if the Exists() function works as intended"<<endl;
  bool testExists = (testVec1.Exists(8));
  stampaRisultati("Exists ", testExists);
  cout<<"  -Existance of value: 8, Actual existance: "<<testVec1.Exists(8)<<endl;
  allPassed &= testExists;

  //Test di sorting con numeri casuali
  cout<<"Testing the sorting"<<endl;
  int randomNumber = 0;
  lasd::List<int> tempList;
  for (ulong index = 0; index<5; index++){
    randomNumber = genInt();
    tempList.InsertAtBack(randomNumber);
  }
  cout<<"Prepared a list with randomly generated values: ";
  tempList.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  lasd::SortableVector<int> sortableVector(tempList);
  sortableVector.Sort();
  bool testSort = true;
  for (ulong index = 0; index<sortableVector.Size()-1; index++){
    if (sortableVector[index] > sortableVector[index+1]){
      testSort = false;
    }
  }
  stampaRisultati("Sorting test ", testSort);
  cout<<"  -The vector should be sorted: ";
  sortableVector.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testSort;


  cout<<"PreOrderFold Test with int"<<endl;
  int sum = testVec1.PreOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PreOrderFoldTest = (sum == 20);
  stampaRisultati("Pre order fold test int", PreOrderFoldTest);
  cout<<"  -Expected sum should be: 20, Actual sum is: "<<sum<<endl;
  allPassed &= PreOrderFoldTest;
  
  lasd::Vector<string> testStringVec(5);
  testStringVec[0] = "A"; testStringVec[1] = "B"; testStringVec[2] = "C"; testStringVec[3] = "D"; testStringVec[4] = "E";
  cout<<"PreOrderFold Test with string"<<endl;
  string concat = testStringVec.PreOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PreOrderFoldTestString = (concat == "ABCDE");
  stampaRisultati("Pre order fold test string", PreOrderFoldTestString);
  cout<<"  -Expected concatenation should be: ABCDE, Actual concatenation is: "<<concat<<endl;
  allPassed &= PreOrderFoldTestString;

  cout<<"PostOrderFold Test with int"<<endl;
  int sum2 = testVec1.PostOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PostOrderFoldTest = (sum2 == 20);
  stampaRisultati("Post order fold test int", PostOrderFoldTest);
  cout<<"  -Expected sum should be: 20, Actual sum is: "<<sum2<<endl;
  allPassed &= PostOrderFoldTest;
  
  cout<<"PostOrderFold Test with string"<<endl;
  string concat2 = testStringVec.PostOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PostOrderFoldTestString = (concat2 == "EDCBA");
  stampaRisultati("Pre order fold test string", PostOrderFoldTestString);
  cout<<"  -Expected concatenation should be: EDCBA, Actual concatenation is: "<<concat2<<endl;
  allPassed &= PostOrderFoldTestString;

  
  cout<<"End of the vector other functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCasiLimiteVector(){
  cout << "Testing Vector limit cases" << endl;
  cout << "Here we are testing if exceptions are handled correctly" << endl;
  bool allPassed = true;
  lasd::Vector<int> limitVector1(5);
  for (ulong index = 0; index<5; index++) limitVector1[index] = index+1;
  cout<<"Testing accessing out of array size"<<endl;
  bool testOutOfIndex = false;
  try{
    limitVector1[5] = 0;
  } catch (out_of_range& e){
    testOutOfIndex = true;
    cout << e.what() << endl;
  }
  stampaRisultati("Not able to access out of index ", testOutOfIndex);
  cout<<"  -Last accessible index: 4, Actual tried index: 5"<<endl;
  allPassed &= testOutOfIndex;

  cout<<"Testing front & back with an empty vector"<<endl;
  limitVector1.Clear();
  bool testEmptyFront = false;
  bool testEmptyBack = false;
  try{
    limitVector1.Front();
  } catch (length_error& e){
    testEmptyFront = true;
    cout << e.what() << endl;
  }
  stampaRisultati("Not able to access front with an empty vector ", testEmptyFront);

  try{
    limitVector1.Back();
  } catch (length_error& e){
    testEmptyBack = true;
    cout << e.what() << endl;
  }
  stampaRisultati("Not able to access Back with empty vector ", testEmptyBack);
  allPassed &= testEmptyBack & testEmptyFront;

  cout<<"End of the vector limit cases test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCostruttoriList(){
  cout << "Testing List Constructors" << endl;
  bool allPassed = true;
  
  //Costruttore di default con int, string and double
  cout<<"-Default Constructor-"<<endl;
  lasd::List<int> list1;
  bool defaultListConstructorInt = (list1.Size() == 0 && list1.Empty());
  stampaRisultati("Default list constructor int", defaultListConstructorInt);
  cout<<"Expected size: 0, Actual size: "<<list1.Size()<<endl;
  cout<<"Expected empty list, Actual emptiness: "<<list1.Empty()<<endl;
  allPassed &= defaultListConstructorInt;

  lasd::List<string> list2;
  bool defaultListConstructorString = (list2.Size() == 0 && list2.Empty());
  stampaRisultati("Default list constructor string", defaultListConstructorString);
  cout<<"Expected size: 0, Actual size: "<<list2.Size()<<endl;
  cout<<"Expected empty list, Actual emptiness: "<<list2.Empty()<<endl;
  allPassed &= defaultListConstructorString;

  lasd::Vector<double> list3;
  bool defaultListConstructorDouble = (list3.Size() == 0 && list3.Empty());
  stampaRisultati("Default list constructor double ", defaultListConstructorDouble);
  cout<<"Expected size: 0, Actual size: "<<list3.Size()<<endl;
  cout<<"Expected empty list, Actual emptiness: "<<list3.Empty()<<endl;
  allPassed &= defaultListConstructorDouble;

  //Preparazione della lista per il test del costruttore da TraversableContainer
  lasd::Vector<int> vector1(5);
  lasd::Vector<string> vector2(5);
  lasd::Vector<double> vector3(5);
  for (ulong index = 0; index < 5; index++){
    vector1[index] = index;
  }

  vector2[0] = "A"; vector2[1] = "B"; vector2[2] = "C"; vector2[3] = "D"; vector2[4] = "E";

  double vecValue = 0;
  for (ulong index = 0; index < vector3.Size(); index++){
    vector3[index] = vecValue;
    vecValue += 0.1;
  }
  
  //Test del costruttore di TraversableContainer
  cout<<"-TraversableContainer constructor-"<<endl;
  lasd::List<int> list4(vector1);
  bool TraversableContainerListConstructorInt = (list4.Size() == 5 && !list4.Empty());
  stampaRisultati("TraversableContainer list constructor int", TraversableContainerListConstructorInt);
  cout<<"Expected size: 5, Actual size: "<<list4.Size()<<endl;
  cout<<"Expected non-empty list, Actual emptiness: "<<list4.Empty()<<endl;
  allPassed &= TraversableContainerListConstructorInt;

  lasd::List<string> list5(vector2);
  bool TraversableContainerListConstructorString = (list5.Size() == 5 && !list5.Empty());
  stampaRisultati("TraversableContainer list constructor string", TraversableContainerListConstructorString);
  cout<<"Expected size: 5, Actual size: "<<list5.Size()<<endl;
  cout<<"Expected non-empty list, Actual emptiness: "<<list5.Empty()<<endl;
  allPassed &= TraversableContainerListConstructorString;

  lasd::List<double> list6(vector3);
  bool TraversableContainerListConstructorDouble = (list6.Size() == 5 && !list6.Empty());
  stampaRisultati("TraversableContainer list constructor double ", TraversableContainerListConstructorDouble);
  cout<<"Expected size: 5, Actual size: "<<list6.Size()<<endl;
  cout<<"Expected non-empty list, Actual emptiness: "<<list6.Empty()<<endl;
  allPassed &= TraversableContainerListConstructorDouble;

  //Test delle inizializzazioni
  bool elementsCorrectInt = true;
  for (ulong index = 0; index < list4.Size(); index++) {
    if (list4[index] != vector1[index]) {
      elementsCorrectInt = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- int (content)", elementsCorrectInt);
  cout << "  - Expected elements: 0 1 2 3 4" << endl;
  cout << "  - Actual elements: ";
  list4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectInt);


  bool elementsCorrectString = true;
  if (list5[0] != "A" || list5[1] != "B" || list5[2] != "C" || list5[3] != "D" || list5[4] != "E") elementsCorrectString = false;
  stampaRisultati("-TraversableContainer constructor- string (content)", elementsCorrectString);
  cout << "  - Expected elements: A B C D E " << endl;
  cout << "  - Actual elements: ";
  list5.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectString);

  bool elementsCorrectDouble = true;
  double value = 0;
  for (ulong index = 0; index<list6.Size(); index++){
    if (list6[index] != value){
      elementsCorrectDouble = false;
    }
    value += 0.1;
  }
  stampaRisultati("-TraversableContainer constructor- double (content)", elementsCorrectDouble);
  cout << "  - Expected elements: 0 0.1 0.2 0.3 0.4 " << endl;
  cout << "  - Actual elements: ";
  list6.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDouble);

  //
  cout<<"-MappableContainer constructor-"<<endl;
  lasd::List<int> list14(std::move(vector1));
  bool MappableContainerListConstructorInt = (list14.Size() == 5 && !list14.Empty());
  stampaRisultati("MappableContainer list constructor int", MappableContainerListConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<list14.Size()<<endl;
  cout<<"  -Expected non-empty list, Actual emptiness: "<<list14.Empty()<<endl;
  allPassed &= MappableContainerListConstructorInt;

  lasd::List<string> list15(std::move(vector2));
  bool MappableContainerConstructorString = (list15.Size() == 5 && !list15.Empty());
  stampaRisultati("MappableContainer list constructor string", MappableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<list15.Size()<<endl;
  cout<<"  -Expected non-empty list, Actual emptiness: "<<list15.Empty()<<endl;
  allPassed &= MappableContainerConstructorString;

  lasd::List<double> list16(std::move(vector3));
  bool MappableContainerConstructorDouble = (list16.Size() == 5 && !list16.Empty());
  stampaRisultati("MappableContainer list constructor double ", MappableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<list16.Size()<<endl;
  cout<<"  -Expected non-empty list, Actual emptiness: "<<list16.Empty()<<endl;
  allPassed &= MappableContainerConstructorDouble;

  //Test delle inizializzazioni
  bool elementsCorrectIntMap = true;
  for (ulong index = 0; index < list14.Size(); index++) {
    if (list14[index] != static_cast<int>(index)) {
      elementsCorrectIntMap = false;
      break;
    }
  }
  stampaRisultati("-MappableContainer constructor- int (content)", elementsCorrectIntMap);
  cout << "  - Expected elements: 0 1 2 3 4" << endl;
  cout << "  - Actual elements: ";
  list14.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectIntMap);

  bool elementsCorrectStringMap = true;
  if (list15[0] != "A" || list15[1] != "B" || list15[2] != "C" || list15[3] != "D" || list15[4] != "E") elementsCorrectStringMap = false;
  stampaRisultati("-MappableContainer constructor- string (content)", elementsCorrectStringMap);
  cout << "  - Expected elements: A B C D E " << endl;
  cout << "  - Actual elements: ";
  list15.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectStringMap);

  bool elementsCorrectDoubleMap = true;
  double value2 = 0;
  for (ulong index = 0; index<list16.Size(); index++){
    if (list16[index] != value2){
      elementsCorrectDoubleMap = false;
    }
    value2 += 0.1;
  }
  stampaRisultati("-MappableContainer constructor- double (content)", elementsCorrectDoubleMap);
  cout << "  - Expected elements: 0 0.1 0.2 0.3 0.4 " << endl;
  cout << "  - Actual elements: ";
  list16.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDoubleMap);

  //Preparando la lista per il costruttore di Copy
  lasd::List<int> list7;
  lasd::List<string> list8;
  lasd::List<double> list9;
  for (ulong index = 0; index < 5; index++){
    list7.InsertAtBack(index);
  }
  list8.InsertAtBack("A"); list8.InsertAtBack("B"); list8.InsertAtBack("C"); list8.InsertAtBack("D"); list8.InsertAtBack("E");

  for (double index = 0; index < 0.5; index = index + 0.1){
    list9.InsertAtBack(index);
  }

  //Test dei costruttori di Copy e Move
  lasd::List<int> copylist1(list7);
  lasd::List<string> copylist2(list8);
  lasd::List<double> copylist3(list9);

  cout<<"-Copy constructor-"<<endl;
  bool copyConstructorTestInt = (copylist1.Size() == list7.Size() && copylist1 == list7);
  stampaRisultati("-Copy constructor- int", copyConstructorTestInt);
  cout << "  - Expected size: " << copylist1.Size() << ", Actual size: " << list7.Size() << endl;
  cout << "  - Identical elements: " << (copylist1 == list7 ? "true" : "false") << endl;
  allPassed &= copyConstructorTestInt;

  bool copyConstructorTestString = (copylist2.Size() == list8.Size() && copylist2 == list8);
  stampaRisultati("-Copy constructor- string", copyConstructorTestString);
  cout << "  - Expected size: " << copylist2.Size() << ", Actual size: " << list8.Size() << endl;
  cout << "  - Identical elements: " << (copylist2 == list8 ? "true" : "false") << endl;
  allPassed &= copyConstructorTestString;

  bool copyConstructorTestDouble = (copylist3.Size() == list9.Size() && copylist3 == list9);
  stampaRisultati("-Copy constructor- double", copyConstructorTestDouble);
  cout << "  - Expected size: " << copylist3.Size() << ", Actual size: " << list9.Size() << endl;
  cout << "  - Identical elements: " << (copylist3 == list9 ? "true" : "false") << endl;
  allPassed &= copyConstructorTestDouble;

  lasd::List<int> movelist1(std::move(list7));
  lasd::List<string> movelist2(std::move(list8));
  lasd::List<double> movelist3(std::move(list9));

  cout<<"-Move constructor-"<<endl;
  bool moveConstructorTestInt = (movelist1.Size() == 5 && list7.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestInt);
  cout << "  - Expected size of new vector: 5, Actual size: " << movelist1.Size() << endl;
  cout << "  - Expected size of original vector: 0, Actual size: " << list7.Size() << endl;
  cout << "  - Elements of new vector: ";
  movelist1.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestInt;

  bool moveConstructorTestString = (movelist2.Size() == 5 && list8.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestString);
  cout << "  - Expected size of new vector: 5, Actual size: " << movelist2.Size() << endl;
  cout << "  - Expected size of original vector: 0, Actual size: " << list8.Size() << endl;
  cout << "  - Elements of new vector: ";
  movelist2.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestString;

  bool moveConstructorTestDouble = (movelist3.Size() == 5 && list9.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestDouble);
  cout << "  - Expected size of new vector: 5, Actual size: " << movelist3.Size() << endl;
  cout << "  - Expected size of original vector: 0, Actual size: " << list9.Size() << endl;
  cout << "  - Elements of new vector: ";
  movelist3.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestDouble;

  cout<<"End of the list constructors test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testFunzioniList(){
  cout << "Testing List Functions without testing limit cases" << endl;
  cout << "Not testing every datatype in this test, tests will be limited to the int type"<<endl;
  cout << "Implicitly tested functions while testing the constructors: "<<endl;
  cout << " -Every Node constructor "<<endl;
  cout << " -Node Clone function "<<endl;
  cout << " -PreOrderTraverse "<<endl;
  cout << " -operator[] in reading"<<endl;
  cout << " -operator =="<<endl;
  cout << " -Copy InsertAtBack"<<endl;
  bool allPassed = true;

  cout<<"Testing Move InsertAtBack while preparating a list for the tests"<<endl;
  lasd::List<int> testList1;
  bool testMoveInsertAtBack = true;
  int value = 0;
  for (ulong index = 0; index<5; index++){
    testList1.InsertAtBack(std::move(value));
    value = testList1[index]+1;
  }

  value = 0;
  for (ulong index = 0; index<testList1.Size(); index++){
    if (testList1[index] != value){
      testMoveInsertAtBack = false;
    }
    value++;
  }
  stampaRisultati("Move insert at back ", testMoveInsertAtBack);
  cout << "  -Expected size: 5, Actual size: " << testList1.Size() <<endl;
  cout << "  -Expected non-empty list, Actual emptiness: "<< testList1.Empty() << endl;
  cout << "  -Elements: ";
  testList1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testMoveInsertAtBack;

  cout<<"Testing Back() and RemoveFromBack, also testing copy assignment here"<<endl;
  int back = testList1.Back();
  bool testBack = (back == testList1[testList1.Size()-1]);
  stampaRisultati("Back test ", testBack);
  cout << "Expected back: " << testList1[testList1.Size()-1] << " Actual back: " << back << endl;
  allPassed &= testBack;

  lasd::List<int> testList2;
  testList2 = testList1;
  bool testCopyAssignment = (testList1 == testList2);
  stampaRisultati("Copy assignment test ", testCopyAssignment);
  cout<<"  -Expected elements: ";
  testList1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"  -Actual elements: ";
  testList2.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  testList1.RemoveFromBack();
  allPassed &= testCopyAssignment;

  bool testRemoveFromBack = (testList1.Size() == 4);
  for (ulong index = 0; index < testList1.Size(); index++){
    if (testList1[index] != testList2[index]){
      testRemoveFromBack = false;
      break;
    }
  }
  stampaRisultati("Remove from back test ", testRemoveFromBack);
  cout<<"  -Expected elements: 0 1 2 3"<<endl;
  cout<<"  -Actual elements, if equal to above, the initial elements have been preserved: ";
  testList1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testRemoveFromBack;

  cout<<"Testing BackNRemove"<<endl;
  int removedBack = testList2.BackNRemove();
  bool testBackNRemove = (removedBack == back);
  stampaRisultati("BackNRemove test ", testBackNRemove);
  cout<<"  -Removed back should be: "<<back<<" Actual back: "<<removedBack<<endl;
  allPassed &= testBackNRemove;

  cout<<"Testing InsertAtFront, both move and copy versions, this test includes Front()"<<endl;
  int insertCopy = 5; int insertMove = 8;
  testList2.InsertAtFront(insertCopy);
  bool testInsertAtFrontCopy = (insertCopy == testList2.Front());
  stampaRisultati("Insert at front copy version ", testInsertAtFrontCopy);
  cout << "  -Front should be: "<<insertCopy<<" Actual front: "<<testList2.Front()<<endl;
  allPassed &= testInsertAtFrontCopy;

  testList2.InsertAtFront(std::move(insertMove));
  insertMove = 0;
  bool testInsertAtFrontMove = (testList2.Front() == 8);
  stampaRisultati("Insert at front move version ", testInsertAtFrontMove);
  cout << "  -Front should be: "<< 8 <<" Actual front: "<<testList2.Front()<<endl;
  allPassed &= testInsertAtFrontMove;

  cout<<"List after the insertions: ";
  testList2.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"Testing != operator, confronting list2 and list1";
  bool testNotEqualList = (testList2 != testList1);
  stampaRisultati("!= operator test ", testNotEqualList);
  cout << "  -The two lists should not be equal, and they are " << ((testList1 != testList2) ? "not equal" : "equal") << endl;

  cout<<"Testing RemoveFromFront"<<endl;
  int newFront = testList2[1];
  testList2.RemoveFromFront();
  bool testFrontRemove = (newFront == testList2.Front());
  stampaRisultati("Remove from front test ", testFrontRemove);
  cout << "  -New front after removal should be: "<<newFront<<" Actual front: "<<testList2.Front()<<endl;
  allPassed &= testFrontRemove;

  cout<<"Testing FrontNRemove"<<endl;
  int frontAfterRemove = testList2[1];
  int removedFront = testList2.FrontNRemove();
  bool testFrontNRemove = (removedFront == newFront && testList2.Front() == frontAfterRemove);
  stampaRisultati("FrontNRemove test ", testFrontNRemove);
  cout<< "  -Removed front should be: "<<newFront<<" Actual removed front: "<<removedFront<<endl;
  cout<< "  -New front after removal should be: "<<frontAfterRemove<<" Actual front after removal: "<<testList2.Front()<<endl;
  allPassed &= testFrontNRemove;

  cout<<"List after the removals: ";
  testList2.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout << endl;

  lasd::List<int> testList10;
  cout<<"Copy assignment to empty test" <<endl;
  cout<<"  -Expected elements before: ";
  testList1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  testList1 = testList10;
  testCopyAssignment = (testList1 == testList10);
  stampaRisultati("Copy assignment empties the list", testCopyAssignment);
  cout<<"  -Expected elements after: ";
  testList1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyAssignment;

  lasd::Vector<int> copyVector(5);
  lasd::List<int> testList3(copyVector);
  cout << "Testing operator[] in writing with a new list"<<endl;
  for (int index = 0; index < 5; index++){
    testList3[index] = index;
  }
  cout<<"  -Expected list: 0 1 2 3 4, Actual list: ";
  testList3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"Testing PreOrderMap"<<endl;
  bool testPreOrderMap = true;
  testList2 = testList3;
  testList3.PreOrderMap([](int& x){ x = x*2;});
  for (ulong index = 0; index < testList3.Size(); index++){
    if ((testList3[index]/2) != testList2[index]){
      testPreOrderMap = false;
      break;
    }
  }
  stampaRisultati("Pre Order Map ", testPreOrderMap);
  cout<<"  -Expected list: 0 2 4 6 8, Actual list: ";
  testList3.PreOrderTraverse([](const int& x){cout << x << " ";});
  cout<<endl;
  allPassed &= testPreOrderMap;

  cout<<"Testing PostOrderMap"<<endl;
  bool testPostOrderMap = true;
  testList3.PostOrderMap([](int& x){x=x/2;});
  for (ulong index = 0; index < testList3.Size(); index++){
    if (testList3[index] != testList2[index]){
      testPostOrderMap = false;
      break;
    }
  }
  stampaRisultati("PostOrderMap ", testPostOrderMap);
  cout << "  -Expected list: 0 1 2 3 4, Actual list: ";
  testList3.PreOrderTraverse([](const int& x){cout << x << " ";});
  cout<<endl;
  allPassed &= testPostOrderMap;
  
  cout<<"Testing PreOrderFold with int"<<endl;
  lasd::List<int> testListInt;
  for (ulong index = 0; index < 5; index++){
    testListInt.InsertAtBack(index);
  }
  int sum = testListInt.PreOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PreOrderFoldTest = (sum == 10);
  stampaRisultati("Pre order fold test int", PreOrderFoldTest);
  cout<<"  -Expected sum should be: 10, Actual sum is: "<<sum<<endl;
  allPassed &= PreOrderFoldTest;
  
  cout<<"Testing PreOrderFold with string"<<endl;
  lasd::List<string> testListString;
  testListString.InsertAtBack("A"); testListString.InsertAtBack("B"); testListString.InsertAtBack("C"); testListString.InsertAtBack("D"); testListString.InsertAtBack("E");
  string concat = testListString.PreOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PreOrderFoldTestString = (concat == "ABCDE");
  stampaRisultati("Pre order fold test string", PreOrderFoldTestString);
  cout<<"  -Expected concatenation should be: ABCDE, Actual concatenation is: "<<concat<<endl;
  allPassed &= PreOrderFoldTestString;


  cout<<"Testing PostOrderFold with int"<<endl;
  int sumPost = testListInt.PostOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PostOrderFoldTestInt = (sumPost == 10);
  stampaRisultati("Post order fold test int", PostOrderFoldTestInt);
  cout<<"  -Expected sum should be: 10, Actual sum is: "<<sumPost<<endl;
  allPassed &= PostOrderFoldTestInt;
  
  cout<<"Testing PostOrderFold with string"<<endl;
  string concatPost = testListString.PostOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PostOrderFoldTestString = (concatPost == "EDCBA");
  stampaRisultati("Pre order fold test string", PostOrderFoldTestString);
  cout<<"  -Expected concatenation should be: EDCBA, Actual concatenation is: "<<concatPost<<endl;
  allPassed &= PostOrderFoldTestString;

  cout<<"Testing clear function"<<endl;
  testListString.Clear();
  bool testClear = (testListString.Size() == 0 && testListString.Empty());
  stampaRisultati("Clear test ", testClear);
  cout << "  -Expected size should be 0, actual size: "<<testListString.Size()<<endl;
  cout << "  -The list should be empty, and it is "<<(testListString.Empty() ? "Empty" : "Not Empty")<<endl;


  cout<<"Testing move assignment"<<endl;
  lasd::List<int> testList4;
  cout << "  - Elements of the old list: ";
  testList2.PreOrderTraverse([](const int &x) {cout << x << " "; });
  cout << endl;
  testList4 = std::move(testList2);
  bool moveAssignmentTest = (testList2.Size() == 0 && testList4.Size() == 5);
  stampaRisultati("Move assignment test ", moveAssignmentTest);
  cout << "  - Expected size of original list: 0, Actual size: " << testList2.Size() << endl;
  cout << "  - Elements of new list: ";
  testList4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveAssignmentTest;

  cout<<"End of the list functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCasiLimiteList(){
  cout << "Testing List limit cases" << endl;
  cout << "Here we are testing if exceptions are handled correctly" << endl;
  bool allPassed = true;
  lasd::List<int> limitList1;
  for (ulong index = 0; index<5; index++){
    limitList1.InsertAtBack(index);
  }

  cout<<"Testing accessing out of size with operator[]"<<endl;
  bool testOutOfSize = false;
  try{
    limitList1[5] = 0;
  } catch (out_of_range& e){
    testOutOfSize = true;
    cout << e.what() << endl;
  }
  stampaRisultati("Not able to access out of size ", testOutOfSize);
  allPassed &= testOutOfSize;

  limitList1.Clear();
  cout<<"Testing the removal of the back with an empty list"<<endl;
  bool testRemoveBackEmpty = false;
  try{
    limitList1.RemoveFromBack();
  } catch (length_error& e){
    testRemoveBackEmpty = true;
    cout << e.what() << endl;
  }
  allPassed &= testRemoveBackEmpty;
  stampaRisultati("Not able to remove from back with an empty list ", testRemoveBackEmpty);

  cout<<"Testing the removal and return of the back with an empty list"<<endl;
  bool testBackNRemoveEmpty = false;
  try{
    limitList1.BackNRemove();
  } catch (length_error& e){
    testBackNRemoveEmpty = true;
    cout << e.what() << endl;
  }
  allPassed &= testBackNRemoveEmpty;
  stampaRisultati("Not able to Back and Remove with an empty list ", testBackNRemoveEmpty);

  cout<<"Testing the removal of the front with an empty list"<<endl;
  bool testRemoveFrontEmpty = false;
  try{
    limitList1.RemoveFromFront();
  } catch (length_error& e){
    testRemoveFrontEmpty = true;
    cout << e.what() << endl;
  }
  allPassed &= testRemoveFrontEmpty;
  stampaRisultati("not able to remove from front with an empty list", testRemoveFrontEmpty);

  cout<<"Testing the removal and return of the front with an empty list"<<endl;
  bool testFrontNRemoveEmpty = false;
  try{
    limitList1.FrontNRemove();
  } catch (length_error& e){
    testFrontNRemoveEmpty = true;
    cout << e.what() << endl;
  }
  allPassed &= testFrontNRemoveEmpty;
  stampaRisultati("Not able to Front and Remove with an empty list  ", testFrontNRemoveEmpty);

  cout<<"Testing front with an empty list"<<endl;
  bool testFrontEmpty = false;
  try {
    limitList1.Front();
  } catch (length_error& e){
    testFrontEmpty = true;
    cout << e.what() << endl;
  }
  stampaRisultati("Not able to access Front with an empty list ", testFrontEmpty);
  allPassed &= testFrontEmpty;

  cout<<"Testing back with an empty list"<<endl;
  bool testBackEmpty = false;
  try {
    limitList1.Back();
  } catch (length_error& e){
    testBackEmpty = true;
    cout << e.what() << endl;
  }
  stampaRisultati("Not able to access Back with an empty list ", testBackEmpty);
  allPassed &= testBackEmpty;

  cout<<"Testing removing back with single element"<<endl;
  limitList1.Clear();
  bool testBackOne = false;
  limitList1.InsertAtBack(1);
  limitList1.RemoveFromBack();
  testBackOne = (0 == limitList1.Size());
  stampaRisultati("List emptied correctly", testBackOne);
  allPassed &= testBackOne;

  cout<<"End of the list limit cases test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCostruttoriSetLst(auto genInt, auto genChar, auto genReal){
  cout << "Testing SetLst Constructors" << endl;
  bool allPassed = true;

  cout<<"-Default Constructors-"<<endl;
  lasd::SetLst<int> setlist1;
  bool defaultSetListConstructorInt = (setlist1.Size() == 0 && setlist1.Empty());
  stampaRisultati("Default set list constructor int", defaultSetListConstructorInt);
  cout<<"  -Expected size: 0, Actual size: "<<setlist1.Size()<<endl;
  cout<<"  -Expected empty set list, Actual emptiness: "<<setlist1.Empty()<<endl;
  allPassed &= defaultSetListConstructorInt;

  lasd::SetLst<string> setlist2;
  bool defaultSetListConstructorString = (setlist2.Size() == 0 && setlist2.Empty());
  stampaRisultati("Default set list constructor string", defaultSetListConstructorString);
  cout<<"  -Expected size: 0, Actual size: "<<setlist2.Size()<<endl;
  cout<<"  -Expected empty set list, Actual emptiness: "<<setlist2.Empty()<<endl;
  allPassed &= defaultSetListConstructorString;

  lasd::SetLst<double> setlist3;
  bool defaultSetListConstructorDouble = (setlist3.Size() == 0 && setlist3.Empty());
  stampaRisultati("Default list constructor double ", defaultSetListConstructorDouble);
  cout<<"  -Expected size: 0, Actual size: "<<setlist3.Size()<<endl;
  cout<<"  -Expected empty list, Actual emptiness: "<<setlist3.Empty()<<endl;
  allPassed &= defaultSetListConstructorDouble;

  cout<<"-TraversableContainer constructor-"<<endl;
  //Preparazione delle liste necessarie
  lasd::List<int> list1; lasd::List<string> list2; lasd::List<double> list3;
  int randomNumber = 0;
  //I duplicati non sono ancora verificati
  while (list1.Size() < 5){
    randomNumber = genInt();
    while (list1.Exists(randomNumber)){
      randomNumber = genInt();
    }
    list1.InsertAtBack(randomNumber);
  }

  string randomString = "";
  while (list2.Size() < 5){
    randomString = generaStringaCasuale(genChar);
    while (list2.Exists(randomString)){
      randomString = generaStringaCasuale(genChar);
    }
    list2.InsertAtBack(randomString);
  }

  double randomDouble = 0.0;
  while (list3.Size() < 5){
    randomDouble = genReal();
    while (list3.Exists(randomDouble)){
      randomDouble = genReal();
    }
    list3.InsertAtBack(randomDouble);
  }

  lasd::SetLst<int> setlist4(list1);
  bool TraversableContainerSetListConstructorInt = (setlist4.Size() == 5 && !setlist4.Empty());
  stampaRisultati("TraversableContainer set list constructor int", TraversableContainerSetListConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<setlist4.Size()<<endl;
  cout<<"  -Expected non-empty set list, Actual emptiness: "<<setlist4.Empty()<<endl;
  allPassed &= TraversableContainerSetListConstructorInt;

  lasd::SetLst<string> setlist5(list2);
  bool TraversableContainerSetListConstructorString = (setlist5.Size() == 5 && !setlist5.Empty());
  stampaRisultati("TraversableContainer set list constructor string", TraversableContainerSetListConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<setlist5.Size()<<endl;
  cout<<"  -Expected non-empty set list, Actual emptiness: "<<setlist5.Empty()<<endl;
  allPassed &= TraversableContainerSetListConstructorString;

  lasd::SetLst<double> setlist6(list3);
  bool TraversableContainerSetListConstructorDouble = (setlist6.Size() == 5 && !setlist6.Empty());
  stampaRisultati("TraversableContainer set list constructor double", TraversableContainerSetListConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<setlist6.Size()<<endl;
  cout<<"  -Expected non-empty set list, Actual emptiness: "<<setlist6.Empty()<<endl;
  allPassed &= TraversableContainerSetListConstructorDouble;

  bool elementsCorrectInt = true;
  for (ulong index = 0; index < setlist4.Size(); index++) {
    if (!list1.Exists(setlist4[index])){
      elementsCorrectInt = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- int (content)", elementsCorrectInt);
  cout << "  - Expected elements: ";
  list1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setlist4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectInt);


  bool elementsCorrectString = true;
  for (ulong index = 0; index < setlist5.Size(); index++) {
    if (!list2.Exists(setlist5[index])){
      elementsCorrectString = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- string (content)", elementsCorrectString);
  cout << "  - Expected elements: ";
  list2.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setlist5.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectString);

  bool elementsCorrectDouble = true;
  for (ulong index = 0; index < setlist6.Size(); index++) {
    if (!list3.Exists(setlist6[index])){
      elementsCorrectDouble = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- double (content)", elementsCorrectDouble);
  cout << "  - Expected elements: ";
  list3.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setlist6.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDouble);

  lasd::SetLst<int> setlist14(std::move(list1));
  bool MappableContainerConstructorInt = (setlist14.Size() == 5 && !setlist14.Empty());
  stampaRisultati("MappableContainer setlist constructor int", MappableContainerConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<setlist14.Size()<<endl;
  cout<<"  -Expected non-empty set, Actual emptiness: "<<setlist14.Empty()<<endl;
  allPassed &= MappableContainerConstructorInt;

  lasd::SetLst<string> setlist15(std::move(list2));
  bool MappableContainerConstructorString = (setlist15.Size() == 5 && !setlist15.Empty());
  stampaRisultati("MappableContainer setlist constructor string", MappableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<setlist15.Size()<<endl;
  cout<<"  -Expected non-empty set, Actual emptiness: "<<setlist15.Empty()<<endl;
  allPassed &= MappableContainerConstructorString;

  lasd::SetLst<double> setlist16(std::move(list3));
  bool MappableContainerConstructorDouble = (setlist16.Size() == 5 && !setlist16.Empty());
  stampaRisultati("MappableContainer Vector constructor double ", MappableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<setlist16.Size()<<endl;
  cout<<"  -Expected non-empty set, Actual emptiness: "<<setlist16.Empty()<<endl;
  allPassed &= MappableContainerConstructorDouble;

  //-Copy constructor-
  cout<<"-Copy constructors-"<<endl;
  lasd::SetLst<int> setlist7(setlist4);
  bool copySetListConstructorInt = (setlist7.Size() == setlist4.Size());
  stampaRisultati("-Copy constructor- set list constructor int", copySetListConstructorInt);
  cout << "  -Expected size: " << setlist4.Size() << " Actual size: " << setlist7.Size() <<endl;
  cout << "  -Identical elements: " << (setlist7 == setlist4 ? "true" : "false") << endl;
  allPassed &= copySetListConstructorInt;

  lasd::SetLst<string> setlist8(setlist5);
  bool copySetListConstructorString = (setlist8.Size() == setlist5.Size());
  stampaRisultati("-Copy constructor- set list constructor string", copySetListConstructorString);
  cout << "  -Expected size: " << setlist5.Size() << " Actual size: " << setlist8.Size() <<endl;
  cout << "  -Identical elements: " << (setlist8 == setlist5 ? "true" : "false") << endl;
  allPassed &= copySetListConstructorString;

  lasd::SetLst<double> setlist9(setlist6);
  bool copySetListConstructorDouble = (setlist9.Size() == setlist6.Size());
  stampaRisultati("-Copy constructor- set list constructor double", copySetListConstructorDouble);
  cout << "  -Expected size: " << setlist6.Size() << " Actual size: " << setlist9.Size() <<endl;
  cout << "  -Identical elements: " << (setlist9 == setlist6 ? "true" : "false") << endl;
  allPassed &= copySetListConstructorDouble;

  bool elementsCorrectIntCopy = true;
  for (ulong index = 0; index < setlist7.Size(); index++) {
    if (setlist7[index] != setlist4[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- int (content)", elementsCorrectIntCopy);
  cout << "  - Expected elements: ";
  setlist4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setlist7.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectIntCopy);

  bool elementsCorrectStringCopy = true;
  for (ulong index = 0; index < setlist8.Size(); index++) {
    if (setlist8[index] != setlist5[index]){
      elementsCorrectStringCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- string (content)", elementsCorrectStringCopy);
  cout << "  - Expected elements: ";
  setlist5.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setlist8.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectStringCopy);

  bool elementsCorrectDoubleCopy = true;
  for (ulong index = 0; index < setlist9.Size(); index++) {
    if (setlist9[index] != setlist6[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- double (content)", elementsCorrectDoubleCopy);
  cout << "  - Expected elements: ";
  setlist6.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setlist9.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDoubleCopy);


  cout<<"-Move constructors-"<<endl;
  lasd::SetLst<int> movesetlist1(move(setlist4));
  bool moveConstructorTestInt = (movesetlist1.Size() == 5 && setlist4.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestInt);
  cout << "  - Expected size of setlist: 5, Actual size: " << movesetlist1.Size() << endl;
  cout << "  - Expected size of original setlist: 0, Actual size: " << setlist4.Size() << endl;
  cout << "  - Elements of new setlist: ";
  movesetlist1.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestInt;

  lasd::SetLst<string> movesetlist2(move(setlist5));
  bool moveConstructorTestString = (movesetlist2.Size() == 5 && setlist5.Size() == 0);
  stampaRisultati("-Move constructor- string", moveConstructorTestString);
  cout << "  - Expected size of setlist: 5, Actual size: " << movesetlist2.Size() << endl;
  cout << "  - Expected size of original setlist: 0, Actual size: " << setlist5.Size() << endl;
  cout << "  - Elements of new setlist: ";
  movesetlist2.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestString;

  lasd::SetLst<double> movesetlist3(move(setlist6));
  bool moveConstructorTestDouble = (movesetlist3.Size() == 5 && setlist6.Size() == 0);
  stampaRisultati("-Move constructor- double", moveConstructorTestDouble);
  cout << "  - Expected size of setlist: 5, Actual size: " << movesetlist3.Size() << endl;
  cout << "  - Expected size of original setlist: 0, Actual size: " << setlist6.Size() << endl;
  cout << "  - Elements of new setlist: ";
  movesetlist3.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestDouble;
  cout<<"End of the setlist constructors test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testFunzioniSetLst(){
  cout << "Testing SetLst Functions without testing limit cases" << endl;
  cout << "Not testing every datatype in this test, tests will be limited to the int type"<<endl;
  cout << "Implicitly tested functions while testing the constructors: "<<endl;
  cout << " -Not explicitly testing functions that may have been inherited from list even though list has been inherited as protected"<<endl;
  cout << " -PreOrderTraverse "<<endl;
  cout << " -operator =="<<endl;
  cout << " -operator[] in reading"<<endl;
  cout << " -Exists"<<endl;
  cout << " -Copy Insert (even though the insertion of duplicate elements has not been tested)"<<endl;
  bool allPassed = true;

  cout<<"Testing copy insert with duplicates"<<endl;
  cout<<"Trying to insert the values: 8 3 4 5 8 5 3"<<endl;
  lasd::SetLst<int> testsetlist1;
  int array[] = {8, 3, 4, 5, 8, 5, 3};
  for (ulong index = 0; index < 7; index++){
    testsetlist1.Insert(array[index]);
  } 
  bool testCopyInsertAndDupes = (testsetlist1.Size() == 4);
  for (ulong index = 0; index < testsetlist1.Size()-1; index++){
    for (ulong index2 = index+1; index2<testsetlist1.Size(); index2++){
      if (testsetlist1[index] == testsetlist1[index2]){
        testCopyInsertAndDupes = false;
        break;
      }
    }
  }
  stampaRisultati("Duplicates copy insert test ", testCopyInsertAndDupes);
  cout<<"  -Set size should be 4, Actual size: "<<testsetlist1.Size()<<endl;
  cout<<"  -Set elements should be: 3 4 5 8, Actual elements: ";
  testsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyInsertAndDupes;

  cout<<"Testing copy assignment"<<endl;
  lasd::SetLst<int> testsetlist2;
  testsetlist2 = testsetlist1;
  bool testCopyAssignment = (testsetlist1 == testsetlist2);
  stampaRisultati("Copy assignment ", testCopyAssignment);
  cout<<"  -Size should be: "<<testsetlist1.Size()<<" Actual size is: "<<testsetlist2.Size()<<endl;
  cout<<"  -Elements should be: ";
  testsetlist1.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual elements: ";
  testsetlist2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyAssignment;

  cout<<"Testing move assignment, also general Traverse will be tested"<<endl;
  testsetlist2.Clear();
  testsetlist2 = move(testsetlist1);
  bool testMoveAssignment = (testsetlist1.Empty());
  stampaRisultati("Move assignment ", testMoveAssignment);
  cout<<"  -Size should be: 4 Actual size is: "<<testsetlist2.Size()<<endl;
  cout<<"  -Other list should be empty, Other emptiness: "<<testsetlist1.Empty()<<endl;
  cout<<"  -Elements: ";
  testsetlist2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testMoveAssignment;

  cout<<"Testing move insert along with the != operator and Max()"<<endl;
  cout<<"Inserting element 9 (which should be at the end of the set)"<<endl;
  lasd::SetLst<int> testsetlist3(testsetlist2);
  testsetlist2.Insert(move(9));
  bool testMoveInsert = (testsetlist2.Max() == 9);
  bool testMax = testMoveInsert;
  bool testNotEqual = (testsetlist2 != testsetlist3);
  stampaRisultati("Move insert", testMoveInsert);
  cout<<"  -Inserted value should be 9, Actual set: ";
  testsetlist2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  stampaRisultati("Max ", testMax);
  cout<<"  -Max should be 9, actual back: "<<testsetlist2.Max()<<endl;
  stampaRisultati("operator != ", testNotEqual);
  cout<<"  -List before inserting 9: ";
  testsetlist3.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -List after inserting 9: ";
  testsetlist2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -So the two lists shouldn't be equal, and they are "<<(testsetlist2 != testsetlist3 ? "Not Equal" : "Equal")<<endl;
  allPassed &= testMoveInsert & testMax & testNotEqual;

  cout<<"Testing Min, RemoveMin and MinNRemove"<<endl;
  int min = testsetlist2.Min();
  bool testMin = (min == testsetlist2[0]);
  stampaRisultati("Min ", testMin);
  cout<<"  -Min should be: "<<testsetlist2[0]<<" Actual min: "<<min<<endl;

  testsetlist2.RemoveMin();
  bool testRemoveMin = (testsetlist2.Min() == testsetlist2[0] && testsetlist2.Size() == 4);
  stampaRisultati("Remove min ", testRemoveMin);
  cout<< "  -New min should be: "<<testsetlist2[0]<<" Actual min: "<<testsetlist2.Min()<<endl;
  cout<< "  -New size should be 4, Actual size: "<<testsetlist2.Size()<<endl;

  lasd::SetLst<int> testsetlist4(testsetlist2);
  min = testsetlist2.MinNRemove();
  bool testMinNRemove = (testsetlist4[0] == min && testsetlist2.Size() == 3);
  stampaRisultati("Min and remove ", testMinNRemove);
  cout<< "  -New min should be: "<<testsetlist2[0]<<" Actual min: "<<testsetlist2.Min()<<endl;
  cout<< "  -New size should be 3, Actual size: "<<testsetlist2.Size()<<endl;
  cout<< "  -Removed min should be: "<<testsetlist4[0]<<" Actual removed min: "<<min<<endl;
  allPassed &= testMin & testRemoveMin & testMinNRemove;

  cout<<"Testing Max, RemoveMax and MaxNRemove"<<endl;
  int max = testsetlist4.Max();
  bool testMax2 = (max == testsetlist4[testsetlist4.Size()-1]);
  stampaRisultati("Max ", testMax2);
  cout<<"  -Max should be: "<<testsetlist4[testsetlist4.Size()-1]<<" Actual max: "<<max<<endl;

  testsetlist4.RemoveMax();
  bool testRemoveMax = (testsetlist4.Max() == testsetlist4[testsetlist4.Size()-1] && testsetlist4.Size() == 3);
  stampaRisultati("Remove max ", testRemoveMax);
  cout<< "  -New max should be: "<<testsetlist4[testsetlist4.Size()-1]<<" Actual min: "<<testsetlist4.Max()<<endl;
  cout<< "  -New size should be 3, Actual size: "<<testsetlist4.Size()<<endl;

  lasd::SetLst<int> testsetlist5(testsetlist4);
  max = testsetlist4.MaxNRemove();
  bool testMaxNRemove = (testsetlist5[testsetlist5.Size()-1] == max && testsetlist4.Size() == 2);
  stampaRisultati("Max and remove ", testMaxNRemove);
  cout<< "  -New max should be: "<<testsetlist4[testsetlist4.Size()-1]<<" Actual max: "<<testsetlist4.Max()<<endl;
  cout<< "  -New size should be 2, Actual size: "<<testsetlist4.Size()<<endl;
  cout<< "  -Removed max should be: "<<testsetlist5[testsetlist5.Size()-1]<<" Actual removed max: "<<max<<endl;
  allPassed &= testMax2 & testRemoveMax & testMaxNRemove;

  // ADDED LATER
    cout<<"Testing Front and Back"<<endl;
    min = testsetlist3.Min(); max = testsetlist3.Max();
    bool testBack = (max == testsetlist3.Back());
    bool testFront = (min == testsetlist3.Front());
    stampaRisultati("Front of the set ", testFront);
    cout<<"  -Front of the set should be its minimum value, so: "<<min<<" , Actual front of the set: "<<testsetlist3.Front()<<endl;
    stampaRisultati("Back of the set ", testBack);
    cout<<"  -Back of the set should be its maximum value, so: "<<max<<" ,Actual back of the set: "<<testsetlist3.Back()<<endl;
    allPassed &= testBack & testFront;
  //

  cout<<"Testing InsertAll(copy) and InsertSome on two different lists that will be used in upcoming tests"<<endl;
  int array2[] = {5, 8, 2, 6, 9};
  int array3[] = {5, 5, 2, 8, 4};
  lasd::List<int> list2, list3;
  for (ulong index = 0; index<5; index++){
    list2.InsertAtBack(array2[index]);
    list3.InsertAtBack(array3[index]);
  }
  testsetlist5.Clear();
  bool testInsertAll = testsetlist5.InsertAll(list2);
  stampaRisultati("Insert all ", testInsertAll);
  cout<< "  -Values that should be inserted: ";
  list2.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<< "  -Actual inserted values: ";
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testInsertAll;

  testsetlist5.Clear();
  bool testInsertSome = testsetlist5.InsertSome(list3);
  stampaRisultati("Insert some ", testInsertSome);
  cout<< "  -Values that should be inserted: ";
  for (ulong index = 0; index < list3.Size(); index++) {
    bool seen = false;
    for (ulong index2 = 0; index2 < index; index2++) {
      if (list3[index] == list3[index2]) {
        seen = true;
        break;
      }
    }
    if (!seen) {
      cout << list3[index]<<" ";
    }
  }
  cout<<endl;
  cout<<"  -Actual inserted values: ";
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testInsertSome;

  lasd::SetLst<int> list13;
  bool testTail;
  list13.Insert(1); list13.Insert(2);
  cout<<"Testing Remove on the biggest element without RemoveMax"<<endl;
  list13.Remove(2);
  testTail = (list13.Min() == list13.Max());
  stampaRisultati("Removal of the biggest element without RemoveMax", testTail);
  cout<<"Min and max of the set should be the same, and they " <<(testTail ? "are" : "are not");

  cout<<"Testing Predecessor, RemovePredecessor and PredecessorNRemove"<<endl;
  cout<<"Print of the set for clarification: "<<endl;
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing predecessor for value: 6"<<endl;
  int pred = testsetlist5.Predecessor(6);
  bool testPredecessor = (pred == 5);
  stampaRisultati("Predecessor for value 6 ", testPredecessor);
  cout<<"  -Predecessor for value 6 must be 5, Actual predecessor: "<<pred<<endl;
  allPassed &= testPredecessor;

  cout<<"Testing removal of predecessor for value: 6"<<endl;
  lasd::SetLst<int> testsetlist6;
  testsetlist6.Insert(4); testsetlist6.Insert(2); testsetlist6.Insert(8);
  testsetlist5.RemovePredecessor(6);
  bool testRemovePredecessor = (testsetlist5 == testsetlist6 && testsetlist5.Size() == 3);
  stampaRisultati("Removal of predecessor for value: 6 ", testRemovePredecessor);
  cout<<"  -Set should be: ";
  testsetlist6.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testRemovePredecessor;

  testsetlist5.Insert(5);
  cout<<"Testing removal and returnal of predecessor for value: 6"<<endl;
  cout<<"Predecessor removed from the above test has been inserted back in the set"<<endl;
  int pred2 = testsetlist5.PredecessorNRemove(6);
  bool testPredecessorNRemove = (pred == pred2 && testsetlist5.Size() == 3);
  stampaRisultati("Predecessor and removal of predecessor for value: 6", testPredecessorNRemove);
  cout<<"  -Set should be: ";
  testsetlist6.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Removed predecessor should be: "<<pred<<" Actual removed predecessor: "<<pred2<<endl;
  allPassed &= testPredecessorNRemove;

  //
  cout<<"Testing Successor, RemoveSuccessor and SuccessorNRemove"<<endl;
  cout<<"Print of the set for clarification: "<<endl;
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing successor for value: 6"<<endl;
  int succ = testsetlist5.Successor(6);
  bool testSuccecessor = (succ == 8);
  stampaRisultati("Successor for value 6 ", testSuccecessor);
  cout<<"  -Successor for value 6 must be 8, Actual successor: "<<succ<<endl;
  allPassed &= testSuccecessor;

  cout<<"Testing removal of successor for value: 6, also testing removeall"<<endl;
  lasd::List<int> removeList;
  removeList.InsertAtBack(2); removeList.InsertAtBack(4); removeList.InsertAtBack(8);
  bool removedAll = testsetlist6.RemoveAll(removeList);
  stampaRisultati("Remove all ", removedAll);
  testsetlist6.Insert(4); testsetlist6.Insert(2);

  testsetlist5.RemoveSuccessor(6);
  bool testRemoveSuccessor = (testsetlist5 == testsetlist6 && testsetlist5.Size() == 2);
  stampaRisultati("Removal of successor for value: 6 ", testRemoveSuccessor);
  cout<<"  -Set should be: ";
  testsetlist6.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testRemoveSuccessor;

  testsetlist5.Insert(8);
  cout<<"Testing removal and returnal of successor for value: 6"<<endl;
  cout<<"Successor removed from the above test has been inserted back in the set"<<endl;
  int succ2 = testsetlist5.SuccessorNRemove(6);
  bool testSuccessorNRemove = (succ == succ2 && testsetlist5.Size() == 2);
  stampaRisultati("Successor and removal of successor for value: 6", testSuccessorNRemove);
  cout<<"  -Set should be: ";
  testsetlist6.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Removed successor should be: "<<succ<<" Actual removed successor: "<<succ2<<endl;
  allPassed &= testSuccessorNRemove;

  cout<<"Testing if values 7 and 16 exist in this set: ";
  testsetlist5.Insert(8); testsetlist5.Insert(7); testsetlist5.Insert(9); testsetlist5.Insert(18);
  testsetlist5.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testExists = (testsetlist5.Exists(7));
  bool testNotExists = (!testsetlist5.Exists(16));
  stampaRisultati("Existance of value 7", testExists);
  cout<<"  -Value 7 should exist in the set, and it "<<(testsetlist5.Exists(7) ? "Exists":"Doesn't Exist")<<endl;
  stampaRisultati("Existance of value 16", testNotExists);
  cout<<"  -Value 16 should not exist in the set, and it "<<(testsetlist5.Exists(16) ? "Exists":"Doesn't Exist")<<endl;
  allPassed &= testExists & testNotExists;

  cout<<"Testing post order traverse"<<endl;
  cout<<"  -The traverse print should be: 18 9 8 7 4 2"<<endl;
  cout<<"  -Actual print: ";
  testsetlist5.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"Testing pre order fold and post order fold with a string set"<<endl;
  lasd::SetLst<string> testsetliststring;
  testsetliststring.Insert("A"); testsetliststring.Insert("B"); testsetliststring.Insert("C"); testsetliststring.Insert("D");
  string concat = testsetliststring.PreOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PreOrderFoldTestString = (concat == "ABCD");
  stampaRisultati("Pre order fold test string", PreOrderFoldTestString);
  cout<<"  -Expected concatenation should be: ABCD, Actual concatenation is: "<<concat<<endl;
  allPassed &= PreOrderFoldTestString;

  concat = testsetliststring.PostOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PostOrderFoldTestString = (concat == "DCBA");
  stampaRisultati("Post order fold test string", PostOrderFoldTestString);
  cout<<"  -Expected concatenation should be: DCBA, Actual concatenation is: "<<concat<<endl;
  allPassed &= PostOrderFoldTestString;

  cout<<"End of the set list functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCasiLimiteSetLst(){
  cout << "Testing SetLst limit cases" << endl;
  cout << "Here we are testing if exceptions are handled correctly" << endl;
  lasd::SetLst<int> limitsetlist1;
  bool allPassed = true;
  cout<<"Testing operator[] with an empty set"<<endl;
  bool testOutOfIndex = false;
  try{
    limitsetlist1[5];
  } catch(out_of_range & e){
    testOutOfIndex = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the set at index 5 ", testOutOfIndex);
  allPassed &= testOutOfIndex;

  cout<<"Testing Min with an empty set"<<endl;
  bool testMinEmpty = false;
  try{
    limitsetlist1.Min();
  } catch(length_error & e){
    testMinEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the minimum with an empty set ", testMinEmpty);
  allPassed &= testMinEmpty;

  cout<<"Testing RemoveMin with an empty set"<<endl;
  bool testRemoveMinEmpty = false;
  try{
    limitsetlist1.RemoveMin();
  } catch(length_error & e){
    testRemoveMinEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the minimum with an empty set ", testRemoveMinEmpty);
  allPassed &= testRemoveMinEmpty;

  cout<<"Testing MinNRemove with an empty set"<<endl;
  bool testMinNRemoveEmpty = false;
  try{
    limitsetlist1.MinNRemove();
  } catch(length_error & e){
    testMinNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and access the minimum with an empty set ", testMinNRemoveEmpty);
  allPassed &= testMinNRemoveEmpty;

  cout<<"Testing Max with an empty set"<<endl;
  bool testMaxEmpty = false;
  try{
    limitsetlist1.Max();
  } catch(length_error & e){
    testMaxEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the maximum with an empty set", testMaxEmpty);
  allPassed &= testMaxEmpty;

  cout<<"Testing RemoveMax with an empty set"<<endl;
  bool testRemoveMaxEmpty = false;
  try{
    limitsetlist1.RemoveMax();
  } catch(length_error & e){
    testRemoveMaxEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the maximum with an empty set ", testRemoveMaxEmpty);
  allPassed &= testRemoveMaxEmpty;

  cout<<"Testing MaxNRemove with an empty set"<<endl;
  bool testMaxNRemoveEmpty = false;
  try{
    limitsetlist1.MaxNRemove();
  } catch(length_error & e){
    testMaxNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the maximum with an empty set ", testMaxNRemoveEmpty);
  allPassed &= testMaxNRemoveEmpty;

  cout<<"Testing predecessor with an empty set, reference value: 5"<<endl;
  bool testPredecessorEmpty = false;
  try{
    limitsetlist1.Predecessor(5);
  } catch (length_error & e){
    testPredecessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the predecessor of any value with an empty set ", testPredecessorEmpty);
  allPassed &= testPredecessorEmpty;

  cout<<"Testing the removal of predecessor for value 5 with an empty set"<<endl;
  bool testRemovePredecessorEmpty = false;
  try{
    limitsetlist1.RemovePredecessor(5);
  } catch (length_error & e){
    testRemovePredecessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the predecessor of any value with an empty set ", testPredecessorEmpty);
  allPassed &= testRemovePredecessorEmpty;

  cout<<"Testing the removal and returnal of predecessor for value 5 with an empty set"<<endl;
  bool testPredecessorNRemoveEmpty = false;
  try{
    limitsetlist1.PredecessorNRemove(5);
  } catch (length_error & e){
    testPredecessorNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the predecessor of any value with an empty set ", testPredecessorNRemoveEmpty);
  allPassed &= testPredecessorNRemoveEmpty;

  cout<<"Testing predecessor of value 5 with every value in the set > 5, here's the set: "<<endl;
  bool testPredecessorNotExisting = false;
  limitsetlist1.Insert(5); limitsetlist1.Insert(8); limitsetlist1.Insert(19); limitsetlist1.Insert(23); limitsetlist1.Insert(33);
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  try{
    limitsetlist1.Predecessor(5);
  } catch (length_error & e){
    testPredecessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to find any predecessors for value: 5 ", testPredecessorNotExisting);
  allPassed &= testPredecessorNotExisting;

  cout<<"Testing the removal of predecessor for value 5 every value in the set > 5, here's the set: "<<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testRemovePredecessorNotExisting = false;
  try{
    limitsetlist1.RemovePredecessor(5);
  } catch (length_error & e){
    testRemovePredecessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the predecessor for value: 5, it has not been found ", testRemovePredecessorNotExisting);
  allPassed &= testRemovePredecessorNotExisting;

  cout<<"Testing the removal and returnal of predecessor for value 5 every value in the set > 5, here's the set: "<<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testPredecessorNRemoveNotExisting = false;
  try{
    limitsetlist1.PredecessorNRemove(5);
  } catch (length_error & e){
    testPredecessorNRemoveNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the predecessor for value: 5, it has not been found ", testPredecessorNRemoveNotExisting);
  allPassed &= testPredecessorNRemoveNotExisting;

  cout<<"Testing the removal of the predecessor when it's the first of the set, here's the set: " <<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testRemovePredecessorFirst = false;
  limitsetlist1.RemovePredecessor(7);
  testRemovePredecessorFirst = (8 == limitsetlist1.Min());
  stampaRisultati("Removing the predecessor of the second element of the set", testRemovePredecessorFirst);
  cout<<"New min of the set should be 8, actual min of the set: " <<limitsetlist1.Min();
  allPassed &= testRemovePredecessorFirst;

  cout<<"Testing the return and removal of the predecessor when it's the first of the set, here's the set: " <<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  testRemovePredecessorFirst = false;
  int value = limitsetlist1.PredecessorNRemove(10);
  testRemovePredecessorFirst = (19 == limitsetlist1.Min() && value == 8);
  stampaRisultati("Removing the second value of the set", testRemovePredecessorFirst);
  cout<<"Removing the predecessor of " <<value <<", that was the second element of the set" <<endl;
  cout<<"New min of the set should be 19, actual min of the set: " <<limitsetlist1.Min();
  allPassed &= testRemovePredecessorFirst;

  limitsetlist1.Clear();

  cout<<"Testing successor with an empty set, reference value: 5"<<endl;
  bool testSuccessorEmpty = false;
  try{
    limitsetlist1.Successor(5);
  } catch (length_error & e){
    testSuccessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the successor of any value with an empty set ", testSuccessorEmpty);
  allPassed &= testSuccessorEmpty;

  cout<<"Testing the removal of successor for value 5 with an empty set"<<endl;
  bool testRemoveSuccessorEmpty = false;
  try{
    limitsetlist1.RemoveSuccessor(5);
  } catch (length_error & e){
    testRemoveSuccessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the successor of any value with an empty set ", testRemoveSuccessorEmpty);
  allPassed &= testRemoveSuccessorEmpty;

  cout<<"Testing the removal and returnal of successor for value 5 with an empty set"<<endl;
  bool testSuccessorNRemoveEmpty = false;
  try{
    limitsetlist1.SuccessorNRemove(5);
  } catch (length_error & e){
    testSuccessorNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the successor of any value with an empty set ", testSuccessorNRemoveEmpty);
  allPassed &= testSuccessorNRemoveEmpty;

  cout<<"Testing successor of value 5 with every value in the set < 5,, here's the set: "<<endl;
  bool testSuccessorNotExisting = false;
  limitsetlist1.Insert(-1); limitsetlist1.Insert(-5); limitsetlist1.Insert(3); limitsetlist1.Insert(4); limitsetlist1.Insert(0);
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  try{
    limitsetlist1.Successor(5);
  } catch (length_error & e){
    testSuccessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to find any successor for value: 5 ", testSuccessorNotExisting);
  allPassed &= testSuccessorNotExisting;

  cout<<"Testing the removal of successor for value 5 every value in the set < 5, here's the set: "<<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testRemoveSuccessorNotExisting = false;
  try{
    limitsetlist1.RemoveSuccessor(5);
  } catch (length_error & e){
    testRemoveSuccessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the successor for value: 5, it has not been found ", testRemoveSuccessorNotExisting);
  allPassed &= testRemoveSuccessorNotExisting;

  cout<<"Testing the removal and returnal of successor for value 5 every value in the set < 5"<<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testSuccessorNRemoveNotExisting = false;
  try{
    limitsetlist1.SuccessorNRemove(5);
  } catch (length_error & e){
    testSuccessorNRemoveNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the successor for value: 5, it has not been found ", testSuccessorNRemoveNotExisting);
  allPassed &= testSuccessorNRemoveNotExisting;


  limitsetlist1.Clear();
  limitsetlist1.Insert(1);

  cout<<"Testing the removal of the successor when it's the first of the set, here's the set: " <<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testRemoveSuccessorFirst = false;
  limitsetlist1.RemoveSuccessor(0);
  testRemoveSuccessorFirst = limitsetlist1.Empty();
  stampaRisultati("Removing the successor of an out of bounds element of the set", testRemoveSuccessorFirst);
  cout<<"New set should be empty, and it " <<(limitsetlist1.Empty() ? "is" : "isn't");
  allPassed &= testRemoveSuccessorFirst;

  limitsetlist1.Insert(1);

  cout<<"Testing the return and removal of the successor when it's the first of the set, here's the set: " <<endl;
  limitsetlist1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  testRemoveSuccessorFirst = false;
  value = limitsetlist1.SuccessorNRemove(0);
  testRemoveSuccessorFirst = (limitsetlist1.Empty() && value == 1);
  stampaRisultati("Removing first value in the set", testRemoveSuccessorFirst);
  cout<<"Removing the successor of " <<value <<", that was the second element of the set" <<endl;
  cout<<"New set should be empty, and it " <<(limitsetlist1.Empty() ? "is" : "isn't");
  allPassed &= testRemoveSuccessorFirst;
  
  cout<<"End of the set list limit cases test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCostruttoriSetVec(auto genInt, auto genChar, auto genReal){
  cout << "Testing SetVec Constructors" << endl;
  bool allPassed = true;
  cout <<"-Default Constructor-"<<endl;
  lasd::SetVec<int> setvec1;
  bool defaultSetVecConstructorInt = (setvec1.Size() == 0 && setvec1.Empty());
  stampaRisultati("Default SetVec constructor int", defaultSetVecConstructorInt);
  cout<<"Expected size: 0, Actual size: "<<setvec1.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<setvec1.Empty()<<endl;
  allPassed &= defaultSetVecConstructorInt;

  lasd::SetVec<string> setvec2;
  bool defaultSetVecConstructorString = (setvec2.Size() == 0 && setvec2.Empty());
  stampaRisultati("Default SetVec constructor string", defaultSetVecConstructorString);
  cout<<"Expected size: 0, Actual size: "<<setvec2.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<setvec2.Empty()<<endl;
  allPassed &= defaultSetVecConstructorString;

  lasd::SetVec<double> setvec3;
  bool defaultSetVecConstructorDouble = (setvec3.Size() == 0 && setvec3.Empty());
  stampaRisultati("Default SetVec constructor double", defaultSetVecConstructorDouble);
  cout<<"Expected size: 0, Actual size: "<<setvec3.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<setvec3.Empty()<<endl;
  allPassed &= defaultSetVecConstructorDouble;

  cout<<"-TraversableContainer constructor-"<<endl;
  lasd::List<int> list1;
  int randomNumber = 0;
  while (list1.Size() < 5){
    randomNumber = genInt();
    while (list1.Exists(randomNumber)){
      randomNumber = genInt();
    }
    list1.InsertAtBack(randomNumber);
  }

  lasd::List<string> list2;
  string randomString = "";
  while (list2.Size() < 5){
    randomString = generaStringaCasuale(genChar);
    while (list2.Exists(randomString)){
      randomString = generaStringaCasuale(genChar);
    }
    list2.InsertAtBack(randomString);
  }

  lasd::List<double> list3;
  double randomDouble = 0.0;
  while (list3.Size() < 5){
    randomDouble = genReal();
    while (list3.Exists(randomDouble)){
      randomDouble = genReal();
    }
    list3.InsertAtBack(randomDouble);
  }


  lasd::SetVec<int> setvec4(list1);
  bool TraversableContainerSetVecConstructorInt = (setvec4.Size() == 5 && !setvec4.Empty());
  stampaRisultati("TraversableContainer SetVec constructor int", TraversableContainerSetVecConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<setvec4.Size()<<endl;
  cout<<"  -Expected non-empty set list, Actual emptiness: "<<setvec4.Empty()<<endl;
  allPassed &= TraversableContainerSetVecConstructorInt;

  lasd::SetVec<string> setvec5(list2);
  bool TraversableContainerSetVecConstructorString = (setvec5.Size() == 5 && !setvec5.Empty());
  stampaRisultati("TraversableContainer SetVec constructor string", TraversableContainerSetVecConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<setvec5.Size()<<endl;
  cout<<"  -Expected non-empty set list, Actual emptiness: "<<setvec5.Empty()<<endl;
  allPassed &= TraversableContainerSetVecConstructorString;

  lasd::SetVec<double> setvec6(list3);
  bool TraversableContainerSetVecConstructorDouble = (setvec6.Size() == 5 && !setvec6.Empty());
  stampaRisultati("TraversableContainer SetVec constructor double", TraversableContainerSetVecConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<setvec6.Size()<<endl;
  cout<<"  -Expected non-empty set list, Actual emptiness: "<<setvec6.Empty()<<endl;
  allPassed &= TraversableContainerSetVecConstructorDouble;

  bool elementsCorrectInt = true;
  for (ulong index = 0; index < setvec4.Size(); index++) {
    if (!list1.Exists(setvec4[index])){
      elementsCorrectInt = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- int (content)", elementsCorrectInt);
  cout << "  - Expected elements: ";
  list1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setvec4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectInt);

  bool elementsCorrectString = true;
  for (ulong index = 0; index < setvec5.Size(); index++) {
    if (!list2.Exists(setvec5[index])){
      elementsCorrectString = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- string (content)", elementsCorrectString);
  cout << "  - Expected elements: ";
  list2.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setvec5.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectString);

  bool elementsCorrectDouble = true;
  for (ulong index = 0; index < setvec6.Size(); index++) {
    if (!list3.Exists(setvec6[index])){
      elementsCorrectDouble = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- double (content)", elementsCorrectDouble);
  cout << "  - Expected elements: ";
  list3.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setvec6.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDouble);

  lasd::SetVec<int> setvec14(std::move(list1));
  bool MappableContainerConstructorInt = (setvec14.Size() == 5 && !setvec14.Empty());
  stampaRisultati("MappableContainer setlist constructor int", MappableContainerConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<setvec14.Size()<<endl;
  cout<<"  -Expected non-empty set, Actual emptiness: "<<setvec14.Empty()<<endl;
  allPassed &= MappableContainerConstructorInt;

  lasd::SetVec<string> setvec15(std::move(list2));
  bool MappableContainerConstructorString = (setvec15.Size() == 5 && !setvec15.Empty());
  stampaRisultati("MappableContainer setlist constructor string", MappableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<setvec15.Size()<<endl;
  cout<<"  -Expected non-empty set, Actual emptiness: "<<setvec15.Empty()<<endl;
  allPassed &= MappableContainerConstructorString;

  lasd::SetVec<double> setvec16(std::move(list3));
  bool MappableContainerConstructorDouble = (setvec16.Size() == 5 && !setvec16.Empty());
  stampaRisultati("MappableContainer Vector constructor double ", MappableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<setvec16.Size()<<endl;
  cout<<"  -Expected non-empty set, Actual emptiness: "<<setvec16.Empty()<<endl;
  allPassed &= MappableContainerConstructorDouble;

  cout<<"-Copy constructor-"<<endl;
  lasd::SetVec<int> setvec7(setvec4);
  bool copySetVecConstructorInt = (setvec7.Size() == setvec4.Size());
  stampaRisultati("-Copy constructor- SetVec constructor int", copySetVecConstructorInt);
  cout << "  -Expected size: " << setvec4.Size() << " Actual size: " << setvec7.Size() <<endl;
  cout << "  -Identical elements: " << (setvec7 == setvec4 ? "true" : "false") << endl;
  allPassed &= copySetVecConstructorInt;

  lasd::SetVec<string> setvec8(setvec5);
  bool copySetVecConstructorString = (setvec8.Size() == setvec5.Size());
  stampaRisultati("-Copy constructor- SetVec constructor string", copySetVecConstructorString);
  cout << "  -Expected size: " << setvec5.Size() << " Actual size: " << setvec8.Size() <<endl;
  cout << "  -Identical elements: " << (setvec8 == setvec5 ? "true" : "false") << endl;
  allPassed &= copySetVecConstructorString;

  lasd::SetVec<double> setvec9(setvec6);
  bool copySetVecConstructorDouble = (setvec9.Size() == setvec6.Size());
  stampaRisultati("-Copy constructor- SetVec constructor double", copySetVecConstructorDouble);
  cout << "  -Expected size: " << setvec6.Size() << " Actual size: " << setvec9.Size() <<endl;
  cout << "  -Identical elements: " << (setvec9 == setvec6 ? "true" : "false") << endl;
  allPassed &= copySetVecConstructorDouble;

  bool elementsCorrectIntCopy = true;
  for (ulong index = 0; index < setvec7.Size(); index++) {
    if (setvec7[index] != setvec4[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- int (content)", elementsCorrectIntCopy);
  cout << "  - Expected elements: ";
  setvec4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setvec7.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectIntCopy);

  bool elementsCorrectStringCopy = true;
  for (ulong index = 0; index < setvec8.Size(); index++) {
    if (setvec8[index] != setvec5[index]){
      elementsCorrectStringCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- string (content)", elementsCorrectStringCopy);
  cout << "  - Expected elements: ";
  setvec5.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setvec8.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectStringCopy);

  bool elementsCorrectDoubleCopy = true;
  for (ulong index = 0; index < setvec9.Size(); index++) {
    if (setvec9[index] != setvec6[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- double (content)", elementsCorrectDoubleCopy);
  cout << "  - Expected elements: ";
  setvec6.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  setvec9.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDoubleCopy);

  cout<<"-Move constructor-"<<endl;
  lasd::SetVec<int> movesetvec1(move(setvec4));
  bool moveConstructorTestInt = (movesetvec1.Size() == 5 && setvec4.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestInt);
  cout << "  - Expected size of setvec: 5, Actual size: " << movesetvec1.Size() << endl;
  cout << "  - Expected size of original setvec: 0, Actual size: " << setvec4.Size() << endl;
  cout << "  - Elements of new setvec: ";
  movesetvec1.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestInt;

  lasd::SetVec<string> movesetvec2(move(setvec5));
  bool moveConstructorTestString = (movesetvec2.Size() == 5 && setvec5.Size() == 0);
  stampaRisultati("-Move constructor- string", moveConstructorTestString);
  cout << "  - Expected size of setvec: 5, Actual size: " << movesetvec2.Size() << endl;
  cout << "  - Expected size of original setvec: 0, Actual size: " << setvec5.Size() << endl;
  cout << "  - Elements of new setvec: ";
  movesetvec2.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestString;

  lasd::SetVec<double> movesetvec3(move(setvec6));
  bool moveConstructorTestDouble = (movesetvec3.Size() == 5 && setvec6.Size() == 0);
  stampaRisultati("-Move constructor- double", moveConstructorTestDouble);
  cout << "  - Expected size of setvec: 5, Actual size: " << movesetvec3.Size() << endl;
  cout << "  - Expected size of original setvec: 0, Actual size: " << setvec6.Size() << endl;
  cout << "  - Elements of new setvec: ";
  movesetvec3.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestDouble;
  cout<<"End of the setvec constructors test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testFunzioniSetVec(){
  cout << "Testing SetVec Functions without testing limit cases" << endl;
  cout << "Not testing every datatype in this test, tests will be limited to the int type"<<endl;
  cout << "Implicitly tested functions while testing the constructors: "<<endl;
  cout << " -PreOrderTraverse "<<endl;
  cout << " -operator =="<<endl;
  cout << " -operator[] in reading"<<endl;
  cout << " -Exists"<<endl;
  cout << " -Copy Insert (even though the insertion of duplicate elements has not been tested)"<<endl;
  cout << " -Resize function will also be tested implicitly because it gets called in Insert and Remove functions"<<endl;
  bool allPassed = true;

  cout << "Testing the duplicate insertion"<<endl;
  cout<<"Trying to insert the values: 8 3 4 5 8 5 3"<<endl;
  lasd::SetVec<int> setvec1;
  int array[] = {8, 3, 4, 5, 8, 5, 3};
  for (ulong index = 0; index < 7; index++){
    setvec1.Insert(array[index]);
  } 
  bool testCopyInsertAndDupes = (setvec1.Size() == 4);
  for (ulong index = 0; index < setvec1.Size()-1; index++){
    for (ulong index2 = index+1; index2<setvec1.Size(); index2++){
      if (setvec1[index] == setvec1[index2]){
        testCopyInsertAndDupes = false;
        break;
      }
    }
  }
  stampaRisultati("Duplicates copy insert test ", testCopyInsertAndDupes);
  cout<<"  -Set size should be 4, Actual size: "<<setvec1.Size()<<endl;
  cout<<"  -Set elements should be: 3 4 5 8, Actual elements: ";
  setvec1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyInsertAndDupes;

  cout<<"Testing copy assignment"<<endl;
  lasd::SetVec<int> setvec2;
  setvec2 = setvec1;
  bool testCopyAssignment = (setvec1 == setvec2);
  stampaRisultati("Copy assignment ", testCopyAssignment);
  cout<<"  -Size should be: "<<setvec1.Size()<<" Actual size is: "<<setvec2.Size()<<endl;
  cout<<"  -Elements should be: ";
  setvec1.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual elements: ";
  setvec2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyAssignment;

  cout<<"Testing move assignment, also general Traverse will be tested"<<endl;
  setvec2.Clear();
  setvec2 = move(setvec1);
  bool testMoveAssignment = (setvec1.Empty());
  stampaRisultati("Move assignment ", testMoveAssignment);
  cout<<"  -Size should be: 4 Actual size is: "<<setvec2.Size()<<endl;
  cout<<"  -Other list should be empty, Other emptiness: "<<setvec1.Empty()<<endl;
  cout<<"  -Elements: ";
  setvec2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testMoveAssignment;

  cout<<"Testing Min, RemoveMin and MinNRemove"<<endl;
  int min = setvec2.Min();
  bool testMin = (min == setvec2[0]);
  stampaRisultati("Min ", testMin);
  cout<<"  -Min should be: "<<setvec2[0]<<" Actual min: "<<min<<endl;

  setvec2.RemoveMin();
  bool testRemoveMin = (setvec2.Min() == setvec2[0] && setvec2.Size() == 3);
  stampaRisultati("Remove min ", testRemoveMin);
  cout<< "  -New min should be: "<<setvec2[0]<<" Actual min: "<<setvec2.Min()<<endl;
  cout<< "  -New size should be 3, Actual size: "<<setvec2.Size()<<endl;

  lasd::SetVec<int> setvec3(setvec2);
  min = setvec2.MinNRemove();
  bool testMinNRemove = (setvec3[0] == min && setvec2.Size() == 2);
  stampaRisultati("Min and remove ", testMinNRemove);
  cout<< "  -New min should be: "<<setvec2[0]<<" Actual min: "<<setvec2.Min()<<endl;
  cout<< "  -New size should be 2, Actual size: "<<setvec2.Size()<<endl;
  cout<< "  -Removed min should be: "<<setvec3[0]<<" Actual removed min: "<<min<<endl;
  allPassed &= testMin & testRemoveMin & testMinNRemove;

  cout<<"Testing Max, RemoveMax and MaxNRemove"<<endl;
  int max = setvec3.Max();
  bool testMax2 = (max == setvec3[setvec3.Size()-1]);
  stampaRisultati("Max ", testMax2);
  cout<<"  -Max should be: "<<setvec3[setvec3.Size()-1]<<" Actual max: "<<max<<endl;

  setvec3.RemoveMax();
  bool testRemoveMax = (setvec3.Max() == setvec3[setvec3.Size()-1] && setvec3.Size() == 2);
  stampaRisultati("Remove max ", testRemoveMax);
  cout<< "  -New max should be: "<<setvec3[setvec3.Size()-1]<<" Actual max: "<<setvec3.Max()<<endl;
  cout<< "  -New size should be 2, Actual size: "<<setvec3.Size()<<endl;

  lasd::SetVec<int> setvec4(setvec3);
  max = setvec3.MaxNRemove();
  bool testMaxNRemove = (setvec4[setvec4.Size()-1] == max && setvec3.Size() == 1);
  stampaRisultati("Max and remove ", testMaxNRemove);
  cout<< "  -New max should be: "<<setvec3[setvec3.Size()-1]<<" Actual max: "<<setvec3.Max()<<endl;
  cout<< "  -New size should be 1, Actual size: "<<setvec3.Size()<<endl;
  cout<< "  -Removed max should be: "<<setvec4[setvec4.Size()-1]<<" Actual removed max: "<<max<<endl;
  allPassed &= testMax2 & testRemoveMax & testMaxNRemove;

  cout<<"Testing Predecessor, RemovePredecessor and PredecessorNRemove"<<endl;
  cout<<"Print of the set for clarification: "<<endl;
  setvec3.Clear();
  setvec3.Insert(8); setvec3.Insert(5); setvec3.Insert(22); setvec3.Insert(16); setvec3.Insert(7); setvec3.Insert(6);
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing predecessor for value: 18"<<endl;
  int pred = setvec3.Predecessor(18);
  bool testPredecessor = (pred == 16);
  stampaRisultati("Predecessor for value 18 ", testPredecessor);
  cout<<"  -Predecessor for value 18 must be 16, Actual predecessor: "<<pred<<endl;
  allPassed &= testPredecessor;

  cout<<"Testing removal of predecessor for value: 18"<<endl;
  setvec4.Clear();
  setvec4.Insert(8); setvec4.Insert(5); setvec4.Insert(22); setvec4.Insert(7); setvec4.Insert(6);
  setvec3.RemovePredecessor(18);
  bool testRemovePredecessor = (setvec3 == setvec4 && setvec3.Size() == 5);
  stampaRisultati("Removal of predecessor for value: 18 ", testRemovePredecessor);
  cout<<"  -Set should be: ";
  setvec4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testRemovePredecessor;

  setvec3.Insert(16);
  cout<<"Testing removal and returnal of predecessor for value: 18"<<endl;
  cout<<"Predecessor removed from the above test has been inserted back in the set"<<endl;
  int pred2 = setvec3.PredecessorNRemove(18);
  bool testPredecessorNRemove = (pred == pred2 && setvec3.Size() == 5);
  stampaRisultati("Predecessor and removal of predecessor for value: 18 ", testPredecessorNRemove);
  cout<<"  -Set should be: ";
  setvec4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Removed predecessor should be: "<<pred<<" Actual removed predecessor: "<<pred2<<endl;
  allPassed &= testPredecessorNRemove;

  cout<<"Testing Successor, RemoveSuccessor and SuccessorNRemove"<<endl;
  cout<<"Print of the set for clarification: "<<endl;
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing successor for value: 7"<<endl;
  int succ = setvec3.Successor(7);
  bool testSuccecessor = (succ == 8);
  stampaRisultati("Successor for value 7 ", testSuccecessor);
  cout<<"  -Successor for value 7 must be 8, Actual successor: "<<succ<<endl;
  allPassed &= testSuccecessor;

  cout<<"Testing removal of successor for value: 18"<<endl;
  setvec3.RemoveSuccessor(7);
  setvec4.Remove(8);
  bool testRemoveSuccessor = (setvec3 == setvec4 && setvec3.Size() == 4);
  stampaRisultati("Removal of successor for value: 7 ", testRemoveSuccessor);
  cout<<"  -Set should be: ";
  setvec4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testRemoveSuccessor;

  setvec3.Insert(8);
  cout<<"Testing removal and returnal of successor for value: 7"<<endl;
  cout<<"Successor removed from the above test has been inserted back in the set"<<endl;
  int succ2 = setvec3.SuccessorNRemove(7);
  bool testSuccessorNRemove = (succ == succ2 && setvec3.Size() == 4);
  stampaRisultati("Successor and removal of successor for value: 7 ", testSuccessorNRemove);
  cout<<"  -Set should be: ";
  setvec4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual set: ";
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Removed successor should be: "<<succ<<" Actual removed successor: "<<succ2<<endl;
  allPassed &= testSuccessorNRemove;

  cout<<"Testing Exists"<<endl;
  cout<<"Print of the set for clarification"<<endl;
  setvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing existance of value 6 and non-existance of value 1"<<endl;
  bool Exists = (setvec3.Exists(6));
  bool NotExists = (!setvec3.Exists(1));
  stampaRisultati("Existstance of value 6 ", Exists);
  cout<<"  -Value 6 should exist, and it "<<(setvec3.Exists(6) ? "Exists" : "Doesn't Exist")<<endl;
  stampaRisultati("Non-existance of value 1 ", NotExists);
  cout<<"  -Value 1 should exist, and it "<<(setvec3.Exists(1) ? "Exists" : "Doesn't Exist")<<endl;
  allPassed &= Exists & NotExists;

  cout<<"Testing Front and Back"<<endl;
  min = setvec3.Min(); max = setvec3.Max();
  bool testBack = (max == setvec3.Back());
  bool testFront = (min == setvec3.Front());
  stampaRisultati("Front of the set ", testFront);
  cout<<"  -Front of the set should be its minimum value, so: "<<min<<" , Actual front of the set: "<<setvec3.Front()<<endl;
  stampaRisultati("Back of the set ", testBack);
  cout<<"  -Back of the set should be its maximum value, so: "<<max<<" ,Actual back of the set: "<<setvec3.Back()<<endl;
  allPassed &= testBack & testFront;

  cout<<"Testing PostOrderTraverse"<<endl;
  cout<<"Output should be: 22 7 6 5, Actual output: ";
  setvec3.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"PreOrderFold Test with int"<<endl;
  int sum = setvec3.PreOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PreOrderFoldTest = (sum == 40);
  stampaRisultati("Pre order fold test int", PreOrderFoldTest);
  cout<<"  -Expected sum should be: 40, Actual sum is: "<<sum<<endl;
  allPassed &= PreOrderFoldTest;

  cout<<"Testing Remove and reinserting"<<endl;
  bool RemoveTest = setvec3.Remove(7);
  stampaRisultati("Remove test int", RemoveTest);
  allPassed &= RemoveTest;
  bool InsertTest = setvec3.Insert(7);
  stampaRisultati("Insert test int", RemoveTest);
  allPassed &= InsertTest;
  
  lasd::SetVec<string> setvecstring;
  setvecstring.Insert("A"); setvecstring.Insert("B"); setvecstring.Insert("C"); setvecstring.Insert("D"); setvecstring.Insert("E");
  cout<<"PreOrderFold Test with string"<<endl;
  string concat = setvecstring.PreOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PreOrderFoldTestString = (concat == "ABCDE");
  stampaRisultati("Pre order fold test string", PreOrderFoldTestString);
  cout<<"  -Expected concatenation should be: ABCDE, Actual concatenation is: "<<concat<<endl;
  allPassed &= PreOrderFoldTestString;

  cout<<"PostOrderFold Test with int"<<endl;
  sum = setvec3.PostOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PostOrderFoldTest = (sum == 40);
  stampaRisultati("Post order fold test int", PostOrderFoldTest);
  cout<<"  -Expected sum should be: 40, Actual sum is: "<<sum<<endl;
  allPassed &= PostOrderFoldTest;

  cout<<"PostOrderFold Test with string"<<endl;
  concat = setvecstring.PostOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PostOrderFoldTestString = (concat == "EDCBA");
  stampaRisultati("Post order fold test string", PostOrderFoldTestString);
  cout<<"  -Expected concatenation should be: EDCBA, Actual concatenation is: "<<concat<<endl;
  allPassed &= PostOrderFoldTestString;
  cout<<"End of the setvec functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;

  return allPassed;
}

bool testCasiLimiteSetVec(){
  cout << "Testing SetVec limit cases" << endl;
  cout << "Here we are testing if exceptions are handled correctly and other cases" << endl;
  bool allPassed = true;

  lasd::SetVec<int> emptysetvec;
  lasd::SetVec<int> setvec;
  cout<<"Testing access to a certain index with an empty set"<<endl;
  bool emptyAccessTest = false;
  try{
    emptysetvec[5];
  } catch(out_of_range & e){
    emptyAccessTest = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access at index 5 of an empty set ", emptyAccessTest);
  allPassed &= emptyAccessTest;

  cout<<"Testing remove with an empty set"<<endl;
  bool testRemoveEmpty = false;
  try {
    emptysetvec.Remove(10);
  } catch (length_error & e){
    testRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not remove 10 in an empty set ", testRemoveEmpty);
  allPassed &= testRemoveEmpty;

  cout<<"Testing access to the minimum value with an empty set"<<endl;
  bool testMinEmpty = false;
  try {
    emptysetvec.Min();
  } catch (length_error & e){
    testMinEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access the minimum value of an empty set ", testMinEmpty);
  allPassed &= testMinEmpty;

  cout<<"Testing removal of the minimum value with an empty set"<<endl;
  bool testRemoveMinEmpty = false;
  try {
    emptysetvec.RemoveMin();
  } catch (length_error & e){
    testRemoveMinEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not remove the minimum value of an empty set ", testRemoveMinEmpty);
  allPassed &= testRemoveMinEmpty;

  cout<<"Testing access and removal of the minimum value with an empty set"<<endl;
  bool testMinNRemoveEmpty = false;
  try {
    emptysetvec.MinNRemove();
  } catch (length_error & e){
    testMinNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access the minimum value of an empty set ", testMinNRemoveEmpty);
  allPassed &= testMinNRemoveEmpty;

  cout<<"Testing access to the maximum value with an empty set"<<endl;
  bool testMaxEmpty = false;
  try {
    emptysetvec.Max();
  } catch (length_error & e){
    testMaxEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access the maximum value of an empty set ", testMaxEmpty);
  allPassed &= testMaxEmpty;

  cout<<"Testing removal of the maximum value with an empty set"<<endl;
  bool testRemoveMaxEmpty = false;
  try {
    emptysetvec.RemoveMax();
  } catch (length_error & e){
    testRemoveMaxEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not remove the minimum value of an empty set ", testRemoveMaxEmpty);
  allPassed &= testRemoveMaxEmpty;

  cout<<"Testing access and removal of the maximum value with an empty set"<<endl;
  bool testMaxNRemoveEmpty = false;
  try {
    emptysetvec.MaxNRemove();
  } catch (length_error & e){
    testMaxNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access the maximum value of an empty set ", testMaxNRemoveEmpty); 
  allPassed &= testMaxNRemoveEmpty;

  cout<<"Testing predecessor with an empty set, reference value: 5"<<endl;
  bool testPredecessorEmpty = false;
  try{
    emptysetvec.Predecessor(5);
  } catch (length_error & e){
    testPredecessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the predecessor of any value with an empty set ", testPredecessorEmpty);
  allPassed &= testPredecessorEmpty;

  cout<<"Testing the removal of predecessor for value 5 with an empty set"<<endl;
  bool testRemovePredecessorEmpty = false;
  try{
    emptysetvec.RemovePredecessor(5);
  } catch (length_error & e){
    testRemovePredecessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the predecessor of any value with an empty set ", testPredecessorEmpty);
  allPassed &= testRemovePredecessorEmpty;

  cout<<"Testing the removal and returnal of predecessor for value 5 with an empty set"<<endl;
  bool testPredecessorNRemoveEmpty = false;
  try{
    emptysetvec.PredecessorNRemove(5);
  } catch (length_error & e){
    testPredecessorNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the predecessor of any value with an empty set ", testPredecessorNRemoveEmpty);
  allPassed &= testPredecessorNRemoveEmpty;

  cout<<"Testing successor with an empty set, reference value: 5"<<endl;
  bool testSuccessorEmpty = false;
  try{
    emptysetvec.Successor(5);
  } catch (length_error & e){
    testSuccessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to access the successor of any value with an empty set ", testSuccessorEmpty);
  allPassed &= testSuccessorEmpty;

  cout<<"Testing the removal of successor for value 5 with an empty set"<<endl;
  bool testRemoveSuccessorEmpty = false;
  try{
    emptysetvec.RemoveSuccessor(5);
  } catch (length_error & e){
    testRemoveSuccessorEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the successor of any value with an empty set ", testRemoveSuccessorEmpty);
  allPassed &= testRemoveSuccessorEmpty;

  cout<<"Testing the removal and returnal of successor for value 5 with an empty set"<<endl;
  bool testSuccessorNRemoveEmpty = false;
  try{
    emptysetvec.SuccessorNRemove(5);
  } catch (length_error & e){
    testSuccessorNRemoveEmpty = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the successor of any value with an empty set ", testSuccessorNRemoveEmpty);
  allPassed &= testSuccessorNRemoveEmpty;

  cout<<"Now testing things with a non-empty set, set of reference: ";
  setvec.Insert(7); setvec.Insert(34); setvec.Insert(32); setvec.Insert(9); setvec.Insert(22);
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"Testing predecessor of value 5 with every value in the set > 5, here's the set: "<<endl;
  bool testPredecessorNotExisting = false;
  try{
    setvec.Predecessor(5);
  } catch (length_error & e){
    testPredecessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to find any predecessors for value: 5 ", testPredecessorNotExisting);
  allPassed &= testPredecessorNotExisting;

  cout<<"Testing the removal of predecessor for value 5 every value in the set > 5, here's the set: "<<endl;
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testRemovePredecessorNotExisting = false;
  try{
    setvec.RemovePredecessor(5);
  } catch (length_error & e){
    testRemovePredecessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the predecessor for value: 5, it has not been found ", testRemovePredecessorNotExisting);
  allPassed &= testRemovePredecessorNotExisting;

  cout<<"Testing the removal and returnal of predecessor for value 5 every value in the set > 5, here's the set: "<<endl;
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testPredecessorNRemoveNotExisting = false;
  try{
    setvec.PredecessorNRemove(5);
  } catch (length_error & e){
    testPredecessorNRemoveNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the predecessor for value: 5, it has not been found ", testPredecessorNRemoveNotExisting);
  allPassed &= testPredecessorNRemoveNotExisting;

  cout<<"Testing predecessor of value 35 with every value in the set < 35, here's the set:";
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testSuccessorNotExisting = false;
  try{
    setvec.Successor(35);
  } catch (length_error & e){
    testSuccessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to find any successor for value: 35 ", testSuccessorNotExisting);
  allPassed &= testSuccessorNotExisting;

  cout<<"Testing the removal of successor for value 35 every value in the set < 35, here's the set: "<<endl;
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testRemoveSuccessorNotExisting = false;
  try{
    setvec.RemoveSuccessor(35);
  } catch (length_error & e){
    testRemoveSuccessorNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove the successor for value: 35, it has not been found ", testRemoveSuccessorNotExisting);
  allPassed &= testRemoveSuccessorNotExisting;

  cout<<"Testing the removal and returnal of successor for value 35 every value in the set < 35"<<endl;
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  bool testSuccessorNRemoveNotExisting = false;
  try{
    setvec.SuccessorNRemove(35);
  } catch (length_error & e){
    testSuccessorNRemoveNotExisting = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Not able to remove and return the successor for value: 35, it has not been found ", testSuccessorNRemoveNotExisting);
  allPassed &= testSuccessorNRemoveNotExisting;

  cout<<"Testing removal of predecessor when it's the first element of the set"<<endl;
  cout<<"So we are trying to remove the predecessor of 8, which is 7 in the set"<<endl;
  lasd::SetVec<int> setvec2(setvec);
  setvec.RemovePredecessor(8);
  cout<<"Set after the removal: ";
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set structure has "<< (setvec[0] == setvec2[1] ? "been preserved" : "not been preserved")<<endl;

  cout<<"Testing removal of predecessor when it's the last element of the set"<<endl;
  cout<<"So we are trying to remove the predecessor of 35, which is 34 in the set"<<endl;
  setvec2 = setvec;
  setvec.RemovePredecessor(35);
  cout<<"Set after the removal: ";
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set structure has "<< (setvec[setvec.Size()-1] == setvec2[setvec2.Size()-2] ? "been preserved" : "not been preserved")<<endl;

  cout<<"Testing removal of successor when it's the first element of the set"<<endl;
  cout<<"So we are trying to remove the successor of 8, which is 9 in the set"<<endl;
  setvec2 = setvec;
  setvec.RemoveSuccessor(8);
  cout<<"Set after the removal: ";
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set structure has "<< (setvec[0] == setvec2[1] ? "been preserved" : "not been preserved")<<endl;

  cout<<"Testing removal of successor when it's the last element of the set"<<endl;
  cout<<"So we are trying to remove the predecessor of 31, which is 32 in the set"<<endl;
  setvec2 = setvec;
  setvec.RemoveSuccessor(31);
  cout<<"Set after the removal: ";
  setvec.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set structure has "<< (setvec[setvec.Size()-1] == setvec2[setvec2.Size()-2] ? "been preserved" : "not been preserved")<<endl;

  cout<<"Testing MinNRemove and RemoveMin in a single element set"<<endl;
  lasd::SetVec<int> singleSet;
  singleSet.Insert(1);
  singleSet.MinNRemove();
  cout<<"Set after the removal: ";
  singleSet.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set has "<< (singleSet.Empty() ? "been emptied" : "not been emptied")<<endl;

  singleSet.Insert(1);
  singleSet.RemoveMin();
  cout<<"Set after the removal: ";
  singleSet.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set has "<< (singleSet.Empty() ? "been emptied" : "not been emptied")<<endl;

  cout<<"Testing MaxNRemove and RemoveMax in a single element set"<<endl;
  singleSet.Clear();
  singleSet.Insert(1);
  singleSet.MaxNRemove();
  cout<<"Set after the removal: ";
  singleSet.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set has "<< (singleSet.Empty() ? "been emptied" : "not been emptied")<<endl;

  singleSet.Insert(1);
  singleSet.RemoveMax();
  cout<<"Set after the removal: ";
  singleSet.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"The set has "<< (singleSet.Empty() ? "been emptied" : "not been emptied")<<endl;

  cout<<"End of the setvec limit cases test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCostruttoriHeapVec(auto genChar, auto genInt, auto genReal){
  cout << "Testing HeapVec Constructors" << endl;
  bool allPassed = true;
  cout <<"-Default Constructor-"<<endl;
  lasd::HeapVec<int> heapvec1;
  bool defaultHeapVecConstructorInt = (heapvec1.Size() == 0 && heapvec1.Empty());
  stampaRisultati("Default HeapVec constructor int", defaultHeapVecConstructorInt);
  cout<<"Expected size: 0, Actual size: "<<heapvec1.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<heapvec1.Empty()<<endl;
  allPassed &= defaultHeapVecConstructorInt;

  lasd::HeapVec<string> heapvec2;
  bool defaultHeapVecConstructorString = (heapvec2.Size() == 0 && heapvec2.Empty());
  stampaRisultati("Default HeapVec constructor string", defaultHeapVecConstructorString);
  cout<<"Expected size: 0, Actual size: "<<heapvec2.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<heapvec2.Empty()<<endl;
  allPassed &= defaultHeapVecConstructorString;

  lasd::HeapVec<double> heapvec3;
  bool defaultHeapVecConstructorDouble = (heapvec3.Size() == 0 && heapvec3.Empty());
  stampaRisultati("Default HeapVec constructor double", defaultHeapVecConstructorDouble);
  cout<<"Expected size: 0, Actual size: "<<heapvec3.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<heapvec3.Empty()<<endl;
  allPassed &= defaultHeapVecConstructorDouble;

  cout<<"-TraversableContainer constructor-"<<endl;
  lasd::List<int> list1;
  int randomNumber = 0;
  while (list1.Size() < 5){
    randomNumber = genInt();
    while (list1.Exists(randomNumber)){
      randomNumber = genInt();
    }
    list1.InsertAtBack(randomNumber);
  }

  lasd::List<string> list2;
  string randomString = "";
  while (list2.Size() < 5){
    randomString = generaStringaCasuale(genChar);
    while (list2.Exists(randomString)){
      randomString = generaStringaCasuale(genChar);
    }
    list2.InsertAtBack(randomString);
  }

  lasd::List<double> list3;
  double randomDouble = 0.0;
  while (list3.Size() < 5){
    randomDouble = genReal();
    while (list3.Exists(randomDouble)){
      randomDouble = genReal();
    }
    list3.InsertAtBack(randomDouble);
  }

  lasd::HeapVec<int> heapvec4(list1);
  bool TraversableContainerHeapVecConstructorInt = (heapvec4.Size() == 5 && !heapvec4.Empty());
  stampaRisultati("TraversableContainer HeapVec constructor int", TraversableContainerHeapVecConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<heapvec4.Size()<<endl;
  cout<<"  -Expected non-empty heap list, Actual emptiness: "<<heapvec4.Empty()<<endl;
  allPassed &= TraversableContainerHeapVecConstructorInt;

  lasd::HeapVec<string> heapvec5(list2);
  bool TraversableContainerHeapVecConstructorString = (heapvec5.Size() == 5 && !heapvec5.Empty());
  stampaRisultati("TraversableContainer HeapVec constructor string", TraversableContainerHeapVecConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<heapvec5.Size()<<endl;
  cout<<"  -Expected non-empty heap list, Actual emptiness: "<<heapvec5.Empty()<<endl;
  allPassed &= TraversableContainerHeapVecConstructorString;

  lasd::HeapVec<double> heapvec6(list3);
  bool TraversableContainerHeapVecConstructorDouble = (heapvec6.Size() == 5 && !heapvec6.Empty());
  stampaRisultati("TraversableContainer HeapVec constructor double", TraversableContainerHeapVecConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<heapvec6.Size()<<endl;
  cout<<"  -Expected non-empty heap list, Actual emptiness: "<<heapvec6.Empty()<<endl;
  allPassed &= TraversableContainerHeapVecConstructorDouble;

  bool elementsCorrectInt = true;
  for (ulong index = 0; index < heapvec4.Size(); index++) {
    if (!list1.Exists(heapvec4[index])){
      elementsCorrectInt = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- int (content)", elementsCorrectInt);
  cout << "  - Expected elements: ";
  list1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  heapvec4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectInt);

  bool elementsCorrectString = true;
  for (ulong index = 0; index < heapvec5.Size(); index++) {
    if (!list2.Exists(heapvec5[index])){
      elementsCorrectString = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- string (content)", elementsCorrectString);
  cout << "  - Expected elements: ";
  list2.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  heapvec5.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectString);

  bool elementsCorrectDouble = true;
  for (ulong index = 0; index < heapvec6.Size(); index++) {
    if (!list3.Exists(heapvec6[index])){
      elementsCorrectDouble = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- double (content)", elementsCorrectDouble);
  cout << "  - Expected elements: ";
  list3.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  heapvec6.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDouble);

  lasd::HeapVec<int> heapvec14(std::move(list1));
  bool MappableContainerConstructorInt = (heapvec14.Size() == 5 && !heapvec14.Empty());
  stampaRisultati("MappableContainer heapvec constructor int", MappableContainerConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<heapvec14.Size()<<endl;
  cout<<"  -Expected non-empty heap, Actual emptiness: "<<heapvec14.Empty()<<endl;
  allPassed &= MappableContainerConstructorInt;

  lasd::HeapVec<string> heapvec15(std::move(list2));
  bool MappableContainerConstructorString = (heapvec15.Size() == 5 && !heapvec15.Empty());
  stampaRisultati("MappableContainer heapvec constructor string", MappableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<heapvec15.Size()<<endl;
  cout<<"  -Expected non-empty heap, Actual emptiness: "<<heapvec15.Empty()<<endl;
  allPassed &= MappableContainerConstructorString;

  lasd::HeapVec<double> heapvec16(std::move(list3));
  bool MappableContainerConstructorDouble = (heapvec16.Size() == 5 && !heapvec16.Empty());
  stampaRisultati("MappableContainer Vector constructor double ", MappableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<heapvec16.Size()<<endl;
  cout<<"  -Expected non-empty heap, Actual emptiness: "<<heapvec16.Empty()<<endl;
  allPassed &= MappableContainerConstructorDouble;

  cout<<"-Copy constructor-"<<endl;
  lasd::HeapVec<int> heapvec7(heapvec4);
  bool copyHeapVecConstructorInt = (heapvec7.Size() == heapvec4.Size());
  stampaRisultati("-Copy constructor- HeapVec constructor int", copyHeapVecConstructorInt);
  cout << "  -Expected size: " << heapvec4.Size() << " Actual size: " << heapvec7.Size() <<endl;
  cout << "  -Identical elements: " << (heapvec7 == heapvec4 ? "true" : "false") << endl;
  allPassed &= copyHeapVecConstructorInt;

  lasd::HeapVec<string> heapvec8(heapvec5);
  bool copyHeapVecConstructorString = (heapvec8.Size() == heapvec5.Size());
  stampaRisultati("-Copy constructor- HeapVec constructor string", copyHeapVecConstructorString);
  cout << "  -Expected size: " << heapvec5.Size() << " Actual size: " << heapvec8.Size() <<endl;
  cout << "  -Identical elements: " << (heapvec8 == heapvec5 ? "true" : "false") << endl;
  allPassed &= copyHeapVecConstructorString;

  lasd::HeapVec<double> heapvec9(heapvec6);
  bool copyHeapVecConstructorDouble = (heapvec9.Size() == heapvec6.Size());
  stampaRisultati("-Copy constructor- HeapVec constructor double", copyHeapVecConstructorDouble);
  cout << "  -Expected size: " << heapvec6.Size() << " Actual size: " << heapvec9.Size() <<endl;
  cout << "  -Identical elements: " << (heapvec9 == heapvec6 ? "true" : "false") << endl;
  allPassed &= copyHeapVecConstructorDouble;

  bool elementsCorrectIntCopy = true;
  for (ulong index = 0; index < heapvec7.Size(); index++) {
    if (heapvec7[index] != heapvec4[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- int (content)", elementsCorrectIntCopy);
  cout << "  - Expected elements: ";
  heapvec4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  heapvec7.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectIntCopy);

  bool elementsCorrectStringCopy = true;
  for (ulong index = 0; index < heapvec8.Size(); index++) {
    if (heapvec8[index] != heapvec5[index]){
      elementsCorrectStringCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- string (content)", elementsCorrectStringCopy);
  cout << "  - Expected elements: ";
  heapvec5.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  heapvec8.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectStringCopy);

  bool elementsCorrectDoubleCopy = true;
  for (ulong index = 0; index < heapvec9.Size(); index++) {
    if (heapvec9[index] != heapvec6[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- double (content)", elementsCorrectDoubleCopy);
  cout << "  - Expected elements: ";
  heapvec6.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  heapvec9.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDoubleCopy);

  cout<<"-Move constructor-"<<endl;
  lasd::HeapVec<int> moveheapvec1(move(heapvec4));
  bool moveConstructorTestInt = (moveheapvec1.Size() == 5 && heapvec4.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestInt);
  cout << "  - Expected size of heapvec: 5, Actual size: " << moveheapvec1.Size() << endl;
  cout << "  - Expected size of original heapvec: 0, Actual size: " << heapvec4.Size() << endl;
  cout << "  - Elements of new heapvec: ";
  moveheapvec1.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestInt;

  lasd::HeapVec<string> moveheapvec2(move(heapvec5));
  bool moveConstructorTestString = (moveheapvec2.Size() == 5 && heapvec5.Size() == 0);
  stampaRisultati("-Move constructor- string", moveConstructorTestString);
  cout << "  - Expected size of heapvec: 5, Actual size: " << moveheapvec2.Size() << endl;
  cout << "  - Expected size of original heapvec: 0, Actual size: " << heapvec5.Size() << endl;
  cout << "  - Elements of new heapvec: ";
  moveheapvec2.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestString;

  lasd::HeapVec<double> moveheapvec3(move(heapvec6));
  bool moveConstructorTestDouble = (moveheapvec3.Size() == 5 && heapvec6.Size() == 0);
  stampaRisultati("-Move constructor- double", moveConstructorTestDouble);
  cout << "  - Expected size of heapvec: 5, Actual size: " << moveheapvec3.Size() << endl;
  cout << "  - Expected size of original heapvec: 0, Actual size: " << heapvec6.Size() << endl;
  cout << "  - Elements of new heapvec: ";
  moveheapvec3.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestDouble;

  cout<<"End of the heapvec constructors test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testFunzioniHeapVec(){
  cout << "Testing HeapVec Functions without testing limit cases" << endl;
  cout << "Not testing every datatype in this test, tests will be limited to the int type"<<endl;
  cout << "Implicitly tested functions while testing the constructors: "<<endl;
  cout << " -PreOrderTraverse "<<endl;
  cout << " -operator =="<<endl;
  cout << " -operator[] in reading"<<endl;
  cout << " -Exists"<<endl;
  cout << " -Both Heapify"<<endl;
  cout << " -HeapSort"<<endl;
  bool allPassed = true;

  cout<<"Testing copy assignment"<<endl;
  lasd::List<int> list1;
  int number = 2;
  while (list1.Size() < 7){
    list1.InsertAtBack(number);
    number++;
  }
  lasd::HeapVec<int> heapvec1(list1), heapvec2;
  heapvec2 = heapvec1;
  bool testCopyAssignment = (heapvec1 == heapvec2);
  stampaRisultati("Copy assignment ", testCopyAssignment);
  cout<<"  -Size should be: "<<heapvec1.Size()<<" Actual size is: "<<heapvec2.Size()<<endl;
  cout<<"  -Elements should be: ";
  heapvec1.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual elements: ";
  heapvec2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyAssignment;

  cout<<"Testing move assignment, also general Traverse will be tested"<<endl;
  heapvec2.Clear();
  heapvec2 = move(heapvec1);
  bool testMoveAssignment = (heapvec1.Empty());
  stampaRisultati("Move assignment ", testMoveAssignment);
  cout<<"  -Size should be: 4 Actual size is: "<<heapvec2.Size()<<endl;
  cout<<"  -Other list should be empty, Other emptiness: "<<heapvec1.Empty()<<endl;
  cout<<"  -Elements: ";
  heapvec2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testMoveAssignment;

  lasd::HeapVec<int> heapvec3(heapvec2);
  cout<<"Testing Exists"<<endl;
  cout<<"Print of the heap for clarification"<<endl;
  heapvec3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing existance of value 6 and non-existance of value 1"<<endl;
  bool Exists = (heapvec3.Exists(6));
  bool NotExists = (!heapvec3.Exists(1));
  stampaRisultati("Existstance of value 6 ", Exists);
  cout<<"  -Value 6 should exist, and it "<<(heapvec3.Exists(6) ? "Exists" : "Doesn't Exist")<<endl;
  stampaRisultati("Non-existance of value 1 ", NotExists);
  cout<<"  -Value 1 should exist, and it "<<(heapvec3.Exists(1) ? "Exists" : "Doesn't Exist")<<endl;
  allPassed &= Exists & NotExists;

  cout<<"Testing Front and Back"<<endl;
  int front = heapvec3[0];
  int back = heapvec3[heapvec3.Size()-1];
  bool testBack = (back == heapvec3.Back());
  bool testFront = (front == heapvec3.Front());
  stampaRisultati("Front of the heap ", testFront);
  cout<<"  -Front of the heap should be its maximum value, so: "<<front<<" , Actual front of the heap: "<<heapvec3.Front()<<endl;
  stampaRisultati("Back of the heap ", testBack);
  cout<<"  -Back of the heap should be one of its leaves, so: "<<back<<" ,Actual back of the heap: "<<heapvec3.Back()<<endl;
  allPassed &= testBack & testFront;

  cout<<"Testing PostOrderTraverse"<<endl;
  cout<<"Output should be: 4 2 3 5 7 6 8, Actual output: ";
  heapvec3.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"PreOrderFold Test with int"<<endl;
  int sum = heapvec3.PreOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PreOrderFoldTest = (sum == 35);
  stampaRisultati("Pre order fold test int", PreOrderFoldTest);
  cout<<"  -Expected sum should be: 35, Actual sum is: "<<sum<<endl;
  allPassed &= PreOrderFoldTest;
  
  lasd::List<string> list2;
  list2.InsertAtBack("A");list2.InsertAtBack("B");list2.InsertAtBack("C");list2.InsertAtBack("E");list2.InsertAtBack("G");
  lasd::HeapVec<string> heapvecstring(list2);
  cout<<"PreOrderFold Test with string"<<endl;
  string concat = heapvecstring.PreOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PreOrderFoldTestString = (concat == "GECAB");
  stampaRisultati("Pre order fold test string", PreOrderFoldTestString);
  cout<<"  -Expected concatenation should be: GECAB, Actual concatenation is: "<<concat<<endl;
  allPassed &= PreOrderFoldTestString;

  cout<<"PostOrderFold Test with int"<<endl;
  sum = heapvec3.PostOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PostOrderFoldTest = (sum == 35);
  stampaRisultati("Post order fold test int", PostOrderFoldTest);
  cout<<"  -Expected sum should be: 35, Actual sum is: "<<sum<<endl;
  allPassed &= PostOrderFoldTest;

  cout<<"PostOrderFold Test with string"<<endl;
  concat = heapvecstring.PostOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PostOrderFoldTestString = (concat == "BACEG");
  stampaRisultati("Post order fold test string", PostOrderFoldTestString);
  cout<<"  -Expected concatenation should be: BACEG, Actual concatenation is: "<<concat<<endl;
  allPassed &= PostOrderFoldTestString;

  lasd::List<int> list20;
  number = 5;
  while (list20.Size() < 5){
    list20.InsertAtBack(number);
    number--;
  }
  lasd::HeapVec<int> heapvec20(list20);
  cout<<"Testing IsHeap" <<endl;
  bool isHeap = heapvec20.IsHeap();
  stampaRisultati("Heapiness", isHeap);
  cout<<"  -Container should be a heap and it "<<(heapvec20.IsHeap() ? "is" : "isn't")<<endl;
  allPassed &= isHeap;

  cout<<"Testing Sort" <<endl;
  heapvec20.Sort();
  bool isSorted = true;
  for (int i = 1; i <= 5; i++) {
    if (i != heapvec20[i-1]) {isSorted = false;}
  }
  stampaRisultati("Sorting of the heapvec", isSorted);
  cout<<"  -Container should be sorted and it "<<(isSorted ? "is" : "isn't")<<endl;
  cout<<"  -Sorted heapvec:";
  heapvec20.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= isSorted;

  cout<<"End of the heapvec functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCasiLimiteHeapVec(){
  cout << "Testing HeapVec limit cases" << endl;
  cout << "Here we are testing if exceptions are handled correctly and other cases" << endl;
  bool allPassed = true;

  lasd::HeapVec<int> emptyheapvec;
  cout<<"Testing access to a certain index with an empty heapvec"<<endl;
  bool emptyAccessTest = false;
  try{
    emptyheapvec[5];
  } catch(out_of_range & e){
    emptyAccessTest = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access at index 5 of an empty heapvec ", emptyAccessTest);
  allPassed &= emptyAccessTest;

  cout<<"Testing heapiness of empty heapvec"<<endl;
  bool testIsHeap = false;
  testIsHeap = emptyheapvec.IsHeap();
  stampaRisultati("An empty heap is an heap ", testIsHeap);
  allPassed &= testIsHeap;

  cout<<"Testing Heapify on an empty heapvec"<<endl;
  bool testHeapify = true;
  try {
    emptyheapvec.Heapify();
  } catch (...) {
    testHeapify = false;
    cout<<"Something went wrong!" <<endl;
  }
  stampaRisultati("An empty heap cannot be heapified ", testHeapify);
  allPassed &= testHeapify;

  cout<<"Testing Sort on an empty heapvec"<<endl;
  bool testSort = true;
  try {
    emptyheapvec.Sort();
  } catch (...) {
    testSort = false;
    cout<<"Something went wrong!" <<endl;
  }
  stampaRisultati("An empty heap cannot be sorted ", testSort);
  allPassed &= testSort;

  // ADDED LATER
    lasd::Vector<int> vec1(1);
    vec1[0] = 5;
    lasd::HeapVec<int> heap1(vec1);
    bool constTest;
    int& notC = vec1[0];
    const int& c = vec1[0];
    int& notC2 = heap1[0];
    const int& c2 = heap1[0];
    constTest = (5 == vec1[0] && 5 == heap1[0] && 5 == notC && 5 == c && 5 == notC2 && 5 == c2);
    stampaRisultati("Const correctness test", constTest);
    allPassed &= constTest;
  //

  cout<<"End of the heapvec limit cases test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCostruttoriPQHeap(auto genChar, auto genInt, auto genReal){
  cout << "Testing PQHeap Constructors" << endl;
  bool allPassed = true;
  cout <<"-Default Constructor-"<<endl;
  lasd::PQHeap<int> pq1;
  bool defaultPQHeapConstructorInt = (pq1.Size() == 0 && pq1.Empty());
  stampaRisultati("Default PQHeap constructor int", defaultPQHeapConstructorInt);
  cout<<"Expected size: 0, Actual size: "<<pq1.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<pq1.Empty()<<endl;
  allPassed &= defaultPQHeapConstructorInt;

  lasd::PQHeap<string> pq2;
  bool defaultPQHeapConstructorString = (pq2.Size() == 0 && pq2.Empty());
  stampaRisultati("Default PQHeap constructor string", defaultPQHeapConstructorString);
  cout<<"Expected size: 0, Actual size: "<<pq2.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<pq2.Empty()<<endl;
  allPassed &= defaultPQHeapConstructorString;

  lasd::PQHeap<double> pq3;
  bool defaultPQHeapConstructorDouble = (pq3.Size() == 0 && pq3.Empty());
  stampaRisultati("Default PQHeap constructor double", defaultPQHeapConstructorDouble);
  cout<<"Expected size: 0, Actual size: "<<pq3.Size()<<endl;
  cout<<"Expected empty vector, Actual emptiness: "<<pq3.Empty()<<endl;
  allPassed &= defaultPQHeapConstructorDouble;

  cout<<"-TraversableContainer constructor-"<<endl;
  lasd::List<int> list1;
  int randomNumber = 0;
  while (list1.Size() < 5){
    randomNumber = genInt();
    while (list1.Exists(randomNumber)){
      randomNumber = genInt();
    }
    list1.InsertAtBack(randomNumber);
  }

  lasd::List<string> list2;
  string randomString = "";
  while (list2.Size() < 5){
    randomString = generaStringaCasuale(genChar);
    while (list2.Exists(randomString)){
      randomString = generaStringaCasuale(genChar);
    }
    list2.InsertAtBack(randomString);
  }

  lasd::List<double> list3;
  double randomDouble = 0.0;
  while (list3.Size() < 5){
    randomDouble = genReal();
    while (list3.Exists(randomDouble)){
      randomDouble = genReal();
    }
    list3.InsertAtBack(randomDouble);
  }

  lasd::PQHeap<int> pq4(list1);
  bool TraversableContainerPQHeapConstructorInt = (pq4.Size() == 5 && !pq4.Empty());
  stampaRisultati("TraversableContainer PQHeap constructor int", TraversableContainerPQHeapConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<pq4.Size()<<endl;
  cout<<"  -Expected non-empty pq list, Actual emptiness: "<<pq4.Empty()<<endl;
  allPassed &= TraversableContainerPQHeapConstructorInt;

  lasd::PQHeap<string> pq5(list2);
  bool TraversableContainerPQHeapConstructorString = (pq5.Size() == 5 && !pq5.Empty());
  stampaRisultati("TraversableContainer PQHeap constructor string", TraversableContainerPQHeapConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<pq5.Size()<<endl;
  cout<<"  -Expected non-empty pq list, Actual emptiness: "<<pq5.Empty()<<endl;
  allPassed &= TraversableContainerPQHeapConstructorString;

  lasd::PQHeap<double> pq6(list3);
  bool TraversableContainerPQHeapConstructorDouble = (pq6.Size() == 5 && !pq6.Empty());
  stampaRisultati("TraversableContainer PQHeap constructor double", TraversableContainerPQHeapConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<pq6.Size()<<endl;
  cout<<"  -Expected non-empty pq list, Actual emptiness: "<<pq6.Empty()<<endl;
  allPassed &= TraversableContainerPQHeapConstructorDouble;

  bool elementsCorrectInt = true;
  for (ulong index = 0; index < pq4.Size(); index++) {
    if (!list1.Exists(pq4[index])){
      elementsCorrectInt = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- int (content)", elementsCorrectInt);
  cout << "  - Expected elements: ";
  list1.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  pq4.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectInt);

  bool elementsCorrectString = true;
  for (ulong index = 0; index < pq5.Size(); index++) {
    if (!list2.Exists(pq5[index])){
      elementsCorrectString = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- string (content)", elementsCorrectString);
  cout << "  - Expected elements: ";
  list2.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  pq5.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectString);

  bool elementsCorrectDouble = true;
  for (ulong index = 0; index < pq6.Size(); index++) {
    if (!list3.Exists(pq6[index])){
      elementsCorrectDouble = false;
      break;
    }
  }
  stampaRisultati("-TraversableContainer constructor- double (content)", elementsCorrectDouble);
  cout << "  - Expected elements: ";
  list3.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  pq6.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDouble);

  lasd::PQHeap<int> pq14(std::move(list1));
  bool MappableContainerConstructorInt = (pq14.Size() == 5 && !pq14.Empty());
  stampaRisultati("MappableContainer pq constructor int", MappableContainerConstructorInt);
  cout<<"  -Expected size: 5, Actual size: "<<pq14.Size()<<endl;
  cout<<"  -Expected non-empty pq, Actual emptiness: "<<pq14.Empty()<<endl;
  allPassed &= MappableContainerConstructorInt;

  lasd::PQHeap<string> pq15(std::move(list2));
  bool MappableContainerConstructorString = (pq15.Size() == 5 && !pq15.Empty());
  stampaRisultati("MappableContainer pq constructor string", MappableContainerConstructorString);
  cout<<"  -Expected size: 5, Actual size: "<<pq15.Size()<<endl;
  cout<<"  -Expected non-empty pq, Actual emptiness: "<<pq15.Empty()<<endl;
  allPassed &= MappableContainerConstructorString;

  lasd::PQHeap<double> pq16(std::move(list3));
  bool MappableContainerConstructorDouble = (pq16.Size() == 5 && !pq16.Empty());
  stampaRisultati("MappableContainer Vector constructor double ", MappableContainerConstructorDouble);
  cout<<"  -Expected size: 5, Actual size: "<<pq16.Size()<<endl;
  cout<<"  -Expected non-empty pq, Actual emptiness: "<<pq16.Empty()<<endl;
  allPassed &= MappableContainerConstructorDouble;

  cout<<"-Copy constructor-"<<endl;
  lasd::PQHeap<int> pq7(pq4);
  bool copyPQHeapConstructorInt = (pq7.Size() == pq4.Size());
  stampaRisultati("-Copy constructor- PQHeap constructor int", copyPQHeapConstructorInt);
  cout << "  -Expected size: " << pq4.Size() << " Actual size: " << pq7.Size() <<endl;
  cout << "  -Identical elements: " << (pq7 == pq4 ? "true" : "false") << endl;
  allPassed &= copyPQHeapConstructorInt;

  lasd::PQHeap<string> pq8(pq5);
  bool copyPQHeapConstructorString = (pq8.Size() == pq5.Size());
  stampaRisultati("-Copy constructor- PQHeap constructor string", copyPQHeapConstructorString);
  cout << "  -Expected size: " << pq5.Size() << " Actual size: " << pq8.Size() <<endl;
  cout << "  -Identical elements: " << (pq8 == pq5 ? "true" : "false") << endl;
  allPassed &= copyPQHeapConstructorString;

  lasd::PQHeap<double> pq9(pq6);
  bool copyPQHeapConstructorDouble = (pq9.Size() == pq6.Size());
  stampaRisultati("-Copy constructor- PQHeap constructor double", copyPQHeapConstructorDouble);
  cout << "  -Expected size: " << pq6.Size() << " Actual size: " << pq9.Size() <<endl;
  cout << "  -Identical elements: " << (pq9 == pq6 ? "true" : "false") << endl;
  allPassed &= copyPQHeapConstructorDouble;

  bool elementsCorrectIntCopy = true;
  for (ulong index = 0; index < pq7.Size(); index++) {
    if (pq7[index] != pq4[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- int (content)", elementsCorrectIntCopy);
  cout << "  - Expected elements: ";
  pq4.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  pq7.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectIntCopy);

  bool elementsCorrectStringCopy = true;
  for (ulong index = 0; index < pq8.Size(); index++) {
    if (pq8[index] != pq5[index]){
      elementsCorrectStringCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- string (content)", elementsCorrectStringCopy);
  cout << "  - Expected elements: ";
  pq5.PreOrderTraverse([](const string& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  pq8.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectStringCopy);

  bool elementsCorrectDoubleCopy = true;
  for (ulong index = 0; index < pq9.Size(); index++) {
    if (pq9[index] != pq6[index]){
      elementsCorrectIntCopy = false;
      break;
    }
  }
  stampaRisultati("-Copy constructor- double (content)", elementsCorrectDoubleCopy);
  cout << "  - Expected elements: ";
  pq6.PreOrderTraverse([](const double& x){cout<<x<<" ";});
  cout<<endl;
  cout << "  - Actual elements: ";
  pq9.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= (elementsCorrectDoubleCopy);

  cout<<"-Move constructor-"<<endl;
  lasd::PQHeap<int> movepq1(move(pq4));
  bool moveConstructorTestInt = (movepq1.Size() == 5 && pq4.Size() == 0);
  stampaRisultati("-Move constructor- int", moveConstructorTestInt);
  cout << "  - Expected size of pq: 5, Actual size: " << movepq1.Size() << endl;
  cout << "  - Expected size of original pq: 0, Actual size: " << pq4.Size() << endl;
  cout << "  - Elements of new pq: ";
  movepq1.PreOrderTraverse([](const int& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestInt;

  lasd::PQHeap<string> movepq2(move(pq5));
  bool moveConstructorTestString = (movepq2.Size() == 5 && pq5.Size() == 0);
  stampaRisultati("-Move constructor- string", moveConstructorTestString);
  cout << "  - Expected size of pq: 5, Actual size: " << movepq2.Size() << endl;
  cout << "  - Expected size of original pq: 0, Actual size: " << pq5.Size() << endl;
  cout << "  - Elements of new pq: ";
  movepq2.PreOrderTraverse([](const string& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestString;

  lasd::PQHeap<double> movepq3(move(pq6));
  bool moveConstructorTestDouble = (movepq3.Size() == 5 && pq6.Size() == 0);
  stampaRisultati("-Move constructor- double", moveConstructorTestDouble);
  cout << "  - Expected size of pq: 5, Actual size: " << movepq3.Size() << endl;
  cout << "  - Expected size of original pq: 0, Actual size: " << pq6.Size() << endl;
  cout << "  - Elements of new pq: ";
  movepq3.PreOrderTraverse([](const double& x) { cout << x << " "; });
  cout << endl;
  allPassed &= moveConstructorTestDouble;

  cout<<"End of the priority queue constructors test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testFunzioniPQHeap(){
  cout << "Testing PQHeap Functions without testing limit cases" << endl;
  cout << "Not testing every datatype in this test, tests will be limited to the int type"<<endl;
  cout << "Implicitly tested functions while testing the constructors: "<<endl;
  cout << " -PreOrderTraverse "<<endl;
  cout << " -operator =="<<endl;
  cout << " -operator[] in reading"<<endl;
  cout << " -Exists"<<endl;
  cout << " -Resize"<<endl;
  cout << " -HeapifyUp"<<endl;
  bool allPassed = true;

  cout<<"Testing copy assignment"<<endl;
  lasd::List<int> list1;
  int number = 2;
  while (list1.Size() < 7){
    list1.InsertAtBack(number);
    number++;
  }
  lasd::PQHeap<int> pq1(list1), pq2;
  pq2 = pq1;
  bool testCopyAssignment = (pq1 == pq2);
  stampaRisultati("Copy assignment ", testCopyAssignment);
  cout<<"  -Size should be: "<<pq1.Size()<<" Actual size is: "<<pq2.Size()<<endl;
  cout<<"  -Elements should be: ";
  pq1.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"  -Actual elements: ";
  pq2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testCopyAssignment;

  cout<<"Testing move assignment, also general Traverse will be tested"<<endl;
  pq2.Clear();
  pq2 = move(pq1);
  bool testMoveAssignment = (pq1.Empty());
  stampaRisultati("Move assignment ", testMoveAssignment);
  cout<<"  -Size should be: 4 Actual size is: "<<pq2.Size()<<endl;
  cout<<"  -Other list should be empty, Other emptiness: "<<pq1.Empty()<<endl;
  cout<<"  -Elements: ";
  pq2.Traverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  allPassed &= testMoveAssignment;

  lasd::PQHeap<int> pq3(pq2);
  cout<<"Testing Exists"<<endl;
  cout<<"Print of the pq for clarification"<<endl;
  pq3.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  cout<<"Testing existance of value 6 and non-existance of value 1"<<endl;
  bool Exists = (pq3.Exists(6));
  bool NotExists = (!pq3.Exists(1));
  stampaRisultati("Existstance of value 6 ", Exists);
  cout<<"  -Value 6 should exist, and it "<<(pq3.Exists(6) ? "Exists" : "Doesn't Exist")<<endl;
  stampaRisultati("Non-existance of value 1 ", NotExists);
  cout<<"  -Value 1 should exist, and it "<<(pq3.Exists(1) ? "Exists" : "Doesn't Exist")<<endl;
  allPassed &= Exists & NotExists;

  cout<<"Testing Front and Back"<<endl;
  int front = pq3[0];
  int back = pq3[pq3.Size()-1];
  bool testBack = (back == pq3.Back());
  bool testFront = (front == pq3.Front());
  stampaRisultati("Front of the pq ", testFront);
  cout<<"  -Front of the pq should be its most prioritized element, so: "<<front<<" , Actual front of the pq: "<<pq3.Front()<<endl;
  stampaRisultati("Back of the pq ", testBack);
  cout<<"  -Back of the pq should be one of its least prioritized element, so: "<<back<<" ,Actual back of the pq: "<<pq3.Back()<<endl;
  allPassed &= testBack & testFront;

  cout<<"Testing PostOrderTraverse"<<endl;
  cout<<"Output should be: 4 2 3 5 7 6 8, Actual output: ";
  pq3.PostOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;

  cout<<"PreOrderFold Test with int"<<endl;
  int sum = pq3.PreOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PreOrderFoldTest = (sum == 35);
  stampaRisultati("Pre order fold test int", PreOrderFoldTest);
  cout<<"  -Expected sum should be: 35, Actual sum is: "<<sum<<endl;
  allPassed &= PreOrderFoldTest;
  
  lasd::List<string> list2;
  list2.InsertAtBack("A");list2.InsertAtBack("B");list2.InsertAtBack("C");list2.InsertAtBack("E");list2.InsertAtBack("G");
  lasd::PQHeap<string> pqstring(list2);
  cout<<"PreOrderFold Test with string"<<endl;
  string concat = pqstring.PreOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PreOrderFoldTestString = (concat == "GECAB");
  stampaRisultati("Pre order fold test string", PreOrderFoldTestString);
  cout<<"  -Expected concatenation should be: GECAB, Actual concatenation is: "<<concat<<endl;
  allPassed &= PreOrderFoldTestString;

  cout<<"PostOrderFold Test with int"<<endl;
  sum = pq3.PostOrderFold<int>([](const int& x, const int& acc) -> int {
    return acc + x;
  }, 0);
  bool PostOrderFoldTest = (sum == 35);
  stampaRisultati("Post order fold test int", PostOrderFoldTest);
  cout<<"  -Expected sum should be: 35, Actual sum is: "<<sum<<endl;
  allPassed &= PostOrderFoldTest;

  cout<<"PostOrderFold Test with string"<<endl;
  concat = pqstring.PostOrderFold<string>([](const string& x, const string& acc) -> string {
    return acc + x;
  }, "");
  bool PostOrderFoldTestString = (concat == "BACEG");
  stampaRisultati("Post order fold test string", PostOrderFoldTestString);
  cout<<"  -Expected concatenation should be: BACEG, Actual concatenation is: "<<concat<<endl;
  allPassed &= PostOrderFoldTestString;

  lasd::List<int> list20;
  number = 5;
  while (list20.Size() < 5){
    list20.InsertAtBack(number);
    number--;
  }
  lasd::PQHeap<int> pq20(list20);
  cout<<"Testing Tip, TipNRemove, RemoveTip of the PQ" <<endl;

  bool testTip = (5 == pq20.Tip());
  stampaRisultati("Test on tip of the PQ", testTip);
  cout<<"  -Tip of the pq should be its most prioritized element, so: "<<5 <<" ,Actual tip of the pq: "<<pq3.Tip()<<endl;
  allPassed &= testTip;

  testTip = (5 == pq20.TipNRemove());
  testTip &= (4 == pq20.Size());
  testTip &= (!pq20.Exists(5));
  stampaRisultati("Test on tip and remove of the PQ", testTip);
  cout<<"  -Tip of the pq should be its most prioritized element, so: "<<4 <<" ,Actual tip of the pq: "<<pq3.Tip()<<endl;
  cout<<"  -The size of the PQ should now be "<<4 <<" ,Actual size of the pq: "<<pq3.Size()<<endl;
  cout<<"  -Value 5 has " <<(testTip ? "" : "not ") <<"been removed successfully" <<endl;
  allPassed &= testTip;

  pq20.RemoveTip();
  testTip = (3 == pq20.Size());
  testTip &= (3 == pq20.Tip());
  testTip &= (!pq20.Exists(4));
  stampaRisultati("Test on remove of the tip of the PQ", testTip);
  cout<<"  -Tip of the pq should be its most prioritized element, so: "<<3 <<" ,Actual tip of the pq: "<<pq3.Tip()<<endl;
  cout<<"  -The size of the PQ should now be "<<3 <<" ,Actual size of the pq: "<<pq3.Size()<<endl;
  cout<<"  -The new tip of the PQ should now be "<<3 <<" ,Actual tip of the pq: "<<pq3.Tip()<<endl;
  cout<<"  -Value 4 has " <<(testTip ? "" : "not ") <<"been removed successfully" <<endl;
  allPassed &= testTip;

  cout<<"Testing Insert with copy and move semantics (considering also duplicate elements)" <<endl;
  bool insertTest = true, capTest = false;
  try { // The capacity should be equal to size
    pq20[pq20.Size()];
  } catch (out_of_range& e) {
    capTest = true;
  }
  insertTest &= capTest;
  pq20.Insert(4);
  insertTest = (capTest && pq20.Exists(4));
  stampaRisultati("Inserting 4 into the PQ with copy semantics", insertTest);
  cout<<" -The tip of the pq should now be 4, Actual tip of the pq: " <<pq20.Tip() <<endl;
  cout<<" -Capacity should also have been increased" <<endl;
  allPassed &= insertTest;

  int value = 2;
  pq20.Insert(std::move(value));
  insertTest = pq20.Exists(2);
  stampaRisultati("Inserting 2 into the PQ with move semantics", insertTest);
  cout<<" -The tip of the pq should still be 4, Actual tip of the pq: " <<pq20.Tip() <<endl;
  allPassed &= insertTest;

  cout<<"Testing Change with copy and move semantics" <<endl;
  bool changeTest;
  ulong toChange = pq20.Size()-1;
  pq20.Change(toChange, 5);
  changeTest = (5 == pq20.Tip());
  stampaRisultati("Changing the 2 that we added previously in a 5 (with copy semantics), thus making it climb the PQ", changeTest);
  cout<<" -The tip of the pq should now be 5, Actual tip of the pq: " <<pq20.Tip() <<endl;
  allPassed &= changeTest;

  value = 0;
  pq20.Change(0, std::move(value));
  changeTest = (4 == pq20.Tip());
  stampaRisultati("Changing the 5 that we changed previously in a 0 (with move semantics), thus making it climb the PQ downwards", changeTest);
  cout<<" -The tip of the pq should now be 4, Actual tip of the pq: " <<pq20.Tip() <<endl;
  allPassed &= changeTest;

  cout<<"Testing new version of Clear" <<endl;
  bool testClear;
  pq20.Clear();
  testClear = (0 == pq20.Size());
  stampaRisultati("Clearing the PQ", testClear);
  cout<<"The PQ has " <<(testClear ? "" : "not ") <<"been emptied correctly." <<endl;

  cout<<"End of the priority queue functions test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

bool testCasiLimitePQHeap(){
  cout << "Testing PQHeap limit cases" << endl;
  cout << "Here we are testing if exceptions are handled correctly and other cases" << endl;
  bool allPassed = true;

  lasd::PQHeap<int> emptypq;
  cout<<"Testing access to a certain index with an empty pq"<<endl;
  bool emptyAccessTest = false;
  try{
    emptypq[5];
  } catch(out_of_range & e){
    emptyAccessTest = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not access at index 5 of an empty pq ", emptyAccessTest);
  allPassed &= emptyAccessTest;

  cout<<"Testing the tip versions on an empty pq" <<endl;
  emptyAccessTest = false;
  try {
    emptypq.Tip();
  } catch(length_error& e) {
    emptyAccessTest = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not check the tip of a PQ", emptyAccessTest);
  allPassed &= emptyAccessTest;

  emptyAccessTest = false;
  try {
    emptypq.TipNRemove();
  } catch(length_error& e) {
    emptyAccessTest = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not check the tip of a PQ and remove it", emptyAccessTest);
  allPassed &= emptyAccessTest;

  emptyAccessTest = false;
  try {
    emptypq.RemoveTip();
  } catch(length_error& e) {
    emptyAccessTest = true;
    cout<<e.what()<<endl;
  }
  stampaRisultati("Could not remove the tip of a PQ", emptyAccessTest);
  allPassed &= emptyAccessTest;

  cout<<"Testing change on empty pq" <<endl;
  emptypq.Change(5, 5);
  emptyAccessTest = emptypq.Empty();
  stampaRisultati("Could not change a value in an empty pq", emptyAccessTest);
  allPassed &= emptyAccessTest;

  lasd::PQHeap<int> pq;
  pq.Insert(5); pq.Insert(6);
  bool wrongIndex;
  ulong oldSize = pq.Size();
  cout<<"Testing change on a wrong index of the pq"<<endl;
  cout<<"  -Values just inserted: ";
  pq.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  pq.Change(5, 5);
  wrongIndex = (oldSize == pq.Size());
  cout<<endl <<"  -After the supposed change: ";
  pq.PreOrderTraverse([](const int& x){cout<<x<<" ";});
  cout<<endl;
  stampaRisultati("Change on a wrong index does nothing", wrongIndex);
  allPassed &= wrongIndex;

  // ADDED LATER
    lasd::Vector<int> vec1(1);
    vec1[0] = 5;
    lasd::PQHeap<int> pq1(vec1);
    bool constTest;
    int& notC = vec1[0];
    const int& c = vec1[0];
    // int& notC2 = pq1[0]; // Cannot do this
    const int& c2 = pq1[0];
    constTest = (5 == vec1[0] && 5 == pq1[0] && 5 == notC && 5 == c && 5 == c2);
    stampaRisultati("Const correctness test", constTest);
    allPassed &= constTest;
  //

  cout<<"End of the priority queue limit cases test: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  return allPassed;
}

void mytest(){
  cout <<endl <<"====================BEGIN OF MY TESTS===================="<<endl;
  bool allPassed = true;
  random_device randomDevice;
  default_random_engine randomEngine {randomDevice()};
  uniform_int_distribution<int> disInt{0, 9};
  uniform_int_distribution<int> disChar{0, 25};
  uniform_real_distribution<double> disReal{0.0, 9.9};
  auto genInt = [&]() {return disInt(randomEngine);};
  auto genChar = [&]() {return disChar(randomEngine);};
  auto genReal = [&]() {return disReal(randomEngine);};

  allPassed &= testCostruttoriVector();
  cout<<endl;
  allPassed &= testFunzioniVector();
  cout<<endl;
  allPassed &= testUlterioriFunzioniVector(genInt);
  cout<<endl;
  allPassed &= testCasiLimiteVector();
  cout<<endl;

  allPassed &= testCostruttoriList();
  cout<<endl;
  allPassed &= testFunzioniList();
  cout<<endl;
  allPassed &= testCasiLimiteList();
  cout<<endl;

  allPassed &= testCostruttoriSetLst(genInt, genChar, genReal);
  cout<<endl;
  allPassed &= testFunzioniSetLst();
  cout<<endl;
  allPassed &= testCasiLimiteSetLst();
  cout<<endl;

  allPassed &= testCostruttoriSetVec(genInt, genChar, genReal);
  cout<<endl;
  allPassed &= testFunzioniSetVec();
  cout<<endl;
  allPassed &= testCasiLimiteSetVec();
  cout<<endl;

  allPassed &= testCostruttoriHeapVec(genInt, genChar,genReal);
  cout<<endl;
  allPassed &= testFunzioniHeapVec();
  cout<<endl;
  allPassed &= testCasiLimiteHeapVec();
  cout<<endl;

  allPassed &= testCostruttoriPQHeap(genInt, genChar,genReal);
  cout<<endl;
  allPassed &= testFunzioniPQHeap();
  cout<<endl;
  allPassed &= testCasiLimitePQHeap();
  cout<<endl;

  cout<<"FINAL RESULTS: " << (allPassed ? "EVERYTHING GOOD" : "SOMETHING WRONG")<<endl;
  cout<<"====================END OF MY TESTS====================" <<endl;
}