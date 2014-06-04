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
using arma::Col;
using arma::span;
using arma::Row;

#include <InputClass.hpp>
using armadilloJava::InputClass;

#include <Input.hpp>
using armadilloJava::Input;

namespace armadilloJava {
  class ExpectedInPlaceGenColVecElemIndRangeGenRowVec : public Expected {
    public:
      ExpectedInPlaceGenColVecElemIndRangeGenRowVec() {
        cout << "Compute ExpectedInPlaceGenColVecElemIndRangeGenRowVec(): " << endl;

          vector<vector<pair<string, void*>>> inputs = Input::getTestParameters({
            InputClass::GenColVec,
            InputClass::ElemIndRange,
            InputClass::GenRowVec
          });

          for (vector<pair<string, void*>> input : inputs) {
            _fileSuffix = "";

            int n = 0;
            for (pair<string, void*> value : input) {
              switch (n) {
                case 0:
                  _fileSuffix += value.first;
                  _genColVec = *static_cast<Col<double>*>(value.second);
                  break;
                case 1:
                  _fileSuffix += "," + value.first;
                  _elemIndRange = *static_cast<span*>(value.second);
                  break;
                case 2:
                  _fileSuffix += "," + value.first;
                  _genRowVec = *static_cast<Row<double>*>(value.second);
                  break;
              }
              ++n;
            }

            cout << "Using input: " << _fileSuffix << endl;

            _copyOfGenColVec = _genColVec;
            _copyOfElemIndRange = _elemIndRange;
            _copyOfGenRowVec = _genRowVec;

			expectedColVecRowsEqual();

            _genColVec = _copyOfGenColVec;
            _elemIndRange = _copyOfElemIndRange;
            _genRowVec = _copyOfGenRowVec;
            
			expectedColVecRowsPlus();

            _genColVec = _copyOfGenColVec;
            _elemIndRange = _copyOfElemIndRange;
            _genRowVec = _copyOfGenRowVec;
            
			expectedColVecRowsMinus();

            _genColVec = _copyOfGenColVec;
            _elemIndRange = _copyOfElemIndRange;
            _genRowVec = _copyOfGenRowVec;
            
			expectedColVecRowsTimes();

            _genColVec = _copyOfGenColVec;
            _elemIndRange = _copyOfElemIndRange;
            _genRowVec = _copyOfGenRowVec;
            
			expectedColVecRowsDivide();

			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;

			expectedColVecSubvecEqual();

			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;

			expectedColVecSubvecPlus();

			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;

			expectedColVecSubvecMinus();

			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;

			expectedColVecSubvecTimes();
			  
			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;
			  
			expectedColVecSubvecDivide();

			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;

			expectedColVecSubvecSpanEqual();

			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;

			expectedColVecSubvecSpanPlus();
			  
			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;
			  
			expectedColVecSubvecSpanMinus();
			  
			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;
			  
			expectedColVecSubvecSpanTimes();
			  
			_genColVec = _copyOfGenColVec;
			_elemIndRange = _copyOfElemIndRange;
			_genRowVec = _copyOfGenRowVec;
			  
			expectedColVecSubvecSpanDivide();
          }

          cout << "done." << endl;
        }

    protected:
      Col<double> _genColVec;
      Col<double> _copyOfGenColVec;

      span _elemIndRange;
      span _copyOfElemIndRange;

      Row<double> _genRowVec;
      Row<double> _copyOfGenRowVec;


      void expectedColVecRowsEqual() {
    	if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
          return;
        }
        cout << "- Compute expectedColVecRowsEqual() ... ";

        _genColVec.rows(_elemIndRange.a, _elemIndRange.b) == _genRowVec;

        save<double>("Col.rowsEqual", _genColVec);
        cout << "done." << endl;
      }

      void expectedColVecRowsPlus() {
    	if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
          return;
        }
        cout << "- Compute expectedColVecRowsPlus() ... ";

        _genColVec.rows(_elemIndRange.a, _elemIndRange.b) += _genRowVec;

        save<double>("Col.rowsPlus", _genColVec);
        cout << "done." << endl;
      }

      void expectedColVecRowsMinus() {
    	if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
          return;
        }
        cout << "- Compute expectedColVecRowsMinus() ... ";

        _genColVec.rows(_elemIndRange.a,_elemIndRange.b) -= _genRowVec;

        save<double>("Col.rowsMinus", _genColVec);
        cout << "done." << endl;
      }

      void expectedColVecRowsTimes() {
    	if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
          return;
        }

        cout << "- Compute expectedColVecRowsTimes() ... ";

        _genColVec.rows(_elemIndRange.a, _elemIndRange.b) %= _genRowVec;

        save<double>("Col.rowsElemTimes", _genColVec);
        cout << "done." << endl;
      }

      void expectedColVecRowsDivide() {
    	if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
          return;
        }

        cout << "- Compute expectedColVecRowsDivide() ... ";

        _genColVec.rows(_elemIndRange.a, _elemIndRange.b) /= _genRowVec;

        save<double>("Col.rowsElemDivide", _genColVec);
        cout << "done." << endl;
      }

      void expectedColVecSubvecEqual() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
			  return;
		  }

		  cout << "- Compute expectedColVecSubvecEqual() ... ";

		  _genColVec.subvec(_elemIndRange.a, _elemIndRange.b) == _genRowVec;

		  save<double>("Col.subvecEqual", _genColVec);
		  cout << "done." << endl;
      }

      void expectedColVecSubvecPlus() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
			  return;
		  }
		  
		  cout << "- Compute expectedColVecSubvecPlus() ... ";

		  _genColVec.subvec(_elemIndRange.a, _elemIndRange.b) += _genRowVec;
		  
		  save<double>("Col.subvecPlus", _genColVec);
		  cout << "done." << endl;
      }
	  
      void expectedColVecSubvecMinus() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
			  return;
		  }
		  
		  cout << "- Compute expectedColVecSubvecMinus() ... ";

		  _genColVec.subvec(_elemIndRange.a, _elemIndRange.b) -= _genRowVec;
		  

		  save<double>("Col.subvecMinus", _genColVec);
		  cout << "done." << endl;
      }
	  
      void expectedColVecSubvecTimes() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
			  return;
		  }
		  
		  cout << "- Compute expectedColVecSubvecTimes() ... ";

		  _genColVec.subvec(_elemIndRange.a, _elemIndRange.b) %= _genRowVec;
		  
		  save<double>("Col.subvecElemTimes", _genColVec);
		  cout << "done." << endl;
      }
	  
      void expectedColVecSubvecDivide() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
			  return;
		  }
		  
		  cout << "- Compute expectedColVecSubvecDivide() ... ";

		  _genColVec.subvec(_elemIndRange.a, _elemIndRange.b) /= _genRowVec;
		  

		  save<double>("Col.subvecElemDivide", _genColVec);
		  cout << "done." << endl;
      }

      void expectedColVecSubvecSpanEqual() {
   	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
			  return;
		  }

		  cout << "- Compute expectedColVecSubvecSpanEqual() ... ";

		  _genColVec.subvec(_elemIndRange) == _genRowVec;

		  save<double>("Col.subvecSpanEqual", _genColVec);
		  cout << "done." << endl;
      }

      void expectedColVecSubvecSpanPlus() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
 			  return;
 		  }

 		  cout << "- Compute expectedColVecSubvecSpanPlus() ... ";

 		  _genColVec.subvec(_elemIndRange) += _genRowVec;

 		  save<double>("Col.subvecSpanPlus", _genColVec);
 		  cout << "done." << endl;
       }

       void expectedColVecSubvecSpanMinus() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
 			  return;
 		  }

 		  cout << "- Compute expectedColVecSubvecSpanMinus() ... ";

 		  _genColVec.subvec(_elemIndRange) -= _genRowVec;

 		  save<double>("Col.subvecSpanMinus", _genColVec);
 		  cout << "done." << endl;
       }

       void expectedColVecSubvecSpanTimes() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
 			  return;
 		  }

		  cout << "- Compute expectedColVecSubvecSpanTimes() ... ";

 		  _genColVec.subvec(_elemIndRange) %= _genRowVec;

 		  save<double>("Col.subvecSpanElemTimes", _genColVec);
 		  cout << "done." << endl;
       }

       void expectedColVecSubvecSpanDivide() {
    	  if(!_genColVec.in_range(_elemIndRange) || _genRowVec.n_cols != _genColVec.n_cols || _genRowVec.n_rows != (_elemIndRange.b-_elemIndRange.a)+1) {
 			  return;
 		  }

 		  cout << "- Compute expectedColVecSubvecSpanDivide() ... ";

 		  _genColVec.subvec(_elemIndRange) /= _genRowVec;

 		  save<double>("Col.subvecSpanElemDivide", _genColVec);
 		  cout << "done." << endl;
       }
	  
  };
}
