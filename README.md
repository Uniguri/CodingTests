# Solution of Coding Tests
- [programmers](https://programmers.co.kr/)
- [Baekjoon](https://www.acmicpc.net/)
- [LeetCode](https://leetcode.com/)

# Utility
- [commit_and_push.sh](./commit_and_push.sh): Add every files, commit with current time and push it.
## Baekjoon
- [make_template.sh](./Baekjoon/compile.sh): Make template folder with problem id. It has two files: solution.cc and testcase.json.
- [compile.sh](./Baekjoon/compile.sh): Compile given file(default: solution.cc) with Baekjoon's compile option. Out file is \[given file without extension\].
- [test_testcase.py](./Baekjoon/test_testcase.py): Test given binary(default: solution) with given test cases(default: testcase.json) and show result.
- [clean.sh](./Baekjoon/clean.sh): Delete every executed file with "solution*".