import pymongo
import time

file_o = open("./serverApp/creds.txt", "r")
user = file_o.readline().strip()
password = file_o.readline().strip()
cluster = file_o.readline().strip()
dnsprefix = file_o.readline().strip()

print("hello world!")
connectionUrl = f"mongodb+srv://{user}:{password}@{cluster}.{dnsprefix}.mongodb.net/"

start = time.time()
client = pymongo.MongoClient(connectionUrl)
end = time.time()

print(f"time: {end - start}")

print(f"Ping result: {client.admin.command('ping')}")


db = client.get_database("connect_4")
nodes = db.nodes

nodes.delete_many({})

# doc = {
#     "_id": '{goes here}',
#     "count": 1,
#     "wins": 1
# }

# docs = [
#     {"_id": 'AAAA', "count": 1, "wins": 1},
#     {"_id": 'AAIA', "count": 1, "wins": 1}
# ]

# nodes.insert_one(doc)
# nodes.insert_many(docs)

# print(list(nodes.find({})))

# # filt = {"name": "bob"}
# # res = nodes.delete_one(filt)

# # filt2 = {}
# # nodes.delete_many(filt2)    