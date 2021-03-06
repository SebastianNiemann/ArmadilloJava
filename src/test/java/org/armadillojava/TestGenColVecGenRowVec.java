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
import static org.junit.Assert.assertThat;
import static org.junit.Assume.assumeThat;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.number.IsCloseTo.closeTo;

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
public class TestGenColVecGenRowVec extends TestClass {

  @Parameters(name = "{index}: GenColVec = {0}, GenRowVec = {2}")
  public static Collection<Object[]> getParameters() {
    List<InputClass> inputClasses = new ArrayList<>();

    inputClasses.add(InputClass.GenColVec);
    inputClasses.add(InputClass.GenRowVec);

    return Input.getTestParameters(inputClasses);
  }

  @Parameter(0)
  public String _genColVecString;

  @Parameter(1)
  public Col    _genColVec;

  protected Col _copyOfGenColVec;

  @Parameter(2)
  public String _genRowVecString;

  @Parameter(3)
  public Row    _genRowVec;

  protected Row _copyOfGenRowVec;

  @Before
  public void before() {
    _fileSuffix = _genColVecString + "," + _genRowVecString;

    _copyOfGenColVec = new Col(_genColVec);
    _copyOfGenRowVec = new Row(_genRowVec);
  }

  @After
  public void after() {
    assertMatEquals(_genColVec, _copyOfGenColVec, 0);
    assertMatEquals(_genRowVec, _copyOfGenRowVec, 0);
  }

  @Test
  public void testArmaToeplitz() throws IOException {
    assertMatEquals(Arma.toeplitz(_genColVec, _genRowVec), load("Arma.toeplitz"));
  }

  @Test
  public void testArmaDot() throws IOException {
    assumeThat(_genColVec.n_elem, is(_genRowVec.n_elem));

    double expected = load("Arma.dot")._data[0];
    double actual = Arma.dot(_genColVec, _genRowVec);

    if (Double.isInfinite(expected) || Double.isNaN(expected)) {
      assertThat(actual, is(expected));
    } else {
      assertThat(actual, is(closeTo(expected, Math.abs(expected) * 1e-12)));
    }
  }

  @Test
  public void testArmaNorm_dot() throws IOException {
    assumeThat(_genColVec.n_elem, is(_genRowVec.n_elem));

    double expected = load("Arma.norm_dot")._data[0];
    double actual = Arma.norm_dot(_genColVec, _genRowVec);

    if (Double.isInfinite(expected) || Double.isNaN(expected)) {
      assertThat(actual, is(expected));
    } else {
      assertThat(actual, is(closeTo(expected, Math.abs(expected) * 1e-12)));
    }
  }

  @Test
  public void testArmaConv() throws IOException {
    assertMatEquals(Arma.conv(_genColVec, _genRowVec), load("Arma.conv"));
  }

  @Test
  public void testArmaCor() throws IOException {
    assumeThat(_genColVec.n_rows, is(_genRowVec.n_rows));
    assumeThat(_genColVec.n_cols, is(_genRowVec.n_cols));

    double expected = load("Arma.cor")._data[0];
    double actual = Arma.cor(_genColVec, _genRowVec);

    if (Double.isInfinite(expected) || Double.isNaN(expected)) {
      assertThat(actual, is(expected));
    } else {
      assertThat(actual, is(closeTo(expected, Math.abs(expected) * 1e-12)));
    }
  }

  @Test
  public void testArmaCov() throws IOException {
    assumeThat(_genColVec.n_rows, is(_genRowVec.n_rows));
    assumeThat(_genColVec.n_cols, is(_genRowVec.n_cols));

    double expected = load("Arma.cov")._data[0];
    double actual = Arma.cov(_genColVec, _genRowVec);

    if (Double.isInfinite(expected) || Double.isNaN(expected)) {
      assertThat(actual, is(expected));
    } else {
      assertThat(actual, is(closeTo(expected, Math.abs(expected) * 1e-12)));
    }
  }

  @Test
  public void testArmaCross() throws IOException {
    Col tempGenColVec = new Col(_genColVec);
    tempGenColVec.resize(3);
    Row tempGenRowVec = new Row(_genRowVec);
    tempGenRowVec.resize(3);

    assertMatEquals(Arma.cross(tempGenColVec, tempGenRowVec), load("Arma.cross"));
  }

  @Test
  public void testArmaJoin_rows() throws IOException {
    assumeThat(_genColVec.n_rows, is(_genRowVec.n_rows));

    assertMatEquals(Arma.join_rows(_genColVec, _genRowVec), load("Arma.join_rows"));
  }

  @Test
  public void testArmaJoin_horiz() throws IOException {
    assumeThat(_genColVec.n_rows, is(_genRowVec.n_rows));

    assertMatEquals(Arma.join_horiz(_genColVec, _genRowVec), load("Arma.join_horiz"));
  }

  @Test
  public void testArmaJoin_cols() throws IOException {
    assumeThat(_genColVec.n_cols, is(_genRowVec.n_cols));

    assertMatEquals(Arma.join_cols(_genColVec, _genRowVec), load("Arma.join_cols"));
  }

  @Test
  public void testArmaJoin_vert() throws IOException {
    assumeThat(_genColVec.n_cols, is(_genRowVec.n_cols));

    assertMatEquals(Arma.join_vert(_genColVec, _genRowVec), load("Arma.join_vert"));
  }

  @Test
  public void testArmaKron() throws IOException {
    assertMatEquals(Arma.kron(_genColVec, _genRowVec), load("Arma.kron"));
  }
  
  
  @Test
  public void testColPlus() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.plus(_genRowVec), load("Col.plus"));
  }

  @Test
  public void testColMinus() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.minus(_genRowVec), load("Col.minus"));
  }
  
  @Test
  public void testColTimes() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_cols));
    assumeThat(_genRowVec.is_finite(), is(true));
    assumeThat(_genColVec.is_finite(), is(true));
    
    assertMatEquals(_genColVec.times(_genRowVec), load("Col.times"));
  }

  @Test
  public void testColElemTimes() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.elemTimes(_genRowVec), load("Col.elemTimes"));
  }

  @Test
  public void testColElemDivide() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.elemDivide(_genRowVec), load("Col.elemDivide"));
  }

  @Test
  public void testColEquals() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.equals(_genRowVec), load("Col.equals"));
  }

  @Test
  public void testColNonEquals() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.nonEquals(_genRowVec), load("Col.nonEquals"));
  }

  @Test
  public void testColGreaterThan() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.greaterThan(_genRowVec), load("Col.greaterThan"));
  }

  @Test
  public void testColLessThan() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.lessThan(_genRowVec), load("Col.lessThan"));
  }

  @Test
  public void testColStrictGreaterThan() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.strictGreaterThan(_genRowVec), load("Col.strictGreaterThan"));
  }

  @Test
  public void testColStrictLessThan() throws IOException {
    assumeThat(_genRowVec.n_rows, is(_genColVec.n_rows));
    assumeThat(_genRowVec.n_cols, is(_genColVec.n_cols));
    
    assertMatEquals(_genColVec.strictLessThan(_genRowVec), load("Col.strictLessThan"));
  }

}
