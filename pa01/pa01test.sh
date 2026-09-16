#!/bin/bash

case $1 in
    pa01.c)
    rm -f -- pa01
    gcc pa01.c -o pa01
    if [ $? -ne 0 ]; then
    	echo "Compile of pa01.c failed"
    	echo "Good bye!"
    	exit 1
    fi
    EXE="./pa01"
    ;;
    pa01.cpp)
    rm -f -- pa01
    g++ pa01.cpp -o pa01
    if [ $? -ne 0 ]; then
    	echo "Compile of pa01.cpp failed"
    	echo "Good bye!"
    	exit 1
    fi
    EXE="./pa01"
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
*)
    echo "Invalid source file name"
    echo "-> should be pa01.c, pa01.cpp, pa01.go, pa01.java, pa01.py or pa01.rs"
    exit 1
esac

echo "Compile of pa01 succeeded."

echo "Case #1"
eval $EXE k1.txt p1.txt >stu1Output.txt
diff -w stu1Output.txt base1.txt>/dev/null
error=$?
if [ $error -eq 0 ]
then
	echo " -> program output matched expected"
  	echo " -> Case #1 - complete"
elif [ $error -eq 1 ]
then
	echo "Output on the left, expected on the right"
	echo "Output mismatch -> "
	echo " check for errors in formatting & encryption"
	diff -w --side-by-side stu1Output.txt base1.txt
	echo "Case #1 - failed"
	exit
else
	echo "There was something wrong with the diff command"
	exit
fi

echo "Case #1 - complete"


echo "Case #2"
eval $EXE k2.txt p2.txt >stu2Output.txt
diff -w stu2Output.txt base2.txt>/dev/null
error=$?
if [ $error -eq 0 ]
then
	echo " -> program output matched expected"
	echo " -> Case #2 - complete"
elif [ $error -eq 1 ]
then
	echo "Output on the left, expected on the right"
	echo "Output mismatch -> "
	echo " check for errors in formatting & encryption"
	diff -w --side-by-side stu2Output.txt base2.txt
	echo "Case #2 - failed"
	exit
else
	echo "There was something wrong with the diff command"
	exit
fi


echo "Case #2 - complete"

echo "Case #3"
eval $EXE k3.txt p3.txt >stu3Output.txt
diff -w stu3Output.txt base3.txt>/dev/null
error=$?
if [ $error -eq 0 ]
then
	echo " -> program output matched expected"
	echo " -> Case #3 - complete"
elif [ $error -eq 1 ]
then
	echo "Output on the left, expected on the right"
	echo "Output mismatch -> "
	echo " check for errors in formatting & encryption"
	diff -w --side-by-side stu3Output.txt base3.txt
	echo "Case #3 - failed"
	exit
else
	echo "There was something wrong with the diff command"
	exit
fi


echo "Case #3 - complete"

echo "Case #4"
eval $EXE k4.txt p4.txt >stu4Output.txt
diff -w stu4Output.txt base4.txt>/dev/null
error=$?
if [ $error -eq 0 ]
then
	echo " -> program output matched expected"
	echo " -> Case #4 - complete"
elif [ $error -eq 1 ]
then
	echo "Output on the left, expected on the right"
	echo "Output mismatch -> "
	echo " check for errors in formatting & encryption"
	diff -w --side-by-side stu4Output.txt base4.txt
	echo "Case #4 - failed"
	exit
else
	echo "There was something wrong with the diff command"
	exit
fi

echo "Case #4 - complete"


echo "Case #5"
eval $EXE k5.txt p5.txt >stu5Output.txt
diff -w stu5Output.txt base5.txt>/dev/null
error=$?
if [ $error -eq 0 ]
then
	echo " -> program output matched expected"
	echo " -> Case #5 - complete"
elif [ $error -eq 1 ]
then
	echo "Output on the left, expected on the right"
	echo "Output mismatch -> "
	echo " check for errors in formatting & encryption"
	diff -w --side-by-side stu5Output.txt base5.txt
	echo "Case #5 - failed"
	exit
else
	echo "There was something wrong with the diff command"
	exit
fi

echo "Case #5 - complete"
echo "Hill Cipher testing completed"
