import string
import re

# Path as string
textPath = "/Volumes/Big Bro/Users/jon/SfPC/sfpc/Workshops/python/meteors.csv"

# Create a read-only file object
textFile = open(textPath, "r")

# print the object
print textFile

# Read the text file
text = textFile.read()

print len(text)

#print text

#lines = text.split(',')

lines = re.split('\r\n', text)
#print lines

#lines = lines[2 - len(lines):len(lines)]

for i, line in enumerate(lines):
    lines[i] = line.split(',')
    
#lines.pop(0)

#print lines

def valueCompare(arr):
        return arr[0]

sortedLines = sorted(lines, key=valueCompare)

print sortedLines

#print text

# CSV Path