#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    maze_t *ptr = malloc(sizeof(maze_t));
    if(ptr == NULL)
        return NULL;

    FILE *fileptr = fopen(fileName, "r"); 
    if(fileptr == NULL){
        free(ptr); 
        return NULL; 
    }

    fscanf(fileptr, "%d %d", &(ptr->width), &(ptr->height)); 

    // Allocate memory for the 2D array (cells)
    ptr->cells = malloc(ptr->height * sizeof(char *));
    for (int i = 0; i < ptr->height; i++) {
        ptr->cells[i] = malloc(ptr->width * sizeof(char));
    }
    //this manual creation of 2D arrays is some fried shit

    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width; j++){
            char c; 
            fscanf(fileptr, "%c", &c);
            while(c == '\n' || c == '\r'){
                fscanf(fileptr, "%c", &c); 
            } 

            ptr->cells[i][j] = c; 

            if(c == 'S'){
                ptr->startRow = i; 
                ptr->startColumn = j; 
            }
            if(c == 'E'){
                ptr->endRow = i; 
                ptr->endColumn = j; 
            }
        }
    }

    fclose(fileptr); 
    return ptr; 

}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    for(int i = 0; i < maze->height; i++){
        free(maze->cells[i]); 
    } 
    free(maze->cells);
    free(maze); 
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    for(int i = 0; i < maze->height; i++){
        for(int j = 0; j < maze->width; j++){
            printf("%c", maze->cells[i][j]); 
        }
        printf("\n"); 
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if (col < 0 || row < 0 || row >= maze->height || col >= maze->width)
        return 0;

    if ((row != maze->startRow || col != maze->startColumn) &&
        maze->cells[row][col] == 'S')
        return 0;

    if (maze->cells[row][col] == '%' || maze->cells[row][col] == '*' || maze->cells[row][col] == '~')
        return 0;

    if (maze->cells[row][col] == 'E')
        return 1;

    if (maze->cells[row][col] != 'S')
        maze->cells[row][col] = '*';

    if (solveMazeDFS(maze, col - 1, row) == 1)
        return 1;
    if (solveMazeDFS(maze, col, row - 1) == 1)
        return 1;
    if (solveMazeDFS(maze, col + 1, row) == 1)
        return 1;
    if (solveMazeDFS(maze, col, row + 1) == 1)
        return 1;

    if (maze->cells[row][col] != 'S')
        maze->cells[row][col] = '~';

    return 0;
}
