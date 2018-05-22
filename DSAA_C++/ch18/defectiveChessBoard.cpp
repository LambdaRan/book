

#include <iostream>

#include <assert.h>
#include <math.h>


// 残缺棋盘
// 对于任意的k，恰有exp2（2k）种不同的残缺棋盘
// 所需的三格板总数为（exp2(2k) - 1） / 3


int **board; // 棋盘
int tile = 1; // 当前使用的三格板

// topRow 表示棋盘上左上角方格的行号
// topColumn 表示棋盘上左上角方格的列号
// defectRow 表示残缺方格的行号
// defectColumn 表示残缺方格的列号
// size 表示棋盘一个边的长度
void tileBoard(int topRow, int topColumn, int defectRow, int defectColumn, int size)
{
    if (size == 1) return;
    int tileToUse = tile++;
    int quadrantSize = size / 2;

    // 覆盖左上角象限
    if (defectRow < topRow + quadrantSize && 
        defectColumn < topColumn + quadrantSize)
    {
        tileBoard(topRow, topColumn, defectRow, defectColumn, quadrantSize);
    }
    else   
    {   // 这个象限无残缺方格
        // 在右下角放置一个三格板
        board[topRow + quadrantSize - 1][topColumn + quadrantSize - 1] = tileToUse;
        // 覆盖剩余方格
        tileBoard(topRow, topColumn, 
                topRow + quadrantSize - 1,
                topColumn + quadrantSize - 1, quadrantSize);
    }

    // 覆盖右上角象限
    if (defectRow >= topRow && defectRow < topRow + quadrantSize &&
        defectColumn >= topColumn + quadrantSize && defectColumn < topColumn + size)
    {
        tileBoard(topRow, topColumn + quadrantSize, 
                    defectRow, defectColumn, quadrantSize);
    }
    else   
    {   // 这个象限无残缺方格
        // 在左下角放置一个三格板
        board[topRow + quadrantSize - 1][topColumn + quadrantSize] = tileToUse;
        // 覆盖剩余方格
        tileBoard(topRow, topColumn + quadrantSize, 
                topRow + quadrantSize - 1,
                topColumn + quadrantSize, quadrantSize);
    }

    // 覆盖左下角象限
    if (defectRow >= topRow + quadrantSize && defectRow < topRow + size &&
        defectColumn >= topColumn && defectColumn < topColumn + quadrantSize)
    {
        tileBoard(topRow + quadrantSize, topColumn, 
                    defectRow, defectColumn, quadrantSize);
    }
    else   
    {   // 这个象限无残缺方格
        // 在右上角放置一个三格板
        board[topRow + quadrantSize][topColumn + quadrantSize - 1] = tileToUse;
        // 覆盖剩余方格
        tileBoard(topRow + quadrantSize, topColumn, 
                topRow + quadrantSize,
                topColumn + quadrantSize - 1, quadrantSize);
    }

    // 覆盖右下角象限
    if (defectRow >= topRow + quadrantSize && defectRow < topRow + size &&
        defectColumn >= topColumn + quadrantSize && defectColumn < topColumn + size)
    {
        tileBoard(topRow + quadrantSize, topColumn + quadrantSize, 
                    defectRow, defectColumn, quadrantSize);
    }
    else   
    {   // 这个象限无残缺方格
        // 在左上角放置一个三格板
        board[topRow + quadrantSize][topColumn + quadrantSize] = tileToUse;
        // 覆盖剩余方格
        tileBoard(topRow + quadrantSize, topColumn + quadrantSize, 
                topRow + quadrantSize,
                topColumn + quadrantSize, quadrantSize);
    }
}

int main(void)
{

    std::cout << "请输入k值，创建一个exp2(k) * exp2(k) 大小的方形棋盘" << std::endl;
    int k = 0;
    std::cin >> k;

    int size = ::exp2(k);
    std::cout << "创建的方形棋盘大小为：" << size << " * " << size << std::endl;

    board = new int *[size];  
    for(int i = 0;i < size;i++)  
        board[i] = new int[size];  
    
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            board[i][j] = 0;

    std::cout << "在下标范围0~" << size-1 << "内输入残缺方格的行号列号" << std::endl;
    int defectR = 0;
    int defectC = 0;
    std::cin >> defectR >> defectC;

    if (defectR < size && defectC < size)
    {
        board[defectR][defectC] = -1;

        tileBoard(0, 0, defectR, defectC, size);
    }

    std::cout << "\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "共需要 " << tile << " 块方格板" << "\n";

    //释放空间  
    for(int i = 0; i < size; ++i)  
    {  
        delete board[i];  
        board[i] = NULL;  
    }  
    delete [] board;  
    board = NULL;  
    return 0;
}