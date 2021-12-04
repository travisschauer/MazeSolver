// Travis Schauer
// 12/07/20
// Kramer 3700
// This program generates a random maze and then solves it
// It then outputs the results as .ps file

#include <iostream>
#include "pathfinder.h"
#include "sampler.h"
#include "DisjointSetForest.h"
#include "stack.h"

using namespace std;

uint32_t encode(uint32_t row,uint32_t col,uint32_t dir, uint32_t nR, uint32_t nC) {
    return (dir * nR + row) * nC + col;
}

void decode(uint32_t val,uint32_t &row,uint32_t &col,uint32_t &dir, uint32_t nR, uint32_t nC) {
    col = val % nC;
    val /= nC;
    row = val % nR;
    dir = val / nR;
}

void generateMaze(uint8_t maze[][MAX_COLS],int32_t nR,int32_t nC) {
    Sampler
        sampler(2*nR*nC-nR-nC);
    DisjointSetForest
        dsf(nR*nC);
    uint32_t
        nRemoved = 0,
        r,c,
        r2,c2,
        w1,w2,
        cell1,cell2;

    for (r = 0; r < nR; r++){
        for (c = 0; c < nC; c++){
            maze[r][c] = 15;
        }
    }


    // loop until nR * nC - 1 walls removed
    while (nRemoved < nR * nC - 1) {

        // get wall at random
        uint32_t
            w = sampler.sample();

        // if it is a right wall...
        if (w < nR * (nC - 1)) {

            // calculate r,c,r2,c2,w1,w2
            r = w / (nC - 1);
            c = w % (nC - 1);
            w1 = WALL_RIGHT;
            w2 = WALL_LEFT;
            r2 = r;
            c2 = c + 1;

            // encode cell1 and cell2
            cell1 = encode(r,c,0,nR,nC);
            cell2 = encode(r2,c2,0,nR,nC);
        } else {        // ... else it's a down wall

            // adjust w
            w -= nR*(nC - 1);

            // calculate r,c,r2,c2,w1,w2
            r = w % (nR - 1);
            c = w / (nR - 1);
            w1 = WALL_DOWN;
            w2 = WALL_UP;
            r2 = r + 1;
            c2 = c;

            // encode cell1 and cell2
            cell1 = encode(r,c,0,nR,nC);
            cell2 = encode(r2,c2,0,nR,nC);
        }

        // if cell1 and cell2 are not connected...
        if (dsf.dsfFind(cell1) != dsf.dsfFind(cell2)) {

            // connect them
            dsf.dsfUnion(cell1,cell2);

            // remove w1 from r,c
            maze[r][c] &= ~w1;

            // remove w2 from r2,c2
            maze[r2][c2] &= ~w2;

            // increment removed count
            nRemoved++;
        }
    }
}

void solveMaze(uint8_t maze[][MAX_COLS],int32_t nR,int32_t nC) {
    uint32_t r, r2, c, c2, d, cell;
    Stack<uint32_t> data;

    // s.push(encode(0,0,0,nR,nC))
    data.push(encode(0,0,0,nR,nC));

    // mark maze[0][0] as VISITED
    maze[0][0] |= VISITED;

    // loop forever
    while (true){

        // decode top of stack into r,c,d
        cell = data.peek();
        decode(cell, r, c, d, nR, nC);

        // if r,c is (nR-1),(nC-1) then break
        if (r == (nR - 1) && c == (nC - 1)){
            break;
        }


        // if d == 4, you're at a dead end
        if (d == 4){

            // mark maze[r][c] as a DEAD_END
            maze[r][c] |= DEAD_END;

            // s.pop()
            data.pop();

        // else
        } else {

            // calculate r2,c2 as neighbor in direction d
            if (d == 0){
                r2 = r - 1;
                c2 = c;
            } else if (d == 1){
                r2 = r;
                c2 = c + 1;
            } else if (d == 2){
                r2 = r + 1;
                c2 = c;
            } else if (d == 3){
                r2 = r;
                c2 = c - 1;
            }

            // replace top of stack with encode(r,c,d+1,nR,nC)
            data.pop();
            data.push(encode(r,c,d+1,nR,nC));

            int wall = 1 << d;

            // if no wall exists in direction d AND...
            // ... maze[r2][c2] is NOT VISITED then...
            if ((maze[r][c] & wall) == 0 && (maze[r2][c2] & VISITED) == 0){

                // s.push(encode(r2,c2,0,nR,nC))
                data.push(encode(r2,c2,0,nR,nC));

                // mark maze[r2][c2] as VISITED
                maze[r2][c2] |= VISITED;

            }
        }
    }
}

int main(int argc,char *argv[]) {
    int32_t
        nR,nC;
    uint8_t
        maze[MAX_ROWS][MAX_COLS];

    if (argc != 3) {
        cout << "Usage: " << argv[0] << " numrows numcols" << endl;
        return 1;
    }

    nR = strtol(argv[1],nullptr,10);
    nC = strtol(argv[2],nullptr,10);

    // verify that 0 < nR,nC <= 50
    if (nR <= 0 || nR > 50){
        cout << "Invalid number of rows" << endl;
        return 1;
    }

    if (nC <= 0 || nC > 50){
        cout << "Invalid number of columns" << endl;
        return 1;
    }

    // call maze generator
    generateMaze(maze,nR,nC);

    // call maze solver
    solveMaze(maze,nR,nC);

    // call Dr. Bob's output function
    printMaze(maze,nR,nC);

    return 0;
}