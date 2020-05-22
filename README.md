# trainee-cpp-sort

## About

trainee-cpp-sort is a program that has been developed from the beginning and should be an imitation of the standard sort 
command. It was only developed for learning and testing purposes, so I cannot guarantee that it will work perfectly with
a real complicated program.

quick sort and merge sort algorithm have also been added to the program, so that with various sort options you have ample
opportunities to simplify your work.


To learn more about what they mean and what they are for, see the bunch of sort options below.
### Parameters
| short Options | long Options      |                 Usage |
| ----------- | ----------- |  ---------------- |
| -b  | --ignore-leading-blanks   |    Ignore leading blanks.       |
| -f  | --ignore-case   |    Ignore case e.g (uppercase or lowercase) this would be ignored.       |
| -n  | --numeric-sort   |    Numeric sort from the lowest the highest.       |
| -o  | --output[ARG required]   |    Write result in FILE instead of standard output.       |
| -r  | --reverse   |    Reverse the result of sorting.       |
| -R  | --random-sort   |    Sort the keys using a random hash.       |
| -u  | --unique   |    Only output the first of several matches.       |
| -q  | --quick-sort | Use quick sort Algorithm.       |
| -m  | --merge-sort  | Use merge sort Algorithm.       |
| -h  | --help  | Display this help and exit the Program.       |


### Examples of sort commandos..

First of all we have to compile our code and this is done by doing the command as follows ``g++ -o output main.cpp``. 
And the compiled code is saved in the ``output`` file as ``binary code``.

Now we can e.g. execute this command to sort the contents of the ``in.txt`` file ``numeric-sort``.
content of ``in.txt`` file:
```
4
9
6
15
10
3
12
8
7
```
The output looks like this, if you run this command 
``./output -n in.txt`` OR ``./output -n < in.txt``.
```
3
4
6
7
8
9
10
12
15
```

if you would like to sort with quick sort or merge sort you only have to change a little bit when executing 
the commands as follows``./output -q -n in.txt`` OR ``./output --quick-sort -n < in.txt`` 

And we do the same with merge sort``./output -m -n in.txt`` OR ``./output --merge-sort -n < in.txt``.
They all work like clockwork.


And if you want to store the sorted values ​​in a new file, you only have to do as follows.. 

``./output -n -o output.txt in.txt`` OR ``./output -n --output output.txt < in.txt``
 then check the ``output.txt`` file.
 
 
 
 
I hope you have as much fun with it as I have when coding
and would be very happy if you would develop the program further or if you could give me suggestions how I can do it even better ..

Thank you :+1: