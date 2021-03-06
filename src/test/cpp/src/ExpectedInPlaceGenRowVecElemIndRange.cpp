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

#include <utility>
using std::pair;

#include <armadillo>
using arma::Row;
using arma::span;

#include <InputClass.hpp>
using armadilloJava::InputClass;

#include <Input.hpp>
using armadilloJava::Input;

namespace armadilloJava {
  class ExpectedInPlaceGenRowVecElemIndRange : public Expected {
    public:
      ExpectedInPlaceGenRowVecElemIndRange() {
        cout << "Compute ExpectedInPlaceGenRowVecElemIndRange(): " << endl;

          vector<vector<pair<string, void*>>> inputs = Input::getTestParameters({
            InputClass::GenRowVec,
            InputClass::ElemIndRange
          });

          for (vector<pair<string, void*>> input : inputs) {
            _fileSuffix = "";

            int n = 0;
            for (pair<string, void*> value : input) {
              switch (n) {
                case 0:
                  _fileSuffix += value.first;
                  _genRowVec = *static_cast<Row<double>*>(value.second);
                  break;
                case 1:
                  _fileSuffix += "," + value.first;
                  _elemIndRange = *static_cast<span*>(value.second);
                  break;
              }
              ++n;
            }

            cout << "Using input: " << _fileSuffix << endl;

            _copyOfGenRowVec = _genRowVec;
            _copyOfElemIndRange = _elemIndRange;

            expectedRowSwapCols();

            _genRowVec = _copyOfGenRowVec;
            _elemIndRange = _copyOfElemIndRange;

            expectedRowVecShedCols();
          }

          cout << "done." << endl;
        }

    protected:
      Row<double> _genRowVec;
      Row<double> _copyOfGenRowVec;

      span _elemIndRange;
      span _copyOfElemIndRange;

      void expectedRowSwapCols() {
        if(_elemIndRange.whole) {
          return;
        }

        if(!_genRowVec.in_range(_elemIndRange)) {
          return;
        }

        cout << "- Compute expectedRowSwapCols() ... ";

        _genRowVec.swap_cols(_elemIndRange.a, _elemIndRange.b);
        save<double>("Row.swap_cols", _genRowVec);

        cout << "done." << endl;
      }

      void expectedRowVecShedCols() {
        if(_elemIndRange.whole) {
          return;
        }

        if(!_genRowVec.in_range(_elemIndRange)) {
          return;
        }

        cout << "- Compute expectedRowVecShedCols() ... ";

        _genRowVec.shed_cols(_elemIndRange.a, _elemIndRange.b);
        save<double>("Row.shed_cols", _genRowVec);

        cout << "done." << endl;
      }
  };
}
