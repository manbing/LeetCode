bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    int i = 0, j = 0;
    int col = *matrixColSize;
    
    i = matrixSize - 1;
    j = 0;
    
    while (i >= 0 && j < col) {
        int value = *(*(matrix + i) + j);
        
        if (value == target)
            return true;
        else if ( value > target)
            i--;
        else
            j++;
    }
    
    return false;
}
