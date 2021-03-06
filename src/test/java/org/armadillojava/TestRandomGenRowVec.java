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
public class TestRandomGenRowVec extends TestClass {

  @Parameters(name = "{index}: Random = {0}, GenRowVec = {2}")
  public static Collection<Object[]> getParameters() {
    RNG.set_seed(123456789);
    
    List<InputClass> inputClasses = new ArrayList<>();

    inputClasses.add(InputClass.Random);
    inputClasses.add(InputClass.GenRowVec);

    return Input.getTestParameters(inputClasses);
  }

  @Parameter(0)
  public String _randomString;

  @Parameter(1)
  public int    _random;

  protected int _copyOfRandom;

  @Parameter(2)
  public String _genRowVecString;

  @Parameter(3)
  public Row    _genRowVec;

  protected Row _copyOfGenRowVec;

  @Before
  public void before() {
    _fileSuffix = _randomString + "," + _genRowVecString;

    _copyOfGenRowVec = new Row(_genRowVec);
    _copyOfRandom = new Integer(_random);
  }

  @After
  public void after() {
    assertMatEquals(_genRowVec, _copyOfGenRowVec, 0);
    assertThat(_random, is(_copyOfRandom));
  }

  @Test
  public void testArmaShuffle() throws IOException {
    assumeThat(_genRowVec.is_finite(), is(true));

    Row result = Arma.shuffle(_genRowVec);
    for (int n = 2; n <= _random; n++) {
      result = (result.times(n)).plus(Arma.shuffle(_genRowVec)).divide(n + 1);
    }
    assertMatEquals(result.minus(load("Arma.shuffle")), Arma.zeros(result.n_rows, result.n_cols), 1);
  }

}
