/*-------------------------------------------------------------------------------------------
 * this program is a modification of: https://github.com/Great-Hill-Corporation/quickBlocks/blob/7b38e3777d1a184f4ba479438b4d482cd7ed5962/src/examples/simple/simple.cpp which is licsensed under GPLv3 (see the following)
 * therefor this modification is also GPLv3 and I am the author of the modification. 

 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2018 Great Hill Corporation (http://greathill.com)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include "etherlib.h"

/*-------------------------------------------------------------------------
 * Name:    Simple
 * Purpose: To provide the easiest introduction to the QBlocks library.
 *          Simply request a block from Infura and print it to the screen.
 *------------------------------------------------------------------------*/
int main(int argc, const char *argv[]) {

    // Initialize the system and tell it where to find the blockchain data.
    etherlib_init();
    getCurlContext()->headers  = "Content-Type: application/json\n";
    getCurlContext()->baseURL = "http://localhost:8545";
    CBlock block;
    for (int i =0;i<3274533;i++){
      try{
	getBlock(block, i);
	cout << block << endl;
      } catch(...){}
    }
    etherlib_cleanup();
    return 0;
}
