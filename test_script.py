import subprocess
import os
def run_interpreter(input_data):
    # Determine binary extension dynamically based on the OS platform
    binary_name = './interpreter' if os.name != 'nt' else 'interpreter.exe'
    process = subprocess.Popen(
        [binary_name],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def test_interpreter():
    tests = [
        {
            "input": "5 + 3 * 2\n",
            "expected_output": "11"
        },
        {
            "input": "var a = 10\na + 3\n",
            "expected_output": "10\n13"
        },
        {
            "input": "def f(x) { x * 2 }\nf(5)\n",
            "expected_output": "0\n10",
        },
        {
            "input": "def f(x) { x * 2 }\nintegral(f, 0, 3)\n",
            "expected_output": "0\n9",
        }
    ]

    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_interpreter(input_data)

        clean_lines = []

        for line in output.splitlines():
            line = line.strip()
            if line.startswith("Your result:"):
                clean_lines.append(line.replace("Your result: ", "").strip())
            elif line.isdigit() or (line.replace('.', '',1).isdigit() and "Welcome" not in line and "Enter" not in line):
                clean_lines.appent(line)

        clean_output = "\n".join(clean_lines)
        clean_expected = "\n".join([l.strip() for l in expected_output.splitlines() if l.strip()])

        if error:
            print(f"Test failed for input:\n{input_data}")
        elif clean_output.strip() != clean_expected:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{clean_expected}")
            print(f"Got:\n{clean_output}")
        else:
            print(f"Test passed for input:\n{input_data}")

if __name__ == "__main__":
    test_interpreter()