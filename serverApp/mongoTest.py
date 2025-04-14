import pymongo
import time

print("hello world!")
user = "user"
password = "steve"
cluster = "cluster0"
dnsprefix = "9heovzz"
connectionUrl = f"mongodb+srv://{user}:{password}@{cluster}.{dnsprefix}.mongodb.net/"

start = time.time()
client = pymongo.MongoClient(connectionUrl)
end = time.time()

print(f"time: {end - start}")

print(f"Ping result: {client.admin.command('ping')}")


db = client.get_database("connect_4")
nodes = db.nodes

nodes.delete_many({})

given = ['0', '1', '1', '1', '0', '1', '0', '1']
result = 0

for bit in given:
    result <<= 1
    if bit == '1':
        result |= 1

byte_value = result.to_bytes(1)#, byteorder="big")    

doc = {
    "_id": '{goes here}',
    "count": 1,
    "wins": 1
}

docs = [
    {"_id": '111111000000111111000000111111000000111101', "count": 1, "wins": 1},
    {"_id": '111111000000111111000000111111000000111110', "count": 1, "wins": 1}
]

nodes.insert_one(doc)
nodes.insert_many(docs)

print(list(nodes.find({})))

# filt = {"name": "bob"}
# res = nodes.delete_one(filt)

# filt2 = {}
# nodes.delete_many(filt2)    