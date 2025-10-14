#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

#include <iostream>

int main() {
  bool again = true;
  int test;
  while (again) {
    std::cout<<std::endl <<"LASD Libraries 2025" <<std::endl;
    std::cout<<"Quale test vuoi provare?" <<std::endl;
    std::cout<<"1) lasdtest()" <<std::endl <<"2) mytest" <<std::endl <<"0) Esci" <<std::endl;
    std::cin>>test;
    switch (test) {
      case 1:
        lasdtest();
        break;
      case 2:
        mytest();
        break;
      case 0:
        again = false;
        std::cout<<"Grazie e arrivederci!" <<std::endl;
        break;
      default:
        std::cout<<"Errore nella scelta" <<std::endl;
        break;
    }
  }
  return 0;
}