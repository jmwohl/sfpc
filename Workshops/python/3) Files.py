import string

# Path as string
textPath = "/Volumes/Big Bro/Users/jon/SfPC/sfpc/Workshops/python/someText.txt"

# Create a read-only file object
textFile = open(textPath, "r")

# print the object
print textFile

# Read the text file
text = textFile.read()
print text

print "-" * 80

myName = "Jon Wohl"
print myName
print myName[2:5]

