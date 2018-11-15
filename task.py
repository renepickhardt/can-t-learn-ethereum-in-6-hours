import json

f = open("out.json", "r")
jsn_str = ""
contract_txs = {}

for line in f:
    if line.startswith("{"):
        jsn_str = ""
    jsn_str += line
    if line.startswith("}"):
        block = json.loads(jsn_str)
        for tx in block["transactions"]:
            if tx["from"] in contract_txs:
                contract_txs[tx["from"]].append(-1 * tx["value"])
            receipt_addr = tx["receipt"]["contractAddress"]
            if receipt_addr == "0x0":
                continue
            else:
                # print(receipt_addr)
                if receipt_addr in contract_txs:
                    contract_txs[receipt_addr].append(tx["value"])
                else:
                    contract_txs[receipt_addr] = [tx["value"]]

print("created contract hashmap")
print("found", len(contract_txs), "contracts")

print("find contract with largest balance")
max_key = None
max_value = 0
for k, v in contract_txs.items():
    s = sum(v)
    if s >= max_value:
        max_key = k
        max_value = s

print("contract: ", max_key, "has balance", max_value)

print("find largest number of tx on behalf of contract")
max_key = None
max_value = 0
for k, v in contract_txs.items():
    s = len(v)
    if s >= max_value:
        max_key = k
        max_value = s

print("contract: ", max_key, "has", max_value, "transactions")
