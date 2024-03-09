import json
import os
import subprocess
import sys
import time


def run_executable_with_input(
    executable_path: str, case_in: str
) -> tuple[str, str, int]:
    """Run executable with specific input.

    Args:
        executable_path (str): the path of executable file.
        case_in (str): the input to be passed to executable.

    Returns:
        tuple[str, str, int]: output and errors of execution and execution time.
    """
    start_time = time.time_ns()
    pipe = subprocess.Popen(
        executable_path,
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    outs, errs = pipe.communicate(input=case_in.encode())
    total_time = time.time_ns() - start_time

    outs = outs.decode().rstrip()
    errs = errs.decode().rstrip()
    return (outs, errs, total_time)


def is_result_correct(output: str, err: str, answer: str) -> bool:
    """Check output is correct and there is no error when testing.

    Args:
        output (str): the output from executable to check.
        err (str): the error from executable.
        answer (str): the correct output.

    Returns:
        bool: True if correct.
    """
    if len(err) != 0:
        return False

    out_list = output.split("\n")
    ans_list = answer.split("\n")
    if len(out_list) != len(ans_list):
        return False
    for i in range(len(out_list)):
        out_line = out_list[i].rstrip(" ")
        ans_line = ans_list[i].rstrip(" ")
        if out_line != ans_line:
            return False

    return True


def is_timeout(exec_time_ns: int, time_limit_ns: int) -> bool:
    return exec_time_ns > time_limit_ns


def test_cases_and_print_result(
    executable_path: str, testcases: list[dict], time_limit_ns: int
) -> int:
    """
    Test executable file.

    Args:
        executable_path (str): executable path to test.
        testcases (list[dict]): list of testcase which contains input list and output list.
        time_limit_ns (int): time limit for execution time in nano seconds.
    Returns:
        int: The number of testcase which executable cannot pass.
    """
    fail_count: int = 0
    for i, tc in enumerate(testcases):
        assert "inputs" in tc and "outputs" in tc
        case_in: str = "\n".join(tc["inputs"]).rstrip()
        case_out: str = "\n".join(tc["outputs"]).rstrip()

        outs, errs, exec_time_ns = run_executable_with_input(
            executable_path, case_in
        )
        if not is_result_correct(outs, errs, case_out):
            fail_count += 1
            print(f"Case {i + 1}: Fail")
            print("==========[ Case input ]==========")
            print(case_in)
            if len(errs) != 0:
                print("==========[ Your error ]==========")
                print(errs)
            else:
                print("==========[ Case output ]==========")
                print(case_out)
                print("==========[ Your output ]==========")
                print(outs)
            print("==================================")
        elif is_timeout(exec_time_ns, time_limit_ns):
            fail_count += 1
            print(f"Case {i+1}: Timeout")
        else:
            print(f"Case {i + 1}: Pass")
    return fail_count


def main(argc: int, argv: list[str]) -> None:
    """Just main function

    Args:
        argc (int): the length of arguments list
        argv (list[str]): arguments list
    """
    executable_path = "./solution"
    testcase_path = "./testcase.json"
    if argc >= 2:
        executable_path = argv[1]
    if argc >= 3:
        testcase_path = argv[2]

    if not os.path.isfile(executable_path):
        print(f"{executable_path}: not found")
        return
    if not os.path.isfile(testcase_path):
        print(f"{testcase_path}: not found")
        return

    with open(testcase_path, "r", encoding="UTF-8") as f:
        testcases_json = json.loads(f.read())
        assert "testcases" in testcases_json
        testcases: list[dict] = testcases_json["testcases"]
        assert "timeout" in testcases_json
        time_limit_s: float = float(testcases_json["timeout"])

    fail_count = test_cases_and_print_result(
        executable_path, testcases, int(time_limit_s * 10**9)
    )
    if fail_count == 0:
        print("\nPass all test cases.")
    else:
        print(f"\nCannot pass {fail_count} test cases")


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
