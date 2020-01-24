
message = "Hello!"
message2 = "Some message with \"extra quotes\""
a = 3
b = a + 2
print(message, message2)
print("a: ", a, "  b: ", b)
print(message2.title())  # prints the string in title-case


# string and variable concatenation
age = 47
message3 = "Happy " + str(age) + "rd Birthday!"
print("\n" + message3)

# Arrays (Lists)
myList = ["Mike", "Sally", "Susan"]
print("Initial List: ",myList)
print("Index 2: ", myList[2])
print("List length: ", len(myList))
myList.append("Lisa")
print("Adding Lisa; new list: ", myList)

name = myList.pop(1)
print("Popping index 1: ", myList, " ... Removed: ", name )

# This fails because Idiot isn't in the list.  Seems strange that the API can't accept incorrect values.
# myList.remove("Idiot")
# print("Removed: Idiot ", myList)

myList.remove("Mike")
print("Removed: Mike ", myList)


# For loops.  Indenting is what defines what belongs inside the for loop.  (I don't love that...)
print("\nNames in list printed from for loop")
for name in myList:
    print(name)

# a list of numbers
numbers = list(range(1,6)) # includes 1 through 5.
print("\nNumbers List: ", numbers)

print("\nGenerating list of squares from 1 to 10:")
squares = []
for value in range(1,11):
    square = value ** 2
    squares.append(square)
print(squares)
print("Min:", min(squares), " Max:", max(squares), " Sum:", sum(squares))

#another way of creating the list by embedding the for loop inside the list creation:
print("\nAnother way to create the same list:")
squares2 = [value**2 for value in range(1,11)]
print(squares2)

print(squares2[0:2]) # prints the 1st and 2nd items of the list
print(squares2[-3:]) # prints the last 3 elements of the list

# making a copy of a list
squares_pointer = squares2  # this doesn't make a copy, just points to the old list.
squares_copy = squares2[:]  # this makes a copy   (or:  squares2.copy())
for i in range(4,6) :
    del squares_copy[i] # del to remove an item by index.  (use pop if you want to get the value being removed)
print("\nOriginal: ", squares2)
print("Copy with some removed: ", squares_copy)
# note that the result is strange:  16, 36, 64.  It removed the 4th element (25), and then the 5th element of the NEW list
# (which used to be 36 but is now 49!!!!)  So 36 remains.
# resolved:
squares_copy2 = squares2[:]
del squares_copy2[4:6]  # deletes indices 4 and 5 from _copy2 of the list.
print("New copy with correct indices 4 and 5 removed: ", squares_copy2 )

squares_subset = squares[5:8] # creates a new list that is a subset of the original
print("Subset: ", squares_subset, "\n")

# combining lists
list1 = [ "blue", "red", "green"]
list2 = [ "yellow", "brown", "orange"]
colours = list1 + list2
print("Colours: ", colours, "\n")

# if statements
age1 = 12
age2 = 14
if (age1 > 11) and (age2 < 16):
    print("They're ready for Disney!")
elif ( age2 >= 16 ) :
    print("Too old...")
else:
    print("Some other situation")
   

# Dictionary:  a hashmap
person = {
    'name' : "Mike",
    'age' : 47
    }

print(person)
print(person['age'])

# Strongly-typed
a = 3 # int
b = 3.1415927 # float
c = "Fred"  # str
print( "A:", type(a), " B:", type(b), " C:", type(c) )

d = "34"
e = int(d)  # converts from str to int
print(e)


# creates a dictionary where each key/value pair contains a set as a value (set is an unordered list)
drinks = {
    'martini': {'vodka', 'vermouth'},
    'black russian': {'vodka', 'kahlua'},
    'white russian': {'cream', 'kahlua', 'vodka'},
    'manhattan': {'rye', 'vermouth', 'bitters'},
    'screwdriver': {'orange juice', 'vodka'}
}
print(drinks)

# while
count = 1
numbers2 = []
while count <= 5:
    numbers2.append(count)
    count += 1
print("Number list generated from while loop: ", numbers2)

# comprehension:
number_list = [(number-1) for number in range(1,6)]
print("Number list generated from comprehension: ", number_list)

# more complex comprehension example
a_list = [number for number in range(1,6) if number % 2 == 1]
print( "Complex list: ", a_list )

# comprehension in dictionary
word = 'letters'
letter_counts = {letter: word.count(letter) for letter in word}
print("Letter counts: ", letter_counts)

# function
def myFunction( param1 ): 
    print(param1.upper())
    return True

myFunction( "Crapioca pudding")
# myFunction( 1.34 ) # causes it to fail because a float doesn't have ".upper()"

def Func2( name, address, phone) :
    'This is the docstring for this function'
    return{ 'Name': name, 'Address' : address, 'PhoneNumber' : phone }

#now call Func2 with params out of order
p1 = Func2( address="68 Cedar Valley", name="Mike", phone="555-3111")
print(p1) # prints in the correct order (Name/Address/Phone)

#function with variable number of args:
def Func3( *args ) :
    print("Number of arguments: ", len(args))
    print( "Arguments: ", args )

Func3( "blue", "yellow", "gold", 34 )

#passing a function to another function
def Func4( func, *args ) :
    print( "Calling ", func.__name__, " with ", len(args), " arguments.")
    func( args )

Func4( Func3, "red", "green", 4, 5, 6)

