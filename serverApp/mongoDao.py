import pymongo
from pymongo import UpdateOne, ReplaceOne
from collections import defaultdict

class MongoDao:
    def __init__(self):
        file_o = open("./serverApp/creds.txt", "r")
        self.user = file_o.readline().strip()
        self.password = file_o.readline().strip()
        self.cluster = file_o.readline().strip()
        self.dnsprefix = file_o.readline().strip()

        self.connectionUrl = f"mongodb+srv://{self.user}:{self.password}@{self.cluster}.{self.dnsprefix}.mongodb.net/"

        self.client = pymongo.MongoClient(self.connectionUrl)

        self.db = self.client.get_database("connect_4")
        self.nodes = self.db.nodes

    def postData(self, data):
        combined = defaultdict(lambda: {"count": 0, "wins": 0})

        for doc in data:
            _id = doc["_id"]
            combined[_id]["count"] += doc["count"]
            combined[_id]["wins"] += doc["wins"]

        final_docs = [{"_id": _id, **values} for _id, values in combined.items()]

        ops = [
            ReplaceOne({"_id": doc["_id"]}, doc, upsert=True)
            for doc in final_docs
        ]

        if ops:
            result = self.nodes.bulk_write(ops)

    def getData(self):
        return list(self.nodes.find({}))
