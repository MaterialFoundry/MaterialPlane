/**
 *  Library to perfom homography transforms
 *  Author: C Deenen
 */

#include "Arduino.h"
#include "MatrixMath.h"
#include "math.h"
#include "homography.h"

homography::homography(){
    //initialize the homography array
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            _H[i][j] = 0;

    //initialize bounds array
    _bounds[0][0] = 0;
    _bounds[0][1] = 0;
    _bounds[0][2] = 1023;
    _bounds[0][3] = 1023;
    _bounds[1][0] = 1023;
    _bounds[1][1] = 0;
    _bounds[1][2] = 0;
    _bounds[1][3] = 1023;
}

void homography::calculateHomographyMatrix() {
    mtx_type A[8][8];
    mtx_type AT[8][8];
    mtx_type B[8][8];
    mtx_type C[8] ={_bounds[0][0],_bounds[1][0],
                  _bounds[0][1],_bounds[1][1],
                  _bounds[0][2],_bounds[1][2],
                  _bounds[0][3],_bounds[1][3]};
    mtx_type D[8];
    mtx_type E[8];

    for (int i=0; i<4; i++){
        A[0][i*2] = _calArray[0][i];
        A[0][i*2+1] = 0;
        A[1][i*2] = _calArray[1][i];
        A[1][i*2+1] = 0;
        A[2][i*2] = 1;
        A[2][i*2+1] = 0;
        A[3][i*2] = 0;
        A[3][i*2+1] = _calArray[0][i];
        A[4][i*2] = 0;
        A[4][i*2+1] = _calArray[1][i];
        A[5][i*2] = 0;
        A[5][i*2+1] = 1;
        A[6][i*2] = (float)-_bounds[0][i]*_calArray[0][i];
        A[6][i*2+1] = (float)-_bounds[1][i]*_calArray[0][i];
        A[7][i*2] = (float)-_bounds[0][i]*_calArray[1][i];
        A[7][i*2+1] = (float)-_bounds[1][i]*_calArray[1][i];
    }

    Matrix.Transpose((mtx_type*)A, 8, 8, (mtx_type*)AT);
    Matrix.Multiply((mtx_type*)A, (mtx_type*)AT, 8, 8, 8, (mtx_type*)B);
    Matrix.Invert((mtx_type*)B, 8);
    Matrix.Multiply((mtx_type*)C, (mtx_type*)AT, 8, 8, 8, (mtx_type*)D);
    Matrix.Multiply((mtx_type*)D, (mtx_type*)B, 8, 8, 8, (mtx_type*)E);

    for (int i=0; i<3; i++) {
        _H[i][0] = E[i];
        _H[i][1] = E[i+3];
        _H[i][2] = E[i+6];
    }
    _H[2][2] = 1;
}

void homography::calculateCoordinates(int x, int y){
    mtx_type TP[3] = {x,y,1};
    mtx_type outputTemp[3];
    Matrix.Multiply((mtx_type*)TP, (mtx_type*)_H, 1, 3, 3, (mtx_type*)outputTemp);
    outputTemp[0] /= outputTemp[2];
    outputTemp[1] /= outputTemp[2];
    _x = round(outputTemp[0]);
    _y = round(outputTemp[1]);
}

int homography::getX(){
    return _x;
}

int homography::getY(){
    return _y;
}

void homography::setCalArray(int point,int axis, int value){
    _calArray[axis][point] = value;
}

int homography::getCalArray(int point, int axis){
    return _calArray[axis][point];
}

void homography::orderCalArray(){
    uint16_t calTempX[4], calTempY[4];

    //Store the calibration values in temporary arrays
    for (int i=0; i<4; i++){
        calTempX[i] = _calArray[0][i];
        calTempY[i] = _calArray[1][i];
    }

    //Order by size of X array
    uint8_t maxPos;
    for (int i=0; i< 4; i++) {
        maxPos = findMax(calTempX);
        _calArray[0][i] = calTempX[maxPos];
        _calArray[1][i] = calTempY[maxPos];
        calTempX[maxPos] = 0;
        maxPos = findMax(calTempX);
    }

    //Make temporary arrays the same as calibration array
    for (int i=0; i<4; i++){
        calTempX[i] = _calArray[0][i];
        calTempY[i] = _calArray[1][i];
    }

    //Order the 2 points with highest x value, so point 0 has a higher y value than point 1
    if (_calArray[1][1] > _calArray[1][0]) {
        _calArray[0][0] = calTempX[1];
        _calArray[1][0] = calTempY[1];
        _calArray[0][1] = calTempX[0];
        _calArray[1][1] = calTempY[0];
    }

    //Order the 2 points with lowest x value, so point 3 has a higher y value than point 2
    if (_calArray[1][3] < _calArray[1][2]) {
        _calArray[0][2] = calTempX[3];
        _calArray[1][2] = calTempY[3];
        _calArray[0][3] = calTempX[2];
        _calArray[1][3] = calTempY[2];
    }

    //Get the homography array
    calculateHomographyMatrix();
}


/**
 * Finds the index of the highest value in an array
 */
uint8_t homography::findMax(uint16_t ARRAY[]){
  uint16_t maxValue = ARRAY[0];
  uint8_t maxPos = 0;
  for (int i=1; i<4; i++){
    if (ARRAY[i] > maxValue){
      maxValue = ARRAY[i];
      maxPos = i;
    }
  }
  return maxPos;
}
