#!/bin/bash
function convert {
    if [ $# -eq 1 ]; then
        str=$1
        value=0
        for (( i=0; i<${#str}; i++ )); do
            char="${str:$i:1}"
            curr=0

            if [ "$char" == "a" ] || [ "$char" == "A" ]; then
                curr=10
            elif [ "$char" == "b" ] || [ "$char" == "B" ]; then
                curr=11
            elif [ "$char" == "c" ] || [ "$char" == "C" ]; then
                curr=12
            elif [ "$char" == "d" ] || [ "$char" == "D" ]; then
                curr=13
            elif [ "$char" == "e" ] || [ "$char" == "E" ]; then
                curr=14
            elif [ "$char" == "f" ] || [ "$char" == "F" ]; then
                curr=15
            else
                curr=$char
            fi

            value=$((value * 16 + curr))
        done
        echo $value

    else
        mode=$1
        val=$2

        if [ "$mode" = "2" ]; then
            hex=""
            while [ $val -gt 0 ]; do
                rem=$((val % 16))
                if [ $rem -eq 10 ]; then
                    hex="A$hex"
                elif [ $rem -eq 11 ]; then
                    hex="B$hex"
                elif [ $rem -eq 12 ]; then
                    hex="C$hex"
                elif [ $rem -eq 13 ]; then
                    hex="D$hex"
                elif [ $rem -eq 14 ]; then
                    hex="E$hex"
                elif [ $rem -eq 15 ]; then
                    hex="F$hex"
                else
                    hex="$rem$hex"
                fi
                val=$((val / 16))
            done

            if [ -z "$hex" ]; then
                hex="0"
            fi

            echo $hex

        elif [ "$mode" = "1" ]; then
            value=0
            for (( i=0; i<${#val}; i++ )); do
                char="${val:$i:1}"
                curr=0

                if [ "$char" == "a" ] || [ "$char" == "A" ]; then
                    curr=10
                elif [ "$char" == "b" ] || [ "$char" == "B" ]; then
                    curr=11
                elif [ "$char" == "c" ] || [ "$char" == "C" ]; then
                    curr=12
                elif [ "$char" == "d" ] || [ "$char" == "D" ]; then
                    curr=13
                elif [ "$char" == "e" ] || [ "$char" == "E" ]; then
                    curr=14
                elif [ "$char" == "f" ] || [ "$char" == "F" ]; then
                    curr=15
                else
                    curr=$char
                fi

                value=$((value * 16 + curr))
            done

            echo $value
        fi
    fi
}

function checkParen {
    str=$1
    stack=""
    for (( i=0; i<${#str}; i++ )); do
        char="${str:$i:1}"
        if [ "$char" == "(" ];then
            stack="($stack"
        elif [ "$char" == ")" ]; then
            if [ -z "$stack" ]; then
                echo "0"
                return
            fi
            stack="${stack:1}"
        fi
    done
    if [ -z "$stack" ]; then
        echo "1"
    else
        echo "0"
    fi
}
