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
// http://arma.sourceforge.net/docs.html#config_hpp
#define ARMA_USE_CXX11 // Use C++11 features, such as initialiser lists

#include <Input.hpp>
using armadilloJava::Input;

#include <algorithm>
using std::sort;
using std::set_union;

#include <string>
using std::to_string;

#include <stdexcept>
using std::runtime_error;

#include <vector>
using std::vector;

#include <armadillo>
using arma::Mat;
using arma::Col;
using arma::Row;
using arma::zeros;
using arma::ones;
using arma::eye;
using arma::datum;
using arma::span;
using arma::SizeMat;
using arma::distr_param;

#include <iostream>
using std::cout;
using std::endl;

namespace armadilloJava {
  vector<vector<pair<string, void*>>> Input::getTestParameters(const vector<InputClass>& testClasses) {
    vector<vector<pair<string, void*>>> inputs;

    for (InputClass testClass : testClasses) {
      switch (testClass) {
        case InputClass::ElemInd:
          inputs.push_back(getElemInd());
          break;
        case InputClass::ColInd:
          inputs.push_back(getColInd());
          break;
        case InputClass::ExtColInd:
          inputs.push_back(getExtColInd());
          break;
        case InputClass::RowInd:
          inputs.push_back(getRowInd());
          break;
        case InputClass::ExtRowInd:
          inputs.push_back(getExtRowInd());
          break;
        case InputClass::NumElems:
          inputs.push_back(getNumElems());
          break;
        case InputClass::NumCols:
          inputs.push_back(getNumCols());
          break;
        case InputClass::NumRows:
          inputs.push_back(getNumRows());
          break;
        case InputClass::Normal:
          inputs.push_back(getNormal());
          break;
        case InputClass::Dim:
          inputs.push_back(getDim());
          break;
        case InputClass::Exp:
          inputs.push_back(getExp());
          break;
        case InputClass::MatNormInt:
          inputs.push_back(getMatNormInt());
          break;
        case InputClass::VecNormInt:
          inputs.push_back(getVecNormInt());
          break;
        case InputClass::GenDouble:
          inputs.push_back(getGenDouble());
          break;
        case InputClass::TriDouble:
          inputs.push_back(getTriDouble());
          break;
        case InputClass::SinValTol:
          inputs.push_back(getSinValTol());
          break;
        case InputClass::ElemIndRange:
          inputs.push_back(getElemIndRange());
          break;
        case InputClass::ColIndRange:
          inputs.push_back(getColIndRange());
          break;
        case InputClass::RowIndRange:
          inputs.push_back(getRowIndRange());
          break;
        case InputClass::MatSize:
          inputs.push_back(getMatSize());
          break;
        case InputClass::ColVecSize:
          inputs.push_back(getColVecSize());
          break;
        case InputClass::RowVecSize:
          inputs.push_back(getRowVecSize());
          break;
        case InputClass::GenMatVec:
          inputs.push_back(getGenMatVec());
          break;
        case InputClass::LogicMatVec:
          inputs.push_back(getLogicMatVec());
          break;
        case InputClass::OOMatVec:
          inputs.push_back(getOOMatVec());
          break;
        case InputClass::GenMat:
          inputs.push_back(getGenMat());
          break;
        case InputClass::SquMat:
          inputs.push_back(getSquMat());
          break;
        case InputClass::InvMat:
          inputs.push_back(getInvMat());
          break;
        case InputClass::SymMat:
          inputs.push_back(getSymMat());
          break;
        case InputClass::SymPDMat:
          inputs.push_back(getSymPDMat());
          break;
        case InputClass::LogicMat:
          inputs.push_back(getLogicMat());
          break;
        case InputClass::OOMat:
          inputs.push_back(getOOMat());
          break;
        case InputClass::GenVec:
          inputs.push_back(getGenVec());
          break;
        case InputClass::MonVec:
          inputs.push_back(getMonVec());
          break;
        case InputClass::LogicVec:
          inputs.push_back(getLogicVec());
          break;
        case InputClass::OOVec:
          inputs.push_back(getOOVec());
          break;
        case InputClass::GenColVec:
          inputs.push_back(getGenColVec());
          break;
        case InputClass::MonColVec:
          inputs.push_back(getMonColVec());
          break;
        case InputClass::LogicColVec:
          inputs.push_back(getLogicColVec());
          break;
        case InputClass::OOColVec:
          inputs.push_back(getOOColVec());
          break;
        case InputClass::GenRowVec:
          inputs.push_back(getGenRowVec());
          break;
        case InputClass::MonRowVec:
          inputs.push_back(getMonRowVec());
          break;
        case InputClass::LogicRowVec:
          inputs.push_back(getLogicRowVec());
          break;
        case InputClass::OORowVec:
          inputs.push_back(getOORowVec());
          break;
        case InputClass::ElemInds:
          inputs.push_back(getElemInds());
          break;
        case InputClass::ColInds:
          inputs.push_back(getColInds());
          break;
        case InputClass::RowInds:
          inputs.push_back(getRowInds());
          break;
        case InputClass::MatNormString:
          inputs.push_back(getMatNormString());
          break;
        case InputClass::VecNormString:
          inputs.push_back(getVecNormString());
          break;
        case InputClass::Sort:
          inputs.push_back(getSort());
          break;
        case InputClass::SinValSel:
          inputs.push_back(getSinValSel());
          break;
        case InputClass::DistrParam:
          inputs.push_back(getDistrParam());
          break;
        case InputClass::Fill:
          inputs.push_back(getFill());
          break;
        default:
          throw new runtime_error("Unsupported test class requested.");
      }
    }

    return cartesianProduct(inputs);
  }

  vector<vector<pair<string, void*>>> Input::cartesianProduct(const vector<vector<pair<string, void*>>>& inputs) {
    vector<vector<pair<string, void*>>> cartesianProduct = {{}};
    for (vector<pair<string, void*>> input : inputs) {
      vector<vector<pair<string, void*>>> tempProduct;
      for (vector<pair<string, void*>> tempInput : cartesianProduct) {
        for (pair<string, void*> keyValuePair : input) {
          tempProduct.push_back(tempInput);
          tempProduct.back().push_back(keyValuePair);
        }
      }
      cartesianProduct.swap(tempProduct);
    }
    return cartesianProduct;
  }

  vector<pair<string, void*>> Input::vectorUnion(const vector<vector<pair<string, void*>>>& inputs) {
    vector<pair<string, void*>> vectorUnion = inputs.at(0);

    sort(vectorUnion.begin(), vectorUnion.end(), [](const pair<string, void*>& lhs, const pair<string, void*>& rhs) {return lhs.first < rhs.first;});

    for (int n = 1; n < inputs.size(); n++) {
      vector<pair<string, void*>> input = inputs.at(n);
      sort(input.begin(), input.end(), [](const pair<string, void*>& lhs, const pair<string, void*>& rhs) {return lhs.first < rhs.first;});

      vector<pair<string, void*>> temp(vectorUnion.size() + input.size());
      vector<pair<string, void*>>::iterator end = set_union(vectorUnion.begin(), vectorUnion.end(), input.begin(), input.end(), temp.begin(), [](const pair<string, void*>& lhs, const pair<string, void*>& rhs) {return lhs.first < rhs.first;});
      temp.resize(end - temp.begin());

      vectorUnion = temp;
    }

    return vectorUnion;
  }

  Mat<double> Input::getHilbertMatrix(int n_rows, int n_cols) {
    Mat<double> hilbertMatrix(n_rows, n_cols);

    for (int j = 0; j < n_cols; j++) {
      for (int i = 0; i < n_rows; i++) {
        hilbertMatrix.at(i, j) = 1.0 / (i + j + 1);
      }
    }

    return hilbertMatrix;
  }

  Mat<double> Input::getKMSMatrix(int n_rows, int n_cols) {
    Mat<double> kmsMatrix(n_rows, n_cols);

    for (int j = 0; j < n_cols; j++) {
      for (int i = 0; i < n_rows; i++) {
        kmsMatrix.at(i, j) = pow(2, abs(i - j));
      }
    }

    return kmsMatrix;
  }

  vector<pair<string, void*>> Input::getElemInd() {
    vector<vector<pair<string, void*>>> inputs = {};
    inputs.push_back({
      pair<string, void*>("0", new int(0)),
      pair<string, void*>("1", new int(1))
    });

    for (pair<string, void*> keyValuePair : getNumElems()) {
      int numElems = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>(to_string(numElems - 1), new int(numElems - 1))
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getColInd() {
    return getRowInd();
  }

  vector<pair<string, void*>> Input::getExtColInd() {
    return getExtRowInd();
  }

  vector<pair<string, void*>> Input::getRowInd() {
    vector<vector<pair<string, void*>>> inputs = {};
    inputs.push_back({
      pair<string, void*>("0", new int(0)),
      pair<string, void*>("1", new int(1))
    });

    for (pair<string, void*> keyValuePair : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>(to_string(numRows - 1), new int(numRows - 1))
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getExtRowInd() {
    return vectorUnion({
      getRowInd(),
      getNumRows()
    });
  }

  vector<pair<string, void*>> Input::getNumElems() {
    return {
      pair<string, void*>("1", new int(1)),
      pair<string, void*>("2", new int(2)),
      pair<string, void*>("25", new int(25))
    };
  }

  vector<pair<string, void*>> Input::getNumCols() {
    return getNumRows();
  }

  vector<pair<string, void*>> Input::getNumRows() {
    return {
      pair<string, void*>("1", new int(1)),
      pair<string, void*>("2", new int(2)),
      pair<string, void*>("5", new int(5))
    };
  }

  vector<pair<string, void*>> Input::getNormal() {
    return {
      pair<string, void*>("0", new int(0)),
      pair<string, void*>("1", new int(1))
    };
  }

  vector<pair<string, void*>> Input::getDim() {
    return {
      pair<string, void*>("0", new int(0)),
      pair<string, void*>("1", new int(1))
    };
  }

  vector<pair<string, void*>> Input::getExp() {
    return {
      pair<string, void*>("0.5", new double(0.5)),
      pair<string, void*>("1.0", new double(1)),
      pair<string, void*>("2.0", new double(2)),
      pair<string, void*>("3.0", new double(3))
    };
  }

  vector<pair<string, void*>> Input::getMatNormInt() {
    return {
      pair<string, void*>("1", new int(1)),
      pair<string, void*>("2", new int(2))
    };
  }

  vector<pair<string, void*>> Input::getVecNormInt() {
    return {
      pair<string, void*>("1", new int(1)),
      pair<string, void*>("2", new int(2)),
      pair<string, void*>("3", new int(3)),
      pair<string, void*>("4", new int(4))
    };
  }

  vector<pair<string, void*>> Input::getGenDouble() {
    return vectorUnion({{
      pair<string, void*>("-inf", new double(-datum::inf)),
      pair<string, void*>("-2.0", new double(-2)),
      pair<string, void*>("0.0", new double(0)),
      pair<string, void*>("machine_epsilon", new double(datum::eps)),
      pair<string, void*>("0.5", new double(0.5)),
      pair<string, void*>("1.0", new double(1)),
      pair<string, void*>("euler_number", new double(datum::e)),
      pair<string, void*>("3.0", new double(3)),
      pair<string, void*>("4.0", new double(4)),
      pair<string, void*>("inf", new double(datum::inf))
    }, getTriDouble()});
  }

  vector<pair<string, void*>> Input::getTriDouble() {
    return {
      pair<string, void*>("-inf", new double(-datum::inf)),
      pair<string, void*>("-2.0", new double(-2)),
      pair<string, void*>("0.0", new double(0)),
      pair<string, void*>("machine_epsilon", new double(datum::eps)),
      pair<string, void*>("1.0", new double(1)),
      pair<string, void*>("pi", new double(datum::pi)),
      pair<string, void*>("inf", new double(datum::inf))
    };
  }

  vector<pair<string, void*>> Input::getSinValTol() {
    return {
      pair<string, void*>("0", new int(0)),
      pair<string, void*>("1", new int(1)),
      pair<string, void*>("-1", new int(-1))
    };
  }

  vector<pair<string, void*>> Input::getElemIndRange() {
    vector<vector<pair<string, void*>>> inputs = {};
    inputs.push_back({
      pair<string, void*>("span(0,0)", new span(0, 0))
    });

    for (pair<string, void*> keyValuePair : getNumElems()) {
      int numElems = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>("span(0," + to_string(numElems - 1) + ")", new span(0, numElems - 1)),
        pair<string, void*>("span(" + to_string(numElems - 1) + "," + to_string(numElems - 1) + ")", new span(numElems - 1, numElems - 1)),
        pair<string, void*>("span(" + to_string(numElems/2 - 1) + "," + to_string(numElems/2 + 1) + ")", new span(numElems/2 - 1, numElems/2 + 1))
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getColIndRange() {
    return getRowIndRange();
  }

  vector<pair<string, void*>> Input::getRowIndRange() {
    vector<vector<pair<string, void*>>> inputs = {};
    inputs.push_back({
      pair<string, void*>("span(0,0)", new span(0, 0))
    });

    for (pair<string, void*> keyValuePair : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>("span(0," + to_string(numRows - 1) + ")", new span(0, numRows - 1)),
        pair<string, void*>("span(" + to_string(numRows - 1) + "," + to_string(numRows - 1) + ")", new span(numRows - 1, numRows - 1)),
        pair<string, void*>("span(" + to_string(numRows/2 - 1) + "," + to_string(numRows/2 + 1) + ")", new span(numRows/2 - 1, numRows/2 + 1))
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getMatSize() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        input.push_back(pair<string, void*>("size(" + to_string(numRows) + "," + to_string(numCols) + ")", new SizeMat(numRows, numCols)));
        input.push_back(pair<string, void*>("size(Mat(" + to_string(numRows) + "," + to_string(numCols) + "))", new SizeMat(numRows, numCols)));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getColVecSize() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePair : getNumElems()) {
      int numElems = *static_cast<int*>(keyValuePair.second);

      input.push_back(pair<string, void*>("size(" + to_string(numElems) + ",1)", new SizeMat(numElems, 1)));
    }

    return input;
  }

  vector<pair<string, void*>> Input::getRowVecSize() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePair : getNumElems()) {
      int numElems = *static_cast<int*>(keyValuePair.second);

      input.push_back(pair<string, void*>("size(1," + to_string(numElems) + ")", new SizeMat(1, numElems)));
    }

    return input;
  }

  vector<pair<string, void*>> Input::getGenMatVec() {
    return vectorUnion({
      getGenMat(),
      getGenVec(),
      getLogicMatVec(),
      getOOMatVec()
    });
  }

  vector<pair<string, void*>> Input::getLogicMatVec() {
    return vectorUnion({
      getLogicMat(),
      getLogicVec()
    });
  }

  vector<pair<string, void*>> Input::getOOMatVec() {
    return vectorUnion({
      getOOMat(),
      getOOVec()
    });
  }

  vector<pair<string, void*>> Input::getGenMat() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        input.push_back(pair<string, void*>("Mat(zeros(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(zeros<Mat<double>>(numRows, numCols))));
        input.push_back(pair<string, void*>("Mat(ones(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(ones<Mat<double>>(numRows, numCols))));
        input.push_back(pair<string, void*>("Mat(eye(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(eye<Mat<double>>(numRows, numCols))));
        input.push_back(pair<string, void*>("Mat(hilbert(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(getHilbertMatrix(numRows, numCols))));
        input.push_back(pair<string, void*>("Mat(kms(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(getKMSMatrix(numRows, numCols))));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getSquMat() {
    return vectorUnion({
      getInvMat(),
      getSymMat()
    });
  }

  vector<pair<string, void*>> Input::getInvMat() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        if(numRows == numCols) {
          input.push_back(pair<string, void*>("Mat(eye(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(eye<Mat<double>>(numRows, numCols))));
          input.push_back(pair<string, void*>("Mat(kms(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(getKMSMatrix(numRows, numCols))));
        }
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getSymMat() {
    vector<vector<pair<string, void*>>> inputs = {};
    inputs.push_back(getSymPDMat());

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        if(numRows == numCols) {
          inputs.push_back({
            pair<string, void*>("Mat(zeros(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(zeros<Mat<double>>(numRows, numCols))),
            pair<string, void*>("Mat(ones(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(ones<Mat<double>>(numRows, numCols)))
          });
        }
      }
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getSymPDMat() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        if(numRows == numCols) {
          input.push_back(pair<string, void*>("Mat(eye(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(eye<Mat<double>>(numRows, numCols))));
          input.push_back(pair<string, void*>("Mat(hilbert(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(getHilbertMatrix(numRows, numCols))));
        }
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getLogicMat() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        input.push_back(pair<string, void*>("Mat(zeros(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(zeros<Mat<double>>(numRows, numCols))));
        input.push_back(pair<string, void*>("Mat(ones(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(ones<Mat<double>>(numRows, numCols))));
        input.push_back(pair<string, void*>("Mat(hilbertSub(" + to_string(numRows) + "," + to_string(numCols) + "))", new Mat<double>(getHilbertMatrix(numRows, numCols) - 2.0/(numRows + numCols + 2))));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getOOMat() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePair : getGenDouble()) {
      double genDouble = *static_cast<double*>(keyValuePair.second);

      input.push_back(pair<string, void*>("Mat({" + keyValuePair.first + "})", new Mat<double>({genDouble})));
    }

    return input;
  }

  vector<pair<string, void*>> Input::getGenVec() {
    return vectorUnion({
      getGenColVec(),
      getGenRowVec(),
      getMonVec(),
      getLogicVec(),
      getOOVec()
    });
  }

  vector<pair<string, void*>> Input::getMonVec() {
    return vectorUnion({
      getMonColVec(),
      getMonRowVec()
    });
  }

  vector<pair<string, void*>> Input::getLogicVec() {
    return vectorUnion({
      getLogicColVec(),
      getLogicRowVec()
    });
  }

  vector<pair<string, void*>> Input::getOOVec() {
    return vectorUnion({
      getOOColVec(),
      getOORowVec()
    });
  }

  vector<pair<string, void*>> Input::getGenColVec() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      input.push_back(pair<string, void*>("Col(zeros(" + to_string(numRows) + ",1))", new Col<double>(zeros<Col<double>>(numRows))));
      input.push_back(pair<string, void*>("Col(ones(" + to_string(numRows) + ",1))", new Col<double>(ones<Col<double>>(numRows))));

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        Mat<double> identity = eye<Mat<double>>(numRows, numCols);
        Mat<double> hilbert = getHilbertMatrix(numRows, numCols);
        Mat<double> kms = getKMSMatrix(numRows, numCols);

        input.push_back(pair<string, void*>("Col(eye(" + to_string(numRows) + "," + to_string(numCols) + ").col(0))", new Col<double>(identity.col(0))));
        input.push_back(pair<string, void*>("Col(hilbert(" + to_string(numRows) + "," + to_string(numCols) + ").col(0))", new Col<double>(hilbert.col(0))));
        input.push_back(pair<string, void*>("Col(kms(" + to_string(numRows) + "," + to_string(numCols) + ").col(0))", new Col<double>(kms.col(0))));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getMonColVec() {
    return {
      pair<string, void*>("Col({0,1,...,n})", new Col<double>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})),
      pair<string, void*>("Col({0,0.1,...,1})", new Col<double>({0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1})),
      pair<string, void*>("Col({-10,-5,10})", new Col<double>({-10, -5, 10})),
      pair<string, void*>("Col({-inf,0,inf})", new Col<double>({datum::inf, 0, -datum::inf})),
      pair<string, void*>("Col({0})", new Col<double>({0})),
      pair<string, void*>("Col({-inf})", new Col<double>({-datum::inf})),
      pair<string, void*>("Col({inf})", new Col<double>({datum::inf}))
    };
  }

  vector<pair<string, void*>> Input::getLogicColVec() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePairA.second);

      input.push_back(pair<string, void*>("Col(zeros(" + to_string(numRows) + ",1))", new Col<double>(zeros<Col<double>>(numRows))));
      input.push_back(pair<string, void*>("Col(ones(" + to_string(numRows) + ",1))", new Col<double>(ones<Col<double>>(numRows))));

      for (pair<string, void*> keyValuePairB : getNumCols()) {
        int numCols = *static_cast<int*>(keyValuePairB.second);

        Mat<double> identity = eye<Mat<double>>(numRows, numCols);
        Mat<double> hilbertSub = getHilbertMatrix(numRows, numCols) - 2.0/(numRows + numCols + 2);

        input.push_back(pair<string, void*>("Col(eye(" + to_string(numRows) + "," + to_string(numCols) + ").col(0))", new Col<double>(identity.col(0))));
        input.push_back(pair<string, void*>("Col(hilbertSub(" + to_string(numRows) + "," + to_string(numCols) + ").col(0))", new Col<double>(hilbertSub.col(0))));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getOOColVec() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePair : getGenDouble()) {
      double genDouble = *static_cast<double*>(keyValuePair.second);

      input.push_back(pair<string, void*>("Col({" + keyValuePair.first + "})", new Col<double>({genDouble})));
    }

    return input;
  }

  vector<pair<string, void*>> Input::getGenRowVec() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumCols()) {
      int numCols = *static_cast<int*>(keyValuePairA.second);

      input.push_back(pair<string, void*>("Row(zeros(1," + to_string(numCols) + "))", new Row<double>(zeros<Row<double>>(numCols))));
      input.push_back(pair<string, void*>("Row(ones(1," + to_string(numCols) + "))", new Row<double>(ones<Row<double>>(numCols))));

      for (pair<string, void*> keyValuePairB : getNumRows()) {
        int numRows = *static_cast<int*>(keyValuePairB.second);

        Mat<double> identity = eye<Mat<double>>(numRows, numCols);
        Mat<double> hilbert = getHilbertMatrix(numRows, numCols);
        Mat<double> kms = getKMSMatrix(numRows, numCols);

        input.push_back(pair<string, void*>("Row(eye(" + to_string(numRows) + "," + to_string(numCols) + ").row(0))", new Row<double>(identity.row(0))));
        input.push_back(pair<string, void*>("Row(hilbert(" + to_string(numRows) + "," + to_string(numCols) + ").row(0))", new Row<double>(hilbert.row(0))));
        input.push_back(pair<string, void*>("Row(kms(" + to_string(numRows) + "," + to_string(numCols) + ").row(0))", new Row<double>(kms.row(0))));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getMonRowVec() {
    return {
      pair<string, void*>("Row({0,1,...,n})", new Row<double>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})),
      pair<string, void*>("Row({0,0.1,...,1})", new Row<double>({0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1})),
      pair<string, void*>("Row({-10,-5,10})", new Row<double>({-10, -5, 10})),
      pair<string, void*>("Row({-inf,0,inf})", new Row<double>({datum::inf, 0, -datum::inf})),
      pair<string, void*>("Row({0})", new Row<double>({0})),
      pair<string, void*>("Row({-inf})", new Row<double>({-datum::inf})),
      pair<string, void*>("Row({inf})", new Row<double>({datum::inf}))
    };
  }

  vector<pair<string, void*>> Input::getLogicRowVec() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePairA : getNumCols()) {
      int numCols = *static_cast<int*>(keyValuePairA.second);

      input.push_back(pair<string, void*>("Row(zeros(1," + to_string(numCols) + "))", new Row<double>(zeros<Row<double>>(numCols))));
      input.push_back(pair<string, void*>("Row(ones(1," + to_string(numCols) + "))", new Row<double>(ones<Row<double>>(numCols))));

      for (pair<string, void*> keyValuePairB : getNumRows()) {
        int numRows = *static_cast<int*>(keyValuePairB.second);

        Mat<double> identity = eye<Mat<double>>(numRows, numCols);
        Mat<double> hilbertSub = getHilbertMatrix(numRows, numCols) - 2.0/(numRows + numCols + 2);

        input.push_back(pair<string, void*>("Row(eye(" + to_string(numRows) + "," + to_string(numCols) + ").row(0))", new Row<double>(identity.row(0))));
        input.push_back(pair<string, void*>("Row(hilbertSub(" + to_string(numRows) + "," + to_string(numCols) + ").row(0))", new Row<double>(hilbertSub.row(0))));
      }
    }

    return input;
  }

  vector<pair<string, void*>> Input::getOORowVec() {
    vector<pair<string, void*>> input = {};

    for (pair<string, void*> keyValuePair : getGenDouble()) {
      double genDouble = *static_cast<double*>(keyValuePair.second);

      input.push_back(pair<string, void*>("Row({" + keyValuePair.first + "})", new Row<double>({genDouble})));
    }

    return input;
  }

  vector<pair<string, void*>> Input::getElemInds() {
    vector<vector<pair<string, void*>>> inputs = {};

    inputs.push_back({
      pair<string, void*>("Col({0})", new Col<double>({0})),
      pair<string, void*>("Row({0})", new Row<double>({0})),
      pair<string, void*>("Col({1,1,1,1,1})", new Col<double>({1, 1, 1, 1, 1})),
      pair<string, void*>("Row({1,1,1,1,1})", new Row<double>({1, 1, 1, 1, 1}))
    });

    for (pair<string, void*> keyValuePair : getNumElems()) {
      int numElems = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>("Col({" + to_string(numElems - 1) + "})", new Col<double>({static_cast<double>(numElems - 1)})),
        pair<string, void*>("Row({" + to_string(numElems - 1) + "})", new Row<double>({static_cast<double>(numElems - 1)})),
        pair<string, void*>("Col({" + to_string(numElems/2 - 1) + "," + to_string(numElems/2) + "," + to_string(numElems/2 + 1) + "})", new Col<double>({static_cast<double>(numElems/2 - 1), static_cast<double>(numElems/2), static_cast<double>(numElems/2 + 1)})),
        pair<string, void*>("Row({" + to_string(numElems/2 - 1) + "," + to_string(numElems/2) + "," + to_string(numElems/2 + 1) + "})", new Row<double>({static_cast<double>(numElems/2 - 1), static_cast<double>(numElems/2), static_cast<double>(numElems/2 + 1)}))
      });

      vector<double> sequenceA(numElems);
      vector<double> sequenceB(numElems);
      for(int n = 0; n < numElems; n++) {
        sequenceA.at(n) = n;
        sequenceB.at(n) = ((n % 2 == 0) ? static_cast<double>(n) : static_cast<double>(numElems - n));
      }

      inputs.push_back({
        pair<string, void*>("Col({0,1,...,n})", new Col<double>(sequenceA)),
        pair<string, void*>("Row({0,1,...,n})", new Row<double>(sequenceA)),
        pair<string, void*>("Col({0,n,1,n-1,...})", new Col<double>(sequenceB)),
        pair<string, void*>("Row({0,n,1,n-1,...})", new Row<double>(sequenceB)),
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getColInds() {
    vector<vector<pair<string, void*>>> inputs = {};

    inputs.push_back({
      pair<string, void*>("Col({0})", new Col<double>({0})),
      pair<string, void*>("Row({0})", new Row<double>({0})),
      pair<string, void*>("Col({1,1,1,1,1})", new Col<double>({1, 1, 1, 1, 1})),
      pair<string, void*>("Row({1,1,1,1,1})", new Row<double>({1, 1, 1, 1, 1}))
    });

    for (pair<string, void*> keyValuePair : getNumCols()) {
      int numCols = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>("Col({" + to_string(numCols - 1) + "})", new Col<double>({static_cast<double>(numCols - 1)})),
        pair<string, void*>("Row({" + to_string(numCols - 1) + "})", new Row<double>({static_cast<double>(numCols - 1)})),
        pair<string, void*>("Col({" + to_string(numCols/2 - 1) + "," + to_string(numCols/2) + "," + to_string(numCols/2 + 1) + "})", new Col<double>({static_cast<double>(numCols/2 - 1), static_cast<double>(numCols/2), static_cast<double>(numCols/2 + 1)})),
        pair<string, void*>("Row({" + to_string(numCols/2 - 1) + "," + to_string(numCols/2) + "," + to_string(numCols/2 + 1) + "})", new Row<double>({static_cast<double>(numCols/2 - 1), static_cast<double>(numCols/2), static_cast<double>(numCols/2 + 1)}))
      });

      vector<double> sequenceA(numCols);
      vector<double> sequenceB(numCols);
      for(int n = 0; n < numCols; n++) {
        sequenceA.at(n) = n;
        sequenceB.at(n) = ((n % 2 == 0) ? static_cast<double>(n) : static_cast<double>(numCols - n));
      }

      inputs.push_back({
        pair<string, void*>("Col({0,1,...,n})", new Col<double>(sequenceA)),
        pair<string, void*>("Row({0,1,...,n})", new Row<double>(sequenceA)),
        pair<string, void*>("Col({0,n,1,n-1,...})", new Col<double>(sequenceB)),
        pair<string, void*>("Row({0,n,1,n-1,...})", new Row<double>(sequenceB)),
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getRowInds() {
    vector<vector<pair<string, void*>>> inputs = {};

    inputs.push_back({
      pair<string, void*>("Col({0})", new Col<double>({0})),
      pair<string, void*>("Row({0})", new Row<double>({0})),
      pair<string, void*>("Col({1,1,1,1,1})", new Col<double>({1, 1, 1, 1, 1})),
      pair<string, void*>("Row({1,1,1,1,1})", new Row<double>({1, 1, 1, 1, 1}))
    });

    for (pair<string, void*> keyValuePair : getNumRows()) {
      int numRows = *static_cast<int*>(keyValuePair.second);

      inputs.push_back({
        pair<string, void*>("Col({" + to_string(numRows - 1) + "})", new Col<double>({static_cast<double>(numRows - 1)})),
        pair<string, void*>("Row({" + to_string(numRows - 1) + "})", new Row<double>({static_cast<double>(numRows - 1)})),
        pair<string, void*>("Col({" + to_string(numRows/2 - 1) + "," + to_string(numRows/2) + "," + to_string(numRows/2 + 1) + "})", new Col<double>({static_cast<double>(numRows/2 - 1), static_cast<double>(numRows/2), static_cast<double>(numRows/2 + 1)})),
        pair<string, void*>("Row({" + to_string(numRows/2 - 1) + "," + to_string(numRows/2) + "," + to_string(numRows/2 + 1) + "})", new Row<double>({static_cast<double>(numRows/2 - 1), static_cast<double>(numRows/2), static_cast<double>(numRows/2 + 1)}))
      });

      vector<double> sequenceA(numRows);
      vector<double> sequenceB(numRows);
      for(int n = 0; n < numRows; n++) {
        sequenceA.at(n) = n;
        sequenceB.at(n) = ((n % 2 == 0) ? static_cast<double>(n) : static_cast<double>(numRows - n));
      }

      inputs.push_back({
        pair<string, void*>("Col({0,1,...,n})", new Col<double>(sequenceA)),
        pair<string, void*>("Row({0,1,...,n})", new Row<double>(sequenceA)),
        pair<string, void*>("Col({0,n,1,n-1,...})", new Col<double>(sequenceB)),
        pair<string, void*>("Row({0,n,1,n-1,...})", new Row<double>(sequenceB)),
      });
    }

    return vectorUnion(inputs);
  }

  vector<pair<string, void*>> Input::getMatNormString() {
    return {
      pair<string, void*>("'inf'", new string("inf")),
      pair<string, void*>("'fro'", new string("fro"))
    };
  }

  vector<pair<string, void*>> Input::getVecNormString() {
    return {
      pair<string, void*>("'inf'", new string("inf")),
      pair<string, void*>("'-inf'", new string("-inf")),
      pair<string, void*>("'fro'", new string("fro"))
    };
  }

  vector<pair<string, void*>> Input::getSort() {
    return {
      pair<string, void*>("'ascend'", new string("ascend")),
      pair<string, void*>("'descend'", new string("descend"))
    };
  }

  vector<pair<string, void*>> Input::getSinValSel() {
    return {
      pair<string, void*>("'left'", new string("left")),
      pair<string, void*>("'right'", new string("right")),
      pair<string, void*>("'both'", new string("both"))
    };
  }

  vector<pair<string, void*>> Input::getDistrParam() {
    return {
      pair<string, void*>("distr_param(0,10)", new distr_param(0, 10)),
      pair<string, void*>("distr_param(1,1)", new distr_param(1, 1)),
      pair<string, void*>("distr_param(-5,6)", new distr_param(-5, 6))
    };
  }

  vector<pair<string, void*>> Input::getFill() {
    return {

    };
  }
}