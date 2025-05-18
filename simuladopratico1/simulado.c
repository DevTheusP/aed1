#include <stdio.h>
#include <stdlib.h>
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    if (boardSize == 0 || word == NULL || strlen(word) == 0) {
        return false;
    }
    
    int m = boardSize;
    int n = boardColSize[0];
    
    
    bool dfs(int i, int j, int index) {
        
        if (index == strlen(word)) {
            return true;
        }
        
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[index] || board[i][j] == '#') {
            return false;
        }
        
        
        char temp = board[i][j];
        
        board[i][j] = '#';
        
       
        bool found = dfs(i+1, j, index+1) || 
                     dfs(i-1, j, index+1) || 
                     dfs(i, j+1, index+1) || 
                     dfs(i, j-1, index+1);
        
        board[i][j] = temp;
        
        return found;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0] && dfs(i, j, 0)) {
                return true;
            }
        }
    }
    
    return false;
}