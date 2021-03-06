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
using arma::Mat;
using arma::toeplitz;
using arma::dot;
using arma::norm_dot;
using arma::conv;
using arma::cor;
using arma::cov;
using arma::cross;
using arma::join_rows;
using arma::join_horiz;
using arma::join_cols;
using arma::join_vert;
using arma::kron;

#include <InputClass.hpp>
using armadilloJava::InputClass;

#include <Input.hpp>
using armadilloJava::Input;

namespace armadilloJava {
  class ExpectedGenRowVecGenRowVec : public Expected {
    public:
      ExpectedGenRowVecGenRowVec() {
        cout << "Compute ExpectedGenRowVecGenRowVec(): " << endl;

        vector<vector<pair<string, void*>>> inputs = Input::getTestParameters({
          InputClass::GenRowVec,
          InputClass::GenRowVec
        });

        for (vector<pair<string, void*>> input : inputs) {
          _fileSuffix = "";

          int n = 0;
          for (pair<string, void*> value : input) {
            switch (n) {
              case 0:
                _fileSuffix += value.first;
                _genRowVecA = *static_cast<Row<double>*>(value.second);
                break;
              case 1:
                _fileSuffix += "," + value.first;
                _genRowVecB = *static_cast<Row<double>*>(value.second);
                break;
            }
            ++n;
          }

          cout << "Using input: " << _fileSuffix << endl;

          expectedArmaToeplitz();
          expectedArmaDot();
          expectedArmaNorm_dot();
          expectedArmaConv();
          expectedArmaCor();
          expectedArmaCov();
          expectedArmaCross();
          expectedArmaJoin_rows();
          expectedArmaJoin_horiz();
          expectedArmaJoin_cols();
          expectedArmaJoin_vert();
          expectedArmaKron();
          expectedRowPlus();
          expectedRowMinus();
          expectedRowTimes();
          expectedRowElemTimes();
          expectedRowElemDivide();
          expectedRowEquals();
          expectedRowNonEquals();
          expectedRowGreaterThan();
          expectedRowLessThan();
          expectedRowStrictGreaterThan();
          expectedRowStrictLessThan();
        }

        cout << "done." << endl;
      }

    protected:
      Row<double> _genRowVecA;
      Row<double> _genRowVecB;

      void expectedArmaToeplitz() {
        cout << "- Compute expectedArmaToeplitz() ... ";
        save<double>("Arma.toeplitz", toeplitz(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaDot() {
        if(_genRowVecA.n_elem != _genRowVecB.n_elem) {
          return;
        }

        cout << "- Compute expectedArmaDot() ... ";
        save<double>("Arma.dot", Mat<double>({dot(_genRowVecA, _genRowVecB)}));
        cout << "done." << endl;
      }

      void expectedArmaNorm_dot() {
        if(_genRowVecA.n_elem != _genRowVecB.n_elem) {
          return;
        }

        cout << "- Compute expectedArmaNorm_dot() ... ";
        save<double>("Arma.norm_dot", Mat<double>({norm_dot(_genRowVecA, _genRowVecB)}));
        cout << "done." << endl;
      }

      void expectedArmaConv() {
        cout << "- Compute expectedArmaConv() ... ";
        save<double>("Arma.conv", conv(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaCor() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedArmaCor() ... ";
        save<double>("Arma.cor", cor(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaCov() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedArmaCov() ... ";
        save<double>("Arma.cov", cov(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaCross() {
        cout << "- Compute expectedArmaCross() ... ";

        Row<double> tempGenRowVecA = Row<double>(_genRowVecA);
        tempGenRowVecA.resize(3);
        Row<double> tempGenRowVecB = Row<double>(_genRowVecB);
        tempGenRowVecB.resize(3);

        save<double>("Arma.cross", cross(tempGenRowVecA, tempGenRowVecB));

        cout << "done." << endl;
      }

      void expectedArmaJoin_rows() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        cout << "- Compute expectedArmaJoin_rows() ... ";
        save<double>("Arma.join_rows", join_rows(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaJoin_horiz() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        cout << "- Compute expectedArmaJoin_horiz() ... ";
        save<double>("Arma.join_horiz", join_horiz(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaJoin_cols() {
        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedArmaJoin_cols() ... ";
        save<double>("Arma.join_cols", join_cols(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaJoin_vert() {
        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedArmaJoin_vert() ... ";
        save<double>("Arma.join_vert", join_cols(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedArmaKron() {
        cout << "- Compute expectedArmaKron() ... ";
        save<double>("Arma.kron", kron(_genRowVecA, _genRowVecB));
        cout << "done." << endl;
      }

      void expectedRowPlus() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowPlus() ... ";
        save<double>("Row.plus", _genRowVecA + _genRowVecB);
        cout << "done." << endl;
      }

      void expectedRowMinus() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowMinus() ... ";
        save<double>("Row.minus", _genRowVecA - _genRowVecB);
        cout << "done." << endl;
      }

      void expectedRowTimes() {
        if(_genRowVecA.n_cols != _genRowVecB.n_rows) {
          return;
        }

        cout << "- Compute expectedRowTimes() ... ";
        save<double>("Row.times", _genRowVecA * _genRowVecB);
        cout << "done." << endl;
      }

      void expectedRowElemTimes() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowElemTimes() ... ";
        save<double>("Row.elemTimes", _genRowVecA % _genRowVecB);
        cout << "done." << endl;
      }

      void expectedRowElemDivide() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowElemDivide() ... ";
        save<double>("Row.elemDivide", _genRowVecA / _genRowVecB);
        cout << "done." << endl;
      }

      void expectedRowEquals() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowEquals() ... ";

        Mat<uword> expected = _genRowVecA == _genRowVecB;
        save<uword>("Row.equals", expected);

        cout << "done." << endl;
      }

      void expectedRowNonEquals() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowNonEquals() ... ";

        Mat<uword> expected = _genRowVecA != _genRowVecB;
        save<uword>("Row.nonEquals", expected);

        cout << "done." << endl;
      }

      void expectedRowGreaterThan() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowGreaterThan() ... ";

        Mat<uword> expected = _genRowVecA >= _genRowVecB;
        save<uword>("Row.greaterThan", expected);

        cout << "done." << endl;
      }

      void expectedRowLessThan() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowLessThan() ... ";

        Mat<uword> expected = _genRowVecA <= _genRowVecB;
        save<uword>("Row.lessThan", expected);

        cout << "done." << endl;
      }

      void expectedRowStrictGreaterThan() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowStrictGreaterThan() ... ";

        Mat<uword> expected = _genRowVecA > _genRowVecB;
        save<uword>("Row.strictGreaterThan", expected);

        cout << "done." << endl;
      }

      void expectedRowStrictLessThan() {
        if(_genRowVecA.n_rows != _genRowVecB.n_rows) {
          return;
        }

        if(_genRowVecA.n_cols != _genRowVecB.n_cols) {
          return;
        }

        cout << "- Compute expectedRowStrictLessThan() ... ";

        Mat<uword> expected = _genRowVecA < _genRowVecB;
        save<uword>("Row.strictLessThan", expected);

        cout << "done." << endl;
      }

  };
}
