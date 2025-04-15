
class MongoDao:
    def __init__(self):
        file_o = open("cred.txt", "r")
        self.user = file_o.readline().strip()
        self.password = file_o.readline().strip()
        self.cluster = file_o.readline().strip()
        self.dnsprefix = file_o.readline().strip()

    def postData(data):
        pass
