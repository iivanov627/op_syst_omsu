#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo "First line" > alpha.txt
echo "aboba line" >> alpha.txt

echo -e "Row 1\n\n\nRow 4" > beta.txt
echo -e "\tTabbed\nFinishx" >> beta.txt

tests=(
  "alpha.txt"
  "-b beta.txt"
  "-E beta.txt"
  "-n alpha.txt"
  "-s beta.txt"
  "-T beta.txt"
  "-v beta.txt"

  "--number alpha.txt"
  "--number-nonblank beta.txt"
  "--squeeze-blank beta.txt"

  "-n alpha.txt beta.txt"
  "-nb alpha.txt"
  "-bn alpha.txt"
  "-ens beta.txt"
  "-Tv beta.txt"
)

SUCCESS=0
FAIL=0
TOTAL=0

echo "===== s21_cat tests ====="
echo

for t in "${tests[@]}"; do
  ((TOTAL++))

  cat $t > cat_ref.txt 2>/dev/null
  ./cat $t > cat_test.txt 2>/dev/null

  if diff cat_ref.txt cat_test.txt >/dev/null; then
    echo -e "Test $TOTAL: cat $t ${GREEN}PASSED${NC}"
    ((SUCCESS++))
  else
    echo -e "Test $TOTAL: cat $t ${RED}FAILED${NC}"
    ((FAIL++))
  fi
done

rm -f alpha.txt beta.txt cat_ref.txt cat_test.txt

echo
echo "Results: $SUCCESS/$TOTAL"

if [ $FAIL -ne 0 ]; then
  exit 1
fi
