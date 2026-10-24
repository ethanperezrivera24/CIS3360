#!/bin/bash
case $1 in
    pa01.c)
	rm -f -- a.out
	gcc pa01.c 
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.c failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./a.out"
	;;
    pa01.cpp)
	rm -f -- a.out
	g++ pa01.cpp
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.cpp failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./a.out"
	;;
    pa01.go)
	rm -f -- pa01
	go build pa01.go
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.go failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./pa01"
	;;
    pa01.rs)
	rm -f -- pa01
	rustc pa01.rs
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.rs failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./pa01"
	;;
    pa01.java)
	rm -f -- pa01.class
	javac pa01.java
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.java failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="java pa01"
	;;
    pa01.py)
	EXE="python3 pa01.py"
	;;
*)
    echo "Invalid source file name"
    echo "->  should be pa01.c, pa01.cpp, pa01.go, pa01.java, pa01.rs or pa01.py"
    exit 1
esac

echo "Compile of pa01 succeded."

for i in $(ls i?.txt); do
   echo Processing: $i
   eval $EXE $i 8   # comment this line out by placing a # in front of eval...
   eval $EXE $i 16  # comment this line out by placing a # in front of eval...
   eval $EXE $i 32  # comment this line out by placing a # in front of eval...
done
