#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

declare -a tests=(
"VAR test_case_cat.txt"
)

declare -a extra=(
"-s test_1_cat.txt"
"-b -e -n -s -t test_1_cat.txt"
"-t test_3_cat.txt"
"-n test_2_cat.txt"
# "no_file.txt"
"-n -b test_1_cat.txt"
"-s -n -e test_4_cat.txt"
"test_1_cat.txt -n"
"-n test_1_cat.txt"
"-n test_1_cat.txt test_2_cat.txt"
"test_5_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(cmp -s test_s21_cat.log test_sys_cat.log && echo xyq)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "xyq" ]
    then
      (( SUCCESS++ ))
        echo -e "${RED}$FAIL${NC}/${GREEN}$SUCCESS${NC}/$COUNTER ${GREEN}success${NC} cat $t\n"
    else
      (( FAIL++ ))
        echo -e "${RED}$FAIL${NC}/${GREEN}$SUCCESS${NC}/$COUNTER ${RED}fail${NC} cat $t\n"
        
    fi
    rm test_s21_cat.log test_sys_cat.log
}


# rm test_s21_cat.log test_sys_cat.log

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in b e n s t v
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

# 2 параметра
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                var="-$var1 -$var2"
                testing $i
            done
        fi
    done
done

# 3 параметра
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                    var="-$var1 -$var2 -$var3"
                    testing $i
                done
            fi
        done
    done
done

# 4 параметра
for var1 in b e n s t v
do
    for var2 in b e n s t v
    do
        for var3 in b e n s t v
        do
            for var4 in b e n s t v
            do
                if [ $var1 != $var2 ] && [ $var2 != $var3 ] \
                && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${tests[@]}"
                    do
                        var="-$var1 -$var2 -$var3 -$var4"
                        testing $i
                    done
                fi
            done
        done
    done
done

echo -e "${RED}FAIL: $FAIL${NC}"
echo -e "${GREEN}SUCCESS: $SUCCESS${NC}"
echo -e "ALL: $COUNTER"
