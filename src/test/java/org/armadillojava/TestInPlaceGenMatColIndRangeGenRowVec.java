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
 * Sebastian Niemann - Lead developer
 * Daniel Kiechle - Unit testing
 ******************************************************************************/
package org.armadillojava;

import static org.armadillojava.TestUtil.assertMatEquals;
import static org.junit.Assume.assumeThat;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.Matchers.lessThan;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import org.junit.runners.Parameterized.Parameters;

@RunWith(Parameterized.class)
public class TestInPlaceGenMatColIndRangeGenRowVec extends TestClass {

  @Parameters(name = "{index}: GenMat = {0}, ColIndRange = {2}, GenRowVec = {4}")
  public static Collection<Object[]> getParameters() {
    List<InputClass> inputClasses = new ArrayList<>();

    inputClasses.add(InputClass.GenMat);
    inputClasses.add(InputClass.ColIndRange);
    inputClasses.add(InputClass.GenRowVec);

    return Input.getTestParameters(inputClasses);
  }

  @Parameter(0)
  public String    _genMatString;

  @Parameter(1)
  public Mat       _genMat;

  protected Mat    _copyOfGenMat;

  @Parameter(2)
  public String    _colIndRangeString;

  @Parameter(3)
  public Span      _colIndRange;

  protected Span   _copyOfColIndRange;

  @Parameter(4)
  public String    _genRowVecString;

  @Parameter(5)
  public Row    _genRowVec;

  protected Row _copyOfGenRowVec;

  @Before
  public void before() {
    _fileSuffix = _genMatString + "," + _colIndRangeString + "," + _genRowVecString;

    _copyOfGenMat = new Mat(_genMat);
    _copyOfColIndRange = new Span(_colIndRange._first, _colIndRange._last);
    _copyOfGenRowVec = new Row(_genRowVec);
  }

  @After
  public void after() {
    _genMat.inPlace(Op.EQUAL, _copyOfGenMat);
    _colIndRange = new Span(_copyOfColIndRange._first, _copyOfColIndRange._last);
    _genRowVec.inPlace(Op.EQUAL, _copyOfGenRowVec);
  }

  @Test
  public void testMatColsEqual() throws IOException {
    assumeThat(_colIndRange._last, is(lessThan(_genMat.n_cols)));
    assumeThat(_genMat.n_rows, is(1));
    assumeThat(_genRowVec.n_cols, is(_colIndRange._last - _colIndRange._first + 1));

    _genMat.cols(_colIndRange._first, _colIndRange._last, Op.EQUAL, _genRowVec);

    assertMatEquals(_genMat, load("Mat.colsEqual"));
  }

  @Test
  public void testMatColsPlus() throws IOException {
    assumeThat(_colIndRange._last, is(lessThan(_genMat.n_cols)));
    assumeThat(_genMat.n_rows, is(1));
    assumeThat(_genRowVec.n_cols, is(_colIndRange._last - _colIndRange._first + 1));

    _genMat.cols(_colIndRange._first, _colIndRange._last, Op.PLUS, _genRowVec);

    assertMatEquals(_genMat, load("Mat.colsPlus"));
  }

  @Test
  public void testMatColsMinus() throws IOException {
    assumeThat(_colIndRange._last, is(lessThan(_genMat.n_cols)));
    assumeThat(_genMat.n_rows, is(1));
    assumeThat(_genRowVec.n_cols, is(_colIndRange._last - _colIndRange._first + 1));

    _genMat.cols(_colIndRange._first, _colIndRange._last, Op.MINUS, _genRowVec);

    assertMatEquals(_genMat, load("Mat.colsMinus"));
  }

  @Test
  public void testMatColsTimes() throws IOException {
    assumeThat(_colIndRange._last, is(lessThan(_genMat.n_cols)));
    assumeThat(_genMat.n_rows, is(1));
    assumeThat(_genRowVec.n_cols, is(_colIndRange._last - _colIndRange._first + 1));

    _genMat.cols(_colIndRange._first, _colIndRange._last, Op.ELEMTIMES, _genRowVec);

    assertMatEquals(_genMat, load("Mat.colsElemTimes"));
  }

  @Test
  public void testMatColsDivide() throws IOException {
    assumeThat(_colIndRange._last, is(lessThan(_genMat.n_cols)));
    assumeThat(_genMat.n_rows, is(1));
    assumeThat(_genRowVec.n_cols, is(_colIndRange._last - _colIndRange._first + 1));
    
    _genMat.cols(_colIndRange._first, _colIndRange._last, Op.ELEMDIVIDE, _genRowVec);

    assertMatEquals(_genMat, load("Mat.colsElemDivide"));
  }

}
