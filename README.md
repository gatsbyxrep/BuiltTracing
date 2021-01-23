# BuiltTracing
The program for finding a minimum path between two points escaped barriers

![Main window screen](https://i.imgur.com/rFrNbPe.png)

# Guide
Compile the program, create a file with source data:\
n lines with coords of barriers (x,y) separated by spaces\
Points\
Source point coord (x,y)\
Target point coord (x,y)
### Example:
2,1 2,7 3,7\
3.5,6 3.5,8.5 4.5,5\
2.5,8 2.5,10 1,10\
Points\
1,2\
6,9
## Result interpetation:
Yellow curve is the finded by Djikstra alghorithm minimum path\
Red lines is the lines of the barriers\
Black lines is the other lines of the net\
In the text box you can see the result in the text format
# Technical info
Language: C++14\
Compiler: MSVC2019\
GUI: QT


