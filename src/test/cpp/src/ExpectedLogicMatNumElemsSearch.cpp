/*******************************************************************************
 * Copyright 2013-2014 Sebastian Niemann <niemann@sra.uni-hannover.de>.
 * 
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://opensource.org/licenses/MIT
 * 
 * Developers:
 *   Sebastian Niemann - Lead developer
 *   Daniel Kiechle - Unit testing
 ******************************************************************************/
#include <Expected.hpp>
using armadilloJava::Expected;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <armadillo>
using arma::Mat;
using arma::uword;
using arma::find;

#include <InputClass.hpp>
using armadilloJava::InputClass;

#include <Input.hpp>
using armadilloJava::Input;

namespace armadilloJava {
  class ExpectedLogicMatNumElemsSearch : public Expected {
    public:
      ExpectedLogicMatNumElemsSearch() {
        cout << "Compute ExpectedLogicMatNumElemsSearch(): " << endl;

        vector<vector<pair<string, void*>>> inputs = Input::getTestParameters({
          InputClass::LogicMat,
          InputClass::NumElems,
          InputClass::Search
        });

        for (vector<pair<string, void*>> input : inputs) {
          _fileSuffix = "";

          int n = 0;
          for (pair<string, void*> value : input) {
            switch (n) {
              case 0:
                _fileSuffix += value.first;
                _logicMat = *static_cast<Mat<double>*>(value.second);
                break;
              case 1:
                _fileSuffix += "," + value.first;
                _numElems = *static_cast<int*>(value.second);
                break;
              case 2:
                _fileSuffix += "," + value.first;
                _search = *static_cast<string*>(value.second);
                break;
            }
            ++n;
          }

          cout << "Using input: " << _fileSuffix << endl;

          expectedArmaFind();
        }

        cout << "done." << endl;
      }

    protected:
      Mat<double> _logicMat;
      int _numElems;
      string _search;

      void expectedArmaFind() {
        cout << "- Compute expectedArmaFind() ... ";
        save<uword>("Arma.find", find(_logicMat, _numElems, _search.c_str()));
        cout << "done." << endl;
      }

  };
}
