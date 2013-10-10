# string, in quotes:
print "hellowwwww!"
print 'hello "Jon"'

# numbers, not in quotes
print 20
print 40 + 3
print 15 * 4

# division of ints depends on environment - in DrawBot we get float here:
print 5 / 2

# and int here:
print 5 // 2

# can do some maths with strings
print "Jon is my" + " name"
print "Jon" * 5


print
print "-" * 80
print


# This is a list - like an array
print range(5)
print range(10, 15)

# Basic for loop iterating over list
for x in range(12, 15):
    print x
    

# Define a list directly.  Types can be mixed in lists.
# Useful to think of indexes as 'dividers'
#        0  1       2  3  4
myList = ["a", "Jon", 1, 4, False]
print myList

for item in myList:
    print item
    
# go to divider one, and read the next element
print myList[1]

# go one divider back from the end and read the next element
print myList[-1]

# got to divider one, and read until divider 4 -- ONLY RETURNS 3 ELEMENTS!
print myList[1:4]