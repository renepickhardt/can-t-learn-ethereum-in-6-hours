# Disclaimer: 
This repository is a quick hack for a programming exercise given by Mariusz Nowostawski ( https://www.ntnu.edu/employees/mariusz.nowostawski ). It is by no means complete or beautiful. I was only able to invest 6 hours with a technology I previously have never looked at and this is the intermediate result together with some thoughts. My previous experience is with the bitcoin and lightning network protocol . I have the feeling that I made some wrong assumptions on how ethereum works and / or the cpp lib that I have used is either broken or was not used correctly by me. I still share the small amount of code I wrote as well as my thoughts on it. In doubt look at the end of this Readme in sections (Limitations, Mistakes, Conclusion)

# Programming Exercise Ethereum: 
Task: Consider an Ethereum blockchain. Pick any testnet that you see fit. Write a simplest program that checks which of the smart contracts deployed on the network (a testnet of your choice) has the largest Ether balance (A) and which one has the largest amount of transactions that has been executed on its behalf (B). Which one is easier to answer? A or B? Why? 

# Own reformulation: 
(A) largest amount is how much ether was sent to the contract in total minus how much ether flew away. Look at the value field of transactions. (found later out that for smart ontracts the value field seems to be always 0 so that I probably would have had to use gas, gasprice and used gas.)
(B) largest amount of tx on its behalf. Count how many tx have been flowing in and out of this contract address?

# Approach: 
A quick google search explains how there is no UTXO set in Etherum which would have been the natural thing to look at. However once one has an Ethereum node installed and testchain synched there exists tools which can be used to parse the level.db (which is the internal storage of ethernet blocks) to get a list of all blocks with all transactions in a json format. 

I followed this tutorial ( https://gist.github.com/cryptogoth/10a98e8078cfd69f7ca892ddbdcf26bc ) to get my rinkesby testnet node running. There was no particular reason why I opted for the rinkesby testnet. While searching for general information this tutorial seemed good. Since I did not want to reimplement the data format for the blocks and transactions I looked for an ethereum blockchain parser which I found in this git respository: https://github.com/Great-Hill-Corporation/quickBlocks I followed the install instructions and particularly this issues https://github.com/Great-Hill-Corporation/quickBlocks/issues/632 to adapt this file: https://github.com/Great-Hill-Corporation/quickBlocks/blob/7b38e3777d1a184f4ba479438b4d482cd7ed5962/src/examples/simple/simple.cpp with which I was now able to extract every block and print the out the data in a human readable json format to stdout. This cpp-file took less than 1 minute to extract 10k blocks. With roughly 3.5 Million blocks this would run 350 Minutes or roughly 6 hours which I thought is fair enough.

The JSON of block 3911 looked like this:
```
{
    "gasLimit": 4712388,
    "gasUsed": 155085,
    "hash": "0xea841221179e37ca9cc23424b64201d8805df327c3296a513e9f1fe6faa5ffb3",
    "blockNumber": 3911,
    "parentHash": "0x488f0453a8d64cc609aaa8636b778f4142ed14f79efd345b26afdda396886cc9",
    "miner": "0x0",
    "difficulty": 2,
    "price": 0,
    "finalized": 0,
    "timestamp": 1492069109,
    "transactions": [
        {
            "hash": "0x2dd50756cfd189177d0de4d65b7926459d7bb01de197c26517d05cd2b1c77ebc",
            "blockHash": "0xdb16f0d4465f2fd79f10ba539b169404a3e026db1be082e7fd6071b4c5f37db7",
            "blockNumber": 55,
            "transactionIndex": 0,
            "nonce": 0,
            "timestamp": 1492069109,
            "from": "0x31b98d14007bdee637298086988a0bbd31184523",
            "to": "0x2ed530faddb7349c1efdbf4410db2de835a004e4",
            "value": 1000000000000000000,
            "gas": 21000,
            "gasPrice": 20000000000,
            "input": "0x",
            "receipt": {
                "contractAddress": "0x0",
                "gasUsed": 21000,
                "logs": [],
                "status": null
            },
            "gasUsed": 21000
        },
        {
            "hash": "0x5d72db8affa6090bf7226b1c135f4324528a1a8da0cc95816d101357381abc54",
            "blockHash": "0xacb74aa08838896ad60319bce6e07c92edb2f5253080eb3883549ed8f57ea679",
            "blockNumber": 3907,
            "transactionIndex": 0,
            "nonce": 1,
            "timestamp": 1492069109,
            "from": "0x31b98d14007bdee637298086988a0bbd31184523",
            "to": "0xbedcf417ff2752d996d2ade98b97a6f0bef4beb9",
            "value": 1000000000000000000,
            "gas": 21000,
            "gasPrice": 20000000000,
            "input": "0x",
            "receipt": {
                "contractAddress": "0x0",
                "gasUsed": 21000,
                "logs": [],
                "status": null
            },
            "gasUsed": 21000
        },
        {
            "hash": "0xe5854bda43d2dff2c4c809e044ad5ac9c1f34ff22dbf0931459858575896c967",
            "blockHash": "0xea841221179e37ca9cc23424b64201d8805df327c3296a513e9f1fe6faa5ffb3",
            "blockNumber": 3911,
            "transactionIndex": 0,
            "nonce": 0,
            "timestamp": 1492069109,
            "from": "0xbedcf417ff2752d996d2ade98b97a6f0bef4beb9",
            "to": "0x0",
            "value": 0,
            "gas": 4700000,
            "gasPrice": 20000000000,
            "input": "0x6060604052341561000c57fe5b5b6101828061001c6000396000f30060606040526000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff168063230925601461003b575bfe5b341561004357fe5b61008360048080356000191690602001909190803560ff1690602001909190803560001916906020019091908035600019169060200190919050506100c5565b604051808273ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200191505060405180910390f35b6000600185858585604051806000526020016040526000604051602001526040518085600019166000191681526020018460ff1660ff1681526020018360001916600019168152602001826000191660001916815260200194505050505060206040516020810390808403906000866161da5a03f1151561014257fe5b50506020604051035190505b9493505050505600a165627a7a7230582054abc8e7b2d8ea0972823aa9f0df23ecb80ca0b58be9f31b7348d411aaf585be0029",
            "receipt": {
                "contractAddress": "0x5481c0fe170641bd2e0ff7f04161871829c1902d",
                "gasUsed": 155085,
                "logs": [],
                "status": null
            },
            "gasUsed": 155085
        }
    ]
}
```

 From this JSON output I mainly deduced how I imagined ethereum transactions to work (taking into consideration my knowledge about bitcoin) I was already quite surprised that the Ethereum virtual machine does check the balance and that transactions are not spent by following transactions as in bitcoin. However I thought I could work with the following observations (which I guess I should have double checked in the docs)

This shows that the list of transactions consists essentially of two types of transactions: 
a) Sending ethereum from one account to another one
b) Sending ethereum from one account to a smart contract
as far as I understand the system the sender could also be a smartcontract in both cases. 

Transactions of type (a) are identified by having an "empty" receipt which is identified with a contractAddress of 0x0. Also they seem to have an "empty" input script (though I did not rely on that observation)
Transactions of type (b) are identified by having a a non empty contract address  and some information in the input script. which probably defines the smart contract as itself. As far as I understood the exercise there was no explicit necessity to parse the input script and check what the contract is supposed to do or if it is actually a smart contract at all. 

From there on the exercise seemed straight forward. My machine has 32 GB of main memory and it seems like I should be able to store a Hashmap of necessary data in main memory (the level db has more data than I need and it was only 22 GB). The hashmap should have the the contract addresses as keys and a list of values (taken from each transaction as a value - which was probably a mistake as I should have worked with gas, gasprice and gase used) containing the amount  that is being sent to or from that contract. I decided to internally store amounts sent to that contract address as positive integers and amounts sent from that address as negative integers. I omitted the gas + gas price as I was not sure if it is added to the total transacted values or removed from the final receiped amount or maintained in a different way. I thought I discuss this as a systematical error (however by now I believe this was more a fundamental error). 

That hashmap is built by parsing the json dump (called out.json) which was constucted with the help of the small cpp program. 

Once that hashmap was built it is easy to figure out both questions, actually it would have been possible to answer both questions in one loop over that hashmap.
 
for A) we just have to iterate over the hashmap and build the sum of the elements in the list that was stored as a value and remember the key for which the sum was highest.
for B) we just have to iterate over the hashmap and remember the key for which the value list has the most elements. 

Technically one has to be a little bit smarter in case there are two ore more keys for which the above calculation is a maximum. in this case I just took the first case this happened. 

# Limitations of the soluation
I ran the cpp program to extract 10k blocks as mentioned above. Afterwards I created the python program to build the hashmap index of the relevant data and answer the two questions. 
I already assumed that the program would need to much space if I first extracted all the json with the help of the cpp program: As for size considerations: The rinkesby blockchain was about 22 GB in its leveldb format. The json would be several 100 GB at least. In order to do a better estimation of the size I wanted to make a test run with 100k blocks (in order to see if the size grew roughly linearly with the block number, as I would imagine the blocks in the beginning would be mostly empty) however the third party library always broke shortly after hitting 10k blocks resulting in a crash of the geth node. Since I only had limited time I did not go for debugging this library or exchanging the code. As far as I understood the entire exercise was more meant to see what approach I would choose.  

if a contract can send a tx to itself in order to change the state of the contract this will probably be counted as two transactions. This seems semantically questionable. 

In any case it would have been possible to pipe the output of the c-program directly as the input for the python parser. So I guess I would have added a little bit more snapshopping of my state every 100k blocks so that the program could continue to run in case it crashes. 

# Mistakes made
after running the program I realized 2 things: 
1.) all the smartcontracts have the same address which is weired but maybe specific to the first couple of blocks
2.) the value field in each transaction to a smart contract is empty.
Therefor I probably should have used the gas and gas price in comparison the the gas used within the smart contract. Probably the smart contracts 

# Conclusion
It does not make sense to hack something together without properly understanding the used software. I have never really looked at the ethereum protocol and made many assumptions by transfering from bitcoin. Due to this I could not know or verify if the quickBlock CPP library was working correctly. 
