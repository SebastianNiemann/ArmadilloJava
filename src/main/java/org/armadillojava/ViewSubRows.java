/*******************************************************************************
 * Copyright 2013 Sebastian Niemann <niemann@sra.uni-hannover.de> and contributors.
 * 
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://opensource.org/licenses/MIT
 *******************************************************************************/

package org.armadillojava;

/**
 * Provides shallow row vectors sub views of {@link AbstractMat}.
 * 
 * @author Sebastian Niemann <niemann@sra.uni-hannover.de>
 */
class ViewSubRows extends AbstractView {

  /**
   * The first position of the sub view within the underlying matrix
   */
  protected int _firstPosition;

  /**
   * The rows to skip within the underlying matrix to move from the last position of a column to one position before
   * the first element in the following column.
   */
  protected int _n_rows_skip;

  /**
   * The current row number within the sub view
   */
  protected int _row_number;

  /**
   * Creates a shallow copy of the specified matrix and restrict the access to a sub view.
   * 
   * @param matrix The matrix
   * @param first_row The first row position
   * @param last_row The last tow position
   */
  protected ViewSubRows(AbstractMat matrix, int first_row, int last_row) {
    super(matrix);

    n_rows = last_row - first_row + 1;
    n_cols = matrix.n_cols;
    n_elem = n_rows * n_cols;

    _firstPosition = first_row;
    _n_rows_skip = matrix.n_rows - last_row + first_row - 1;
  }

  @Override
  protected void iteratorReset() {
    _iterator = _firstPosition - 1;
    _row_number = -1;
  }

  @Override
  protected int iteratorNext() {
    ++_row_number;

    if (_row_number >= n_rows) {
      _iterator += _n_rows_skip;
      _row_number = 0;
    }

    return ++_iterator;
  }
}
