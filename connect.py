from pymongo import MongoClient 
from pymongo import errors 

def connectDB():

    connection_string = "mongodb+srv://yeniay:9j9fjtJaUnEgxd9@yeniay.m4idn2i.mongodb.net/"

    try:
        client = MongoClient(connection_string)
        db = client["yeniay"]
        print("Connection established to your db")
        return db
    except Exception as e:
        print(f"An error occurred: {e}")
        return None
def createCollection(db, collection_name):
    try:
        
        if collection_name not in db.list_collection_names():
            db.create_collection(collection_name)
            print(f"Collection '{collection_name}' created.")
        elif collection_name in db.list_collection_names():
            print("Collection already exists")
    except Exception as e:
        print("An error occured: ", e)
def insert_doc(db, collection_name, doc):
    try:
        
        collection = db[collection_name]

        
        result = collection.insert_one(doc)
        doc_id = result.inserted_id
        
        print("Insertion successfully completed")
        print(f"Inserted document ID: {doc_id}")

    except Exception as e:
        print(f"An error occurred: {e}")


def read_all_data(db, collection_name):
    try:
        
        collection = db[collection_name]
        
        result = collection.find()

        for document in result:
            print(document)

    except Exception as e:
        print(f"An error occurred: {e}")


if __name__ == "__main__":
    db = connectDB()
    read_all_data(db,'series')
