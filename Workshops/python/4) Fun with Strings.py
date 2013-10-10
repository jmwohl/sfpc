import string

# Path as string
textPath = "/Volumes/Big Bro/Users/jon/SfPC/sfpc/Workshops/python/MollyBloomSoliloquyFull.txt"

# Create a read-only file object
textFile = open(textPath, "r")

# print the object
print textFile

# Read the text file
text = textFile.read()
#print text

textLowered = text.lower();

print textLowered.count("the")
print text.count("the")

# CSV Path